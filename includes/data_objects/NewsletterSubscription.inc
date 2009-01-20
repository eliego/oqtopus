<?php
	require(__INCLUDES__ . 'data_objects_generated/NewsletterSubscriptionGen.inc');

	/**
	 * The NewsletterSubscription class defined here contains any
	 * customized code for the NewsletterSubscription class in the
	 * Object Relational Model.  It represents the "newsletter_subscription" table 
	 * in the database, and extends from the code generated abstract NewsletterSubscriptionGen
	 * class, which contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 * 
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class NewsletterSubscription extends NewsletterSubscriptionGen {
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objNewsletterSubscription->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('NewsletterSubscription Object %s',  $this->intId);
		}



		// Override or Create New LoadArray / CountBy methods
		// For obvious reasons, these methods are commented out.  But if you wish
		// to implement a new set of LoadArray and CountBy methods, feel free
		// to use these examples as a starting point.
/*
		/**
		 * Load an array of NewsletterSubscription objects, based on the SAMPLE
		 * search parameters of Param1, Param2 and Param3
		 * @param string $strParam1 some SAMPLE parameter 1
		 * @param string $strParam2 some SAMPLE parameter 2
		 * @param integer $intParam3 some SAMPLE parameter 3
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return NewsletterSubscription[]
		* -- REMOVE SPACE -- /
		public static function LoadArrayBySample($strParam1, $strParam2, $intParam3, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			NewsletterSubscription::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strParam1 = $objDatabase->SqlVariable($strParam1);
			$strParam2 = $objDatabase->SqlVariable($strParam2);
			$intParam3 = $objDatabase->SqlVariable($intParam3);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`newsletter_subscription`.*
					%s
				FROM
					`newsletter_subscription` AS `newsletter_subscription`
					%s
				WHERE
					param_1 = %s AND
					param_2 != %s AND
					param_3 < %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strParam1, $strParam2, $intParam3,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return NewsletterSubscription::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count NewsletterSubscriptions objects, based on the SAMPLE
		 * search parameters of Param1, Param2 and Param3
		 * @param string $strParam1 some SAMPLE parameter 1
		 * @param string $strParam2 some SAMPLE parameter 2
		 * @param integer $intParam3 some SAMPLE parameter 3
		 * @return integer the count of NewsletterSubscriptions objects
		* -- REMOVE SPACE -- /
		public static function CountBySample($strParam1, $strParam2, $intParam3) {
			// Call to QueryHelper to Get the Database Object
			NewsletterSubscription::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strParam1 = $objDatabase->SqlVariable($strParam1);
			$strParam2 = $objDatabase->SqlVariable($strParam2);
			$intParam3 = $objDatabase->SqlVariable($intParam3);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					`newsletter_subscription`
				WHERE
					param_1 = %s AND
					param_2 != %s AND
					param_3 < %s', $strParam1, $strParam2, $intParam3);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}
*/



		// Override or Create New Properties and Variables
		// For performance reasons, these variables and __set and __get override methods
		// are commented out.  But if you wish to implement or override any
		// of the data generated properties, please feel free to uncomment them.
/*
		protected $strSomeNewProperty;

		public function __get($strName) {
			switch ($strName) {
				case 'SomeNewProperty': return $this->strSomeNewProperty;

				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'SomeNewProperty':
					try {
						return ($this->strSomeNewProperty = QType::Cast($mixValue, QType::String));
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

				default:
					try {
						return (parent::__set($strName, $mixValue));
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}
*/
	}
?>