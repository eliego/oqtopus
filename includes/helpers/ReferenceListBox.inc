<?php
	/**
	 * ListBox alternative, which uses references to keep track of items and is capable of having a parent
	 * 
	 * Needs some cleanup, since it's partly pretty ugly. Works like a charm though.
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class ReferenceListBox extends QControl {
		protected $strItems;
		protected $mixSelected;
		protected $rlbParent;
		protected $strNullName;
		public $strParentName; // Seriously, it's 3 hours left of possible sleep, there's nothing in this world that could make me create getters and setters for this
		
		public function __construct(&$strItems, $objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->strItems =& $strItems;
		}
		
		public function ParsePostData() {
			if (isset($_POST[$this->strControlId]))
				$this->mixSelected = $_POST[$this->strControlId];
		}
		
		protected function GetControlHtml() {
			$strStyle = $this->GetStyleAttributes();
			if ($strStyle)
				$strStyle = sprintf('style="%s"', $strStyle);

			$strToReturn = sprintf('<select name="%s" id="%s" %s%s>', 
						$this->strControlId,
						$this->strControlId,
						$this->GetAttributes(),
						$strStyle);
						
						
			if ($this->rlbParent && !$this->rlbParent->Selected)
				return $strToReturn . '</select>'; // kolla helt enkelt om några options mer än spelar ingen roll skrivits ut, isåf parentname
						
			if ($this->strNullName) {
				$strToReturn .= '<option value="">'.$this->strNullName.'</option>';
			}
			
			// Get correct array
			$rlbParent = $this->rlbParent;
			$intPath = array();

			while ($rlbParent) {
				if (!$rlbParent->Selected)
					break;
					
				$intPath[] = $rlbParent->Selected;
				$rlbParent = $rlbParent->Parent;
			}
			
			$intPath = array_reverse($intPath);
			$strItems = $this->strItems;
			for ($i = 0; $i < sizeof($intPath); $i++)
				$strItems = $strItems[$intPath[$i]];
						
			if (is_array($strItems)) {
				// If we haven't selected anything, first item is selected
				if ((!$this->mixSelected) && (!$this->strNullName))
					$this->mixSelected = key($strItems);				
					
				foreach ($strItems as $value => $name)
					if (!is_array($name))
						$strToReturn .= sprintf('<option value="%s" %s>%s</option>',
							$value,
							($this->mixSelected == $value) ? 'selected="selected"' : "",
							htmlentities($name, ENT_COMPAT, QApplication::$EncodingType)
						);
			}
			$strToReturn .= "</select>";
			
			return $strToReturn;
		}
		
		public function Update() {
			$this->mixSelected = null;
			$this->blnModified = true;
			foreach ($this->GetAllActions('QChangeEvent') as $objAction)
				$objAction->trigger();
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'Selected':
					return $this->mixSelected;
					
				case 'Parent':
					return $this->rlbParent;
					
				case 'NullName':
					return $this->strNullName;
					
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
				case 'Selected':
					$this->mixSelected = $mixValue;
					break;
					
				case 'Parent':
					$this->rlbParent = $mixValue;
					$this->rlbParent->AddAction(new QChangeEvent(), new QAjaxControlAction($this, 'Update'));
					break;
					
				case 'NullName':
					$this->strNullName = $mixValue;
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
		
		public function Validate() {
			return true;
		}
	}
?>