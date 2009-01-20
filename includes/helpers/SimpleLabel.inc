<?php
	class SimpleLabel {
		protected $strText;
		protected function GetControlHtml() {
			return $this->strText;
		}
		
		public function Render($blnOutput = true) {
			if ($blnOutput)
				echo($this->GetControlHtml());
			else
				return $this->GetControlHtml();
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Text':
					$this->strText = $mixValue;
					break;
					
				default:
					$objReflection = new ReflectionClass($this);
					throw new QUndefinedPropertyException("SET", $objReflection->getName(), $strName);
					break;
			}
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'Text':
					return $this->strText;
					
				default:
					$objReflection = new ReflectionClass($this);
					throw new QUndefinedPropertyException('GET', $objReflection->getName(), $strName);
					break;
			}
		}
	}
?>