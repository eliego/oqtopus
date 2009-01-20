<?php
	/**
	 * This user gets redirected to this form when an error has occured (exception uncaught)
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage qforms
	 */
	class ErrorForm extends OqtopusForm {
		protected $lblId;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->lblId = new QLabel($this);
			if (isset($_GET['arg1']))
				$this->lblId->Text = $_GET['arg1'];
		}
	}
?>