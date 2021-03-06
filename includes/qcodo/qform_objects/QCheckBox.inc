<?php
	// This class will render an HTML Checkbox.
	// * "Text" is used to display text that is displayed next to the checkbox.  The text is rendered as
	//   an html "Label For" the checkbox.
	// * "TextAlign" specifies if "Text" should be displayed to the left or to the right of the checkbox.
	// * "Checked" specifices whether or not hte checkbox is checked

	class QCheckBox extends QControl {
		///////////////////////////
		// Private Member Variables
		///////////////////////////

		// APPEARANCE
		protected $strText = null;
		protected $strTextAlign = QTextAlign::Right;
		
		// MISC
		protected $blnChecked = false;

		//////////
		// Methods
		//////////
		public function ParsePostData() {
			if ($this->objForm->IsCheckableControlRendered($this->strControlId)) {
				if (array_key_exists($this->strControlId, $_POST)) {
					if ($_POST[$this->strControlId])
						$this->blnChecked = true;
					else
						$this->blnChecked = false;
				} else {
					$this->blnChecked = false;
				}
			}
		}

		public function GetJavaScriptAction() {
			return "onclick";
		}

		protected function GetControlHtml() {
			if (!$this->blnEnabled)
				$strDisabled = 'disabled="disabled" ';
			else
				$strDisabled = "";

			if ($this->intTabIndex)
				$strTabIndex = sprintf('tabindex="%s" ', $this->intTabIndex);
			else
				$strTabIndex = "";

			if ($this->strToolTip)
				$strToolTip = sprintf('title="%s" ', $this->strToolTip);
			else
				$strToolTip = "";

			if ($this->strCssClass)
				$strCssClass = sprintf('class="%s" ', $this->strCssClass);
			else
				$strCssClass = "";

			if ($this->strAccessKey)
				$strAccessKey = sprintf('accesskey="%s" ', $this->strAccessKey);
			else
				$strAccessKey = "";
				
			if ($this->blnChecked)
				$strChecked = 'checked="checked"';
			else
				$strChecked = "";

			$strStyle = $this->GetStyleAttributes();
			if (strlen($strStyle) > 0)
				$strStyle = sprintf('style="%s" ', $strStyle);

			$strCustomAttributes = $this->GetCustomAttributes();

			$strActions = $this->GetActionAttributes();

			if ($this->strTextAlign == QTextAlign::Left) {
				$strToReturn = sprintf('<table cellspacing="0" cellpadding="0" border="0"><tr><td %s%s%s%s%s><label for="%s">%s</label><input type="checkbox" id="%s" name="%s" %s%s%s%s%s /></td></tr></table>',
					$strCssClass,
					$strToolTip,
					$strStyle,
					$strCustomAttributes,
					$strDisabled,
					$this->strControlId,
					$this->strText,
					$this->strControlId,
					$this->strControlId,
					$strDisabled,
					$strChecked,
					$strActions,
					$strAccessKey,
					$strTabIndex
				);				
			} else {
				$strToReturn = sprintf('<table cellspacing="0" cellpadding="0" border="0"><tr><td><input type="checkbox" id="%s" name="%s" %s%s%s%s%s /></td><td %s%s%s%s%s><label for="%s">%s</label></td></tr></table>',
					$this->strControlId,
					$this->strControlId,
					$strDisabled,
					$strChecked,
					$strActions,
					$strAccessKey,
					$strTabIndex,
					$strCssClass,
					$strToolTip,
					$strStyle,
					$strCustomAttributes,
					$strDisabled,
					$this->strControlId,
					$this->strText
				);
			}

			return $strToReturn;
		}

		public function Validate() {
			if ($this->blnRequired) {
				if (!$this->blnChecked) {
					$this->strValidationError = sprintf("%s is required", $this->strName);
					return false;
				}
			}

			$this->strValidationError = null;
			return true;
		}

		/////////////////////////
		// Public Properties: GET
		/////////////////////////
		public function __get($strName) {
			switch ($strName) {
				// APPEARANCE
				case "Text": return $this->strText;
				case "TextAlign": return $this->strTextAlign;

				// MISC
				case "Checked": return $this->blnChecked;
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
				case "Text":
					try {
						$this->strText = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "TextAlign":
					try {
						$this->strTextAlign = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				
				// MISC
				case "Checked":
					try {
						$this->blnChecked = QType::Cast($mixValue, QType::Boolean);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
					
				default:
					try {
						parent::__set($strName, $mixValue);
						break;
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		public function RenderWithName($blnDisplayOutput = true) {
			////////////////////
			// Call RenderHelper
			$this->RenderHelper(func_get_args(), __FUNCTION__);
			////////////////////

			// Custom Render Functionality Here
			if ($this->strName) {
//				if ($this->blnRequired)
					$strName = sprintf('<b>%s</b>', $this->strName);
//				else
//					$strName = sprintf('%s', $this->strName);
			} else
				$strName = '';

			try {
				if ($this->blnEnabled)
					$strClass = 'item_label';
				else
					$strClass = 'item_label_disabled';

				$strToReturn = sprintf('<div class="%s">%s</div>%s%s%s',
					$strClass,
					$strName,
					$this->strHtmlBefore,
					$this->GetControlHtml(),
					$this->strHtmlAfter);

				if ($this->strInstructions)
					$strToReturn .= sprintf('<br /><span class="instructions">%s</span>', $this->strInstructions);

				if ($this->strValidationError)
					$strToReturn .= sprintf('<br /><span class="%s">%s</span>', $this->strErrorClass, $this->strValidationError);
				else if ($this->strWarning)
					$strToReturn .= sprintf('<br /><span class="%s">%s</span>', $this->strErrorClass, $this->strWarning);

				$strToReturn .= '<br />';
			} catch (QCallerException $objExc) {
				$objExc->IncrementOffset();
				throw $objExc;
			}

			////////////////////////////////////////////
			// Call RenderOutput, Returning its Contents
			return $this->RenderOutput($strToReturn, $blnDisplayOutput);
			////////////////////////////////////////////
		}		
	}
?>