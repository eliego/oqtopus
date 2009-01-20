<?php
	/**
	 * The abstract KeywordGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the Keyword subclass which
	 * extends this KeywordGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the Keyword class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class KeywordGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a Keyword from PK Info
		 * @param integer $intId
		 * @return Keyword
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Keyword::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`keyword`
				FROM
					`keyword`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Keyword::InstantiateDbRow($objDbResult->GetNextRow());
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
				$objQueryExpansion = new QQueryExpansion('Keyword', 'keyword', $objExpansionMap);
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
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `keyword` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`keyword` AS `%s__%s__keyword`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$strParentAlias = $strParentAlias . '__' . $strAlias;
			}

			if (is_array($objExpansionMap))
				foreach ($objExpansionMap as $strKey=>$objValue) {
					switch ($strKey) {
						default:
							throw new QCallerException(sprintf('Unknown Object to Expand in %s: %s', $strParentAlias, $strKey));
					}
				}
		}



		/**
		 * Load all Keywords
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Keyword[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Keyword::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`keyword`.`id` AS `id`,
					`keyword`.`keyword` AS `keyword`
					%s
				FROM
					`keyword` AS `keyword`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Keyword::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all Keywords
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`keyword`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a Keyword from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this Keyword::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return Keyword
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the Keyword object
			$objToReturn = new Keyword();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->strKeyword = $objDbRow->GetColumn($strAliasPrefix . 'keyword', 'VarChar');

			// Instantiate Virtual Attributes
			foreach ($objDbRow->GetColumnNameArray() as $strColumnName => $mixValue) {
				$strVirtualPrefix = $strAliasPrefix . '__';
				$strVirtualPrefixLength = strlen($strVirtualPrefix);
				if (substr($strColumnName, 0, $strVirtualPrefixLength) == $strVirtualPrefix)
					$objToReturn->__strVirtualAttributeArray[substr($strColumnName, $strVirtualPrefixLength)] = $mixValue;
			}

			// Prepare to Check for Early Binding
			if (!$strAliasPrefix)
				$strAliasPrefix = 'keyword__';

			
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
		 * Instantiate an array of Keywords from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return Keyword[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, Keyword::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load a single Keyword object,
		 * by Keyword Index(es)
		 * @param string $strKeyword
		 * @return Keyword
		*/
		public static function LoadByKeyword($strKeyword) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Keyword::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strKeyword = $objDatabase->SqlVariable($strKeyword, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`keyword`
				FROM
					`keyword`
				WHERE
					`keyword` %s', $strKeyword);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Keyword::InstantiateDbRow($objDbResult->GetNextRow());
		}





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////
			/**
		 * Load an array of Ad objects for a given Ad
		 * via the ad_keyword_assn table
		 * @param integer $intAdId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		*/
		public static function LoadArrayByAd($intAdId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Keyword::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intAdId = $objDatabase->SqlVariable($intAdId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`keyword`.`id` AS `id`,
					`keyword`.`keyword` AS `keyword`
					%s
				FROM
					(`keyword` AS `keyword`,
					`ad_keyword_assn` AS `ad_keyword_assn`)
					%s
				WHERE
					`ad_keyword_assn`.`keyword_id` = `keyword`.`id` AND
					`ad_keyword_assn`.`ad_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intAdId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Keyword::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Keywords for a given Ad
		 * via the ad_keyword_assn table
		 * @param integer $intAdId
		 * @return int
		*/
		public static function CountByAd($intAdId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Keyword::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intAdId = $objDatabase->SqlVariable($intAdId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`keyword`,
					`ad_keyword_assn`
				WHERE
					`ad_keyword_assn`.`keyword_id` = `keyword`.`id` AND
					`ad_keyword_assn`.`ad_id` = %s
			', $intAdId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}
			/**
		 * Load an array of Search objects for a given Search
		 * via the search_keyword_assn table
		 * @param integer $intSearchId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Search[]
		*/
		public static function LoadArrayBySearch($intSearchId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Keyword::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSearchId = $objDatabase->SqlVariable($intSearchId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`keyword`.`id` AS `id`,
					`keyword`.`keyword` AS `keyword`
					%s
				FROM
					(`keyword` AS `keyword`,
					`search_keyword_assn` AS `search_keyword_assn`)
					%s
				WHERE
					`search_keyword_assn`.`keyword_id` = `keyword`.`id` AND
					`search_keyword_assn`.`search_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intSearchId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Keyword::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Keywords for a given Search
		 * via the search_keyword_assn table
		 * @param integer $intSearchId
		 * @return int
		*/
		public static function CountBySearch($intSearchId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Keyword::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSearchId = $objDatabase->SqlVariable($intSearchId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`keyword`,
					`search_keyword_assn`
				WHERE
					`search_keyword_assn`.`keyword_id` = `keyword`.`id` AND
					`search_keyword_assn`.`search_id` = %s
			', $intSearchId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this Keyword
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `keyword` (
							`keyword`
						) VALUES (
							' . $objDatabase->SqlVariable($this->strKeyword) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('keyword', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`keyword`
						SET
							`keyword` = ' . $objDatabase->SqlVariable($this->strKeyword) . '
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
		 * Delete this Keyword
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this Keyword with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`keyword`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all Keywords
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`keyword`');
		}

		/**
		 * Truncate keyword table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `keyword`');
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

				case 'Keyword':
					/**
					 * Gets the value for strKeyword (Unique)
					 * @return string
					 */
					return $this->strKeyword;


				///////////////////
				// Member Objects
				///////////////////

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
				case 'Keyword':
					/**
					 * Sets the value for strKeyword (Unique)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strKeyword = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}


				///////////////////
				// Member Objects
				///////////////////
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

			
		// Related Many-to-Many Objects' Methods for Ad
		//-------------------------------------------------------------------

		/**
		 * Gets all many-to-many associated Ads as an array of Ad objects
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		*/ 
		public function GetAdArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Ad::LoadArrayByKeyword($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Ads
		 * @return int
		*/ 
		public function CountAds() {
			if ((is_null($this->intId)))
				return 0;

			return Ad::CountByKeyword($this->intId);
		}

		/**
		 * Associates a Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function AssociateAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this unsaved Keyword.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this Keyword with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `ad_keyword_assn` (
					`keyword_id`,
					`ad_id`
				) VALUES (
					' . $objDatabase->SqlVariable($this->intId) . ',
					' . $objDatabase->SqlVariable($objAd->Id) . '
				)
			');
		}

		/**
		 * Unassociates a Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function UnassociateAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Keyword.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this Keyword with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_keyword_assn`
				WHERE
					`keyword_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`ad_id` = ' . $objDatabase->SqlVariable($objAd->Id) . '
			');
		}

		/**
		 * Unassociates all Ads
		 * @return void
		*/ 
		public function UnassociateAllAds() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllAdArray on this unsaved Keyword.');

			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_keyword_assn`
				WHERE
					`keyword_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}
			
		// Related Many-to-Many Objects' Methods for Search
		//-------------------------------------------------------------------

		/**
		 * Gets all many-to-many associated Searches as an array of Search objects
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Search[]
		*/ 
		public function GetSearchArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Search::LoadArrayByKeyword($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Searches
		 * @return int
		*/ 
		public function CountSearches() {
			if ((is_null($this->intId)))
				return 0;

			return Search::CountByKeyword($this->intId);
		}

		/**
		 * Associates a Search
		 * @param Search $objSearch
		 * @return void
		*/ 
		public function AssociateSearch(Search $objSearch) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSearch on this unsaved Keyword.');
			if ((is_null($objSearch->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSearch on this Keyword with an unsaved Search.');

			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `search_keyword_assn` (
					`keyword_id`,
					`search_id`
				) VALUES (
					' . $objDatabase->SqlVariable($this->intId) . ',
					' . $objDatabase->SqlVariable($objSearch->Id) . '
				)
			');
		}

		/**
		 * Unassociates a Search
		 * @param Search $objSearch
		 * @return void
		*/ 
		public function UnassociateSearch(Search $objSearch) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this unsaved Keyword.');
			if ((is_null($objSearch->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this Keyword with an unsaved Search.');

			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search_keyword_assn`
				WHERE
					`keyword_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`search_id` = ' . $objDatabase->SqlVariable($objSearch->Id) . '
			');
		}

		/**
		 * Unassociates all Searches
		 * @return void
		*/ 
		public function UnassociateAllSearches() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllSearchArray on this unsaved Keyword.');

			// Call to QueryHelper to Get the Database Object
			Keyword::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search_keyword_assn`
				WHERE
					`keyword_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}





		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column keyword.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column keyword.keyword
		 * @var string strKeyword
		 */
		protected $strKeyword;

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





		////////////////////////////////////////
		// COLUMN CONSTANTS for OBJECT EXPANSION
		////////////////////////////////////////




		////////////////////////////////////////
		// METHODS for WEB SERVICES
		////////////////////////////////////////
		public static function GetSoapComplexTypeXml() {
			$strToReturn = '<complexType name="Keyword"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="Keyword" type="xsd:string"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('Keyword', $strComplexTypeArray)) {
				$strComplexTypeArray['Keyword'] = Keyword::GetSoapComplexTypeXml();
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, Keyword::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new Keyword();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if (property_exists($objSoapObject, 'Keyword'))
				$objToReturn->strKeyword = $objSoapObject->Keyword;
			if (property_exists($objSoapObject, '__blnRestored'))
				$objToReturn->__blnRestored = $objSoapObject->__blnRestored;
			return $objToReturn;
		}

		public static function GetSoapArrayFromArray($objArray) {
			if (!$objArray)
				return null;

			$objArrayToReturn = array();

			foreach ($objArray as $objObject)
				array_push($objArrayToReturn, Keyword::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			return $objObject;
		}
	}
?>