<?php
	/**
	 * Subclass of QTextBox to validate organization numbers
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */

	class OrganizationNumberTextBox extends QTextBox {
		//////////
		// Methods
		//////////
		public function Validate() {
			if (parent::Validate()) {
				if ($this->strText != "") {
					if ( !Localization::ValidateOrganizationNumber($this->strText)) {
						$this->strValidationError = _tr("Invalid D&B D-U-N-S number");
						return false;
					}
				}
			} else
				return false;

			$this->strValidationError = "";
			return true;
		}	
	}
	
?>