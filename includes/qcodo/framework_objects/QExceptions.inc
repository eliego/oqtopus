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

	/**
	 * This is the main exception to be thrown by any
	 * method to indicate that the CALLER is responsible for
	 * causing the exception.  This works in conjunction with Qcodo's
	 * error handling/reporting, so that the correct file/line-number is
	 * displayed to the user.
	 *
	 * So for example, for a class that contains the method GetItemAtIndex($intIndex),
	 * it is conceivable that the caller could call GetItemAtIndex(15), where 15 does not exist.
	 * GetItemAtIndex would then thrown an IndexOutOfRangeException (which extends CallerException).
	 * If the CallerException is not caught, then the Exception will be reported to the user.  The CALLER
	 * (the script who CALLED GetItemAtIndex) would have that line highlighted as being responsible
	 * for calling the error.
	 *
	 * The PHP default for exeception reporting would normally say that the "throw Exception" line in GetItemAtIndex
	 * is responsible for throwing the exception.  While this is technically true, in reality, it was the line that
	 * CALLED GetItemAtIndex which is responsible.  In short, this allows for much cleaner exception reporting.
	 *
	 * On a more in-depth note, in general, suppose a method OuterMethod takes in parameters, and ends up passing those
	 * paremeters into ANOTHER method InnerMethod which could throw a CallerException.  OuterMethod is responsible
	 * for catching and rethrowing the caller exception.  And when this is done, IncrementOffset() MUST be called on
	 * the exception object, to indicate that OuterMethod's CALLER is responsible for the exception.
	 *
	 * So the code snippet to call InnerMethod by OuterMethod should look like:
	 *	function OuterMethod($mixValue) {
	 *		try {
	 *			InnerMethod($mixValue);
	 *		} catch (CallerException $objExc) {
	 *			$objExc->IncrementOffset();
	 *			throw $objExc;
	 *		}
	 *		// Do Other Stuff
	 *	}
	 * Again, this will assure the user that the line of code responsible for the excpetion is properly being reported
	 * by the Qcodo error reporting/handler.
	 */
	class QCallerException extends Exception {
		private $intOffset;
		private $strTraceArray;
		
		public function setMessage($strMessage) {
			$this->message = $strMessage;
		}

		/**
		 * The constructor of CallerExceptions.  Takes in a message string
		 * as well as an optional Offset parameter (defaults to 1).
		 * The Offset specificies how many calls up the call stack is responsible
		 * for the exception.  By definition, when a CallerException is called,
		 * at the very least the Caller of the most immediate function, which is
		 * 1 up the call stack, is responsible.  So therefore, by default, intOffset
		 * is set to 1.
		 * 
		 * It is rare for intOffset to be set to an integer other than 1.
		 *
		 * Normally, the Offset would be altered by calls to IncrementOffset
		 * at every step the CallerException is caught/rethrown up the call stack.
		 * @param string $strMessage the Message of the exception
		 * @param integer $intOffset the optional Offset value (currently defaulted to 1)
		 * @return CallerException the new exception
		 */
		public function __construct($strMessage, $intOffset = 1) {
			parent::__construct($strMessage);
			$this->intOffset = $intOffset;
			$this->strTraceArray = debug_backtrace();

			$this->file = $this->strTraceArray[$this->intOffset]['file'];
			$this->line = $this->strTraceArray[$this->intOffset]['line'];
		}

		public function IncrementOffset() {
			$this->intOffset++;
			$this->file = $this->strTraceArray[$this->intOffset]['file'];
			$this->line = $this->strTraceArray[$this->intOffset]['line'];
		}

		public function DecrementOffset() {
			$this->intOffset--;
			$this->file = $this->strTraceArray[$this->intOffset]['file'];
			$this->line = $this->strTraceArray[$this->intOffset]['line'];
		}

		public function __get($strName) {
			if ($strName == "Offset")
				return $this->intOffset;
			else if ($strName == "BackTrace"); {
				$objTraceArray = debug_backtrace();
				return (var_export($objTraceArray, true));
			}
		}
	}

	
	class QUndefinedPrimaryKeyException extends QCallerException {
		public function __construct($strMessage) {
			parent::__construct($strMessage, 2);
		}
	}

	class QIndexOutOfRangeException extends QCallerException {
		public function __construct($intIndex, $strMessage) {
			if ($strMessage)
				$strMessage = ": " . $strMessage;
			parent::__construct(sprintf("Index (%s) is out of range%s", $intIndex, $strMessage), 2);
		}
	}

	class QUndefinedPropertyException extends QCallerException {
		public function __construct($strType, $strClass, $strProperty) {
			parent::__construct(sprintf("Undefined %s property or variable in '%s' class: %s", $strType, $strClass, $strProperty), 2);
		}
	}
	
	class QOptimisticLockingException extends QCallerException {
		public function __construct($strClass) {
			parent::__construct(sprintf('Optimistic Locking constraint when trying to update %s object.  To update anyway, call ->Save() with $blnForceUpdate set to true', $strClass, 2));
		}
	}
?>