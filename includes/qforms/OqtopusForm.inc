<?php
    /**
     * Abstract class to provide the common part of all Oqtopus pages
     *
     * Remember that inheriting classes must call parent::Form_Create()
     *
     * @author Kung den Knege <kungdenknege@gmail.com>
     * @package oqtopus
     * @subpackage qforms
     */
    abstract class OqtopusForm extends QForm {
        private $strInnerHtml;
        
        protected $txtOQUsername;
        protected $txtOQPassword;
        protected $btnOQOk;
        protected $btnOQRegisterAsSeller;
        protected $btnOQRegisterAsBuyer;
        private $mcMenu;
        private $objSeller;
        private $pnlRightIn;
        private $pnlRightOut;
        
        protected function Form_Create() {
			$this->pnlRightIn = new QPanel($this, 'pnlRightIn');
			$this->pnlRightIn->Template = sprintf('%s%s.pnlRightIn.inc', __TEMPLATES__, __CLASS__);
			$this->pnlRightIn->Visible = (bool)Security::Current();
			
			$this->pnlRightOut = new QPanel($this, 'pnlRightOut');
			$this->pnlRightOut->Template = sprintf('%s%s.pnlRightOut.inc', __TEMPLATES__, __CLASS__);
			$this->pnlRightOut->Visible = !(bool)Security::Current();
			        	
            $this->txtOQUsername = new QTextBox($this->pnlRightOut, "txtOQUsername");
            $this->txtOQUsername->Required = false;
            $this->txtOQUsername->Name = _tr("Username");
            
            $this->txtOQPassword = new QTextBox($this->pnlRightOut, "txtOQPassword");
            $this->txtOQPassword->Required = false;
            $this->txtOQPassword->Name = _tr("Password");
            $this->txtOQPassword->TextMode = QTextMode::Password;
            $this->txtOQPassword->AddAction(new QEnterKeyEvent(), new QAjaxAction('DoLogin'));
            $this->txtOQPassword->AddAction(new QEnterKeyEvent(), new QTerminateAction());
            
            $this->btnOQRegisterAsSeller = new ButtonLink($this->pnlRightOut, 'btnOQRegisterAsSeller', Navigation::CreateUrl('SellersRegisterForm'));
            $this->btnOQRegisterAsSeller->Text = _tr('Register as seller');
            
            $this->btnOQRegisterAsBuyer = new ButtonLink($this->pnlRightOut, 'btnOQRegisterAsBuyer', Navigation::CreateUrl('BuyersRegisterForm'));
            $this->btnOQRegisterAsBuyer->Text = _tr('Register as buyer');

        	$this->btnOQOk = new QButton($this->pnlRightOut, "btnOQOk");
            $this->btnOQOk->Text = _tr("Login");
            $strCondition = "qcodo.getControl('txtOQUsername').value != '' && qcodo.getControl('txtOQPassword').value != ''";
            $this->btnOQOk->AddAction(new QClickEvent(0, $strCondition), new QAjaxAction("DoLogin"));
            $this->btnOQOk->CausesValidation = false;
			
			$this->mcMenu = new MenuControl($this, 'top');
			$this->mcMenu->Menu = $this->PrepareMenu();
        }
        
        protected function Render($strAlternateHtmlFile) {
            $this->strInnerHtml = $strAlternateHtmlFile;
            require(sprintf('%s%s.inc', __TEMPLATES__, __CLASS__));
        }
                
        private function RenderInnerPage() {   
                if ($this->strInnerHtml)
			require($this->strInnerHtml);
    		else
    			require(QApplication::$ScriptFilename . '.inc');        
        }
        
        protected function DoLogin() {
            try {
                $login = Security::AuthLogin($this->txtOQUsername->Text, $this->txtOQPassword->Text);
                if ($login->Role == Role::Seller)
                	if ($objSellers = $login->GetSellerArray(null, '1'))
                		$this->Seller = $objSellers[0];
                
                // Deselect first menupost
                $objTemp = $this->mcMenu->Menu;
                $objTemp->Selected = null;
                $this->GetControl('objMenu')->Selected = $this->GetControl('objAccountMenu');
                // Go home if on MainForm or ActivateForm, otherwise refersh
                if (QApplication::$FormName == 'MainForm' || QApplication::$FormName == 'ActivateForm')
                	Navigation::Home();
                else
					Navigation::Refresh();
            } catch (AuthenticationException $e) {
                // Set error message
                switch ($e->ErrorCause) {
                    case AuthenticationErrorCause::Username:
                        $this->txtOQPassword->Warning = $e->getMessage();
                        break;
                    
                    case AuthenticationErrorCause::Password:
                        $this->txtOQPassword->Warning = $e->getMessage();
                        break;
                }
            } 
        }
        
        public function __get($strName) {
        	switch ($strName) {
        		case 'CssFile':
        			if (QApplication::IsBrowser(QBrowserType::InternetExplorer))
        				return 'ie.css';
        			else
        				return 'CSS.css';
        			break;
        			
				case 'Seller':
					if (isset($_SESSION['currentseller']))
						return $_SESSION['currentseller'];
					else 
						return null;        			
        			
        		default:
        			try {
        				return parent::__get($strName);
        			} catch (QCallerException $e) {
        				$e->IncrementOffset();
        				throw $e;
        			}
        	}
        }
        
        private function PrepareMenu() {
        	$objMenu = new Menu(null, $this->mcMenu, 'objMenu');
        		$objAccount = new Menu(mb_strtoupper(_tr('Account')), $objMenu, 'objAccountMenu');        	
        		$objAccount->Visible = false;
        	if (Security::Current()) {
				$objAccount->Visible = true;

        		
        		foreach (MediaType::$MediaType as $intMediaTypeId => $strMediaTypeName)
					if (MediaType::$MediaSubType[$intMediaTypeId]) {
						$objMediaType = new Menu(mb_strtoupper($strMediaTypeName), $objMenu);
						$objMediaType->LinkForm = 'BrowseForm';
						$objMediaType->Arg1 = $intMediaTypeId;
						foreach (MediaType::$MediaSubType[$intMediaTypeId] as $intMediaSubTypeId => $strMediaSubTypeName)
							$objMediaSubType = new MenuItem(mb_strtoupper($strMediaSubTypeName), Navigation::CreateUrl('BrowseForm', $intMediaTypeId, $intMediaSubTypeId), $objMediaType);
					} else {
						$objMediaType = new Menu(mb_strtoupper($strMediaTypeName), $objMenu);
						$objMediaType->LinkForm = 'BrowseForm';
						$objMediaType->Arg1 = $intMediaTypeId;
					}
					
					$objSearch = new Menu(mb_strtoupper(_tr('Search')), $objMenu);
					$objSearch->LinkForm = 'SearchForm';
        	} else {
        		$objAccount = new MenuItem(mb_strtoupper(_tr('Account')), sprintf("javascript:alert('%s')", _tr('Please log in first!')), $objMenu);
        		
        		foreach (MediaType::$MediaType as $intMediaTypeId => $strMediaTypeName)
						$objMediaType = new MenuItem(mb_strtoupper($strMediaTypeName), sprintf("javascript:alert('%s')", _tr('Please log in first!')), $objMenu);
					
					$objSearch = new MenuItem(mb_strtoupper(_tr('Search')), sprintf("javascript:alert('%s')", _tr('Please log in first!')), $objMenu);
        	}
        	
        		if (Security::Current()->Role == Role::Buyer) {

					$objAccount->LinkForm = 'BuyersNewsForm';
					$objConclusion = new MenuItem(_tr('Conclusion'), Navigation::CreateUrl('BuyersNewsForm'), $objAccount);					
					$objBid = new MenuItem(_tr('My bids'), Navigation::CreateUrl('BuyersBidsForm'), $objAccount);
					$objNetworks = new MenuItem(_tr('My campaign networks'), Navigation::CreateUrl('BuyersNetworksForm'), $objAccount);					
					$objSettings = new MenuItem(_tr('Settings'), Navigation::CreateUrl('BuyersSettingsForm'), $objAccount);
				
					        	$objLogOut = new Menu(mb_strtoupper(_tr('Logout')), $objMenu);
        	$objLogOut->AddAction(new QClickEvent(), new QAjaxAction('Logout'));
				
        		} elseif (Security::Current()->Role == Role::Seller) {
        			$objAccount->LinkForm = 'SellersNewsForm';
        			$objConclusion = new MenuItem(_tr('Conclusion'), Navigation::CreateUrl('SellersNewsForm'), $objAccount);
					$objAds = new MenuItem(_tr('My ads'), Navigation::CreateUrl('AdsForm'), $objAccount);
					$objSellersBids = new MenuItem(_tr('Received bids'), Navigation::CreateUrl('SellersBidsForm'), $objAccount);
					$objSellersNetworks = new MenuItem(_tr('My campaign networks'), Navigation::CreateUrl('SellersNetworksForm'), $objAccount);
					$objSettings = new MenuItem(_tr('Settings'), Navigation::CreateUrl('SellersSettingsForm'), $objAccount);

        	$objLogOut = new Menu(mb_strtoupper(_tr('Logout')), $objMenu);
        	$objLogOut->AddAction(new QClickEvent(), new QAjaxAction('Logout'));        		
        		}
        	


			return $objMenu;
        }
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Seller':
					$_SESSION['currentseller'] = QType::Cast($mixValue, 'Seller');
					break;
					
				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		protected function LoadSeller() {
			if (isset($_GET['arg1']) && $objSeller = Seller::Load($_GET['arg1']))
				 return $objSeller;
			if (!isset($_GET['arg1']) && $this->Seller)
				return $this->Seller;				 
			
			throw new NoSuchObjectException();
		}
		
		protected function LoadLogin() {
			if (isset($_GET['arg1']) && $objLogin = Login::Load($_GET['arg1']))
				return $objLogin;
			if ($objLogin = Security::Current())
				return $objLogin;
				
			throw new NoSuchObjectException();
		}
		
		protected function Logout() {
			Security::Logout();
			
			$_SESSION = null;
			session_destroy();
			Navigation::MainForm();
		}
    }
?>
