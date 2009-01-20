<?php
	if (!isset($__blnPrependIncluded)) {
		// Ensure prepend.inc is only executed once
		$__blnPrependIncluded = true;


		//////////////////////////////
		// Setup __INCLUDES__ constant
		//////////////////////////////
		/*
		 * This assumes that prepend.inc is in the top level of the
		 * "includes/" directory (and thus, the rest of the qcodo
		 * framework is inside the "includes/qcodo/" subdirectory)
		 */
		define('__INCLUDES__', dirname(__FILE__) . '/');
		
		define('__TEMPLATES__', sprintf("%s../templates/", __INCLUDES__));

		///////////////////////////////////
		// Define Server-specific constants
		///////////////////////////////////	
		/*
		 * For obvious security reasons, you can feel
		 * free to move this file OUT of the docroot,
		 * and to provide a relative or absolute path to the file.
		 */
		require(__INCLUDES__ . '_configuration.inc');

		//////////////////////////////
		// Include the Qcodo Framework
		//////////////////////////////
		require(__INCLUDES__ . 'qcodo/qcodo.inc');

		///////////////////////////////
		// Define the Application Class
		///////////////////////////////
		/**
		 * The Application class is an abstract class that statically provides
		 * information and global utilities for the entire web application.
		 *
		 * Custom constants for this webapp, as well as global variables and global
		 * methods should be declared in this abstract class (declared statically).
		 *
		 * This Application class should extend from the ApplicationBase class in
		 * the framework.
		 */
		abstract class QApplication extends QApplicationBase {
			public static $FormName;
			/**
			 * This is called by the PHP5 Autoloader.  This method overrides the
			 * one in ApplicationBase.
			 *
			 * @return void
			 */
			public static function Autoload($strClassName) {
				// First use the Qcodo Autoloader
				parent::Autoload($strClassName);
				
				if (!class_exists($strClassName)) {
					if (file_exists($file = sprintf('%sqforms/%s.inc', __INCLUDES__, $strClassName)))
						require($file);
					elseif (file_exists($file = sprintf('%shelpers/%s.inc', __INCLUDES__, $strClassName)))
						require($file);
					elseif (file_exists($file = sprintf('%sexceptions/%s.inc', __INCLUDES__, $strClassName)))
						require($file);
				}
			}

			////////////////////////////
			// QApplication Customizations (e.g. EncodingType, etc.)
			////////////////////////////
			// public static $EncodingType = 'UTF-8';

			////////////////////////////
			// Additional Static Methods
			////////////////////////////
			// TODO: Define any other custom global WebApplication functions (if any) here...
		}


		//////////////////////////
		// Custom Global Functions
		//////////////////////////	
		// TODO: Define any custom global functions (if any) here...


		////////////////
		// Include Files
		////////////////
		// TODO: Include any other include files (if any) here...
		
		require(__INCLUDES__ . "helpers/enumerations.inc");


		///////////////////////
		// Setup Error Handling
		///////////////////////
		/*
		 * Set Error/Exception Handling to the default
		 * Qcodo HandleError and HandlException functions
		 * (Only in non CLI mode)
		 *
		 * Feel free to change, if needed, to your own
		 * custom error handling script(s).
		 */
		if (array_key_exists('SERVER_PROTOCOL', $_SERVER)) {
			//set_error_handler('QcodoHandleError');
			set_exception_handler(EXCEPTION_HANDLER);
		}


		////////////////////////////////////////////////
		// Initialize the Application and DB Connections
		////////////////////////////////////////////////
		QApplication::Initialize();
		QApplication::InitializeDatabaseConnections();


		/////////////////////////////
		// Start Session Handler (if required)
		/////////////////////////////
		session_start();


		//////////////////////////////////////////////
		// Setup Internationalization and Localization (if applicable)
		// Note, this is where you would implement code to do Language Setting discovery, as well, for example:
		// * Checking against $_GET['language_code']
		// * checking against session (example provided below)
		// * Checking the URL
		// * etc.
		// TODO: options to do this are left to the developer
		//////////////////////////////////////////////
/*		if (isset($_SESSION)) {
			if (array_key_exists('country_code', $_SESSION))
				QApplication::$CountryCode = $_SESSION['country_code'];
			if (array_key_exists('language_code', $_SESSION))
				QApplication::$LanguageCode = $_SESSION['language_code'];
		}
*/
		QApplication::$LanguageCode = "sv";
		QApplication::$CountryCode = "se";
		QApplication::$EncodingType = "UTF-8";
		mb_internal_encoding(QApplication::$EncodingType);
		date_default_timezone_set('Europe/Stockholm');
		header(sprintf('Content-Type: text/html; charset=%s', QApplication::$EncodingType));
		
		QI18n::Initialize();

	}
	
	function _tr($str) { return QApplication::Translate($str); }
	
	/**
	 * Taking care of all uncatched exceptions..
	 *
	 * @param Exception $e
	 */
	function ProdHandler(Exception $__exc_objException) {
		$intId = time();
		
		Mail::SendExceptionMail($__exc_objException, $intId);
		
		Navigation::ErrorForm($intId);
	}
?>