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

	require(__INCLUDES__ . 'qcodo/codegen/QColumn.inc');
	require(__INCLUDES__ . 'qcodo/codegen/QIndex.inc');
	require(__INCLUDES__ . 'qcodo/codegen/QManyToManyReference.inc');
	require(__INCLUDES__ . 'qcodo/codegen/QReference.inc');
	require(__INCLUDES__ . 'qcodo/codegen/QReverseReference.inc');
	require(__INCLUDES__ . 'qcodo/codegen/QTable.inc');
	require(__INCLUDES__ . 'qcodo/codegen/QTypeTable.inc');

	require(__INCLUDES__ . 'qcodo/codegen/QConvertNotationBase.inc');
	require(__INCLUDES__ .'codegen/QConvertNotation.inc');

	/**
	 * This is the CodeGen class which performs the code generation
	 * for both the Object-Relational Model (e.g. Data Objects) as well as
	 * the draft Forms, which make up simple HTML/PHP scripts to perform
	 * basic CRUD functionality on each object.
	 */
	abstract class QCodeGenBase extends QBaseClass {
		// Objects
		protected $objTableArray;
		protected $objTypeTableArray;
		protected $strAssociationTableNameArray;
		protected $objDb;

		protected $intDatabaseIndex;
		
		// Settings-related Variable
		protected $strSettingArray;
		
		// Class Name Suffix/Prefix
		protected $strClassPrefix;
		protected $strClassSuffix;
		
		// Template Escape markers
		protected $strTemplateEscapeBegin;
		protected $intTemplateEscapeBeginLength;
		protected $strTemplateEscapeEnd;
		protected $intTemplateEscapeEndLength;

		// Table Suffixes
		protected $strTypeTableSuffix;
		protected $intTypeTableSuffixLength;
		protected $strAssociationTableSuffix;
		protected $intAssociationTableSuffixLength;

		// Table Prefix
		protected $strStripTablePrefix;
		protected $intStripTablePrefixLength;

		// Uniquely Associated Objects
		protected $strAssociatedObjectPrefix;
		protected $strAssociatedObjectSuffix;

		// Application Name
		protected $strApplicationName;

		// Errors and Warnings
		protected $strErrors;

		// Expected Keys in SettingArray
		const SettingKeys = 'DatabaseIndex,ClassPrefix,ClassSuffix,TypeTableSuffix,AssociationTableSuffix,StripTablePrefix,TemplateEscapeBegin,TemplateEscapeEnd,AssociatedObjectPrefix,AssociatedObjectSuffix,ApplicationName';

		// PHP Reserved Words.  They make up:
		// Invalid Type names -- these are reserved words which cannot be Type names in any user type table
		// Invalid Table names -- these are reserved words which cannot be used as any table name
		const PhpReservedWords = 'new, null, break, return, switch, self, case, const, clone, continue, declare, default, echo, else, elseif, empty, exit, eval, if, try, throw, catch, public, private, protected, function, extends, foreach, for, while, do, var, class, static, abstract, isset, unset, implements, interface, instanceof, include, include_once, require, require_once, abstract, and, or, xor, array, list, false, true, global, parent, print, exception';

		// Relative Paths (from application root) to Template and Subtemplate Directories
		const TemplatesPath = '/includes/qcodo/codegen/templates/';
		const SubTemplatesPath = '/includes/qcodo/codegen/subtemplates/';
		const TemplatesPathCustom = '/includes/codegen/templates/';
		const SubTemplatesPathCustom = '/includes/codegen/subtemplates/';

		public function GetTable($strTableName) {
			$strTableName = strtolower($strTableName);
			if (array_key_exists($strTableName, $this->objTableArray))
				return $this->objTableArray[$strTableName];
			throw new QCallerException(sprintf('Table does not exist: %s', $strTableName));
		}

		public function GetColumn($strTableName, $strColumnName) {
			try {
				$objTable = $this->GetTable($strTableName);
			} catch (QCallerException $objExc) {
				$objExc->IncrementOffset();
				throw $objExc;
			}
			$strColumnName = strtolower($strColumnName);
			if (array_key_exists($strColumnName, $objTable->ColumnArray))
				return $objTable->ColumnArray[$strColumnName];
			throw new QCallerException(sprintf('Column does not exist in %s: %s', $strTableName, $strColumnName));
		}

		public function AnalyzeDatabase($strSettingArray) {
			// Reset the Errors and Warnings
			$this->strErrors = '';

			// Enesure Settings is an Array
			if (!is_array($strSettingArray)) {
				$this->strErrors = 'FATAL ERROR: Passed in $strSettingArray is not a valid array.';
				return;
			}

			// Reset the local arrays
			$this->strAssociationTableNameArray = array();
			$this->objTableArray = array();
			$this->objTypeTableArray = array();

			// Set the DatabaseIndex
			if (!array_key_exists('DatabaseIndex', $strSettingArray)) {
				$this->strErrors = 'FATAL ERROR: DatabaseIndex was not set in the passed in $strSettingArray.';
				return;
			}
			$this->intDatabaseIndex = $strSettingArray['DatabaseIndex'];

			// Ensure that at least all necessary Setting keys exist in strSettingArray
			// And copy contents to $this->strSettingArray
			foreach (explode(',', QCodeGen::SettingKeys) as $strKey) {
				if (array_key_exists($strKey, $strSettingArray))
					$this->strSettingArray[$strKey] = $strSettingArray[$strKey];
				else
					$this->strSettingArray[$strKey] = null;
			}


			// Calculate Needed Values
			$this->strTypeTableSuffix = $this->strSettingArray['TypeTableSuffix'];
			$this->intTypeTableSuffixLength = strlen($this->strTypeTableSuffix);
			$this->strAssociationTableSuffix = $this->strSettingArray['AssociationTableSuffix'];
			$this->intAssociationTableSuffixLength = strlen($this->strAssociationTableSuffix);
			
			$this->strClassPrefix = $this->strSettingArray['ClassPrefix'];
			$this->strClassSuffix = $this->strSettingArray['ClassSuffix'];

			$this->strStripTablePrefix = $this->strSettingArray['StripTablePrefix'];
			$this->intStripTablePrefixLength = strlen($this->strSettingArray['StripTablePrefix']);

			// Uniquely Associated Prefix/Suffix
			$this->strAssociatedObjectPrefix = $this->strSettingArray['AssociatedObjectPrefix'];
			$this->strAssociatedObjectSuffix = $this->strSettingArray['AssociatedObjectSuffix'];

			// Ensure we have a TemplateEscapeString
			$this->strTemplateEscapeBegin = $this->strSettingArray['TemplateEscapeBegin'];
			$this->intTemplateEscapeBeginLength = strlen($this->strTemplateEscapeBegin);
			$this->strTemplateEscapeEnd = $this->strSettingArray['TemplateEscapeEnd'];
			$this->intTemplateEscapeEndLength = strlen($this->strTemplateEscapeEnd);
			if ((!$this->strTemplateEscapeBegin) || (!$this->strTemplateEscapeEnd)) {
				$this->strErrors = "FATAL ERROR: No template escape begin/end was defined.";
				return;
			}

			// Application Name
			$this->strApplicationName =  $this->strSettingArray['ApplicationName'];

			// Set aside the Database object
			if (array_key_exists($this->intDatabaseIndex, QApplication::$Database))
				$this->objDb = QApplication::$Database[$this->intDatabaseIndex];

			// Ensure the DB Exists
			if (!$this->objDb) {
				$this->strErrors = 'FATAL ERROR: No database configured at index ' . $this->intDatabaseIndex . '.';
				return;
			}

			// Ensure DB Profiling is DISABLED on this DB
			if ($this->objDb->EnableProfiling) {
				$this->strErrors = 'FATAL ERROR: Code generator cannot analyze the database at index ' . $this->intDatabaseIndex . ' while DB Profiling is enabled.';
				return;
			}

			// Get the list of Tables as a string[]
			$strTableArray = $this->objDb->GetTables();

			
			// ITERATION 1: Simply create the Table and TypeTable Arrays
			if ($strTableArray) foreach ($strTableArray as $strTableName) {
				// Perform different tasks based on whether it's an Association table,
				// a Type table, or just a regular table
				if (($this->intTypeTableSuffixLength) &&
					(strlen($strTableName) > $this->intTypeTableSuffixLength) &&
					(substr($strTableName, strlen($strTableName) - $this->intTypeTableSuffixLength) == $this->strTypeTableSuffix)) {
					// Create a TYPE Table and add it to the array
					$objTypeTable = new QTypeTable($strTableName);
					$this->objTypeTableArray[strtolower($strTableName)] = $objTypeTable;
//					echo "TYPE Table: $strTableName<br />";

				} else if (($this->intAssociationTableSuffixLength) &&
					(strlen($strTableName) > $this->intAssociationTableSuffixLength) &&
					(substr($strTableName, strlen($strTableName) - $this->intAssociationTableSuffixLength) == $this->strAssociationTableSuffix)) {
					// Add this ASSOCIATION Table Name to the array
					$this->strAssociationTableNameArray[strtolower($strTableName)] = $strTableName;
//					echo "ASSN Table: $strTableName<br />";

				} else {
					// Create a Regular Table and add it to the array
					$objTable = new QTable($strTableName);
					$this->objTableArray[strtolower($strTableName)] = $objTable;
//					echo "Table: $strTableName<br />";
				}
			}


			// Analyze All the Type Tables
			if ($this->objTypeTableArray) foreach ($this->objTypeTableArray as $objTypeTable)
				$this->AnalyzeTypeTable($objTypeTable);


			// Analyze All the Regular Tables
			if ($this->objTableArray) foreach ($this->objTableArray as $objTable)
				$this->AnalyzeTable($objTable);

			// Analyze All the Association Tables
			if ($this->strAssociationTableNameArray) foreach ($this->strAssociationTableNameArray as $strAssociationTableName)
				$this->AnalyzeAssociationTable($strAssociationTableName);
		}
		
		protected function ListOfColumnsFromTable(QTable $objTable) {
			$strArray = array();
			$objColumnArray = $objTable->ColumnArray;
			if ($objColumnArray) foreach ($objColumnArray as $objColumn)
				array_push($strArray, $objColumn->Name);
			return implode(', ', $strArray);
		}
		
		protected function GetColumnArray(QTable $objTable, $strColumnNameArray) {
			$objToReturn = array();

			if ($strColumnNameArray) foreach ($strColumnNameArray as $strColumnName) {
				array_push($objToReturn, $objTable->ColumnArray[strtolower($strColumnName)]);
			}
			
			return $objToReturn;
		}

		protected function EvaluateTemplate($strTemplate, $mixArgumentArray) {
			// First remove all \r from the template (for Win/*nix compatibility)
			$strTemplate = str_replace("\r", '', $strTemplate);

			// Get all the arguments and set them locally
			if ($mixArgumentArray) foreach ($mixArgumentArray as $strName=>$mixValue) {
				$$strName = $mixValue;
			}

			// Of course, we also need to locally allow "objCodeGen"
			$objCodeGen = $this;

			// Look for the Escape Begin
			$intPosition = strpos($strTemplate, $this->strTemplateEscapeBegin);
			
			// Get Database Escape Identifiers
			$strEscapeIdentifierBegin = QApplication::$Database[$this->intDatabaseIndex]->EscapeIdentifierBegin;
			$strEscapeIdentifierEnd = QApplication::$Database[$this->intDatabaseIndex]->EscapeIdentifierEnd;

			// Evaluate All Escaped Clauses
			while ($intPosition !== false) {
				$intPositionEnd = strpos($strTemplate, $this->strTemplateEscapeEnd, $intPosition);

				// Get and cleanup the Eval Statement
				$strStatement = substr($strTemplate, $intPosition + $this->intTemplateEscapeBeginLength, 
										$intPositionEnd - $intPosition - $this->intTemplateEscapeEndLength);
				$strStatement = trim($strStatement);

				if (substr($strStatement, 0, 1) == '=') {
					// Remove Trailing ';' if applicable
					if (substr($strStatement, strlen($strStatement) - 1) == ';')
						$strStatement = trim(substr($strStatement, 0, strlen($strStatement) - 1));

					// Remove Head '='
					$strStatement = trim(substr($strStatement, 1));
					
					// Add 'return' eval
					$strStatement = sprintf('return (%s);', $strStatement);
				} else if (substr($strStatement, 0, 1) == '@') {
					// Remove Trailing ';' if applicable
					if (substr($strStatement, strlen($strStatement) - 1) == ';')
						$strStatement = trim(substr($strStatement, 0, strlen($strStatement) - 1));

					// Remove Head '@'
					$strStatement = trim(substr($strStatement, 1));

					// Calculate Template Filename
					$intVariablePosition = strpos($strStatement, '(');
					
					if ($intVariablePosition === false)
						throw new Exception('Invalid include subtemplate Command: ' . $strStatement);
					$strTemplateFile = substr($strStatement, 0, $intVariablePosition);

					$strVariableList = substr($strStatement, $intVariablePosition + 1);
					// Remove trailing ')'
					$strVariableList = trim(substr($strVariableList, 0, strlen($strVariableList) - 1));

					$strVariableArray = explode(',', $strVariableList);

					// Clean Each Variable
					for ($intIndex = 0; $intIndex < count($strVariableArray); $intIndex++) {
						// Trim
						$strVariableArray[$intIndex] = trim($strVariableArray[$intIndex]);
						
						// Remove trailing and head "'"
						$strVariableArray[$intIndex] = substr($strVariableArray[$intIndex], 1, strlen($strVariableArray[$intIndex]) - 2);
						
						// Trim Again
						$strVariableArray[$intIndex] = trim($strVariableArray[$intIndex]);
					}
					
					// Ensure each variable exists!
					foreach ($strVariableArray as $strVariable)
						if(!isset($$strVariable))
							throw new Exception(sprintf('Invalid Variable %s in include subtemplate command: %s', $strVariable, $strStatement));
							
					// Ensure the subtelmplate exists (first check in the CUSTOM, and then check in the GENERAL
					$strTemplateFileName = $strTemplateFile;
					$strTemplateFile = sprintf('%s%s%s%s.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPathCustom, $strTemplateFileName);
					if (!file_exists($strTemplateFile)) {
						$strTemplateFile = sprintf('%s%s%s%s.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPath, $strTemplateFileName);
						if (!file_exists($strTemplateFile))
							throw new Exception(sprintf('Subtemplate %s does not exist in include subtemplate command: %s', $strTemplateFile, $strStatement));
					}

					// Setup the ArgumentArray for this subtemplate
					$mixTemplateArgumentArray = array();
					foreach ($strVariableArray as $strVariable)
						$mixTemplateArgumentArray[$strVariable] = $$strVariable;

					// Get the Evaluated Template!
					$strEvaledStatement = $this->EvaluateTemplate(file_get_contents($strTemplateFile), $mixTemplateArgumentArray);
					
					// Set Statement to NULL so that the method knows to that the statement we're replacing
					// has already been eval'ed
					$strStatement = null;
				}

				if (substr($strStatement, 0, 1) == '-') {
					// Backup a number of characters
					$intPosition = $intPosition - strlen($strStatement);
					$strStatement = '';
					
					
				// Check if we're starting an open-ended statemen
				} else if (substr($strStatement, strlen($strStatement) - 1) == '{') {
					// We ARE in an open-ended statement

					// SubTemplate is the contents of this open-ended template
					$strSubTemplate = substr($strTemplate, $intPositionEnd + $this->intTemplateEscapeEndLength);

					// Parse through the rest of the template, and pull the correct SubTemplate,
					// Keeping in account nested open-ended statements
					$intLevel = 1;

					$intSubPosition = strpos($strSubTemplate, $this->strTemplateEscapeBegin);
					while (($intLevel > 0) && ($intSubPosition !== false)) {
						$intSubPositionEnd = strpos($strSubTemplate, $this->strTemplateEscapeEnd, $intSubPosition);
						$strFragment = substr($strSubTemplate, $intSubPosition + $this->intTemplateEscapeEndLength,
							$intSubPositionEnd - $intSubPosition - $this->intTemplateEscapeEndLength);
						$strFragment = trim($strFragment);
						
						$strFragmentLastCharacter = substr($strFragment, strlen($strFragment) - 1);

						if ($strFragmentLastCharacter == '{') {
							$intLevel++;
						} else if ($strFragmentLastCharacter == '}') {
							$intLevel--;
						}

						if ($intLevel)
							$intSubPosition = strpos($strSubTemplate, $this->strTemplateEscapeBegin, $intSubPositionEnd);
					}
					if ($intLevel != 0)
						throw new Exception("Improperly Terminated OpenEnded Command following; $strStatement");

					$strSubTemplate = substr($strSubTemplate, 0, $intSubPosition);

					// Remove First Carriage Return (if applicable)
					$intCrPosition = strpos($strSubTemplate, "\n");
					if ($intCrPosition !== false) {
						$strFragment = substr($strSubTemplate, 0, $intCrPosition + 1);
						if (trim($strFragment) == '') {
							// Nothing exists before the first CR
							// Go ahead and chop it off
							$strSubTemplate = substr($strSubTemplate, $intCrPosition + 1);
						}
					}

					// Remove blank space after the last carriage return (if applicable)
					$intCrPosition = strrpos($strSubTemplate, "\n");
					if ($intCrPosition !== false) {
						$strFragment = substr($strSubTemplate, $intCrPosition + 1);
						if (trim($strFragment) == '') {
							// Nothing exists after the last CR
							// Go ahead and chop it off
							$strSubTemplate = substr($strSubTemplate, 0, $intCrPosition + 1);
						}
					}
					
					// Figure out the Command and calculate SubTemplate
					$strCommand = substr($strStatement, 0, strpos($strStatement, ' '));
					switch ($strCommand) {
						case 'foreach':
							$strFullStatement = $strStatement;

							// Remove leading 'foreach' and trailing '{'
							$strStatement = substr($strStatement, strlen('foreach'));
							$strStatement = substr($strStatement, 0, strlen($strStatement) - 1);
							$strStatement = trim($strStatement);
							
							// Ensure that we've got a "(" and a ")"
							if ((QString::FirstCharacter($strStatement) != '(') ||
								(QString::LastCharacter($strStatement) != ')'))
								throw new Exception("Improperly Formatted foreach: $strFullStatement");
							$strStatement = trim(substr($strStatement, 1, strlen($strStatement) - 2));
							
							// Pull out the two sides of the "as" clause
							$strStatement = explode(' as ', $strStatement);
							if (count($strStatement) != 2)
								throw new Exception("Improperly Formatted foreach: $strFullStatement");
							
							$objArray = eval(sprintf('return %s;', trim($strStatement[0])));
							$strSingleObjectName = trim($strStatement[1]);
							$strNameKeyPair = explode('=>', $strSingleObjectName);

							if (count($strNameKeyPair) == 2) {
								$strSingleObjectKey = trim($strNameKeyPair[0]);
								$strSingleObjectValue = trim($strNameKeyPair[1]);
								
								// Remove leading '$'
								$strSingleObjectKey = substr($strSingleObjectKey, 1);
								$strSingleObjectValue = substr($strSingleObjectValue, 1);

								// Iterate to setup strStatement
								$strStatement = '';
								if ($objArray) foreach ($objArray as $$strSingleObjectKey => $$strSingleObjectValue) {
									$mixArgumentArray[$strSingleObjectKey] = $$strSingleObjectKey;
									$mixArgumentArray[$strSingleObjectValue] = $$strSingleObjectValue;
									
									$strStatement .= $this->EvaluateTemplate($strSubTemplate, $mixArgumentArray);
								}
							} else {
								// Remove leading '$'
								$strSingleObjectName = substr($strSingleObjectName, 1);

								// Iterate to setup strStatement
								$strStatement = '';
								if ($objArray) foreach ($objArray as $$strSingleObjectName) {
									$mixArgumentArray[$strSingleObjectName] = $$strSingleObjectName;
									
									$strStatement .= $this->EvaluateTemplate($strSubTemplate, $mixArgumentArray);
								}
							}
							
							break;
							
						case 'if':
							$strFullStatement = $strStatement;

							// Remove leading 'if' and trailing '{'
							$strStatement = substr($strStatement, strlen('if'));
							$strStatement = substr($strStatement, 0, strlen($strStatement) - 1);
							$strStatement = trim($strStatement);
							
							
							if (eval(sprintf('return (%s);', $strStatement))) {
								$strStatement = $this->EvaluateTemplate($strSubTemplate, $mixArgumentArray);
							} else
								$strStatement = '';
							
							break;
						default:
							throw new Exception("Invalid OpenEnded Command: $strStatement");
					}
					
					// Reclculate intPositionEnd
					$intPositionEnd = $intPositionEnd + $this->intTemplateEscapeEndLength + $intSubPositionEnd;
					
					// If nothing but whitespace between $intPositionEnd and the next CR, then remove the CR
					$intCrPosition = strpos($strTemplate, "\n", $intPositionEnd + $this->intTemplateEscapeEndLength);
					if ($intCrPosition !== false) {
						$strFragment = substr($strTemplate, $intPositionEnd + $this->intTemplateEscapeEndLength, $intCrPosition - ($intPositionEnd + $this->intTemplateEscapeEndLength));
						if (trim($strFragment == '')) {
							// Nothing exists after the escapeend and the next CR
							// Go ahead and chop it off
							$intPositionEnd = $intCrPosition - $this->intTemplateEscapeEndLength + 1;
						}
					} else {
						$strFragment = substr($strTemplate, $intPositionEnd + $this->intTemplateEscapeEndLength);
						if (trim($strFragment == '')) {
							// Nothing exists after the escapeend and the end
							// Go ahead and chop it off
							$intPositionEnd = strlen($strTemplate);
						}
					}

					
					
					// Recalcualte intPosition
					// If nothing but whitespace between $intPosition and the previous CR, then remove the Whitespace (keep the CR)
					$strFragment = substr($strTemplate, 0, $intPosition);
					$intCrPosition = strrpos($strFragment, "\n");

					
					if ($intCrPosition !== false) {
						$intLfLength = 1;
					} else {
						$intLfLength = 0;
						$intCrPosition = 0;
					}

					// Inlcude the previous "\r" if applicable
					if (($intCrPosition > 1) && (substr($strTemplate, $intCrPosition - 1, 1) == "\r")) {
						$intCrLength = 1;
						$intCrPosition--;
					} else
						$intCrLength = 0;
					$strFragment = substr($strTemplate, $intCrPosition, $intPosition - $intCrPosition);
					
					if (trim($strFragment) == '') {
						// Nothing exists before the escapebegin and the previous CR
						// Go ahead and chop it off (but not the CR or CR/LF)
						$intPosition = $intCrPosition + $intLfLength + $intCrLength;
					}
				} else {
					if (is_null($strStatement))
						$strStatement = $strEvaledStatement;
					else
						// Perform the Eval
						$strStatement = eval($strStatement);
				}

				// Do the Replace
				$strTemplate = substr($strTemplate, 0, $intPosition) . $strStatement . substr($strTemplate, $intPositionEnd + $this->intTemplateEscapeEndLength);

				// GO to the next Escape Marker (if applicable)
				$intPosition = strpos($strTemplate, $this->strTemplateEscapeBegin);
			}
			return $strTemplate;
		}
		
		public function GenerateTable(QTable $objTable, $strTemplateFileName = null) {
			// Make sure both our Template and TemplateCustom paths are valid
			$strTemplatePath = sprintf('%s%s%s', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPath);
			if (!is_dir($strTemplatePath))
				throw new Exception(sprintf('QCodeGen::TemplatesPath does not appear to be a valid directory:\n%s', $strTemplatePath));

			$strTemplatePathCustom = sprintf('%s%s%s', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPathCustom);
			if (!is_dir($strTemplatePathCustom))
				throw new Exception(sprintf('QCodeGen::TemplatesPathCustom does not appear to be a valid directory:\n%s', $strTemplatePathCustom));

			// Create an array of Object templates
			$strTemplateFileArray = array();
			
			// Go through the Custom one first
			$objDirectory = opendir($strTemplatePathCustom);
			while ($strTemplateFile = readdir($objDirectory)) {
				if ((is_null($strTemplateFileName) && 
					(substr($strTemplateFile, 0, strlen('object')) == 'object') &&
					(substr($strTemplateFile, strlen($strTemplateFile) - 4) == '.tpl')) ||
					($strTemplateFileName == $strTemplateFile)) {
					$strTemplate = file_get_contents(sprintf('%s%s%s%s',
						QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPathCustom, $strTemplateFile));
					$strTemplateFileArray[$strTemplateFile] = $strTemplate;
				}
			}
			
			// Go through the regular one next
			$objDirectory = opendir($strTemplatePath);
			while ($strTemplateFile = readdir($objDirectory)) {
				if ((is_null($strTemplateFileName) && 
					(substr($strTemplateFile, 0, strlen('object')) == 'object') &&
					(substr($strTemplateFile, strlen($strTemplateFile) - 4) == '.tpl')) ||
					($strTemplateFileName == $strTemplateFile)) {
					// Only add if it doesn't yet exist in the array
					if (!array_key_exists($strTemplateFile, $strTemplateFileArray)) {
						$strTemplate = file_get_contents(sprintf('%s%s%s%s',
							QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPath, $strTemplateFile));
						$strTemplateFileArray[$strTemplateFile] = $strTemplate;
					}
				}
			}
			
			// Iterate through the TemplateFileArray
			foreach ($strTemplateFileArray as $strTemplateFile => $strTemplate) {
				$strTemplate = $this->EvaluateTemplate($strTemplate, array('objTable'=>$objTable));
	
				// Parse out the first line (which contains path and overwriting information)
				$intPosition = strpos($strTemplate, "\n");
				if ($intPosition === false)
					throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
	
				$strFirstLine = trim(substr($strTemplate, 0, $intPosition));
				$strTemplate = substr($strTemplate, $intPosition + 1);
				
				// Brute Force Analysis of FirstLine
				// Possibly change to a real parser?
				if ((substr($strFirstLine, 0, 1) != '<') || (substr($strFirstLine, strlen($strFirstLine) - 1) != '>'))
					throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
	
				$strFirstLine = trim(substr($strFirstLine, 1, strlen($strFirstLine) - 2));
				
				if (substr($strFirstLine, strlen($strFirstLine) - 1) == '/')
					$strFirstLine = trim(substr($strFirstLine, 0, strlen($strFirstLine) - 1));
				
				while ($strFirstLine) {
					if (substr($strFirstLine, 0, strlen('TargetFilePath="')) == 'TargetFilePath="') {
						$strFirstLine = substr($strFirstLine, strlen('TargetFilePath="'));
						$intPosition = strpos($strFirstLine, '"');
						if ($intPosition === false)
							throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
						$strFilePath = substr($strFirstLine, 0, $intPosition);
						$strFirstLine = trim(substr($strFirstLine, $intPosition + 1));
					} else if (substr($strFirstLine, 0, strlen('OverwriteFlag="')) == 'OverwriteFlag="') {
						$strFirstLine = substr($strFirstLine, strlen('OverwriteFlag="'));
						$intPosition = strpos($strFirstLine, '"');
						if ($intPosition === false)
							throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
						$strOverwriteFlag = substr($strFirstLine, 0, $intPosition);
						$strFirstLine = trim(substr($strFirstLine, $intPosition + 1));
						
						if (strtolower($strOverwriteFlag) == 'true')
							$blnOverwriteFlag = true;
						else if (strtolower($strOverwriteFlag) == 'false')
							$blnOverwriteFlag = false;
						else
							throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
					} else
						throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
				}

				if (is_null($strTemplateFileName)) {
					// Create Directory (if needed)
					// TODO: Make this into a Parameter on the Template, and recursively go up the chain if true
					$strDirectory = dirname($strFilePath);
					if (!is_dir($strDirectory)) {
						mkdir($strDirectory);
						
						// CHMOD to full read/write permissions (applicable only to nonwindows)
						// Need to ignore error handling for this call just in case
						set_error_handler('QcodoHandleError', 0);
						$intCurrentLevel = error_reporting();
						error_reporting(0);
						chmod($strDirectory, 0777);
						error_reporting($intCurrentLevel);
						restore_error_handler();
					}

					// Save to Disk
					if ($blnOverwriteFlag || (!file_exists($strFilePath))) {
						file_put_contents($strFilePath, $strTemplate);
						
						// CHMOD to full read/write permissions (applicable only to nonwindows)
						// Need to ignore error handling for this call just in case
						set_error_handler('QcodoHandleError', 0);
						$intCurrentLevel = error_reporting();
						error_reporting(0);
						chmod($strFilePath, 0666);
						error_reporting($intCurrentLevel);
						restore_error_handler();
					}
				} else
					return $strTemplate;
			}

			return true;
		}

		public function GenerateTypeTable(QTypeTable $objTypeTable) {
			// Make sure both our Template and TemplateCustom paths are valid
			$strTemplatePath = sprintf('%s%s%s', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPath);
			if (!is_dir($strTemplatePath))
				throw new Exception(sprintf('QCodeGen::TemplatesPath does not appear to be a valid directory:\n%s', $strTemplatePath));

			$strTemplatePathCustom = sprintf('%s%s%s', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPathCustom);
			if (!is_dir($strTemplatePathCustom))
				throw new Exception(sprintf('QCodeGen::TemplatesPathCustom does not appear to be a valid directory:\n%s', $strTemplatePathCustom));

			// Create an array of Object templates
			$strTemplateFileArray = array();
			
			// Go through the Custom one first
			$objDirectory = opendir($strTemplatePathCustom);
			while ($strTemplateFile = readdir($objDirectory)) {
				if ((substr($strTemplateFile, 0, strlen('type')) == 'type') &&
					(substr($strTemplateFile, strlen($strTemplateFile) - 4) == '.tpl')) {
					$strTemplate = file_get_contents(sprintf('%s%s%s%s',
						QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPathCustom, $strTemplateFile));
					$strTemplateFileArray[$strTemplateFile] = $strTemplate;
				}
			}

			// Go through the regular one next
			$objDirectory = opendir($strTemplatePath);
			while ($strTemplateFile = readdir($objDirectory)) {
				if ((substr($strTemplateFile, 0, strlen('type')) == 'type') &&
					(substr($strTemplateFile, strlen($strTemplateFile) - 4) == '.tpl')) {
					// Only add if it doesn't yet exist in the array
					if (!array_key_exists($strTemplateFile, $strTemplateFileArray)) {
						$strTemplate = file_get_contents(sprintf('%s%s%s%s',
							QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::TemplatesPath, $strTemplateFile));
						$strTemplateFileArray[$strTemplateFile] = $strTemplate;
					}
				}
			}

			
			// Iterate through the TemplateFileArray
			foreach ($strTemplateFileArray as $strTemplateFile => $strTemplate) {		
				$strTemplate = $this->EvaluateTemplate($strTemplate, array('objTypeTable'=>$objTypeTable));
	
				// Parse out the first line (which contains path and overwriting information)
				$intPosition = strpos($strTemplate, "\n");
				if ($intPosition === false)
					throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
	
				$strFirstLine = trim(substr($strTemplate, 0, $intPosition));
				$strTemplate = substr($strTemplate, $intPosition + 1);
				
				// Brute Force Analysis of FirstLine
				// Possibly change to a real parser?
				if ((substr($strFirstLine, 0, 1) != '<') || (substr($strFirstLine, strlen($strFirstLine) - 1) != '>'))
					throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
	
				$strFirstLine = trim(substr($strFirstLine, 1, strlen($strFirstLine) - 2));
				
				if (substr($strFirstLine, strlen($strFirstLine) - 1) == '/')
					$strFirstLine = trim(substr($strFirstLine, 0, strlen($strFirstLine) - 1));
				
				while ($strFirstLine) {
					if (substr($strFirstLine, 0, strlen('TargetFilePath="')) == 'TargetFilePath="') {
						$strFirstLine = substr($strFirstLine, strlen('TargetFilePath="'));
						$intPosition = strpos($strFirstLine, '"');
						if ($intPosition === false)
							throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
						$strFilePath = substr($strFirstLine, 0, $intPosition);
						$strFirstLine = trim(substr($strFirstLine, $intPosition + 1));
					} else if (substr($strFirstLine, 0, strlen('OverwriteFlag="')) == 'OverwriteFlag="') {
						$strFirstLine = substr($strFirstLine, strlen('OverwriteFlag="'));
						$intPosition = strpos($strFirstLine, '"');
						if ($intPosition === false)
							throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
						$strOverwriteFlag = substr($strFirstLine, 0, $intPosition);
						$strFirstLine = trim(substr($strFirstLine, $intPosition + 1));
						
						if (strtolower($strOverwriteFlag) == 'true')
							$blnOverwriteFlag = true;
						else if (strtolower($strOverwriteFlag) == 'false')
							$blnOverwriteFlag = false;
						else
							throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
					} else
						throw new Exception("Template's first line must be <TargetFilePath=\"string\" OverwriteFlag=\"boolean\">: " . $strTemplateFile);
				}

				// Create Directory (if needed)
				// TODO: Make this into a Parameter on the Template, and recursively go up the chain if true
				$strDirectory = dirname($strFilePath);
				if (!is_dir($strDirectory)) {
					mkdir($strDirectory);

					// CHMOD to full read/write permissions (applicable only to nonwindows)
					// Need to ignore error handling for this call just in case						
					set_error_handler('QcodoHandleError', 0);
					$intCurrentLevel = error_reporting();
					error_reporting(0);
					chmod($strDirectory, 0777);
					error_reporting($intCurrentLevel);
					restore_error_handler();
				}

				// Overwrite 
				if ($blnOverwriteFlag || (!file_exists($strFilePath))) {
					file_put_contents($strFilePath, $strTemplate);

					// CHMOD to full read/write permissions (applicable only to nonwindows)
					// Need to ignore error handling for this call just in case						
					set_error_handler('QcodoHandleError', 0);
					$intCurrentLevel = error_reporting();
					error_reporting(0);
					chmod($strFilePath, 0666);
					error_reporting($intCurrentLevel);
					restore_error_handler();
				}
			}

			return true;
		}

		protected function AnalyzeAssociationTable($strTableName) {
			$objFieldArray = $this->objDb->GetFieldsForTable($strTableName);

			// Association tables must have 2 fields
			if (count($objFieldArray) != 2) {
				$this->strErrors .= sprintf("AssociationTable %s does not have exactly 2 columns.\n",
					$strTableName);
				return;
			}

			if ((!$objFieldArray[0]->NotNull) ||
				(!$objFieldArray[1]->NotNull)) {
				$this->strErrors .= sprintf("AssociationTable %s's two columns must both be not null or a composite Primary Key",
					$strTableName);
				return;
			}
			
			if (((!$objFieldArray[0]->PrimaryKey) &&
				 ($objFieldArray[1]->PrimaryKey)) || 
				(($objFieldArray[0]->PrimaryKey) &&
				 (!$objFieldArray[1]->PrimaryKey))) {
				$this->strErrors .= sprintf("AssociationTable %s only support two-column composite Primary Keys.\n",
					$strTableName);
				return;
			}
			
			$objForeignKeyArray = $this->objDb->GetForeignKeysForTable($strTableName);
			if (count($objForeignKeyArray) != 2) {
				$this->strErrors .= sprintf("AssociationTable %s does not have exactly 2 foreign keys.\n",
					$strTableName);
				return;
			}

			// Setup two new ManyToManyReference objects
			$objManyToManyReferenceArray[0] = new QManyToManyReference();
			$objManyToManyReferenceArray[1] = new QManyToManyReference();

			// Setup GraphPrevixArray (if applicable)
			if ($objForeignKeyArray[0]->ReferenceTableName == $objForeignKeyArray[1]->ReferenceTableName) {
				// We are analyzing a graph association
				$strGraphPrefixArray = $this->CalculateGraphPrefixArray($objForeignKeyArray);
			} else {
				$strGraphPrefixArray = array('', '');
			}

			// Go through each FK and setup each ManyToManyReference object
			for ($intIndex = 0; $intIndex < 2; $intIndex++) {
				$objManyToManyReference = $objManyToManyReferenceArray[$intIndex];

				$objForeignKey = $objForeignKeyArray[$intIndex];
				$objOppositeForeignKey = $objForeignKeyArray[($intIndex == 0) ? 1 : 0];

				// Make sure the FK is a single-column FK
				if (count($objForeignKey->ColumnNameArray) != 1) {
					$this->strErrors .= sprintf("AssoiationTable %s has multi-column foreign keys.\n",
						$strTableName);
					return;
				}

				$objManyToManyReference->KeyName = $objForeignKey->KeyName;
				$objManyToManyReference->Table = $strTableName;
				$objManyToManyReference->Column = $objForeignKey->ColumnNameArray[0];
				$objManyToManyReference->OppositeColumn = $objOppositeForeignKey->ColumnNameArray[0];
				$objManyToManyReference->AssociatedTable = $objOppositeForeignKey->ReferenceTableName;
				
				// Calculate OppositeColumnVariableName
				// Do this by first making a fake column which is the PK column of the AssociatedTable,
				// but who's column name is ManyToManyReference->Column
				$objOppositeColumn = clone($this->objTableArray[strtolower($objManyToManyReference->AssociatedTable)]->PrimaryKeyColumnArray[0]);
				$objOppositeColumn->Name = $objManyToManyReference->OppositeColumn;
				$objManyToManyReference->OppositeVariableName = $this->VariableNameFromColumn($objOppositeColumn);
				$objManyToManyReference->OppositeVariableType = $objOppositeColumn->VariableType;

				$objManyToManyReference->VariableName = $this->ReverseReferenceVariableNameFromTable($objOppositeForeignKey->ReferenceTableName);
				$objManyToManyReference->VariableType = $this->ReverseReferenceVariableTypeFromTable($objOppositeForeignKey->ReferenceTableName);

				$objManyToManyReference->ObjectDescription = $strGraphPrefixArray[$intIndex] . $this->CalculateObjectDescriptionForAssociation($strTableName, $objForeignKey->ReferenceTableName, $objOppositeForeignKey->ReferenceTableName, false);
				$objManyToManyReference->ObjectDescriptionPlural = $strGraphPrefixArray[$intIndex] . $this->CalculateObjectDescriptionForAssociation($strTableName, $objForeignKey->ReferenceTableName, $objOppositeForeignKey->ReferenceTableName, true);

				$objManyToManyReference->OppositeObjectDescription = $strGraphPrefixArray[($intIndex == 0) ? 1 : 0] . $this->CalculateObjectDescriptionForAssociation($strTableName, $objOppositeForeignKey->ReferenceTableName, $objForeignKey->ReferenceTableName, false);
			}


			// Iterate through the list of Columns to create objColumnArray
			$objColumnArray = array();
			foreach ($objFieldArray as $objField) {
				if (($objField->Name != $objManyToManyReferenceArray[0]->Column) &&
					($objField->Name != $objManyToManyReferenceArray[1]->Column)) {
					$objColumn = $this->AnalyzeTableColumn($objField);
					$objColumnArray[strtolower($objColumn->Name)] = $objColumn;
				}
			}
			$objManyToManyReferenceArray[0]->ColumnArray = $objColumnArray;
			$objManyToManyReferenceArray[1]->ColumnArray = $objColumnArray;			
			
			// Push the ManyToManyReference Objects to the tables
			for ($intIndex = 0; $intIndex < 2; $intIndex++) {
				$objManyToManyReference = $objManyToManyReferenceArray[$intIndex];
				$strTableWithReference = $objManyToManyReferenceArray[($intIndex == 0) ? 1 : 0]->AssociatedTable;

				$objArray = $this->objTableArray[strtolower($strTableWithReference)]->ManyToManyReferenceArray;
				array_push($objArray, $objManyToManyReference);
				$this->objTableArray[strtolower($strTableWithReference)]->ManyToManyReferenceArray = $objArray;
			}

		}

		protected function AnalyzeTypeTable(QTypeTable $objTypeTable) {
			// Setup the Array of Reserved Words
			$strReservedWords = explode(',', QCodeGen::PhpReservedWords);
			for ($intIndex = 0; $intIndex < count($strReservedWords); $intIndex++)
				$strReservedWords[$intIndex] = strtolower(trim($strReservedWords[$intIndex]));

			// Setup the Type Table Object
			$strTableName = $objTypeTable->Name;
			$objTypeTable->ClassName = $this->ClassNameFromTableName($strTableName);
			
			// Ensure that there are only 2 fields, an integer PK field (can be named anything) and a unique varchar field
			$objFieldArray = $this->objDb->GetFieldsForTable($strTableName);

			if (count($objFieldArray) != 2) {
				$this->strErrors .= sprintf("TypeTable %s does not have exactly 2 columns.\n",
					$strTableName);
				return;
			}
			
			if (($objFieldArray[0]->Type != QDatabaseFieldType::Integer) ||
				(!$objFieldArray[0]->PrimaryKey)) {
				$this->strErrors .= sprintf("TypeTable %s's first column is not a PK integer.\n",
					$strTableName);
				return;
			}
			
			if (($objFieldArray[1]->Type != QDatabaseFieldType::VarChar) ||
				(!$objFieldArray[1]->Unique)) {
				$this->strErrors .= sprintf("TypeTable %s's second column is not a unique VARCHAR.\n",
					$strTableName);
				return;
			}

			// Get the rows
			$objResult = $this->objDb->Query(sprintf('SELECT * FROM %s', $strTableName));
			$strNameArray = array();
			$strTokenArray = array();
			while ($objRow = $objResult->FetchRow()) {
				$strNameArray[$objRow[0]] = str_replace("'", "\\'", str_replace('\\', '\\\\', $objRow[1]));
				$strTokenArray[$objRow[0]] = $this->TypeTokenFromTypeName($objRow[1]);

				foreach ($strReservedWords as $strReservedWord)
					if (trim(strtolower($strTokenArray[$objRow[0]])) == $strReservedWord) {
						$this->strErrors .= sprintf("Warning: TypeTable %s contains a type name which is a reserved word: %s.  Appended _ to the beginning of it.\r\n",
							$strTableName, $strReservedWord);
						$strTokenArray[$objRow[0]] = '_' . $strTokenArray[$objRow[0]];
					}
				if (strlen($strTokenArray[$objRow[0]]) == 0) {
					$this->strErrors .= sprintf("Warning: TypeTable %s contains an invalid type name: %s\r\n",
						$strTableName, stripslashes($strNameArray[$objRow[0]]));
					return;
				}
			}

			ksort($strNameArray);
			ksort($strTokenArray);

			$objTypeTable->NameArray = $strNameArray;
			$objTypeTable->TokenArray = $strTokenArray;
		}
		
		protected function AnalyzeTable(QTable $objTable) {
			// Setup the Table Object
			$strTableName = $objTable->Name;
			$objTable->ClassName = $this->ClassNameFromTableName($strTableName);
			$objTable->ClassNamePlural = $this->Pluralize($objTable->ClassName);


			// Get the List of Columns
			$objFieldArray = $this->objDb->GetFieldsForTable($strTableName);
	
			// Iterate through the list of Columns to create objColumnArray
			$objColumnArray = array();
			if ($objFieldArray) foreach ($objFieldArray as $objField) {
				$objColumn = $this->AnalyzeTableColumn($objField);
				$objColumnArray[strtolower($objColumn->Name)] = $objColumn;
			}
			$objTable->ColumnArray = $objColumnArray;




			// Get the List of Indexes
			$objTable->IndexArray = $this->objDb->GetIndexesForTable($objTable->Name);
			
			// Create an Index array
			$objIndexArray = array();
			
			// Iterate though each Index that exists in this table, set any Columns's "Index" property
			// to TRUE if they are a single-column index
			if ($objTable->IndexArray) foreach ($objArray = $objTable->IndexArray as $objDatabaseIndex) {
				// Make sure the columns are defined
				if (count ($objDatabaseIndex->ColumnNameArray) == 0)
					$this->strErrors .= sprintf("Index %s in table %s indexes on no columns.\n",
						$objDatabaseIndex->KeyName, $strTableName);
				else {
					// Ensure every column exist in the DbIndex's ColumnNameArray
					$blnFailed = false;
					foreach ($objArray = $objDatabaseIndex->ColumnNameArray as $strColumnName) {
						if (array_key_exists(strtolower($strColumnName), $objTable->ColumnArray) &&
							($objTable->ColumnArray[strtolower($strColumnName)])) {
							// It exists -- do nothing
						} else {
							// Otherwise, add a warning
							$this->strErrors .= sprintf("Index %s in table %s indexes on the column %s, which does not appear to exist.\n",
								$objDatabaseIndex->KeyName, $strTableName, $strColumnName);
							$blnFailed = true;
						}
					}
					
					if (!$blnFailed) {
						// Create the Index Object
						$objIndex = new QIndex();
						$objIndex->KeyName = $objDatabaseIndex->KeyName;
						$objIndex->PrimaryKey = $objDatabaseIndex->PrimaryKey;
						$objIndex->Unique = $objDatabaseIndex->Unique;
						$objIndex->ColumnNameArray = $objDatabaseIndex->ColumnNameArray;
	
						// Add the new index object to the index array
						array_push($objIndexArray, $objIndex);
						
						// Lastly, if it's a single-column index, update the Column in the table to reflect this
						if (count($objDatabaseIndex->ColumnNameArray) == 1) {
							$strColumnName = $objDatabaseIndex->ColumnNameArray[0];
							$objColumn = $objTable->ColumnArray[strtolower($strColumnName)];
							$objColumn->Indexed = true;
						}
					}
				}
			}
			
			// Add the IndexArray to the table
			$objTable->IndexArray = $objIndexArray;

			
			
			
			// Get the List of Foreign Keys
			$objForeignKeys = $this->objDb->GetForeignKeysForTable($objTable->Name);

			// Iterate through each foreign key that exists in this table
			if ($objForeignKeys) foreach ($objForeignKeys as $objForeignKey) {

				// Make sure it's a single-column FK
				if (count($objForeignKey->ColumnNameArray) != 1)
					$this->strErrors .= sprintf("Foreign Key %s in table %s keys on multiple columns.  Multiple-columned FKs are not supported by the code generator.\n",
						$objForeignKey->KeyName, $strTableName);
				else {
					// Make sure the column in the FK definition actually exists in this table
					$strColumnName = $objForeignKey->ColumnNameArray[0];

					if (array_key_exists(strtolower($strColumnName), $objTable->ColumnArray) &&
						($objTable->ColumnArray[strtolower($strColumnName)])) {
							
						// Now, we make sure there is a single-column index for this FK that exists
						$blnFound = false;
						if ($objIndexArray = $objTable->IndexArray) foreach ($objIndexArray as $objIndex) {
							if ((count($objIndex->ColumnNameArray) == 1) &&
								(strtolower($objIndex->ColumnNameArray[0]) == strtolower($strColumnName)))
								$blnFound = true;
						}

						if ($blnFound) {
							// Make sure the table being referenced actually exists
							if ((array_key_exists(strtolower($objForeignKey->ReferenceTableName), $this->objTableArray)) ||
								(array_key_exists(strtolower($objForeignKey->ReferenceTableName), $this->objTypeTableArray))) {
	
								// STEP 1: Create the New Reference
								$objReference = new QReference();
		
								// Retrieve the Column object
								$objColumn = $objTable->ColumnArray[strtolower($strColumnName)];
		
								// Setup Key Name
								$objReference->KeyName = $objForeignKey->KeyName;
		
								$strReferencedTableName = $objForeignKey->ReferenceTableName;
	
								// Setup IsType flag
	//							if (($this->intTypeTableSuffixLength) &&
	//								(strlen($strReferencedTableName) > $this->intTypeTableSuffixLength) &&
	//								(substr($strReferencedTableName, strlen($strReferencedTableName) - $this->intTypeTableSuffixLength) == $this->strTypeTableSuffix)) {
								if (array_key_exists(strtolower($strReferencedTableName), $this->objTypeTableArray)) {
									$objReference->IsType = true;
								} else {
									$objReference->IsType = false;
								}
		
								// Setup Table and Column names
								$objReference->Table = $strReferencedTableName;
								$objReference->Column = $objForeignKey->ReferenceColumnNameArray[0];
		
								// Setup VariableType
								$objReference->VariableType = $this->ClassNameFromTableName($strReferencedTableName);
								
								// Setup PropertyName and VariableName
								$objReference->PropertyName = $this->ReferencePropertyNameFromColumn($objColumn);
								$objReference->VariableName = $this->ReferenceVariableNameFromColumn($objColumn);
								
								// Add this reference to the column
								$objColumn->Reference = $objReference;
								
								
								
								// STEP 2: Setup the REVERSE Reference for Non Type-based References
								if (!$objReference->IsType) {						
									// Retrieve the ReferencedTable object
									$objReferencedTable = $this->objTableArray[strtolower($objReference->Table)];
									$objReverseReference = new QReverseReference();
									$objReverseReference->KeyName = $objReference->KeyName;
									$objReverseReference->Table = $strTableName;
									$objReverseReference->Column = $strColumnName;
									$objReverseReference->NotNull = $objColumn->NotNull;
									$objReverseReference->Unique = $objColumn->Unique;
									$objReverseReference->PropertyName = $this->PropertyNameFromColumn($this->GetColumn($strTableName, $strColumnName));
									
									$objReverseReference->ObjectDescription = $this->CalculateObjectDescription($strTableName, $strColumnName, $strReferencedTableName, false);
									$objReverseReference->ObjectDescriptionPlural = $this->CalculateObjectDescription($strTableName, $strColumnName, $strReferencedTableName, true);
									$objReverseReference->VariableName = $this->ReverseReferenceVariableNameFromTable($objTable->Name);
									$objReverseReference->VariableType = $this->ReverseReferenceVariableTypeFromTable($objTable->Name);
									
									// For Unique ReverseReferences, calculate Associated MemberVariableName and PropertyName
									if ($objColumn->Unique) {
										$objReverseReference->ObjectMemberVariable = $this->CalculateObjectMemberVariable($strTableName, $strColumnName, $strReferencedTableName);
										$objReverseReference->ObjectPropertyName = $this->CalculateObjectPropertyName($strTableName, $strColumnName, $strReferencedTableName);
									}
									
									// Add this ReverseReference to the referenced table's ReverseReferenceArray
									$objArray = $objReferencedTable->ReverseReferenceArray;
									array_push($objArray, $objReverseReference);
									$objReferencedTable->ReverseReferenceArray = $objArray;
								}
							} else {
								$this->strErrors .= sprintf("Foreign Key %s in table %s references a table %s that does not appear to exist.\n",
									$objForeignKey->KeyName, $strTableName, $objForeignKey->ReferenceTableName);
							}
						} else {
							$this->strErrors .= sprintf("Foreign Key %s in table %s, column %s is missing a single-column index for that column.\n",
								$objForeignKey->KeyName, $strTableName, $strColumnName);
						}							
					} else {
						$this->strErrors .= sprintf("Foreign Key %s in table %s indexes on a column that does not appear to exist.\n",
							$objForeignKey->KeyName, $strTableName);
					}
				}
			}

			// Verify: Table Name is valid (alphanumeric + "_" characters only, must not start with a number)
			// and NOT a PHP Reserved Word
			$strMatches = array();
			preg_match("/[a-zA-Z_][a-zA-Z0-9_]*/", $strTableName, $strMatches);
			if (count($strMatches) && ($strMatches[0] == $strTableName) && ($strTableName != '_')) {
				// Setup Reserved Words
				$strReservedWords = explode(',', QCodeGen::PhpReservedWords);
				for ($intIndex = 0; $intIndex < count($strReservedWords); $intIndex++)
					$strReservedWords[$intIndex] = strtolower(trim($strReservedWords[$intIndex]));

				$strTableNameToTest = trim(strtolower($strTableName));
				foreach ($strReservedWords as $strReservedWord)
					if ($strTableNameToTest == $strReservedWord) {
						$this->strErrors .= sprintf("Table '%s' has a table name which is a PHP reserved word.\r\n", $strTableName);
						unset($this->objTableArray[strtolower($strTableName)]);
						return;
					}
			} else {
				$this->strErrors .= sprintf("Table '%s' can only contain characters that are alphanumeric or _, and must not begin with a number.\r\n", $strTableName);
				unset($this->objTableArray[strtolower($strTableName)]);
				return;
			}

			// Verify: Column Names are all valid names
			$objColumnArray = $objTable->ColumnArray;
			foreach ($objColumnArray as $objColumn) {
				$strColumnName = $objColumn->Name;
				$strMatches = array();
				preg_match("/[a-zA-Z_][a-zA-Z0-9_]*/", $strColumnName, $strMatches);
				if (count($strMatches) && ($strMatches[0] == $strColumnName) && ($strColumnName != '_')) {
				} else {
					$this->strErrors .= sprintf("Table '%s' has an invalid column name: '%s'\r\n", $strTableName, $strColumnName);
					unset($this->objTableArray[strtolower($strTableName)]);
					return;
				}
			}

			// Verify: Table has at least one PK
			$blnFoundPk = false;
			$objColumnArray = $objTable->ColumnArray;
			foreach ($objColumnArray as $objColumn) {
				if ($objColumn->PrimaryKey)
					$blnFoundPk = true;
			}
			if (!$blnFoundPk) {
				$this->strErrors .= sprintf("Table %s does not have any defined primary keys.\n", $strTableName);
				unset($this->objTableArray[strtolower($strTableName)]);
				return;
			}
		}

		protected function AnalyzeTableColumn(QDatabaseFieldBase $objField) {
			$objColumn = new QColumn();
			$objColumn->Name = $objField->Name;
			$objColumn->DbType = $objField->Type;
		
			$objColumn->VariableType = $this->VariableTypeFromDbType($objColumn->DbType);
			$objColumn->VariableTypeAsConstant = QType::Constant($objColumn->VariableType);

			$objColumn->Length = $objField->MaxLength;
			
			$objColumn->PrimaryKey = $objField->PrimaryKey;
			$objColumn->NotNull = $objField->NotNull;
			$objColumn->Identity = $objField->Identity;
			$objColumn->Unique = $objField->Unique;
			$objColumn->Timestamp = $objField->Timestamp;

			$objColumn->VariableName = $this->VariableNameFromColumn($objColumn);
			$objColumn->PropertyName = $this->PropertyNameFromColumn($objColumn);

			return $objColumn;
		}

		protected function StripPrefixFromTable($strTableName) {
			// If applicable, strip any StripTablePrefix from the table name
			if ($this->intStripTablePrefixLength &&
				(strlen($strTableName) > $this->intStripTablePrefixLength) &&
				(substr($strTableName, 0, $this->intStripTablePrefixLength - strlen($strTableName)) == $this->strStripTablePrefix))
				return substr($strTableName, $this->intStripTablePrefixLength);	

			return $strTableName;
		}

		///////////////////////
		// COMMONLY OVERRIDDEN CONVERSION FUNCTIONS
		///////////////////////

		protected function ClassNameFromTableName($strTableName) {
			$strTableName = $this->StripPrefixFromTable($strTableName);
			return sprintf('%s%s%s',
				$this->strClassPrefix,
				QConvertNotation::CamelCaseFromUnderscore($strTableName),
				$this->strClassSuffix);
		}

		protected function VariableNameFromColumn(QColumn $objColumn) {
			return QConvertNotation::PrefixFromType($objColumn->VariableType) .
				QConvertNotation::CamelCaseFromUnderscore($objColumn->Name);
		}

		protected function PropertyNameFromColumn(QColumn $objColumn) {
			return QConvertNotation::CamelCaseFromUnderscore($objColumn->Name);
		}
		
		protected function ReferenceColumnNameFromColumn(QColumn $objColumn) {
			$strColumnName = $objColumn->Name;
			$intNameLength = strlen($strColumnName);
			
			// Does the column name for this reference column end in "_id"?
			if (($intNameLength > 3) && (substr($strColumnName, $intNameLength - 3) == "_id")) {
				// It ends in "_id" but we don't want to include the "Id" suffix
				// in the Variable Name.  So remove it.
				$strColumnName = substr($strColumnName, 0, $intNameLength - 3);
			} else {
				// Otherwise, let's add "_object" so that we don't confuse this variable name
				// from the variable that was mapped from the physical database
				// E.g., if it's a numeric FK, and the column is defined as "person INT",
				// there will end up being two variables, one for the Person id integer, and
				// one for the Person object itself.  We'll add Object t o the name of the Person object
				// to make this deliniation.
				$strColumnName = sprintf("%s_object", $strColumnName);
			}
			
			return $strColumnName;
		}

		protected function ReferenceVariableNameFromColumn(QColumn $objColumn) {
			$strColumnName = $this->ReferenceColumnNameFromColumn($objColumn);
			return QConvertNotation::PrefixFromType(QType::Object) .
				QConvertNotation::CamelCaseFromUnderscore($strColumnName);
		}

		protected function ReferencePropertyNameFromColumn(QColumn $objColumn) {
			$strColumnName = $this->ReferenceColumnNameFromColumn($objColumn);
			return QConvertNotation::CamelCaseFromUnderscore($strColumnName);
		}

		protected function VariableNameFromTable($strTableName) {
			$strTableName = $this->StripPrefixFromTable($strTableName);
			return QConvertNotation::PrefixFromType(QType::Object) .
				QConvertNotation::CamelCaseFromUnderscore($strTableName);
		}
		
		protected function ReverseReferenceVariableNameFromTable($strTableName) {
			$strTableName = $this->StripPrefixFromTable($strTableName);
			return $this->VariableNameFromTable($strTableName);
		}

		protected function ReverseReferenceVariableTypeFromTable($strTableName) {
			$strTableName = $this->StripPrefixFromTable($strTableName);
			return $this->ClassNameFromTableName($strTableName);
		}

		protected function ParameterCleanupFromColumn(QColumn $objColumn, $blnIncludeEquality = false) {
			if ($blnIncludeEquality)
				return sprintf('$%s = $objDatabase->SqlVariable($%s, true);',
					$objColumn->VariableName, $objColumn->VariableName);
			else
				return sprintf('$%s = $objDatabase->SqlVariable($%s);',
					$objColumn->VariableName, $objColumn->VariableName);
		}

		// To be used to list the columns as input parameters, or as parameters for sprintf
		protected function ParameterListFromColumnArray($objColumnArray) {
			return $this->ImplodeObjectArray(', ', '$', '', 'VariableName', $objColumnArray);
		}

		protected function ImplodeObjectArray($strGlue, $strPrefix, $strSuffix, $strProperty, $objArrayToImplode) {
			$strArrayToReturn = array();
			if ($objArrayToImplode) foreach ($objArrayToImplode as $objObject) {
				array_push($strArrayToReturn, sprintf('%s%s%s', $strPrefix, $objObject->__get($strProperty), $strSuffix));
			}
			
			return implode($strGlue, $strArrayToReturn);
		}

		protected function TypeTokenFromTypeName($strName) {
			$strToReturn = '';
			for($intIndex = 0; $intIndex < strlen($strName); $intIndex++)
				if (((ord($strName[$intIndex]) >= ord('a')) &&
					 (ord($strName[$intIndex]) <= ord('z'))) ||
					((ord($strName[$intIndex]) >= ord('A')) &&
					 (ord($strName[$intIndex]) <= ord('Z'))) ||
					((ord($strName[$intIndex]) >= ord('0')) &&
					 (ord($strName[$intIndex]) <= ord('9'))) ||
					($strName[$intIndex] == '_'))
					$strToReturn .= $strName[$intIndex];

			if (is_numeric(QString::FirstCharacter($strToReturn)))
				$strToReturn = '_' . $strToReturn;
			return $strToReturn;

			$strMatches = array();
			preg_match_all('/[a-zA-Z_][a-zA-Z0-9_]*/', $strName, $strMatches);
			if (count($strMatches[0]))
				return ($strMatches[0][0]);
			else
				return null;
			$strName = str_replace(' ', '_', $strName);
			$strName = str_replace("\t", '_', $strName);
			$strName = str_replace("\r", '_', $strName);
			$strName = str_replace("\n", '_', $strName);
			$strName = str_replace('-', '_', $strName);
			$strName = str_replace('/', '_', $strName);
			$strName = str_replace('.', '', $strName);
			$strName = str_replace(',', '', $strName);
			$strName = str_replace("'", '', $strName);
			return QConvertNotation::CamelCaseFromUnderscore($strName);
		}

		protected function FormControlVariableNameForColumn(QColumn $objColumn) {
			if ($objColumn->Identity)
				return sprintf('lbl%s', $objColumn->PropertyName);
				
			if ($objColumn->Timestamp)
				return sprintf('lbl%s', $objColumn->PropertyName);

			if ($objColumn->Reference)
				return sprintf('lst%s', $objColumn->Reference->PropertyName);

			switch ($objColumn->VariableType) {
				case QType::Boolean:
					return sprintf('chk%s', $objColumn->PropertyName);
				case QType::DateTime:
					return sprintf('cal%s', $objColumn->PropertyName);
				default:
					return sprintf('txt%s', $objColumn->PropertyName);
			}
		}

		protected function FormControlVariableNameForUniqueReverseReference(QReverseReference $objReverseReference) {
			if ($objReverseReference->Unique) {
				return sprintf("lst%s", $objReverseReference->ObjectDescription);
			} else
				throw new Exception('FormControlVariableNameForUniqueReverseReference requires ReverseReference to be unique');
		}

		protected function FormControlVariableNameForManyToManyReference(QManyToManyReference $objManyToManyReference) {
			return sprintf("lst%s", $objManyToManyReference->ObjectDescriptionPlural);
		}

		protected function FormControlTypeForColumn(QColumn $objColumn) {
			if ($objColumn->Reference)
				return 'QListBox';
			
			switch ($objColumn->VariableType) {
				case QType::Boolean:
					return 'QCheckBox';
				case QType::DateTime:
					return 'QCalendar';
				case QType::Float:
					return 'QFloatTextBox';
				case QType::Integer:
					return 'QIntegerTextBox';
				case QType::String:
					return 'QTextBox';
				default:
					throw new Exception('Unknown type for Column: %s' . $objColumn->VariableType);
			}
		}

		protected function CalculateObjectMemberVariable($strTableName, $strColumnName, $strReferencedTableName) {
			return sprintf('%s%s%s%s',
				QConvertNotation::PrefixFromType(QType::Object),
				$this->strAssociatedObjectPrefix,
				$this->CalculateObjectDescription($strTableName, $strColumnName, $strReferencedTableName, false),
				$this->strAssociatedObjectSuffix);
		}

		protected function CalculateObjectPropertyName($strTableName, $strColumnName, $strReferencedTableName) {
			return sprintf('%s%s%s',
				$this->strAssociatedObjectPrefix,
				$this->CalculateObjectDescription($strTableName, $strColumnName, $strReferencedTableName, false),
				$this->strAssociatedObjectSuffix);
		}

		// TODO: These functions need to be documented heavily with information from "lexical analysis on fk names.txt"
		protected function CalculateObjectDescription($strTableName, $strColumnName, $strReferencedTableName, $blnPluralize) {
			// Strip Prefixes (if applicable)
			$strTableName = $this->StripPrefixFromTable($strTableName);
			$strReferencedTableName = $this->StripPrefixFromTable($strReferencedTableName);

			// Starting Point
			$strToReturn = QConvertNotation::CamelCaseFromUnderscore($strTableName);

			if ($blnPluralize)
				$strToReturn = $this->Pluralize($strToReturn);
				
			if ($strTableName == $strReferencedTableName) {
				// Self-referencing Reference to Describe

				// If Column Name is only the name of the referenced table, or the name of the referenced table with "_id",
				// then the object description is simply based off the table name.
				if (($strColumnName == $strReferencedTableName) ||
					($strColumnName == $strReferencedTableName . '_id'))
					return sprintf('Child%s', $strToReturn);
				
				// Rip out trailing "_id" if applicable
				$intLength = strlen($strColumnName);
				if (($intLength > 3) && (substr($strColumnName, $intLength - 3) == "_id"))
					$strColumnName = substr($strColumnName, 0, $intLength - 3);
	
				// Rip out the referenced table name from the column name
				$strColumnName = str_replace($strReferencedTableName, "", $strColumnName);
				
				// Change any double "_" to single "_"
				$strColumnName = str_replace("__", "_", $strColumnName);
				$strColumnName = str_replace("__", "_", $strColumnName);

				$strColumnName = QConvertNotation::CamelCaseFromUnderscore($strColumnName);

				// Special case for Parent/Child
				if ($strColumnName == 'Parent')
					return sprintf('Child%s', $strToReturn);

				return sprintf("%sAs%s",
					$strToReturn, $strColumnName);

			} else {
				// If Column Name is only the name of the referenced table, or the name of the referenced table with "_id",
				// then the object description is simply based off the table name.
				if (($strColumnName == $strReferencedTableName) ||
					($strColumnName == $strReferencedTableName . '_id'))
					return $strToReturn;

				// Rip out trailing "_id" if applicable
				$intLength = strlen($strColumnName);
				if (($intLength > 3) && (substr($strColumnName, $intLength - 3) == "_id"))
					$strColumnName = substr($strColumnName, 0, $intLength - 3);
	
				// Rip out the referenced table name from the column name
				$strColumnName = str_replace($strReferencedTableName, "", $strColumnName);
				
				// Change any double "_" to single "_"
				$strColumnName = str_replace("__", "_", $strColumnName);
				$strColumnName = str_replace("__", "_", $strColumnName);
				
				return sprintf("%sAs%s",
					$strToReturn,
					QConvertNotation::CamelCaseFromUnderscore($strColumnName));
			}
		}
		
		// this is called for ReverseReference Object Descriptions for association tables (many-to-many)
		protected function CalculateObjectDescriptionForAssociation($strAssociationTableName, $strTableName, $strReferencedTableName, $blnPluralize) {
			// Strip Prefixes (if applicable)
			$strTableName = $this->StripPrefixFromTable($strTableName);
			$strAssociationTableName = $this->StripPrefixFromTable($strAssociationTableName);
			$strReferencedTableName = $this->StripPrefixFromTable($strReferencedTableName);

			// Starting Point
			$strToReturn = QConvertNotation::CamelCaseFromUnderscore($strReferencedTableName);

			if ($blnPluralize)
				$strToReturn = $this->Pluralize($strToReturn);

			// Let's start with strAssociationTableName

			// Rip out trailing "_assn" if applicable
			$strAssociationTableName = str_replace($this->strAssociationTableSuffix, '', $strAssociationTableName);
			
			// Take out strTableName if applicable (both with and without underscores)
			$strAssociationTableName = str_replace($strTableName, '', $strAssociationTableName);
			$strTableName = str_replace('_', '', $strTableName);
			$strAssociationTableName = str_replace($strTableName, '', $strAssociationTableName);
			
			// Take out strReferencedTableName if applicable (both with and without underscores)
			$strAssociationTableName = str_replace($strReferencedTableName, '', $strAssociationTableName);
			$strReferencedTableName = str_replace('_', '', $strReferencedTableName);
			$strAssociationTableName = str_replace($strReferencedTableName, '', $strAssociationTableName);

			// Change any double "__" to single "_"
			$strAssociationTableName = str_replace("__", "_", $strAssociationTableName);
			$strAssociationTableName = str_replace("__", "_", $strAssociationTableName);
			$strAssociationTableName = str_replace("__", "_", $strAssociationTableName);
			
			// If we have nothing left or just a single "_" in AssociationTableName, return "Starting Point"
			if (($strAssociationTableName == "_") || ($strAssociationTableName == ""))
				return sprintf("%s%s%s",
					$this->strAssociatedObjectPrefix,
					$strToReturn,
					$this->strAssociatedObjectSuffix);
			
			// Otherwise, add "As" and the predicate
			return sprintf("%s%sAs%s%s",
				$this->strAssociatedObjectPrefix,
				$strToReturn,
				QConvertNotation::CamelCaseFromUnderscore($strAssociationTableName),
				$this->strAssociatedObjectSuffix);
		}

		// This is called by AnalyzeAssociationTable to calculate the GraphPrefixArray for a self-referencing association table (e.g. directed graph)
		protected function CalculateGraphPrefixArray($objForeignKeyArray) {
			// Analyze Column Names to determine GraphPrefixArray
			if ((strpos(strtolower($objForeignKeyArray[0]->ColumnNameArray[0]), 'parent') !== false) ||
				(strpos(strtolower($objForeignKeyArray[1]->ColumnNameArray[0]), 'child') !== false)) {
				$strGraphPrefixArray[0] = '';
				$strGraphPrefixArray[1] = 'Parent';
			} else if ((strpos(strtolower($objForeignKeyArray[0]->ColumnNameArray[0]), 'child') !== false) ||
						(strpos(strtolower($objForeignKeyArray[1]->ColumnNameArray[0]), 'parent') !== false)) {
				$strGraphPrefixArray[0] = 'Parent';
				$strGraphPrefixArray[1] = '';
			} else {
				// Use Default Prefixing for Graphs
				$strGraphPrefixArray[0] = 'Parent';
				$strGraphPrefixArray[1] = '';
			}

			return $strGraphPrefixArray;
		}

		protected function VariableTypeFromDbType($strDbType) {
			switch ($strDbType) {
				case QDatabaseFieldType::Bit:
					return QType::Boolean;
				case QDatabaseFieldType::Blob:
					return QType::String;
				case QDatabaseFieldType::Char:
					return QType::String;
				case QDatabaseFieldType::Date:
					return QType::DateTime;
				case QDatabaseFieldType::DateTime:
					return QType::DateTime;
				case QDatabaseFieldType::Float:
					return QType::Float;
				case QDatabaseFieldType::Integer:
					return QType::Integer;
				case QDatabaseFieldType::Time:
					return QType::DateTime;
				case QDatabaseFieldType::VarChar:
					return QType::String;
				throw new Exception("Invalid Db Type to Convert: $strDbType");
			}
		}

		protected function Pluralize($strName) {
			// Special Rules go Here
			switch (true) {	
				case (strtolower($strName) == 'play'):
					return $strName . 's';
			}

			$intLength = strlen($strName);
			if (substr($strName, $intLength - 1) == "y")
				return substr($strName, 0, $intLength - 1) . "ies";
			if (substr($strName, $intLength - 1) == "s")
				return $strName . "es";
			if (substr($strName, $intLength - 1) == "x")
				return $strName . "es";
			if (substr($strName, $intLength - 1) == "z")
				return $strName . "zes";
			if (substr($strName, $intLength - 2) == "sh")
				return $strName . "es";
			if (substr($strName, $intLength - 2) == "ch")
				return $strName . "es";

			return $strName . "s";
		}


		////////////////////
		// Public Overriders
		////////////////////

		/**
		 * Override method to perform a property "Get"
		 * This will get the value of $strName
		 *
		 * @param string strName Name of the property to get
		 * @return mixed
		 */
		public function __get($strName) {
			switch ($strName) {
				case 'Errors':
					return $this->strErrors;
				case 'TableArray':
					return $this->objTableArray;
				case 'TypeTableArray':
					return $this->objTypeTableArray;
				case 'DatabaseIndex':
					return $this->intDatabaseIndex;
				case 'ApplicationName':
					return $this->strApplicationName;
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
?>