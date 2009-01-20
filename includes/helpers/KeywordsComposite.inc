<?php
	/**
	 * Composite control, consisting of big listbox, textbox and two buttons
	 * Words can then be added to and removed from the big listbox
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class KeywordsComposite extends QControl {
		protected $lbWords;
		protected $txtWord;
		protected $btnAdd;
		protected $btnDel;
		protected $lblLimit;
		
		protected $intLimit = 20;
		
		public function __construct($objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->lbWords = new QListBox($this);
			$this->lbWords->SelectionMode = QSelectionMode::Multiple;
			$this->lbWords->CssClass = "MultipleBox";
			
			$this->txtWord = new SingleWordTextBox($this);
			$this->txtWord->Required = false;
			$this->txtWord->AddAction(new QEnterKeyEvent(), new QAjaxControlAction($this, 'ActionAdd'));
			$this->txtWord->AddAction(new QEnterKeyEvent(), new QTerminateAction());			
			$this->txtWord->CssClass = "txtWord";
			
			$this->btnAdd = new QButton($this);
			$this->btnAdd->Text = _tr('Add');
			$this->btnAdd->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'ActionAdd'));
			$this->btnAdd->CausesValidation = false;
			$this->btnAdd->CssClass = "KeywordButton";
			
			$this->btnDel = new QButton($this);
			$this->btnDel->Text = _tr('Remove tagg');
			$this->btnDel->CausesValidation = false;
			$this->btnDel->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'Del'));
			$this->btnDel->CssClass = "btnDel";
			
			$this->lblLimit = new QLabel($this);
			
			// Initialize limit
			$this->SetUpLimit();
		}
		
		/**
		 * Add a new keyword
		 *
		 * @param string $strWord
		 */
		public function Add($strWord) {
			$this->lbWords->AddItem($strWord, $strWord);	
			$this->SetUpLimit();
		}
		
		/**
		 * Add a new word, to be called by button action
		 *
		 */
		public function ActionAdd($strFormId, $strControlId, $strParameter) {
			if ($strControlId != $this->btnAdd->ControlId && $strControlId != $this->txtWord->ControlId)
				throw new QCallerException("KeywordsComposite::ActionAdd should not be called programatically!");
				
			// We must validate manually
			if ($this->txtWord->Text && $this->txtWord->Validate() && $this->lbWords->ItemCount < $this->intLimit) {
				$this->lbWords->AddItem($this->txtWord->Text, $this->txtWord->Text);
				$this->txtWord->Text = '';
				$this->SetUpLimit();
			}			
		}
		
		/**
		 * Remove a keyword
		 *
		 */
		public function Del() {
			if ($this->lbWords->SelectedItem)
				$this->lbWords->RemoveItem($this->lbWords->SelectedIndex);
				
			$this->SetUpLimit();
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'Keywords':
					$strWords = array();
					for ($i = 0; $i < $this->lbWords->ItemCount; $i++)
						$strWords[] = $this->lbWords->GetItem($i)->Value;
						
					return $strWords;
					
				case 'Limit':
					return $this->intLimit;
					
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
				case 'Keywords':
					$this->DelAll();
					foreach (QType::Cast($mixValue, QType::ArrayType) as $strKeyword)
						$this->Add($strKeyword);
					break;
					
				case 'Limit':
					$this->intLimit = $mixValue;
					
				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		protected function GetControlHtml() {
			$strStyle = $this->GetStyleAttributes();
            if ($strStyle)
                $strStyle = sprintf('style="%s"', $strStyle);
                
            $strAttributes = $this->GetAttributes(true, false);
            
            $str = '<div id="%s" %s%s>%s%s<br /><br />%s%s<br />%s</div>';
            
            $str = sprintf($str, $this->strControlId, $strStyle, $strAttributes, $this->txtWord->RenderWithError(false),
							$this->btnAdd->Render(false),
							$this->lbWords->Render(false),
							$this->btnDel->Render(false), 
            			    $this->lblLimit->Render(false));
            			   
            return $str;			
		}
		
		public function Validate() {
			if ($this->blnRequired && !$this->lbWords->ItemCount) {
				if ($this->strName)
					$this->strValidationError = sprintf(_tr('%s is required'), $this->strName);
				else
					$this->strValidationError = _tr('Required');
					
				return false;
			}
			
			return true;
		}
		
		public function ParsePostData() { }
		
		public function SetUpLimit() {
			$this->lblLimit->Text = sprintf(_tr('%d keywords out of %d selected'), $this->lbWords->ItemCount, $this->intLimit);
			$this->btnAdd->Enabled = ($this->lbWords->ItemCount < $this->intLimit);
			$this->lblLimit->MarkAsModified();
		}		
		
		/**
		 * Remove all words
		 *
		 */
		public function DelAll() {
			$this->lbWords->RemoveAllItems();
			$this->SetUpLimit();
		}
	}
?>