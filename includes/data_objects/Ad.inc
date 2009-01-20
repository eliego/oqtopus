<?php
	require(__INCLUDES__ . 'data_objects_generated/AdGen.inc');

	/**
	 * The Ad class defined here contains any
	 * customized code for the Ad class in the
	 * Object Relational Model.  It represents the "ad" table 
	 * in the database, and extends from the code generated abstract AdGen
	 * class, which contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class Ad extends AdGen {
		protected $strKeywords;
		protected $blnKeywordsChanged = false;
		
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objAd->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('Ad Object %s',  $this->intId);
		}

		/**
		 * Load ads of specified type from specified Seller
		 *  
		 * @param Seller $objSeller
		 * @param AdType $strType
		 * @param boolean $blnIncludeExpired Include expired SIM:s or not?
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		 */
		public static function LoadArrayBySellerAndType(Seller $objSeller, $strType = null, $blnIncludeExpired = false, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$strWhere = sprintf('ad.seller_id = %s', $objDatabase->SqlVariable($objSeller->Id));
			if ($strType)
				$strWhere .= sprintf(' AND ad.type = %s', $objDatabase->SqlVariable($strType));
			if (!$blnIncludeExpired)
				$strWhere .= sprintf(' AND (ad.deadline IS NULL OR ad.deadline >= %s)', time());

			$strQuery = sprintf('SELECT
								%s
								 	ad.*
								 	%s
								 FROM
								 	ad
								 	%s
								 WHERE
								 	%s
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
								 	  $strWhere, $strOrderBy, $strLimitSuffix);
								 	  
			$objResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbResult($objResult);			
		}
		
		/**
		 * Load ads of SIM-type from specified Seller, avaialable for speified Login
		 *  
		 * @param Seller $objSeller
		 * @param Login $objLogin
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return Ad[]
		 */
		public static function LoadSimArrayBySellerAndLogin(Seller $objSeller, Login $objLogin, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$strSellerId = $objDatabase->SqlVariable($objSeller->Id);
			$strNow = $objDatabase->SqlVariable(time());
			$strLoginId = $objDatabase->SqlVariable($objLogin->Id);
			
			$strSub = sprintf('SELECT network_user.login_id FROM ad_network_assn, network_user WHERE
							   ad_network_assn.ad_id = ad.id AND ad_network_assn.network_id = network_user.network_id AND network_user.login_id = %s AND network_user.status = "accepted"
							   LIMIT 1', $strLoginId);

			$strQuery = sprintf('SELECT
								%s
								 	ad.*
								 	%s
								 FROM
								 	ad
								 	%s
								 WHERE
								 	  ad.type = "sim"
								 	AND
								 	  ad.seller_id = %s
								 	AND
								 	  (  
								 	     ad.deadline IS NULL
								 	   OR
								 	     ad.deadline >= %s
								 	  )
								 	AND
								 	  (  
								 	     ad.permission_mode IS NULL
								 	  OR
								 	     ad.permission_mode = "all"
								 	  OR  
								 	     (
								 	       ad.permission_mode = "include"
								 	     AND
								 	       EXISTS(%s)
								 	     )
								 	  OR
								 	     (
								 	       ad.permission_mode = "exclude"
								 	     AND
								 	       NOT EXISTS(%s)
								 	     )
								 	  )
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
								 	  $strSellerId, $strNow, $strSub, $strSub, $strOrderBy, $strLimitSuffix);
								 	  
			$objResult = $objDatabase->Query($strQuery);
			return Ad::InstantiateDbResult($objResult);			
		}		
		
		/**
		 * Have deadline passed?
		 *
		 * @return boolean
		 */
		public function IsExpired() {
			return ($this->intDeadline && (time() > $this->intDeadline));
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'Keywords':
					if (!is_array($this->strKeywords)) {
						$this->strKeywords = array();
						foreach ($this->GetKeywordArray() as $objKeyword)
							if ($objKeyword->Keyword != mb_strtolower($this->Seller->SellerName))
								$this->strKeywords[$objKeyword->Id] = $objKeyword->Keyword;
					}
					
					return $this->strKeywords;
					
				case 'KeywordsChanged':
					return $this->blnKeywordsChanged;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Keywords':
					$this->strKeywords = QType::Cast($mixValue, QType::ArrayType);
					$this->blnKeywordsChanged = true;
					break;
					
				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
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

				// Save cache
				$this->Seller->CacheAd = $this;
				$this->Seller->Save();
				
				if ($this->blnKeywordsChanged) {
					if ($this->__blnRestored && !$blnForceInsert)
						$this->UnassociateAllKeywords();
					
					$tempArr = array();	
					try {
						$objK = new Keyword();
						$objK->Keyword = $this->Seller->SellerName;
						$objK->Save();
					} catch (QMySqliDatabaseException $e) {
						if ($e->ErrorNumber == 1062)
							$objK = Keyword::LoadByKeyword($this->Seller->SellerName);
						else 
							throw $e;
					}
					$objK->AssociateAd($this);
					
					foreach ($this->strKeywords as $strKeyword) {
						$objK = null;
						try {
							$objK = new Keyword();
							$objK->Keyword = $strKeyword;
							$objK->Save();
						} catch (QMySqliDatabaseException $e) {
							if ($e->ErrorNumber == 1062) // The keyword already exists
								$objK = Keyword::LoadByKeyword($strKeyword);
							else
								throw $e;
						}
						try {
							$objK->AssociateAd($this);						
							$tempArr[$objK->Id] = $objK->Keyword;
						} catch (QMySqliDatabaseException $e) {// If 1062, it's because the user entered the same keyword twice. Silently ignore.
							if ($e->ErrorNumber != 1062)
								throw $e;
						}
					}
					$this->blnKeywordsChanged = false;
					$this->strKeywords = $tempArr;
				}
				
				Search::MailMatchingSearches($this);

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
		 * This gets called when the ad is created from another ad
		 * Since only some of the properties is supposed to be cached, we set everything else to nulls
		 *
		 */
		public function __clone() {
			$this->__blnRestored = false;
			$this->strName = null;
			$this->strDescription = null;
			$this->intDeadline = null;
			$this->dttPublicationDate = new QDateTime();
			$this->intPrice = null;
			$this->strSex = null;
			$this->intId = 0;
			if ($this->strType == AdType::SIM)
				$this->strPermissionMode = PermissionMode::All;
			else
				$this->strPermissionMode = null;
		}
		
	 	/**
		 * Delete this Ad,
		 * and set sellers cache to null if it's pointing at me
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
			
			// Set sellers cache to null if pointing at me (we don't really have to save
			// We don't really have to save, since it's only in future saves, before reload from db, that results in error
			if ($this->Seller->CacheAdId = $this->Id)
				$this->Seller->CacheAdId = null;
				
		}		
		
		/**
		 * Get all offers exclusively available for a login
		 *
		 * @param Login $objLogin
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param bool[] $objExpansionMap
		 * @return Ad[]
		 */
		public static function GetAvailableOffersByLogin(Login $objLogin, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			Ad::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
			
			$strNow = $objDatabase->SqlVariable(time());
			$strLoginId = $objDatabase->SqlVariable($objLogin->Id);
			
			$strSub = sprintf('SELECT network_user.login_id FROM ad_network_assn, network_user WHERE
							   ad_network_assn.ad_id = ad.id AND ad_network_assn.network_id = network_user.network_id AND network_user.login_id = %s AND network_user.status = "accepted"
							   LIMIT 1', $strLoginId);

			$strQuery = sprintf('SELECT
								%s
								 	ad.*
								 	%s
								 FROM
								 	ad
								 	%s
								 WHERE
								 	  ad.type = "sim"
								 	AND
								 	  (  
								 	     ad.deadline IS NULL
								 	   OR
								 	     ad.deadline >= %s
								 	  )
								 	AND
								 	  (  
								 	     (
								 	       ad.permission_mode = "include"
								 	     AND
								 	       EXISTS(%s)
								 	     )
								 	  OR
								 	     (
								 	       ad.permission_mode = "exclude"
								 	     AND
								 	       NOT EXISTS(%s)
								 	     )
								 	  )
								 %s
								 %s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
									  $strNow, $strSub, $strSub, $strOrderBy, $strLimitSuffix);
									  
			$objResult = $objDatabase->Query($strQuery);
			return self::InstantiateDbResult($objResult);
		}
	}
?>