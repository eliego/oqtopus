<?php
	/**
	 * The abstract SellerGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the Seller subclass which
	 * extends this SellerGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the Seller class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class SellerGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a Seller from PK Info
		 * @param integer $intId
		 * @return Seller
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`seller_name`,
					`name`,
					`address`,
					`phone`,
					`email`,
					`organization_number`,
					`cache_ad_id`,
					`postal`,
					`city`,
					`mail_on_bid`,
					`mail_on_app`,
					`description`
				FROM
					`seller`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Seller::InstantiateDbRow($objDbResult->GetNextRow());
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
				$objQueryExpansion = new QQueryExpansion('Seller', 'seller', $objExpansionMap);
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
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `seller` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`seller_name` AS `%s__%s__seller_name`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`name` AS `%s__%s__name`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`address` AS `%s__%s__address`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`phone` AS `%s__%s__phone`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`email` AS `%s__%s__email`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`organization_number` AS `%s__%s__organization_number`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`cache_ad_id` AS `%s__%s__cache_ad_id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`postal` AS `%s__%s__postal`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`city` AS `%s__%s__city`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`mail_on_bid` AS `%s__%s__mail_on_bid`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`mail_on_app` AS `%s__%s__mail_on_app`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`description` AS `%s__%s__description`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$strParentAlias = $strParentAlias . '__' . $strAlias;
			}

			if (is_array($objExpansionMap))
				foreach ($objExpansionMap as $strKey=>$objValue) {
					switch ($strKey) {
						case 'cache_ad_id':
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
		 * Load all Sellers
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Seller[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`seller`.`id` AS `id`,
					`seller`.`seller_name` AS `seller_name`,
					`seller`.`name` AS `name`,
					`seller`.`address` AS `address`,
					`seller`.`phone` AS `phone`,
					`seller`.`email` AS `email`,
					`seller`.`organization_number` AS `organization_number`,
					`seller`.`cache_ad_id` AS `cache_ad_id`,
					`seller`.`postal` AS `postal`,
					`seller`.`city` AS `city`,
					`seller`.`mail_on_bid` AS `mail_on_bid`,
					`seller`.`mail_on_app` AS `mail_on_app`,
					`seller`.`description` AS `description`
					%s
				FROM
					`seller` AS `seller`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Seller::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all Sellers
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`seller`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a Seller from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this Seller::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return Seller
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the Seller object
			$objToReturn = new Seller();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->strSellerName = $objDbRow->GetColumn($strAliasPrefix . 'seller_name', 'VarChar');
			$objToReturn->strName = $objDbRow->GetColumn($strAliasPrefix . 'name', 'VarChar');
			$objToReturn->strAddress = $objDbRow->GetColumn($strAliasPrefix . 'address', 'VarChar');
			$objToReturn->strPhone = $objDbRow->GetColumn($strAliasPrefix . 'phone', 'VarChar');
			$objToReturn->strEmail = $objDbRow->GetColumn($strAliasPrefix . 'email', 'VarChar');
			$objToReturn->strOrganizationNumber = $objDbRow->GetColumn($strAliasPrefix . 'organization_number', 'VarChar');
			$objToReturn->intCacheAdId = $objDbRow->GetColumn($strAliasPrefix . 'cache_ad_id', 'Integer');
			$objToReturn->strPostal = $objDbRow->GetColumn($strAliasPrefix . 'postal', 'VarChar');
			$objToReturn->strCity = $objDbRow->GetColumn($strAliasPrefix . 'city', 'VarChar');
			$objToReturn->intMailOnBid = $objDbRow->GetColumn($strAliasPrefix . 'mail_on_bid', 'Integer');
			$objToReturn->intMailOnApp = $objDbRow->GetColumn($strAliasPrefix . 'mail_on_app', 'Integer');
			$objToReturn->strDescription = $objDbRow->GetColumn($strAliasPrefix . 'description', 'Blob');

			// Instantiate Virtual Attributes
			foreach ($objDbRow->GetColumnNameArray() as $strColumnName => $mixValue) {
				$strVirtualPrefix = $strAliasPrefix . '__';
				$strVirtualPrefixLength = strlen($strVirtualPrefix);
				if (substr($strColumnName, 0, $strVirtualPrefixLength) == $strVirtualPrefix)
					$objToReturn->__strVirtualAttributeArray[substr($strColumnName, $strVirtualPrefixLength)] = $mixValue;
			}

			// Prepare to Check for Early Binding
			if (!$strAliasPrefix)
				$strAliasPrefix = 'seller__';

			// Check for CacheAd Early Binding
			if (!is_null($objDbRow->GetColumn($strAliasPrefix . 'cache_ad_id__id')))
				$objToReturn->objCacheAd = Ad::InstantiateDbRow($objDbRow, $strAliasPrefix . 'cache_ad_id__');

			
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
		 * Instantiate an array of Sellers from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return Seller[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, Seller::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load a single Seller object,
		 * by SellerName Index(es)
		 * @param string $strSellerName
		 * @return Seller
		*/
		public static function LoadBySellerName($strSellerName) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strSellerName = $objDatabase->SqlVariable($strSellerName, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`seller_name`,
					`name`,
					`address`,
					`phone`,
					`email`,
					`organization_number`,
					`cache_ad_id`,
					`postal`,
					`city`,
					`mail_on_bid`,
					`mail_on_app`,
					`description`
				FROM
					`seller`
				WHERE
					`seller_name` %s', $strSellerName);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Seller::InstantiateDbRow($objDbResult->GetNextRow());
		}
			
		/**
		 * Load a single Seller object,
		 * by OrganizationNumber Index(es)
		 * @param string $strOrganizationNumber
		 * @return Seller
		*/
		public static function LoadByOrganizationNumber($strOrganizationNumber) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strOrganizationNumber = $objDatabase->SqlVariable($strOrganizationNumber, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`seller_name`,
					`name`,
					`address`,
					`phone`,
					`email`,
					`organization_number`,
					`cache_ad_id`,
					`postal`,
					`city`,
					`mail_on_bid`,
					`mail_on_app`,
					`description`
				FROM
					`seller`
				WHERE
					`organization_number` %s', $strOrganizationNumber);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Seller::InstantiateDbRow($objDbResult->GetNextRow());
		}
			
		/**
		 * Load an array of Seller objects,
		 * by CacheAdId Index(es)
		 * @param integer $intCacheAdId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Seller[]
		*/
		public static function LoadArrayByCacheAdId($intCacheAdId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intCacheAdId = $objDatabase->SqlVariable($intCacheAdId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`seller`.`id` AS `id`,
					`seller`.`seller_name` AS `seller_name`,
					`seller`.`name` AS `name`,
					`seller`.`address` AS `address`,
					`seller`.`phone` AS `phone`,
					`seller`.`email` AS `email`,
					`seller`.`organization_number` AS `organization_number`,
					`seller`.`cache_ad_id` AS `cache_ad_id`,
					`seller`.`postal` AS `postal`,
					`seller`.`city` AS `city`,
					`seller`.`mail_on_bid` AS `mail_on_bid`,
					`seller`.`mail_on_app` AS `mail_on_app`,
					`seller`.`description` AS `description`
					%s
				FROM
					`seller` AS `seller`
					%s
				WHERE
					`seller`.`cache_ad_id` %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intCacheAdId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Seller::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Sellers
		 * by CacheAdId Index(es)
		 * @param integer $intCacheAdId
		 * @return int
		*/
		public static function CountByCacheAdId($intCacheAdId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intCacheAdId = $objDatabase->SqlVariable($intCacheAdId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`seller`
				WHERE
					`cache_ad_id` %s', $intCacheAdId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////
			/**
		 * Load an array of Login objects for a given Login
		 * via the login_seller_assn table
		 * @param integer $intLoginId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Login[]
		*/
		public static function LoadArrayByLogin($intLoginId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`seller`.`id` AS `id`,
					`seller`.`seller_name` AS `seller_name`,
					`seller`.`name` AS `name`,
					`seller`.`address` AS `address`,
					`seller`.`phone` AS `phone`,
					`seller`.`email` AS `email`,
					`seller`.`organization_number` AS `organization_number`,
					`seller`.`cache_ad_id` AS `cache_ad_id`,
					`seller`.`postal` AS `postal`,
					`seller`.`city` AS `city`,
					`seller`.`mail_on_bid` AS `mail_on_bid`,
					`seller`.`mail_on_app` AS `mail_on_app`,
					`seller`.`description` AS `description`
					%s
				FROM
					(`seller` AS `seller`,
					`login_seller_assn` AS `login_seller_assn`)
					%s
				WHERE
					`login_seller_assn`.`seller_id` = `seller`.`id` AND
					`login_seller_assn`.`login_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intLoginId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Seller::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Sellers for a given Login
		 * via the login_seller_assn table
		 * @param integer $intLoginId
		 * @return int
		*/
		public static function CountByLogin($intLoginId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Seller::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLoginId = $objDatabase->SqlVariable($intLoginId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`seller`,
					`login_seller_assn`
				WHERE
					`login_seller_assn`.`seller_id` = `seller`.`id` AND
					`login_seller_assn`.`login_id` = %s
			', $intLoginId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this Seller
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `seller` (
							`seller_name`,
							`name`,
							`address`,
							`phone`,
							`email`,
							`organization_number`,
							`cache_ad_id`,
							`postal`,
							`city`,
							`mail_on_bid`,
							`mail_on_app`,
							`description`
						) VALUES (
							' . $objDatabase->SqlVariable($this->strSellerName) . ',
							' . $objDatabase->SqlVariable($this->strName) . ',
							' . $objDatabase->SqlVariable($this->strAddress) . ',
							' . $objDatabase->SqlVariable($this->strPhone) . ',
							' . $objDatabase->SqlVariable($this->strEmail) . ',
							' . $objDatabase->SqlVariable($this->strOrganizationNumber) . ',
							' . $objDatabase->SqlVariable($this->intCacheAdId) . ',
							' . $objDatabase->SqlVariable($this->strPostal) . ',
							' . $objDatabase->SqlVariable($this->strCity) . ',
							' . $objDatabase->SqlVariable($this->intMailOnBid) . ',
							' . $objDatabase->SqlVariable($this->intMailOnApp) . ',
							' . $objDatabase->SqlVariable($this->strDescription) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('seller', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`seller`
						SET
							`seller_name` = ' . $objDatabase->SqlVariable($this->strSellerName) . ',
							`name` = ' . $objDatabase->SqlVariable($this->strName) . ',
							`address` = ' . $objDatabase->SqlVariable($this->strAddress) . ',
							`phone` = ' . $objDatabase->SqlVariable($this->strPhone) . ',
							`email` = ' . $objDatabase->SqlVariable($this->strEmail) . ',
							`organization_number` = ' . $objDatabase->SqlVariable($this->strOrganizationNumber) . ',
							`cache_ad_id` = ' . $objDatabase->SqlVariable($this->intCacheAdId) . ',
							`postal` = ' . $objDatabase->SqlVariable($this->strPostal) . ',
							`city` = ' . $objDatabase->SqlVariable($this->strCity) . ',
							`mail_on_bid` = ' . $objDatabase->SqlVariable($this->intMailOnBid) . ',
							`mail_on_app` = ' . $objDatabase->SqlVariable($this->intMailOnApp) . ',
							`description` = ' . $objDatabase->SqlVariable($this->strDescription) . '
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
		 * Delete this Seller
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this Seller with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`seller`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all Sellers
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`seller`');
		}

		/**
		 * Truncate seller table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `seller`');
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

				case 'SellerName':
					/**
					 * Gets the value for strSellerName (Unique)
					 * @return string
					 */
					return $this->strSellerName;

				case 'Name':
					/**
					 * Gets the value for strName (Not Null)
					 * @return string
					 */
					return $this->strName;

				case 'Address':
					/**
					 * Gets the value for strAddress (Not Null)
					 * @return string
					 */
					return $this->strAddress;

				case 'Phone':
					/**
					 * Gets the value for strPhone (Not Null)
					 * @return string
					 */
					return $this->strPhone;

				case 'Email':
					/**
					 * Gets the value for strEmail (Not Null)
					 * @return string
					 */
					return $this->strEmail;

				case 'OrganizationNumber':
					/**
					 * Gets the value for strOrganizationNumber (Unique)
					 * @return string
					 */
					return $this->strOrganizationNumber;

				case 'CacheAdId':
					/**
					 * Gets the value for intCacheAdId 
					 * @return integer
					 */
					return $this->intCacheAdId;

				case 'Postal':
					/**
					 * Gets the value for strPostal (Not Null)
					 * @return string
					 */
					return $this->strPostal;

				case 'City':
					/**
					 * Gets the value for strCity (Not Null)
					 * @return string
					 */
					return $this->strCity;

				case 'MailOnBid':
					/**
					 * Gets the value for intMailOnBid (Not Null)
					 * @return integer
					 */
					return $this->intMailOnBid;

				case 'MailOnApp':
					/**
					 * Gets the value for intMailOnApp (Not Null)
					 * @return integer
					 */
					return $this->intMailOnApp;

				case 'Description':
					/**
					 * Gets the value for strDescription (Not Null)
					 * @return string
					 */
					return $this->strDescription;


				///////////////////
				// Member Objects
				///////////////////
				case 'CacheAd':
					/**
					 * Gets the value for the Ad object referenced by intCacheAdId 
					 * @return Ad
					 */
					try {
						if ((!$this->objCacheAd) && (!is_null($this->intCacheAdId)))
							$this->objCacheAd = Ad::Load($this->intCacheAdId);
						return $this->objCacheAd;
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
				case 'SellerName':
					/**
					 * Sets the value for strSellerName (Unique)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strSellerName = QType::Cast($mixValue, QType::String));
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

				case 'Address':
					/**
					 * Sets the value for strAddress (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strAddress = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Phone':
					/**
					 * Sets the value for strPhone (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strPhone = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Email':
					/**
					 * Sets the value for strEmail (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strEmail = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'OrganizationNumber':
					/**
					 * Sets the value for strOrganizationNumber (Unique)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strOrganizationNumber = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'CacheAdId':
					/**
					 * Sets the value for intCacheAdId 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						$this->objCacheAd = null;
						return ($this->intCacheAdId = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Postal':
					/**
					 * Sets the value for strPostal (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strPostal = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'City':
					/**
					 * Sets the value for strCity (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strCity = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'MailOnBid':
					/**
					 * Sets the value for intMailOnBid (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intMailOnBid = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'MailOnApp':
					/**
					 * Sets the value for intMailOnApp (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intMailOnApp = QType::Cast($mixValue, QType::Integer));
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


				///////////////////
				// Member Objects
				///////////////////
				case 'CacheAd':
					/**
					 * Sets the value for the Ad object referenced by intCacheAdId 
					 * @param Ad $mixValue
					 * @return Ad
					 */
					if (is_null($mixValue)) {
						$this->intCacheAdId = null;
						$this->objCacheAd = null;
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
							throw new QCallerException('Unable to set an unsaved CacheAd for this Seller');

						// Update Local Member Variables
						$this->objCacheAd = $mixValue;
						$this->intCacheAdId = $mixValue->Id;

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

			
		
		// Related Objects' Methods for Ad
		//-------------------------------------------------------------------
		
		/**
		 * Gets all associated Ads as an array of Ad objects
		 * @param string $strOrderBy
		 * @param string $strLimit 
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		*/ 
		public function GetAdArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Ad::LoadArrayBySellerId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated Ads
		 * @return int
		*/ 
		public function CountAds() {
			if ((is_null($this->intId)))
				return 0;

			return Ad::CountBySellerId($this->intId);
		}

		/**
		 * Associates a Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function AssociateAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this unsaved Seller.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this Seller with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`ad`
				SET
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objAd->Id) . '
			');
		}

		/**
		 * Unassociates a Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function UnassociateAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Seller.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this Seller with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`ad`
				SET
					`seller_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objAd->Id) . ' AND
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all Ads
		 * @return void
		*/ 
		public function UnassociateAllAds() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`ad`
				SET
					`seller_id` = null
				WHERE
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function DeleteAssociatedAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Seller.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this Seller with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objAd->Id) . ' AND
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated Ads
		 * @return void
		*/ 
		public function DeleteAllAds() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad`
				WHERE
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
		
		// Related Objects' Methods for Network
		//-------------------------------------------------------------------
		
		/**
		 * Gets all associated Networks as an array of Network objects
		 * @param string $strOrderBy
		 * @param string $strLimit 
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Network[]
		*/ 
		public function GetNetworkArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Network::LoadArrayBySellerId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated Networks
		 * @return int
		*/ 
		public function CountNetworks() {
			if ((is_null($this->intId)))
				return 0;

			return Network::CountBySellerId($this->intId);
		}

		/**
		 * Associates a Network
		 * @param Network $objNetwork
		 * @return void
		*/ 
		public function AssociateNetwork(Network $objNetwork) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetwork on this unsaved Seller.');
			if ((is_null($objNetwork->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetwork on this Seller with an unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network`
				SET
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetwork->Id) . '
			');
		}

		/**
		 * Unassociates a Network
		 * @param Network $objNetwork
		 * @return void
		*/ 
		public function UnassociateNetwork(Network $objNetwork) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this unsaved Seller.');
			if ((is_null($objNetwork->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this Seller with an unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network`
				SET
					`seller_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetwork->Id) . ' AND
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all Networks
		 * @return void
		*/ 
		public function UnassociateAllNetworks() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network`
				SET
					`seller_id` = null
				WHERE
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated Network
		 * @param Network $objNetwork
		 * @return void
		*/ 
		public function DeleteAssociatedNetwork(Network $objNetwork) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this unsaved Seller.');
			if ((is_null($objNetwork->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this Seller with an unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetwork->Id) . ' AND
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated Networks
		 * @return void
		*/ 
		public function DeleteAllNetworks() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetwork on this unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network`
				WHERE
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
		// Related Many-to-Many Objects' Methods for Login
		//-------------------------------------------------------------------

		/**
		 * Gets all many-to-many associated Logins as an array of Login objects
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Login[]
		*/ 
		public function GetLoginArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Login::LoadArrayBySeller($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Logins
		 * @return int
		*/ 
		public function CountLogins() {
			if ((is_null($this->intId)))
				return 0;

			return Login::CountBySeller($this->intId);
		}

		/**
		 * Associates a Login
		 * @param Login $objLogin
		 * @return void
		*/ 
		public function AssociateLogin(Login $objLogin) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateLogin on this unsaved Seller.');
			if ((is_null($objLogin->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateLogin on this Seller with an unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `login_seller_assn` (
					`seller_id`,
					`login_id`
				) VALUES (
					' . $objDatabase->SqlVariable($this->intId) . ',
					' . $objDatabase->SqlVariable($objLogin->Id) . '
				)
			');
		}

		/**
		 * Unassociates a Login
		 * @param Login $objLogin
		 * @return void
		*/ 
		public function UnassociateLogin(Login $objLogin) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateLogin on this unsaved Seller.');
			if ((is_null($objLogin->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateLogin on this Seller with an unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`login_seller_assn`
				WHERE
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($objLogin->Id) . '
			');
		}

		/**
		 * Unassociates all Logins
		 * @return void
		*/ 
		public function UnassociateAllLogins() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllLoginArray on this unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Seller::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`login_seller_assn`
				WHERE
					`seller_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}





		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column seller.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column seller.seller_name
		 * @var string strSellerName
		 */
		protected $strSellerName;

		/**
		 * Protected member variable that maps to the database column seller.name
		 * @var string strName
		 */
		protected $strName;

		/**
		 * Protected member variable that maps to the database column seller.address
		 * @var string strAddress
		 */
		protected $strAddress;

		/**
		 * Protected member variable that maps to the database column seller.phone
		 * @var string strPhone
		 */
		protected $strPhone;

		/**
		 * Protected member variable that maps to the database column seller.email
		 * @var string strEmail
		 */
		protected $strEmail;

		/**
		 * Protected member variable that maps to the database column seller.organization_number
		 * @var string strOrganizationNumber
		 */
		protected $strOrganizationNumber;

		/**
		 * Protected member variable that maps to the database column seller.cache_ad_id
		 * @var integer intCacheAdId
		 */
		protected $intCacheAdId;

		/**
		 * Protected member variable that maps to the database column seller.postal
		 * @var string strPostal
		 */
		protected $strPostal;

		/**
		 * Protected member variable that maps to the database column seller.city
		 * @var string strCity
		 */
		protected $strCity;

		/**
		 * Protected member variable that maps to the database column seller.mail_on_bid
		 * @var integer intMailOnBid
		 */
		protected $intMailOnBid;

		/**
		 * Protected member variable that maps to the database column seller.mail_on_app
		 * @var integer intMailOnApp
		 */
		protected $intMailOnApp;

		/**
		 * Protected member variable that maps to the database column seller.description
		 * @var string strDescription
		 */
		protected $strDescription;

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
		 * in the database column seller.cache_ad_id.
		 *
		 * NOTE: Always use the CacheAd property getter to correctly retrieve this Ad object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var Ad objCacheAd
		 */
		protected $objCacheAd;





		////////////////////////////////////////
		// COLUMN CONSTANTS for OBJECT EXPANSION
		////////////////////////////////////////
		const ExpandCacheAd = 'cache_ad_id';




		////////////////////////////////////////
		// METHODS for WEB SERVICES
		////////////////////////////////////////
		public static function GetSoapComplexTypeXml() {
			$strToReturn = '<complexType name="Seller"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="SellerName" type="xsd:string"/>';
			$strToReturn .= '<element name="Name" type="xsd:string"/>';
			$strToReturn .= '<element name="Address" type="xsd:string"/>';
			$strToReturn .= '<element name="Phone" type="xsd:string"/>';
			$strToReturn .= '<element name="Email" type="xsd:string"/>';
			$strToReturn .= '<element name="OrganizationNumber" type="xsd:string"/>';
			$strToReturn .= '<element name="CacheAd" type="xsd1:Ad"/>';
			$strToReturn .= '<element name="Postal" type="xsd:string"/>';
			$strToReturn .= '<element name="City" type="xsd:string"/>';
			$strToReturn .= '<element name="MailOnBid" type="xsd:int"/>';
			$strToReturn .= '<element name="MailOnApp" type="xsd:int"/>';
			$strToReturn .= '<element name="Description" type="xsd:string"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('Seller', $strComplexTypeArray)) {
				$strComplexTypeArray['Seller'] = Seller::GetSoapComplexTypeXml();
				Ad::AlterSoapComplexTypeArray($strComplexTypeArray);
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, Seller::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new Seller();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if (property_exists($objSoapObject, 'SellerName'))
				$objToReturn->strSellerName = $objSoapObject->SellerName;
			if (property_exists($objSoapObject, 'Name'))
				$objToReturn->strName = $objSoapObject->Name;
			if (property_exists($objSoapObject, 'Address'))
				$objToReturn->strAddress = $objSoapObject->Address;
			if (property_exists($objSoapObject, 'Phone'))
				$objToReturn->strPhone = $objSoapObject->Phone;
			if (property_exists($objSoapObject, 'Email'))
				$objToReturn->strEmail = $objSoapObject->Email;
			if (property_exists($objSoapObject, 'OrganizationNumber'))
				$objToReturn->strOrganizationNumber = $objSoapObject->OrganizationNumber;
			if ((property_exists($objSoapObject, 'CacheAd')) &&
				($objSoapObject->CacheAd))
				$objToReturn->CacheAd = Ad::GetObjectFromSoapObject($objSoapObject->CacheAd);
			if (property_exists($objSoapObject, 'Postal'))
				$objToReturn->strPostal = $objSoapObject->Postal;
			if (property_exists($objSoapObject, 'City'))
				$objToReturn->strCity = $objSoapObject->City;
			if (property_exists($objSoapObject, 'MailOnBid'))
				$objToReturn->intMailOnBid = $objSoapObject->MailOnBid;
			if (property_exists($objSoapObject, 'MailOnApp'))
				$objToReturn->intMailOnApp = $objSoapObject->MailOnApp;
			if (property_exists($objSoapObject, 'Description'))
				$objToReturn->strDescription = $objSoapObject->Description;
			if (property_exists($objSoapObject, '__blnRestored'))
				$objToReturn->__blnRestored = $objSoapObject->__blnRestored;
			return $objToReturn;
		}

		public static function GetSoapArrayFromArray($objArray) {
			if (!$objArray)
				return null;

			$objArrayToReturn = array();

			foreach ($objArray as $objObject)
				array_push($objArrayToReturn, Seller::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			if ($objObject->objCacheAd)
				$objObject->objCacheAd = Ad::GetSoapObjectFromObject($objObject->objCacheAd, false);
			else if (!$blnBindRelatedObjects)
				$objObject->intCacheAdId = null;
			return $objObject;
		}
	}
?>