<?php
	/**
	 * Simply contains the JS to popup a confirmation window, and only proceed if the user press OK
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class JSConfirmAction extends QJavaScriptAction {
		public function __construct() {
			try {
				parent::__construct(sprintf('if (!confirm(\'%s\')) return false', _tr('Are you sure?')));
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
		}
	}
?>