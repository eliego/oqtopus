<?php
	class MenuItem extends QControl {
		protected $strUrl;
		protected $strText;
		
		public function __construct($strText, $strUrl, QControl $objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->strText = $strText;
			$this->strUrl = $strUrl;
			$this->blnCausesValidation = false;
		}
		
		public function ParsePostData() {}
		public function Validate() { return true; }
		protected function GetControlHtml() {
			$strStyle = $this->GetStyleAttributes();
            if ($strStyle)
                $strStyle = sprintf('style="%s"', $strStyle);
                
            $strAttributes = $this->GetAttributes(true, false);
            
            $str = sprintf('<li id="%s" %s%s><a href="%s">%s</a></li>', $this->strControlId, $strStyle, $strAttributes, $this->strUrl, $this->Text);
            
            return $str;
		}
		
			public function __get($strName) {
			switch ($strName) {
				case 'Url': return $this->strUrl;
				case 'Text': return $this->strText;
				
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
				case 'Url': $this->strUrl = $mixValue; break;
				case 'Text': $this->strText = $mixValue; break;
				
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