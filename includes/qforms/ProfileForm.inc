<?php
	/**
	 * Display a sellers info and ads
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage qforms
 	 */
	class ProfileForm extends OqtopusForm {
		// Initial form
		protected $dtgSIMs;
		protected $dtgAds;
		protected $lblSellerName;

		// pnlSellerInfo	
		protected $pnlSellerInfo;
		protected $lblSellerNumber;
		protected $lblSellerContactName;
		protected $lblSellerContactPhone;
		protected $lblSellerContactAdress;
		protected $lblSellerContactEmail;
		protected $pnlSellerDesc;
		
		// Networks
		protected $pnlNetwork;
		protected $lbNetworks;
		protected $btnApplyForNetwork;
		protected $lblNetworkInfo;	
		protected $pnlNetworkDescription;
		
		protected $objSimPnl;
		protected $objAdPnl;

		// Helper objects
		protected $objCache;
		protected $objSeller;
		protected $objSelectedAd;	
		protected $blnNetworkCache = null;	
		public $intSelected;
		
		protected function Form_Create() {
			$this->objSeller = $this->LoadSeller();
			
			Security::VerifyAccess(Actions::SeeProfile, $this->objSeller);
			
			// Call parent constructor
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			// Initialize object cache - stores objects between initial form load and ad select
				$this->objCache = new ObjectCache();
			
			// Initialize datagridcolumns
				//$dgcMediaType = new QDataGridColumn(_tr('Medium'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . (MediaType::$MediaType[$_ITEM->MediaType]) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ? >');
				//$dgcMediaType->SortByCommand = 'media_type';
			
				$dgcMediaSubType = new QDataGridColumn(_tr('Medium'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->MediaSubType ? MediaType::$MediaSubType[$_ITEM->MediaType][$_ITEM->MediaSubType] : "-") . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcMediaSubType->SortByCommand = 'media_sub_type';
			
				$dgcName = new QDataGridColumn(_tr('Name'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_FORM->CreateSelectButton($_ITEM, $_CONTROL)) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcName->SortByCommand = 'name ASC';
				$dgcName->ReverseSortByCommand = 'name DESC';
			
				$dgcReach = new QDataGridColumn(_tr('Reach'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->Reach) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcReach->SortByCommand = 'reach ASC';
				$dgcReach->ReverseSortByCommand = 'reach DESC';
			
				$dgcPrice = new QDataGridColumn(_tr('Requested price'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->Price) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcPrice->SortByCommand = 'price ASC';
				$dgcPrice->ReverseSortByCommand = 'price DESC';
			
				$dgcArea = new QDataGridColumn(_tr('Area'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . (Areas::$Areas[$_ITEM->Area]) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcArea->SortByCommand = 'area';
			
				$dgcEndDate = new QDataGridColumn(_tr('Publication date'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->PublicationDate && !$_ITEM->PublicationDate->IsNull() ? $_ITEM->PublicationDate->PHPDate(Localization::$DateFormat) : "-") . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcEndDate->SortByCommand = 'publication_date ASC';
				$dgcEndDate->ReverseSortByCommand = 'publication_date DESC';
			
				//$dgcSelect = new QDataGridColumn(null, '<?= $_FORM->CreateSelectButton($_ITEM, $_CONTROL) ? >');
			
			// Initialize datagrids
				$this->dtgAds = new QDataGrid($this, 'dtgAds');
				$objAdPag = new QPaginator($this->dtgAds);
				$objAdPag->CssClass='Resultat';
				$this->dtgAds->AddColumn($dgcName);
				//$this->dtgAds->AddColumn($dgcMediaType);
				$this->dtgAds->AddColumn($dgcMediaSubType);
				$this->dtgAds->AddColumn($dgcReach);
				$this->dtgAds->AddColumn($dgcPrice);
				$this->dtgAds->AddColumn($dgcArea);
				//$this->dtgAds->AddColumn($dgcSelect);
				$this->dtgAds->Name = _tr('Prices');
				$this->dtgAds->UseAjax = true;
				$this->dtgAds->Persistent = true;
				$this->dtgAds->Paginator = $objAdPag;
				$this->dtgAds->ItemsPerPage = 6;
				
				$this->dtgSIMs = new QDataGrid($this, 'dtgSIMs');
				$objSIMPag = new QPaginator($this->dtgSIMs);
				$objSIMPag->CssClass='Resultat';
				$this->dtgSIMs->AddColumn(clone $dgcName);			
				//$this->dtgSIMs->AddColumn(clone $dgcMediaType);
				$this->dtgSIMs->AddColumn(clone $dgcMediaSubType);
				$this->dtgSIMs->AddColumn(clone $dgcReach);
				$this->dtgSIMs->AddColumn(clone $dgcPrice);
				$this->dtgSIMs->AddColumn(clone $dgcArea);
				$this->dtgSIMs->AddColumn($dgcEndDate);
				//$this->dtgSIMs->AddColumn(clone $dgcSelect);
				$this->dtgSIMs->Name = _tr('Discounts');
				$this->dtgSIMs->UseAjax = true;
				$this->dtgSIMs->Persistent = true;
				$this->dtgSIMs->Paginator = $objSIMPag;
				$this->dtgSIMs->ItemsPerPage = 6;
				
			// Initialize seller name label
				$this->lblSellerName = new QLabel($this, 'lblSellerName');
				$this->lblSellerName->Text = $this->objSeller->SellerName;

			// Initialize seller info			
				$this->pnlSellerInfo = new QPanel($this, 'pnlSellerInfo');
				$this->pnlSellerInfo->Template = sprintf("%s%s.pnlSellerInfo.inc", __TEMPLATES__, __CLASS__);
			
				$this->lblSellerNumber = new QLabel($this->pnlSellerInfo, 'lblSellerNumber');
				$this->lblSellerNumber->Name = _tr("D&B D-U-N-S number");
				$this->lblSellerNumber->Text = $this->objSeller->OrganizationNumber;
			
				$this->lblSellerContactName = new QLabel($this->pnlSellerInfo, 'lblSellerContactName');
				$this->lblSellerContactName->Name = _tr('Name of contact person');
			
				$this->lblSellerContactAdress = new QLabel($this->pnlSellerInfo, 'lblSellerContactAdress');
				$this->lblSellerContactAdress->Name = _tr('Address of contact person');

				$this->lblSellerContactPhone = new QLabel($this->pnlSellerInfo, 'lblSellerContactPhone');
				$this->lblSellerContactPhone->Name = _tr('Phone number to contact person');
			
				$this->lblSellerContactEmail = new QLabel($this->pnlSellerInfo, 'lblSellerContactEmail');
				$this->lblSellerContactEmail->Name = _tr('Email to contact person');
				
				$this->pnlSellerDesc = new QLabel($this->pnlSellerInfo, 'pnlSellerDesc');
				$this->pnlSellerDesc->Name = _tr('NetworkDescription');
			
			// Fill sellerinfo with data
				$this->lblSellerContactName->Text = $this->objSeller->Name;
				$this->lblSellerContactAdress->Text = sprintf("%s\n %s %s", $this->objSeller->Address, $this->objSeller->Postal, $this->objSeller->City);
				$this->lblSellerContactPhone->Text = $this->objSeller->Phone;
				$this->lblSellerContactEmail->Text =  $this->objSeller->Email;
				$this->pnlSellerDesc->Text = $this->objSeller->Description;
				
			// Initialize network panel
				$this->pnlNetwork = new QPanel($this, 'pnlNetwork');
			
				$this->lbNetworks = new QListBox($this->pnlNetwork, 'lbNetworks');
				$this->lbNetworks->Name = _tr('Campaign networks');
				$this->lbNetworks->AddAction(new QChangeEvent(), new QAjaxAction('UpdateNetwork'));
				foreach ($this->objSeller->GetNetworkArray() as $objNetwork)
						$this->lbNetworks->AddItem($objNetwork->Name, $objNetwork);
			
				$this->btnApplyForNetwork = new QButton($this->pnlNetwork, 'btnApplyForNetwork');
				$this->btnApplyForNetwork->Text = _tr('Apply');
				$this->btnApplyForNetwork->CausesValidation = false;
				$this->btnApplyForNetwork->AddAction(new QClickEvent(), new QAjaxAction('ApplyForNetwork'));
				
				$this->pnlNetwork->Visible = $this->lbNetworks->ItemCount && Security::CheckAccess(Actions::SeeNetworks, $this->objSeller);;
				$this->pnlNetwork->Template = sprintf('%s%s.pnlNetwork.inc', __TEMPLATES__, __CLASS__);
				
				$this->lblNetworkInfo = new QLabel($this->pnlNetwork, 'lblNetworkInfo');
				$this->lblNetworkInfo->Visible = false;
				
				$this->pnlNetworkDescription = new QPanel($this, 'pnlNetworkDescription');
				$this->pnlNetworkDescription->Name = _tr('Description');
				
				if ($this->lbNetworks->ItemCount) {
					$this->lbNetworks->GetItem(0)->Selected = true;
					$this->UpdateNetwork();									
				} else
					$this->pnlNetwork->Visible = false;
					
				// Initialize AdPanel
				$this->objSimPnl = new AdPanel($this, 'objSimPnl');
				$this->objAdPnl = new AdPanel($this, 'objAdPnl');
		}
		
		protected function Form_PreRender() {
			// Update datagrids if needed
			if ($this->dtgAds->Update) {
				$this->dtgAds->TotalItemCount = count(Ad::LoadArrayBySellerAndType($this->objSeller, AdType::STD));
				$this->dtgAds->DataSource = Ad::LoadArrayBySellerAndType($this->objSeller, AdType::STD, false, $this->dtgAds->SortInfo, $this->dtgAds->LimitInfo);
			}
				
			if ($this->dtgSIMs->Update) {
				$this->dtgSIMs->TotalItemCount = count(Ad::LoadSimArrayBySellerAndLogin($this->objSeller, Security::Current()));
				$this->dtgSIMs->DataSource = Ad::LoadSimArrayBySellerAndLogin($this->objSeller, Security::Current(), $this->dtgSIMs->SortInfo, $this->dtgSIMs->LimitInfo);
			}
			
			// Open get-ad if we haven't clicked any button, hence requestmode isn't ajax
			if (isset($_GET['arg2']) && QApplication::$RequestMode != QRequestMode::Ajax) {
				$this->DoSelectAd($this->strFormId, null, $_GET['arg2']);
			}
			
			// Disable apply-button if bidding. We have to cache whether it's old state to reset it later
			// Terribly ugly, but is there a better way?
			if ($this->objAdPnl->IsBidding || $this->objSimPnl->IsBidding) {
				$this->lbNetworks->Enabled = false;
				$this->blnNetworkCache = $this->btnApplyForNetwork->Enabled;
				$this->btnApplyForNetwork->Enabled = false;
			} elseif ($this->blnNetworkCache !== null) {
				$this->lbNetworks->Enabled = true;
				$this->btnApplyForNetwork->Enabled = $this->blnNetworkCache;
				$this->blnNetworkCache = null;
			}
		}
		
		protected function Form_Load() {
			// Clear networks text
				$this->lblNetworkInfo->Visible = false;
				
			// Make sure dtgs refresh, so that buttons get enabled or disabled depending on AdPanel->pnlMakeBid
				$this->dtgAds->MarkAsModified();
				$this->dtgSIMs->MarkAsModified();
				
			// Reset AdPanel
			$this->objAdPnl->Reset();
		}
		
		/**
		 * Render select-button for ad
		 *
		 * @param Ad $objAd
		 * @param QControl $objParent
		 */
		public function CreateSelectButton($objAd, $objParent) {
			$id = "btnSelect" . $objAd->Id;
			
			$btnSelect = null;
			if (!($btnSelect = $this->getControl($id))) {
				$btnSelect = new LinkButton($objParent, $id);
				$btnSelect->CausesValidation = false;
				$btnSelect->AddAction(new QClickEvent(), new QAjaxAction('DoSelectAd'));
				$btnSelect->Text = $objAd->Name;
				$btnSelect->ActionParameter = $objAd->Id;
				//$btnSelect->CssClass = 'btnSelect';
			}
			
			//$btnSelect->Enabled = !($this->objSimPnl->IsBidding || $this->objAdPnl->IsBidding);
			
			return $btnSelect->Render(false);
		}
		
		protected function DoSelectAd($strFormId, $strControlId, $strParameter) {
			$objAd = $this->dtgAds->GetObjectFromDataSource('Id', $strParameter);
			if (!$objAd)
				$objAd = $this->dtgSIMs->GetObjectFromDataSource('Id', $strParameter);
			if (!$objAd)
				throw new NoSuchObjectException();
				
			$this->intSelected = $objAd->Id;
			$this->objAdPnl->DoMakeBid(null, null, UserAnswer::Cancel);
			$this->objSimPnl->DoMakeBid(null, null, UserAnswer::Cancel);
				
			switch ($objAd->Type) {
				case AdType::SIM:
					if ($this->objAdPnl->Visible)
						$this->objAdPnl->CloseAd();
					$this->objSimPnl->Ad = $objAd;
					$this->objSimPnl->SelectAd();
					break;
					
				case AdType::STD:
					if ($this->objSimPnl->Visible)
						$this->objSimPnl->CloseAd();
					$this->objAdPnl->Ad = $objAd;
					$this->objAdPnl->SelectAd();
					break;
			}
		}
		
		/**
		 * Apply for network
		 *
		 */
		protected function ApplyForNetwork() {
			$objNetwork = $this->lbNetworks->SelectedValue;
			
			$objNU = new NetworkUser();
			$objNU->Login = Security::Current();
			$objNU->Network = $objNetwork;
			$objNU->Status = BidStatus::Unanswered;
			
			$objNU->Save();
			$this->btnApplyForNetwork->Enabled = false;
				
			$this->lblNetworkInfo->Text = _tr("Your application is received");
			$this->lblNetworkInfo->Visible = true;
		}
		
		/**
		 * Check if we can apply for selected network
		 */
		protected function UpdateNetwork() {
			if ($this->lbNetworks->SelectedIndex == -1)
				$this->lbNetworks->SelectedIndex = 0;
			$objNetwork = $this->lbNetworks->SelectedValue;
			
			if (!Security::CheckAccess(Actions::ApplyForNetwork, $objNetwork)) {
				$this->btnApplyForNetwork->Visible = false;
			}
			
			if (!$objNetwork->IsMemberOrPending(Security::Current())) {
				$this->btnApplyForNetwork->Enabled = true;
			} else {
				$this->btnApplyForNetwork->Enabled = false;
				$this->lblNetworkInfo->Text = _tr("You're already a member of this network, or waiting to become one");
				$this->lblNetworkInfo->Visible = true;
			}
			$this->pnlNetworkDescription->Text = $objNetwork->Description;
		}
	}
?>