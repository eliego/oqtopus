<?php
	/**
	 * Should work pretty much as QListBox with SelectionMode set to Multiple, but instead of a single input element,
	 * two boxes with items are displayed, and buttons for moving items from one box to another. Just like BitmaskComposite.
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class MultipleListBox extends QListControl {
		protected $lbSelected;
		protected $lbNotSelected;
		protected $btnSelect;
		protected $btnUnSelect;
		
		/**
		 * Create new MultipleListBox
		 *
		 * @param object $objParent
		 * @param string $strControlId
		 */
		public function __construct($objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->lbSelected = new QListBox($this);
			$this->lbSelected->SelectionMode = QSelectionMode::Multiple;
			$this->lbSelected->CssClass = "MultipleBox";
			
			$this->lbNotSelected = new QListBox($this);
			$this->lbNotSelected->SelectionMode = QSelectionMode::Multiple;
			$this->lbNotSelected->CssClass = "MultipleBox";
						
			$this->btnSelect = new QButton($this);
			$this->btnSelect->Text = sprintf('%s ', _tr('Add'));
			$this->btnSelect->AddAction(new QClickEvent(), $objMoveAction = new QAjaxControlAction($this, 'SwitchSelect'));
			$this->btnSelect->ActionParameter = SelectActions::Select;
			$this->btnSelect->CausesValidation = false;
			$this->btnSelect->CssClass = "MultipleButton";
			
			$this->btnUnSelect = new QButton($this);
			$this->btnUnSelect->Text = sprintf(' %s', _tr('Put back'));
			$this->btnUnSelect->AddAction(new QClickEvent(), $objMoveAction);
			$this->btnUnSelect->ActionParameter = SelectActions::UnSelect;
			$this->btnUnSelect->CausesValidation = false;
			$this->btnUnSelect->CssClass = "MultipleButton";
		}		
		
		public function GetControlHtml() {
			$this->PreRender();
			$this->lbNotSelected->Enabled = $this->blnEnabled;
			$this->lbSelected->Enabled = $this->blnEnabled;
			$this->btnSelect->Enabled = $this->blnEnabled;
			$this->btnUnSelect->Enabled = $this->blnEnabled;
			
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
		
		/**
		 * Fill private listboxes with the items that belong there
		 *
		 */
		protected function PreRender() {
			$this->lbSelected->RemoveAllItems();
			$this->lbNotSelected->RemoveAllItems();
			
			if ($this->objItemsArray)
				foreach ($this->objItemsArray as $objItem)
					if ($objItem->Selected)
						$this->lbSelected->AddItem(clone $objItem);
					else
						$this->lbNotSelected->AddItem(clone $objItem);
						
			$this->btnSelect->Enabled = (bool)$this->lbNotSelected->ItemCount;
			$this->btnUnSelect->Enabled = (bool)$this->lbSelected->ItemCount;
		}
		
		/**
		 * Select or unselect an item
		 *
		 * @param string $strFormId
		 * @param string $strControlId
		 * @param string $strParameter
		 */
		public function SwitchSelect($strFormId, $strControlId, $strParameter) {
			$objSource = null;
			
			switch ($strParameter) {
				case SelectActions::Select:
					$objSource = $this->lbNotSelected;
					break;
					
				case SelectActions::UnSelect:
					$objSource = $this->lbSelected;
					break; 
			}
			
			if (!($objFakeItem = $objSource->SelectedItem))
				return;
				
			if (!($objRealItem = $this->GetItemByValue($objFakeItem->Value)))
				throw new Exception('No such real object!');
				
			$objRealItem->Selected = !$objRealItem->Selected;
			
			$this->blnModified = true;
		}
		
		public function ParsePostData() {}
		public function Validate() { return true; }
	}
?>