<?php
	/**
	 * Abstract class to communicate with factoring service
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	abstract class Factoring {
		
		/**
		 * Check if a login is credit worthy (has got unpaid bills)
		 *
		 * @param Login $objLogin
		 * @return bool
		 */
		public static function CheckWorthy(Login $objLogin) {
			return true;
		}
	}
?>