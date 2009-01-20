<?php
	/**
	 * Renders a menu, with submenus.
	 *
	 * @author Kung den Knege
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class Menu extends QLinkButton  { // Seriosly, my understanding of how this works could best be described as.. vague. How the hell were I thinking!?
		protected $strForm;
		protected $strArg1;
		protected $strArg2;
		protected $strCssClass = '';
		public function __construct($strText, $objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->Text = $strText;
		}
		
		public function Validate() { return true; }
		public function ParsePostData() {}
		protected function GetControlHtml() {
			$strStyle = $this->GetStyleAttributes();
            if ($strStyle)
                $strStyle = sprintf('style="%s"', $strStyle);
                
            $strAttributes = $this->GetAttributes(true, false);
            
            $str = '<li id="%s" %s%s>%s</li>';
            $str = sprintf($str, $this->strControlId, $strStyle, $strAttributes, parent::GetControlHtml());
            
            return $str;
		}
		
		public function AddChildControl(QControl $objControl) {
			switch (get_class($objControl)) {
				case 'Menu':
					$objControl->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'Select'));
					
				case 'MenuItem':
					parent::AddChildControl($objControl);
					break;
					
				default:
					throw new QCallerException("Only Menus and MenuItems can be children of Menus!");
			}
		}
		
		public function Select($strFormId, $strControlId, $strParameter) {
			foreach ($this->GetChildControls() as $objChild)
				if ($objChild->ControlId == $strControlId) {
					$_SESSION[$this->strControlId.'_selected'] = $strControlId;
					$this->objParentControl->MarkAsModified();
					if ($objChild->LinkForm && ($objChild->LinkForm != QApplication::$FormName || ($objChild->Arg1 && !isset($_GET['arg1']) || $objChild->Arg1 != $_GET['arg1'])) || ($objChild->Arg2 && !isset($_GET['arg2']) || $objChild->Arg2 != $_GET['arg2']))
						QApplication::Redirect(Navigation::CreateUrl($objChild->LinkForm, $objChild->Arg1, $objChild->Arg2));
				} else 
					if ($objChild instanceof Menu)
						$objChild->Select($this->objForm->FormId, null, null);
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'Selected': return isset($_SESSION[$this->strControlId.'_selected']) && $_SESSION[$this->strControlId.'_selected'] ? $this->objChildControlArray[$_SESSION[$this->strControlId.'_selected']] : null;
				
				case 'LinkForm': return $this->strForm;
				case 'Arg1': return $this->strArg1;
				case 'Arg2': return $this->strArg2;
				
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Selected': $_SESSION[$this->strControlId.'_selected'] = ($mixValue ? $mixValue->ControlId : ''); break;
				
				case 'LinkForm': $this->strForm = $mixValue; break;
				case 'Arg1': $this->strArg1 = $mixValue; break;
				case 'Arg2': $this->strArg2 = $mixValue; break;
				
				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
	}
?>