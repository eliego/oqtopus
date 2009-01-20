<?php
	/**
	 * Security - handles user authentication, permissions etc
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class Security {
		/**
		 * AuthLogin
		 *
		 * Used to login with a username and a password
		 *
		 * @param string $strUsername Username
		 * @param string @strPassword Password
		 * @return Login
		 */
		public static function AuthLogin($strUsername, $strPassword) {
			if (!($login = Login::LoadByUsername($strUsername)))
				throw new AuthenticationException(QApplication::Translate("No such user"), AuthenticationErrorCause::Username);
		
			if ($login->Status != LoginStatus::Confirmed)
				throw new AuthenticationException(QApplication::Translate('Your account is inactive'), AuthenticationErrorCause::Username);
			
			if (!$login->CheckPass($strPassword)) {
				// Log out if user is logged in (this should never happen, hopefully)
				if (self::Current())
					    self::Logout();
                    
				throw new AuthenticationException(QApplication::Translate("Wrong password"), AuthenticationErrorCause::Password);
			}
			
			return self::Login($login);
		}
		
		/**
		 * Log in specified user
		 *
		 * @param Login $objLogin
		 * @return Login
		 */
		public static function Login(Login $objLogin) {
			if (self::Current())
				throw new AlreadyLoggedInException();
			
			$_SESSION['currentuser'] = $objLogin;
			$objLogin->UpdateLastLogin();
			$objLogin->Save();
			
			return $objLogin;
		}	
	
		/**
		 * Gets the curerently logged in user
		 *
		 * @return Login
		 */
		public static function Current() {
			if (isset($_SESSION['currentuser']) && $_SESSION['currentuser'] instanceof Login)
				return $_SESSION['currentuser'];
			else
				return null;
		}
		
		/**
		 * Logs out currently logged in user
		 *
		 * @return void
		 */
		public static function Logout() {
			if (self::Current())
				unset($_SESSION['currentuser']);
			else
				throw new NotLoggedInException();
		}
		
		/**
		 * Check if a user has got access to a specified action
		 *
		 * @param Actions $intAction The action
		 * @param mixed $mixArg1
		 * @param mixed $mixArg2
		 * @param Login $objLogin Optional user to check instead of logged in (specify false to check for no user)
		 * @return boolean
		 */
		public static function CheckAccess($intAction, $mixArg1 = null, $mixArg2 = null, $objLogin = null) {
			if ($objLogin === null)
				$objLogin = self::Current() ? self::Current() : false;
				
			if (!($objLogin instanceof Login || $objLogin === false))
				throw new WrongParametersException('objLogin must be a Login object or false for guest');
				
			switch ($intAction) {
				case Actions::ManageAds:
					return ($mixArg1 instanceof Seller && $objLogin) ? $objLogin->CachedIsAssociatedWith($mixArg1) : false;
					
				case Actions::Browse:
				case Actions::SeeProfile:
				case Actions::Search:
					return (bool)($objLogin);
					
				case Actions::MakeBid:
				case Actions::ApplyForNetwork:
				case Actions::SeeNetworks;
					return ($objLogin && $objLogin->Role == Role::Buyer);
					
				case Actions::SeeOffers:
					return ($objLogin && $mixArg1 instanceof Login && $mixArg1->Id == $objLogin->Id);
					
				case Actions::ManageBids:
				case Actions::ManageNetworks:
				case Actions::ViewNews:
				case Actions::ManageSettings:
					if (!$objLogin)
						return false;
					elseif ($objLogin->Role == Role::Buyer && $mixArg1 instanceof Login)
						return ($mixArg1->Id == $objLogin->Id);
					elseif ($objLogin->Role == Role::Seller && $mixArg1 instanceof Seller)
						return $objLogin->CachedIsAssociatedWith($mixArg1);
					else
						throw new WrongParametersException('Arg1 must be Login or Seller, depending on role');
					break;
				
				case Actions::Register:
					return !$objLogin;
					
				default:
					throw new NoSuchActionDefinedException();
			}
		}
		
		/**
		 * Make sure a user has got access to a specified action
		 *
		 * @param Actions $intAction The action
		 * @param mixed Arg1
		 * @param mixed Arg2
		 * @param Login Optional user to check instead of logged in (specify false to check for no user)
		 * @return void
		 */
		public static function VerifyAccess($intAction, $mixedArg1 = null, $mixedArg2 = null, $objLogin = null) {
			try {
				if (!self::CheckAccess($intAction, $mixedArg1, $mixedArg2, $objLogin))
						throw new AccessDeniedException();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
		}
		
		/**
		 * Get, possibly cached, SellerArray
		 * 
		 * @param Login $objLogin
		 * @return Seller[]
		 */
		protected static function GetSellerArray(Login $objLogin) {
			if (!isset($_SESSION[$objLogin->Id.'_SellerArray']))
				$_SESSION[$objLogin->Id.'_SellerArray'] = $objLogin->GetSellerArray();
				
			return $_SESSION[$objLogin->Id.'_SellerArray'];
		}
		
		/**
		 * Check if Login can Manage Seller
		 * 
		 * @param Login $objLogin
		 * @param Seller $objSeller
		 * @return bool
		 */
		protected static function CanManage($objLogin, Seller $objSeller) {
			if (!$objLogin)
				return false;
				
			foreach (self::GetSellerArray($objLogin) as $objLoginsSeller)
				if ($objLoginsSeller->Id == $objSeller->Id)
					return true;
					
			return false;
		}
	}
?>