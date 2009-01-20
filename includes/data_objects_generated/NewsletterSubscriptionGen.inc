<?php
	/**
	 * The abstract NewsletterSubscriptionGen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the NewsletterSubscription subclass which
	 * extends this NewsletterSubscriptionGen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the NewsletterSubscription class.
	 * 
	 * @package Oqtopus
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class NewsletterSubscriptionGen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a NewsletterSubscription from PK Info
		 * @param integer $intId
		 * @return NewsletterSubscription
		*/
		public static function Load($intId) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			NewsletterSubscription::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intId = $objDatabase->SqlVariable($intId);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`newsletter`,
					`pm`,
					`press`,
					`email`
				FROM
					`newsletter_subscription`
				WHERE
					`id` = %s', $intId);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return NewsletterSubscription::InstantiateDbRow($objDbResult->GetNextRow());
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
				$objQueryExpansion = new QQueryExpansion('NewsletterSubscription', 'newsletter_subscription', $objExpansionMap);
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
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN `newsletter_subscription` AS `%s__%s` ON `%s`.`%s` = `%s__%s`.`id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`id` AS `%s__%s__id`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`newsletter` AS `%s__%s__newsletter`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`pm` AS `%s__%s__pm`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`press` AS `%s__%s__press`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
				$objQueryExpansion->AddSelectItem(sprintf('`%s__%s`.`email` AS `%s__%s__email`', $strParentAlias, $strAlias, $strParentAlias, $strAlias));

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
		 * Load all NewsletterSubscriptions
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return NewsletterSubscription[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			NewsletterSubscription::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`newsletter_subscription`.`id` AS `id`,
					`newsletter_subscription`.`newsletter` AS `newsletter`,
					`newsletter_subscription`.`pm` AS `pm`,
					`newsletter_subscription`.`press` AS `press`,
					`newsletter_subscription`.`email` AS `email`
					%s
				FROM
					`newsletter_subscription` AS `newsletter_subscription`
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return NewsletterSubscription::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all NewsletterSubscriptions
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			NewsletterSubscription::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					`newsletter_subscription`');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a NewsletterSubscription from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this NewsletterSubscription::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return NewsletterSubscription
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the NewsletterSubscription object
			$objToReturn = new NewsletterSubscription();
			$objToReturn->__blnRestored = true;

			$objToReturn->intId = $objDbRow->GetColumn($strAliasPrefix . 'id', 'Integer');
			$objToReturn->intNewsletter = $objDbRow->GetColumn($strAliasPrefix . 'newsletter', 'Integer');
			$objToReturn->intPm = $objDbRow->GetColumn($strAliasPrefix . 'pm', 'Integer');
			$objToReturn->intPress = $objDbRow->GetColumn($strAliasPrefix . 'press', 'Integer');
			$objToReturn->strEmail = $objDbRow->GetColumn($strAliasPrefix . 'email', 'VarChar');

			// Instantiate Virtual Attributes
			foreach ($objDbRow->GetColumnNameArray() as $strColumnName => $mixValue) {
				$strVirtualPrefix = $strAliasPrefix . '__';
				$strVirtualPrefixLength = strlen($strVirtualPrefix);
				if (substr($strColumnName, 0, $strVirtualPrefixLength) == $strVirtualPrefix)
					$objToReturn->__strVirtualAttributeArray[substr($strColumnName, $strVirtualPrefixLength)] = $mixValue;
			}

			// Prepare to Check for Early Binding
			if (!$strAliasPrefix)
				$strAliasPrefix = 'newsletter_subscription__';

			
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
		 * Instantiate an array of NewsletterSubscriptions from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return NewsletterSubscription[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, NewsletterSubscription::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
			
		/**
		 * Load a single NewsletterSubscription object,
		 * by Email Index(es)
		 * @param string $strEmail
		 * @return NewsletterSubscription
		*/
		public static function LoadByEmail($strEmail) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			NewsletterSubscription::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strEmail = $objDatabase->SqlVariable($strEmail, true);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					`id`,
					`newsletter`,
					`pm`,
					`press`,
					`email`
				FROM
					`newsletter_subscription`
				WHERE
					`email` %s', $strEmail);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return NewsletterSubscription::InstantiateDbRow($objDbResult->GetNextRow());
		}





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////





		//////////////////
		// SAVE AND DELETE
		//////////////////

		/**
		 * Save this NewsletterSubscription
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			NewsletterSubscription::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `newsletter_subscription` (
							`newsletter`,
							`pm`,
							`press`,
							`email`
						) VALUES (
							' . $objDatabase->SqlVariable($this->intNewsletter) . ',
							' . $objDatabase->SqlVariable($this->intPm) . ',
							' . $objDatabase->SqlVariable($this->intPress) . ',
							' . $objDatabase->SqlVariable($this->strEmail) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('newsletter_subscription', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`newsletter_subscription`
						SET
							`newsletter` = ' . $objDatabase->SqlVariable($this->intNewsletter) . ',
							`pm` = ' . $objDatabase->SqlVariable($this->intPm) . ',
							`press` = ' . $objDatabase->SqlVariable($this->intPress) . ',
							`email` = ' . $objDatabase->SqlVariable($this->strEmail) . '
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
		 * Delete this NewsletterSubscription
		 * @return void
		*/
		public function Delete() {
			if ((is_null($this->intId)))
				throw new QUndefinedPrimaryKeyException('Cannot delete this NewsletterSubscription with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			NewsletterSubscription::QueryHelper($objDatabase);


			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					`newsletter_subscription`
				WHERE
					`id` = ' . $objDatabase->SqlVariable($this->intId) . '');
		}

		/**
		 * Delete all NewsletterSubscriptions
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			NewsletterSubscription::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					`newsletter_subscription`');
		}

		/**
		 * Truncate newsletter_subscription table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			NewsletterSubscription::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE `newsletter_subscription`');
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

				case 'Newsletter':
					/**
					 * Gets the value for intNewsletter (Not Null)
					 * @return integer
					 */
					return $this->intNewsletter;

				case 'Pm':
					/**
					 * Gets the value for intPm (Not Null)
					 * @return integer
					 */
					return $this->intPm;

				case 'Press':
					/**
					 * Gets the value for intPress (Not Null)
					 * @return integer
					 */
					return $this->intPress;

				case 'Email':
					/**
					 * Gets the value for strEmail (Unique)
					 * @return string
					 */
					return $this->strEmail;


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
				case 'Newsletter':
					/**
					 * Sets the value for intNewsletter (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intNewsletter = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Pm':
					/**
					 * Sets the value for intPm (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intPm = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Press':
					/**
					 * Sets the value for intPress (Not Null)
					 * @param integer $mixValue
					 * @return integer
					 */
					try {
						return ($this->intPress = QType::Cast($mixValue, QType::Integer));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				case 'Email':
					/**
					 * Sets the value for strEmail (Unique)
					 * @param string $mixValue
					 * @return string
					 */
					try {
						return ($this->strEmail = QType::Cast($mixValue, QType::String));
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






		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
		/**
		 * Protected member variable that maps to the database PK Identity column newsletter_subscription.id
		 * @var integer intId
		 */
		protected $intId;

		/**
		 * Protected member variable that maps to the database column newsletter_subscription.newsletter
		 * @var integer intNewsletter
		 */
		protected $intNewsletter;

		/**
		 * Protected member variable that maps to the database column newsletter_subscription.pm
		 * @var integer intPm
		 */
		protected $intPm;

		/**
		 * Protected member variable that maps to the database column newsletter_subscription.press
		 * @var integer intPress
		 */
		protected $intPress;

		/**
		 * Protected member variable that maps to the database column newsletter_subscription.email
		 * @var string strEmail
		 */
		protected $strEmail;

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
			$strToReturn = '<complexType name="NewsletterSubscription"><sequence>';
			$strToReturn .= '<element name="Id" type="xsd:int"/>';
			$strToReturn .= '<element name="Newsletter" type="xsd:int"/>';
			$strToReturn .= '<element name="Pm" type="xsd:int"/>';
			$strToReturn .= '<element name="Press" type="xsd:int"/>';
			$strToReturn .= '<element name="Email" type="xsd:string"/>';
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('NewsletterSubscription', $strComplexTypeArray)) {
				$strComplexTypeArray['NewsletterSubscription'] = NewsletterSubscription::GetSoapComplexTypeXml();
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, NewsletterSubscription::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new NewsletterSubscription();
			if (property_exists($objSoapObject, 'Id'))
				$objToReturn->intId = $objSoapObject->Id;
			if (property_exists($objSoapObject, 'Newsletter'))
				$objToReturn->intNewsletter = $objSoapObject->Newsletter;
			if (property_exists($objSoapObject, 'Pm'))
				$objToReturn->intPm = $objSoapObject->Pm;
			if (property_exists($objSoapObject, 'Press'))
				$objToReturn->intPress = $objSoapObject->Press;
			if (property_exists($objSoapObject, 'Email'))
				$objToReturn->strEmail = $objSoapObject->Email;
			if (property_exists($objSoapObject, '__blnRestored'))
				$objToReturn->__blnRestored = $objSoapObject->__blnRestored;
			return $objToReturn;
		}

		public static function GetSoapArrayFromArray($objArray) {
			if (!$objArray)
				return null;

			$objArrayToReturn = array();

			foreach ($objArray as $objObject)
				array_push($objArrayToReturn, NewsletterSubscription::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
			return $objObject;
		}
	}
?>