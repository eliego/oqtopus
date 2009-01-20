<?php
	// Utilized by the ListControl class which contains a private array of ListItems.
	// * "Name" is what gets displayed
	// * "Value" is any text that represents the value of the ListItem (e.g. maybe a DB Id)
	// * "Selected" is a boolean of whether or not this item is selected or not

	class QListItem extends QBaseClass {
		///////////////////////////
		// Private Member Variables
		///////////////////////////
		private $strName = null;
		private $strValue = null;
		private $blnSelected = false;


		/////////////////////////
		// Methods
		/////////////////////////
		public function __construct($strName, $strValue, $blnSelected = false) {
			$this->strName = $strName;
			$this->strValue = $strValue;
			$this->blnSelected = $blnSelected;
		}
		
		/**
		 * Cloned items should not inherit selected state
		 *
		 */
		public function __clone() {
			$this->blnSelected = false;
		}
		
		/////////////////////////
		// Public Properties: GET
		/////////////////////////
		public function __get($strName) {
			switch ($strName) {
				case "Name": return $this->strName;
				case "Value": return $this->strValue;
				case "Selected": return $this->blnSelected;

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
				case "Name":
					try {
						$this->strName = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "Value":
					try {
						$this->strValue = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}				
				case "Selected":
					try {
						$this->blnSelected = QType::Cast($mixValue, QType::Boolean);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}				

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