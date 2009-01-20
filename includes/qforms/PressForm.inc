<?php
	class PressForm extends OqtopusForm
	{
		protected $txtSubscriptionEmail;
		protected $chkOptions;
		protected $btnDoSubscribe;
		protected $lblSubInfo;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->chkOptions = new QCheckBoxList($this, 'chkOptions');
			$this->chkOptions->Required = true;
			$this->chkOptions->AddItem(_tr('Newsletter'), Subscriptions::Newsletter);
			$this->chkOptions->AddItem(_tr('PMs'), Subscriptions::PMs);
			$this->chkOptions->AddItem(_tr('Media coverage'), Subscriptions::Press);
			
			$this->txtSubscriptionEmail = new EmailTextBox($this, 'txtSubscriptionEmail');
			$this->txtSubscriptionEmail->Name = _tr('Email');
			$this->txtSubscriptionEmail->AddAction(new QEnterKeyEvent(), new QAjaxAction('DoSubscribe'));
			$this->txtSubscriptionEmail->AddAction(new QEnterKeyEvent(), new QTerminateAction());
			
			$this->btnDoSubscribe = new QButton($this, 'btnDoSubscribe');
			$this->btnDoSubscribe->Text = _tr('subscribe');
			$this->btnDoSubscribe->AddAction(new QClickEvent(), new QAjaxAction('DoSubscribe'));
			
			$this->lblSubInfo = new QLabel($this, 'lblSubInfo');
			$this->lblSubInfo->Visible = false;
		}
		
		protected function DoSubscribe() {
			$objSubscribe = new NewsletterSubscription();
			$objSubscribe->Newsletter = (int)$this->chkOptions->GetItemByValue(Subscriptions::Newsletter)->Selected;
			$objSubscribe->Pm = (int)$this->chkOptions->GetItemByValue(Subscriptions::PMs)->Selected;
			$objSubscribe->Press = (int)$this->chkOptions->GetItemByValue(Subscriptions::Press)->Selected;
			$objSubscribe->Email = $this->txtSubscriptionEmail->Text;
			$objSubscribe->Save();
			
			$this->lblSubInfo->Text = _tr('Thankyou!');
			$this->lblSubInfo->Visible = true;
			$this->btnDoSubscribe->Enabled = false;
		}
	}
?>