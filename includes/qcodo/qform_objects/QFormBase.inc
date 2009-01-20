<?php
	/* Qcodo Development Framework for PHP
	 * http://www.qcodo.com/
	 * 
	 * The Qcodo Development Framework is distributed by QuasIdea Development, LLC
	 * under the terms of The MIT License.  More information can be found at
	 * http://www.opensource.org/licenses/mit-license.php
	 * 
	 * Copyright (c) 2001 - 2006, QuasIdea Development, LLC
	 * 
	 * Permission is hereby granted, free of charge, to any person obtaining a copy of
	 * this software and associated documentation files (the "Software"), to deal in
	 * the Software without restriction, including without limitation the rights to
	 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	 * of the Software, and to permit persons to whom the Software is furnished to do
	 * so, subject to the following conditions:
	 * 
	 * The above copyright notice and this permission notice shall be included in all
	 * copies or substantial portions of the Software.
	 * 
	 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	 * SOFTWARE.
	 */

	abstract class QFormBase extends QBaseClass {
		///////////////////////////
		// Private Member Variables
		///////////////////////////
		protected $strFormId;
		protected $intFormStatus;
		private $objControlArray;
		protected $objGroupingArray;
		protected $blnRenderedBodyTag = false;
		protected $blnRenderedCheckableControlArray;
		protected $strCallType;
		protected $objDefaultWaitIcon = null;

		///////////////////////////
		// Form Status Constants
		///////////////////////////
		const FormStatusUnrendered = 1;
		const FormStatusRenderBegun = 2;
		const FormStatusRenderEnded = 3;

		///////////////////////////
		// Form Preferences
		///////////////////////////
		public static $EncryptionKey = null;
		public static $FormStateHandler = 'QFormStateHandler';

		/////////////////////////
		// Public Properties: GET
		/////////////////////////
		public function __get($strName) {
			switch ($strName) {
				case "FormId": return $this->strFormId;
				case "CallType": return $this->strCallType;
				case "DefaultWaitIcon": return $this->objDefaultWaitIcon;

				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		/////////////////////////
		// Helpers for ControlId Generation
		/////////////////////////
		public function GenerateControlId() {
//			$strToReturn = sprintf('control%s', $this->intNextControlId);
			$strToReturn = sprintf('ctl%s', $this->intNextControlId);
			$this->intNextControlId++;
			return $strToReturn;
		}
		protected $intNextControlId = 1;

		/////////////////////////
		// Event Handlers
		/////////////////////////
		protected function Form_Run() {}
		protected function Form_Load() {}
		protected function Form_Create() {}
		protected function Form_PreRender() {}
		protected function Form_Invalid() {}
		protected function Form_Exit() {}
		

		public final function VarExport($blnReturn = true) {
			if ($this->objControlArray) foreach ($this->objControlArray as $objControl)
				$objControl->VarExport(false);
			if ($blnReturn)
				return var_export($this, true);
		}

		public function IsCheckableControlRendered($strControlId) {
			return array_key_exists($strControlId, $this->blnRenderedCheckableControlArray);
		}

		public final static function Run($strFormId, $strAlternateHtmlFile = null) {
			// Ensure strFormId is a class
			$objClass = new $strFormId();

			// Ensure strFormId is a subclass of QForm
			if (!($objClass instanceof QForm))
				throw new QCallerException('Object is not a subclass of QForm (note, it can NOT be a subclass of QFormBase): ' . $strFormId);

			// Ensure accompanying HTML file exists
			if ($strAlternateHtmlFile) {
				if (!file_exists($strAlternateHtmlFile))
					throw new QCallerException("Accompanying HTML file does not exist: $strAlternateHtmlFile.  Note: I18n Templates are currently disabled.");
			} else {
				if (!file_exists(QApplication::$ScriptFilename . '.inc'))
					throw new QCallerException('Accompanying HTML file does not exist: ' . QApplication::$ScriptName . '.inc.  Note: I18n Templates are currently disabled.');
			}

			// See if we can get a Form Class out of PostData
			$objClass = null;			
			if (array_key_exists('Qform__FormId', $_POST) && ($_POST['Qform__FormId'] == $strFormId) && array_key_exists('Qform__FormState', $_POST)) {
				$strPostDataState = $_POST['Qform__FormState'];

				if ($strPostDataState)
					// We might have a valid form state -- let's see by unserializing this object
					file_put_contents('/tmp/dump', $strPostDataState);
					$objClass = QForm::Unserialize($strPostDataState);
			}

			if ($objClass) {
				global $$strFormId;
				$$strFormId = $objClass;

				$objClass->strCallType = $_POST['Qform__FormCallType'];
				$objClass->intFormStatus = QFormBase::FormStatusUnrendered;

				if ($objClass->strCallType == QCallType::Ajax)
					QApplication::$RequestMode = QRequestMode::Ajax;

				// Globalize and Set Variable
				global $$strFormId;
				$$strFormId = $objClass;

				// Iterate through all the control modifications
				$strModificationArray = explode("\n", trim($_POST['Qform__FormUpdates']));
				if ($strModificationArray) foreach ($strModificationArray as $strModification) {
					$strModification = trim($strModification);
					
					if ($strModification) {
						$intPosition = strpos($strModification, ' ');
						$strControlId = substr($strModification, 0, $intPosition);
						$strModification = substr($strModification, $intPosition + 1);
						
						$intPosition = strpos($strModification, ' ');
						$strProperty = substr($strModification, 0, $intPosition);
						$strValue = substr($strModification, $intPosition + 1);
						
						switch ($strProperty) {
							case 'Parent':
								if ($strValue) {
									if ($strValue == $objClass->FormId) {
										$objClass->objControlArray[$strControlId]->SetParentControl(null);
									} else {
										$objClass->objControlArray[$strControlId]->SetParentControl($objClass->objControlArray[$strValue]);
									}
								} else {
									// Remove all parents
									$objClass->objControlArray[$strControlId]->SetParentControl(null);
									$objClass->objControlArray[$strControlId]->SetForm(null);
									$objClass->objControlArray[$strControlId] = null;
									unset($objClass->objControlArray[$strControlId]);
								}
								break;
							default:
								$objClass->objControlArray[$strControlId]->__set($strProperty, $strValue);
								break;
						}
					}
				}
				
				// Clear the RenderedCheckableControlArray
				$objClass->blnRenderedCheckableControlArray = array();
				$strCheckableControlList = trim($_POST['Qform__FormCheckableControls']);
				$strCheckableControlArray = explode(' ', $strCheckableControlList);
				foreach ($strCheckableControlArray as $strCheckableControl) {
					$objClass->blnRenderedCheckableControlArray[trim($strCheckableControl)] = true;
				}

				// Iterate through all the controls 
				foreach ($objClass->objControlArray as $objControl) {
					// If they were rendered last time and are visible (and if ServerAction, enabled), then Parse its post data
					if (($objControl->Visible) &&
						(($objClass->strCallType == QCallType::Ajax) || ($objControl->Enabled)) &&
						($objControl->RenderMethod)) {
						// Call each control's ParsePostData()
						$objControl->ParsePostData();
					}

					// Reset the modified/rendered flags and the validation
					// in ALL controls
					$objControl->ResetFlags();
					$objControl->ValidationReset();
				}

				// Trigger Run Event (if applicable)
				$objClass->Form_Run();

				// Trigger Load Event (if applicable)
				$objClass->Form_Load();

				// Trigger a triggered control's Server- or Ajax- action (e.g. PHP method) here (if applicable)
				$objClass->TriggerActions();
			} else {
				// We have no form state -- Create Brand New One
				$objClass = new $strFormId();

				global $$strFormId;
				$$strFormId = $objClass;

				// By default, this form is being created NOT via a PostBack
				// So there is no CallType
				$objClass->strCallType = QCallType::None;

				$objClass->strFormId = $strFormId;
				$objClass->intFormStatus = QFormBase::FormStatusUnrendered;
				$objClass->objControlArray = array();
				$objClass->objGroupingArray = array();

				// Globalize and Set Variable
				global $$strFormId;
				$$strFormId = $objClass;

				// Trigger Run Event (if applicable)
				$objClass->Form_Run();

				// Trigger Create Event (if applicable)
				$objClass->Form_Create();
			}

			// Trigger PreRender Event (if applicable)
			$objClass->Form_PreRender();

			// Render the Page
			switch ($objClass->strCallType) {
				case QCallType::Ajax:
					// Must use AJAX-based renderer
					$objClass->RenderAjax();
					break;

				case QCallType::Server:
				case QCallType::None:
				case '':
					// Server/Postback or New Page -- Use Standard Rendering
					$objClass->Render($strAlternateHtmlFile);
					break;

				default:
					throw new Exception('Unknown Form CallType: ' . $objClass->strCallType);
			}

			// Ensure that RenderEnd() was called during the Render process
			switch ($objClass->intFormStatus) {
				case QFormBase::FormStatusUnrendered:
					throw new QCallerException('$this->RenderBegin() is never called in the HTML Include file');
				case QFormBase::FormStatusRenderBegun:
					throw new QCallerException('$this->RenderEnd() is never called in the HTML Include file');
				case QFormBase::FormStatusRenderEnded:
					break;
				default:
					throw new QCallerException('FormStatus is in an unknown status');
			}

			// Tigger Exit Event (if applicable)
			$objClass->Form_Exit();
		}

		protected function RenderAjaxHelper($objControl) {
			$strToReturn = $objControl->RenderAjax(false);
			if ($strToReturn)
				$strToReturn .= "\r\n";
			foreach ($objControl->GetChildControls() as $objChildControl)
				$strToReturn .= $this->RenderAjaxHelper($objChildControl);
			return $strToReturn;
		}
		
		protected function RenderAjax() {			
			// Create the Control collection
			$strToReturn = '<controls>';

			// Include each control (if applicable) that has been changed/modified
			foreach ($this->GetAllControls() as $objControl)
				if (!$objControl->ParentControl)
//					$strToReturn .= $objControl->RenderAjax(false) . "\r\n";
					$strToReturn .= $this->RenderAjaxHelper($objControl);

			$strCommands = '';
			
			// Look to the Application object for any commands to run
			foreach (QApplication::$AlertMessageArray as $strAlert) {
				$strAlert = QString::XmlEscape(sprintf('alert("%s");', addslashes($strAlert)));
				$strCommands .= sprintf('<command>%s</command>', $strAlert);
			}
			foreach (QApplication::$JavaScriptArrayHighPriority as $strJavaScript) {
				$strJavaScript = trim($strJavaScript);
				
				if (strlen($strJavaScript)) {
					if (QString::LastCharacter($strJavaScript) != ';')
						$strJavaScript .= ';';
					$strCommands .= sprintf('<command>%s</command>', QString::XmlEscape($strJavaScript));
				}
			}
			foreach (QApplication::$JavaScriptArray as $strJavaScript) {
				$strJavaScript = trim($strJavaScript);
				if (strlen($strJavaScript)) {
					if (QString::LastCharacter($strJavaScript) != ';')
						$strJavaScript .= ';';
					$strCommands .= sprintf('<command>%s</command>', QString::XmlEscape($strJavaScript));
				}
			}
			$strRegCJavaScript = '';
			foreach ($this->GetAllControls() as $objControl) {
				if ($objControl->Rendered) {
					$strRegCJavaScript .= sprintf('qc.regC("%s"); ', $objControl->ControlId);
				}
			}
			if ($strRegCJavaScript)
				$strCommands .= sprintf('<command>%s</command>', QString::XmlEscape($strRegCJavaScript));

			foreach ($this->GetAllControls() as $objControl) {
				if ($objControl->Rendered) {
					$strJavaScript = $objControl->GetEndScript();
					if (strlen($strJavaScript))
						$strCommands .= sprintf('<command>%s</command>', QString::XmlEscape($objControl->GetEndScript()));
				}
			}
			foreach ($this->objGroupingArray as $objGrouping) {
				$strRender = $objGrouping->Render();
				if (trim($strRender))
					$strCommands .= sprintf('<command>%s</command>', QString::XmlEscape($strRender));
			}

			// Add in the form state
			// DO SOMETHING DIFFERENT IF FORM IS UseSession
			$strFormState = QForm::Serialize($this);
			$strToReturn .= sprintf('<control id="Qform__FormState">%s</control>', $strFormState);

			// close Control collection, Open the Command collection
			$strToReturn .= '</controls><commands>';
			
			$strToReturn .= $strCommands;

			// close Command collection
			$strToReturn .= '</commands>';

			$strContents = trim(ob_get_contents());

			if (strtolower(substr($strContents, 0, 5)) == 'debug') {
			} else {
				ob_clean();

				// Response is in XML Format
				header('Content-Type: text/xml');

				// Output it and update render state
				if (QApplication::$EncodingType)
					printf("<?xml version=\"1.0\" encoding=\"%s\"?><response>%s</response>\r\n", QApplication::$EncodingType, $strToReturn);
				else
					printf("<?xml version=\"1.0\"?><response>%s</response>\r\n", $strToReturn);
			}

			// Update Render State
			$this->intFormStatus = QFormBase::FormStatusRenderEnded;
		}

		/**
		 * @param Form $objForm
		 * @return string the Serialized Form
		 */
		public final static function Serialize(QForm $objForm) {
			// Create a Clone of the Form to Serialize
			$objForm = clone($objForm);

			// Cleanup Reverse Control->Form links
			if ($objForm->objControlArray) foreach ($objForm->objControlArray as $objControl)
				$objControl->SetForm(null);

			// Use PHP "serialize" to serialize the form
			$strSerializedForm = serialize($objForm);

			// Setup and Call the FormStateHandler to retrieve the PostDataState to return
			$strSaveCommand = array(QForm::$FormStateHandler, 'Save');
			$strPostDataState = call_user_func($strSaveCommand, $strSerializedForm);

			// Return the PostDataState
			return $strPostDataState;
		}

		/**
		 * @param string $strSerializedForm
		 * @return Form the Form object
		 */
		public final static function Unserialize($strPostDataState) {
			// Setup and Call the FormStateHandler to retrieve the Serialized Form
			$strLoadCommand = array(QForm::$FormStateHandler, 'Load');
			$strSerializedForm = call_user_func($strLoadCommand, $strPostDataState);

			if ($strSerializedForm) {
				// Unserialize and Cast the Form
				$objForm = unserialize($strSerializedForm);
				$objForm = QType::Cast($objForm, 'QForm');

				// Reset the links from Control->Form
				if ($objForm->objControlArray) foreach ($objForm->objControlArray as $objControl)
					$objControl->SetForm($objForm);

				// Return the Form
				return $objForm;
			} else
				return null;
		}

		public final function AddControl(QControl $objControl) {
			$strControlId = $objControl->ControlId;
			if (array_key_exists($strControlId, $this->objControlArray))
				throw new QCallerException(sprintf('A control already exists in the form with the ID: %s', $strControlId));
			if (array_key_exists($strControlId, $this->objGroupingArray))
				throw new QCallerException(sprintf('A Grouping already exists in the form with the ID: %s', $strControlId));
			$this->objControlArray[$strControlId] = $objControl;
		}

		public final function GetControl($strControlId) {
			if (array_key_exists($strControlId, $this->objControlArray))
				return $this->objControlArray[$strControlId];
			else
				return null;
		}

		public final function RemoveControl($strControlId) {
			if (array_key_exists($strControlId, $this->objControlArray)) {
				// Get the Control in Question
				$objControl = $this->objControlArray[$strControlId];

				// Remove all Child Controls as well
				$objControl->RemoveChildControls(true);

				// Remove this control from the parent
				if ($objControl->ParentControl)
					$objControl->RemoveChildControl($strControlId);

				// Remove this control
				unset($this->objControlArray[$strControlId]);

				// Remove this control from any groups
				foreach ($this->objGroupingArray as $strKey => $objGrouping)
					$this->objGroupingArray[$strKey]->RemoveControl($strControlId);
			}
		}

		public final function GetAllControls() {
			return $this->objControlArray;
		}
		
		public final function AddGrouping(QControlGrouping $objGrouping) {
			$strGroupingId = $objGrouping->GroupingId;
			if (array_key_exists($strGroupingId, $this->objGroupingArray))
				throw new QCallerException(sprintf('A Grouping already exists in the form with the ID: %s', $strGroupingId));
			if (array_key_exists($strGroupingId, $this->objControlArray))
				throw new QCallerException(sprintf('A Control already exists in the form with the ID: %s', $strGroupingId));
			$this->objGroupingArray[$strGroupingId] = $objGrouping;
		}

		public final function GetGrouping($strGroupingId) {
			if (array_key_exists($strGroupingId, $this->objGroupingArray))
				return $this->objGroupingArray[$strGroupingId];
			else
				return null;
		}
		
		public final function RemoveGrouping($strGroupingId) {
			if (array_key_exists($strGroupingId, $this->objGroupingArray)) {
				// Remove this Grouping
				unset($this->objGroupingArray[$strGroupingId]);
			}
		}
		
		public final function GetAllGroupings() {
			return $this->objGroupingArray;
		}
		
		public final function GetChildControls($objParentObject) {
			$objControlArrayToReturn = array();

			if ($objParentObject instanceof QForm) {
				// They want all the ChildControls for this Form
				// Basically, return all objControlArray QControls where the Qcontrol's parent is NULL
				foreach ($this->objControlArray as $objChildControl) {
					if (!($objChildControl->ParentControl))
						array_push($objControlArrayToReturn, $objChildControl);
				}
				return $objControlArrayToReturn;

			} else if ($objParentObject instanceof QControl) {
				return $objParentObject->GetChildControls();
				// THey want all the ChildControls for a specific Control
				// Basically, return all objControlArray QControls where the Qcontrol's parent is the passed in parentobject
/*				$strControlId = $objParentObject->ControlId;
				foreach ($this->objControlArray as $objChildControl) {
					$objParentControl = $objChildControl->ParentControl;
					if (($objParentControl) && ($objParentControl->ControlId == $strControlId)) {
						array_push($objControlArrayToReturn, $objChildControl);
					}
				}*/

			} else
				throw new CallerException('ParentObject must be either a QForm or QControl object');
		}

		public final function EvaluateTemplate($strTemplate) {
			global $_ITEM;
			global $_FORM;
			global $_CONTROL;

			if ($strTemplate) {
				// Store the Output Buffer locally
				$strAlreadyRendered = ob_get_contents();
				ob_clean();

				// Evaluate the new template
				require($strTemplate);
				$strTemplateEvaluated = ob_get_contents();
				ob_clean();

				// Restore the output buffer and return evaluated template
				print($strAlreadyRendered);
				return $strTemplateEvaluated;
			} else
				return null;
		}
		
		public final function TriggerMethod($strId, $strMethodName) {
			$strParameter = $_POST['Qform__FormParameter'];

			$intPosition = strpos($strMethodName, ':');
			if ($intPosition !== false) {
				$strControlName = substr($strMethodName, 0, $intPosition);
				$strMethodName = substr($strMethodName, $intPosition + 1);

				$objControl = $this->objControlArray[$strControlName];
				$objControl->$strMethodName($this->strFormId, $strId, $strParameter);
			} else
				$this->$strMethodName($this->strFormId, $strId, $strParameter);
		}

		private final function TriggerActions($strControlIdOverride = null) {
			if (array_key_exists('Qform__FormControl', $_POST)) {
				if ($strControlIdOverride)
					$strId = $strControlIdOverride;
				else
					$strId = $_POST['Qform__FormControl'];
				$strEvent = $_POST['Qform__FormEvent'];

				if ($strId != '') {
					// Does this Control which performed the action exist?
					if (($objActionControl = $this->GetControl($strId))) {
						// Were we able to click on it? Otherwise, drop silently to avoid double-click-errors
						if ($objActionControl->Enabled && $objActionControl->Visible) {
						// Validation Check
						$blnValid = true;

						// If the control CausesValidation, go ahead and validate all Controls in the form
						if ($objActionControl->CausesValidation) {
							foreach ($this->objControlArray as $objControl) {
//								// Reset the Rendered and Modified Flags
//								$objControl->ResetFlags();

								// Only Enabled and Visible and Rendered controls should be validated
								if (($objControl->ActuallyVisible) && ($objControl->Enabled) && ($objControl->RenderMethod)) {
									$objControl->ValidationReset();
									if (!$objControl->Validate()) {
										$objControl->MarkAsModified();
										$blnValid = false;
									}
								}// else
//									$objControl->ValidationReset();
							}
						} /*else {
							// No validation requested -- go ahead and reset validation for all Controls
							foreach ($this->objControlArray as $objControl) {
								// Reset the Rendered and Modified Flags
								$objControl->ResetFlags();

								// Reset the Validation
								$objControl->ValidationReset();
							}
						}*/

						// Go ahead and run the ServerActions or AjaxActions if Validation Passed and if there are Server/Ajax-Actions defined
						if ($blnValid) {
							// Pull up the set of Actions to run (based on the Form's calltype)
							switch ($this->strCallType) {
								case QCallType::Ajax:
									$objActions = $objActionControl->GetAllActions($strEvent, 'QAjaxAction');
									break;
								case QCallType::Server:
									$objActions = $objActionControl->GetAllActions($strEvent, 'QServerAction');
									break;
								default:
									throw new Exception('Unknown Form CallType: ' . $this->strCallType);					
							}
							if ($objActions) foreach ($objActions as $objAction) {
								if ($strMethodName = $objAction->MethodName) {
									$this->TriggerMethod($strId, $strMethodName);
								}
							}
						} else 								
							$this->Form_Invalid();
					}} else
						// Nope -- Throw an exception
						throw new Exception(sprintf('Control passed by Qform__FormControl does not exist: %s', $strId));
				}/* else {
					// TODO: Code to automatically execute any PrimaryButton's onclick action, if applicable
					// Difficult b/c of all the Qcodo hidden parameters that need to be set to get the action to work properly
					// Javascript interaction of PrimaryButton works fine in Firefox... currently doens't work in IE 6.
				}*/
			}
		}

		protected function Render($strAlternateHtmlFile) {
			if ($strAlternateHtmlFile)
				require($strAlternateHtmlFile);
			else
				require(QApplication::$ScriptFilename . '.inc');
		}

		protected final function RenderChildren($blnDisplayOutput = true) {
			$strToReturn = "";

			foreach ($this->GetChildControls($this) as $objControl)
				if (!$objControl->Rendered)
					$strToReturn .= $objControl->Render($blnDisplayOutput);

			if ($blnDisplayOutput) {
				print ($strToReturn);
				return null;
			} else
				return $strToReturn;
		}

		// This exists to prevent inadverant "New"
		protected final function __construct() {}


		protected function RenderBegin($blnDisplayOutput = true) {
			// Ensure that RenderBegin() has not yet been called
			switch ($this->intFormStatus) {
				case QFormBase::FormStatusUnrendered:
					break;
				case QFormBase::FormStatusRenderBegun:
				case QFormBase::FormStatusRenderEnded:
					throw new QCallerException('$this->RenderBegin() has already been called');
					break;
				default:
					throw new QCallerException('FormStatus is in an unknown status');
			}

			// Update FormStatus
			$this->intFormStatus = QFormBase::FormStatusRenderBegun;

			// Iterate through the form's ControlArray to Define FormAttributes and JavaScriptIncludes
			$strJavaScriptArray = array();
			$strFormAttributeArray = array();
			foreach ($this->GetAllControls() as $objControl) {
				// JavaScript Includes?  The control would have a
				// comma-delimited list of javascript files to include (if applicable)
				if ($objControl->JavaScripts) {
					$strScriptArray = explode(',', $objControl->JavaScripts);
					
					if ($strScriptArray) foreach ($strScriptArray as $strScript) {
						if (trim($strScript))
							$strJavaScriptArray[trim($strScript)] = $strScript;
					}
				}

				// Form Attributes?
				if ($objControl->FormAttributes) {
					$strFormAttributeArray = array_merge($strFormAttributeArray, $objControl->FormAttributes);
				}
			}

			// Create $strFormAttributes
			$strFormAttributes = '';
			foreach ($strFormAttributeArray as $strKey=>$strValue) {
				$strFormAttributes .= sprintf(' %s="%s"', $strKey, $strValue);
			}
			
			$strOutputtedText = strtolower(trim(ob_get_contents()));
			if (strpos($strOutputtedText, '<body') === false) {
				$strToReturn = '<body>';
				$this->blnRenderedBodyTag = true;
			} else
				$strToReturn = '';

			// Setup Rendered HTML
//			$strToReturn .= sprintf('<form method="post" name="%s" id="%s" action="%s"%s>', $this->strFormId, $this->strFormId, QApplication::$RequestUri, $strFormAttributes);
			$strToReturn .= sprintf('<form method="post" id="%s" autocomplete="off" action="%s"%s>', $this->strFormId, QApplication::$RequestUri, $strFormAttributes);

			// Call in JavaScript
			$strToReturn .= sprintf('<script type="text/javascript" src="%s%s/includes/qcodo/qform_objects/_form.js"></script>', DOCROOT_VIRTUAL_DIRECTORY, DOCROOT_SUBFOLDER);

			// Call in OTHER JavaScripts (if any)
			foreach ($strJavaScriptArray as $strScript)
				$strToReturn .= sprintf('<script type="text/javascript" src="%s%s/includes/qform/assets/%s"></script>', DOCROOT_VIRTUAL_DIRECTORY, DOCROOT_SUBFOLDER, $strScript);

			// Perhaps a strFormModifiers as an array to
			// allow controls to update other parts of the form, like enctype, onsubmit, etc.

			// Return or Display
			if ($blnDisplayOutput) {
				print ($strToReturn);
				return null;
			} else
				return $strToReturn;
		}

		/**
		 * Will return an array of Control objects that exists within this object.
		 * Doesn't matter if the object is directly defined in the class, or if
		 * it's defined within an array in the class.
		 *
		 * The returned array will be indexed by the ControlId with which the control was created.
		 *
		 * Side Effect: Anything NOT a control in the object will be nulled out if blnNullNonControlObjects is true
		 * Exception: will be thrown if two controls in this object have the same ControlId.
		 */
/*		private final function GetControlArray($blnNullNonControlObjects = false) {
			// Setup the return array
			$objControlArray = array();

			// Reflect this class
			$objReflection = new ReflectionClass($this->strFormId);
			
			// Pull the properties in this class
			$objPropertyArray = $objReflection->getProperties();

			// Iterate through each property in the class
			if ($objPropertyArray) foreach ($objPropertyArray as $objProperty) {
				// Only check properties NOT declared in Form and FormBase
				$strDeclaringClassName = $objProperty->getDeclaringClass()->getName();
				if (($strDeclaringClassName != 'Form') && ($strDeclaringClassName != 'FormBase')) {
					
					// Get the property name and this object's value for that property
					$strPropertyName = $objProperty->getName();
					$mixValue = &$this->$strPropertyName;

					if ($mixValue instanceof QControl) {						
						// This property IS a control -- add it to the return objControlArray
						if (!array_key_exists($mixValue->ControlId, $objControlArray))
							$objControlArray[$mixValue->ControlId] = $mixValue;
						else {
							// Duplicate ControlId found.  Throw exception.
							$objReflection = new ReflectionClass($mixValue);
							throw new QCallerException($objReflection->getName()  . " Control " . $strPropertyName . " is attempting to use a duplicate Control ID: " . $mixValue->ControlId);
						}
					} else if (gettype($mixValue) == Type::ArrayType) {
						// This property is an array.  Iterate through the array
						foreach ($mixValue as $mixKey=>$mixObject) {
							if ($mixObject instanceof QControl) {
								// This item in the array is a control! -- ad it to the return objControlArray
								if (!array_key_exists($mixObject->ControlId, $objControlArray))
									$objControlArray[$mixObject->ControlId] = $mixObject;
								else {
									// Duplicate ControlId found.  Throw exception.
									$objReflection = new ReflectionClass($mixObject);
									throw new QCallerException($objReflection->getName()  . " Control " . $strPropertyName . "[" . $mixValue . "] is attempting to use a duplicate Control ID: " . $mixObject->ControlId);
								}
							} else {
								// This array element is NOT a control.
								if ($blnNullNonControlObjects) {
									$mixValue[$mixKey] = null;
									unset($mixValue[$mixKey]);
								}
							}
						}
					} else {
						// This property is NOT a control.
						if ($blnNullNonControlObjects)
							$this->$strPropertyName = null;
					}
				}
			}
			// Return the return array
			return $objControlArray;
		}
*/		
		public function IsPostBack() {
			return ($this->strCallType != QCallType::None);
		}

		/**
		 * Will return an array of Strings which will show all the error and warning messages
		 * in all the controls in the form.
		 * 
		 * @param bool $blnErrorsOnly Show only the errors (otherwise, show both warnings and errors)
		 * @return string[] an array of strings representing the (multiple) errors and warnings
		 */
		protected function GetErrorMessages($blnErrorsOnly = false) {
			$strToReturn = array();
			foreach ($this->GetAllControls() as $objControl) {
				if ($objControl->ValidationError)
					array_push($strToReturn, $objControl->ValidationError);
				if (!$blnErrorsOnly)
					if ($objControl->Warning)
						array_push($strToReturn, $objControl->Warning);
			}
			
			return $strToReturn;
		}

		/**
		 * Will return an array of QControls from the form which have either an error or warning message.
		 * 
		 * @param bool $blnErrorsOnly Return controls that have just errors (otherwise, show both warnings and errors)
		 * @return QControl[] an array of controls representing the (multiple) errors and warnings
		 */
		protected function GetErrorControls($blnErrorsOnly = false) {
			$objToReturn = array();
			foreach ($this->GetAllControls() as $objControl) {
				if ($objControl->ValidationError)
					array_push($objToReturn, $objControl);
				else if (!$blnErrorsOnly)
					if ($objControl->Warning)
						array_push($objToReturn, $objControl);
			}

			return $objToReturn;
		}

		protected function RenderEnd($blnDisplayOutput = true) {
			// Ensure that RenderEnd() has not yet been called
			switch ($this->intFormStatus) {
				case QFormBase::FormStatusUnrendered:
					throw new QCallerException('$this->RenderBegin() was never called');
				case QFormBase::FormStatusRenderBegun:
					break;
				case QFormBase::FormStatusRenderEnded:
					throw new QCallerException('$this->RenderEnd() has already been called');
					break;
				default:
					throw new QCallerException('FormStatus is in an unknown status');
			}

			// Get End Script
//			$strEndScript = '<script type="text/javascript">';
			$strEndScript = '';
			foreach ($this->GetAllControls() as $objControl)
				if ($objControl->Rendered)
//				$strEndScript .= sprintf('qcodo.registerControl("%s"); ', $objControl->ControlId);
					$strEndScript .= sprintf('qc.regC("%s"); ', $objControl->ControlId);
			foreach ($this->GetAllControls() as $objControl)
				if ($objControl->Rendered)
					$strEndScript .= $objControl->GetEndScript();
			foreach ($this->objGroupingArray as $objGrouping) {
				$strEndScript .= $objGrouping->Render();
			}
			$strEndScript .= sprintf('qc.includesPath = "%s"; ', DOCROOT_VIRTUAL_DIRECTORY . DOCROOT_SUBFOLDER . '/includes');
			
			// End Script Compressor
			$strEndScriptArray = explode('; ', $strEndScript);
			$strEndScriptCommands = array();
			foreach ($strEndScriptArray as $strEndScript)
				$strEndScriptCommands[trim($strEndScript)] = true;
				
			// End Script Outputter
//			$strEndScript = sprintf('<script type="text/javascript">%s</script>',
			$strEndScript = sprintf('<script type="text/javascript">%s qc.registerForm();</script>',
				implode('; ', array_keys($strEndScriptCommands)));

			// Clone Myself
			$objForm = clone($this);

			// Render HTML
			$strToReturn = "\n\t";
			$strToReturn .= sprintf('<input type="hidden" name="Qform__FormState" id="Qform__FormState" value="%s" />', QForm::Serialize($objForm));

			$strToReturn .= "\n\t";			
			$strToReturn .= sprintf('<input type="hidden" name="Qform__FormId" id="Qform__FormId" value="%s" />', $this->strFormId);

//			$strToReturn .= "\n\t";
//			$strToReturn .= '<input type="hidden" name="Qform__FormControl" id="Qform__FormControl" value="" />';
//			$strToReturn .= '<input type="hidden" name="Qform__FormEvent" id="Qform__FormEvent" value="" />';
//			$strToReturn .= '<input type="hidden" name="Qform__FormParameter" id="Qform__FormParameter" value="" />';
//			$strToReturn .= '<input type="hidden" name="Qform__FormCallType" id="Qform__FormCallType" value="" />';
//			$strToReturn .= '<input type="hidden" name="Qform__FormUpdates" id="Qform__FormUpdates" value="" />';
//			$strToReturn .= '<input type="hidden" name="Qform__FormCheckableControls" id="Qform__FormCheckableControls" value="" />';

/*			$strToReturn .= '<div id="Qform_Logger" style="display:none;width:400px;background-color:#dddddd;font-size:10px;font-family:lucida console, courier, monospaced;padding:6px;';
			if (QApplication::IsBrowser(QBrowserType::InternetExplorer))
				$strToReturn .= 'filter:alpha(opacity=50);';
			else
				$strToReturn .= 'opacity:0.5;';
			$strToReturn .= 'overflow:auto;"></div>';*/

			foreach ($this->GetAllControls() as $objControl)
				if ($objControl->Rendered)
					$strToReturn .= $objControl->GetEndHtml();
			$strToReturn .= "\n</form>";

			$strToReturn .= $strEndScript;

			if ($this->blnRenderedBodyTag)
				$strToReturn .= '</body>';

			// Update Form Status
			$this->intFormStatus = QFormBase::FormStatusRenderEnded;

			// Display or Return
			if ($blnDisplayOutput) {
				print ($strToReturn);
				return null;
			} else
				return $strToReturn;
		}
	}
?>