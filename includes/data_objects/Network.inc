<?php
	require(__INCLUDES__ . 'data_objects_generated/NetworkGen.inc');

	/**
	 * The Network class defined here contains any
	 * customized code for the Network class in the
	 * Object Relational Model.  It represents the "network" table 
	 * in the database, and extends from the code generated abstract NetworkGen
	 * class, which contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 * 
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class Network extends NetworkGen {
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objNetwork->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('Network Object %s',  $this->intId);
		}

		/**
		 * Gets some associated NetworkUsers as an array of NetworkUser objects
		 * @param BidStatus $strStatus
		 * @param string $strOrderBy
		 * @param string $strLimit 
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return NetworkUser[]
		*/ 
		public function GetNetworkUserArrayByStatus($strStatus, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();

			return NetworkUser::LoadArrayByNetworkIdAndStatus($this->intId, $strStatus, $strOrderBy, $strLimit, $objExpansionMap);
		}	
		
		/**
		 * Get an array of networks, owned by the specified seller,
		 * and with the virtual attribute __Selected set to 0 or 1 depending on if the network is associatied with the specified ad or not
		 *
		 * @param Seller $objSeller
		 * @param Ad $objAd
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param bool[] $objExpansionMap
		 * @return Network[]
		 */
		public static function LoadArrayWithSelectedBySellerAndAd(Seller $objSeller, Ad $objAd, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Network::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			$intSellerId = $objDatabase->SqlVariable($objSeller->Id);
			$intAdId = $objDatabase->SqlVariable($objAd->Id);
				
			$strQuery = sprintf('SELECT
								 %s
								   network. *,
								   IF( ad_network_assn.ad_id <=> NULL , 0, 1 ) AS __Selected
								   %s
								 FROM  `network`
								 LEFT JOIN ad_network_assn ON
								     ad_network_assn.network_id = network.id
								   AND
								     ad_network_assn.ad_id = %s
								 %s
								 WHERE
								   network.seller_id = %s
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $intAdId, $strExpandFrom, $intSellerId, $strOrderBy, $strLimitSuffix);
			
			$objResult = $objDatabase->Query($strQuery);
			return self::InstantiateDbResult($objResult);
		}
		
		/**
		 * Load array of networks by Seller, with virtual variables:
		 *  __MemberCount set to the number of members in the network,
		 * __SimCount set to the number of SIM:s avaiable for the network and
		 * __BidCount, the total numbers of Bids issued by the network
		 *
		 * @param Seller $objSeller
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param bool[] $objExpansionMap
		 * @return Network[]
		 */
		public static function LoadArrayWithMemberCount(Seller $objSeller, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Network::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$strSellerId = $objDatabase->SqlVariable($objSeller->Id);
			
			$strQuery = sprintf('SELECT
								 %s
								 	network.*,
								 	(
								 		SELECT COUNT(*) FROM network_user WHERE network_user.network_id = network.id AND network_user.status = "accepted"
								 	) AS __MemberCount,
								 	(
								 		SELECT COUNT(*) FROM ad, ad_network_assn WHERE ad.type = "sim" AND ad.permission_mode = "include" AND ad_network_assn.ad_id = ad.id AND ad_network_assn.network_id = network.id
								 	) AS __SimCount,
								 	(
								 		SELECT IF(SUM(bid.amount) IS NULL, 0, SUM(bid.amount)) FROM bid, ad, network_user WHERE bid.login_id = network_user.login_id AND network_user.network_id = network.id AND bid.ad_id = ad.id AND ad.seller_id = %s AND network_user.status = "accepted"
								 	) AS __BidAmount
								 	%s
								 FROM
								 	network
								 %s
								 WHERE
								 	  network.seller_id = %s
								 %s
								 %s', $strLimitPrefix, $strSellerId, $strExpandSelect, $strExpandFrom, $strSellerId, $strOrderBy, $strLimitSuffix);
			
			$objResult = $objDatabase->Query($strQuery);
			return self::InstantiateDbResult($objResult);
		}
		
		/**
		 * Check if a login is member, pending or confirmed, of this network
		 *
		 * @param Login $objLogin
		 * @return bool
		 */
		public function IsMemberOrPending(Login $objLogin) {
			self::QueryHelper($objDatabase);
			
			$strLId = $objDatabase->SqlVariable($objLogin->Id);
			$strNId = $objDatabase->SqlVariable($this->intId);
			
			$strQuery = sprintf('SELECT id FROM network_user WHERE network_id = %s AND login_id = %s LIMIT 1', $strNId, $strLId);
			
			$objResult = $objDatabase->Query($strQuery);
			return (bool)$objResult->CountRows();
		}
	}
?>