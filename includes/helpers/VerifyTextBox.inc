<?php
	/**
	 * Subclass of QTextBox to verify passwords and such
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */

	class VerifyTextBox extends QTextBox {
		protected $objVerify;
		public function __construct($objVerify, $objParent, $strIdentifier = null) {
			if (!($objVerify instanceof QTextBox))
				throw new WrongParametersException(_tr("The object to verify against must be a QTextBox"));
				
			parent::__construct($objParent, $strIdentifier);
			$this->objVerify = $objVerify;
		}
		//////////
		// Methods
		//////////
		public function Validate() {
			if (parent::Validate()) {
				if ( $this->strText != $this->objVerify->Text ) {
					$this->strValidationError = _tr("Content doesn't match");
					$this->blnModified = true;
					return false;
				}
			} else
				return false;

			$this->strValidationError = "";
			return true;
		}
	}
	
?>