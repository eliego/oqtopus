<?php
	require(__INCLUDES__ . 'data_objects_generated/NetworkUserGen.inc');

	/**
	 * The NetworkUser class defined here contains any
	 * customized code for the NetworkUser class in the
	 * Object Relational Model.  It represents the "network_user" table 
	 * in the database, and extends from the code generated abstract NetworkUserGen
	 * class, which contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 * 
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class NetworkUser extends NetworkUserGen {
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objNetworkUser->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('NetworkUser Object %s',  $this->intId);
		}
		/**
		 * Load an array of NetworkUser objects,
		 * by NetworkId Index(es) and status
		 * @param integer $intNetworkId
		 * @param BidStatus $strStatus
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return NetworkUser[]
		*/
		public static function LoadArrayByNetworkIdAndStatus($intNetworkId, $strStatus, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			NetworkUser::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intNetworkId = $objDatabase->SqlVariable($intNetworkId, true);
			$strStatus = $objDatabase->SqlVariable($strStatus);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`network_user`.`id` AS `id`,
					`network_user`.`status` AS `status`,
					`network_user`.`login_id` AS `login_id`,
					`network_user`.`network_id` AS `network_id`
					%s
				FROM
					`network_user` AS `network_user`
					%s
				WHERE
					`network_user`.`network_id` %s AND
					`network_user`.`status` = %s
 				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intNetworkId, $strStatus,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return NetworkUser::InstantiateDbResult($objDbResult);
		}
		
		/**
		 * Load an array of NetworkUser objects,
		 * by status and seller
		 * @param Seller  $objSeller
		 * @param BidStatus $strStatus
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return NetworkUser[]
		*/
		public static function LoadArrayBySellerAndStatus(Seller $objSeller, $strStatus, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			NetworkUser::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$strStatus = $objDatabase->SqlVariable($strStatus);
			$strSellerId = $objDatabase->SqlVariable($objSeller->Id);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`network_user`.`id` AS `id`,
					`network_user`.`status` AS `status`,
					`network_user`.`login_id` AS `login_id`,
					`network_user`.`network_id` AS `network_id`
					%s
				FROM
					`network`,
					`network_user` AS `network_user`
					%s
				WHERE
					`network_user`.`status` = %s
					AND network_user.network_id = network.id
					AND network.seller_id = %s
 				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strStatus, $strSellerId, $strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return NetworkUser::InstantiateDbResult($objDbResult);
		}
		
/**
		 * Load an array of NetworkUser objects,
		 * by login ID, with some virtual attributes set
		 * @param int $intLogin
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return NetworkUser[]
		*/
		public static function LoadArrayByLoginIdWithSellerNameAndNetworkName($intLogin, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			NetworkUser::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$intLogin = $objDatabase->SqlVariable($intLogin);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
					`network_user`.`id` AS `id`,
					`network_user`.`status` AS `status`,
					`network_user`.`login_id` AS `login_id`,
					`network_user`.`network_id` AS `network_id`,
					`network`.`name` AS __NetworkName,
					`seller`.`seller_name` AS __SellerName
					%s
				FROM
					`network_user` AS `network_user`,
					`network`,
					`seller`
					%s
				WHERE
					network_user.login_id = %s
					AND network_user.network_id = network.id
					AND network.seller_id = seller.id
 				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$intLogin, $strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return NetworkUser::InstantiateDbResult($objDbResult);
		}		
		
		public static function CountBySellerAndStatus(Seller $objSeller, $strStatus) {
			self::QueryHelper($objDatabase);
			
			$strSellerId = $objDatabase->SqlVariable($objSeller->Id);
			$strStatus = $objDatabase->SqlVariable($strStatus);
			
			$strQuery = sprintf('SELECT COUNT(*) AS Count FROM network_user, network WHERE
								 network_user.status = %s AND network_user.network_id = network.id AND network.seller_id = %s',
								$strStatus, $strSellerId);
								
			$objResult = $objDatabase->Query($strQuery);
			$objResult = $objResult->FetchRow();
			return (int)$objResult[0];
		}
		
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			if ($blnForceInsert || !$this->__blnRestored)
				if ($this->Network->Seller->MailOnApp)
					Mail::SendAppMail($this);
					
					
			try {
				parent::Save($blnForceInsert, $blnForceUpdate);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
		}
	}
?>