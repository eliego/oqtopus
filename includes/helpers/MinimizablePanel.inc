<?php
	/**
	 * Minimizable panel
	 * 
	 * A button to minimize or mazimize is automatically rendered.
	 * When minimized, the panels height gets set to MinimizedHeight, and all child controls gets Visible = false;
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class MinimizablePanel extends QPanel {
		protected $intMinimizedHeight = 25;
		protected $intState = ControlState::Maximized;
		protected $btnState;
		protected $blnChildStates;
		protected $strAlwaysShow;
		protected $strMinLabel = 'Min';
		protected $strMaxLabel = 'Max';
		
		public function __construct($objParent, $strId = null) {
			try {
				parent::__construct($objParent, $strId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->btnState = new QButton($this, $this->strControlId . 'btnState');
			$this->btnState->Text = $this->strMinLabel;
			$this->btnState->CausesValidation = false;
			$this->btnState->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'changeState'));
			$this->btnState->CssClass = 'btnState';
			
			$this->blnChildStates = array();
		}
		
		public function changeState() {
			switch ($this->intState) {
				case ControlState::Maximized:
					$this->strHeight = sprintf("%dpx", $this->intMinimizedHeight);
					$this->intState = ControlState::Minimzed;
					$this->btnState->Text = $this->strMaxLabel;
					foreach ($this->objChildControlArray as $key => $objChild)
						if ($objChild !== $this->btnState && !(isset($this->strAlwaysShow[$objChild->ControlId]) && $this->strAlwaysShow[$objChild->ControlId] == true)) {
							$this->blnChildStates{$key} = $objChild->Visible;
							$objChild->Visible = false;
						}
						
					// Terrible
					if (isset($this->objChildControlArray['btnOk']))
						$this->objChildControlArray['btnOk']->CssClass = 'btnSearch_Simple';	
						
					break;
					
				case ControlState::Minimzed:
					$this->strHeight = null;
					$this->intState = ControlState::Maximized;
					$this->btnState->Text = $this->strMinLabel;
					foreach ($this->objChildControlArray as $key => $objChild)
						if ($objChild !== $this->btnState && !(isset($this->strAlwaysShow[$objChild->ControlId]) && $this->strAlwaysShow[$objChild->ControlId] == true))
							$objChild->Visible = $this->blnChildStates[$key];
							
					// Terrible
					if (isset($this->objChildControlArray['btnOk']))
						$this->objChildControlArray['btnOk']->CssClass = 'btnSearch_Advanced';
						
					break;
			}
			$this->blnModified = true;
		}
		
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

			$strToReturn = sprintf('<%s id="%s" %s%s>%s%s%s%s</%s>',
				$this->strTagName,
				$this->strControlId,
				$this->GetAttributes(),
				$strStyle,
				$this->btnState->Render(false),
				nl2br($this->strText),
				$strTemplateEvaluated,
				($this->blnAutoRenderChildren) ? $this->RenderChildren(false) : '',
				$this->strTagName);

			return $strToReturn;
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'MinimizedHeight':
					return $this->intMinimizedHeight;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e ) {
						$e->IncrementOffset();
						throw $e;			
					}
			}
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'MinimizedHeight':
					$this->intMinimizedHeight = QType::Cast($mixValue, QType::Integer);
					break;
					
				case 'MinLabel':
					$this->strMinLabel = $mixValue;
					break;
					
				case 'MaxLabel':
					$this->strMaxLabel = $mixValue;
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
		
		/**
		 * Always show this control, no matter of state
		 *
		 * @param QControl $strControlId
		 */
		public function AlwaysShow(QControl $objControl) {
			$strControlId = $objControl->ControlId;
			if (!isset($this->objChildControlArray[$strControlId]))
				throw new QCallerException('I don\'t have any childcontrol with that name!');
				
			$this->strAlwaysShow[$strControlId] = true;
		}
	}
?>