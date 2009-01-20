<TargetFilePath="<%= QApplication::$DocumentRoot . DOCROOT_SUBFOLDER %>/form_drafts/<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_edit.php" OverwriteFlag="false">
<?php
	// Include prepend.inc to load Qcodo
	require('../includes/prepend.inc');		/* if you DO NOT have "includes/" in your include_path */
	// require('prepend.inc');				/* if you DO have "includes/" in your include_path */

	// Include the classfile for <%= $objTable->ClassName %>EditFormBase
	require(__INCLUDES__ . 'forms_generated/<%= $objTable->ClassName %>EditFormBase.inc');

	/**
	 * This is a quick-and-dirty draft form object to do Create, Edit, and Delete functionality
	 * of the <%= $objTable->ClassName %> class.  It extends from the code-generated
	 * abstract <%= $objTable->ClassName %>EditFormBase class.
	 *
	 * Any display custimizations and presentation-tier logic can be implemented
	 * here by overriding existing or implementing new methods, properties and variables.
	 *
	 * Additional qform control objects can also be defined and used here, as well.
	 * 
	 * @package <%= $objCodeGen->ApplicationName; %>
	 * @subpackage FormDraftObjects
	 * 
	 */
	class <%= $objTable->ClassName %>EditForm extends <%= $objTable->ClassName %>EditFormBase {
		// Override Form Event Handlers as Needed
//		protected function Form_Run() {}

//		protected function Form_Load() {}

//		protected function Form_Create() {
//			parent::Form_Create();
//		}

//		protected function Form_PreRender() {}

//		protected function Form_Exit() {}
	}

	// Go ahead and run this form object to render the page and its event handlers, using
	// generated/<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_edit.php.inc as the included HTML template file
	<%= $objTable->ClassName %>EditForm::Run('<%= $objTable->ClassName %>EditForm', 'generated/<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_edit.php.inc');
?>