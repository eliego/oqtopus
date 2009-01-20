<?php

	/**
	 * Does a search and display the results as a moveable box
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class SearchComposite extends QPanel  {
		public $btnClose;
		public $btnState;
		public $dtgData;
		public $txtName;
		public $lblName;
		protected $objSearch;
		protected $intState = ControlState::Maximized;
		protected $intMinimizedHeight = 30;
		
		/**
		 * Constructor, instantiates and displays a SearchResult
		 * (and does the actual search)
		 *
		 * @param Search $objSearch The search to ehrm.. search for. :P
		 * @param QControl $objParent Parent control
		 * @param string $strId Id
		 */
		public function __construct($objSearch, $objParent, $strId = null) {
			try {
				parent::__construct($objParent, $strId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			if (!($objSearch instanceof Search))
				throw new WrongParametersException(_tr("First argument must be a Search object"));
			
			$this->btnClose = new QButton($this);
			$this->btnClose->CausesValidation = false; 
			$this->btnClose->Text = "Ta bort"; 
			$this->btnClose->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'Close'));
			$this->btnClose->CssClass = "SearchComposite_btnClose";
			
			$this->btnState = new QButton($this);
			$this->btnState->CausesValidation = false;
			$this->btnState->Text = $this->intState == ControlState::Maximized ? "Minimera" : "Maximera"; // THIS TOO
			$this->btnState->AddAction(new QClickEvent(), new QAjaxControlAction($this, "changeState"));
			$this->btnState->CssClass = "SearchComposite_btnState";
			
			$this->txtName = new QTextBox($this);
			$this->txtName->CssClass = 'SearchComposite_txtName';
			$this->txtName->Required = false;
			$this->txtName->Visible = false;
			$this->txtName->AddAction(new QEnterKeyEvent(), new QAjaxControlAction($this, 'DoChangeName'));
			$this->txtName->AddAction(new QBlurEvent(), new QAjaxControlAction($this, 'DoChangeName'));
			$this->txtName->AddAction(new QEnterKeyEvent(), new QTerminateAction());
			
			$this->lblName = new QLabel($this);
			$this->lblName->CssClass = 'SearchComposite_lblName';
			$this->lblName->Text = $objSearch->Name;
			$this->lblName->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'ChangeName'));
					
			$this->dtgData = new SellersDataGrid($objSearch, $this);
			$this->dtgData->UseAjax = true;
			$this->dtgData->Persistent = true;
			$this->dtgData->CssClass = 'dtgData';
			
			$this->strTemplate = sprintf('%s%s.inc', __TEMPLATES__, __CLASS__);
			
			$this->objSearch = $objSearch;
		}
		
		public function ChangeName() {
			$this->txtName->Text = $this->objSearch->Name;
			$this->txtName->Visible = true;
			$this->lblName->Visible = false;
			$this->blnModified = true;
			
			// This refuses to work when implemented as actions on txtName
			QApplication::ExecuteJavaScript(sprintf('document.getElementById("%s").focus()', $this->txtName->ControlId));
			QApplication::ExecuteJavaScript(sprintf('document.getElementById("%s").select()', $this->txtName->ControlId));			
		}
		
		public function DoChangeName() {
			$this->lblName->Text = $this->objSearch->Name = $this->txtName->Text;
			if ($this->objSearch->Id)
				$this->objSearch->Save();

			$this->lblName->Visible = true;
			$this->txtName->Visible = false;
			$this->blnModified = true;
		}
		
		public function ParsePostData() {}
		
		public function Validate() { return true; }
		
		protected function GetControlHtml() {
			$strStyle = $this->GetStyleAttributes();

			if ($strStyle)
				$strStyle = sprintf('style="%s"', $strStyle);

			$strTemplateEvaluated = '';
			if ($this->strTemplate) {
				global $_CONTROL;
				$objCurrentControl = $_CONTROL;
				$_CONTROL = $this;
				$strTemplateEvaluated = $this->objForm->EvaluateTemplate($this->strTemplate);
				$_CONTROL = $objCurrentControl;
			}

			$strToReturn = sprintf('<%s id="%s" %s%s>%s%s%s</%s>',
				$this->strTagName,
				$this->strControlId,
				$this->GetAttributes(),
				$strStyle,
				nl2br($this->strText),
				$strTemplateEvaluated,
				($this->blnAutoRenderChildren) ? $this->RenderChildren(false) : '',
				$this->strTagName);
            
            return $strToReturn;
		}
		
		/**
		 * Close this control
		 *
		 * @return void;
		 */
		public function Close() {
			if ($this->objSearch->Id)
				$this->objSearch->Delete();
			
			$this->objParentControl->RemoveChildControl($this->strControlId, true);
		}
		
		/**
		 * Toogle state for this control
		 * 
		 * @return void
		 */
		public function changeState() {
			switch ($this->intState) {
				case ControlState::Maximized:
					$this->strHeight = sprintf("%dpx", $this->intMinimizedHeight);
					$this->intState = ControlState::Minimzed;
					$this->btnState->Text = "Maximera";
					break;
					
				case ControlState::Minimzed:
					$this->strHeight = null;
					$this->intState = ControlState::Maximized;
					$this->btnState->Text = "Minimera";
					break;
			}
			$this->blnModified = true;
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'ItemsPerPage':
					$this->dtgData->ItemsPerPage = $mixValue;
					break;
					
				case 'MinimizedHeight':
					$this->intMinimizedHeight = (int)$mixValue;
					break;
					
				case 'Template':
					$objReflection = new ReflectionClass($this);
					throw new QUndefinedPropertyException("SET", $objReflection->getName(), $strName);					
					
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
				case 'ItemsPerPage':
					return $this->dtgData->ItemsPerPage;
					
				case 'MinimizedHeight':
					return $this->intMinimizedHeight;
					
				case 'Template':
					$objReflection = new ReflectionClass($this);
					throw new QUndefinedPropertyException("GET", $objReflection->getName(), $strName);
					break;
					
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