<?php
	/**
	 * Subclass of QTextBox that only accepts a single word
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */

	class SingleWordTextBox extends QTextBox {
		//////////
		// Methods
		//////////
		public function Validate() {
			$this->strText = trim($this->strText);
			
			if (parent::Validate()) {
				if ($this->strText != "") {
					// RegExp taken from php.net
					if ( strpos($this->strText, ' ') ) {
						$this->strValidationError = _tr("Please enter a single word only");
						$this->blnModified = true;						
						return false;
					}
				}
			} else
				return false;

			$this->strValidationError = "";
			$this->blnModified = true;
			return true;
		}
	}
?>