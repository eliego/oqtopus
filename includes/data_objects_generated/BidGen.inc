<?php
	/**
	 * The abstract BidGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the Bid subclass which
	 * extends this BidGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the Bid class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class BidGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a Bid from PK Info
		 * @param integer $intId
		 * @return Bid
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Bid::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`login_id`,
					`ad_id`,
					`amount`,
					`status`,
					`deadline`,
					`answer_timestamp`,
					`contacted_buyer`,
					`publication_date`
				FROM
					`bid`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbRow($objDbResult->GetNextRow());
		}



		/**
		 * Internally called method to assist with SQL Query options/preferences for single row loaders.
		 * Any Load (single row) method can use this method to get the Database object.
		 * @param string $objDatabase reference to the Database object to be queried
		 */
		protected static function QueryHelper(&$objDatabase) {
			// Get the Database
			$objDatabase = QApplication::$Database[1];
		}



		/**
		 * Internally called method to assist with SQL Query options/preferences for array loaders.
		 * Any LoadAll or LoadArray method can use this method to setup SQL Query Clauses that deal
		 * with OrderBy, Limit, and Object Expansion.  Strings that contain SQL Query Clauses are
		 * passed in by reference.
		 * @param string $strOrderBy reference to the Order By as passed in to the LoadArray method
		 * @param string $strLimit the Limit as passed in to the LoadArray method
		 * @param string $strLimitPrefix reference to the Limit Prefix to be used in the SQL
		 * @param string $strLimitSuffix reference to the Limit Suffix to be used in the SQL
		 * @param string $strExpandSelect reference to the Expand Select to be used in the SQL
		 * @param string $strExpandFrom reference to the Expand From to be used in the SQL
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @param string $objDatabase reference to the Database object to be queried
		 */
		protected static function ArrayQueryHelper(&$strOrderBy, $strLimit, &$strLimitPrefix, &$strLimitSuffix, &$strExpandSelect, &$strExpandFrom, $objExpansionMap, &$objDatabase) {
			// Get the Database
			$objDatabase = QApplication::$Database[1];

			// Setup OrderBy and Limit Information (if applicable)
			$strOrderBy = $objDatabase->SqlSortByVariable($strOrderBy);
			$strLimitPrefix = $objDatabase->SqlLimitVariablePrefix($strLimit);
			$strLimitSuffix = $objDatabase->SqlLimitVariableSuffix($strLimit);

			// Setup QueryExpansion (if applicable)
			if ($objExpansionMap) {
				$objQueryExpansion = new QQueryExpansion('Bid', 'bid', $objExpansionMap);
				$strExpandSelect = $objQueryExpansion->GetSelectSql();
				$strExpandFrom = $objQueryExpansion->GetFromSql();
			} else {
				$strExpandSelect = null;
				$strExpandFrom = null;
			}
		}



		/**
		 * Internally called method to assist with early binding of objects
		 * on load methods.  Can only early-bind references that this class owns in the database.
		 * @param string $strParentAlias the alias of the parent (if any)
		 * @param string $strAlias the alias of this object
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @param QueryExpansion an already instantiated QueryExpansion object (used as a utility object to assist with object expansion)
		 */
		public static function ExpandQuery($strParentAlias, $strAlias, $objExpansionMap, QQueryExpansion $objQueryExpansion) {
			if ($strAlias) {
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `bid` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`login_id` AS `%s__%s__login_id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`ad_id` AS `%s__%s__ad_id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`amount` AS `%s__%s__amount`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`status` AS `%s__%s__status`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`deadline` AS `%s__%s__deadline`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`answer_timestamp` AS `%s__%s__answer_timestamp`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`contacted_buyer` AS `%s__%s__contacted_buyer`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`publication_date` AS `%s__%s__publication_date`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$strParentAlias = $strParentAlias . '__' . $strAlias;
			}

			if (is_array($objExpansionMap))
				foreach ($objExpansionMap as $strKey=>$objValue) {
					switch ($strKey) {
						case 'login_id':
							try {
								Login::ExpandQuery($strParentAlias, $strKey, $objValue, $objQueryExpansion);
								break;
							} catch (QCallerException $objExc) {
								$objExc->IncrementOffset();
								throw $objExc;
							}
						case 'ad_id':
							try {
								Ad::ExpandQuery($strParentAlias, $strKey, $objValue, $objQueryExpansion);
								break;
							} catch (QCallerException $objExc) {
								$objExc->IncrementOffset();
								throw $objExc;
							}
						default:
							throw new QCallerException(sprintf('Unknown Object to Expand in %s: %s', $strParentAlias, $strKey));
					}
				}
		}



		/**
		 * Load all Bids
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Bid[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`bid`.`id` AS `id`,
					`bid`.`login_id` AS `login_id`,
					`bid`.`ad_id` AS `ad_id`,
					`bid`.`amount` AS `amount`,
					`bid`.`status` AS `status`,
					`bid`.`deadline` AS `deadline`,
					`bid`.`answer_timestamp` AS `answer_timestamp`,
					`bid`.`contacted_buyer` AS `contacted_buyer`,
					`bid`.`publication_date` AS `publication_date`
					%s
				FROM
					`bid` AS `bid`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all Bids
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			Bid::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`bid`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a Bid from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this Bid::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return Bid
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the Bid object
			$objToReturn = new Bid();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->intLoginId = $objDbRow->GetColumn($strAliasPrefix . 'login_id', 'Integer');
			$objToReturn->intAdId = $objDbRow->GetColumn($strAliasPrefix . 'ad_id', 'Integer');
			$objToReturn->intAmount = $objDbRow->GetColumn($strAliasPrefix . 'amount', 'Integer');
			$objToReturn->strStatus = $objDbRow->GetColumn($strAliasPrefix . 'status', 'VarChar');
			$objToReturn->dttDeadline = $objDbRow->GetColumn($strAliasPrefix . 'deadline', 'DateTime');
			$objToReturn->dttAnswerTimestamp = $objDbRow->GetColumn($strAliasPrefix . 'answer_timestamp', 'DateTime');
			$objToReturn->intContactedBuyer = $objDbRow->GetColumn($strAliasPrefix . 'contacted_buyer', 'Integer');
			$objToReturn->dttPublicationDate = $objDbRow->GetColumn($strAliasPrefix . 'publication_date', 'DateTime');

			// Instantiate Virtual Attributes
			foreach ($objDbRow->GetColumnNameArray() as $strColumnName => $mixValue) {
				$strVirtualPrefix = $strAliasPrefix . '__';
				$strVirtualPrefixLength = strlen($strVirtualPrefix);
				if (substr($strColumnName, 0, $strVirtualPrefixLength) == $strVirtualPrefix)
					$objToReturn->__strVirtualAttributeArray[substr($strColumnName, $strVirtualPrefixLength)] = $mixValue;
			}

			// Prepare to Check for Early Binding
			if (!$strAliasPrefix)
				$strAliasPrefix = 'bid__';

			// Check for Login Early Binding
			if (!is_null($objDbRow->GetColumn($strAliasPrefix . 'login_id__id')))
				$objToReturn->objLogin = Login::InstantiateDbRow($objDbRow, $strAliasPrefix . 'login_id__');

			// Check for Ad Early Binding
			if (!is_null($objDbRow->GetColumn($strAliasPrefix . 'ad_id__id')))
				$objToReturn->objAd = Ad::InstantiateDbRow($objDbRow, $strAliasPrefix . 'ad_id__');

			
			return $objToReturn;
		}


		/**
		 * Lookup a VirtualAttribute value (if applicable).  Returns NULL if none found.
		 * @param string $strName
		 * @return string
		*/
		public function GetVirtualAttribute($strName) {
			if (array_key_exists($strName, $this->__strVirtualAttributeArray))
				return $this->__strVirtualAttributeArray[$strName];
			return null;
		}


		/**
		 * Instantiate an array of Bids from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return Bid[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, Bid::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load an array of Bid objects,
		 * by LoginId Index(es)
		 * @param integer $intLoginId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Bid[]
		*/
		public static function LoadArrayByLoginId($intLoginId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`bid`.`id` AS `id`,
					`bid`.`login_id` AS `login_id`,
					`bid`.`ad_id` AS `ad_id`,
					`bid`.`amount` AS `amount`,
					`bid`.`status` AS `status`,
					`bid`.`deadline` AS `deadline`,
					`bid`.`answer_timestamp` AS `answer_timestamp`,
					`bid`.`contacted_buyer` AS `contacted_buyer`,
					`bid`.`publication_date` AS `publication_date`
					%s
				FROM
					`bid` AS `bid`
					%s
				WHERE
					`bid`.`login_id` %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intLoginId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Bids
		 * by LoginId Index(es)
		 * @param integer $intLoginId
		 * @return int
		*/
		public static function CountByLoginId($intLoginId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Bid::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`bid`
				WHERE
					`login_id` %s', $intLoginId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}
			
		/**
		 * Load an array of Bid objects,
		 * by AdId Index(es)
		 * @param integer $intAdId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Bid[]
		*/
		public static function LoadArrayByAdId($intAdId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intAdId = $objDatabase->SqlVariable($intAdId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`bid`.`id` AS `id`,
					`bid`.`login_id` AS `login_id`,
					`bid`.`ad_id` AS `ad_id`,
					`bid`.`amount` AS `amount`,
					`bid`.`status` AS `status`,
					`bid`.`deadline` AS `deadline`,
					`bid`.`answer_timestamp` AS `answer_timestamp`,
					`bid`.`contacted_buyer` AS `contacted_buyer`,
					`bid`.`publication_date` AS `publication_date`
					%s
				FROM
					`bid` AS `bid`
					%s
				WHERE
					`bid`.`ad_id` %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intAdId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Bids
		 * by AdId Index(es)
		 * @param integer $intAdId
		 * @return int
		*/
		public static function CountByAdId($intAdId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Bid::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intAdId = $objDatabase->SqlVariable($intAdId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`bid`
				WHERE
					`ad_id` %s', $intAdId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this Bid
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Bid::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `bid` (
							`login_id`,
							`ad_id`,
							`amount`,
							`status`,
							`deadline`,
							`answer_timestamp`,
							`contacted_buyer`,
							`publication_date`
						) VALUES (
							' . $objDatabase->SqlVariable($this->intLoginId) . ',
							' . $objDatabase->SqlVariable($this->intAdId) . ',
							' . $objDatabase->SqlVariable($this->intAmount) . ',
							' . $objDatabase->SqlVariable($this->strStatus) . ',
							' . $objDatabase->SqlVariable($this->dttDeadline) . ',
							' . $objDatabase->SqlVariable($this->dttAnswerTimestamp) . ',
							' . $objDatabase->SqlVariable($this->intContactedBuyer) . ',
							' . $objDatabase->SqlVariable($this->dttPublicationDate) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('bid', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`bid`
						SET
							`login_id` = ' . $objDatabase->SqlVariable($this->intLoginId) . ',
							`ad_id` = ' . $objDatabase->SqlVariable($this->intAdId) . ',
							`amount` = ' . $objDatabase->SqlVariable($this->intAmount) . ',
							`status` = ' . $objDatabase->SqlVariable($this->strStatus) . ',
							`deadline` = ' . $objDatabase->SqlVariable($this->dttDeadline) . ',
							`answer_timestamp` = ' . $objDatabase->SqlVariable($this->dttAnswerTimestamp) . ',
							`contacted_buyer` = ' . $objDatabase->SqlVariable($this->intContactedBuyer) . ',
							`publication_date` = ' . $objDatabase->SqlVariable($this->dttPublicationDate) . '
						WHERE
							`id` = ' . $objDatabase->SqlVariable($this->intId) . '
					');
				}

			} catch (QCallerException $objExc) {
				$objExc->IncrementOffset();
				throw $objExc;
			}

			// Update __blnRestored
			$this->__blnRestored = true;

			// Return 
			return $mixToReturn;
		}

				/**
		 * Delete this Bid
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this Bid with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			Bid::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`bid`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all Bids
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			Bid::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`bid`');
		}

		/**
		 * Truncate bid table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			Bid::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `bid`');
		}





		////////////////////
		// PUBLIC OVERRIDERS
		////////////////////

				/**
		 * Override method to perform a property "Get"
		 * This will get the value of $strName
		 *
		 * @param string $strName Name of the property to get
		 * @return mixed
		 */
		public function __get($strName) {
			switch ($strName) {
				///////////////////
				// Member Variables
				///////////////////
				case 'Id':
					/**
					 * Gets the value for intId (Read-Only PK)
					 * @return integer
					 */
					return $this->intId;

				case 'LoginId':
					/**
					 * Gets the value for intLoginId (Not Null)
					 * @return integer
					 */
					return $this->intLoginId;

				case 'AdId':
					/**
					 * Gets the value for intAdId (Not Null)
					 * @return integer
					 */
					return $this->intAdId;

				case 'Amount':
					/**
					 * Gets the value for intAmount (Not Null)
					 * @return integer
					 */
					return $this->intAmount;

				case 'Status':
					/**
					 * Gets the value for strStatus (Not Null)
					 * @return string
					 */
					return $this->strStatus;

				case 'Deadline':
					/**
					 * Gets the value for dttDeadline 
					 * @return QDateTime
					 */
					return $this->dttDeadline;

				case 'AnswerTimestamp':
					/**
					 * Gets the value for dttAnswerTimestamp 
					 * @return QDateTime
					 */
					return $this->dttAnswerTimestamp;

				case 'ContactedBuyer':
					/**
					 * Gets the value for intContactedBuyer (Not Null)
					 * @return integer
					 */
					return $this->intContactedBuyer;

				case 'PublicationDate':
					/**
					 * Gets the value for dttPublicationDate 
					 * @return QDateTime
					 */
					return $this->dttPublicationDate;


				///////////////////
				// Member Objects
				///////////////////
				case 'Login':
					/**
					 * Gets the value for the Login object referenced by intLoginId (Not Null)
					 * @return Login
					 */
					try {
						if ((!$this->objLogin) && (!is_null($this->intLoginId)))
							$this->objLogin = Login::Load($this->intLoginId);
						return $this->objLogin;
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Ad':
					/**
					 * Gets the value for the Ad object referenced by intAdId (Not Null)
					 * @return Ad
					 */
					try {
						if ((!$this->objAd) && (!is_null($this->intAdId)))
							$this->objAd = Ad::Load($this->intAdId);
						return $this->objAd;
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}


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
		 * Override method to perform a property "Set"
		 * This will set the property $strName to be $mixValue
		 *
		 * @param string $strName Name of the property to set
		 * @param string $mixValue New value of the property
		 * @return mixed
		 */
		public function __set($strName, $mixValue) {
			switch ($strName) {
				///////////////////
				// Member Variables
				///////////////////
				case 'LoginId':
					/**
					 * Sets the value for intLoginId (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						$this->objLogin = null;
						return ($this->intLoginId = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'AdId':
					/**
					 * Sets the value for intAdId (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						$this->objAd = null;
						return ($this->intAdId = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Amount':
					/**
					 * Sets the value for intAmount (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intAmount = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Status':
					/**
					 * Sets the value for strStatus (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strStatus = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Deadline':
					/**
					 * Sets the value for dttDeadline 
					 * @param QDateTime $mixValue
					 * @return QDateTime
					 */
					try {
						return ($this->dttDeadline = QType::Cast($mixValue, QType::DateTime));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'AnswerTimestamp':
					/**
					 * Sets the value for dttAnswerTimestamp 
					 * @param QDateTime $mixValue
					 * @return QDateTime
					 */
					try {
						return ($this->dttAnswerTimestamp = QType::Cast($mixValue, QType::DateTime));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'ContactedBuyer':
					/**
					 * Sets the value for intContactedBuyer (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intContactedBuyer = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'PublicationDate':
					/**
					 * Sets the value for dttPublicationDate 
					 * @param QDateTime $mixValue
					 * @return QDateTime
					 */
					try {
						return ($this->dttPublicationDate = QType::Cast($mixValue, QType::DateTime));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}


				///////////////////
				// Member Objects
				///////////////////
				case 'Login':
					/**
					 * Sets the value for the Login object referenced by intLoginId (Not Null)
					 * @param Login $mixValue
					 * @return Login
					 */
					if (is_null($mixValue)) {
						$this->intLoginId = null;
						$this->objLogin = null;
						return null;
					} else {
						// Make sure $mixValue actually is a Login object
						try {
							$mixValue = QType::Cast($mixValue, 'Login');
						} catch (QInvalidCastException $objExc) {
							$objExc->IncrementOffset();
							throw $objExc;
						} 

						// Make sure $mixValue is a SAVED Login object
						if (is_null($mixValue->Id))
							throw new QCallerException('Unable to set an unsaved Login for this Bid');

						// Update Local Member Variables
						$this->objLogin = $mixValue;
						$this->intLoginId = $mixValue->Id;

						// Return $mixValue
						return $mixValue;
					}
					break;

				case 'Ad':
					/**
					 * Sets the value for the Ad object referenced by intAdId (Not Null)
					 * @param Ad $mixValue
					 * @return Ad
					 */
					if (is_null($mixValue)) {
						$this->intAdId = null;
						$this->objAd = null;
						return null;
					} else {
						// Make sure $mixValue actually is a Ad object
						try {
							$mixValue = QType::Cast($mixValue, 'Ad');
						} catch (QInvalidCastException $objExc) {
							$objExc->IncrementOffset();
							throw $objExc;
						} 

						// Make sure $mixValue is a SAVED Ad object
						if (is_null($mixValue->Id))
							throw new QCallerException('Unable to set an unsaved Ad for this Bid');

						// Update Local Member Variables
						$this->objAd = $mixValue;
						$this->intAdId = $mixValue->Id;

						// Return $mixValue
						return $mixValue;
					}
					break;

				default:
					try {
						return parent::__set($strName, $mixValue);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}





		///////////////////////////////
		// ASSOCIATED OBJECTS
		///////////////////////////////






		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column bid.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column bid.login_id
		 * @var integer intLoginId
		 */
		protected $intLoginId;

		/**
		 * Protected member variable that maps to the database column bid.ad_id
		 * @var integer intAdId
		 */
		protected $intAdId;

		/**
		 * Protected member variable that maps to the database column bid.amount
		 * @var integer intAmount
		 */
		protected $intAmount;

		/**
		 * Protected member variable that maps to the database column bid.status
		 * @var string strStatus
		 */
		protected $strStatus;

		/**
		 * Protected member variable that maps to the database column bid.deadline
		 * @var QDateTime dttDeadline
		 */
		protected $dttDeadline;

		/**
		 * Protected member variable that maps to the database column bid.answer_timestamp
		 * @var QDateTime dttAnswerTimestamp
		 */
		protected $dttAnswerTimestamp;

		/**
		 * Protected member variable that maps to the database column bid.contacted_buyer
		 * @var integer intContactedBuyer
		 */
		protected $intContactedBuyer;

		/**
		 * Protected member variable that maps to the database column bid.publication_date
		 * @var QDateTime dttPublicationDate
		 */
		protected $dttPublicationDate;

		/**
		 * Protected array of virtual attributes for this object (e.g. extra/other calculated and/or non-object bound
		 * columns from the run-time database query result for this object).  Used by InstantiateDbRow and
		 * GetVirtualAttribute.
		 * @var string[] $__strVirtualAttributeArray
		 */
		protected $__strVirtualAttributeArray = array();

		/**
		 * Protected internal member variable that specifies whether or not this object is Restored from the database.
		 * Used by Save() to determine if Save() should perform a db UPDATE or INSERT.
		 * @var bool __blnRestored;
		 */
		protected $__blnRestored;





		///////////////////////////////
		// PROTECTED MEMBER OBJECTS
		///////////////////////////////

		/**
		 * Protected member variable that contains the object pointed by the reference
		 * in the database column bid.login_id.
		 *
		 * NOTE: Always use the Login property getter to correctly retrieve this Login object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var Login objLogin
		 */
		protected $objLogin;

		/**
		 * Protected member variable that contains the object pointed by the reference
		 * in the database column bid.ad_id.
		 *
		 * NOTE: Always use the Ad property getter to correctly retrieve this Ad object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var Ad objAd
		 */
		protected $objAd;





		////////////////////////////////////////
		// COLUMN CONSTANTS for OBJECT EXPANSION
		////////////////////////////////////////
		const ExpandLogin = 'login_id';
		const ExpandAd = 'ad_id';




		////////////////////////////////////////
		// METHODS for WEB SERVICES
		////////////////////////////////////////
		public static function GetSoapComplexTypeXml() {
			$strToReturn = '<complexType name="Bid"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="Login" type="xsd1:Login"/>';
			$strToReturn .= '<element name="Ad" type="xsd1:Ad"/>';
			$strToReturn .= '<element name="Amount" type="xsd:int"/>';
			$strToReturn .= '<element name="Status" type="xsd:string"/>';
			$strToReturn .= '<element name="Deadline" type="xsd:dateTime"/>';
			$strToReturn .= '<element name="AnswerTimestamp" type="xsd:dateTime"/>';
			$strToReturn .= '<element name="ContactedBuyer" type="xsd:int"/>';
			$strToReturn .= '<element name="PublicationDate" type="xsd:dateTime"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('Bid', $strComplexTypeArray)) {
				$strComplexTypeArray['Bid'] = Bid::GetSoapComplexTypeXml();
				Login::AlterSoapComplexTypeArray($strComplexTypeArray);
				Ad::AlterSoapComplexTypeArray($strComplexTypeArray);
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, Bid::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new Bid();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if ((property_exists($objSoapObject, 'Login')) &&
				($objSoapObject->Login))
				$objToReturn->Login = Login::GetObjectFromSoapObject($objSoapObject->Login);
			if ((property_exists($objSoapObject, 'Ad')) &&
				($objSoapObject->Ad))
				$objToReturn->Ad = Ad::GetObjectFromSoapObject($objSoapObject->Ad);
			if (property_exists($objSoapObject, 'Amount'))
				$objToReturn->intAmount = $objSoapObject->Amount;
			if (property_exists($objSoapObject, 'Status'))
				$objToReturn->strStatus = $objSoapObject->Status;
			if (property_exists($objSoapObject, 'Deadline'))
				$objToReturn->dttDeadline = new QDateTime($objSoapObject->Deadline);
			if (property_exists($objSoapObject, 'AnswerTimestamp'))
				$objToReturn->dttAnswerTimestamp = new QDateTime($objSoapObject->AnswerTimestamp);
			if (property_exists($objSoapObject, 'ContactedBuyer'))
				$objToReturn->intContactedBuyer = $objSoapObject->ContactedBuyer;
			if (property_exists($objSoapObject, 'PublicationDate'))
				$objToReturn->dttPublicationDate = new QDateTime($objSoapObject->PublicationDate);
			if (property_exists($objSoapObject, '__blnRestored'))
				$objToReturn->__blnRestored = $objSoapObject->__blnRestored;
			return $objToReturn;
		}

		public static function GetSoapArrayFromArray($objArray) {
			if (!$objArray)
				return null;

			$objArrayToReturn = array();

			foreach ($objArray as $objObject)
				array_push($objArrayToReturn, Bid::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			if ($objObject->objLogin)
				$objObject->objLogin = Login::GetSoapObjectFromObject($objObject->objLogin, false);
			else if (!$blnBindRelatedObjects)
				$objObject->intLoginId = null;
			if ($objObject->objAd)
				$objObject->objAd = Ad::GetSoapObjectFromObject($objObject->objAd, false);
			else if (!$blnBindRelatedObjects)
				$objObject->intAdId = null;
			if ($objObject->dttDeadline)
				$objObject->dttDeadline = $objObject->dttDeadline->__toString(QDateTime::FormatSoap);
			if ($objObject->dttAnswerTimestamp)
				$objObject->dttAnswerTimestamp = $objObject->dttAnswerTimestamp->__toString(QDateTime::FormatSoap);
			if ($objObject->dttPublicationDate)
				$objObject->dttPublicationDate = $objObject->dttPublicationDate->__toString(QDateTime::FormatSoap);
			return $objObject;
		}
	}
?>