<?php
	require(__INCLUDES__ . 'data_objects_generated/BidGen.inc');

	/**
	 * The Bid class defined here contains any
	 * customized code for the Bid class in the
	 * Object Relational Model.  It represents the "bid" table 
	 * in the database, and extends from the code generated abstract BidGen
	 * class, which contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 * 
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class Bid extends BidGen {
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objBid->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('Bid Object %s',  $this->intId);
		}
		

		
		/**
		 * Load an array of bids amde by login id
		 * If $blnStatus == true, only bids with status new will be returned
		 * If $blnStatus == false, only bids without status new will be returned
		 * If $dtAnsweredTimestamp is set, only bids with answered_timestamp after or before specified timestamp will be returned, depending on $strTimeComparisonMode
		 *
		 * @param int $intLoginId
		 * @param boolean $blnStatus
		 * @param QDateTime $dtAnsweredTimestamp
		 * @param TimeComparisonMode $strTimeComparisonMode
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap
		 * @return Bid[]
		 */
		public static function LoadArrayByLoginIdAndAnsweredTimestamp($intLoginId, $blnStatus, $dtAnsweredTimestamp = null, $strTimeComparisonMode = TimeComparisonMode::Before, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$intLoginId = $objDatabase->SqlVariable($intLoginId);
			$strOp = $blnStatus ? '=' : '!=';
			$strWhere = '';
			
			if ($dtAnsweredTimestamp)
				$strWhere = sprintf(' AND bid.answer_timestamp %s %s ', $strTimeComparisonMode, $objDatabase->SqlVariable($dtAnsweredTimestamp));
			
			$strQuery = sprintf('SELECT
								 %s
								 	bid.*
								 	%s
								 FROM
								 	bid
								 	%s
								 WHERE
								 	  bid.login_id = %s
								 	AND
								 	   bid.status %s "new"
								 	%s
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom, $intLoginId, $strOp, $strWhere, $strOrderBy, $strLimitSuffix);

			$objDbResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objDbResult);
		}
		
		/**
		 * Load desginated Bid-array for New- and Old-bid-dtgs in BuyersBidsForm
		 *
		 * @param integer $intLoginId
		 * @param QDateTime $dtAnsweredTimestamp Only return bids with answer_timestamp $strTimeComparisonMode (before or after) this
		 * @param TimeComparisonMode $strTimeComparisonMode
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param boolean[] $objExpansionMap
		 * @return Bid[]
		 */
		public static function LoadArrayForBuyersAnsweredBids($intLoginId, QDateTime $dtAnsweredTimestamp, $strTimeComparisonMode, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$intLoginId = $objDatabase->SqlVariable($intLoginId);
			$dtAnsweredTimestamp = $objDatabase->SqlVariable($dtAnsweredTimestamp);
			if (!($strTimeComparisonMode == TimeComparisonMode::After  || $strTimeComparisonMode == TimeComparisonMode::Before))
				throw new WrongParametersException(sprintf('%s::%s: Parameter 3 must be a TimeComparisonMode', __CLASS__, __FUNCTION__));
				
			$strQuery = sprintf('SELECT
								 %s
								 	bid.*,
								 	seller.seller_name AS __SellerName,
								 	seller.id AS __SellerId,
								 	ad.name AS __AdName
								 	%s
								 FROM
								 	bid,
								 	seller,
								 	ad
								 	%s
								 WHERE
								 	  bid.login_id = %s
								 	AND
								 	  bid.status != "new"
								 	AND
								 	  bid.answer_timestamp %s %s
								 	AND
								 	  ad.id = bid.ad_id
								 	AND
								 	  seller.id = ad.seller_id
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom, $intLoginId, $strTimeComparisonMode, $dtAnsweredTimestamp, $strOrderBy, $strLimitSuffix);
			
			$objResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objResult);
		}
		
		public static function LoadArrayForBuyersPendingBids($intLoginId, $strTimeComparisonMode, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$intLoginId = $objDatabase->SqlVariable($intLoginId);
			$strNow = $objDatabase->SqlVariable(new QDateTime(QDateTime::Now));
			if (!($strTimeComparisonMode == TimeComparisonMode::After  || $strTimeComparisonMode == TimeComparisonMode::Before))
				throw new WrongParametersException(sprintf('%s::%s: Parameter 2 must be a TimeComparisonMode', __CLASS__, __FUNCTION__));
				
			$strQuery = sprintf('SELECT
								 %s
								 	bid.*,
								 	seller.seller_name AS __SellerName,
								 	seller.id AS __SellerId,
								 	ad.name AS __AdName
								 	%s
								 FROM
								 	bid,
								 	seller,
								 	ad
								 	%s
								 WHERE
								 	  bid.login_id = %s
								 	AND
								 	  bid.status = "new"
								 	AND
								 	  bid.deadline %s %s
								 	AND
								 	  ad.id = bid.ad_id
								 	AND
								 	  seller.id = ad.seller_id
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom, $intLoginId, $strTimeComparisonMode, $strNow, $strOrderBy, $strLimitSuffix);
			
			$objResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objResult);
		}
		
		/**
		 * Load a designated Bid-array for New Bids-dtg on SellersBidsForm
		 *
		 * @param integer $intSellerId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param boolean[] $objExpansionMap
		 * @return Bid[]
		 */
		public static function LoadArrayForSellersNewBids($intSellerId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$intSellerId = $objDatabase->SqlVariable($intSellerId);
			$strNow = $objDatabase->SqlVariable(new QDateTime(QDateTime::Now));
			
			$strQuery = sprintf('SELECT
								 %s
								 	bid.*,
								 	ad.name AS __AdName,
								 	ad.price AS __AdPrice
								 	%s
								 FROM
								 	ad,
								 	bid
								 	%s
								 WHERE
								 	  ad.seller_id = %s
									AND
								 	  bid.ad_id = ad.id
								 	AND
								 	  bid.status = "new"
								 	AND
								 	  (bid.deadline IS NULL OR bid.deadline >= %s)
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom, $intSellerId, $strNow, $strOrderBy, $strLimitSuffix);
			
			$objResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objResult);
		}
		
		/**
		 * Load designated array for OldBids-dtg on SellersBidsForm
		 *
		 * @param integer $intSellerId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param boolean[] $objExpansionMap
		 * @return Bid[]
		 */
		public static function LoadArrayForSellersOldBids($intSellerId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$intSellerId = $objDatabase->SqlVariable($intSellerId);
			
			$strQuery = sprintf('SELECT
								 %s
								 	bid.*,
								 	ad.name AS __AdName,
								 	login.company_name AS __BuyerName
								 	%s
								 FROM
								 	bid,
								 	ad,
								 	login
								 	%s
								 WHERE
								 	  ad.seller_id = %s
								 	AND
								 	  bid.ad_id = ad.id
								 	AND
								 	  bid.status != "new"
								 	AND
								 	  login.id = bid.login_id
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom, $intSellerId, $strOrderBy, $strLimitSuffix);
			
			$objResult = $objDatabase->Query($strQuery);
			return Bid::InstantiateDbResult($objResult);
		}
		
		/**
		 * Load accepted bids with contacted_buyer == false for ToContactForm
		 *
		 * @param int $intSellerId
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param string $objExpansionMap
		 * @return Bid[]
		 */
		public static function LoadArrayForToContact($intSellerId, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Bid::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$intSellerId = $objDatabase->SqlVariable($intSellerId);
			
			$strQuery = sprintf('SELECT
								 %s
								 	bid.*,
								 	ad.name AS __AdName
								 	%s
								 FROM
								 	ad,
								 	bid
								 	%s
								 WHERE
								 	  ad.seller_id = %s
								 	AND
								 	  bid.ad_id = ad.id
								 	AND
								 	  bid.status = "accepted"
								 	AND
								 	  bid.contacted_buyer = 0
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom, $intSellerId, $strOrderBy, $strLimitSuffix);
			
			
			$objResult = $objDatabase->Query($strQuery);
			
			return Bid::InstantiateDbResult($objResult);
		}		
		
		
		
		public function __get($strName) {
			switch ($strName) {
				case 'Discount':
					return round((($this->Ad->Price - $this->Amount) / (float)$this->Ad->Price) * 100, 0);
					
				case 'Provision':
					return self::CalculateProvision($this->Amount);
					
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
		 * Has deadline passed?
		 *
		 * @return boolean
		 */
		public function IsExpired() {
			return ($this->dttDeadline && !$this->dttDeadline->IsNull() && ($this->dttDeadline->Timestamp < time()));
		}
		
	/**
		 * Save this Bid
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
				
			// Call to QueryHelper to Get the Database Object
			Bid::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Make sure ad hasn't expired
					if ($this->Ad->IsExpired())
						throw new Exception("You can't make bids on expired ads!");
						
					// Mail seller
					if ($this->Ad->Seller->MailOnBid)
						Mail::SendBidMail($this);
				
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `bid` (
							`login_id`,
							`ad_id`,
							`amount`,
							`status`,
							`deadline`,
							`answer_timestamp`,
							`contacted_buyer`,
							`publication_date` 
						) VALUES (
							' . $objDatabase->SqlVariable($this->intLoginId) . ',
							' . $objDatabase->SqlVariable($this->intAdId) . ',
							' . $objDatabase->SqlVariable($this->intAmount) . ',
							' . $objDatabase->SqlVariable($this->strStatus) . ',
							' . $objDatabase->SqlVariable($this->dttDeadline) . ',
							' . $objDatabase->SqlVariable($this->dttAnswerTimestamp) . ',
							' . $objDatabase->SqlVariable($this->intContactedBuyer) . ',
							' . $objDatabase->SqlVariable($this->dttPublicationDate) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('bid', 'id');
				} else {
						
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`bid`
						SET
							`login_id` = ' . $objDatabase->SqlVariable($this->intLoginId) . ',
							`ad_id` = ' . $objDatabase->SqlVariable($this->intAdId) . ',
							`amount` = ' . $objDatabase->SqlVariable($this->intAmount) . ',
							`status` = ' . $objDatabase->SqlVariable($this->strStatus) . ',
							`deadline` = ' . $objDatabase->SqlVariable($this->dttDeadline) . ',
							`answer_timestamp` = ' . $objDatabase->SqlVariable($this->dttAnswerTimestamp) . ',
							`contacted_buyer` = ' . $objDatabase->SqlVariable($this->intContactedBuyer) . ',
							`publication_date` = ' .$objDatabase->SqlVariable($this->dttPublicationDate) . '
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
		
		public static function CountBySellerAndStatus(Seller $objSeller, $strStatus) {
			self::QueryHelper($objDatabase);
			
			$strSellerId = $objDatabase->SqlVariable($objSeller->Id);
			$strDeadlineWhere = '';
			if ($strStatus == BidStatus::Unanswered)
				$strDeadlineWhere = sprintf(' AND (bid.deadline IS NULL OR bid.deadline >= %s)', $objDatabase->SqlVariable(new QDateTime(QDateTime::Now)));
			$strStatus = $objDatabase->SqlVariable($strStatus);
				
			
			$strQuery = sprintf('SELECT COUNT(*) AS Count FROM bid, ad WHERE
								 ad.seller_id = %s AND ad.id = bid.ad_id AND bid.status = %s%s',
								$strSellerId, $strStatus, $strDeadlineWhere);
			
			$objResult = $objDatabase->Query($strQuery);
			$objResult = $objResult->FetchRow();
			return (int)$objResult[0];
		}
		
		public static function GetTotalProvisionBySellerAndStatus(Seller $objSeller, $strStatus) {
			self::QueryHelper($objDatabase);
			
			$strSellerId = $objDatabase->SqlVariable($objSeller->Id);
			$strDeadlineWhere = '';
			if ($strStatus == BidStatus::Unanswered)
				$strDeadlineWhere = sprintf(' AND (bid.deadline IS NULL OR bid.deadline >= %s)', $objDatabase->SqlVariable(new QDateTime(QDateTime::Now)));
			$strStatus = $objDatabase->SqlVariable($strStatus);
			$strProv = $objDatabase->SqlVariable(OQTOPUS_PROVISION);
			$strMin = $objDatabase->SqlVariable(OQTOPUS_MINIMUM_PROVISION);
			
			$strQuery = sprintf('SELECT SUM(TempTable.Prov) AS TotalAmount FROM (SELECT IF(bid.amount * %s < %s, %s, bid.amount * %s) AS Prov FROM bid, ad WHERE
								 ad.seller_id = %s AND ad.id = bid.ad_id AND bid.status = %s%s) AS TempTable',
								 $strProv, $strMin, $strMin, $strProv, $strSellerId, $strStatus, $strDeadlineWhere);
								 
			$objResult = $objDatabase->Query($strQuery);
			$objResult = $objResult->FetchRow();
			$objResult = (int)$objResult[0];
			return $objResult;
		}
		
		/**
		 * Provision for an amount
		 *
		 * @param int $intAmount
		 * @return int
		 */
		protected static function CalculateProvision($intAmount) {
			$intProvision = 0;
			if (($intProvision = round($intAmount * OQTOPUS_PROVISION, 0)) < OQTOPUS_MINIMUM_PROVISION)
				$intProvision = OQTOPUS_MINIMUM_PROVISION;
				
			return $intProvision;
		}
	}
?>