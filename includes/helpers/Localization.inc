<?php
	/**
	 * Handles all localization things
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	abstract class Localization {
		public static $DateFormat = "j/n -y";
		/**
		 * Valide an organization number
		 *
		 * @param $strNum 
		 * @return bool
		 */
		public static function ValidateOrganizationNumber($strNum) {
			switch (QApplication::$CountryCode) {
				case 'se':
					if ( preg_match('/^(16)??[0-9]{2}[2-9][0-9]{3}-?[0-9]{4}$/', $strNum) && 
						 ( $strNum{6} == '-' ? Math::Modulo10Validate(substr($strNum, 0, 6) . substr($strNum, 7)) : Math::Modulo10Validate($strNum) ))
						return true;
					break;
					
				default:
					return true;
					
			}
			return false;
		}
		
		/**
		 * Format a timestamp
		 *
		 * @param long $lngTimestamp
		 * @return string
		 */
		public static function FormatTimestamp($lngTimestamp) {
			$strFormat = "";
			switch (QApplication::$CountryCode) {
				case 'se':
					$strFormat = "j/n -y";
					break;
				
				case 'us':
				default:
					break;
			}
			return date($strFormat, $lngTimestamp);
		}
	}
?>