<?php
	class DemoForm extends OqtopusForm {
		protected $pnlC;
		protected $btnB;
		protected $btnF;
		public function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			if (!isset($_GET['arg1']))
				$_GET['arg1'] = 1;
				
			$this->pnlC = new QPanel($this);
			
			$class = new ReflectionClass($this);
			$class = $class->getName();
										
			$this->btnB = new ButtonLink($this->pnlC);
			$this->btnB->CausesValidation = false;
			if (file_exists(sprintf('%s%s.%s.inc', __TEMPLATES__, $class, $_GET['arg1'] - 1))) {
				$this->btnB->Url = Navigation::CreateUrl(QApplication::$FormName, $_GET['arg1'] - 1);
				$this->btnB->Text = _tr('Previous');
			} else {
				$this->btnB->Url = Navigation::HomeUrl();
				$this->btnB->Text = _tr('Home');
			}
			
			$this->btnF = new ButtonLink($this->pnlC);
			$this->btnF->CausesValidation = false;
			if (file_exists(sprintf('%s%s.%s.inc', __TEMPLATES__, $class, $_GET['arg1'] + 1))) {
				$this->btnF->Url = Navigation::CreateUrl(QApplication::$FormName, $_GET['arg1'] + 1);
				$this->btnF->Text = _tr('Next');
			} else {
				$this->btnF->Url = Navigation::HomeUrl();
				$this->btnF->Text = _tr('Home');
			}

			try {
				$this->pnlC->Template = sprintf('%s%s.%s.inc', __TEMPLATES__, $class, $_GET['arg1']);
			} catch (QCallerException $e) {
				throw new NoSuchObjectException();
			}
		}
	}
?>