<?php
    /**
     * Oqtopus controller
     *
     * Starting point for all Oqtopus views
     *
     * @author Kung den Knege <kungdenknege@gmail.com>
     * @package oqtopus
     */
	try {
    	require("../includes/prepend.inc");

    	if (!isset($_GET['form']) or !$_GET['form'] or strpos($_GET['form'], '..') or strpos($_GET['form'], '/'))
        	$_GET['form'] = Security::Current() ? (Security::Current()->Role == Role::Buyer ? 'BuyersNewsForm' : 'SellersNewsForm'): 'MainForm';       

        // we have to be a bit ugly here - using qcodo for each hint-request causes unserializing of all objects - fucks performance too much
        if ($_GET['form'] == 'Special') {file_put_contents("/tmp/dump","hej",FILE_APPEND);
       		//$ret = call_user_func(array($_GET['arg1'], $_GET['arg2']));
       		die("test\n");
        }
        	
    	// Load up the form (we have to load it manually, since class_exists doesn't autoload)
    	QApplication::Autoload($_GET['form']);
    	if (!class_exists($_GET['form']))
        	throw new NoSuchFormException(QApplication::Translate("Oqtopus knows no form named") . " " . $_GET['form']);

    	QApplication::$FormName = $_GET['form'];
   
    	QForm::Run($_GET['form'], sprintf('%s%s.inc', __TEMPLATES__, $_GET['form']));
   	} catch (AccessDeniedException $e) {
   		Navigation::Home();
   	} catch (QMySqliDatabaseException $e) {
   		if (SERVER_INSTANCE == 'prod' || SERVER_INSTACE == 'demo')
   			die("It seems like we're having some problems with the database right now.. Please try again in a bunch!");
   		else throw $e;
   	} catch (NoSuchFormException $e) {
   		die("I don't know no form with that name!");
   	} catch (NoSuchObjectException $e) {
   		if (SERVER_INSTANCE == 'prod' || SERVER_INSTANCE == 'demo')
   			Navigation::Home();
   		else throw $e;
   	}

?>
