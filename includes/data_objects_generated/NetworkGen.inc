<?php
	/**
	 * The abstract NetworkGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the Network subclass which
	 * extends this NetworkGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the Network class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class NetworkGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a Network from PK Info
		 * @param integer $intId
		 * @return Network
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Network::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`seller_id`,
					`name`,
					`description`
				FROM
					`network`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return Network::InstantiateDbRow($objDbResult->GetNextRow());
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
				$objQueryExpansion = new QQueryExpansion('Network', 'network', $objExpansionMap);
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
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `network` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`seller_id` AS `%s__%s__seller_id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`name` AS `%s__%s__name`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`description` AS `%s__%s__description`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

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
						default:
							throw new QCallerException(sprintf('Unknown Object to Expand in %s: %s', $strParentAlias, $strKey));
					}
				}
		}



		/**
		 * Load all Networks
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Network[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Network::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`network`.`id` AS `id`,
					`network`.`seller_id` AS `seller_id`,
					`network`.`name` AS `name`,
					`network`.`description` AS `description`
					%s
				FROM
					`network` AS `network`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Network::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all Networks
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`network`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a Network from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this Network::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return Network
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the Network object
			$objToReturn = new Network();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->intSellerId = $objDbRow->GetColumn($strAliasPrefix . 'seller_id', 'Integer');
			$objToReturn->strName = $objDbRow->GetColumn($strAliasPrefix . 'name', 'VarChar');
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
				$strAliasPrefix = 'network__';

			// Check for Seller Early Binding
			if (!is_null($objDbRow->GetColumn($strAliasPrefix . 'seller_id__id')))
				$objToReturn->objSeller = Seller::InstantiateDbRow($objDbRow, $strAliasPrefix . 'seller_id__');

			
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
		 * Instantiate an array of Networks from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return Network[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, Network::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load an array of Network objects,
		 * by SellerId Index(es)
		 * @param integer $intSellerId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Network[]
		*/
		public static function LoadArrayBySellerId($intSellerId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Network::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSellerId = $objDatabase->SqlVariable($intSellerId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`network`.`id` AS `id`,
					`network`.`seller_id` AS `seller_id`,
					`network`.`name` AS `name`,
					`network`.`description` AS `description`
					%s
				FROM
					`network` AS `network`
					%s
				WHERE
					`network`.`seller_id` %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intSellerId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Network::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Networks
		 * by SellerId Index(es)
		 * @param integer $intSellerId
		 * @return int
		*/
		public static function CountBySellerId($intSellerId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Network::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intSellerId = $objDatabase->SqlVariable($intSellerId, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`network`
				WHERE
					`seller_id` %s', $intSellerId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////
			/**
		 * Load an array of Ad objects for a given Ad
		 * via the ad_network_assn table
		 * @param integer $intAdId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		*/
		public static function LoadArrayByAd($intAdId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Network::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intAdId = $objDatabase->SqlVariable($intAdId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`network`.`id` AS `id`,
					`network`.`seller_id` AS `seller_id`,
					`network`.`name` AS `name`,
					`network`.`description` AS `description`
					%s
				FROM
					(`network` AS `network`,
					`ad_network_assn` AS `ad_network_assn`)
					%s
				WHERE
					`ad_network_assn`.`network_id` = `network`.`id` AND
					`ad_network_assn`.`ad_id` = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intAdId,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return Network::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count Networks for a given Ad
		 * via the ad_network_assn table
		 * @param integer $intAdId
		 * @return int
		*/
		public static function CountByAd($intAdId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Network::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intAdId = $objDatabase->SqlVariable($intAdId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`network`,
					`ad_network_assn`
				WHERE
					`ad_network_assn`.`network_id` = `network`.`id` AND
					`ad_network_assn`.`ad_id` = %s
			', $intAdId);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this Network
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `network` (
							`seller_id`,
							`name`,
							`description`
						) VALUES (
							' . $objDatabase->SqlVariable($this->intSellerId) . ',
							' . $objDatabase->SqlVariable($this->strName) . ',
							' . $objDatabase->SqlVariable($this->strDescription) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('network', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`network`
						SET
							`seller_id` = ' . $objDatabase->SqlVariable($this->intSellerId) . ',
							`name` = ' . $objDatabase->SqlVariable($this->strName) . ',
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
		 * Delete this Network
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this Network with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all Networks
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network`');
		}

		/**
		 * Truncate network table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `network`');
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

				case 'SellerId':
					/**
					 * Gets the value for intSellerId (Not Null)
					 * @return integer
					 */
					return $this->intSellerId;

				case 'Name':
					/**
					 * Gets the value for strName (Not Null)
					 * @return string
					 */
					return $this->strName;

				case 'Description':
					/**
					 * Gets the value for strDescription (Not Null)
					 * @return string
					 */
					return $this->strDescription;


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
							throw new QCallerException('Unable to set an unsaved Seller for this Network');

						// Update Local Member Variables
						$this->objSeller = $mixValue;
						$this->intSellerId = $mixValue->Id;

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

			return NetworkUser::LoadArrayByNetworkId($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all associated NetworkUsers
		 * @return int
		*/ 
		public function CountNetworkUsers() {
			if ((is_null($this->intId)))
				return 0;

			return NetworkUser::CountByNetworkId($this->intId);
		}

		/**
		 * Associates a NetworkUser
		 * @param NetworkUser $objNetworkUser
		 * @return void
		*/ 
		public function AssociateNetworkUser(NetworkUser $objNetworkUser) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetworkUser on this unsaved Network.');
			if ((is_null($objNetworkUser->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateNetworkUser on this Network with an unsaved NetworkUser.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network_user`
				SET
					`network_id` = ' . $objDatabase->SqlVariable($this->intId) . '
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
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Network.');
			if ((is_null($objNetworkUser->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this Network with an unsaved NetworkUser.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network_user`
				SET
					`network_id` = null
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetworkUser->Id) . ' AND
					`network_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Unassociates all NetworkUsers
		 * @return void
		*/ 
		public function UnassociateAllNetworkUsers() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				UPDATE
					`network_user`
				SET
					`network_id` = null
				WHERE
					`network_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes an associated NetworkUser
		 * @param NetworkUser $objNetworkUser
		 * @return void
		*/ 
		public function DeleteAssociatedNetworkUser(NetworkUser $objNetworkUser) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Network.');
			if ((is_null($objNetworkUser->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this Network with an unsaved NetworkUser.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network_user`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($objNetworkUser->Id) . ' AND
					`network_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

		/**
		 * Deletes all associated NetworkUsers
		 * @return void
		*/ 
		public function DeleteAllNetworkUsers() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateNetworkUser on this unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`network_user`
				WHERE
					`network_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}

			
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

			return Ad::LoadArrayByNetwork($this->intId, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated Ads
		 * @return int
		*/ 
		public function CountAds() {
			if ((is_null($this->intId)))
				return 0;

			return Ad::CountByNetwork($this->intId);
		}

		/**
		 * Associates a Ad
		 * @param Ad $objAd
		 * @return void
		*/ 
		public function AssociateAd(Ad $objAd) {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this unsaved Network.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call AssociateAd on this Network with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO `ad_network_assn` (
					`network_id`,
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
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this unsaved Network.');
			if ((is_null($objAd->Id)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAd on this Network with an unsaved Ad.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_network_assn`
				WHERE
					`network_id` = ' . $objDatabase->SqlVariable($this->intId) . ' AND
					`ad_id` = ' . $objDatabase->SqlVariable($objAd->Id) . '
			');
		}

		/**
		 * Unassociates all Ads
		 * @return void
		*/ 
		public function UnassociateAllAds() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAllAdArray on this unsaved Network.');

			// Call to QueryHelper to Get the Database Object
			Network::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`ad_network_assn`
				WHERE
					`network_id` = ' . $objDatabase->SqlVariable($this->intId) . '
			');
		}





		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column network.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column network.seller_id
		 * @var integer intSellerId
		 */
		protected $intSellerId;

		/**
		 * Protected member variable that maps to the database column network.name
		 * @var string strName
		 */
		protected $strName;

		/**
		 * Protected member variable that maps to the database column network.description
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
		 * in the database column network.seller_id.
		 *
		 * NOTE: Always use the Seller property getter to correctly retrieve this Seller object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var Seller objSeller
		 */
		protected $objSeller;





		////////////////////////////////////////
		// COLUMN CONSTANTS for OBJECT EXPANSION
		////////////////////////////////////////
		const ExpandSeller = 'seller_id';




		////////////////////////////////////////
		// METHODS for WEB SERVICES
		////////////////////////////////////////
		public static function GetSoapComplexTypeXml() {
			$strToReturn = '<complexType name="Network"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="Seller" type="xsd1:Seller"/>';
			$strToReturn .= '<element name="Name" type="xsd:string"/>';
			$strToReturn .= '<element name="Description" type="xsd:string"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('Network', $strComplexTypeArray)) {
				$strComplexTypeArray['Network'] = Network::GetSoapComplexTypeXml();
				Seller::AlterSoapComplexTypeArray($strComplexTypeArray);
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, Network::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new Network();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if ((property_exists($objSoapObject, 'Seller')) &&
				($objSoapObject->Seller))
				$objToReturn->Seller = Seller::GetObjectFromSoapObject($objSoapObject->Seller);
			if (property_exists($objSoapObject, 'Name'))
				$objToReturn->strName = $objSoapObject->Name;
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
				array_push($objArrayToReturn, Network::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			if ($objObject->objSeller)
				$objObject->objSeller = Seller::GetSoapObjectFromObject($objObject->objSeller, false);
			else if (!$blnBindRelatedObjects)
				$objObject->intSellerId = null;
			return $objObject;
		}
	}
?>