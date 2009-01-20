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
	 * Every database adapter must implement the following 5 classes (all which are abstract):
	 * * DatabaseBase
	 * * DatabaseFieldBase
	 * * DatabaseResultBase
	 * * DatabaseRowBase
	 * * DatabaseExceptionBase
	 *
	 * This Database library also has the following classes already defined, and 
	 * Database adapters are assumed to use them internally:
	 * * DatabaseIndex
	 * * DatabaseForeignKey
	 * * DatabaseFieldType (which is an abstract class that solely contains constants)
	 */

	abstract class QDatabaseBase extends QBaseClass {
		// Protected Member Variables for ALL Database Adapters
		protected $intDatabaseIndex;
		protected $blnEnableProfiling;
		protected $strProfileArray;
		protected $strScriptPath;
		protected $blnCaseSensitiveScript;

		protected $strEscapeIdentifierBegin = '"';
		protected $strEscapeIdentifierEnd = '"';

		// Abstract Methods that ALL Database Adapters MUST implement
		abstract public function __construct($intDatabaseIndex);
		abstract public function Query($strQuery);
		abstract public function NonQuery($strNonQuery);

		abstract public function GetTables();
		abstract public function InsertId($strTableName = null, $strColumnName = null);

		abstract public function GetIndexesForTable($strTableName);
		abstract public function GetForeignKeysForTable($strTableName);

		abstract public function TransactionBegin();
		abstract public function TransactionCommit();
		abstract public function TransactionRollBack();

		abstract public function SqlLimitVariablePrefix($strLimitInfo);
		abstract public function SqlLimitVariableSuffix($strLimitInfo);
		abstract public function SqlSortByVariable($strSortByInfo);

		abstract public function Close();

		public function __get($strName) {
			switch ($strName) {
				case 'EscapeIdentifierBegin':
					return $this->strEscapeIdentifierBegin;
				case 'EscapeIdentifierEnd':
					return $this->strEscapeIdentifierEnd;
				case 'EnableProfiling':
					return $this->blnEnableProfiling;
				case 'AffectedRows':
					return -1;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		/**
		 * This will go through the ScriptPath (if applicable)
		 * to parse for virtual Foreign Keys (that are not programmitcally defined in the database)
		 * for a given table.
		 *
		 * If no ScriptPath is defined, this method will simply exit.
		 *
		 * @param string $strTableName Name of the table to pull foreign keys for
		 * @param DatabaseForeignKeyBase[] Array of currently found DB FK objects which will be appended to
		 * @return DatabaseForeignKeyBase[] Array of DB FK objects that were parsed out
		 */
		protected function ForeignKeysFromScriptPath($strTableName, $objForeignKeyArray) {
			if (!$this->strScriptPath)
				// No Script Path Defined -- Simply Return
				return $objForeignKeyArray;

			// Parse Script to Get Keys
			if (!file_exists($this->strScriptPath))
				throw new Exception(sprintf('SCRIPT_PATH does not exist: %s', $this->strScriptPath));

			$strScript = trim(file_get_contents($this->strScriptPath));

//			if (!$this->blnCaseSensitiveScript)
			$strScript = strtolower($strScript);

			$strLines = explode("\n", $strScript);
			if ($strLines) foreach ($strLines as $strLine) {
				$strLine = trim($strLine);

				// Make sure this is not a BLANK line
				// Make sure that this isn't a COMMENT line (denoted by //, --, or #)
				if (($strLine) && 
					(strlen($strLine) > 2) &&
					(substr($strLine, 0, 2) != '//') &&
					(substr($strLine, 0, 2) != '--') &&
					(substr($strLine, 0, 1) != '#')) {
					$strTokens = explode('=>', $strLine);
					if (count($strTokens) != 2)
						throw new Exception(sprintf('Invalid reference defined in SCRIPT_PATH (%s): %s', $this->strScriptPath, $strLine));

					$strSourceTokens = explode('.', $strTokens[0]);
					$strDestinationTokens = explode('.', $strTokens[1]);

					if (count($strSourceTokens) != 2)
						throw new Exception(sprintf('Invalid reference defined in SCRIPT_PATH (%s): %s', $this->strScriptPath, $strLine));
					if (count($strDestinationTokens) != 2)
						throw new Exception(sprintf('Invalid reference defined in SCRIPT_PATH (%s): %s', $this->strScriptPath, $strLine));

					$strFkName = 'FromScript'; // Default
					$strColumnName = trim($strSourceTokens[1]);
					$strReferenceTableName = trim($strDestinationTokens[0]);
					$strReferenceColumnName = trim($strDestinationTokens[1]);

					// This particular line is a FK for the table
					if (trim($strSourceTokens[0]) == strtolower($strTableName)) {
						// Ensure that the column exists
						$objFieldArray = $this->GetFieldsForTable($strTableName);
						$blnFound = false;
						if ($objFieldArray) foreach ($objFieldArray as $objField) {
							if (strtolower($objField->Name) == strtolower($strColumnName))
								$blnFound = true;
						}
						if (!$blnFound)
							throw new Exception(sprintf('Invalid reference (column %s.%s does not exist) defined in SCRIPT_PATH (%s): %s', $strTableName, $strColumnName, $this->strScriptPath, $strLine));
	
						// Ensure that the other column exists
						try {
							$objFieldArray = $this->GetFieldsForTable($strReferenceTableName);
						} catch (Exception $objExc) {
							throw new Exception(sprintf('Invalid reference defined in SCRIPT_PATH (%s): %s: %s', $this->strScriptPath, $strLine, $objExc->getMessage()));
						}
	
						$blnFound = false;
						if ($objFieldArray) foreach ($objFieldArray as $objField) {
							if ($objField->Name == $strReferenceColumnName)
								$blnFound = true;
						}
						if (!$blnFound)
							throw new Exception(sprintf('Invalid reference (column %s.%s does not exist) defined in SCRIPT_PATH (%s): %s', $strReferenceTableName, $strReferenceColumnName, $this->strScriptPath, $strLine));
						
						$objForeignKey = new QDatabaseForeignKey('FromScript', array(trim($strSourceTokens[1])), trim($strDestinationTokens[0]), array(trim($strDestinationTokens[1])));
						array_push($objForeignKeyArray, $objForeignKey);
					}
				}
			}

			return $objForeignKeyArray;
		}

		/**
		 * Sets up the base-level configuration properties for this database,
		 * namely DB Profiling, Database Index, and the SCript Path for Foreign Keys.
		 *
		 * @param integer $intDatabaseIndex
		 * @return void
		 */
		protected function ConfigureBaseProperties($intDatabaseIndex) {
			// Setup DatabaseIndex
			$this->intDatabaseIndex = $intDatabaseIndex;

			// Setup Profiling Array (if applicable)
			$this->blnEnableProfiling = QType::Cast(QApplication::$ConnectionStringArray[$intDatabaseIndex]['profiling'], QType::Boolean);
			if ($this->blnEnableProfiling)
				$this->strProfileArray = array();

			// Setup Script Path for Foreign Keys (if applicable)
			$this->strScriptPath = QApplication::$ConnectionStringArray[$intDatabaseIndex]['scriptpath'];
			$this->blnCaseSensitiveScript = QType::Cast(QApplication::$ConnectionStringArray[$intDatabaseIndex]['casesensitivescript'], QType::Boolean);
		}

		/**
		 * Allows for the enabling of DB profiling while in middle of the script
		 *
		 * @return void
		 */
		public function EnableProfiling() {
			// Only perform profiling initialization if profiling is not yet enabled
			if (!$this->blnEnableProfiling) {
				$this->blnEnableProfiling = true;
				$this->strProfileArray = array();
			}
		}

		/**
		 * If EnableProfiling is on, then log the query to the profile array
		 *
		 * @param string $strQuery
		 * @return void
		 */
		protected function LogQuery($strQuery) {
			if ($this->blnEnableProfiling) {
				// Dereference-ize Backtrace Information
				$objDebugBacktrace = debug_backtrace();
				$objDebugBacktrace = unserialize(serialize($objDebugBacktrace));

				// Push it onto the profiling information array
				array_push($this->strProfileArray, $objDebugBacktrace);
				array_push($this->strProfileArray, $strQuery);
			}
		}

		/**
		 * Properly escapes $mixData to be used as a SQL query parameter.
		 * If IncludeEquality is set (usually not), then include an equality operator.
		 * So for most data, it would just be "=".  But, for example,
		 * if $mixData is NULL, then most RDBMS's require the use of "IS".
		 *
		 * @param mixed $mixData
		 * @param boolean $blnIncludeEquality whether or not to include an equality operator
		 * @return string the properly formatted SQL variable
		 */
		public function SqlVariable($mixData, $blnIncludeEquality = false) {
			// Are we SqlVariabling a BOOLEAN value?
			if (is_bool($mixData)) {
				// Yes
				if ($blnIncludeEquality) {
					// We must include the inequality

					// Check against NULL, True then False
					if (is_null($mixData))
						return 'IS NULL';
					else if ($mixData)
						return '!= 0';
					else
						return '= 0';
				} else {
					// Check against NULL, True then False
					if (is_null($mixData))
						return 'NULL';
					else if ($mixData)
						return '1';
					else
						return '0';
				}
			}

			// Check for Equality Inclusion
			if ($blnIncludeEquality) {
				if (is_null($mixData))
					$strToReturn = 'IS ';
				else
					$strToReturn = '= ';
			} else
				$strToReturn = '';

			// Check for NULL Value
			if (is_null($mixData))
				return $strToReturn . 'NULL';

			// Check for NUMERIC Value
			if (is_integer($mixData) || is_float($mixData))
				return $strToReturn . sprintf('%s', $mixData);

			// Check for DATE Value
			if ($mixData instanceof QDateTime)
				return $strToReturn . sprintf("'%s'", $mixData->__toString(QDateTime::FormatIso));

			// Assume it's some kind of string value
			return $strToReturn . sprintf("'%s'", mysql_escape_string($mixData));
		}

		/**
		 * Displays the OutputProfiling results, plus a link which will popup the details of the profiling.
		 *
		 * @return void
		 */
		public function OutputProfiling() {
			if ($this->blnEnableProfiling) {
				printf(sprintf('<form method="post" target="_blank" name="frmDbProfile%s" id="frmDbProfile%s" action="%s%s/includes/qcodo/database_profiling/profile.php">',
					$this->intDatabaseIndex, $this->intDatabaseIndex, DOCROOT_VIRTUAL_DIRECTORY, DOCROOT_SUBFOLDER));
				printf('<input type="hidden" name="strProfileData" value="%s" />',
					base64_encode(serialize($this->strProfileArray)));
				printf('<input type="hidden" name="intDatabaseIndex" value="%s" />', $this->intDatabaseIndex);
				printf('<input type="hidden" name="strReferrer" value="%s" /></form>', htmlentities(QApplication::$RequestUri, ENT_COMPAT, QApplication::$EncodingType));

				printf('<b>PROFILING INFORMATION FOR DATABASE CONNECTION #%s</b>: %s queries performed.  Please <a href="javascript:document.frmDbProfile%s.submit()">click here to view profiling detail</a><br />',
					$this->intDatabaseIndex, round(count($this->strProfileArray) / 2), $this->intDatabaseIndex);

			} else {
				print('Profiling was not enabled for this database connection (#' . $this->intDatabaseIndex . ').  To enable, ensure that ENABLE_PROFILING is set to TRUE.');
			}
		}
	}

	abstract class QDatabaseFieldBase extends QBaseClass {
		protected $strName;
		protected $strOriginalName;
		protected $strTable;
		protected $strOriginalTable;
		protected $strDefault;
		protected $intMaxLength;

		// Bool
		protected $blnIdentity;
		protected $blnNotNull;
		protected $blnPrimaryKey;
		protected $blnUnique;
		protected $blnTimestamp;

		protected $strType;

		public function __get($strName) {
			switch ($strName) {
				case "Name":
					return $this->strName;
				case "OriginalName":
					return $this->strOriginalName;
				case "Table":
					return $this->strTable;
				case "OriginalTable":
					return $this->strOriginalTable;
				case "Default":
					return $this->strDefault;
				case "MaxLength":
					return $this->intMaxLength;
				case "Identity":
					return $this->blnIdentity;
				case "NotNull":
					return $this->blnNotNull;
				case "PrimaryKey":
					return $this->blnPrimaryKey;
				case "Unique":
					return $this->blnUnique;
				case "Timestamp":
					return $this->blnTimestamp;
				case "Type":
					return $this->strType;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}
	}

	abstract class QDatabaseResultBase extends QBaseClass {
		abstract public function FetchArray();
		abstract public function FetchRow();
		abstract public function FetchField();
		abstract public function FetchFields();
		abstract public function CountRows();
		abstract public function CountFields();

		abstract public function GetNextRow();
		abstract public function GetRows();

		abstract public function Close();
	}
	
	abstract class QDatabaseRowBase extends QBaseClass {
		abstract public function GetColumn($strColumnName, $strColumnType = null);
		abstract public function ColumnExists($strColumnName);
		abstract public function GetColumnNameArray();
	}

	abstract class QDatabaseExceptionBase extends QCallerException {
		protected $intErrorNumber;
		protected $strQuery;

		public function __get($strName) {
			switch ($strName) {
				case "ErrorNumber":
					return $this->intErrorNumber;
				case "Query";
					return $this->strQuery;
				default:
					return parent::__get($strName);
			}
		}
	}

	class QDatabaseForeignKey extends QBaseClass {
		protected $strKeyName;
		protected $strColumnNameArray;
		protected $strReferenceTableName;
		protected $strReferenceColumnNameArray;

		public function __construct($strKeyName, $strColumnNameArray, $strReferenceTableName, $strReferenceColumnNameArray) {
			$this->strKeyName = $strKeyName;
			$this->strColumnNameArray = $strColumnNameArray;
			$this->strReferenceTableName = $strReferenceTableName;
			$this->strReferenceColumnNameArray = $strReferenceColumnNameArray;
		}

		public function __get($strName) {
			switch ($strName) {
				case "KeyName":
					return $this->strKeyName;
				case "ColumnNameArray":
					return $this->strColumnNameArray;
				case "ReferenceTableName":
					return $this->strReferenceTableName;
				case "ReferenceColumnNameArray":
					return $this->strReferenceColumnNameArray;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}
	}

	class QDatabaseIndex extends QBaseClass {
		protected $strKeyName;
		protected $blnPrimaryKey;
		protected $blnUnique;
		protected $strColumnNameArray;
		
		public function __construct($strKeyName, $blnPrimaryKey, $blnUnique, $strColumnNameArray) {
			$this->strKeyName = $strKeyName;
			$this->blnPrimaryKey = $blnPrimaryKey;
			$this->blnUnique = $blnUnique;
			$this->strColumnNameArray = $strColumnNameArray;
		}
		
		public function __get($strName) {
			switch ($strName) {
				case "KeyName":
					return $this->strKeyName;
				case "PrimaryKey":
					return $this->blnPrimaryKey;
				case "Unique":
					return $this->blnUnique;
				case "ColumnNameArray":
					return $this->strColumnNameArray;
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}
	}

	abstract class QDatabaseFieldType {
		const Blob = "Blob";
		const VarChar = "VarChar";
		const Char = "Char";
		const Integer = "Integer";
		const DateTime = "DateTime";
		const Date = "Date";
		const Time = "Time";
		const Float = "Float";
		const Bit = "Bit";
	}
?>