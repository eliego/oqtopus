<?php
	require(__INCLUDES__ . 'data_objects_generated/SellerGen.inc');

	/**
	 * The Seller class defined here contains any
	 * customized code for the Seller class in the
	 * Object Relational Model.  It represents the "seller" table 
	 * in the database, and extends from the code generated abstract SellerGen
	 * class, which contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 * 
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class Seller extends SellerGen {
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objSeller->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('Seller Object %s',  $this->intId);
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'Debt':
					return Bid::GetTotalProvisionBySellerAndStatus($this, BidStatus::Accepted);
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		/**
		 * Get a new instance with some default properties set
		 *
		 * @return Seller
		 */
		public static function Create() {
			$o = new self();
			$o->MailOnBid = 1;
			$o->MailOnApp = 1;
			return $o;
		}
		
		/**
		 * Get all of this sellers networks, with a virtual variable __Selected set to 1 or 0 depending on if the specified ad is associated with the network or not
		 *
		 * @param Ad $objAd
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param bool[] $objExpansionMap
		 * @return Network[]
		 */
		public function GetNetworkArrayWithSelectedByAd(Ad $objAd, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();
				
			return Network::LoadArrayWithSelectedBySellerAndAd($this, $objAd, $strOrderBy, $strLimit, $objExpansionMap);
		}
		
		public function GetNetworkArrayWithMemberCount($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();
			
			return Network::LoadArrayWithMemberCount($this, $strOrderBy, $strLimit, $objExpansionMap);
		}
		
		public function CountBidsByStatus($strStatus) {
			return Bid::CountBySellerAndStatus($this, $strStatus);
		}
		
		public function CountNetworkApplicationsByStatus($strStatus) {
			return NetworkUser::CountBySellerAndStatus($this, $strStatus);
		}
		
		public function GetApplicationArray($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if ((is_null($this->intId)))
				return array();
				
			return NetworkUser::LoadArrayBySellerAndStatus($this, BidStatus::Unanswered, $strOrderBy, $strLimit, $objExpansionMap);
		}
	}
?>