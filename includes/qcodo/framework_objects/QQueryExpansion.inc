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
	 * Utility object used by the Code Generator and the generated data objects
	 * to assist with Early Binding of referenced objects.
	 * 
	 * It is rare for this to be used manually.
	 */
	class QQueryExpansion extends QBaseClass {
		protected $strSelectArray;
		protected $strFromArray;
		protected $strWhereArray;

		public function __construct($strClassName = null, $strParentAlias = null, $objExpansionMap = null) {
			$this->strSelectArray = array();
			$this->strFromArray = array();
			$this->strWhereArray = array();
			
			if ($strClassName) {
				try {
					call_user_func(array($strClassName, 'ExpandQuery'), $strParentAlias, null, $objExpansionMap, $this);
				} catch (QCallerException $objExc) {
					$objExc->IncrementOffset();
					$objExc->IncrementOffset();
					$objExc->IncrementOffset();
					throw $objExc;
				}
			}
		}

		public function AddSelectItem($strItem) {
			array_push($this->strSelectArray, $strItem);
		}

		public function AddFromItem($strItem) {
			array_push($this->strFromArray, $strItem);
		}

		public function AddWhereItem($strItem) {
			array_push($this->strWhereArray, $strItem);
		}

		public function GetSelectSql($strPrefix = ",\n					", $strGlue = ",\n					") {
			if (count($this->strSelectArray) > 0) {
				return $strPrefix . implode($strGlue, $this->strSelectArray);
			} else {
				return '';
			}
		}

		public function GetFromSql($strPrefix = '', $strGlue = "\n					") {
			if (count($this->strFromArray) > 0) {
				return $strPrefix . implode($strGlue, $this->strFromArray);
			} else {
				return '';
			}
		}

		public function GetWhereSql($strPrefix, $strGlue) {
			if (count($this->strWhereArray) > 0) {
				return $strPrefix . implode($strGlue, $this->strWhereArray);
			} else {
				return '';
			}
		}
	}
?>