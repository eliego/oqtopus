<?php
	/**
	 * Form that lets a registered user activate his or her account.
	 * If activation key isn't supplied in GET, a textbox is displayed
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class ActivateForm extends OqtopusForm {
		protected $txtKey;
		protected $txtUsername;
		protected $btnOk;
		protected $lblText;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->txtKey = new QTextBox($this);
			$this->txtKey->MaxLength = 25;
			$this->txtKey->Name = _tr('Registration key');
			$this->txtKey->AddAction(new QEnterKeyEvent(), $objA = new QAjaxAction('Activate'));
			$this->txtKey->AddAction(new QEnterKeyEvent(), new QTerminateAction());
			
			$this->txtUsername = new QTextBox($this);
			$this->txtUsername->Name = _tr('Username');
			
			$this->btnOk = new QButton($this);
			$this->btnOk->Text = _tr('Ok');
			$this->btnOk->AddAction(new QClickEvent(), clone $objA);
			
			$this->lblText = new QLabel($this);
			$this->lblText->Visible = false;
			
			if (isset($_GET['arg1']) && isset($_GET['arg2'])) {
				$this->txtKey->Visible = false;
				$this->txtUsername->Visible = false;
				$this->btnOk->Visible = false;
				
				$this->Activate();
			}
		}
		
		protected function Activate() {
			$strKey = isset($_GET['arg2']) ? $_GET['arg2'] : $this->txtKey->Text;
			$strUser = isset($_GET['arg1']) ? $_GET['arg1'] : $this->txtUsername->Text;
			
			if (!($objLogin = Login::LoadByUsername($strUser))) {
				$this->lblText->Text = _tr('No such user');
				$this->lblText->Visible = true;
				return;
			}
			
			try {
				$objLogin->Activate($strKey);
				$objLogin->Save();
			} catch (WrongParametersException $e) {
				$this->lblText->Text = _tr('Wrong key');
				$this->lblText->Visible = true;
				return;
			} catch (AlreadyActiveException $e) {
				$this->lblText->Text = _tr('Your account is already active');
				$this->lblText->Visible = true;
				return;
			}
			
			$this->btnOk->Enabled = false;
			$this->lblText->Text = _tr('Your account is now active! Please enter your credentials and press Ok to your right');
			$this->lblText->Visible = true;
		}
	}
?>