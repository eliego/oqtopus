<?php
	// This class will render an HTML Textbox -- which can either be <input type="text">,
	// <input type="password"> or <textarea> depending on the TextMode (see below).
	// * "Columns" is the "cols" html attribute (applicable for MultiLine textboxes)
	// * "Text" is the contents of the textbox, itself
	// * "MaxLength" is the "maxlength" html attribute (applicable for SingleLine textboxes)
	// * "MinLength" is the minimum requred length to pass validation
	// * "ReadOnly" is the "readonly" html attribute (making a textbox "ReadOnly" is very similar to setting
	//   the textbox to Enabled=false.  There are only subtle display-differences, I believe, between the two.
	// * "Rows" is the "rows" html attribute (applicable for MultiLine textboxes)
	// * "TextMode" can be "SingleLine", "MultiLine", and "Password".
	// * "Wrap" is the "wrap" html attribute (applicable for MultiLine textboxes)
	//
	// * "CrossScripting" can be Allow, HtmlEntities, or Deny.  Deny is the default.
	//   Prevents cross scripting hacks.  HtmlEntities causes framework to automatically call php
	//   function htmlentities on the input data.  Allow allows everything to come through without altering
	//   at all.  USE "ALLOW" judiciously: using ALLOW on text entries, and then outputting that data
	//   WILL allow hackers to perform cross scripting hacks.

	abstract class QTextBoxBase extends QControl {
		///////////////////////////
		// Private Member Variables
		///////////////////////////

		// APPEARANCE
		protected $intColumns = 0;
		protected $strText = null;
		protected $strLabelForRequired;
		protected $strLabelForRequiredUnnamed;

		// BEHAVIOR
		protected $intMaxLength = 0;
		protected $intMinLength = 0;
		protected $blnReadOnly = false;
		protected $intRows = 0;
		protected $strTextMode = QTextMode::SingleLine;
		protected $strCrossScripting = QCrossScripting::Deny;

		// LAYOUT
		protected $blnWrap = true;

		//////////
		// Methods
		//////////
		public function __construct($objParentObject, $strControlId = null) {
			parent::__construct($objParentObject, $strControlId);

			$this->strLabelForRequired = QApplication::Translate('%s is required');
			$this->strLabelForRequiredUnnamed = QApplication::Translate('Required');
		}


		public function ParsePostData() {
			// Check to see if this Control's Value was passed in via the POST data
			if (array_key_exists($this->strControlId, $_POST)) {
				// It was -- update this Control's value with the new value passed in via the POST arguments
				$this->strText = $_POST[$this->strControlId];	
				
				switch ($this->strCrossScripting) {
					case QCrossScripting::Allow:
						// Do Nothing, allow everything
						break;
					case QCrossScripting::HtmlEntities:
						// Go ahead and perform HtmlEntities on the text
						$this->strText = htmlentities($this->strText, ENT_COMPAT, QApplication::$EncodingType);
						break;
					default:
						// Deny the Use of CrossScripts

						// Check for cross scripting patterns
						// TODO: Change this to RegExp						
						$strText = strtolower($this->strText);
						if ((strpos($strText, '<script') !== false) ||
							(strpos($strText, '<applet') !== false) ||
							(strpos($strText, '<embed') !== false) ||
							(strpos($strText, '<style') !== false) ||
							(strpos($strText, '<link') !== false) ||
							(strpos($strText, '<body') !== false) ||
							(strpos($strText, '<iframe') !== false) ||
							(strpos($strText, 'javascript:') !== false) ||
							(strpos($strText, ' onfocus=') !== false) ||
							(strpos($strText, ' onblur=') !== false) ||
							(strpos($strText, ' onkeydown=') !== false) ||
							(strpos($strText, ' onkeyup=') !== false) ||
							(strpos($strText, ' onkeypress=') !== false) ||
							(strpos($strText, ' onmousedown=') !== false) ||
							(strpos($strText, ' onmouseup=') !== false) ||
							(strpos($strText, ' onmouseover=') !== false) ||
							(strpos($strText, ' onmouseout=') !== false) ||
							(strpos($strText, ' onmousemove=') !== false) ||
							(strpos($strText, ' onclick=') !== false) ||
							(strpos($strText, '<object') !== false) ||
							(strpos($strText, 'background:url') !== false))
							throw new QCallerException('Cross Scripting Violation -- SCRIPT EMBED OBJECT LINK APPLET STYLE IFRAME BODY BACKGROUND:URL and JavaScript not allowed in ' . $this->strControlId);
				}
			}
		}

		public function GetJavaScriptAction() {
			return "onchange";
		}

		public function GetAttributes($blnIncludeCustom = true, $blnIncludeAction = true) {
			$strToReturn = parent::GetAttributes($blnIncludeCustom, $blnIncludeAction);

			if ($this->blnReadOnly)
				$strToReturn .= 'readonly="readonly" ';
			
			if ($this->strTextMode == QTextMode::MultiLine) {
				if ($this->intColumns)
					$strToReturn .= sprintf('cols="%s" ', $this->intColumns);			
				if ($this->intRows)
					$strToReturn .= sprintf('rows="%s" ', $this->intRows);
				if (!$this->blnWrap)
					$strToReturn .= 'wrap="off" ';
			} else {
				if ($this->intColumns)
					$strToReturn .= sprintf('size="%s" ', $this->intColumns);
				if ($this->intMaxLength)
					$strToReturn .= sprintf('maxlength="%s" ', $this->intMaxLength);
			}
				
			return $strToReturn;
		}

		protected function GetControlHtml() {
			$strStyle = $this->GetStyleAttributes();
			if ($strStyle)
				$strStyle = sprintf('style="%s"', $strStyle);

			switch ($this->strTextMode) {
				case QTextMode::MultiLine:
					$strToReturn = sprintf('<textarea name="%s" id="%s" %s%s>%s</textarea>',
						$this->strControlId,
						$this->strControlId,
						$this->GetAttributes(),
						$strStyle,
						htmlentities($this->strText, ENT_COMPAT, QApplication::$EncodingType));
					break;
				case QTextMode::Password:
					$strToReturn = sprintf('<input type="password" name="%s" id="%s" value="%s" %s%s />',
						$this->strControlId,
						$this->strControlId,
						htmlentities($this->strText, ENT_COMPAT, QApplication::$EncodingType),
						$this->GetAttributes(),
						$strStyle);
					break;
				case QTextMode::SingleLine:
				default:
					$strToReturn = sprintf('<input type="text" name="%s" id="%s" value="%s" %s%s />',
						$this->strControlId,
						$this->strControlId,
						htmlentities($this->strText, ENT_COMPAT, QApplication::$EncodingType),
						$this->GetAttributes(),
						$strStyle);
			}

			return $strToReturn;
		}

		public function Validate() {
			$this->strValidationError = "";

			if ($this->intMinLength > (strlen($this->strText))) {
				if ($this->strName)
					$this->strValidationError = sprintf(_tr("Must be at least %s characters long"),$this->intMinLength);
				else
					$this->strValidationError = sprintf(_tr("Entry too short (must be at least %s characters long)"),$this->intMinLength);
				$this->blnModified = true;
				return false;
			}

			if ($this->blnRequired) {
				if (strlen($this->strText) > 0)
					return true;
				else {
					if ($this->strName)
						$this->strValidationError = sprintf($this->strLabelForRequired, $this->strName);
					else
						$this->strValidationError = $this->strLabelForRequiredUnnamed;
					$this->blnModified = true;
					return false;
				}
			}
			return true;
		}

		/////////////////////////
		// Public Properties: GET
		/////////////////////////
		public function __get($strName) {
			switch ($strName) {
				// APPEARANCE
				case "Columns": return $this->intColumns;
				case "Text": return $this->strText;
				case "LabelForRequired": return $this->strLabelForRequired;
				case "LabelForRequiredUnnamed": return $this->strLabelForRequiredUnnamed;

				// BEHAVIOR
				case "CrossScripting": return $this->strCrossScripting;
				case "MaxLength": return $this->intMaxLength;
				case "MinLength": return $this->intMinLength;
				case "ReadOnly": return $this->blnReadOnly;
				case "Rows": return $this->intRows;
				case "TextMode": return $this->strTextMode;

				// LAYOUT
				case "Wrap": return $this->blnWrap;

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
		// Public Properties: SET
		/////////////////////////
		public function __set($strName, $mixValue) {
			$this->blnModified = true;

			switch ($strName) {
				// APPEARANCE
				case "Columns":
					try {
						$this->intColumns = QType::Cast($mixValue, QType::Integer);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "Text":
					try {
						$this->strText = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "LabelForRequired":
					try {
						$this->strLabelForRequired = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "LabelForRequiredUnnamed":
					try {
						$this->strLabelForRequiredUnnamed = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				// BEHAVIOR
				case "CrossScripting":
					try {
						$this->strCrossScripting = QType::Cast($mixValue, QType::Boolean);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "MaxLength":
					try {
						$this->intMaxLength = QType::Cast($mixValue, QType::Integer);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "MinLength":
					try {
						$this->intMinLength = QType::Cast($mixValue, QType::Integer);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "ReadOnly":
					try {
						$this->blnReadOnly = QType::Cast($mixValue, QType::Boolean);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "Rows":
					try {
						$this->intRows = QType::Cast($mixValue, QType::Integer);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "TextMode":
					try {
						$this->strTextMode = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				// LAYOUT
				case "Wrap":
					try {
						$this->blnWrap = QType::Cast($mixValue, QType::Boolean);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
					break;
			}
		}
	}
?>
