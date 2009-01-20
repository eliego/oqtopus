<?php
	/**
	 * The abstract LoginGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the Login subclass which
	 * extends this LoginGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the Login class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class LoginGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a Login from PK Info
		 * @param integer $intId
		 * @return Login
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Login::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`password`,
					`role`,
					`name`,
					`address`,
					`phone`,
					`email`,
					`username`,
					`salt`,
					`organization_number`,
					`company_name`,
					`last_login`,
					`postal`,
					`city`,
					`status`,
					`notes`,
					`worthy`,
					`last_worthy_check`,
					`registration_date`
				FROM
					`login`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Login::InstantiateDbRow($objDbResult->GetNextRow());
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
				$objQueryExpansion = new QQueryExpansion('Login', 'login', $objExpansionMap);
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
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `login` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`password` AS `%s__%s__password`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`role` AS `%s__%s__role`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`name` AS `%s__%s__name`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`address` AS `%s__%s__address`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`phone` AS `%s__%s__phone`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`email` AS `%s__%s__email`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`username` AS `%s__%s__username`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`salt` AS `%s__%s__salt`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`organization_number` AS `%s__%s__organization_number`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`company_name` AS `%s__%s__company_name`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`last_login` AS `%s__%s__last_login`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`postal` AS `%s__%s__postal`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`city` AS `%s__%s__city`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`status` AS `%s__%s__status`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`notes` AS `%s__%s__notes`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`worthy` AS `%s__%s__worthy`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`last_worthy_check` AS `%s__%s__last_worthy_check`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`registration_date` AS `%s__%s__registration_date`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

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
		 * Load all Logins
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Login[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Login::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`login`.`id` AS `id`,
					`login`.`password` AS `password`,
					`login`.`role` AS `role`,
					`login`.`name` AS `name`,
					`login`.`address` AS `address`,
					`login`.`phone` AS `phone`,
					`login`.`email` AS `email`,
					`login`.`username` AS `username`,
					`login`.`salt` AS `salt`,
					`login`.`organization_number` AS `organization_number`,
					`login`.`company_name` AS `company_name`,
					`login`.`last_login` AS `last_login`,
					`login`.`postal` AS `postal`,
					`login`.`city` AS `city`,
					`login`.`status` AS `status`,
					`login`.`notes` AS `notes`,
					`login`.`worthy` AS `worthy`,
					`login`.`last_worthy_check` AS `last_worthy_check`,
					`login`.`registration_date` AS `registration_date`
					%s
				FROM
					`login` AS `login`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Login::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all Logins
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`login`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a Login from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this Login::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return Login
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the Login object
			$objToReturn = new Login();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->strPassword = $objDbRow->GetColumn($strAliasPrefix . 'password', 'VarChar');
			$objToReturn->strRole = $objDbRow->GetColumn($strAliasPrefix . 'role', 'VarChar');
			$objToReturn->strName = $objDbRow->GetColumn($strAliasPrefix . 'name', 'VarChar');
			$objToReturn->strAddress = $objDbRow->GetColumn($strAliasPrefix . 'address', 'VarChar');
			$objToReturn->strPhone = $objDbRow->GetColumn($strAliasPrefix . 'phone', 'VarChar');
			$objToReturn->strEmail = $objDbRow->GetColumn($strAliasPrefix . 'email', 'VarChar');
			$objToReturn->strUsername = $objDbRow->GetColumn($strAliasPrefix . 'username', 'VarChar');
			$objToReturn->strSalt = $objDbRow->GetColumn($strAliasPrefix . 'salt', 'VarChar');
			$objToReturn->strOrganizationNumber = $objDbRow->GetColumn($strAliasPrefix . 'organization_number', 'VarChar');
			$objToReturn->strCompanyName = $objDbRow->GetColumn($strAliasPrefix . 'company_name', 'VarChar');
			$objToReturn->dttLastLogin = $objDbRow->GetColumn($strAliasPrefix . 'last_login', 'DateTime');
			$objToReturn->strPostal = $objDbRow->GetColumn($strAliasPrefix . 'postal', 'VarChar');
			$objToReturn->strCity = $objDbRow->GetColumn($strAliasPrefix . 'city', 'VarChar');
			$objToReturn->strStatus = $objDbRow->GetColumn($strAliasPrefix . 'status', 'VarChar');
			$objToReturn->strNotes = $objDbRow->GetColumn($strAliasPrefix . 'notes', 'VarChar');
			$objToReturn->intWorthy = $objDbRow->GetColumn($strAliasPrefix . 'worthy', 'Integer');
			$objToReturn->dttLastWorthyCheck = $objDbRow->GetColumn($strAliasPrefix . 'last_worthy_check', 'DateTime');
			$objToReturn->dttRegistrationDate = $objDbRow->GetColumn($strAliasPrefix . 'registration_date', 'DateTime');

			// Instantiate Virtual Attributes
			foreach ($objDbRow->GetColumnNameArray() as $strColumnName => $mixValue) {
				$strVirtualPrefix = $strAliasPrefix . '__';
				$strVirtualPrefixLength = strlen($strVirtualPrefix);
				if (substr($strColumnName, 0, $strVirtualPrefixLength) == $strVirtualPrefix)
					$objToReturn->__strVirtualAttributeArray[substr($strColumnName, $strVirtualPrefixLength)] = $mixValue;
			}

			// Prepare to Check for Early Binding
			if (!$strAliasPrefix)
				$strAliasPrefix = 'login__';

			
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
		 * Instantiate an array of Logins from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return Login[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, Login::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load a single Login object,
		 * by Username Index(es)
		 * @param string $strUsername
		 * @return Login
		*/
		public static function LoadByUsername($strUsername) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Login::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strUsername = $objDatabase->SqlVariable($strUsername, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`password`,
					`role`,
					`name`,
					`address`,
					`phone`,
					`email`,
					`username`,
					`salt`,
					`organization_number`,
					`company_name`,
					`last_login`,
					`postal`,
					`city`,
					`status`,
					`notes`,
					`worthy`,
					`last_worthy_check`,
					`registration_date`
				FROM
					`login`
				WHERE
					`username` %s', $strUsername);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Login::InstantiateDbRow($objDbResult->GetNextRow());
		}





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////
			/**
		 * Load an array of Seller objects for a given Seller
		 * via the login_seller_assn table
		 * @param integer $intSellerId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Seller[]
		*/
		public static function LoadArrayBySeller($intSellerId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Login::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSellerId = $objDatabase->SqlVariable($intSellerId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`login`.`id` AS `id`,
					`login`.`password` AS `password`,
					`login`.`role` AS `role`,
					`login`.`name` AS `name`,
					`login`.`address` AS `address`,
					`login`.`phone` AS `phone`,
					`login`.`email` AS `email`,
					`login`.`username` AS `username`,
					`login`.`salt` AS `salt`,
					`login`.`organization_number` AS `organization_number`,
					`login`.`company_name` AS `company_name`,
					`login`.`last_login` AS `last_login`,
					`login`.`postal` AS `postal`,
					`login`.`city` AS `city`,
					`login`.`status` AS `status`,
					`login`.`notes` AS `notes`,
					`login`.`worthy` AS `worthy`,
					`login`.`last_worthy_check` AS `last_worthy_check`,
					`login`.`registration_date` AS `registration_date`
					%s
				FROM
					(`login` AS `login`,
					`login_seller_assn` AS `login_seller_assn`)
					%s
				WHERE
					`login_seller_assn`.`login_id` = `login`.`id` AND
					`login_seller_assn`.`seller_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intSellerId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Login::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Logins for a given Seller
		 * via the login_seller_assn table
		 * @param integer $intSellerId
		 * @return int
		*/
		public static function CountBySeller($intSellerId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Login::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSellerId = $objDatabase->SqlVariable($intSellerId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`login`,
					`login_seller_assn`
				WHERE
					`login_seller_assn`.`login_id` = `login`.`id` AND
					`login_seller_assn`.`seller_id` = %s
			', $intSellerId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this Login
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `login` (
							`password`,
							`role`,
							`name`,
							`address`,
							`phone`,
							`email`,
							`username`,
							`salt`,
							`organization_number`,
							`company_name`,
							`last_login`,
							`postal`,
							`city`,
							`status`,
							`notes`,
							`worthy`,
							`last_worthy_check`,
							`registration_date`
						) VALUES (
							' . $objDatabase->SqlVariable($this->strPassword) . ',
							' . $objDatabase->SqlVariable($this->strRole) . ',
							' . $objDatabase->SqlVariable($this->strName) . ',
							' . $objDatabase->SqlVariable($this->strAddress) . ',
							' . $objDatabase->SqlVariable($this->strPhone) . ',
							' . $objDatabase->SqlVariable($this->strEmail) . ',
							' . $objDatabase->SqlVariable($this->strUsername) . ',
							' . $objDatabase->SqlVariable($this->strSalt) . ',
							' . $objDatabase->SqlVariable($this->strOrganizationNumber) . ',
							' . $objDatabase->SqlVariable($this->strCompanyName) . ',
							' . $objDatabase->SqlVariable($this->dttLastLogin) . ',
							' . $objDatabase->SqlVariable($this->strPostal) . ',
							' . $objDatabase->SqlVariable($this->strCity) . ',
							' . $objDatabase->SqlVariable($this->strStatus) . ',
							' . $objDatabase->SqlVariable($this->strNotes) . ',
							' . $objDatabase->SqlVariable($this->intWorthy) . ',
							' . $objDatabase->SqlVariable($this->dttLastWorthyCheck) . ',
							' . $objDatabase->SqlVariable($this->dttRegistrationDate) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('login', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`login`
						SET
							`password` = ' . $objDatabase->SqlVariable($this->strPassword) . ',
							`role` = ' . $objDatabase->SqlVariable($this->strRole) . ',
							`name` = ' . $objDatabase->SqlVariable($this->strName) . ',
							`address` = ' . $objDatabase->SqlVariable($this->strAddress) . ',
							`phone` = ' . $objDatabase->SqlVariable($this->strPhone) . ',
							`email` = ' . $objDatabase->SqlVariable($this->strEmail) . ',
							`username` = ' . $objDatabase->SqlVariable($this->strUsername) . ',
							`salt` = ' . $objDatabase->SqlVariable($this->strSalt) . ',
							`organization_number` = ' . $objDatabase->SqlVariable($this->strOrganizationNumber) . ',
							`company_name` = ' . $objDatabase->SqlVariable($this->strCompanyName) . ',
							`last_login` = ' . $objDatabase->SqlVariable($this->dttLastLogin) . ',
							`postal` = ' . $objDatabase->SqlVariable($this->strPostal) . ',
							`city` = ' . $objDatabase->SqlVariable($this->strCity) . ',
							`status` = ' . $objDatabase->SqlVariable($this->strStatus) . ',
							`notes` = ' . $objDatabase->SqlVariable($this->strNotes) . ',
							`worthy` = ' . $objDatabase->SqlVariable($this->intWorthy) . ',
							`last_worthy_check` = ' . $objDatabase->SqlVariable($this->dttLastWorthyCheck) . ',
							`registration_date` = ' . $objDatabase->SqlVariable($this->dttRegistrationDate) . '
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
		 * Delete this Login
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this Login with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`login`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all Logins
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`login`');
		}

		/**
		 * Truncate login table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `login`');
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

				case 'Password':
					/**
					 * Gets the value for strPassword (Not Null)
					 * @return string
					 */
					return $this->strPassword;

				case 'Role':
					/**
					 * Gets the value for strRole (Not Null)
					 * @return string
					 */
					return $this->strRole;

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

				case 'Username':
					/**
					 * Gets the value for strUsername (Unique)
					 * @return string
					 */
					return $this->strUsername;

				case 'Salt':
					/**
					 * Gets the value for strSalt (Not Null)
					 * @return string
					 */
					return $this->strSalt;

				case 'OrganizationNumber':
					/**
					 * Gets the value for strOrganizationNumber (Not Null)
					 * @return string
					 */
					return $this->strOrganizationNumber;

				case 'CompanyName':
					/**
					 * Gets the value for strCompanyName (Not Null)
					 * @return string
					 */
					return $this->strCompanyName;

				case 'LastLogin':
					/**
					 * Gets the value for dttLastLogin 
					 * @return QDateTime
					 */
					return $this->dttLastLogin;

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

				case 'Status':
					/**
					 * Gets the value for strStatus (Not Null)
					 * @return string
					 */
					return $this->strStatus;

				case 'Notes':
					/**
					 * Gets the value for strNotes 
					 * @return string
					 */
					return $this->strNotes;

				case 'Worthy':
					/**
					 * Gets the value for intWorthy 
					 * @return integer
					 */
					return $this->intWorthy;

				case 'LastWorthyCheck':
					/**
					 * Gets the value for dttLastWorthyCheck 
					 * @return QDateTime
					 */
					return $this->dttLastWorthyCheck;

				case 'RegistrationDate':
					/**
					 * Gets the value for dttRegistrationDate (Not Null)
					 * @return QDateTime
					 */
					return $this->dttRegistrationDate;


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
				case 'Password':
					/**
					 * Sets the value for strPassword (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strPassword = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Role':
					/**
					 * Sets the value for strRole (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strRole = QType::Cast($mixValue, QType::String));
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

				case 'Username':
					/**
					 * Sets the value for strUsername (Unique)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strUsername = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Salt':
					/**
					 * Sets the value for strSalt (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strSalt = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'OrganizationNumber':
					/**
					 * Sets the value for strOrganizationNumber (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strOrganizationNumber = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'CompanyName':
					/**
					 * Sets the value for strCompanyName (Not Null)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strCompanyName = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'LastLogin':
					/**
					 * Sets the value for dttLastLogin 
					 * @param QDateTime $mixValue
					 * @return QDateTime
					 */
					try {
						return ($this->dttLastLogin = QType::Cast($mixValue, QType::DateTime));
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

				case 'Notes':
					/**
					 * Sets the value for strNotes 
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strNotes = QType::Cast($mixValue, QType::String));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Worthy':
					/**
					 * Sets the value for intWorthy 
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intWorthy = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'LastWorthyCheck':
					/**
					 * Sets the value for dttLastWorthyCheck 
					 * @param QDateTime $mixValue
					 * @return QDateTime
					 */
					try {
						return ($this->dttLastWorthyCheck = QType::Cast($mixValue, QType::DateTime));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'RegistrationDate':
					/**
					 * Sets the value for dttRegistrationDate (Not Null)
					 * @param QDateTime $mixValue
					 * @return QDateTime
					 */
					try {
						return ($this->dttRegistrationDate = QType::Cast($mixValue, QType::DateTime));
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

			return Ad::LoadArrayByLoginId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated Ads
		 * @return int
		*/ 
		public function CountAds() {
			if ((is_null($this->intId)))
				return 0;

			return Ad::CountByLoginId($this->intId);
		}

		/**
		 * Associates a Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function AssociateAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this unsaved Login.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this Login with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`ad`
				SET
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
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
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Login.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this Login with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`ad`
				SET
					`login_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objAd->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all Ads
		 * @return void
		*/ 
		public function UnassociateAllAds() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`ad`
				SET
					`login_id` = null
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function DeleteAssociatedAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Login.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this Login with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objAd->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated Ads
		 * @return void
		*/ 
		public function DeleteAllAds() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad`
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
		
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

			return Bid::LoadArrayByLoginId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated Bids
		 * @return int
		*/ 
		public function CountBids() {
			if ((is_null($this->intId)))
				return 0;

			return Bid::CountByLoginId($this->intId);
		}

		/**
		 * Associates a Bid
		 * @param Bid $objBid
		 * @return void
		*/ 
		public function AssociateBid(Bid $objBid) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateBid on this unsaved Login.');
			if ((is_null($objBid->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateBid on this Login with an unsaved Bid.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`bid`
				SET
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
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
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Login.');
			if ((is_null($objBid->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this Login with an unsaved Bid.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`bid`
				SET
					`login_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objBid->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all Bids
		 * @return void
		*/ 
		public function UnassociateAllBids() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`bid`
				SET
					`login_id` = null
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated Bid
		 * @param Bid $objBid
		 * @return void
		*/ 
		public function DeleteAssociatedBid(Bid $objBid) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Login.');
			if ((is_null($objBid->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this Login with an unsaved Bid.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`bid`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objBid->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated Bids
		 * @return void
		*/ 
		public function DeleteAllBids() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateBid on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`bid`
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
		
		// Related Objects' Methods for NetworkUser
		//-------------------------------------------------------------------
		
		/**
		 * Gets all associated NetworkUsers as an array of NetworkUser objects
		 * @param string $strOrderBy
		 * @param string $strLimit 
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return NetworkUser[]
		*/ 
		public function GetNetworkUserArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return NetworkUser::LoadArrayByLoginId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated NetworkUsers
		 * @return int
		*/ 
		public function CountNetworkUsers() {
			if ((is_null($this->intId)))
				return 0;

			return NetworkUser::CountByLoginId($this->intId);
		}

		/**
		 * Associates a NetworkUser
		 * @param NetworkUser $objNetworkUser
		 * @return void
		*/ 
		public function AssociateNetworkUser(NetworkUser $objNetworkUser) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetworkUser on this unsaved Login.');
			if ((is_null($objNetworkUser->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetworkUser on this Login with an unsaved NetworkUser.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network_user`
				SET
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetworkUser->Id) . '
			');
		}

		/**
		 * Unassociates a NetworkUser
		 * @param NetworkUser $objNetworkUser
		 * @return void
		*/ 
		public function UnassociateNetworkUser(NetworkUser $objNetworkUser) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Login.');
			if ((is_null($objNetworkUser->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this Login with an unsaved NetworkUser.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network_user`
				SET
					`login_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetworkUser->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all NetworkUsers
		 * @return void
		*/ 
		public function UnassociateAllNetworkUsers() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network_user`
				SET
					`login_id` = null
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated NetworkUser
		 * @param NetworkUser $objNetworkUser
		 * @return void
		*/ 
		public function DeleteAssociatedNetworkUser(NetworkUser $objNetworkUser) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Login.');
			if ((is_null($objNetworkUser->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this Login with an unsaved NetworkUser.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network_user`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetworkUser->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated NetworkUsers
		 * @return void
		*/ 
		public function DeleteAllNetworkUsers() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network_user`
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
		
		// Related Objects' Methods for Search
		//-------------------------------------------------------------------
		
		/**
		 * Gets all associated Searches as an array of Search objects
		 * @param string $strOrderBy
		 * @param string $strLimit 
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Search[]
		*/ 
		public function GetSearchArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Search::LoadArrayByLoginId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated Searches
		 * @return int
		*/ 
		public function CountSearches() {
			if ((is_null($this->intId)))
				return 0;

			return Search::CountByLoginId($this->intId);
		}

		/**
		 * Associates a Search
		 * @param Search $objSearch
		 * @return void
		*/ 
		public function AssociateSearch(Search $objSearch) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSearch on this unsaved Login.');
			if ((is_null($objSearch->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSearch on this Login with an unsaved Search.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`search`
				SET
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objSearch->Id) . '
			');
		}

		/**
		 * Unassociates a Search
		 * @param Search $objSearch
		 * @return void
		*/ 
		public function UnassociateSearch(Search $objSearch) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this unsaved Login.');
			if ((is_null($objSearch->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this Login with an unsaved Search.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`search`
				SET
					`login_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objSearch->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all Searches
		 * @return void
		*/ 
		public function UnassociateAllSearches() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`search`
				SET
					`login_id` = null
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated Search
		 * @param Search $objSearch
		 * @return void
		*/ 
		public function DeleteAssociatedSearch(Search $objSearch) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this unsaved Login.');
			if ((is_null($objSearch->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this Login with an unsaved Search.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objSearch->Id) . ' AND
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated Searches
		 * @return void
		*/ 
		public function DeleteAllSearches() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSearch on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`search`
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
		// Related Many-to-Many Objects' Methods for Seller
		//-------------------------------------------------------------------

		/**
		 * Gets all many-to-many associated Sellers as an array of Seller objects
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Seller[]
		*/ 
		public function GetSellerArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return Seller::LoadArrayByLogin($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Sellers
		 * @return int
		*/ 
		public function CountSellers() {
			if ((is_null($this->intId)))
				return 0;

			return Seller::CountByLogin($this->intId);
		}

		/**
		 * Associates a Seller
		 * @param Seller $objSeller
		 * @return void
		*/ 
		public function AssociateSeller(Seller $objSeller) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSeller on this unsaved Login.');
			if ((is_null($objSeller->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateSeller on this Login with an unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `login_seller_assn` (
					`login_id`,
					`seller_id`
				) VALUES (
					' . $objDatabase->SqlVariable($this->intId) . ',
					' . $objDatabase->SqlVariable($objSeller->Id) . '
				)
			');
		}

		/**
		 * Unassociates a Seller
		 * @param Seller $objSeller
		 * @return void
		*/ 
		public function UnassociateSeller(Seller $objSeller) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSeller on this unsaved Login.');
			if ((is_null($objSeller->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateSeller on this Login with an unsaved Seller.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`login_seller_assn`
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`seller_id` = ' . $objDatabase->SqlVariable($objSeller->Id) . '
			');
		}

		/**
		 * Unassociates all Sellers
		 * @return void
		*/ 
		public function UnassociateAllSellers() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllSellerArray on this unsaved Login.');

			// Call to QueryHelper to Get the Database Object
			Login::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`login_seller_assn`
				WHERE
					`login_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}





		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column login.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column login.password
		 * @var string strPassword
		 */
		protected $strPassword;

		/**
		 * Protected member variable that maps to the database column login.role
		 * @var string strRole
		 */
		protected $strRole;

		/**
		 * Protected member variable that maps to the database column login.name
		 * @var string strName
		 */
		protected $strName;

		/**
		 * Protected member variable that maps to the database column login.address
		 * @var string strAddress
		 */
		protected $strAddress;

		/**
		 * Protected member variable that maps to the database column login.phone
		 * @var string strPhone
		 */
		protected $strPhone;

		/**
		 * Protected member variable that maps to the database column login.email
		 * @var string strEmail
		 */
		protected $strEmail;

		/**
		 * Protected member variable that maps to the database column login.username
		 * @var string strUsername
		 */
		protected $strUsername;

		/**
		 * Protected member variable that maps to the database column login.salt
		 * @var string strSalt
		 */
		protected $strSalt;

		/**
		 * Protected member variable that maps to the database column login.organization_number
		 * @var string strOrganizationNumber
		 */
		protected $strOrganizationNumber;

		/**
		 * Protected member variable that maps to the database column login.company_name
		 * @var string strCompanyName
		 */
		protected $strCompanyName;

		/**
		 * Protected member variable that maps to the database column login.last_login
		 * @var QDateTime dttLastLogin
		 */
		protected $dttLastLogin;

		/**
		 * Protected member variable that maps to the database column login.postal
		 * @var string strPostal
		 */
		protected $strPostal;

		/**
		 * Protected member variable that maps to the database column login.city
		 * @var string strCity
		 */
		protected $strCity;

		/**
		 * Protected member variable that maps to the database column login.status
		 * @var string strStatus
		 */
		protected $strStatus;

		/**
		 * Protected member variable that maps to the database column login.notes
		 * @var string strNotes
		 */
		protected $strNotes;

		/**
		 * Protected member variable that maps to the database column login.worthy
		 * @var integer intWorthy
		 */
		protected $intWorthy;

		/**
		 * Protected member variable that maps to the database column login.last_worthy_check
		 * @var QDateTime dttLastWorthyCheck
		 */
		protected $dttLastWorthyCheck;

		/**
		 * Protected member variable that maps to the database column login.registration_date
		 * @var QDateTime dttRegistrationDate
		 */
		protected $dttRegistrationDate;

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
			$strToReturn = '<complexType name="Login"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="Password" type="xsd:string"/>';
			$strToReturn .= '<element name="Role" type="xsd:string"/>';
			$strToReturn .= '<element name="Name" type="xsd:string"/>';
			$strToReturn .= '<element name="Address" type="xsd:string"/>';
			$strToReturn .= '<element name="Phone" type="xsd:string"/>';
			$strToReturn .= '<element name="Email" type="xsd:string"/>';
			$strToReturn .= '<element name="Username" type="xsd:string"/>';
			$strToReturn .= '<element name="Salt" type="xsd:string"/>';
			$strToReturn .= '<element name="OrganizationNumber" type="xsd:string"/>';
			$strToReturn .= '<element name="CompanyName" type="xsd:string"/>';
			$strToReturn .= '<element name="LastLogin" type="xsd:dateTime"/>';
			$strToReturn .= '<element name="Postal" type="xsd:string"/>';
			$strToReturn .= '<element name="City" type="xsd:string"/>';
			$strToReturn .= '<element name="Status" type="xsd:string"/>';
			$strToReturn .= '<element name="Notes" type="xsd:string"/>';
			$strToReturn .= '<element name="Worthy" type="xsd:int"/>';
			$strToReturn .= '<element name="LastWorthyCheck" type="xsd:dateTime"/>';
			$strToReturn .= '<element name="RegistrationDate" type="xsd:dateTime"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('Login', $strComplexTypeArray)) {
				$strComplexTypeArray['Login'] = Login::GetSoapComplexTypeXml();
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, Login::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new Login();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if (property_exists($objSoapObject, 'Password'))
				$objToReturn->strPassword = $objSoapObject->Password;
			if (property_exists($objSoapObject, 'Role'))
				$objToReturn->strRole = $objSoapObject->Role;
			if (property_exists($objSoapObject, 'Name'))
				$objToReturn->strName = $objSoapObject->Name;
			if (property_exists($objSoapObject, 'Address'))
				$objToReturn->strAddress = $objSoapObject->Address;
			if (property_exists($objSoapObject, 'Phone'))
				$objToReturn->strPhone = $objSoapObject->Phone;
			if (property_exists($objSoapObject, 'Email'))
				$objToReturn->strEmail = $objSoapObject->Email;
			if (property_exists($objSoapObject, 'Username'))
				$objToReturn->strUsername = $objSoapObject->Username;
			if (property_exists($objSoapObject, 'Salt'))
				$objToReturn->strSalt = $objSoapObject->Salt;
			if (property_exists($objSoapObject, 'OrganizationNumber'))
				$objToReturn->strOrganizationNumber = $objSoapObject->OrganizationNumber;
			if (property_exists($objSoapObject, 'CompanyName'))
				$objToReturn->strCompanyName = $objSoapObject->CompanyName;
			if (property_exists($objSoapObject, 'LastLogin'))
				$objToReturn->dttLastLogin = new QDateTime($objSoapObject->LastLogin);
			if (property_exists($objSoapObject, 'Postal'))
				$objToReturn->strPostal = $objSoapObject->Postal;
			if (property_exists($objSoapObject, 'City'))
				$objToReturn->strCity = $objSoapObject->City;
			if (property_exists($objSoapObject, 'Status'))
				$objToReturn->strStatus = $objSoapObject->Status;
			if (property_exists($objSoapObject, 'Notes'))
				$objToReturn->strNotes = $objSoapObject->Notes;
			if (property_exists($objSoapObject, 'Worthy'))
				$objToReturn->intWorthy = $objSoapObject->Worthy;
			if (property_exists($objSoapObject, 'LastWorthyCheck'))
				$objToReturn->dttLastWorthyCheck = new QDateTime($objSoapObject->LastWorthyCheck);
			if (property_exists($objSoapObject, 'RegistrationDate'))
				$objToReturn->dttRegistrationDate = new QDateTime($objSoapObject->RegistrationDate);
			if (property_exists($objSoapObject, '__blnRestored'))
				$objToReturn->__blnRestored = $objSoapObject->__blnRestored;
			return $objToReturn;
		}

		public static function GetSoapArrayFromArray($objArray) {
			if (!$objArray)
				return null;

			$objArrayToReturn = array();

			foreach ($objArray as $objObject)
				array_push($objArrayToReturn, Login::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			if ($objObject->dttLastLogin)
				$objObject->dttLastLogin = $objObject->dttLastLogin->__toString(QDateTime::FormatSoap);
			if ($objObject->dttLastWorthyCheck)
				$objObject->dttLastWorthyCheck = $objObject->dttLastWorthyCheck->__toString(QDateTime::FormatSoap);
			if ($objObject->dttRegistrationDate)
				$objObject->dttRegistrationDate = $objObject->dttRegistrationDate->__toString(QDateTime::FormatSoap);
			return $objObject;
		}
	}
?>