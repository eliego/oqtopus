<?php
	/**
	 * Abstract class to navigate across the website
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	abstract class Navigation {
		/**
		 * Go to profileform
		 *
		 * @param int $intId
		 */
		static public function ProfileForm($intId) {
			QApplication::Redirect(self::CreateUrl("Profileform", $intId));
		}
		
		/**
		 * Go to MainForm
		 *
		 */
		static public function MainForm() {
			QApplication::Redirect(self::CreateUrl("MainForm"));
		}
		
		static public function Refresh() {
			QApplication::ExecuteJavaScript('document.location.reload(true);');
		}
		
		static public function Home() {
			QApplication::Redirect(self::HomeUrl());
		}
		
		static public function HomeUrl() {
			if (Security::Current())
				switch (Security::Current()->Role) {
					case Role::Buyer:
						return self::CreateUrl('BuyersNewsForm');
						break;
						
					case Role::Seller:
						return self::CreateUrl('SellersNewsForm');
						break;
				}
			else 
				return self::CreateUrl('MainForm');
		}
		
		public static function BuyersNewsForm() {
			QApplication::Redirect(self::CreateUrl('BuyersNewsForm'));
		}
		
		public static function SellersNewsForm() {
			QApplication::Redirect(self::CreateUrl('SellersNewsForm'));
		}
		
		public static function ErrorForm($intId) {
			QApplication::Redirect(self::CreateUrl('ErrorForm', $intId));
		}
		
		/**
		 * Create URL to specified form with specified arguments
		 * 
		 * Arguments can be QBaseClass-objects or plain ints or strings
		 *
		 * @param string $strForm
		 * @param mixed $arg1, $arg2 ... $argN
		 * @return string
		 */
		static public function CreateUrl($strForm) {
			$strArgs = func_get_args();
			$str = '';
			switch (SERVER_INSTANCE) { // Create mod_rewrite-compatible URL if we're in production
				case 'dev':
					$str .= sprintf('%s?form=%s', OQTOPUS_START_URL, $strForm);
					for ($i = 1; $i < sizeof($strArgs); $i++)
						if ($strArgs[$i])
							$str .= sprintf('&arg%d=%s', $i, ($strArgs[$i] instanceof QBaseClass) ? $strArgs[$i]->Id : $strArgs[$i]);
					break;
			
				case 'prod':
				case 'demo':
					$str .= sprintf('%s%s/', OQTOPUS_START_URL, $strForm);
					for ($i = 1; $i < sizeof($strArgs); $i++)
						if ($strArgs[$i])
							$str .= sprintf('%s/', ($strArgs[$i] instanceof QBaseClass) ? $strArgs[$i]->Id : $strArgs[$i]);
					break;
			}	
				
			return $str;
		}
	}
?>
