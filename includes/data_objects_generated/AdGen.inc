<?php
	/**
	 * The abstract AdGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the Ad subclass which
	 * extends this AdGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the Ad class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class AdGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a Ad from PK Info
		 * @param integer $intId
		 * @return Ad
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`type`,
					`media_type`,
					`reach`,
					`price`,
					`description`,
					`seller_id`,
					`area`,
					`login_id`,
					`media_sub_type`,
					`deadline`,
					`start_age`,
					`end_age`,
					`sex`,
					`sectors`,
					`salaries`,
					`educations`,
					`name`,
					`sub_area`,
					`sub_sub_area`,
					`permission_mode`,
					`publication_date`
				FROM
					`ad`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbRow($objDbResult->GetNextRow());
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
				$objQueryExpansion = new QQueryExpansion('Ad', 'ad', $objExpansionMap);
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
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `ad` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`type` AS `%s__%s__type`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`media_type` AS `%s__%s__media_type`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`reach` AS `%s__%s__reach`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`price` AS `%s__%s__price`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`description` AS `%s__%s__description`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`seller_id` AS `%s__%s__seller_id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`area` AS `%s__%s__area`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`login_id` AS `%s__%s__login_id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`media_sub_type` AS `%s__%s__media_sub_type`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`deadline` AS `%s__%s__deadline`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`start_age` AS `%s__%s__start_age`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`end_age` AS `%s__%s__end_age`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sex` AS `%s__%s__sex`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sectors` AS `%s__%s__sectors`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`salaries` AS `%s__%s__salaries`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`educations` AS `%s__%s__educations`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`name` AS `%s__%s__name`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sub_area` AS `%s__%s__sub_area`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`sub_sub_area` AS `%s__%s__sub_sub_area`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`permission_mode` AS `%s__%s__permission_mode`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`publication_date` AS `%s__%s__publication_date`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$strParentAlias = $strParentAlias . '__' . $strAlias;
			}

			if (is_array($objExpansionMap))
				foreach ($objExpansionMap as $strKey=>$objValue) {
					switch ($strKey) {
						case 'seller_id':
							try {
								Seller::ExpandQuery($strParentAlias, $strKey, $objValue, $objQueryExpansion);
								break;
							} catch (QCallerException $objExc) {
								$objExc->IncrementOffset();
								throw $objExc;
							}
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
		 * Load all Ads
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`ad`.`id` AS `id`,
					`ad`.`type` AS `type`,
					`ad`.`media_type` AS `media_type`,
					`ad`.`reach` AS `reach`,
					`ad`.`price` AS `price`,
					`ad`.`description` AS `description`,
					`ad`.`seller_id` AS `seller_id`,
					`ad`.`area` AS `area`,
					`ad`.`login_id` AS `login_id`,
					`ad`.`media_sub_type` AS `media_sub_type`,
					`ad`.`deadline` AS `deadline`,
					`ad`.`start_age` AS `start_age`,
					`ad`.`end_age` AS `end_age`,
					`ad`.`sex` AS `sex`,
					`ad`.`sectors` AS `sectors`,
					`ad`.`salaries` AS `salaries`,
					`ad`.`educations` AS `educations`,
					`ad`.`name` AS `name`,
					`ad`.`sub_area` AS `sub_area`,
					`ad`.`sub_sub_area` AS `sub_sub_area`,
					`ad`.`permission_mode` AS `permission_mode`,
					`ad`.`publication_date` AS `publication_date`
					%s
				FROM
					`ad` AS `ad`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all Ads
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`ad`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a Ad from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this Ad::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return Ad
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the Ad object
			$objToReturn = new Ad();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->strType = $objDbRow->GetColumn($strAliasPrefix . 'type', 'VarChar');
			$objToReturn->intMediaType = $objDbRow->GetColumn($strAliasPrefix . 'media_type', 'Integer');
			$objToReturn->intReach = $objDbRow->GetColumn($strAliasPrefix . 'reach', 'Integer');
			$objToReturn->intPrice = $objDbRow->GetColumn($strAliasPrefix . 'price', 'Integer');
			$objToReturn->strDescription = $objDbRow->GetColumn($strAliasPrefix . 'description', 'Blob');
			$objToReturn->intSellerId = $objDbRow->GetColumn($strAliasPrefix . 'seller_id', 'Integer');
			$objToReturn->intArea = $objDbRow->GetColumn($strAliasPrefix . 'area', 'Integer');
			$objToReturn->intLoginId = $objDbRow->GetColumn($strAliasPrefix . 'login_id', 'Integer');
			$objToReturn->intMediaSubType = $objDbRow->GetColumn($strAliasPrefix . 'media_sub_type', 'Integer');
			$objToReturn->intDeadline = $objDbRow->GetColumn($strAliasPrefix . 'deadline', 'Integer');
			$objToReturn->intStartAge = $objDbRow->GetColumn($strAliasPrefix . 'start_age', 'Integer');
			$objToReturn->intEndAge = $objDbRow->GetColumn($strAliasPrefix . 'end_age', 'Integer');
			$objToReturn->strSex = $objDbRow->GetColumn($strAliasPrefix . 'sex', 'VarChar');
			$objToReturn->intSectors = $objDbRow->GetColumn($strAliasPrefix . 'sectors', 'Integer');
			$objToReturn->intSalaries = $objDbRow->GetColumn($strAliasPrefix . 'salaries', 'Integer');
			$objToReturn->intEducations = $objDbRow->GetColumn($strAliasPrefix . 'educations', 'Integer');
			$objToReturn->strName = $objDbRow->GetColumn($strAliasPrefix . 'name', 'VarChar');
			$objToReturn->intSubArea = $objDbRow->GetColumn($strAliasPrefix . 'sub_area', 'Integer');
			$objToReturn->intSubSubArea = $objDbRow->GetColumn($strAliasPrefix . 'sub_sub_area', 'Integer');
			$objToReturn->strPermissionMode = $objDbRow->GetColumn($strAliasPrefix . 'permission_mode', 'VarChar');
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
				$strAliasPrefix = 'ad__';

			// Check for Seller Early Binding
			if (!is_null($objDbRow->GetColumn($strAliasPrefix . 'seller_id__id')))
				$objToReturn->objSeller = Seller::InstantiateDbRow($objDbRow, $strAliasPrefix . 'seller_id__');

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
		 * Instantiate an array of Ads from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return Ad[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, Ad::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load an array of Ad objects,
		 * by SellerId Index(es)
		 * @param integer $intSellerId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		*/
		public static function LoadArrayBySellerId($intSellerId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSellerId = $objDatabase->SqlVariable($intSellerId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`ad`.`id` AS `id`,
					`ad`.`type` AS `type`,
					`ad`.`media_type` AS `media_type`,
					`ad`.`reach` AS `reach`,
					`ad`.`price` AS `price`,
					`ad`.`description` AS `description`,
					`ad`.`seller_id` AS `seller_id`,
					`ad`.`area` AS `area`,
					`ad`.`login_id` AS `login_id`,
					`ad`.`media_sub_type` AS `media_sub_type`,
					`ad`.`deadline` AS `deadline`,
					`ad`.`start_age` AS `start_age`,
					`ad`.`end_age` AS `end_age`,
					`ad`.`sex` AS `sex`,
					`ad`.`sectors` AS `sectors`,
					`ad`.`salaries` AS `salaries`,
					`ad`.`educations` AS `educations`,
					`ad`.`name` AS `name`,
					`ad`.`sub_area` AS `sub_area`,
					`ad`.`sub_sub_area` AS `sub_sub_area`,
					`ad`.`permission_mode` AS `permission_mode`,
					`ad`.`publication_date` AS `publication_date`
					%s
				FROM
					`ad` AS `ad`
					%s
				WHERE
					`ad`.`seller_id` %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intSellerId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Ads
		 * by SellerId Index(es)
		 * @param integer $intSellerId
		 * @return int
		*/
		public static function CountBySellerId($intSellerId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSellerId = $objDatabase->SqlVariable($intSellerId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`ad`
				WHERE
					`seller_id` %s', $intSellerId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}
			
		/**
		 * Load an array of Ad objects,
		 * by LoginId Index(es)
		 * @param integer $intLoginId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		*/
		public static function LoadArrayByLoginId($intLoginId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`ad`.`id` AS `id`,
					`ad`.`type` AS `type`,
					`ad`.`media_type` AS `media_type`,
					`ad`.`reach` AS `reach`,
					`ad`.`price` AS `price`,
					`ad`.`description` AS `description`,
					`ad`.`seller_id` AS `seller_id`,
					`ad`.`area` AS `area`,
					`ad`.`login_id` AS `login_id`,
					`ad`.`media_sub_type` AS `media_sub_type`,
					`ad`.`deadline` AS `deadline`,
					`ad`.`start_age` AS `start_age`,
					`ad`.`end_age` AS `end_age`,
					`ad`.`sex` AS `sex`,
					`ad`.`sectors` AS `sectors`,
					`ad`.`salaries` AS `salaries`,
					`ad`.`educations` AS `educations`,
					`ad`.`name` AS `name`,
					`ad`.`sub_area` AS `sub_area`,
					`ad`.`sub_sub_area` AS `sub_sub_area`,
					`ad`.`permission_mode` AS `permission_mode`,
					`ad`.`publication_date` AS `publication_date`
					%s
				FROM
					`ad` AS `ad`
					%s
				WHERE
					`ad`.`login_id` %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intLoginId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Ads
		 * by LoginId Index(es)
		 * @param integer $intLoginId
		 * @return int
		*/
		public static function CountByLoginId($intLoginId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`ad`
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
		 * via the ad_keyword_assn table
		 * @param integer $intKeywordId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Keyword[]
		*/
		public static function LoadArrayByKeyword($intKeywordId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intKeywordId = $objDatabase->SqlVariable($intKeywordId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`ad`.`id` AS `id`,
					`ad`.`type` AS `type`,
					`ad`.`media_type` AS `media_type`,
					`ad`.`reach` AS `reach`,
					`ad`.`price` AS `price`,
					`ad`.`description` AS `description`,
					`ad`.`seller_id` AS `seller_id`,
					`ad`.`area` AS `area`,
					`ad`.`login_id` AS `login_id`,
					`ad`.`media_sub_type` AS `media_sub_type`,
					`ad`.`deadline` AS `deadline`,
					`ad`.`start_age` AS `start_age`,
					`ad`.`end_age` AS `end_age`,
					`ad`.`sex` AS `sex`,
					`ad`.`sectors` AS `sectors`,
					`ad`.`salaries` AS `salaries`,
					`ad`.`educations` AS `educations`,
					`ad`.`name` AS `name`,
					`ad`.`sub_area` AS `sub_area`,
					`ad`.`sub_sub_area` AS `sub_sub_area`,
					`ad`.`permission_mode` AS `permission_mode`,
					`ad`.`publication_date` AS `publication_date`
					%s
				FROM
					(`ad` AS `ad`,
					`ad_keyword_assn` AS `ad_keyword_assn`)
					%s
				WHERE
					`ad_keyword_assn`.`ad_id` = `ad`.`id` AND
					`ad_keyword_assn`.`keyword_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intKeywordId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Ads for a given Keyword
		 * via the ad_keyword_assn table
		 * @param integer $intKeywordId
		 * @return int
		*/
		public static function CountByKeyword($intKeywordId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intKeywordId = $objDatabase->SqlVariable($intKeywordId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`ad`,
					`ad_keyword_assn`
				WHERE
					`ad_keyword_assn`.`ad_id` = `ad`.`id` AND
					`ad_keyword_assn`.`keyword_id` = %s
			', $intKeywordId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}
			/**
		 * Load an array of Network objects for a given Network
		 * via the ad_network_assn table
		 * @param integer $intNetworkId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Network[]
		*/
		public static function LoadArrayByNetwork($intNetworkId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intNetworkId = $objDatabase->SqlVariable($intNetworkId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`ad`.`id` AS `id`,
					`ad`.`type` AS `type`,
					`ad`.`media_type` AS `media_type`,
					`ad`.`reach` AS `reach`,
					`ad`.`price` AS `price`,
					`ad`.`description` AS `description`,
					`ad`.`seller_id` AS `seller_id`,
					`ad`.`area` AS `area`,
					`ad`.`login_id` AS `login_id`,
					`ad`.`media_sub_type` AS `media_sub_type`,
					`ad`.`deadline` AS `deadline`,
					`ad`.`start_age` AS `start_age`,
					`ad`.`end_age` AS `end_age`,
					`ad`.`sex` AS `sex`,
					`ad`.`sectors` AS `sectors`,
					`ad`.`salaries` AS `salaries`,
					`ad`.`educations` AS `educations`,
					`ad`.`name` AS `name`,
					`ad`.`sub_area` AS `sub_area`,
					`ad`.`sub_sub_area` AS `sub_sub_area`,
					`ad`.`permission_mode` AS `permission_mode`,
					`ad`.`publication_date` AS `publication_date`
					%s
				FROM
					(`ad` AS `ad`,
					`ad_network_assn` AS `ad_network_assn`)
					%s
				WHERE
					`ad_network_assn`.`ad_id` = `ad`.`id` AND
					`ad_network_assn`.`network_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intNetworkId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Ads for a given Network
		 * via the ad_network_assn table
		 * @param integer $intNetworkId
		 * @return int
		*/
		public static function CountByNetwork($intNetworkId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Ad::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intNetworkId = $objDatabase->SqlVariable($intNetworkId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`ad`,
					`ad_network_assn`
				WHERE
					`ad_network_assn`.`ad_id` = `ad`.`id` AND
					`ad_network_assn`.`network_id` = %s
			', $intNetworkId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this Ad
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `ad` (
							`type`,
							`media_type`,
							`reach`,
							`price`,
							`description`,
							`seller_id`,
							`area`,
							`login_id`,
							`media_sub_type`,
							`deadline`,
							`start_age`,
							`end_age`,
							`sex`,
							`sectors`,
							`salaries`,
							`educations`,
							`name`,
							`sub_area`,
							`sub_sub_area`,
							`permission_mode`,
							`publication_date`
						) VALUES (
							' . $objDatabase->SqlVariable($this->strType) . ',
							' . $objDatabase->SqlVariable($this->intMediaType) . ',
							' . $objDatabase->SqlVariable($this->intReach) . ',
							' . $objDatabase->SqlVariable($this->intPrice) . ',
							' . $objDatabase->SqlVariable($this->strDescription) . ',
							' . $objDatabase->SqlVariable($this->intSellerId) . ',
							' . $objDatabase->SqlVariable($this->intArea) . ',
							' . $objDatabase->SqlVariable($this->intLoginId) . ',
							' . $objDatabase->SqlVariable($this->intMediaSubType) . ',
							' . $objDatabase->SqlVariable($this->intDeadline) . ',
							' . $objDatabase->SqlVariable($this->intStartAge) . ',
							' . $objDatabase->SqlVariable($this->intEndAge) . ',
							' . $objDatabase->SqlVariable($this->strSex) . ',
							' . $objDatabase->SqlVariable($this->intSectors) . ',
							' . $objDatabase->SqlVariable($this->intSalaries) . ',
							' . $objDatabase->SqlVariable($this->intEducations) . ',
							' . $objDatabase->SqlVariable($this->strName) . ',
							' . $objDatabase->SqlVariable($this->intSubArea) . ',
							' . $objDatabase->SqlVariable($this->intSubSubArea) . ',
							' . $objDatabase->SqlVariable($this->strPermissionMode) . ',
							' . $objDatabase->SqlVariable($this->dttPublicationDate) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('ad', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`ad`
						SET
							`type` = ' . $objDatabase->SqlVariable($this->strType) . ',
							`media_type` = ' . $objDatabase->SqlVariable($this->intMediaType) . ',
							`reach` = ' . $objDatabase->SqlVariable($this->intReach) . ',
							`price` = ' . $objDatabase->SqlVariable($this->intPrice) . ',
							`description` = ' . $objDatabase->SqlVariable($this->strDescription) . ',
							`seller_id` = ' . $objDatabase->SqlVariable($this->intSellerId) . ',
							`area` = ' . $objDatabase->SqlVariable($this->intArea) . ',
							`login_id` = ' . $objDatabase->SqlVariable($this->intLoginId) . ',
							`media_sub_type` = ' . $objDatabase->SqlVariable($this->intMediaSubType) . ',
							`deadline` = ' . $objDatabase->SqlVariable($this->intDeadline) . ',
							`start_age` = ' . $objDatabase->SqlVariable($this->intStartAge) . ',
							`end_age` = ' . $objDatabase->SqlVariable($this->intEndAge) . ',
							`sex` = ' . $objDatabase->SqlVariable($this->strSex) . ',
							`sectors` = ' . $objDatabase->SqlVariable($this->intSectors) . ',
							`salaries` = ' . $objDatabase->SqlVariable($this->intSalaries) . ',
							`educations` = ' . $objDatabase->SqlVariable($this->intEducations) . ',
							`name` = ' . $objDatabase->SqlVariable($this->strName) . ',
							`sub_area` = ' . $objDatabase->SqlVariable($this->intSubArea) . ',
							`sub_sub_area` = ' . $objDatabase->SqlVariable($this->intSubSubArea) . ',
							`permission_mode` = ' . $objDatabase->SqlVariable($this->strPermissionMode) . ',
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
		 * Delete this Ad
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this Ad with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all Ads
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad`');
		}

		/**
		 * Truncate ad table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `ad`');
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

				case 'Type':
					/**
					 * Gets the value for strType (Not Null)
					 * @return string
					 */
					return $this->strType;

				case 'MediaType':
					/**
					 * Gets the value for intMediaType (Not Null)
					 * @return integer
					 */
					return $this->intMediaType;

				case 'Reach':
					/**
					 * Gets the value for intReach (Not Null)
					 * @return integer
					 */
					return $this->intReach;

				case 'Price':
					/**
					 * Gets the value for intPrice (Not Null)
					 * @return integer
					 */
					return $this->intPrice;

				case 'Description':
					/**
					 * Gets the value for strDescription (Not Null)
					 * @return string
					 */
					return $this->strDescription;

				case 'SellerId':
					/**
					 * Gets the value for intSellerId (Not Null)
					 * @return integer
					 */
					return $this->intSellerId;

				case 'Area':
					/**
					 * Gets the value for intArea (Not Null)
					 * @return integer
					 */
					return $this->intArea;

				case 'LoginId':
					/**
					 * Gets the value for intLoginId 
					 * @return integer
					 */
					return $this->intLoginId;

				case 'MediaSubType':
					/**
					 * Gets the value for intMediaSubType 
					 * @return integer
					 */
					return $this->intMediaSubType;

				case 'Deadline':
					/**
					 * Gets the value for intDeadline 
					 * @return integer
					 */
					return $this->intDeadline;

				case 'StartAge':
					/**
					 * Gets the value for intStartAge (Not Null)
					 * @return integer
					 */
					return $this->intStartAge;

				case 'EndAge':
					/**
					 * Gets the value for intEndAge (Not Null)
					 * @return integer
					 */
					return $this->intEndAge;

				case 'Sex':
					/**
					 * Gets the value for strSex (Not Null)
					 * @return string
					 */
					return $this->strSex;

				case 'Sectors':
					/**
					 * Gets the value for intSectors (Not Null)
					 * @return integer
					 */
					return $this->intSectors;

				case 'Salaries':
					/**
					 * Gets the value for intSalaries (Not Null)
					 * @return integer
					 */
					return $this->intSalaries;

				case 'Educations':
					/**
					 * Gets the value for intEducations (Not Null)
					 * @return integer
					 */
					return $this->intEducations;

				case 'Name':
					/**
					 * Gets the value for strName (Not Null)
					 * @return string
					 */
					return $this->strName;

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

				case 'PermissionMode':
					/**
					 * Gets the value for strPermissionMode 
					 * @return string
					 */
					return $this->strPermissionMode;

				case 'PublicationDate':
					/**
					 * Gets the value for dttPublicationDate 
					 * @return QDateTime
					 */
					return $this->dttPublicationDate;


				///////////////////
				// Member Objects
				///////////////////
				case 'Seller':
					/**
					 * Gets the value for the Seller object referenced by intSellerId (Not Null)
					 * @return Seller
					 */
					try {
						if ((!$this->objSeller) && (!is_null($this->intSellerId)))
							$this->objSeller = Seller::Load($this->intSellerId);
						return $this->objSeller;
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Login':
					/**
					 * Gets the value for the Login object referenced by intLoginId 
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
				case 'Type':
					/**
					 * Sets the value for strType (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strType = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'MediaType':
					/**
					 * Sets the value for intMediaType (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intMediaType = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Reach':
					/**
					 * Sets the value for intReach (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intReach = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Price':
					/**
					 * Sets the value for intPrice (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intPrice = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Description':
					/**
					 * Sets the value for strDescription (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strDescription = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'SellerId':
					/**
					 * Sets the value for intSellerId (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						$this->objSeller = null;
						return ($this->intSellerId = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Area':
					/**
					 * Sets the value for intArea (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intArea = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'LoginId':
					/**
					 * Sets the value for intLoginId 
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

				case 'Deadline':
					/**
					 * Sets the value for intDeadline 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intDeadline = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'StartAge':
					/**
					 * Sets the value for intStartAge (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intStartAge = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'EndAge':
					/**
					 * Sets the value for intEndAge (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intEndAge = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Sex':
					/**
					 * Sets the value for strSex (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strSex = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Sectors':
					/**
					 * Sets the value for intSectors (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intSectors = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Salaries':
					/**
					 * Sets the value for intSalaries (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intSalaries = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Educations':
					/**
					 * Sets the value for intEducations (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intEducations = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Name':
					/**
					 * Sets the value for strName (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strName = QType::Cast($mixValue, QType::String));
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

				case 'PermissionMode':
					/**
					 * Sets the value for strPermissionMode 
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strPermissionMode = QType::Cast($mixValue, QType::String));
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
				case 'Seller':
					/**
					 * Sets the value for the Seller object referenced by intSellerId (Not Null)
					 * @param Seller $mixValue
					 * @return Seller
					 */
					if (is_null($mixValue)) {
						$this->intSellerId = null;
						$this->objSeller = null;
						return null;
					} else {
						// Make sure $mixValue actually is a Seller object
						try {
							$mixValue = QType::Cast($mixValue, 'Seller');
						} catch (QInvalidCastException $objExc) {
							$objExc->IncrementOffset();
							throw $objExc;
						} 

						// Make sure $mixValue is a SAVED Seller object
						if (is_null($mixValue->Id))
							throw new QCallerException('Unable to set an unsaved Seller for this Ad');

						// Update Local Member Variables
						$this->objSeller = $mixValue;
						$this->intSellerId = $mixValue->Id;

						// Return $mixValue
						return $mixValue;
					}
					break;

				case 'Login':
					/**
					 * Sets the value for the Login object referenced by intLoginId 
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
							throw new QCallerException('Unable to set an unsaved Login for this Ad');

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

			
		
		// Related Objects' Methods for Bid
		//-------------------------------------------------------------------
		
		/**
		 * Gets all associated Bids as an array of Bid objects
		 * @param string $strOrderBy
		 * @param string $strLimit 
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Bid[]
		*/ 
		public function GetBidArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Bid::LoadArrayByAdId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated Bids
		 * @return int
		*/ 
		public function CountBids() {
			if ((is_null($this->intId)))
				return 0;

			return Bid::CountByAdId($this->intId);
		}

		/**
		 * Associates a Bid
		 * @param Bid $objBid
		 * @return void
		*/ 
		public function AssociateBid(Bid $objBid) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateBid on this unsaved Ad.');
			if ((is_null($objBid->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateBid on this Ad with an unsaved Bid.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`bid`
				SET
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objBid->Id) . '
			');
		}

		/**
		 * Unassociates a Bid
		 * @param Bid $objBid
		 * @return void
		*/ 
		public function UnassociateBid(Bid $objBid) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Ad.');
			if ((is_null($objBid->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this Ad with an unsaved Bid.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`bid`
				SET
					`ad_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objBid->Id) . ' AND
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all Bids
		 * @return void
		*/ 
		public function UnassociateAllBids() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`bid`
				SET
					`ad_id` = null
				WHERE
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated Bid
		 * @param Bid $objBid
		 * @return void
		*/ 
		public function DeleteAssociatedBid(Bid $objBid) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Ad.');
			if ((is_null($objBid->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this Ad with an unsaved Bid.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`bid`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objBid->Id) . ' AND
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated Bids
		 * @return void
		*/ 
		public function DeleteAllBids() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`bid`
				WHERE
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
		
		// Related Objects' Methods for SellerAsCache
		//-------------------------------------------------------------------
		
		/**
		 * Gets all associated SellersAsCache as an array of Seller objects
		 * @param string $strOrderBy
		 * @param string $strLimit 
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Seller[]
		*/ 
		public function GetSellerAsCacheArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Seller::LoadArrayByCacheAdId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated SellersAsCache
		 * @return int
		*/ 
		public function CountSellersAsCache() {
			if ((is_null($this->intId)))
				return 0;

			return Seller::CountByCacheAdId($this->intId);
		}

		/**
		 * Associates a SellerAsCache
		 * @param Seller $objSeller
		 * @return void
		*/ 
		public function AssociateSellerAsCache(Seller $objSeller) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSellerAsCache on this unsaved Ad.');
			if ((is_null($objSeller->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSellerAsCache on this Ad with an unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`seller`
				SET
					`cache_ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objSeller->Id) . '
			');
		}

		/**
		 * Unassociates a SellerAsCache
		 * @param Seller $objSeller
		 * @return void
		*/ 
		public function UnassociateSellerAsCache(Seller $objSeller) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSellerAsCache on this unsaved Ad.');
			if ((is_null($objSeller->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSellerAsCache on this Ad with an unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`seller`
				SET
					`cache_ad_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objSeller->Id) . ' AND
					`cache_ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all SellersAsCache
		 * @return void
		*/ 
		public function UnassociateAllSellersAsCache() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSellerAsCache on this unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`seller`
				SET
					`cache_ad_id` = null
				WHERE
					`cache_ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated SellerAsCache
		 * @param Seller $objSeller
		 * @return void
		*/ 
		public function DeleteAssociatedSellerAsCache(Seller $objSeller) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSellerAsCache on this unsaved Ad.');
			if ((is_null($objSeller->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSellerAsCache on this Ad with an unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`seller`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objSeller->Id) . ' AND
					`cache_ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated SellersAsCache
		 * @return void
		*/ 
		public function DeleteAllSellersAsCache() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSellerAsCache on this unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`seller`
				WHERE
					`cache_ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
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

			return Keyword::LoadArrayByAd($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Keywords
		 * @return int
		*/ 
		public function CountKeywords() {
			if ((is_null($this->intId)))
				return 0;

			return Keyword::CountByAd($this->intId);
		}

		/**
		 * Associates a Keyword
		 * @param Keyword $objKeyword
		 * @return void
		*/ 
		public function AssociateKeyword(Keyword $objKeyword) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateKeyword on this unsaved Ad.');
			if ((is_null($objKeyword->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateKeyword on this Ad with an unsaved Keyword.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `ad_keyword_assn` (
					`ad_id`,
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
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateKeyword on this unsaved Ad.');
			if ((is_null($objKeyword->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateKeyword on this Ad with an unsaved Keyword.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_keyword_assn`
				WHERE
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`keyword_id` = ' . $objDatabase->SqlVariable($objKeyword->Id) . '
			');
		}

		/**
		 * Unassociates all Keywords
		 * @return void
		*/ 
		public function UnassociateAllKeywords() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllKeywordArray on this unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_keyword_assn`
				WHERE
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}
			
		// Related Many-to-Many Objects' Methods for Network
		//-------------------------------------------------------------------

		/**
		 * Gets all many-to-many associated Networks as an array of Network objects
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Network[]
		*/ 
		public function GetNetworkArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Network::LoadArrayByAd($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Networks
		 * @return int
		*/ 
		public function CountNetworks() {
			if ((is_null($this->intId)))
				return 0;

			return Network::CountByAd($this->intId);
		}

		/**
		 * Associates a Network
		 * @param Network $objNetwork
		 * @return void
		*/ 
		public function AssociateNetwork(Network $objNetwork) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetwork on this unsaved Ad.');
			if ((is_null($objNetwork->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetwork on this Ad with an unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `ad_network_assn` (
					`ad_id`,
					`network_id`
				) VALUES (
					' . $objDatabase->SqlVariable($this->intId) . ',
					' . $objDatabase->SqlVariable($objNetwork->Id) . '
				)
			');
		}

		/**
		 * Unassociates a Network
		 * @param Network $objNetwork
		 * @return void
		*/ 
		public function UnassociateNetwork(Network $objNetwork) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this unsaved Ad.');
			if ((is_null($objNetwork->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this Ad with an unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_network_assn`
				WHERE
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`network_id` = ' . $objDatabase->SqlVariable($objNetwork->Id) . '
			');
		}

		/**
		 * Unassociates all Networks
		 * @return void
		*/ 
		public function UnassociateAllNetworks() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllNetworkArray on this unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Ad::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_network_assn`
				WHERE
					`ad_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}





		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column ad.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column ad.type
		 * @var string strType
		 */
		protected $strType;

		/**
		 * Protected member variable that maps to the database column ad.media_type
		 * @var integer intMediaType
		 */
		protected $intMediaType;

		/**
		 * Protected member variable that maps to the database column ad.reach
		 * @var integer intReach
		 */
		protected $intReach;

		/**
		 * Protected member variable that maps to the database column ad.price
		 * @var integer intPrice
		 */
		protected $intPrice;

		/**
		 * Protected member variable that maps to the database column ad.description
		 * @var string strDescription
		 */
		protected $strDescription;

		/**
		 * Protected member variable that maps to the database column ad.seller_id
		 * @var integer intSellerId
		 */
		protected $intSellerId;

		/**
		 * Protected member variable that maps to the database column ad.area
		 * @var integer intArea
		 */
		protected $intArea;

		/**
		 * Protected member variable that maps to the database column ad.login_id
		 * @var integer intLoginId
		 */
		protected $intLoginId;

		/**
		 * Protected member variable that maps to the database column ad.media_sub_type
		 * @var integer intMediaSubType
		 */
		protected $intMediaSubType;

		/**
		 * Protected member variable that maps to the database column ad.deadline
		 * @var integer intDeadline
		 */
		protected $intDeadline;

		/**
		 * Protected member variable that maps to the database column ad.start_age
		 * @var integer intStartAge
		 */
		protected $intStartAge;

		/**
		 * Protected member variable that maps to the database column ad.end_age
		 * @var integer intEndAge
		 */
		protected $intEndAge;

		/**
		 * Protected member variable that maps to the database column ad.sex
		 * @var string strSex
		 */
		protected $strSex;

		/**
		 * Protected member variable that maps to the database column ad.sectors
		 * @var integer intSectors
		 */
		protected $intSectors;

		/**
		 * Protected member variable that maps to the database column ad.salaries
		 * @var integer intSalaries
		 */
		protected $intSalaries;

		/**
		 * Protected member variable that maps to the database column ad.educations
		 * @var integer intEducations
		 */
		protected $intEducations;

		/**
		 * Protected member variable that maps to the database column ad.name
		 * @var string strName
		 */
		protected $strName;

		/**
		 * Protected member variable that maps to the database column ad.sub_area
		 * @var integer intSubArea
		 */
		protected $intSubArea;

		/**
		 * Protected member variable that maps to the database column ad.sub_sub_area
		 * @var integer intSubSubArea
		 */
		protected $intSubSubArea;

		/**
		 * Protected member variable that maps to the database column ad.permission_mode
		 * @var string strPermissionMode
		 */
		protected $strPermissionMode;

		/**
		 * Protected member variable that maps to the database column ad.publication_date
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
		 * in the database column ad.seller_id.
		 *
		 * NOTE: Always use the Seller property getter to correctly retrieve this Seller object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var Seller objSeller
		 */
		protected $objSeller;

		/**
		 * Protected member variable that contains the object pointed by the reference
		 * in the database column ad.login_id.
		 *
		 * NOTE: Always use the Login property getter to correctly retrieve this Login object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var Login objLogin
		 */
		protected $objLogin;





		////////////////////////////////////////
		// COLUMN CONSTANTS for OBJECT EXPANSION
		////////////////////////////////////////
		const ExpandSeller = 'seller_id';
		const ExpandLogin = 'login_id';




		////////////////////////////////////////
		// METHODS for WEB SERVICES
		////////////////////////////////////////
		public static function GetSoapComplexTypeXml() {
			$strToReturn = '<complexType name="Ad"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="Type" type="xsd:string"/>';
			$strToReturn .= '<element name="MediaType" type="xsd:int"/>';
			$strToReturn .= '<element name="Reach" type="xsd:int"/>';
			$strToReturn .= '<element name="Price" type="xsd:int"/>';
			$strToReturn .= '<element name="Description" type="xsd:string"/>';
			$strToReturn .= '<element name="Seller" type="xsd1:Seller"/>';
			$strToReturn .= '<element name="Area" type="xsd:int"/>';
			$strToReturn .= '<element name="Login" type="xsd1:Login"/>';
			$strToReturn .= '<element name="MediaSubType" type="xsd:int"/>';
			$strToReturn .= '<element name="Deadline" type="xsd:int"/>';
			$strToReturn .= '<element name="StartAge" type="xsd:int"/>';
			$strToReturn .= '<element name="EndAge" type="xsd:int"/>';
			$strToReturn .= '<element name="Sex" type="xsd:string"/>';
			$strToReturn .= '<element name="Sectors" type="xsd:int"/>';
			$strToReturn .= '<element name="Salaries" type="xsd:int"/>';
			$strToReturn .= '<element name="Educations" type="xsd:int"/>';
			$strToReturn .= '<element name="Name" type="xsd:string"/>';
			$strToReturn .= '<element name="SubArea" type="xsd:int"/>';
			$strToReturn .= '<element name="SubSubArea" type="xsd:int"/>';
			$strToReturn .= '<element name="PermissionMode" type="xsd:string"/>';
			$strToReturn .= '<element name="PublicationDate" type="xsd:dateTime"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('Ad', $strComplexTypeArray)) {
				$strComplexTypeArray['Ad'] = Ad::GetSoapComplexTypeXml();
				Seller::AlterSoapComplexTypeArray($strComplexTypeArray);
				Login::AlterSoapComplexTypeArray($strComplexTypeArray);
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, Ad::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new Ad();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if (property_exists($objSoapObject, 'Type'))
				$objToReturn->strType = $objSoapObject->Type;
			if (property_exists($objSoapObject, 'MediaType'))
				$objToReturn->intMediaType = $objSoapObject->MediaType;
			if (property_exists($objSoapObject, 'Reach'))
				$objToReturn->intReach = $objSoapObject->Reach;
			if (property_exists($objSoapObject, 'Price'))
				$objToReturn->intPrice = $objSoapObject->Price;
			if (property_exists($objSoapObject, 'Description'))
				$objToReturn->strDescription = $objSoapObject->Description;
			if ((property_exists($objSoapObject, 'Seller')) &&
				($objSoapObject->Seller))
				$objToReturn->Seller = Seller::GetObjectFromSoapObject($objSoapObject->Seller);
			if (property_exists($objSoapObject, 'Area'))
				$objToReturn->intArea = $objSoapObject->Area;
			if ((property_exists($objSoapObject, 'Login')) &&
				($objSoapObject->Login))
				$objToReturn->Login = Login::GetObjectFromSoapObject($objSoapObject->Login);
			if (property_exists($objSoapObject, 'MediaSubType'))
				$objToReturn->intMediaSubType = $objSoapObject->MediaSubType;
			if (property_exists($objSoapObject, 'Deadline'))
				$objToReturn->intDeadline = $objSoapObject->Deadline;
			if (property_exists($objSoapObject, 'StartAge'))
				$objToReturn->intStartAge = $objSoapObject->StartAge;
			if (property_exists($objSoapObject, 'EndAge'))
				$objToReturn->intEndAge = $objSoapObject->EndAge;
			if (property_exists($objSoapObject, 'Sex'))
				$objToReturn->strSex = $objSoapObject->Sex;
			if (property_exists($objSoapObject, 'Sectors'))
				$objToReturn->intSectors = $objSoapObject->Sectors;
			if (property_exists($objSoapObject, 'Salaries'))
				$objToReturn->intSalaries = $objSoapObject->Salaries;
			if (property_exists($objSoapObject, 'Educations'))
				$objToReturn->intEducations = $objSoapObject->Educations;
			if (property_exists($objSoapObject, 'Name'))
				$objToReturn->strName = $objSoapObject->Name;
			if (property_exists($objSoapObject, 'SubArea'))
				$objToReturn->intSubArea = $objSoapObject->SubArea;
			if (property_exists($objSoapObject, 'SubSubArea'))
				$objToReturn->intSubSubArea = $objSoapObject->SubSubArea;
			if (property_exists($objSoapObject, 'PermissionMode'))
				$objToReturn->strPermissionMode = $objSoapObject->PermissionMode;
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
				array_push($objArrayToReturn, Ad::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			if ($objObject->objSeller)
				$objObject->objSeller = Seller::GetSoapObjectFromObject($objObject->objSeller, false);
			else if (!$blnBindRelatedObjects)
				$objObject->intSellerId = null;
			if ($objObject->objLogin)
				$objObject->objLogin = Login::GetSoapObjectFromObject($objObject->objLogin, false);
			else if (!$blnBindRelatedObjects)
				$objObject->intLoginId = null;
			if ($objObject->dttPublicationDate)
				$objObject->dttPublicationDate = $objObject->dttPublicationDate->__toString(QDateTime::FormatSoap);
			return $objObject;
		}
	}
?>