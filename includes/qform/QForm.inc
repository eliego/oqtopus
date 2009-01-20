<?php
	abstract class QForm extends QFormBase {
		///////////////////////////
		// Form Preferences
		///////////////////////////

		/**
		 * If you wish to encrypt the resulting formstate data to be put on the form (via
		 * QCryptography), please specify a key to use.  The default cipher and encrypt mode
		 * on QCryptography will be used, and because the resulting encrypted data will be
		 * sent via HTTP POST, it will be Base64 encoded.
		 *
		 * @var string EncryptionKey the key to use, or NULL if no encryption is required
		 */
		public static $EncryptionKey = null;

		/**
		 * The QFormStateHandler to use to handle the actual serialized form.  By default,
		 * QFormStateHandler will be used (which simply outputs the entire serialized
		 * form data stream to the form), but file- and session- based, or any custom db-
		 * based FormState handling can be used as well.
		 *
		 * @var string FormStateHandler the classname of the FormState handler to use
		 */
		public static $FormStateHandler = 'QFormStateHandler';
		
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
			$strToReturn .= sprintf('<script type="text/javascript" src="/js/_form.js"></script>');

			// Call in OTHER JavaScripts (if any)
			foreach ($strJavaScriptArray as $strScript)
				$strToReturn .= sprintf('<script type="text/javascript" src="/js/%s"></script>', $strScript);

			// Perhaps a strFormModifiers as an array to
			// allow controls to update other parts of the form, like enctype, onsubmit, etc.

			// Return or Display
			if ($blnDisplayOutput) {
				print ($strToReturn);
				return null;
			} else
				return $strToReturn;
		}
		protected function RenderAjax() {			
			// Create the Control collection
			$strToReturn = '<controls>';

			// Include each control (if applicable) that has been changed/modified
			foreach ($this->GetAllControls() as $objControl)
				if (!$objControl->ParentControl)
//					$strToReturn .= $objControl->RenderAjax(false) . "\r\n";
					$strToReturn .= $objControl->Visible ? $this->RenderAjaxHelper($objControl) : sprintf('<control id="%s"></control>', $objControl->ControlId);

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
	}
?>