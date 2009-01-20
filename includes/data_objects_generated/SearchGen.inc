<?php
	/**
	 * The abstract SearchGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the Search subclass which
	 * extends this SearchGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the Search class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class SearchGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a Search from PK Info
		 * @param integer $intId
		 * @return Search
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`login_id`,
					`reach_mode`,
					`reach`,
					`price_mode`,
					`price`,
					`interests`,
					`age`,
					`area`,
					`send_email`,
					`media_type`,
					`media_sub_type`,
					`sex`,
					`sector`,
					`salary`,
					`education`,
					`sub_area`,
					`sub_sub_area`,
					`name`,
					`keyword_mode`
				FROM
					`search`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Search::InstantiateDbRow($objDbResult->GetNextRow());
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
				$objQueryExpansion = new QQueryExpansion('Search', 'search', $objExpansionMap);
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
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `search` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`login_id` AS `%s__%s__login_id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`reach_mode` AS `%s__%s__reach_mode`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`reach` AS `%s__%s__reach`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`price_mode` AS `%s__%s__price_mode`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`price` AS `%s__%s__price`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`interests` AS `%s__%s__interests`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`age` AS `%s__%s__age`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`area` AS `%s__%s__area`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`send_email` AS `%s__%s__send_email`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`media_type` AS `%s__%s__media_type`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`media_sub_type` AS `%s__%s__media_sub_type`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sex` AS `%s__%s__sex`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sector` AS `%s__%s__sector`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`salary` AS `%s__%s__salary`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`education` AS `%s__%s__education`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sub_area` AS `%s__%s__sub_area`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sub_sub_area` AS `%s__%s__sub_sub_area`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`name` AS `%s__%s__name`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`keyword_mode` AS `%s__%s__keyword_mode`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

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
						default:
							throw new QCallerException(sprintf('Unknown Object to Expand in %s: %s', $strParentAlias, $strKey));
					}
				}
		}



		/**
		 * Load all Searches
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Search[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`search`.`id` AS `id`,
					`search`.`login_id` AS `login_id`,
					`search`.`reach_mode` AS `reach_mode`,
					`search`.`reach` AS `reach`,
					`search`.`price_mode` AS `price_mode`,
					`search`.`price` AS `price`,
					`search`.`interests` AS `interests`,
					`search`.`age` AS `age`,
					`search`.`area` AS `area`,
					`search`.`send_email` AS `send_email`,
					`search`.`media_type` AS `media_type`,
					`search`.`media_sub_type` AS `media_sub_type`,
					`search`.`sex` AS `sex`,
					`search`.`sector` AS `sector`,
					`search`.`salary` AS `salary`,
					`search`.`education` AS `education`,
					`search`.`sub_area` AS `sub_area`,
					`search`.`sub_sub_area` AS `sub_sub_area`,
					`search`.`name` AS `name`,
					`search`.`keyword_mode` AS `keyword_mode`
					%s
				FROM
					`search` AS `search`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Search::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all Searches
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`search`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a Search from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this Search::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return Search
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the Search object
			$objToReturn = new Search();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->intLoginId = $objDbRow->GetColumn($strAliasPrefix . 'login_id', 'Integer');
			$objToReturn->intReachMode = $objDbRow->GetColumn($strAliasPrefix . 'reach_mode', 'Integer');
			$objToReturn->intReach = $objDbRow->GetColumn($strAliasPrefix . 'reach', 'Integer');
			$objToReturn->intPriceMode = $objDbRow->GetColumn($strAliasPrefix . 'price_mode', 'Integer');
			$objToReturn->intPrice = $objDbRow->GetColumn($strAliasPrefix . 'price', 'Integer');
			$objToReturn->intInterests = $objDbRow->GetColumn($strAliasPrefix . 'interests', 'Integer');
			$objToReturn->intAge = $objDbRow->GetColumn($strAliasPrefix . 'age', 'Integer');
			$objToReturn->intArea = $objDbRow->GetColumn($strAliasPrefix . 'area', 'Integer');
			$objToReturn->intSendEmail = $objDbRow->GetColumn($strAliasPrefix . 'send_email', 'Integer');
			$objToReturn->intMediaType = $objDbRow->GetColumn($strAliasPrefix . 'media_type', 'Integer');
			$objToReturn->intMediaSubType = $objDbRow->GetColumn($strAliasPrefix . 'media_sub_type', 'Integer');
			$objToReturn->strSex = $objDbRow->GetColumn($strAliasPrefix . 'sex', 'VarChar');
			$objToReturn->intSector = $objDbRow->GetColumn($strAliasPrefix . 'sector', 'Integer');
			$objToReturn->intSalary = $objDbRow->GetColumn($strAliasPrefix . 'salary', 'Integer');
			$objToReturn->intEducation = $objDbRow->GetColumn($strAliasPrefix . 'education', 'Integer');
			$objToReturn->intSubArea = $objDbRow->GetColumn($strAliasPrefix . 'sub_area', 'Integer');
			$objToReturn->intSubSubArea = $objDbRow->GetColumn($strAliasPrefix . 'sub_sub_area', 'Integer');
			$objToReturn->strName = $objDbRow->GetColumn($strAliasPrefix . 'name', 'VarChar');
			$objToReturn->strKeywordMode = $objDbRow->GetColumn($strAliasPrefix . 'keyword_mode', 'VarChar');

			// Instantiate Virtual Attributes
			foreach ($objDbRow->GetColumnNameArray() as $strColumnName => $mixValue) {
				$strVirtualPrefix = $strAliasPrefix . '__';
				$strVirtualPrefixLength = strlen($strVirtualPrefix);
				if (substr($strColumnName, 0, $strVirtualPrefixLength) == $strVirtualPrefix)
					$objToReturn->__strVirtualAttributeArray[substr($strColumnName, $strVirtualPrefixLength)] = $mixValue;
			}

			// Prepare to Check for Early Binding
			if (!$strAliasPrefix)
				$strAliasPrefix = 'search__';

			// Check for Login Early Binding
			if (!is_null($objDbRow->GetColumn($strAliasPrefix . 'login_id__id')))
				$objToReturn->objLogin = Login::InstantiateDbRow($objDbRow, $strAliasPrefix . 'login_id__');

			
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
		 * Instantiate an array of Searches from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return Search[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, Search::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load an array of Search objects,
		 * by LoginId Index(es)
		 * @param integer $intLoginId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Search[]
		*/
		public static function LoadArrayByLoginId($intLoginId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`search`.`id` AS `id`,
					`search`.`login_id` AS `login_id`,
					`search`.`reach_mode` AS `reach_mode`,
					`search`.`reach` AS `reach`,
					`search`.`price_mode` AS `price_mode`,
					`search`.`price` AS `price`,
					`search`.`interests` AS `interests`,
					`search`.`age` AS `age`,
					`search`.`area` AS `area`,
					`search`.`send_email` AS `send_email`,
					`search`.`media_type` AS `media_type`,
					`search`.`media_sub_type` AS `media_sub_type`,
					`search`.`sex` AS `sex`,
					`search`.`sector` AS `sector`,
					`search`.`salary` AS `salary`,
					`search`.`education` AS `education`,
					`search`.`sub_area` AS `sub_area`,
					`search`.`sub_sub_area` AS `sub_sub_area`,
					`search`.`name` AS `name`,
					`search`.`keyword_mode` AS `keyword_mode`
					%s
				FROM
					`search` AS `search`
					%s
				WHERE
					`search`.`login_id` %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intLoginId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Search::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Searches
		 * by LoginId Index(es)
		 * @param integer $intLoginId
		 * @return int
		*/
		public static function CountByLoginId($intLoginId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`search`
				WHERE
					`login_id` %s', $intLoginId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////
			/**
		 * Load an array of Keyword objects for a given Keyword
		 * via the search_keyword_assn table
		 * @param integer $intKeywordId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Keyword[]
		*/
		public static function LoadArrayByKeyword($intKeywordId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intKeywordId = $objDatabase->SqlVariable($intKeywordId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`search`.`id` AS `id`,
					`search`.`login_id` AS `login_id`,
					`search`.`reach_mode` AS `reach_mode`,
					`search`.`reach` AS `reach`,
					`search`.`price_mode` AS `price_mode`,
					`search`.`price` AS `price`,
					`search`.`interests` AS `interests`,
					`search`.`age` AS `age`,
					`search`.`area` AS `area`,
					`search`.`send_email` AS `send_email`,
					`search`.`media_type` AS `media_type`,
					`search`.`media_sub_type` AS `media_sub_type`,
					`search`.`sex` AS `sex`,
					`search`.`sector` AS `sector`,
					`search`.`salary` AS `salary`,
					`search`.`education` AS `education`,
					`search`.`sub_area` AS `sub_area`,
					`search`.`sub_sub_area` AS `sub_sub_area`,
					`search`.`name` AS `name`,
					`search`.`keyword_mode` AS `keyword_mode`
					%s
				FROM
					(`search` AS `search`,
					`search_keyword_assn` AS `search_keyword_assn`)
					%s
				WHERE
					`search_keyword_assn`.`search_id` = `search`.`id` AND
					`search_keyword_assn`.`keyword_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intKeywordId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Search::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Searches for a given Keyword
		 * via the search_keyword_assn table
		 * @param integer $intKeywordId
		 * @return int
		*/
		public static function CountByKeyword($intKeywordId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intKeywordId = $objDatabase->SqlVariable($intKeywordId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`search`,
					`search_keyword_assn`
				WHERE
					`search_keyword_assn`.`search_id` = `search`.`id` AND
					`search_keyword_assn`.`keyword_id` = %s
			', $intKeywordId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this Search
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `search` (
							`login_id`,
							`reach_mode`,
							`reach`,
							`price_mode`,
							`price`,
							`interests`,
							`age`,
							`area`,
							`send_email`,
							`media_type`,
							`media_sub_type`,
							`sex`,
							`sector`,
							`salary`,
							`education`,
							`sub_area`,
							`sub_sub_area`,
							`name`,
							`keyword_mode`
						) VALUES (
							' . $objDatabase->SqlVariable($this->intLoginId) . ',
							' . $objDatabase->SqlVariable($this->intReachMode) . ',
							' . $objDatabase->SqlVariable($this->intReach) . ',
							' . $objDatabase->SqlVariable($this->intPriceMode) . ',
							' . $objDatabase->SqlVariable($this->intPrice) . ',
							' . $objDatabase->SqlVariable($this->intInterests) . ',
							' . $objDatabase->SqlVariable($this->intAge) . ',
							' . $objDatabase->SqlVariable($this->intArea) . ',
							' . $objDatabase->SqlVariable($this->intSendEmail) . ',
							' . $objDatabase->SqlVariable($this->intMediaType) . ',
							' . $objDatabase->SqlVariable($this->intMediaSubType) . ',
							' . $objDatabase->SqlVariable($this->strSex) . ',
							' . $objDatabase->SqlVariable($this->intSector) . ',
							' . $objDatabase->SqlVariable($this->intSalary) . ',
							' . $objDatabase->SqlVariable($this->intEducation) . ',
							' . $objDatabase->SqlVariable($this->intSubArea) . ',
							' . $objDatabase->SqlVariable($this->intSubSubArea) . ',
							' . $objDatabase->SqlVariable($this->strName) . ',
							' . $objDatabase->SqlVariable($this->strKeywordMode) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('search', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`search`
						SET
							`login_id` = ' . $objDatabase->SqlVariable($this->intLoginId) . ',
							`reach_mode` = ' . $objDatabase->SqlVariable($this->intReachMode) . ',
							`reach` = ' . $objDatabase->SqlVariable($this->intReach) . ',
							`price_mode` = ' . $objDatabase->SqlVariable($this->intPriceMode) . ',
							`price` = ' . $objDatabase->SqlVariable($this->intPrice) . ',
							`interests` = ' . $objDatabase->SqlVariable($this->intInterests) . ',
							`age` = ' . $objDatabase->SqlVariable($this->intAge) . ',
							`area` = ' . $objDatabase->SqlVariable($this->intArea) . ',
							`send_email` = ' . $objDatabase->SqlVariable($this->intSendEmail) . ',
							`media_type` = ' . $objDatabase->SqlVariable($this->intMediaType) . ',
							`media_sub_type` = ' . $objDatabase->SqlVariable($this->intMediaSubType) . ',
							`sex` = ' . $objDatabase->SqlVariable($this->strSex) . ',
							`sector` = ' . $objDatabase->SqlVariable($this->intSector) . ',
							`salary` = ' . $objDatabase->SqlVariable($this->intSalary) . ',
							`education` = ' . $objDatabase->SqlVariable($this->intEducation) . ',
							`sub_area` = ' . $objDatabase->SqlVariable($this->intSubArea) . ',
							`sub_sub_area` = ' . $objDatabase->SqlVariable($this->intSubSubArea) . ',
							`name` = ' . $objDatabase->SqlVariable($this->strName) . ',
							`keyword_mode` = ' . $objDatabase->SqlVariable($this->strKeywordMode) . '
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
		 * Delete this Search
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this Search with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all Searches
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search`');
		}

		/**
		 * Truncate search table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `search`');
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

				case 'ReachMode':
					/**
					 * Gets the value for intReachMode 
					 * @return integer
					 */
					return $this->intReachMode;

				case 'Reach':
					/**
					 * Gets the value for intReach 
					 * @return integer
					 */
					return $this->intReach;

				case 'PriceMode':
					/**
					 * Gets the value for intPriceMode 
					 * @return integer
					 */
					return $this->intPriceMode;

				case 'Price':
					/**
					 * Gets the value for intPrice 
					 * @return integer
					 */
					return $this->intPrice;

				case 'Interests':
					/**
					 * Gets the value for intInterests 
					 * @return integer
					 */
					return $this->intInterests;

				case 'Age':
					/**
					 * Gets the value for intAge 
					 * @return integer
					 */
					return $this->intAge;

				case 'Area':
					/**
					 * Gets the value for intArea 
					 * @return integer
					 */
					return $this->intArea;

				case 'SendEmail':
					/**
					 * Gets the value for intSendEmail (Not Null)
					 * @return integer
					 */
					return $this->intSendEmail;

				case 'MediaType':
					/**
					 * Gets the value for intMediaType 
					 * @return integer
					 */
					return $this->intMediaType;

				case 'MediaSubType':
					/**
					 * Gets the value for intMediaSubType 
					 * @return integer
					 */
					return $this->intMediaSubType;

				case 'Sex':
					/**
					 * Gets the value for strSex 
					 * @return string
					 */
					return $this->strSex;

				case 'Sector':
					/**
					 * Gets the value for intSector 
					 * @return integer
					 */
					return $this->intSector;

				case 'Salary':
					/**
					 * Gets the value for intSalary 
					 * @return integer
					 */
					return $this->intSalary;

				case 'Education':
					/**
					 * Gets the value for intEducation 
					 * @return integer
					 */
					return $this->intEducation;

				case 'SubArea':
					/**
					 * Gets the value for intSubArea 
					 * @return integer
					 */
					return $this->intSubArea;

				case 'SubSubArea':
					/**
					 * Gets the value for intSubSubArea 
					 * @return integer
					 */
					return $this->intSubSubArea;

				case 'Name':
					/**
					 * Gets the value for strName 
					 * @return string
					 */
					return $this->strName;

				case 'KeywordMode':
					/**
					 * Gets the value for strKeywordMode 
					 * @return string
					 */
					return $this->strKeywordMode;


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

				case 'ReachMode':
					/**
					 * Sets the value for intReachMode 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intReachMode = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Reach':
					/**
					 * Sets the value for intReach 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intReach = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'PriceMode':
					/**
					 * Sets the value for intPriceMode 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intPriceMode = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Price':
					/**
					 * Sets the value for intPrice 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intPrice = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Interests':
					/**
					 * Sets the value for intInterests 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intInterests = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Age':
					/**
					 * Sets the value for intAge 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intAge = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Area':
					/**
					 * Sets the value for intArea 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intArea = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'SendEmail':
					/**
					 * Sets the value for intSendEmail (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intSendEmail = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'MediaType':
					/**
					 * Sets the value for intMediaType 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intMediaType = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'MediaSubType':
					/**
					 * Sets the value for intMediaSubType 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intMediaSubType = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Sex':
					/**
					 * Sets the value for strSex 
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strSex = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Sector':
					/**
					 * Sets the value for intSector 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intSector = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Salary':
					/**
					 * Sets the value for intSalary 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intSalary = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Education':
					/**
					 * Sets the value for intEducation 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intEducation = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'SubArea':
					/**
					 * Sets the value for intSubArea 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intSubArea = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'SubSubArea':
					/**
					 * Sets the value for intSubSubArea 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intSubSubArea = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Name':
					/**
					 * Sets the value for strName 
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strName = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'KeywordMode':
					/**
					 * Sets the value for strKeywordMode 
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strKeywordMode = QType::Cast($mixValue, QType::String));
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
							throw new QCallerException('Unable to set an unsaved Login for this Search');

						// Update Local Member Variables
						$this->objLogin = $mixValue;
						$this->intLoginId = $mixValue->Id;

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

			
		// Related Many-to-Many Objects' Methods for Keyword
		//-------------------------------------------------------------------

		/**
		 * Gets all many-to-many associated Keywords as an array of Keyword objects
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Keyword[]
		*/ 
		public function GetKeywordArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Keyword::LoadArrayBySearch($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Keywords
		 * @return int
		*/ 
		public function CountKeywords() {
			if ((is_null($this->intId)))
				return 0;

			return Keyword::CountBySearch($this->intId);
		}

		/**
		 * Associates a Keyword
		 * @param Keyword $objKeyword
		 * @return void
		*/ 
		public function AssociateKeyword(Keyword $objKeyword) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateKeyword on this unsaved Search.');
			if ((is_null($objKeyword->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateKeyword on this Search with an unsaved Keyword.');

			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `search_keyword_assn` (
					`search_id`,
					`keyword_id`
				) VALUES (
					' . $objDatabase->SqlVariable($this->intId) . ',
					' . $objDatabase->SqlVariable($objKeyword->Id) . '
				)
			');
		}

		/**
		 * Unassociates a Keyword
		 * @param Keyword $objKeyword
		 * @return void
		*/ 
		public function UnassociateKeyword(Keyword $objKeyword) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateKeyword on this unsaved Search.');
			if ((is_null($objKeyword->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateKeyword on this Search with an unsaved Keyword.');

			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search_keyword_assn`
				WHERE
					`search_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`keyword_id` = ' . $objDatabase->SqlVariable($objKeyword->Id) . '
			');
		}

		/**
		 * Unassociates all Keywords
		 * @return void
		*/ 
		public function UnassociateAllKeywords() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllKeywordArray on this unsaved Search.');

			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search_keyword_assn`
				WHERE
					`search_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}





		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column search.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column search.login_id
		 * @var integer intLoginId
		 */
		protected $intLoginId;

		/**
		 * Protected member variable that maps to the database column search.reach_mode
		 * @var integer intReachMode
		 */
		protected $intReachMode;

		/**
		 * Protected member variable that maps to the database column search.reach
		 * @var integer intReach
		 */
		protected $intReach;

		/**
		 * Protected member variable that maps to the database column search.price_mode
		 * @var integer intPriceMode
		 */
		protected $intPriceMode;

		/**
		 * Protected member variable that maps to the database column search.price
		 * @var integer intPrice
		 */
		protected $intPrice;

		/**
		 * Protected member variable that maps to the database column search.interests
		 * @var integer intInterests
		 */
		protected $intInterests;

		/**
		 * Protected member variable that maps to the database column search.age
		 * @var integer intAge
		 */
		protected $intAge;

		/**
		 * Protected member variable that maps to the database column search.area
		 * @var integer intArea
		 */
		protected $intArea;

		/**
		 * Protected member variable that maps to the database column search.send_email
		 * @var integer intSendEmail
		 */
		protected $intSendEmail;

		/**
		 * Protected member variable that maps to the database column search.media_type
		 * @var integer intMediaType
		 */
		protected $intMediaType;

		/**
		 * Protected member variable that maps to the database column search.media_sub_type
		 * @var integer intMediaSubType
		 */
		protected $intMediaSubType;

		/**
		 * Protected member variable that maps to the database column search.sex
		 * @var string strSex
		 */
		protected $strSex;

		/**
		 * Protected member variable that maps to the database column search.sector
		 * @var integer intSector
		 */
		protected $intSector;

		/**
		 * Protected member variable that maps to the database column search.salary
		 * @var integer intSalary
		 */
		protected $intSalary;

		/**
		 * Protected member variable that maps to the database column search.education
		 * @var integer intEducation
		 */
		protected $intEducation;

		/**
		 * Protected member variable that maps to the database column search.sub_area
		 * @var integer intSubArea
		 */
		protected $intSubArea;

		/**
		 * Protected member variable that maps to the database column search.sub_sub_area
		 * @var integer intSubSubArea
		 */
		protected $intSubSubArea;

		/**
		 * Protected member variable that maps to the database column search.name
		 * @var string strName
		 */
		protected $strName;

		/**
		 * Protected member variable that maps to the database column search.keyword_mode
		 * @var string strKeywordMode
		 */
		protected $strKeywordMode;

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
		 * in the database column search.login_id.
		 *
		 * NOTE: Always use the Login property getter to correctly retrieve this Login object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var Login objLogin
		 */
		protected $objLogin;





		////////////////////////////////////////
		// COLUMN CONSTANTS for OBJECT EXPANSION
		////////////////////////////////////////
		const ExpandLogin = 'login_id';




		////////////////////////////////////////
		// METHODS for WEB SERVICES
		////////////////////////////////////////
		public static function GetSoapComplexTypeXml() {
			$strToReturn = '<complexType name="Search"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="Login" type="xsd1:Login"/>';
			$strToReturn .= '<element name="ReachMode" type="xsd:int"/>';
			$strToReturn .= '<element name="Reach" type="xsd:int"/>';
			$strToReturn .= '<element name="PriceMode" type="xsd:int"/>';
			$strToReturn .= '<element name="Price" type="xsd:int"/>';
			$strToReturn .= '<element name="Interests" type="xsd:int"/>';
			$strToReturn .= '<element name="Age" type="xsd:int"/>';
			$strToReturn .= '<element name="Area" type="xsd:int"/>';
			$strToReturn .= '<element name="SendEmail" type="xsd:int"/>';
			$strToReturn .= '<element name="MediaType" type="xsd:int"/>';
			$strToReturn .= '<element name="MediaSubType" type="xsd:int"/>';
			$strToReturn .= '<element name="Sex" type="xsd:string"/>';
			$strToReturn .= '<element name="Sector" type="xsd:int"/>';
			$strToReturn .= '<element name="Salary" type="xsd:int"/>';
			$strToReturn .= '<element name="Education" type="xsd:int"/>';
			$strToReturn .= '<element name="SubArea" type="xsd:int"/>';
			$strToReturn .= '<element name="SubSubArea" type="xsd:int"/>';
			$strToReturn .= '<element name="Name" type="xsd:string"/>';
			$strToReturn .= '<element name="KeywordMode" type="xsd:string"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('Search', $strComplexTypeArray)) {
				$strComplexTypeArray['Search'] = Search::GetSoapComplexTypeXml();
				Login::AlterSoapComplexTypeArray($strComplexTypeArray);
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, Search::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new Search();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if ((property_exists($objSoapObject, 'Login')) &&
				($objSoapObject->Login))
				$objToReturn->Login = Login::GetObjectFromSoapObject($objSoapObject->Login);
			if (property_exists($objSoapObject, 'ReachMode'))
				$objToReturn->intReachMode = $objSoapObject->ReachMode;
			if (property_exists($objSoapObject, 'Reach'))
				$objToReturn->intReach = $objSoapObject->Reach;
			if (property_exists($objSoapObject, 'PriceMode'))
				$objToReturn->intPriceMode = $objSoapObject->PriceMode;
			if (property_exists($objSoapObject, 'Price'))
				$objToReturn->intPrice = $objSoapObject->Price;
			if (property_exists($objSoapObject, 'Interests'))
				$objToReturn->intInterests = $objSoapObject->Interests;
			if (property_exists($objSoapObject, 'Age'))
				$objToReturn->intAge = $objSoapObject->Age;
			if (property_exists($objSoapObject, 'Area'))
				$objToReturn->intArea = $objSoapObject->Area;
			if (property_exists($objSoapObject, 'SendEmail'))
				$objToReturn->intSendEmail = $objSoapObject->SendEmail;
			if (property_exists($objSoapObject, 'MediaType'))
				$objToReturn->intMediaType = $objSoapObject->MediaType;
			if (property_exists($objSoapObject, 'MediaSubType'))
				$objToReturn->intMediaSubType = $objSoapObject->MediaSubType;
			if (property_exists($objSoapObject, 'Sex'))
				$objToReturn->strSex = $objSoapObject->Sex;
			if (property_exists($objSoapObject, 'Sector'))
				$objToReturn->intSector = $objSoapObject->Sector;
			if (property_exists($objSoapObject, 'Salary'))
				$objToReturn->intSalary = $objSoapObject->Salary;
			if (property_exists($objSoapObject, 'Education'))
				$objToReturn->intEducation = $objSoapObject->Education;
			if (property_exists($objSoapObject, 'SubArea'))
				$objToReturn->intSubArea = $objSoapObject->SubArea;
			if (property_exists($objSoapObject, 'SubSubArea'))
				$objToReturn->intSubSubArea = $objSoapObject->SubSubArea;
			if (property_exists($objSoapObject, 'Name'))
				$objToReturn->strName = $objSoapObject->Name;
			if (property_exists($objSoapObject, 'KeywordMode'))
				$objToReturn->strKeywordMode = $objSoapObject->KeywordMode;
			if (property_exists($objSoapObject, '__blnRestored'))
				$objToReturn->__blnRestored = $objSoapObject->__blnRestored;
			return $objToReturn;
		}

		public static function GetSoapArrayFromArray($objArray) {
			if (!$objArray)
				return null;

			$objArrayToReturn = array();

			foreach ($objArray as $objObject)
				array_push($objArrayToReturn, Search::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			if ($objObject->objLogin)
				$objObject->objLogin = Login::GetSoapObjectFromObject($objObject->objLogin, false);
			else if (!$blnBindRelatedObjects)
				$objObject->intLoginId = null;
			return $objObject;
		}
	}
?>