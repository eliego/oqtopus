<?php
	class QTreeNav extends QControl {
		protected $strTagName = 'div';
		protected $strJavaScripts = 'treenav.js';
//		protected $strDisplayStyle = QDisplayStyle::Inline;

		protected $objSelectedTreeNavItem = null;
		protected $strSelectedCssSyle = 'selectedStyle';
		protected $objDropZoneGrouping;

		public function __construct($objParentObject, $strControlId = null) {
			parent::__construct($objParentObject, $strControlId);
			$this->objDropZoneGrouping = new QDropZoneGrouping($this->objForm, $this->strControlId . 'DZG');
		}

		protected function GetRenderedChildTreeNavControls() {
			$objToReturn = array();
			foreach ($this->Form->GetAllControls() as $objControl)
				if (($objControl instanceof QTreeNavItem) &&
					($objControl->ParentTreeNav->ControlId == $this->strControlId) &&
					($objControl->RenderMethod))
					array_push($objToReturn, $objControl);
			return $objToReturn;
		}

		public function ParsePostData() {}
		public function Validate() {return true;}

		public function GetControlHtml() {
			$strAttributes = $this->GetAttributes();
			$strStyles = $this->GetStyleAttributes();
			
			if ($strStyles)
				$strStyles = sprintf(' style="%s"', $strStyles);
			$strToReturn = sprintf('<%s id="%s" %s%s>%s</%s>',
				$this->strTagName,
				$this->strControlId,
				$strAttributes,
				$strStyles,
				$this->RenderChildren(false),
				$this->strTagName);

			$objChildren = $this->GetRenderedChildTreeNavControls();

			return $strToReturn;
		}
		

		/////////////////////////
		// Public Properties: GET
		/////////////////////////
		public function __get($strName) {
			switch ($strName) {
				case "SelectedCssStyle": return $this->strSelectedCssSyle;
				case "SelectedItem":
					return $this->objSelectedTreeNavItem;
/*					$objChildren = $this->GetChildControls();
					foreach ($objChildren as $objChild)
						if ($objChild instanceof QTreeNavItem)
							if ($objChild->Selected)
								return $objChild;
					return null;*/
				case "SelectedValue":
					if ($this->objSelectedTreeNavItem)
						return $this->objSelectedTreeNavItem->Value;
					else
						return null;
/*					$objChildren = $this->GetChildControls();
					foreach ($objChildren as $objChild)
						if ($objChild instanceof QTreeNavItem)
							if ($objChild->Selected)
								return $objChild->Value;
					return null;*/
					
				case "DropZoneGrouping":
					return $this->objDropZoneGrouping;

				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		/////////////////////////
		// Public Properties: SET
		/////////////////////////
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case "SelectedCssStyle":
					try {
						$this->strSelectedCssSyle = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case "SelectedItem":
					try {
						$objItem = QType::Cast($mixValue, "QTreeNavItem");
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

					if ($this->objSelectedTreeNavItem) {
						if ($this->objSelectedTreeNavItem->ControlId == $objItem->ControlId)
							return $objItem;
						$this->objSelectedTreeNavItem->SetSelectedFlag(false);
//						$this->objSelectedTreeNavItem->Selected = false;
					}

					$this->objSelectedTreeNavItem = $objItem;
//					$this->objSelectedTreeNavItem->Selected = true;
					$this->objSelectedTreeNavItem->SetSelectedFlag(true);

					return $objItem;

				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
					break;
			}
		}
	}
?>