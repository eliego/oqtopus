<?php

/**
 * Random class
 *
 * Helper class to generate random numbers and strings
 * of various kinds.
 *
 * @author Kung den Knege <kungdenknege@gmail.com>
 * @package Oqtopus
 * @subpackage HelperClasses
 */
abstract class Random {
    /**
     * Generate random characters
     *
     * This method generates a string of random ASCII characters
     * of specified length.
     *
     * @param integer @iLen Length of generated string
     * @return string
     */
    public static function generateChars($iLen) {
        $result = "";
        
        for ($i = 0; $i < $iLen; $i++)
            $result .= chr(rand(1,127));
            
        return $result;
    }
    
    public static function generateUpperChars($iLen) {
    	$result = "";
    	
    	for ($i = 0; $i < $iLen; $i++)
    		$result .= chr(rand(65,90));
    		
    	return $result;
    }
}
    
?>