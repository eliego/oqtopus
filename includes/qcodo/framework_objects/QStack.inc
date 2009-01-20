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
	 * An DataType class for the Stack data type.
	 */
	class QStack extends QBaseClass {
		private $objArray = array();

		public function Push($mixValue) {
			$this->objArray[count($this->objArray)] = $mixValue;
			return $mixValue;
		}

		public function PushFirst($mixValue) {
			if ($this->Size() > 0) {
				$this->objArray = array_reverse($this->objArray);
				$this->objArray[count($this->objArray)] = $mixValue;
				$this->objArray = array_reverse($this->objArray);
			} else
				$this->objArray[0] = $mixValue;

			return $mixValue;
		}

		public function Pop() {
			if (!$this->IsEmpty())
				return array_pop($this->objArray);
			else
				throw new QCallerException("Cannot pop off of an empty Stack");
		}

		public function PopFirst() {
			if (!$this->IsEmpty()) {
				$this->objArray = array_reverse($this->objArray);
				$mixToReturn = array_pop($this->objArray);
				$this->objArray = array_reverse($this->objArray);
				return $mixToReturn;
			} else
				throw new QCallerException("Cannot pop off of an empty Stack");
		}

		public function Peek($intIndex) {
			if (array_key_exists($intIndex, $this->objArray))
				return $this->objArray[$intIndex];
			else
				throw new QIndexOutOfRangeException("Index on stack does not exist");
		}

		public function PeekLast() {
			if ($intCount = count($this->objArray))
				return $this->objArray[$intCount - 1];
			else
				throw new QIndexOutOfRangeException("Stack is empty");
		}

		public function IsEmpty() {
			return (count($this->objArray) == 0);
		}

		public function Size() {
			return count($this->objArray);
		}

		public function ConvertToArray() {
			return $this->objArray;
		}
	}
?>