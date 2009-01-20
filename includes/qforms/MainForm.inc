<?php

class MainForm extends OqtopusForm{

	protected function Form_Create() {
		try { 
			parent::Form_Create();
		} catch(QCallerException $E) {
			$E->IncrementOffset();
			throw $E;
		}
	}
}

?>
