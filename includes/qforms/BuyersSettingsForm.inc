<?php
	class BuyersSettingsForm extends OqtopusForm {
		protected $txtSellerContactName;
		protected $txtSellerContactAdress;
		protected $txtSellerContactPhone;
		protected $txtSellerContactEmail;
		protected $txtSellerContactPostal;
		protected $txtSellerContactCity;
		protected $txtOldPass;
		protected $txtNewPass;
		protected $txtNewPass2;
		protected $btnDoChangePass;
		protected $lblPassInfo;
		protected $btnDoEditSellerInfo;
		protected $btnCancelEditSellerInfo;
		protected $lblInfo;
		protected $lblSellerName;
		protected $lblSellerOrgNr;
		protected $chkMailOn;

		protected $objLogin;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			$this->objLogin = Security::Current();
			
			Security::VerifyAccess(Actions::ManageSettings, $this->objLogin);
			
			$this->txtSellerContactName = new QTextBox($this, 'txtSellerContactName');
			$this->txtSellerContactName->Name = _tr('Name of contact person');
			
			$this->txtSellerContactAdress = new QTextBox($this, 'txtSellerContactAdress');
			$this->txtSellerContactAdress->Name = _tr('Address of contact person');
				
			$this->txtSellerContactPhone = new QTextBox($this, 'txtSellerContactPhone');
			$this->txtSellerContactPhone->Name = _tr('Phone number to contact person');
				
			$this->txtSellerContactEmail = new EmailTextBox($this, 'txtSellerContactEmail');
			$this->txtSellerContactEmail->Name = _tr('Email to contact person');
			
			$this->txtSellerContactCity = new QTextBox($this, 'txtSellerContactCity');
			$this->txtSellerContactCity->Name = _tr('City of contact person');
			
			$this->txtSellerContactPostal = new QTextBox($this, 'txtSellerContactPostal');
			$this->txtSellerContactPostal->Name = _tr('Postal of contact person');
			
			$this->lblSellerName = new QLabel($this, 'lblSellerName');
			$this->lblSellerName->Text = $this->objLogin->CompanyName;
			
			$this->lblSellerOrgNr = new QLabel($this, 'lblSellerOrgNr');
			$this->lblSellerOrgNr->Name = _tr('D&B D-U-N-S number');
			$this->lblSellerOrgNr->Text = $this->objLogin->OrganizationNumber;
				
			$this->txtOldPass = new QTextBox($this, 'txtOldPass');
			$this->txtOldPass->Name = _tr('Old password');
			$this->txtOldPass->TextMode = QTextMode::Password;
			$this->txtOldPass->Required = false;
			
			$this->txtNewPass = new QTextBox($this, 'txtNewPass');
			$this->txtNewPass->Name = _tr('New password');
			$this->txtNewPass->TextMode = QTextMode::Password;
			$this->txtNewPass->Required = false;
			
			$this->txtNewPass2 = new VerifyTextBox($this->txtNewPass, $this, 'txtNewPass2');
			$this->txtNewPass2->Name = _tr('Verify new password');
			$this->txtNewPass2->TextMode = QTextMode::Password;
			$this->txtNewPass2->Required = false;
			$this->txtNewPass2->AddAction(new QEnterKeyEvent(), $objA = new QAjaxAction('ChangePass'));
			$this->txtNewPass2->AddAction(new QEnterKeyEvent(), new QTerminateAction());
			
			$this->btnDoChangePass = new QButton($this, 'btnDoChangePass');
			$this->btnDoChangePass->CausesValidation = false;
			$this->btnDoChangePass->Text = _tr('Ok');
			$this->btnDoChangePass->AddAction(new QClickEvent(), clone $objA);
			$this->btnDoChangePass->CssClass = 'btnEditAd';
			
			$this->btnDoEditSellerInfo = new QButton($this, 'btnDoEditSellerInfo');
			$this->btnDoEditSellerInfo->Text = _tr('Ok');
			$this->btnDoEditSellerInfo->AddAction(new QClickEvent(), $objEditAction = new QAjaxAction('DoEditSellerInfo'));
			$this->btnDoEditSellerInfo->ActionParameter = UserAnswer::OK;
			
			$this->btnCancelEditSellerInfo = new QButton($this, 'btnCancelEditSellerInfo');
			$this->btnCancelEditSellerInfo->Text = _tr('Cancel');
			$this->btnCancelEditSellerInfo->AddAction(new QClickEvent(), $objEditAction);
			$this->btnCancelEditSellerInfo->ActionParameter = UserAnswer::Cancel;
			$this->btnCancelEditSellerInfo->CausesValidation = false;	
			
			$this->lblInfo = new QLabel($this, 'lblInfo');
			$this->lblInfo->Visible = false;
			
			$this->lblPassInfo = new QLabel($this, 'lblPassInfo');
			$this->lblPassInfo->Visible = false;
			
			$this->UpdateSellerInfo();
		}
		
		public function Form_Load() {
			$this->lblInfo->Visible = false;
			
			/**
			 * We have to do this on every page refresh, since otherwise, PHP doesn't understand it's the same object as stored in session..
			 */
			$this->objLogin = Security::Current();
			
			// Hide labels
			$this->lblPassInfo->Visible = false;
			$this->lblInfo->Visible = false;
		}
		
		
		protected function UpdateSellerInfo() {
			// Put seller data in textfields
			$this->txtSellerContactName->Text = $this->objLogin->Name;
			$this->txtSellerContactAdress->Text = $this->objLogin->Address;
			$this->txtSellerContactPhone->Text = $this->objLogin->Phone;
			$this->txtSellerContactEmail->Text = $this->objLogin->Email;
			$this->txtSellerContactCity->Text = $this->objLogin->City;
			$this->txtSellerContactPostal->Text = $this->objLogin->Postal;
		}
		
		/**
		 * Save or cancel changes to seller info
		 *
		 * @param string $strFormId
		 * @param string $strControlId
		 * @param UserAnswer $intParameter
		 */
		protected function DoEditSellerInfo($strFormId, $strControlId, $intParameter) {
			// Did the user press OK?
			if ($intParameter == UserAnswer::OK ) {
				$this->objLogin->Name = $this->txtSellerContactName->Text;
				$this->objLogin->Address = $this->txtSellerContactAdress->Text;
				$this->objLogin->Phone = $this->txtSellerContactPhone->Text;
				$this->objLogin->Email = $this->txtSellerContactEmail->Text;
				$this->objLogin->City = $this->txtSellerContactCity->Text;
				$this->objLogin->Postal = $this->txtSellerContactPostal->Text;
				
				$this->objLogin->Save();
				
				$this->lblInfo->Text = _tr('Your changes are saved');
				$this->lblInfo->Visible = true;
			} else
				$this->UpdateSellerInfo();
		}
		
		/**
		 * Change the password
		 *
		 */
		protected function ChangePass() {
			// Manually valuate the controls, in the abscence of validationgroups.. Since we can't have Required, we have to make sure there's data as well
			if (!$this->txtOldPass->Text) {
				$this->txtOldPass->Warning = _tr('Required');
				return;
			}
			
			if (!$this->txtOldPass->Validate())
				return;
			
			if (!$this->txtNewPass->Text) {
				$this->txtNewPass->Warning = _tr('Required');
				return;
			}
			
			if (!$this->txtNewPass->Validate())
				return;
				
			if (!$this->txtNewPass2->Text) {
				$this->txtNewPass2->Warning = _tr('Required');
				return;
			}
			
			if (!$this->txtNewPass2->Validate())
				return;
				
			// Make sure old pass is correct
			if (!$this->objLogin->CheckPass($this->txtOldPass->Text)) {
				$this->txtOldPass->Warning = _tr('Wrong password');
				return;
			}
				
			// Change pass
			$this->objLogin->Password = $this->txtNewPass->Text;
			$this->objLogin->Save();
			
			$this->lblPassInfo->Visible = true;
			$this->lblPassInfo->Text = _tr('Your password is changed');
			
			$this->txtNewPass->Text = '';
			$this->txtNewPass2->Text = '';
			$this->txtOldPass->Text = '';
		}
	}
?>