<?php
	class MultiLineTextBox extends QTextBox {
		protected $intRowLimit;
		protected $strTextMode = QTextMode::MultiLine;
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'RowLimit':
					$this->intRowLimit = $mixValue;
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
				case 'RowLimit':
					return $this->intRowLimit;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		public function Validate() {
			if (!parent::Validate())
				return false;
				
			if ($this->intRowLimit && substr_count($this->strText, "\n") >= $this->intRowLimit) {
				$this->strValidationError = sprintf(_tr('Maxmimum %d rows'), $this->intRowLimit);
				$this->blnModified = true;
				return false;
			}
			
			return true;
		}
	}
?>