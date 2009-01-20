<?php
	/**
	 * Just some mathematical methods
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	abstract class Math {
		/**
		 * Calculate Modulo 10 checkdigit of string of digits
		 *
		 * @param string $str String of digits
		 * @return int
		 */
		public static function Modulo10($str) {
			if (!is_numeric($str))
				throw new WrongParametersException("Argument must be digits only");
				
			$str = (string)$str;
			$res = 0;
			for ($i = 0; $i < strlen($str); $i++) {
				$r = (int)$str{$i} * ($i & 1 ? 1 : 2);
			
				if ($r > 9) {
					$r = (string)$r;
					$res += (int)$r{0} + (int)$r{1};
				} else 
					$res += $r;
			}
			$res = $res % 10;	
			$res = 10 - $res;
			if ($res == 10)
				$res = 0;
			return $res;
		}
	
		/**
		 * Validate a string of digits
		 * The last digit is supposed to be a Modulo 10 ckeckdigit
		 *
		 * @param string $str String of digits
		 * @return boolean
		 */
		public static function Modulo10Validate($str) {
			try {
				$check = self::Modulo10(substr($str, 0, -1));
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}

			if ($check == substr($str, -1, 1))
				return true;
			else
				return false;
		}
	}
?>