<?php
	require(__INCLUDES__ . 'data_objects_generated/SearchGen.inc');

	/**
	 * The Search class
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class Search extends SearchGen {
		protected $strKeywords;
		protected $blnKeywordsChanged = false;		
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objSearch->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('Search Object %s',  $this->intId);
		}

		/**
		 * Load an array of sellers
		 * The MIN() and MAX() of the properties of the ads of the sellers gets loaded as virtual attributes, like MinBp and MaxBp
		 * 
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @return Seller[]
		 */
		public function DoSearch($strOrderBy = null, $strLimit = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, null, $objDatabase);
	
			// Construct query
			$strWhere = "";
			$strKeywordFrom = "";
			try {
				if ($this->intReach)
					$strWhere .= sprintf("ad.reach %s %s AND ", self::getSearchOperator($this->intReachMode), $objDatabase->SqlVariable($this->intReach));
				if ($this->intPrice)
					$strWhere .= sprintf("ad.price %s %s AND ", self::getSearchOperator($this->intPriceMode), $objDatabase->SqlVariable($this->intPrice));
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			if ($this->intArea)
				$strWhere .= sprintf("ad.area = %s AND ", $objDatabase->SqlVariable($this->intArea));
			if ($this->intSubArea)
				$strWhere .= sprintf("ad.sub_area = %s AND ", $objDatabase->SqlVariable($this->intSubArea));
			if ($this->intSubSubArea)
				$strWhere .= sprintf("ad.sub_sub_area = %s AND ", $objDatabase->SqlVariable($this->intSubSubArea));
			if ($this->intAge)
				$strWhere .= sprintf("ad.start_age <= %s AND ad.end_age >= %s AND ", $temp = $objDatabase->SqlVariable($this->intAge), $temp);
			if ($this->strSex)
				$strWhere .= sprintf("ad.sex = %s AND ", $objDatabase->SqlVariable($this->strSex));
			if ($this->intSalary)
				$strWhere .= sprintf("ad.salaries & %s = %s AND ", $temp = $objDatabase->SqlVariable($this->intSalary), $temp);
			if ($this->intEducation)
				$strWhere .= sprintf("ad.educations & %s = %s AND ", $temp = $objDatabase->SqlVariable($this->intEducation), $temp);
			if ($this->intSector)
				$strWhere .= sprintf("ad.sectors & %s = %s AND ", $temp = $objDatabase->SqlVariable($this->intSector), $temp);
			if ($this->intMediaType)
				$strWhere .= sprintf("ad.media_type = %s AND ", $objDatabase->SqlVariable($this->intMediaType)); 
			if ($this->intMediaSubType)
				$strWhere .= sprintf("ad.media_sub_type = %s AND ", $objDatabase->SqlVariable($this->intMediaSubType));
			if ($this->Keywords) {
				if ($this->blnKeywordsChanged) { // Have we changed keywords since load? In that case we have to join with keyword
					switch ($this->KeywordMode) {
						case KeywordMode::Eller:
							$strWhere .= "ad_keyword_assn.ad_id = ad.id AND ad_keyword_assn.keyword_id = keyword.id AND (";
							$strKeywordFrom .= ", ad_keyword_assn, keyword";
							foreach($this->Keywords AS $strKeyword)
								$strWhere .= sprintf("keyword.keyword = %s OR ", $objDatabase->SqlVariable($strKeyword));
							$strWhere = substr($strWhere, 0, -4) . ") AND ";
							break;
							
						case KeywordMode::Och:
							for ($i = 0; $i < sizeof($this->Keywords); $i++) {
								$strKeywordFrom .= sprintf(', ad_keyword_assn AS k%d, keyword AS keyword%d', $i, $i);
								$strWhere .= sprintf('k%d.ad_id = ad.id AND k%d.keyword_id = keyword%d.id AND keyword%d.keyword = %s AND ', $i, $i, $i, $i, $objDatabase->SqlVariable($this->strKeywords[$i]));
							}
							break;
					}
				} else { // Otherwise, we just insert the keyword ID:s
					switch ($this->KeywordMode) {
						case KeywordMode::Eller:
							$strWhere .= "ad_keyword_assn.ad_id = ad.id AND (";
							$strKeywordFrom .= ", ad_keyword_assn";
							foreach($this->Keywords AS $intId => $strKeyword)
								$strWhere .= sprintf("ad_keyword_assn.keyword_id = %s OR ", $objDatabase->SqlVariable($intId));
							$strWhere = substr($strWhere, 0, -4) . ") AND ";
							break;
							
						case KeywordMode::Och:
							foreach ($this->Keywords as $key => $strKeyword) {
								$strKeywordFrom .= sprintf(', ad_keyword_assn AS k%d', $key);
								$strWhere .= sprintf('k%d.ad_id = ad.id AND k%d.keyword_id = %s AND ', $key, $key, $objDatabase->SqlVariable($key));
							}
							break;
					}
				}
			}
			
			// Cut
			if (strlen($strWhere) > 5)
				$strWhere = substr($strWhere, 0, -5);
			else 
				$strWhere = 1;
				
			$query = sprintf("SELECT
							  %s
							  	seller.id,
							  	seller.seller_name,
							  	MIN(ad.price) AS __MinPrice,
							  	MAX(ad.price) AS __MaxPrice,
							  	MIN(ad.reach) AS __MinReach,
							  	MAX(ad.reach) AS __MaxReach,
							  	BIT_OR(ad.area) AS __Areas,
							  	BIT_OR(ad.media_type) AS __Medias
							  FROM
							  	seller,
							  	ad
							  	%s
							  WHERE
							  	%s
							  	AND seller.id = ad.seller_id
							  	AND (ad.type != 'sim' OR ad.permission_mode = 'all')
							  GROUP BY
							  	seller.id
							  %s
							  %s", $strLimitPrefix, $strKeywordFrom,
							  	   $strWhere, $strOrderBy, $strLimitSuffix);

			$result = $objDatabase->Query($query);
			return Seller::InstantiateDbResult($result);
		}
		
		/**
		 * Load searches that would match the specified ad, and have send_email = 1
		 *
		 * @param Ad $objAd
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param string $objExpansionMap
		 * @return Search[]
		 */
		public static function LoadByAd(Ad $objAd, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// We don't care about SIM-searches with permissions other than all
			if ($objAd->Type == AdType::SIM && $objAd->PermissionMode != PermissionMode::All )
				return array();
				
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			Search::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);
	
			// Construct query
			$strWhere = "";
			$strKeywordFrom = "";
			$strGT = $objDatabase->SqlVariable(SearchParameterMode::GT);
			$strLT = $objDatabase->SqlVariable(SearchParameterMode::LT);
			try {
				if ($objAd->Reach)
					$strWhere .= sprintf("(search.reach IS NULL OR (search.reach < %s AND search.reach_mode = %s) OR (search.reach > %s AND search.reach_mode = %s)) AND ", $temp = $objDatabase->SqlVariable($objAd->Reach), $strGT, $temp, $strLT);
				if ($objAd->Price)
					$strWhere .= sprintf("(search.price IS NULL OR (search.price < %s AND search.price_mode = %s) OR (search.price > %s AND search.price_mode = %s)) AND ", $temp = $objDatabase->SqlVariable($objAd->Price), $strGT, $temp, $strLT);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			if ($objAd->Area)
				$strWhere .= sprintf("(search.area IS NULL OR search.area = %s) AND ", $objDatabase->SqlVariable($objAd->Area));
			if ($objAd->SubArea)
				$strWhere .= sprintf("(search.sub_area IS NULL OR search.sub_area = %s) AND ", $objDatabase->SqlVariable($objAd->SubArea));
			if ($objAd->SubSubArea)
				$strWhere .= sprintf("(search.sub_sub_area IS NULL OR search.sub_sub_area = %s) AND ", $objDatabase->SqlVariable($objAd->SubSubArea));
			if ($objAd->StartAge)
				$strWhere .= sprintf("(search.age IS NULL OR (search.age >= %s AND search.age <= %s)) AND ", $objDatabase->SqlVariable($objAd->StartAge), $objDatabase->SqlVariable($objAd->EndAge));
			if ($objAd->Sex)
				$strWhere .= sprintf("(search.sex IS NULL OR search.sex = %s) AND ", $objDatabase->SqlVariable($objAd->Sex));
			if ($objAd->Salaries)
				$strWhere .= sprintf("(search.salary IS NULL OR search.salary & %s = %s) AND ", $temp = $objDatabase->SqlVariable($objAd->Salaries), $temp);
			if ($objAd->Educations)
				$strWhere .= sprintf("(search.education IS NULL OR search.education & %s = %s) AND ", $temp = $objDatabase->SqlVariable($objAd->Educations), $temp);
			if ($objAd->Sectors)
				$strWhere .= sprintf("(search.sector IS NULL OR search.sector & %s = %s) AND ", $temp = $objDatabase->SqlVariable($objAd->Sectors), $temp);
			if ($objAd->MediaType)
				$strWhere .= sprintf("(search.media_type IS NULL OR search.media_type = %s) AND ", $objDatabase->SqlVariable($objAd->MediaType)); 
			if ($objAd->MediaSubType)
				$strWhere .= sprintf("(search.media_sub_type IS NULL OR search.media_sub_type = %s) AND ", $objDatabase->SqlVariable($objAd->MediaSubType));
			if ($strKeywords = $objAd->Keywords) {
				$strSub = '';
				if ($objAd->KeywordsChanged) { // We have to look up by actual keyword
					foreach ($strKeywords as $strKeyword)
						$strSub[] = sprintf('keyword.keyword != %s', $objDatabase->SqlVariable($strKeyword));
					$strSub = implode(' AND ', $strSub);
					$strSub = sprintf('SELECT keyword.id FROM keyword, search_keyword_assn WHERE search_keyword_assn.search_id = search.id AND search_keyword_assn.keyword_id = keyword.id AND %s LIMIT 1', $strSub);
				} else { // We alredy got keyword id's
					foreach ($strKeywords as $intKey => $strKeyword)
						$strSub[] = sprintf('search_keyword_assn.keyword_id != %s', $objDatabase->SqlVariable($intKey));
						$strSub = implode (' AND ', $strSub);
						$strSub = sprintf('SELECT * FROM search_keyword_assn WHERE search_keyword_assn.search_id = search.id AND %s LIMIT 1', $strSub);
				}
				
				$strWhere .= sprintf("(search.keyword_mode IS NULL OR (search.keyword_mode = %s AND NOT EXISTS(%s))) AND ", $objDatabase->SqlVariable(KeywordMode::Och), $strSub); // OR (search.keyword_mode = %s AND ", $objDatabase->SqlVariable(KeywordMode::Och));	
			}
			
			// Cut
			if (strlen($strWhere) > 5)
				$strWhere = substr($strWhere, 0, -5);
			else 
				$strWhere = 1;
				
			$query = sprintf("SELECT
							  %s
							  	search.name
								%s
							  FROM
							  	search
							  %s
							  WHERE
							  	%s
							  	AND search.send_email = 1
							  %s
							  %s", $strLimitPrefix, $strExpandSelect, $strExpandFrom,
							  	   $strWhere, $strOrderBy, $strLimitSuffix);
							  	   
			$result = $objDatabase->Query($query);
			return Search::InstantiateDbResult($result);			
		}
		
		/**
		 * Get search operator by SearchParameterMode
		 *
		 * @param SearchParameterMode $intSearchMode
		 * @return string
		 */
		private static function getSearchOperator($intSearchMode) {
			switch ($intSearchMode) {
				case SearchParameterMode::GT:
					return '>=';
				case SearchParameterMode::LT:
					return '<=';
				default:
					throw new WrongParametersException(_tr("Argument must be a SearchParameterMode"));
			}
		}
		
		/**
		 * Send a mail to everyone who owns a search that match the ad (and wants it, of course)
		 *
		 * @param Ad $objAd
		 */
		public static function MailMatchingSearches(Ad $objAd) {
			$Expansion[self::ExpandLogin] = true;
			foreach (self::LoadByAd($objAd, null, null, $Expansion) as $objSearch)
				Mail::SendNewSearchResult($objSearch);
		}
		
		/**
		 * TODO: To be removed. Super takes care of this much better
		 * 
		 * Save this Search
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 * @return int
		*/
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			// Call to QueryHelper to Get the Database Object
			Search::QueryHelper($objDatabase);

			$mixToReturn = null;

			try {
				if ((!$this->__blnRestored) || ($blnForceInsert)) {
					// Perform an INSERT query
					$objDatabase->NonQuery('
						INSERT INTO `search` (
							`login_id`,
							`reach_mode`,
							`reach`,
							`price_mode`,
							`price`,
							`age`,
							`area`,
							`send_email`,
							`media_type`,
							`media_sub_type`,
							`sex`,
							`sector`,
							`salary`,
							`education`,
							`sub_area`,
							`sub_sub_area`,
							`name`,
							`keyword_mode`
						) VALUES (
							' . $objDatabase->SqlVariable($this->intLoginId) . ',
							' . $objDatabase->SqlVariable($this->intReachMode) . ',
							' . $objDatabase->SqlVariable($this->intReach) . ',
							' . $objDatabase->SqlVariable($this->intPriceMode) . ',
							' . $objDatabase->SqlVariable($this->intPrice) . ',
							' . $objDatabase->SqlVariable($this->intAge) . ',
							' . $objDatabase->SqlVariable($this->intArea) . ',
							' . $objDatabase->SqlVariable($this->intSendEmail) . ',
							' . $objDatabase->SqlVariable($this->intMediaType) . ',
							' . $objDatabase->SqlVariable($this->intMediaSubType) . ',
							' . $objDatabase->SqlVariable($this->strSex) . ',
							' . $objDatabase->SqlVariable($this->intSector) . ',
							' . $objDatabase->SqlVariable($this->intSalary) . ',
							' . $objDatabase->SqlVariable($this->intEducation) . ',
							' . $objDatabase->SqlVariable($this->intSubArea) . ',
							' . $objDatabase->SqlVariable($this->intSubSubArea) . ',
							' . $objDatabase->SqlVariable($this->strName) . ',
							' . $objDatabase->SqlVariable($this->strKeywordMode) . '
						)
					');

					// Update Identity column and return its value
					$mixToReturn = $this->intId = $objDatabase->InsertId('search', 'id');
				} else {
					// Perform an UPDATE query

					// First checking for Optimistic Locking constraints (if applicable)

					// Perform the UPDATE query
					$objDatabase->NonQuery('
						UPDATE
							`search`
						SET
							`login_id` = ' . $objDatabase->SqlVariable($this->intLoginId) . ',
							`reach_mode` = ' . $objDatabase->SqlVariable($this->intReachMode) . ',
							`reach` = ' . $objDatabase->SqlVariable($this->intReach) . ',
							`price_mode` = ' . $objDatabase->SqlVariable($this->intPriceMode) . ',
							`price` = ' . $objDatabase->SqlVariable($this->intPrice) . ',
							`age` = ' . $objDatabase->SqlVariable($this->intAge) . ',
							`area` = ' . $objDatabase->SqlVariable($this->intArea) . ',
							`send_email` = ' . $objDatabase->SqlVariable($this->intSendEmail) . ',
							`media_type` = ' . $objDatabase->SqlVariable($this->intMediaType) . ',
							`media_sub_type` = ' . $objDatabase->SqlVariable($this->intMediaSubType) . ',
							`sex` = ' . $objDatabase->SqlVariable($this->strSex) . ',
							`sector` = ' . $objDatabase->SqlVariable($this->intSector) . ',
							`salary` = ' . $objDatabase->SqlVariable($this->intSalary) . ',
							`education` = ' . $objDatabase->SqlVariable($this->intEducation) . ',
							`sub_area` = ' . $objDatabase->SqlVariable($this->intSubArea) . ',
							`sub_sub_area` = ' . $objDatabase->SqlVariable($this->intSubSubArea) . ',
							`name` = ' . $objDatabase->SqlVariable($this->strName) . ',
							`keyword_mode` = ' . $objDatabase->SqlVariable($this->strKeywordMode) . '
						WHERE
							`id` = ' . $objDatabase->SqlVariable($this->intId) . '
					');
				}
				
				if ($this->blnKeywordsChanged) { // Keywords changed, we have to update keyword table as well
					if ($this->__blnRestored && !$blnForceInsert)
						$this->UnassociateAllKeywords();
					
					$tempArr = array();		
					foreach ($this->strKeywords as $key => $strKeyword) {
						$objK = null;
						try { // Try to insert keyword
							$objK = new Keyword();
							$objK->Keyword = $strKeyword;
							$objK->Save();
						} catch (QMySqliDatabaseException $e) {
							if ($e->ErrorNumber == 1062) // Error cause of the UNIQUE INDEX in db, the keyword already exists
								$objK = Keyword::LoadByKeyword($strKeyword);
							else // Unknown error
								throw $e;
						}
						try {
							$objK->AssociateSearch($this);						
							$tempArr[$objK->Id] = $objK->Keyword;
						} catch (QMySqliDatabaseException $e) {
							if ($e->ErrorNumber != 1062) // If 1062, it's because the user entered the same keyword twice. Silently ignore.
								throw $e;
						}
					}
					$this->strKeywords = $tempArr;
					$this->blnKeywordsChanged = false;
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
		
		public function __get($strName) {
			switch ($strName) {
				case 'Keywords':
					if (!is_array($this->strKeywords)) {
						$this->strKeywords = array();
						foreach ($this->GetKeywordArray() as $objKeyword)
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
	}
?>