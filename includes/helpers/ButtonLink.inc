<?php
	/**
	 * A button that default's to go to another URL instead of making callback
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class ButtonLink extends QButton {
		public function __construct($objParent, $strContorlId = null, $strUrl = null) {
			try {
				parent::__construct($objParent, $strContorlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			if ($strUrl)
				$this->Url = $strUrl;
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Url':
					$this->RemoveAllActions('QClickEvent');
					$this->AddAction(new QClickEvent(), new QJavaScriptAction(sprintf("document.location='%s'", $mixValue)));
					break;
					
				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
	}
?>