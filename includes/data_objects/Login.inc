<?php
	require(__INCLUDES__ . 'data_objects_generated/LoginGen.inc');

	/**
	 * The Login class defined here contains any
	 * customized code for the Login class in the
	 * Object Relational Model.  It represents the "login" table 
	 * in the database, and extends from the code generated abstract LoginGen
	 * class, which contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package Oqtopus
	 * @subpackage DataObjects
	 * 
	 */
	class Login extends LoginGen {
		protected $objAssociatedCache;
		
		/**
		 * Default "to string" handler
		 * Allows pages to "echo" or "print" this object, and to define the default
		 * way this object would be outputted.
		 *
		 * Can also be called directly via $objLogin->__toString().
		 *
		 * @return string a nicely formatted string representation of this object
		 */
		public function __toString() {
			return sprintf('Login Object %s',  $this->intId);
		}
		
		/**
		 * Cache LastLogin in session and set real one to current date and time
		 *
		 */
		public function UpdateLastLogin() {
			$_SESSION[__CLASS__.$this->intId.'_LastLogin'] = $this->dttLastLogin;
			$this->dttLastLogin = new QDateTime(QDateTime::Now);
		}
		
		/**
		 * Override __get to hide Salt
		 *
		 * Otherwise, call parent
		 *
		 * @param string $strName Name of the property to get
		 * @return mixed
		 */
		public function __get($strName) {
			switch ($strName) {
				case 'Password':
				case 'Salt':
					$objReflection = new ReflectionClass($this);
					throw new QUndefinedPropertyException("GET", $objReflection->getName(), $strName);
					break;
					
				case 'LastLogin':
					return isset($_SESSION[__CLASS__.$this->intId.'_LastLogin']) ? $_SESSION[__CLASS__.$this->intId.'_LastLogin'] : $this->dttLastLogin;
					
				case 'Worthy':
					if (!$this->dttLastWorthyCheck || $this->dttLastWorthyCheck->Timestamp < (time() - 86400 * OQTOPUS_WORTHY_VALID_DAYS)) {
						$this->intWorthy = (int)Factoring::CheckWorthy($this);
						$this->dttLastWorthyCheck = new QDateTime(QDateTime::Now);
						$this->Save();
					}
					
					return (bool)$this->intWorthy;
					
				default:
					return parent::__get($strName);
					break;
			}
		}

		/**
		 * Override __set to encrypt and salt Password
		 *
		 * In any other case, just call parent
		 * Oh, and hide Salt as well
		 *
		 * @param string $strName Name of the property to set
		 * @param string $mixValue New value of the property
		 * @return mixed
		 */
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case "Salt":
				case "LastLogin":
				case 'Worthy':
				case 'LastWorthyCheck':
				case 'RegistrationDate':
					$objReflection = new ReflectionClass($this);
					throw new QUndefinedPropertyException("SET", $objReflection->getName(), $strName);
					break;
				
				case "Password":
					$salt = Random::generateChars(OQTOPUS_PASSWORD_SALT_LENGTH);
					$mixValue = $salt . $mixValue;
					$mixValue = hash(OQTOPUS_PASSWORD_HASH_ALGORITHM, $mixValue);
					parent::__set("Salt", $salt);
					
				default:
					try {
						return parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
					break;
			}
		}
		
		public function GetNetworkUserArrayWithSellerNameAndNetworkname($strSortInfo = null, $strLimitInfo = null, $objExpansionMap = null) {
			if (!$this->intId)
				return array();
				
			return NetworkUser::LoadArrayByLoginIdWithSellerNameAndNetworkName($this->intId, $strSortInfo, $strLimitInfo, $objExpansionMap);
		}
		
		/**
		 * Check if a password is correct
		 *
		 * @param string $strPass The password
		 * @return boolean
		 */
		public function CheckPass($strPassword) {
			$strPassword = $this->strSalt . $strPassword;
			$strPassword = hash(OQTOPUS_PASSWORD_HASH_ALGORITHM, $strPassword);
			
			if ($strPassword == $this->strPassword)
				return true;
			else 
				return false;
		}
		
		/**
		 * If key is correct, place login in confirmed status
		 * if ket is incorrect, throws WrongParametersException
		 *
		 * @param string $strKey
		 */
		public function Activate($strKey) {		
			if ($this->Status != LoginStatus::Registered)
				throw new Exception('This login is already active!');
				
			if ($this->strNotes != $strKey)
				throw new WrongParametersException();
				
			$this->strNotes = null;
			$this->Status = LoginStatus::Confirmed;
		}
		
		/**
		 * Get all SIM-ads exclusively available to me
		 *
		 * @param string $strSortInfo
		 * @param string $strLimitInfo
		 * @param bool[] $objExpansionMap
		 * @return Ad[]
		 */
		public function GetAvailableOffers($strSortInfo = null, $strLimitInfo = null, $objExpansionMap = null) {
			if (!$this->intId)
				return array();
				
			return Ad::GetAvailableOffersByLogin($this, $strSortInfo, $strLimitInfo, $objExpansionMap);
		}
		
		/**
		 * Save (wrapper to set RegistrationDate if insert
		 *
		 * @param bool $blnForceInsert
		 * @param bool $blnForceUpdate
		 */
		public function Save($blnForceInsert = false, $blnForceUpdate = false) {
			if ($blnForceInsert || !$this->__blnRestored)
				$this->dttRegistrationDate = new QDateTime(QDateTime::Now);
				
			try {
				parent::Save($blnForceInsert, $blnForceUpdate);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
		}

		/** THESE MUST BE ABLE TO HANDLE OTHER SIDE OF ONE2MANY RELATIONS ANS WELL */
		
		/**
		 * Checks if the passed object is associted with this object.
		 * Fetches all objects from DB and caches them in this object,
		 * so if there's reason to believe that there is many associated objects of same type,
		 * use non-cache version isntead
		 *
		 * @param QBaseClass $objForeign
		 * @param boolean $blnForceUpdate
		 * @return boolean
		 */
		public function CachedIsAssociatedWith(QBaseClass $objForeign, $blnForceUpdate = false) {
			$strForeign = get_class($objForeign);
			
			// Have we already fetched the list and cached it?
			if ($blnForceUpdate || !(isset($this->objAssociatedCache[$strForeign])))
				$this->objAssociatedCache[$strForeign] = $this->{sprintf('Get%sArray', $strForeign)}();
				
			foreach ($this->objAssociatedCache[$strForeign] as $objCached)
				if ($objCached->Id == $objForeign->Id)
					return true;
			
			return false;
		}
		
		public function IsAssociatedWith(QBaseClass $objForeign) {
			self::QueryHelper($objDatabase);
			
			$strForeign = strtolower(get_class($objForeign));
			$strThis = strtolower(get_class($this));
			
			$strForeignId = $objDatabase->SqlVariable($objForeign->Id);
			$strThisId = $objDatabase->SqlVariable($this->Id);
			
			$strQuery = sprintf('SELECT id FROM %s WHERE id = %s AND %s_id = %s LIMIT 1',
								$strForeign, $strForeignId, $strThis, $strThisId);
								
			$objResult = $objDatabase->Query($strQuery);
			return (bool)$objResult->CountRows();
		}
	}
		
?>