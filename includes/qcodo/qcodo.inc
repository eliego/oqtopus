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

	// Versioning Information
	define('QCODO_VERSION', '0.2.13 (Qcodo Beta 2)');

	// Preload Required Framework Classes
	require(__INCLUDES__ . 'qcodo/framework_objects/QBaseClass.inc');
	require(__INCLUDES__ . 'qcodo/framework_objects/QExceptions.inc');
	require(__INCLUDES__ . 'qcodo/framework_objects/QType.inc');
	require(__INCLUDES__ . 'qcodo/framework_objects/QApplicationBase.inc');

	// Setup the Error Handler
	require(__INCLUDES__ . 'qcodo/error.inc');

	// Setup the Autoloader
	function __autoload($strClassName) {
		QApplication::Autoload($strClassName);
	}

	// Start Output Buffering	
	function __ob_callback($strBuffer) {
		return QApplication::OutputPage($strBuffer);
	}
	ob_start('__ob_callback');

	// Qcodo Signature
	header(sprintf('X-Powered-By: PHP/%s; Qcodo/%s', phpversion(), QCODO_VERSION));

	// Preload Other Framework Classes
	require(__INCLUDES__ . 'qcodo/framework_objects/QDatabaseBase.inc');
	require(__INCLUDES__ . 'qcodo/framework_objects/QDateTime.inc');
	require(__INCLUDES__ . 'qcodo/framework_objects/QQueryExpansion.inc');

	// Define Classes to be Preloaded on QApplication::Initialize()
	QApplicationBase::$PreloadedClassFile['_enumerations'] = 'qcodo/qform_objects/_enumerations.inc';
	QApplicationBase::$PreloadedClassFile['QControlBase'] = 'qcodo/qform_objects/QControlBase.inc';
	QApplicationBase::$PreloadedClassFile['QControl'] = 'qform/QControl.inc';
	QApplicationBase::$PreloadedClassFile['QFormBase'] = 'qcodo/qform_objects/QFormBase.inc';
	QApplicationBase::$PreloadedClassFile['QForm'] = 'qform/QForm.inc';
	QApplicationBase::$PreloadedClassFile['_actions'] = 'qcodo/qform_objects/_actions.inc';
	QApplicationBase::$PreloadedClassFile['_events'] = 'qcodo/qform_objects/_events.inc';

	// Define ClassFile Locations for FormState Handlers
	QApplicationBase::$ClassFile['QFormStateHandler'] = 'qcodo/qform_state_handlers/QFormStateHandler.inc';
	QApplicationBase::$ClassFile['QSessionFormStateHandler'] = 'qcodo/qform_state_handlers/QSessionFormStateHandler.inc';
	QApplicationBase::$ClassFile['QFileFormStateHandler'] = 'qcodo/qform_state_handlers/QFileFormStateHandler.inc';

	// Define ClassFile Locations for Framework Classes
	QApplicationBase::$ClassFile['QRssFeed'] = 'qcodo/framework_objects/QRssFeed.inc';
	QApplicationBase::$ClassFile['QRssImage'] = 'qcodo/framework_objects/QRssFeed.inc';
	QApplicationBase::$ClassFile['QRssCategory'] = 'qcodo/framework_objects/QRssFeed.inc';
	QApplicationBase::$ClassFile['QRssItem'] = 'qcodo/framework_objects/QRssFeed.inc';
	QApplicationBase::$ClassFile['QEmailServer'] = 'qcodo/framework_objects/QEmailServer.inc';
	QApplicationBase::$ClassFile['QEmailMessage'] = 'qcodo/framework_objects/QEmailServer.inc';
	QApplicationBase::$ClassFile['QDateTime'] = 'qcodo/framework_objects/QDateTime.inc';
	QApplicationBase::$ClassFile['QString'] = 'qcodo/framework_objects/QString.inc';
	QApplicationBase::$ClassFile['QStack'] = 'qcodo/framework_objects/QStack.inc';
	QApplicationBase::$ClassFile['QCryptography'] = 'qcodo/framework_objects/QCryptography.inc';
	QApplicationBase::$ClassFile['QSoapService'] = 'qcodo/framework_objects/QSoapService.inc';
	QApplicationBase::$ClassFile['QI18n'] = 'qcodo/framework_objects/QI18n.inc';

	QApplicationBase::$ClassFile['QCache'] = 'qcodo/framework_objects/QCache.inc';

	// Define ClassFile Locations for Qform Classes
	QApplicationBase::$ClassFile['QFontFamily'] = 'qcodo/qform_objects/QFontFamily.inc';

	QApplicationBase::$ClassFile['QCalendar'] = 'qcodo/qform_objects/QCalendar.inc';
	QApplicationBase::$ClassFile['QDateTimePicker'] = 'qcodo/qform_objects/QDateTimePicker.inc';
	
	QApplicationBase::$ClassFile['QCheckBox'] = 'qcodo/qform_objects/QCheckBox.inc';
	QApplicationBase::$ClassFile['QFileControl'] = 'qcodo/qform_objects/QFileControl.inc';
	QApplicationBase::$ClassFile['QRadioButton'] = 'qcodo/qform_objects/QRadioButton.inc';

	QApplicationBase::$ClassFile['QBlockControl'] = 'qcodo/qform_objects/QBlockControl.inc';
	QApplicationBase::$ClassFile['QLabel'] = 'qcodo/qform_objects/QLabel.inc';
	QApplicationBase::$ClassFile['QPanel'] = 'qcodo/qform_objects/QPanel.inc';

	QApplicationBase::$ClassFile['QImageLabelBase'] = 'qcodo/qform_objects/QImageLabelBase.inc';
	QApplicationBase::$ClassFile['QImageLabel'] = 'qform/QImageLabel.inc';
	QApplicationBase::$ClassFile['QControlLabel'] = 'qcodo/qform_objects/QControlLabel.inc';

	QApplicationBase::$ClassFile['QActionControl'] = 'qcodo/qform_objects/QActionControl.inc';
	QApplicationBase::$ClassFile['QButtonBase'] = 'qcodo/qform_objects/QButtonBase.inc';
	QApplicationBase::$ClassFile['QButton'] = 'qform/QButton.inc';
	QApplicationBase::$ClassFile['QImageButton'] = 'qcodo/qform_objects/QImageButton.inc';
	QApplicationBase::$ClassFile['QLinkButton'] = 'qcodo/qform_objects/QLinkButton.inc';

	QApplicationBase::$ClassFile['QListControl'] = 'qcodo/qform_objects/QListControl.inc';
	QApplicationBase::$ClassFile['QListItem'] = 'qcodo/qform_objects/QListItem.inc';
	QApplicationBase::$ClassFile['QListBoxBase'] = 'qcodo/qform_objects/QListBoxBase.inc';
	QApplicationBase::$ClassFile['QListBox'] = 'qform/QListBox.inc';
	QApplicationBase::$ClassFile['QCheckBoxList'] = 'qcodo/qform_objects/QCheckBoxList.inc';
	QApplicationBase::$ClassFile['QRadioButtonList'] = 'qcodo/qform_objects/QRadioButtonList.inc';
	QApplicationBase::$ClassFile['QTreeNav'] = 'qcodo/qform_objects/QTreeNav.inc';
	QApplicationBase::$ClassFile['QTreeNavItem'] = 'qcodo/qform_objects/QTreeNavItem.inc';

	QApplicationBase::$ClassFile['QTextBoxBase'] = 'qcodo/qform_objects/QTextBoxBase.inc';
	QApplicationBase::$ClassFile['QTextBox'] = 'qform/QTextBox.inc';
	QApplicationBase::$ClassFile['QFloatTextBox'] = 'qcodo/qform_objects/QFloatTextBox.inc';
	QApplicationBase::$ClassFile['QIntegerTextBox'] = 'qcodo/qform_objects/QIntegerTextBox.inc';
	QApplicationBase::$ClassFile['QWriteBox'] = 'qcodo/qform_objects/QWriteBox.inc';

	QApplicationBase::$ClassFile['QPaginatedControl'] = 'qcodo/qform_objects/QPaginatedControl.inc';
	QApplicationBase::$ClassFile['QPaginatorBase'] = 'qcodo/qform_objects/QPaginatorBase.inc';
	QApplicationBase::$ClassFile['QPaginator'] = 'qform/QPaginator.inc';

	QApplicationBase::$ClassFile['QDataGridBase'] = 'qcodo/qform_objects/QDataGridBase.inc';
	QApplicationBase::$ClassFile['QDataGridColumn'] = 'qcodo/qform_objects/QDataGridColumn.inc';
	QApplicationBase::$ClassFile['QDataGridRowStyle'] = 'qcodo/qform_objects/QDataGridRowStyle.inc';
	QApplicationBase::$ClassFile['QDataGrid'] = 'qform/QDataGrid.inc';

	QApplicationBase::$ClassFile['QDataRepeater'] = 'qcodo/qform_objects/QDataRepeater.inc';

	QApplicationBase::$ClassFile['QWaitIcon'] = 'qcodo/qform_objects/QWaitIcon.inc';
	QApplicationBase::$ClassFile['QControlGrouping'] = 'qcodo/qform_objects/QControlGrouping.inc';
	QApplicationBase::$ClassFile['QDropZoneGrouping'] = 'qcodo/qform_objects/QDropZoneGrouping.inc';



	// Special Print Functions / Shortcuts
	// NOTE: These are simply meant to be shortcuts to actual Qcodo functional
	// calls to make your templates a little easier to read.  By no means do you have to
	// use them.  Your templates can just as easily make the fully-named method/function calls.
		function _p($strString) {
			// Standard Print
			print($strString);
		}

		function _t($strString) {
			// Print, via Translation (if applicable)
			print(QApplication::Translate($strString));
		}

		function _i($intNumber) {
			// Not Yet Implemented
			// Print Integer with Localized Formatting
		}

		function _f($intNumber) {
			// Not Yet Implemented
			// Print Float with Localized Formatting
		}

		function _c($strString) {
			// Not Yet Implemented
			// Print Currency with Localized Formatting
		}
	//////////////////////////////////////
?>