<?php
	define('SERVER_INSTANCE', 'dev');

	switch (SERVER_INSTANCE) {
		case 'dev':
			define('EXCEPTION_HANDLER','QcodoHandleException');
			define('DBCONFIG_1', 'Adapter=MySqli5Database; Server=myoqtopus; Port=3306; Database=oqtopus; Username=oqtopus; Password=; Profiling=false; ScriptPath=;');
			define('OQTOPUS_START_URL', '/oqtopus.php');
			
		case 'demo':
			define('DBCONFIG_1', 'Adapter=MySqli5Database; Server=127.0.0.1; Port=3306; Database=oqtopus_demo; Username=oqtopus; Password=5mJ:L3USRza7GHHR; Profiling=false; ScriptPath=;');
							
		case 'prod':
			// DocumentRoot is automagically calculated by Application::Initialize()
			// However, for whatever reason, if you wish to explicitly set
			// the Application::$DocumentRoot, you can do so here
			//define ('DOCROOT_OVERRIDE', '/var/www/devel.oqtopus.se');

			// The "Subfolder" and "VirtualDirectory" related constants are available
			// to add more flexibility for deployment options.
			// Format must be all unix-style folder delimiters (e.g. use '/' and not '\')
			// You **MUST** have a leading slash, and you must have *NO* trailing slash
			// E.g. '/my/path'

			// "Subfolder": If your application is installed in a subfolder WITHIN your docroot, specify that subfolder here.
			define ('DOCROOT_SUBFOLDER', '/..');
			
			if (!defined('EXPCETION_HANDLER'))
				define('EXCEPTION_HANDLER', 'ProdHandler');

			// "VirtualDirectory": If your application is installed in a Virtual Directory (a.k.a. Directory Alias)
			// specify the virtual directory here.
			// NOTE: If you are using Virtual Directories, you are likley going to have to use DOCROOT_OVERRIDE
			// So if the docroot of THIS application is /home/my_user/public_html and the web url is
			// http://www.domain.com/~my_user/, you will want to set DOCROOT_VIRTUAL_DIRECTORY to '/~my_user'.
			// You will also NEED to set DOCROOT_OVERRIDE to '/home/my_user/public_html'
			define ('DOCROOT_VIRTUAL_DIRECTORY', '');

			// Database Connection String (for DB Connection #1)
			// "Adapter" (Required), options are:
			//		MySqlDatabase (MySQL v4.x, using the old mysql extension)
			//		MySqliDatabase (MySQL v4.x, using the new mysqli extension)
			//		MySqli5Database (MySQL v5.x, using the new mysqli extension)
			//		SqlServerDatabase (Microsoft SQL Server)
			//		PostgreSqlDatabase (PostgreSQL)
			// "Server" (Required) is the db server's name or IP address, e.g. localhost, 10.1.1.5, etc.
			// "Port" is the port number - default is the server-specified default
			// "Database", "Username", "Password" should be self explanatory
			// "Profiling" is true or false, defining whether or not you want to enable DB profiling - default is false
			//		NOTE: Profiling should only be enabled when you are actively wanting to profile a
			//		specific PHP script or scripts.  Because of SIGNIFICANT performance degradation,
			//		it should otherwise always be OFF.
			// "ScriptPath": you can have CodeGen virtually add additional FKs, even though they are
			// 		not defined as a DB constraint in the database, by using a script to define what
			// 		those constraints are.  The path of the script can be defined here. - default is blank or none
			// Note: any option not used or set to blank will result in using the default value for that option
			if (!defined('DBCONFIG_1'))
				define('DBCONFIG_1', 'Adapter=MySqli5Database; Server=127.0.0.1; Port=3306; Database=oqtopus_sharp; Username=oqtopus; Password=5mJ:L3USRza7GHHR; Profiling=false; ScriptPath=;');

			// Additional Database Connection Strings can be defined here (e.g. for connection #2, #3, #4, etc.)
//			define('DBCONFIG_2', 'Adapter=SqlServerDatabase; Server=localhost; Port=; Database=test; Username=root; Password=; Profiling=false; ScriptPath=;');
//			define('DBCONFIG_3', 'Adapter=MySqli5Database; Server=localhost; Port=; Database=test; Username=root; Password=; Profiling=false; ScriptPath=;');
//			define('DBCONFIG_4', 'Adapter=MySqlDatabase; Server=localhost; Port=; Database=test; Username=root; Password=; Profiling=false; ScriptPath=;');

			// Setup the default timezone (if not already specified in php.ini)
			if (!ini_get('date.timezone'))
				date_default_timezone_set('US/Pacific');

			// Define the Filepath for the error page (path MUST be relative to the "includes/" directory)
			define('ERROR_PAGE_PATH', 'qcodo/error_pages/error_page.php');
			
			// Define the default salt length for passwords
			define('OQTOPUS_PASSWORD_SALT_LENGTH', 10);
			
			// Define the "outer" template, relative to the __INCLUDE__ path
			define('OQTOPUS_OUTER_HTML', 'templates/oqtopus.inc');
			
			// Define starting URL
			if (!defined('OQTOPUS_START_URL'))
				define('OQTOPUS_START_URL', '/');
			
			// Define password hash algorithm
			define('OQTOPUS_PASSWORD_HASH_ALGORITHM', 'sha256');
			
			// Define search results per page
			define('OQTOPUS_SEARCH_RESULTS_PER_PAGE', 8);
			
			define('OQTOPUS_PROVISION', 0.03);
			
			define('OQTOPUS_MINIMUM_PROVISION', 50);
			
			define('OQTOPUS_EXCEPTION_MAIL', 'exception@oqtopus.se');
			
			define('OQTOPUS_MAIL_FROM_EMAIL', 'no-reply@oqtopus.se');
			
			define('OQTOPUS_MAIL_FROM_NAME', 'Oqtopus');
			
			define('OQTOPUS_MAIL_SMTP_HOST', 'smtp.ucs.se');
			
			define('OQTOPUS_WORTHY_VALID_DAYS', 14);
			
			define('OQTOPUS_BID_TAX', 0.25);
			break;
	}
?>
