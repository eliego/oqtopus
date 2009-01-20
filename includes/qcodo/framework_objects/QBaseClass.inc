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
	 * This is the Base Class for ALL classes in the system.  It provides
	 * proper error handling of property getters and setters.  It also
	 * provides the OverrideAttribute functionality.
	 */
	abstract class QBaseClass {
		/**
		 * Override method to perform a property "Get"
		 * This will get the value of $strName
		 * All inhereted objects that call __get() should always fall through
		 * to calling parent::__get() in a try/catch statement catching
		 * for CallerExceptions.
		 *
		 * @param string $strName Name of the property to get
		 * @return mixed the returned property
		 */
		public function __get($strName) {
			$objReflection = new ReflectionClass($this);
			throw new QUndefinedPropertyException("GET", $objReflection->getName(), $strName);
		}

		/**
		 * Override method to perform a property "Set"
		 * This will set the property $strName to be $mixValue
		 * All inhereted objects that call __set() should always fall through
		 * to calling parent::__set() in a try/catch statement catching
		 * for CallerExceptions.
		 *
		 * @param string $strName Name of the property to set
		 * @param string $mixValue New value of the property
		 * @return mixed the property that was set
		 */
		public function __set($strName, $mixValue) {
			$objReflection = new ReflectionClass($this);
			throw new QUndefinedPropertyException("SET", $objReflection->getName(), $strName);
		}

		/**
		 * This allows you to set any properties, given by a name-value pair list
		 * in strOverrideArray.
		 *
		 * The strOverrideArray needs to be an array of strings, where each
		 * string is in the format Property=Value.  OverrideAttributes() will basically call
		 * $this->Property = Value for each string element in the array.
		 *
		 * Value can be surrounded by quotes... but this is optional.
		 *
		 * @param string[] $strOverrideArray the array of name-value pair strings of properties/attributes to override
		 * @return void
		 */
		final public function OverrideAttributes($strOverrideArray) {
			// Iterate through the OverrideAttribute Array
			if ($strOverrideArray) foreach ($strOverrideArray as $strOverrideItem) {
				// Extract the Key and Value for this OverrideAttribute
				$intPosition = strpos($strOverrideItem, "=");
				if ($intPosition === false)
					throw new QCallerException(sprintf("Improperly formatted OverrideAttribute: %s", $strOverrideItem));
				$strKey = substr($strOverrideItem, 0, $intPosition);
				$strValue = substr($strOverrideItem, $intPosition + 1);

				// Ensure that the Value is properly formatted (unquoted, single-quoted, or double-quoted)
				if (substr($strValue, 0, 1) == "'") {
					if (substr($strValue, strlen($strValue) - 1) != "'")
						throw new QCallerException(sprintf("Improperly formatted OverrideAttribute: %s", $strOverrideItem));
					$strValue = substr($strValue, 1, strlen($strValue) - 2);
				} else if (substr($strValue, 0, 1) == '"') {
					if (substr($strValue, strlen($strValue) - 1) != '"')
						throw new QCallerException(sprintf("Improperly formatted OverrideAttribute: %s", $strOverrideItem));
					$strValue = substr($strValue, 1, strlen($strValue) - 2);
				}
	
				// Apply the override
				try {
					$this->__set($strKey, $strValue);
				} catch (QCallerException $objExc) {
					$objExc->IncrementOffset();
					throw $objExc;
				}
			}
		}
	}
?>