<?php
	abstract class QAction extends QBaseClass {
		abstract protected function RenderScript(QControl $objControl);

		protected $objEvent;

public static function RenderActions(QControl $objControl, $strEventName, $objActions) {
            $strToReturn = '';
            $blnAjaxRendered = false;
            $blnPostBackRendered = false;
            

            if ($objActions) foreach ($objActions as $objAction) {
                if ($objAction->objEvent->JavaScriptEvent != $strEventName)
                    throw new Exception('Invalid Action Event in this entry in the ActionArray');

                $blnDoRender = true;

                if ($objAction instanceof QAjaxAction)
                {
                    if    (!$blnAjaxRendered )
                    {
                        $blnAjaxRendered=true;
                    }
                    else
                    {
                        $blnDoRender=false;    
                    }
                }
                else if ($objAction instanceof QServerAction)
                {
                    if    (!$blnPostBackRendered )
                    {
                        $blnPostBackRendered=true;
                    }
                    else
                    {
                        $blnDoRender=false;    
                    }
                }
                
                if ($blnAjaxRendered && $blnPostBackRendered)
                {
                    throw new QCallerException("trying to have ajaxAction and postBack on the same event");     
                }
                
                if ($blnDoRender)
                {
                
                    if ($objAction->objEvent->Delay > 0) {
                        $strCode = sprintf(" qcodo.setTimeout('%s', '%s', %s);",
                            $objControl->ControlId,
                            addslashes($objAction->RenderScript($objControl)),
                            $objAction->objEvent->Delay);
                    } else {
                        $strCode = ' ' . $objAction->RenderScript($objControl);
                    }
    
                    // Add Condition (if applicable)
                    if (strlen($objAction->objEvent->Condition))
                        $strCode = sprintf(' if (%s) {%s}', $objAction->objEvent->Condition, trim($strCode));
    
                    // Append it to the Return Value
                    $strToReturn .= $strCode;
                }
            }

            if ($objControl->ActionsMustTerminate)
                $strToReturn .= ' return false;';

            if (count($strToReturn))
                return sprintf('%s="%s" ', $strEventName, substr($strToReturn, 1));
            else
                return null;
        }

		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Event':
					return ($this->objEvent = QType::Cast($mixValue, 'QEvent'));

				default:
					try {
						return parent::__set($strName, $mixValue);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'Event': return $this->objEvent;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}
	}

	class QServerAction extends QAction {
		protected $strMethodName;

		public function __construct($strMethodName = null) {
			$this->strMethodName = $strMethodName;
		}

		public function __get($strName) {
			switch ($strName) {
				case 'MethodName':
					return $this->strMethodName;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		protected function RenderScript(QControl $objControl) {
			return sprintf("qcodo.postBack('%s', '%s', '%s', '%s');",
				$objControl->Form->FormId, $objControl->ControlId, get_class($this->objEvent), addslashes($objControl->ActionParameter));
		}
	}

	class QAjaxAction extends QAction {
		protected $strMethodName;
		protected $objWaitIconControl;

		public function __construct($strMethodName = null, $objWaitIconControl = 'default') {
			$this->strMethodName = $strMethodName;
			$this->objWaitIconControl = $objWaitIconControl;
		}

		public function __get($strName) {
			switch ($strName) {
				case 'MethodName':
					return $this->strMethodName;
				case 'WaitIconControl':
					return $this->objWaitIconControl;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		protected function RenderScript(QControl $objControl) {
			$strWaitIconControlId = null;
			if ($this->objWaitIconControl == 'default') {
				if ($objControl->Form->DefaultWaitIcon)
					$strWaitIconControlId = $objControl->Form->DefaultWaitIcon->ControlId;
			} else if ($this->objWaitIconControl) {
				$strWaitIconControlId = $objWaitIconControl->ControlId;
			}

			return sprintf("qcodo.postAjax('%s', '%s', '%s', '%s', '%s');",
				$objControl->Form->FormId, $objControl->ControlId, get_class($this->objEvent), addslashes($objControl->ActionParameter), $strWaitIconControlId);
		}
		
		public function Trigger($objForm) {
			call_user_func(array($objForm, $this->strMethodName));
		}
	}

	class QServerControlAction extends QServerAction {
		public function __construct(QControl $objControl, $strMethodName) {
			parent::__construct($objControl->ControlId . ':' . $strMethodName);
		}
	}

	class QAjaxControlAction extends QAjaxAction {
		protected $objControl;
		public function __construct(QControl $objControl, $strMethodName, $objWaitIconControl = 'default') {
			parent::__construct($objControl->ControlId . ':' . $strMethodName, $objWaitIconControl);
			$this->objControl = $objControl;
		}
		
		public function Trigger() {
			$strM = substr($this->strMethodName, strpos($this->strMethodName, ':') + 1);
			$this->objControl->$strM();
		}
	}

	class QJavaScriptAction extends QAction {
		protected $strJavaScript;

		public function __construct($strJavaScript) {
			$this->strJavaScript = trim($strJavaScript);
			if (QString::LastCharacter($this->strJavaScript) == ';')
				$this->strJavaScript = substr($this->strJavaScript, 0, strlen($this->strJavaScript) - 1);
		}

		public function __get($strName) {
			switch ($strName) {
				case 'JavaScript':
					return $this->strJavaScript;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		protected function RenderScript(QControl $objControl) {
			return sprintf('%s;', $this->strJavaScript);
		}
	}

	class QConfirmAction extends QAction {
		protected $strMessage;

		public function __construct($strMessage) {
			$this->strMessage = $strMessage;
		}

		public function __get($strName) {
			switch ($strName) {
				case 'Message':
					return $this->strMessage;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		protected function RenderScript(QControl $objControl) {
			return sprintf("if (!confirm('%s')) return false;", addslashes($this->strMessage));
		}
	}

	class QAlertAction extends QAction {
		protected $strMessage;

		public function __construct($strMessage) {
			$this->strMessage = $strMessage;
		}

		public function __get($strName) {
			switch ($strName) {
				case 'Message':
					return $this->strMessage;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		protected function RenderScript(QControl $objControl) {
			return sprintf("alert('%s');", addslashes($this->strMessage));
		}
	}

	class QResetTimerAction extends QAction {
		protected function RenderScript(QControl $objControl) {
			return sprintf("qcodo.clearTimeout('%s');", $objControl->ControlId);
		}
	}
	
	class QTerminateAction extends QAction {
		protected function RenderScript(QControl $objControl) {
			return sprintf('return false;', $objControl->ControlId);
//			return 'return qc.terminatesEvent(event);';
		}
	}

	class QToggleDisplayAction extends QAction {
		protected $strControlId = null;
		protected $blnDisplay = null;

		public function __construct($objControl, $blnDisplay = null) {
			if (!($objControl instanceof QControl))
				throw new QCallerException('First parameter of constructor is expecting an object of type QControl');

			$this->strControlId = $objControl->ControlId;

			if (!is_null($blnDisplay))
				$this->blnDisplay = QType::Cast($blnDisplay, QType::Boolean);
		}

		protected function RenderScript(QControl $objControl) {
			if ($this->blnDisplay === true)
				$strShowOrHide = 'show';
			else if ($this->blnDisplay === false)
				$strShowOrHide = 'hide';
			else
				$strShowOrHide = '';

			return sprintf("qcodo.getWrapper('%s').toggleDisplay('%s');",
				$this->strControlId, $strShowOrHide);
		}
	}

	class QToggleEnableAction extends QAction {
		protected $strControlId = null;
		protected $blnEnabled = null;

		public function __construct($objControl, $blnEnabled = null) {
			if (!($objControl instanceof QControl))
				throw new QCallerException('First parameter of constructor is expecting an object of type QControl');

			$this->strControlId = $objControl->ControlId;

			if (!is_null($blnEnabled))
				$this->blnEnabled = QType::Cast($blnEnabled, QType::Boolean);
		}

		protected function RenderScript(QControl $objControl) {
			if ($this->blnEnabled === true)
				$strEnableOrDisable = 'enable';
			else if ($this->blnEnabled === false)
				$strEnableOrDisable = 'disable';
			else
				$strEnableOrDisable = '';

			return sprintf("qcodo.getWrapper('%s').toggleEnabled('%s');", $this->strControlId, $strEnableOrDisable);
		}
	}
	
	class QRegisterClickPositionAction extends QAction {
		protected $strControlId = null;

		protected function RenderScript(QControl $objControl) {
			return sprintf("qcodo.getWrapper('%s').registerClickPosition(event);", $objControl->ControlId);
		}
	}
?>