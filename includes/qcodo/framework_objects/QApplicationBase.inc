<?php
	/* Qcodo Development Framework for PHP
	 * http://www.qcodo.com/
	 * 
	 * The Qcodo Development Framework is distributed by QuasIdea Development, LLC
	 * under the terms of The MIT License.  More information can be found at
	 * http://www.opensource.org/licenses/mit-license.php
	 * 
	 * Copyright (c) 2001 - 2006, QuasIdea Development, LLC
	 * 
	 * Permission is hereby granted, free of charge, to any person obtaining a copy of
	 * this software and associated documentation files (the "Software"), to deal in
	 * the Software without restriction, including without limitation the rights to
	 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	 * of the Software, and to permit persons to whom the Software is furnished to do
	 * so, subject to the following conditions:
	 * 
	 * The above copyright notice and this permission notice shall be included in all
	 * copies or substantial portions of the Software.
	 * 
	 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	 * SOFTWARE.
	 */

	/**
	 * This abstract class should never be instantiated.  It contains static methods,
	 * variables and constants to be used throughout the application.
	 *
	 * The static method "Initialize" should be called at the begin of the script by
	 * prepend.inc.
	 */
	abstract class QApplicationBase extends QBaseClass {
		//////////////////////////
		// Public Static Variables
		//////////////////////////

		/**
		 * Array of ConnectionStrings as defined in _configuration.inc
		 * ConnectionStringArray will store each connectionstring as its own name/value array
		 * e.g. Application::$ConnectionStringArray[1]['username'] will get you the "Username"
		 * value for DB Connection #1.  All named keys will be lowercased keys.
		 *
		 * @var string ConnectionStringArray
		 */
		public static $ConnectionStringArray;

		/**
		 * Internal bitmask signifying which BrowserType the user is using
		 * Use the QApplication::IsBrowser() method to do browser checking
		 *
		 * @var integer BrowserType
		 */
		protected static $BrowserType = QBrowserType::Other;

		/**
		 * Definition of CacheControl for the HTTP header.  In general, it is
		 * recommended to keep this as "private".  But this can/should be overriden
		 * for file/scripts that have special caching requirements (e.g. dynamically
		 * created images like QImageLabel).
		 *
		 * @var string CacheControl
		 */
		public static $CacheControl = 'private';

		/**
		 * Path of the "web root" or "document root" of the web server
		 * Like "/home/www/htdocs" on Linux/Unix or "c:\inetpub\wwwroot" on Windows
		 *
		 * @var string DocumentRoot
		 */
		public static $DocumentRoot;

		/**
		 * Full path of the actual PHP script being run
		 * Like "/home/www/htdocs/folder/script.php" on Linux/Unix
		 * or "c:\inetpub\wwwroot" on Windows
		 *
		 * @var string ScriptFilename
		 */
		public static $ScriptFilename;

		/**
		 * Web-relative path of the actual PHP script being run
		 * So for "http://www.domain.com/folder/script.php",
		 * QApplication::$ScriptName would be "/folder/script.php"
		 *
		 * @var string ScriptName
		 */
		public static $ScriptName;

		/**
		 * Extended Path Information after the script URL (if applicable)
		 * So for "http://www.domain.com/folder/script.php/15/225"
		 * QApplication::$PathInfo would be "/15/255"
		 *
		 * @var string PathInfo
		 */
		public static $PathInfo;

		/**
		 * Query String after the script URL (if applicable)
		 * So for "http://www.domain.com/folder/script.php?item=15&value=22"
		 * QApplication::$QueryString would be "item=15&value=22"
		 *
		 * @var string QueryString
		 */
		public static $QueryString;

		/**
		 * The full Request URI that was requested
		 * So for "http://www.domain.com/folder/script.php/15/25/?item=15&value=22"
		 * QApplication::$RequestUri would be "/folder/script.php/15/25/?item=15&value=22"
		 *
		 * @var string RequestUri
		 */
		public static $RequestUri;

		/**
		 * The IP address of the server running the script/PHP application
		 * This is either the LOCAL_ADDR or the SERVER_ADDR server constant, depending
		 * on the server type, OS and configuration.
		 *
		 * @var string ServerAddress
		 */
		public static $ServerAddress;

		/**
		 * The encoding type for the application (e.g. UTF-8, ISO-8859-1, etc.)
		 *
		 * @var string EncodingType
		 */
		public static $EncodingType = 'ISO-8859-1';

		/**
		 * An array of Database objects, as initialized by QApplication::InitializeDatabaseConnections()
		 *
		 * @var DatabaseBase[] Database
		 */
		public static $Database;

		/**
		 * A flag to indicate whether or not this script is run as a CLI (Command Line Interface)
		 *
		 * @var boolean CliMode
		 */
		public static $CliMode;

		/**
		 * Class File Array - used by QApplication::AutoLoad to more quickly load
		 * core class objects without making a file_exists call.
		 *
		 * @var array ClassFile
		 */
		public static $ClassFile;

		/**
		 * Preloaded Class File Array - used by QApplication::Initialize to load
		 * any core class objects during Initailize()
		 *
		 * @var array ClassFile
		 */
		public static $PreloadedClassFile;

		/**
		 * The QRequestMode enumerated value for the current request mode
		 *
		 * @var string RequestMode
		 */
		public static $RequestMode;

		/**
		 * 2-letter country code to set for internationalization and localization
		 * (e.g. us, uk, jp)
		 *
		 * @var string CountryCode
		 */
		public static $CountryCode;

		/**
		 * 2-letter language code to set for internationalization and localization
		 * (e.g. en, jp, etc.)
		 *
		 * @var string LanguageCode
		 */
		public static $LanguageCode;

		/**
		 * The instance of the active QI18n object (which contains translation strings), if any.
		 *
		 * @var QI18n $LanguageObject
		 */
		public static $LanguageObject;

		////////////////////////
		// Public Overrides
		////////////////////////
		/**
		 * This faux constructor method throws a caller exception.
		 * The Application object should never be instantiated, and this constructor
		 * override simply guarantees it.
		 *
		 * @return void
		 */
		final public function __construct() {
			throw new QCallerException('Application should never be instantiated.  All methods and variables are publically statically accessible.');
		}


		////////////////////////
		// Public Static Methods
		////////////////////////

		/**
		 * This should be the first call to initialize all the static variables
		 * The application object also has static methods that are miscellaneous web
		 * development utilities, etc.
		 *
		 * @return void
		 */
		public final static function Initialize() {
			// Are we running as CLI?
			if (array_key_exists('SERVER_PROTOCOL', $_SERVER))
				QApplication::$CliMode = false;
			else
				QApplication::$CliMode = true;
				
			// Setup Server Address
			if (array_key_exists('LOCAL_ADDR', $_SERVER))
				QApplication::$ServerAddress = $_SERVER['LOCAL_ADDR'];
			else if (array_key_exists('SERVER_ADDR', $_SERVER))
				QApplication::$ServerAddress = $_SERVER['SERVER_ADDR'];

			// Setup ScriptFilename and ScriptName
			QApplication::$ScriptFilename = $_SERVER['SCRIPT_FILENAME'];
			QApplication::$ScriptName = $_SERVER['SCRIPT_NAME'];
			
			// Ensure both are set, or we'll have to abort
			if ((!QApplication::$ScriptFilename) || (!QApplication::$ScriptName)) {
				throw new Exception('Error on QApplication::Initialize() - ScriptFilename or ScriptName was not set');
			}

			// Setup PathInfo and QueryString (if applicable)
			QApplication::$PathInfo = array_key_exists('PATH_INFO', $_SERVER) ? trim($_SERVER['PATH_INFO']) : null;
			QApplication::$QueryString = array_key_exists('QUERY_STRING', $_SERVER) ? $_SERVER['QUERY_STRING'] : null;

			// Setup RequestUri
			QApplication::$RequestUri = sprintf('%s%s%s',
				QApplication::$ScriptName, QApplication::$PathInfo,
				(QApplication::$QueryString) ? sprintf('?%s', QApplication::$QueryString) : null);

			// Setup DocumentRoot
			if (defined('DOCROOT_OVERRIDE') && (strlen(trim(DOCROOT_OVERRIDE)) > 0))
				// Using DOCROOT_OVERRIDE
				QApplication::$DocumentRoot = trim(DOCROOT_OVERRIDE);
			else if (array_key_exists('DOCUMENT_ROOT', $_SERVER) && ($_SERVER['DOCUMENT_ROOT']))
				// Setup DocumentRoot
				QApplication::$DocumentRoot = $_SERVER['DOCUMENT_ROOT'];
			else {
				// Setup DocumentRoot -- DocumentRoot will NOT be set
				// and therefore needs to be magically figured out
				if (substr(QApplication::$ScriptFilename, 0, 1) == '/') {
					// Unix
					
					// Ensure that ScriptFilename ENDS with ScriptName
					$intSubstrResult = strpos(QApplication::$ScriptFilename, QApplication::$ScriptName);
					$intStrlenResult = strlen(QApplication::$ScriptFilename) - strlen(QApplication::$ScriptName);
					if ($intSubstrResult == $intStrlenResult)
						QApplication::$DocumentRoot = substr(QApplication::$ScriptFilename, 0, $intStrlenResult);
					else
						throw new Exception('Error on QApplication::Initialize() - ScriptFilename does not end with ScriptName');
				} else if (substr(QApplication::$ScriptFilename, 1, 2) == ':\\') {
					// Windows
					
					// We need to first ascertain a DOS-compatible "Script Name"
					$strScriptName = str_replace('/', '\\', QApplication::$ScriptName);

					// Ensure that ScriptFilename ENDS with ScriptName
					$intSubstrResult = strpos(QApplication::$ScriptFilename, $strScriptName);
					$intStrlenResult = strlen(QApplication::$ScriptFilename) - strlen($strScriptName);
					if ($intSubstrResult == $intStrlenResult)
						QApplication::$DocumentRoot = substr(QApplication::$ScriptFilename, 0, $intStrlenResult);
					else
						throw new Exception('Error on QApplication::Initialize() - ScriptFilename does not end with ScriptName');
				} else {
					// Could not ascertain FileSystem type
					throw new Exception('Error on QApplication::Initialize() - Could not ascertain file system type from ScriptFilename');
				}
			}

			// Cleanup DocumentRoot -- path should not end with a trailing / or \
			while ((QString::LastCharacter(QApplication::$DocumentRoot) == '/') ||
					(QString::LastCharacter(QApplication::$DocumentRoot) == '\\'))
				QApplication::$DocumentRoot = substr(QApplication::$DocumentRoot, 0, strlen(QApplication::$DocumentRoot) - 1);

			// Setup SubFolder -- Ensure that it's of the format /Subfolder
			// (e.g. leading slash, no trailing slash)
			// We CAN'T do this test if we are running in CLI mode
			if (!QApplication::$CliMode) {
				// Ensure Subfolder is setup correctly
				if (DOCROOT_SUBFOLDER) {
					if (strpos(DOCROOT_SUBFOLDER, '\\') !== false)
						throw new QCallerException(sprintf('Invalid DOCROOT_SUBFOLDER in Configuration: No backward slashes ("\\") allowed: %s', DOCROOT_SUBFOLDER));
					if (trim(DOCROOT_SUBFOLDER) != DOCROOT_SUBFOLDER)
						throw new QCallerException(sprintf('Invalid DOCROOT_SUBFOLDER in Configuration: No trailing or leading whitespace allowed: %s', DOCROOT_SUBFOLDER));
					if (QString::FirstCharacter(DOCROOT_SUBFOLDER) != '/')
						throw new QCallerException(sprintf('Invalid DOCROOT_SUBFOLDER in Configuration: Must start with leading slash ("/"): %s', DOCROOT_SUBFOLDER));
					if (QString::LastCharacter(DOCROOT_SUBFOLDER) == '/')
						throw new QCallerException(sprintf('Invalid DOCROOT_SUBFOLDER in Configuration: Must not end with slash: %s', DOCROOT_SUBFOLDER));
				}

				// Ensure Virtual Directory is setup correctly
				if (DOCROOT_VIRTUAL_DIRECTORY) {
					if (strpos(DOCROOT_VIRTUAL_DIRECTORY, '\\') !== false)
						throw new QCallerException(sprintf('Invalid DOCROOT_VIRTUAL_DIRECTORY in Configuration: No backward slashes ("\\") allowed: %s', DOCROOT_VIRTUAL_DIRECTORY));
					if (trim(DOCROOT_VIRTUAL_DIRECTORY) != DOCROOT_VIRTUAL_DIRECTORY)
						throw new QCallerException(sprintf('Invalid DOCROOT_VIRTUAL_DIRECTORY in Configuration: No trailing or leading whitespace allowed: %s', DOCROOT_VIRTUAL_DIRECTORY));
					if (QString::FirstCharacter(DOCROOT_VIRTUAL_DIRECTORY) != '/')
						throw new QCallerException(sprintf('Invalid DOCROOT_VIRTUAL_DIRECTORY in Configuration: Must start with leading slash ("/"): %s', DOCROOT_VIRTUAL_DIRECTORY));
					if (QString::LastCharacter(DOCROOT_VIRTUAL_DIRECTORY) == '/')
						throw new QCallerException(sprintf('Invalid DOCROOT_VIRTUAL_DIRECTORY in Configuration: Must not end with slash: %s', DOCROOT_VIRTUAL_DIRECTORY));
				}
				
				// Ensure SubFolder Path and DocRoot and Everything is set up correctly
				$strCurrentFile = __FILE__;
				$strCurrentFile = str_replace('\\', '/', $strCurrentFile);
				$strTestAgainst = QApplication::$DocumentRoot . DOCROOT_SUBFOLDER . '/includes/qcodo/framework_objects/QApplicationBase.inc';
				$strTestAgainst = str_replace('\\', '/', $strTestAgainst);

				// Fixup Casing on DocumentRoot (for Windows)
				$intLength = strlen(QApplication::$DocumentRoot);
				$strCurrentFile = strtolower(substr($strCurrentFile, 0, $intLength)) . substr($strCurrentFile, $intLength);
				$strTestAgainst = strtolower(substr($strTestAgainst, 0, $intLength)) . substr($strTestAgainst, $intLength);
	
/*				if ($strCurrentFile != $strTestAgainst) {
					throw new QCallerException(sprintf("Invalid DocumentRoot configuration: Please ensure that the DOCROOT_SUBFOLDER and DOCROOT matches your Qcodo web application (if any):\n%s versus\n%s",
						$strCurrentFile, $strTestAgainst));
				} */
			}
			
			// Setup Browser Type
			if (array_key_exists('HTTP_USER_AGENT', $_SERVER)) {
				$strUserAgent = trim(strtolower($_SERVER['HTTP_USER_AGENT']));

				if (strpos($strUserAgent, 'msie') !== false)
					QApplication::$BrowserType = QBrowserType::InternetExplorer;
				else if (strpos($strUserAgent, 'firefox') !== false)
					QApplication::$BrowserType = QBrowserType::Firefox;
				else if (strpos($strUserAgent, 'safari') !== false)
					QApplication::$BrowserType = QBrowserType::Safari;
				else
					QApplication::$BrowserType = QBrowserType::Other;

				if (strpos($strUserAgent, 'macintosh') !== false)
					QApplication::$BrowserType = QApplication::$BrowserType | QBrowserType::Macintosh;
			}

			// Preload Class Files
			foreach (QApplication::$PreloadedClassFile as $strClassFile)
				require(__INCLUDES__ . $strClassFile);
		}

		public static function IsBrowser($intBrowserType) {
			return ($intBrowserType & QApplication::$BrowserType);
		}

		/**
		 * This call will initialize the database connection(s) as defined by
		 * the constants DBCONFIG_X, where "X" is the index number of a
		 * particular database connection.
		 *
		 * @return void
		 */
		public static function InitializeDatabaseConnections() {
			$blnLoaded = array();

			for ($intIndex = 0; $intIndex <= 9; $intIndex++) {
				$strConstantName = sprintf("DBCONFIG_%s", $intIndex);

				if (defined($strConstantName)) {
					// Setup Defaults for this Connection #
					QApplication::$ConnectionStringArray[$intIndex]['adapter'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['server'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['port'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['database'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['username'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['password'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['profiling'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['scriptpath'] = null;
					QApplication::$ConnectionStringArray[$intIndex]['casesensitivescript'] = null;

					$strNameValuePairs = explode(';', constant($strConstantName));
					if ($strNameValuePairs) foreach ($strNameValuePairs as $strNameValuePair) {
						if (trim($strNameValuePair)) {
							$intPosition = strpos($strNameValuePair, '=');
							if (!$intPosition)
								throw new Exception('Invalid Connection String for ' . $strConstantName . ': ' . constant($strConstantName));
							$strName = strtolower(trim(substr($strNameValuePair, 0, $intPosition)));
							$strValue = trim(substr($strNameValuePair, $intPosition + 1));
	
							if (strlen($strValue))
								QApplication::$ConnectionStringArray[$intIndex][$strName] = $strValue;
						}
					}

					if (!QApplication::$ConnectionStringArray[$intIndex]['adapter'])
						throw new Exception('No Adapter Defined for ' . $strConstantName . ': ' . constant($strConstantName));

					if (!QApplication::$ConnectionStringArray[$intIndex]['server'])
						throw new Exception('No Server Defined for ' . $strConstantName . ': ' . constant($strConstantName));

					$strDatabaseType = 'Q' . QApplication::$ConnectionStringArray[$intIndex]['adapter'];
					if (!array_key_exists($strDatabaseType, $blnLoaded)) {
						if (!file_exists($q = sprintf(QApplication::$DocumentRoot . DOCROOT_SUBFOLDER . "/includes/qcodo/database_adapters/%s.inc", $strDatabaseType)))
							throw new Exception('Database Type is not valid: ' . QApplication::$ConnectionStringArray[$intIndex]['adapter']);
						require(sprintf('%sqcodo/database_adapters/%s.inc', __INCLUDES__, $strDatabaseType));
						$blnLoaded[$strDatabaseType] = true;
					}

					QApplication::$Database[$intIndex] = new $strDatabaseType($intIndex);
				}
			}
		}

		/**
		 * This is called by the PHP5 Autoloader.  This static method can be overridden.
		 *
		 * @return void
		 */
		public static function Autoload($strClassName) {
			if (array_key_exists($strClassName, QApplication::$ClassFile)) {
				require(__INCLUDES__ . QApplication::$ClassFile[$strClassName]);
			} else if (file_exists($strFilePath = sprintf('%sdata_objects/%s.inc', __INCLUDES__, $strClassName))) {
				require($strFilePath);
			} else if (file_exists($strFilePath = sprintf('%sqform/%s.inc', __INCLUDES__, $strClassName))) {
				require($strFilePath);
			}
		}

		/**
		 * This will redirect the user to a new web location.  This can be a relative or absolute web path, or it
		 * can be an entire URL.
		 *
		 * @return void
		 */
		public final static function Redirect($strLocation) {
			// Clear the output buffer (if any)
			ob_clean();

			if (QApplication::$RequestMode == QRequestMode::Ajax) {
				// AJAX-based Response

				// Response is in XML Format
				header('Content-Type: text/xml');

				// OUtput it and update render state
				printf('<?xml version="1.0"?><response><controls/><commands><command><![CDATA[document.location = "%s"]]></command></commands></response>', $strLocation);

			} else {
				// Was "DOCUMENT_ROOT" set?
				if (array_key_exists('DOCUMENT_ROOT', $_SERVER) && ($_SERVER['DOCUMENT_ROOT'])) {
					// If so, we're likley using PHP as a Plugin/Module
					// Use 'header' to redirect
					header(sprintf('Location: %s', $strLocation));
				} else {
					// We're likely using this as a CGI
					// Use JavaScript to redirect
					printf('<script type="text/javascript">document.location = "%s";</script>', $strLocation);
				}
			}

			// End the Response Script
			exit();
		}


		/**
		 * This will close the window.  It will immediately end processing of the rest of the script.
		 *
		 * @return void
		 */
		public final static function CloseWindow() {
			// Clear the output buffer (if any)
			ob_clean();

			if (QApplication::$RequestMode == QRequestMode::Ajax) {
				// AJAX-based Response

				// Response is in XML Format
				header('Content-Type: text/xml');

				// OUtput it and update render state
				print('<?xml version="1.0"?><response><controls/><commands><command>window.close();</command></commands></response>');

			} else {
				// Use JavaScript to close
				print('<script type="text/javascript">window.close();</script>');
			}

			// End the Response Script
			exit();
		}

		/**
		 * Gets the value of the QueryString item $strItem.  Will return NULL if it doesn't exist.
		 *
		 * @return string
		 */
		public final static function QueryString($strItem) {
			if (array_key_exists($strItem, $_GET))
				return $_GET[$strItem];
			else
				return null;
		}

		/**
		 * Gets the value of the PathInfo item at index $intIndex.  Will return NULL if it doesn't exist.
		 *
		 * The way PathInfo index is determined is, for example, given a URL '/folder/page.php/id/15/blue',
		 * QApplication::PathInfo(0) will return 'id'
		 * QApplication::PathInfo(1) will return '15'
		 * QApplication::PathInfo(2) will return 'blue'
		 *
		 * @return void
		 */
		public final static function PathInfo($intIndex) {
			// TODO: Cache PathInfo
			$strPathInfo = QApplication::$PathInfo;
			
			// Remove Trailing '/'
			if (QString::FirstCharacter($strPathInfo) == '/')			
				$strPathInfo = substr($strPathInfo, 1);
			
			$strPathInfoArray = explode('/', $strPathInfo);

			if (array_key_exists($intIndex, $strPathInfoArray))
				return $strPathInfoArray[$intIndex];
			else
				return null;
		}
		
		public static $AlertMessageArray = array();
		public static $JavaScriptArray = array();
		public static $JavaScriptArrayHighPriority = array();

		public static $ErrorFlag = false;
		
		public final static function DisplayAlert($strMessage) {
			array_push(QApplication::$AlertMessageArray, $strMessage);
		}
		
		public final static function ExecuteJavaScript($strJavaScript, $blnHighPriority = false) {
			if ($blnHighPriority)
				array_push(QApplication::$JavaScriptArrayHighPriority, $strJavaScript);
			else
				array_push(QApplication::$JavaScriptArray, $strJavaScript);
		}
		
		public static function OutputPage($strBuffer) {
			if (QApplication::$ErrorFlag) {
				return $strBuffer;
			} else {
				if (QApplication::$RequestMode == QRequestMode::Ajax) {
					return trim($strBuffer);
				} else {
					// Update Cache-Control setting
					header('Cache-Control: ' . QApplication::$CacheControl);

					$strScript = '';
					foreach (QApplication::$AlertMessageArray as $strAlert) {
						$strScript .= sprintf('alert("%s"); ', addslashes($strAlert));
					}
					foreach (QApplication::$JavaScriptArrayHighPriority as $strJavaScript) {
						$strJavaScript = trim($strJavaScript);
						if (QString::LastCharacter($strJavaScript) != ';')
							$strScript .= sprintf('%s; ', $strJavaScript);
						else
							$strScript .= sprintf('%s ', $strJavaScript);
					}
					foreach (QApplication::$JavaScriptArray as $strJavaScript) {
						$strJavaScript = trim($strJavaScript);
						if (QString::LastCharacter($strJavaScript) != ';')
							$strScript .= sprintf('%s; ', $strJavaScript);
						else
							$strScript .= sprintf('%s ', $strJavaScript);
					}

					if ($strScript)
						return sprintf('%s<script>%s</script>', $strBuffer, $strScript);
					else
						return $strBuffer;
				}
			}
		}


  		/**
		 * If LanguageCode is specified and QI18n::Initialize() has been called, then this
		 * will perform a translation of the given token for the specified Language Code and optional
		 * Country code.
		 *
		 * Otherwise, this will simply return the token as is.
		 *
		 * @param string $strToken
		 * @return string the Translated token (if applicable)
		 */
		public static function Translate($strToken) {
			if (QApplication::$LanguageObject)
				return QApplication::$LanguageObject->TranslateToken($strToken);
			else
				return $strToken;
		}

  		/**
		 * For development purposes, this static method outputs all the Application static variables
		 *
		 * @return void
		 */
		public final static function VarDump() {
			print('<div style="background-color: #cccccc; padding: 5px;"><b>Qcodo Settings</b><ul>');
			if (ini_get('magic_quotes_gpc') || ini_get('magic_quotes_runtime')) {
				printf('<li><font color="red"><b>WARNING:</b> magic_quotes_gpc and magic_quotes_runtime need to be disabled</font>');
			}
			printf('<li>QCODO_VERSION = "%s"</li>', QCODO_VERSION);
			printf('<li>DOCROOT_OVERRIDE = "%s"</li>', DOCROOT_OVERRIDE);
			printf('<li>DOCROOT_SUBFOLDER = "%s"</li>', DOCROOT_SUBFOLDER);
			printf('<li>DOCROOT_VIRTUAL_DIRECTORY = "%s"</li>', DOCROOT_VIRTUAL_DIRECTORY);
			printf('<li>INCLUDE_PATH = "%s"</li>', get_include_path());
			printf('<li>__INCLUDES__ = "%s"</li>', __INCLUDES__);
			printf('<li>ERROR_PAGE_PATH = "%s"</li>', ERROR_PAGE_PATH);
			printf('<li>QApplication::$DocumentRoot = "%s"</li>', QApplication::$DocumentRoot);
			printf('<li>QApplication::$EncodingType = "%s"</li>', QApplication::$EncodingType);
			printf('<li>QApplication::$PathInfo = "%s"</li>', QApplication::$PathInfo);
			printf('<li>QApplication::$QueryString = "%s"</li>', QApplication::$QueryString);
			printf('<li>QApplication::$RequestUri = "%s"</li>', QApplication::$RequestUri);
			printf('<li>QApplication::$ScriptFilename = "%s"</li>', QApplication::$ScriptFilename);
			printf('<li>QApplication::$ScriptName = "%s"</li>', QApplication::$ScriptName);
			printf('<li>QApplication::$ServerAddress = "%s"</li>', QApplication::$ServerAddress);

			if (QApplication::$Database) foreach (QApplication::$Database as $intKey => $objObject) {
				printf('<li>QApplication::$Database[%s] = %s</li>', 
					$intKey,
					constant('DBCONFIG_' . $intKey));
			}
			print('</ul></div>');
		}
	}

	class QRequestMode {
		const Standard = 'Standard';
		const Ajax = 'Ajax';
	}

	class QBrowserType {
		const InternetExplorer = 1;
		const Firefox = 2;
		const Safari = 4;
		const Macintosh = 8;
		const Other = 16;
	}
?>
