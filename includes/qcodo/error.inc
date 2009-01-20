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

	class QErrorAttribute {
		public $Label;
		public $Contents;
		public $MultiLine;
		
		public function __construct($strLabel, $strContents, $blnMultiLine) {
			$this->Label = $strLabel;
			$this->Contents = $strContents;
			$this->MultiLine = $blnMultiLine;
		}
	}

	// Exception and Error Handling
	function QcodoHandleException(Exception $__exc_objException) {
		QApplication::$ErrorFlag = true;

		global $__exc_strType;
		if (isset($__exc_strType))
			return;
			
		$__exc_objReflection = new ReflectionObject($__exc_objException);

		$__exc_strType = "Exception";
		$__exc_strMessage = $__exc_objException->getMessage();
		$__exc_strObjectType = $__exc_objReflection->getName();

		if ($__exc_objException instanceof QDatabaseExceptionBase) {
			$__exc_objErrorAttribute = new QErrorAttribute("Database Error Number", $__exc_objException->ErrorNumber, false);
			$__exc_objErrorAttributeArray[0] = $__exc_objErrorAttribute;

			if ($__exc_objException->Query) {
				$__exc_objErrorAttribute = new QErrorAttribute("Query", $__exc_objException->Query, true);
				$__exc_objErrorAttributeArray[1] = $__exc_objErrorAttribute;
			}
		}

		$__exc_strFilename = $__exc_objException->getFile();
		$__exc_intLineNumber = $__exc_objException->getLine();
		$__exc_strStackTrace = trim($__exc_objException->getTraceAsString());

		if (ob_get_length()) {
			$__exc_strRenderedPage = ob_get_contents();
			ob_clean();
		}

		// Call to display the Error Page (as defined in _configuration.inc)
		require(__INCLUDES__ . ERROR_PAGE_PATH);
		exit;
	}

	function QcodoHandleError($__exc_errno, $__exc_errstr, $__exc_errfile, $__exc_errline) {
		QApplication::$ErrorFlag = true;

		global $__exc_strType;
		if (isset($__exc_strType))
			return;

		$__exc_strType = "Error";
		$__exc_strMessage = $__exc_errstr;

		switch ($__exc_errno) {
			case E_ERROR:
				$__exc_strObjectType = "E_ERROR";
				break;
			case E_WARNING:
				$__exc_strObjectType = "E_WARNING";
				break;
			case E_PARSE:
				$__exc_strObjectType = "E_PARSE";
				break;
			case E_NOTICE:
				$__exc_strObjectType = "E_NOTICE";
				break;
			case E_STRICT:
				$__exc_strObjectType = "E_STRICT";
				break;
			case E_CORE_ERROR:
				$__exc_strObjectType = "E_CORE_ERROR";
				break;
			case E_CORE_WARNING:
				$__exc_strObjectType = "E_CORE_WARNING";
				break;
			case E_COMPILE_ERROR:
				$__exc_strObjectType = "E_COMPILE_ERROR";
				break;
			case E_COMPILE_WARNING:
				$__exc_strObjectType = "E_COMPILE_WARNING";
				break;
			case E_USER_ERROR:
				$__exc_strObjectType = "E_USER_ERROR";
				break;
			case E_USER_WARNING:
				$__exc_strObjectType = "E_USER_WARNING";
				break;
			case E_USER_NOTICE:
				$__exc_strObjectType = "E_USER_NOTICE";
				break;
			default:
				$__exc_strObjectType = "Unknown";
				break;
		}

		$__exc_strFilename = $__exc_errfile;
		$__exc_intLineNumber = $__exc_errline;
		$__exc_strStackTrace = "";
		$__exc_objBacktrace = debug_backtrace();
		for ($__exc_intIndex = 0; $__exc_intIndex < count($__exc_objBacktrace); $__exc_intIndex++) {
			$__exc_objItem = $__exc_objBacktrace[$__exc_intIndex];
			
			$__exc_strKeyFile = (array_key_exists("file", $__exc_objItem)) ? $__exc_objItem["file"] : "";
			$__exc_strKeyLine = (array_key_exists("line", $__exc_objItem)) ? $__exc_objItem["line"] : "";
			$__exc_strKeyClass = (array_key_exists("class", $__exc_objItem)) ? $__exc_objItem["class"] : "";
			$__exc_strKeyType = (array_key_exists("type", $__exc_objItem)) ? $__exc_objItem["type"] : "";
			$__exc_strKeyFunction = (array_key_exists("function", $__exc_objItem)) ? $__exc_objItem["function"] : "";
			
			$__exc_strStackTrace .= sprintf("#%s %s(%s): %s%s%s()\n",
				$__exc_intIndex,
				$__exc_strKeyFile,
				$__exc_strKeyLine,
				$__exc_strKeyClass,
				$__exc_strKeyType,
				$__exc_strKeyFunction);
		}

		if (ob_get_length()) {
			$__exc_strRenderedPage = ob_get_contents();
			ob_clean();
		}

		// Call to display the Error Page (as defined in _configuration.inc)
		require(__INCLUDES__ . ERROR_PAGE_PATH);
		exit;
	}

	function PrepDataForScript($strData) {
		$strData = str_replace("\\", "\\\\", $strData);
		$strData = str_replace("\n", "\\n", $strData);
		$strData = str_replace("\r", "\\r", $strData);
		$strData = str_replace("\"", "&quot;", $strData);
		$strData = str_replace("</script>", "&lt/script&gt", $strData);
		$strData = str_replace("</Script>", "&lt/script&gt", $strData);
		$strData = str_replace("</SCRIPT>", "&lt/script&gt", $strData);
		return $strData;
	}
?>
