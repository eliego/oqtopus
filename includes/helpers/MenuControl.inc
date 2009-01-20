<?php
	class MenuControl extends QControl {
		protected $objMenu;
		
		public function __construct($objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
		}
		
		protected function GetControlHtml() {
			if (!$this->objMenu)
				return '';
				
			$strStyle = $this->GetStyleAttributes();
            if ($strStyle)
                $strStyle = sprintf('style="%s"', $strStyle);
                
            $strAttributes = $this->GetAttributes(true, false);
            
            $objSelected = $this->objMenu;
            $objSelected->Render(false);
            $objChildren = $objSelected->GetChildControls();
            $i = 1;
            $strReturn = '';
            
            do {
            	$strTemp = '';
            	foreach ($objChildren as $objControl)
            		$strTemp .= $objControl->Render(false);
            	
            	$strReturn .= sprintf('<ul class="menu%d">%s</ul>', $i, $strTemp);
            
            $i++;
            } while (($objSelected = $objSelected->Selected) && ($objChildren = $objSelected->GetChildControls()));
            
            $strReturn = sprintf('<div id="%s" %s%s>%s</div>', $this->strControlId, $strStyle, $strAttributes, $strReturn);
            return $strReturn;
		}
		
		public function ParsePostData() {
			if ($this->objMenu && $this->objMenu->Modified)
				$this->blnModified = true;
		}
		
		public function Validate() { return true; }
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Menu': $this->objMenu = $mixValue; break;
				
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
				case 'Menu':
					return $this->objMenu;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
	}
?>