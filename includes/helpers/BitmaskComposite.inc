<?php
	/**
	 * Composite control with two multiple-selection listboxes, and two buttons allowing the user to move objects between them
	 * One represents selected attributes, one represents not selected attributes
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class BitmaskComposite extends QControl {
		protected $strAttributes;
		protected $lbSelected;
		protected $lbNotSelected;
		protected $btnSelect;
		protected $btnUnSelect;
		
		/**
		 * Create new BitmaskComposite
		 *
		 * @param string[] $strAttributes Array of attributes to choose from, must be in format value => name, where value increases by a factor of 2 for each new attribute.
		 * @param object $objParent
		 * @param string $strControlId
		 */
		public function __construct($strAttributes, $objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->strAttributes = $strAttributes;
			
			$this->lbSelected = new QListBox($this);
			$this->lbSelected->SelectionMode = QSelectionMode::Multiple;
			$this->lbSelected->CssClass = "MultipleBox";
			
			$this->lbNotSelected = new QListBox($this);
			$this->lbNotSelected->SelectionMode = QSelectionMode::Multiple;
			$this->lbNotSelected->CssClass = "MultipleBox";
						
			$this->btnSelect = new QButton($this);
			$this->btnSelect->Text = sprintf('%s ', _tr('Add'));
			$this->btnSelect->AddAction(new QClickEvent(), $objMoveAction = new QAjaxControlAction($this, 'MoveAttribute'));
			$this->btnSelect->ActionParameter = SelectActions::Select;
			$this->btnSelect->CausesValidation = false;
			$this->btnSelect->CssClass = "MultipleButton";
			
			$this->btnUnSelect = new QButton($this);
			$this->btnUnSelect->Text = sprintf(' %s', _tr('Put back'));
			$this->btnUnSelect->AddAction(new QClickEvent(), $objMoveAction);
			$this->btnUnSelect->ActionParameter = SelectActions::UnSelect;
			$this->btnUnSelect->CausesValidation = false;
			$this->btnUnSelect->CssClass = "MultipleButton";
			
			// Phony select, to grey out boxes if appliciable
			$this->MoveAttribute(null, null, null);
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Bitmask':
					$this->lbNotSelected->RemoveAllItems();
					$this->lbSelected->RemoveAllItems();
					foreach ($this->strAttributes as $value => $name)
						if ($mixValue & $value)
							$this->lbSelected->AddItem($name, $value);
						else
							$this->lbNotSelected->AddItem($name, $value);
							
					$this->blnModified = true;
					
					// Phony select, to grey out boxes if appliciable
					$this->MoveAttribute(null, null, null);
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
		
		public function __get($strName) {
			switch ($strName) {
				case 'Bitmask':
					$intReturn = 0;
					for ($i = 0; $i < $this->lbSelected->ItemCount; $i++)
						$intReturn |= $this->lbSelected->GetItem($i)->Value;
						
					return $intReturn;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		/**
		 * Select or unselect listbox
		 *
		 * @param string $strFormId
		 * @param string $strControlId
		 * @param SelectActions $strParameter
		 */
		public function MoveAttribute($strFormId, $strControlId, $strParameter) {
			$objSource = null;
			$objTarget = null;
			
			switch ($strParameter) {
				case SelectActions::Select:
					$objSource = $this->lbNotSelected;
					$objTarget = $this->lbSelected;
					break;
					
				case SelectActions::UnSelect:
					$objSource = $this->lbSelected;
					$objTarget = $this->lbNotSelected;
					break;
			}
			
			if ($objSource && $objSource->SelectedItem) {
				$objItem = $objSource->GetItem($objSource->SelectedIndex);
				$objSource->RemoveItem($objSource->SelectedIndex);
				$objTarget->AddItem($objItem);
				
				$this->blnModified = true;
			}
			
			$this->btnSelect->Enabled = (bool)$this->lbNotSelected->ItemCount;
			$this->btnUnSelect->Enabled = (bool)$this->lbSelected->ItemCount;
			
		}
		
		public function GetControlHtml() {
			$strStyle = $this->GetStyleAttributes();
            if ($strStyle)
                $strStyle = sprintf('style="%s"', $strStyle);
                
            $strAttributes = $this->GetAttributes(true, false);
            
            $strPattern = '<div id="%s" %s%s><table><tr><td>%s</td><td>%s</td></tr><tr><td>%s</td><td>%s</td></tr></table></div>';
            
            $str = sprintf($strPattern, $this->strControlId, $strStyle, $strAttributes, 
            												   $this->lbNotSelected->Render(false), $this->lbSelected->Render(false),
            												   $this->btnSelect->Render(false), $this->btnUnSelect->Render(false));
            												   
            return $str;
		}
		
		public function ParsePostData() {}
		
		public function Validate() {
			if ($this->blnRequired && !$this->lbSelected->ItemCount) {
				if ($this->strName)
					$this->strValidationError = sprintf($this->strLabelForRequired, $this->strName);
				else
					$this->strValidationError = $this->strLabelForRequiredUnnamed;
					
				return false;
			}
			
			return true;
		}
		
		/**
		 * TODO: Does a static realy make any sense here?
		 * 
		 * Send in a bitmask and an array of things, get matching things as html list
		 *
		 * @param int $intBitMask
		 * @param string[] $strThings
		 * @return string
		 */
		public static function GetHtmlList($intBitMask, $strThings) {
			if (!$intBitMask) // Todo: use localization
				return 'Ospecificerat';
				
			$strReturn = '<ul class="BitmaskComposite_AttributeList">';
			foreach ($strThings as $value => $name)
				if ($intBitMask & $value)
					$strReturn .= sprintf('<li class="BitmaskComposite_Attribute">%s</li>', htmlentities($name, ENT_COMPAT, QApplication::$EncodingType));
					
			$strReturn .= '</ul>';
			return $strReturn;
		}
	}
?>