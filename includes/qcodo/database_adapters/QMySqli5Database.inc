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

	require(__INCLUDES__ . 'qcodo/database_adapters/QMySqliDatabase.inc');

	// New MySQL 5 constanst not yet in PHP (as of PHP 5.1.2)
	if (!defined('MYSQLI_TYPE_NEWDECIMAL'))
		define('MYSQLI_TYPE_NEWDECIMAL', 246);
	if (!defined('MYSQLI_TYPE_BIT'))
		define('MYSQLI_TYPE_BIT', 16);

	class QMySqli5Database extends QMySqliDatabase {
		public function GetTables() {
			// Use the MySQL5 Information Schema to get a list of all the tables in this database
			// (excluding views, etc.)
			$strDatabaseName = QApplication::$ConnectionStringArray[$this->intDatabaseIndex]['database'];

			$objResult = $this->Query("
				SELECT
					table_name
				FROM
					information_schema.tables
				WHERE
					table_type <> 'VIEW' AND
					table_schema = '$strDatabaseName';
			");

			$strToReturn = array();
			while ($strRowArray = $objResult->FetchRow())
				array_push($strToReturn, $strRowArray[0]);
			return $strToReturn;
		}

		public function Query($strQuery) {
			// Log Query (for Profiling, if applicable)
			$this->LogQuery($strQuery);

			// Perform the Query
			$objResult = $this->objMySqli->query($strQuery);
			if ($this->objMySqli->error)
				throw new QMySqliDatabaseException($this->objMySqli->error, $this->objMySqli->errno, $strQuery);

			// Return the Result
			$objMySqliDatabaseResult = new QMySqli5DatabaseResult($objResult, $this);
			return $objMySqliDatabaseResult;
		}
	}

	class QMySqli5DatabaseResult extends QMySqliDatabaseResult {
		public function FetchFields() {
			$objArrayToReturn = array();
			while ($objField = $this->objMySqliResult->fetch_field())
				array_push($objArrayToReturn, new QMySqli5DatabaseField($objField, $this->objDb));
			return $objArrayToReturn;
		}

		public function FetchField() {
			if ($objField = $this->objMySqliResult->fetch_field())
				return new QMySqli5DatabaseField($objField, $this->objDb);
		}
	}

	class QMySqli5DatabaseField extends QMySqliDatabaseField {
		protected function SetFieldType($intMySqlFieldType) {
			switch ($intMySqlFieldType) {
				case MYSQLI_TYPE_NEWDECIMAL:
					$this->strType = QDatabaseFieldType::Float;
					break;

				case MYSQLI_TYPE_BIT:
					$this->strType = QDatabaseFieldType::Bit;
					break;

				case MYSQLI_TYPE_TINY:
					// With MySQL 5, boolean and bit columns are now stored as BIT
					// Allowing TINYINT to just be regular integers now
					$this->strType = QDatabaseFieldType::Integer;
					break;

				default:
					parent::SetFieldType($intMySqlFieldType);
			}
		}
	}
?>