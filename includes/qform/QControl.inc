<?php
	/*
	 * This class is INTENDED to be modified.  Please define any custom "Render"-based methods
	 * to handle custom global rendering functionality for all your controls.
	 *
	 * As an EXAMPLE, a RenderWithName method is included for you.  Feel free to modify this method,
	 * or to add as many of your own as you wish.
	 *
	 * Please note: All custom render methods should start with a RenderHelper call and end with a RenderOUtput call.
	 */
	abstract class QControl extends QControlBase {
		// This will call GetControlHtml() for the bulk of the work, but will add layout html as well.  It will include
		// the rendering of the Controls' name label, any errors or warnings, instructions, and html before/after (if specified).
		// 
		// This one method can define how ALL controls should be rendered when "Rendered with Name" throughout the entire site.
		// For example:
		//			<Name>
		//			<HTML Before><Control><HTML After>
		//			<Instructions>
		//			<Error>
		//			<warning>
		protected $strErrorClass = 'Error';
		
		public function ResetRenderState() {
			//$this->blnRendered = false;
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

				//$strToReturn .= '<br />';
			} catch (QCallerException $objExc) {
				$objExc->IncrementOffset();
				throw $objExc;
			}

			////////////////////////////////////////////
			// Call RenderOutput, Returning its Contents
			return $this->RenderOutput($strToReturn, $blnDisplayOutput);
			////////////////////////////////////////////
		}
		
		public function RenderWithError($blnDisplayOutput = true) {
			// Call RenderHelper
			$this->RenderHelper(func_get_args(), __FUNCTION__);

			try {
				$strOutput = $this->GetControlHtml();

				if ($this->strValidationError)
					$strOutput .= sprintf('<br /><span class="%s">%s</span>', $this->strErrorClass, $this->strValidationError);
				else if ($this->strWarning)
					$strOutput .= sprintf('<br /><span class="%s">%s</span>', $this->strErrorClass, $this->strWarning);
			} catch (QCallerException $objExc) {
				$objExc->IncrementOffset();
				throw $objExc;
			}

			// Call RenderOutput, Returning its Contents
			return $this->RenderOutput($strOutput, $blnDisplayOutput);
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'ErrorClass':
					return $this->strErrorClass;
					
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
				case 'ErrorClass':
					$this->strErrorClass = $mixValue;
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
	}
?>