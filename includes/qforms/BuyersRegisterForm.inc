<?php
    /**
     * Form to register buyer
     *
     * @author Kung den Knege <kungdenknege@gmail.com>
     * @package oqtopus
     * @subpackage qforms
     */
    class BuyersRegisterForm extends OqtopusForm {
        protected $txtFirstName;
		protected $txtSecondName;
        protected $txtAddress;
        protected $txtPostal;
        protected $txtCity;
        protected $txtPhone;
        protected $txtEmail;
        protected $txtOrgNumber;
        protected $txtCompanyName;
        protected $txtUsername;
        protected $txtPassword;
        protected $txtPassword2;
        protected $btnOk;
        protected $lblInfo;
        
        protected function Form_Create() {
        	try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			Security::VerifyAccess(Actions::Register);
            
            $this->txtFirstName = new QTextBox($this, 'txtFirstName');
            $this->txtFirstName->Name = _tr("FirstName");
            $this->txtFirstName->MinLength = 2;
            $this->txtFirstName->MaxLength = 100;
            
			$this->txtSecondName = new QTextBox($this, 'txtSecondName');
            $this->txtSecondName->Name = _tr("SecondName");
            $this->txtSecondName->MinLength = 2;
            $this->txtSecondName->MaxLength = 100;
			
            $this->txtAddress = new QTextBox($this,'txtAddress');
            $this->txtAddress->Name = _tr("Address of contact person");
            $this->txtAddress->MaxLength = 70;
            
            $this->txtPostal = new QTextBox($this, 'txtPostal');
            $this->txtPostal->Name = _tr("Postal of contact person");
            $this->txtPostal->MaxLength = 6;
            
            $this->txtCity = new QTextBox($this, 'txtCity');
            $this->txtCity->Name = _tr("City of contact person");
            $this->txtCity->MaxLength = 24;
            
            $this->txtPhone = new QTextBox($this, 'txtPhone');
            $this->txtPhone->Name = _tr("Phone number to contact person");
            
            $this->txtEmail = new EmailTextBox($this, 'txtEmail');
            $this->txtEmail->Name = _tr("Email to contact person");
            
            $this->txtOrgNumber = new OrganizationNumberTextBox($this, 'txtOrgNumber');
            $this->txtOrgNumber->Name = _tr("D&B D-U-N-S number");
            
            $this->txtCompanyName = new QTextBox($this, 'txtCompanyName');
            $this->txtCompanyName->Name = _tr("Company name");
            $this->txtCompanyName->MaxLength = 50;
            
            $this->txtUsername = new QTextBox($this, 'txtUsername');
            $this->txtUsername->Name = _tr("Username");
            $this->txtUsername->MinLength = 3;
            $this->txtUsername->MaxLength = 20;
            
            $this->txtPassword = new QTextBox($this, 'txtPassword');
            $this->txtPassword->Name = _tr("Password");
            $this->txtPassword->TextMode = QTextMode::Password;

            $this->txtPassword2 = new VerifyTextBox($this->txtPassword, $this, 'txtPassword2');
            $this->txtPassword2->Name = _tr("Repeat password");
            $this->txtPassword2->TextMode = QTextMode::Password;
            
            $this->btnOk = new QButton($this, 'btnRegister');
            $this->btnOk->Text = _tr("Sign up!");
            $this->btnOk->AddAction(new QClickEvent(), new QAjaxAction("DoRegister"));
            $this->btnOk->PrimaryButton = true;
            
            $this->lblInfo = new QLabel($this);
            $this->lblInfo->Visible = false;
        }
        
        protected function DoRegister() {
                // Create login
                $login = new Login();
                $login->Password = $this->txtPassword->Text;
                $login->Role = Role::Buyer;
                $login->Name = sprintf('%s %s', $this->txtFirstName->Text, $this->txtSecondName->Text);
                $login->Address = $this->txtAddress->Text;
                $login->City = $this->txtCity->Text;
                $login->Postal = $this->txtPostal->Text;
                $login->Phone = $this->txtPhone->Text;
                $login->Email = $this->txtEmail->Text;
                $login->Username = $this->txtUsername->Text;
                $login->OrganizationNumber = $this->txtOrgNumber->Text;
                $login->CompanyName = $this->txtCompanyName->Text;
                $login->Notes = Random::generateUpperChars(25);
                $login->Status = LoginStatus::Registered;
                
                try {
                    $login->Save();
                    
                    // Send email and let user know
                    Mail::SendActivationMail($login, $this->txtPassword->Text);
					$this->btnOk->Enabled = false;
					$this->lblInfo->Text = _tr('Thankyou! An email has now been sent to the address you specified. Follow the instructions therein to activate your account.');
					$this->lblInfo->Visible = true;
                } catch (QMySqliDatabaseException $e) {
                	if ($e->ErrorNumber == 1062) {
                		// Is it Username or SellerName?
                		if (strpos($e->getMessage(), $this->txtUsername->Text)) {
                			$this->txtUsername->Warning = _tr("Username already in use");
                 		} else {
                			if ($login->Id)
                				$login->Delete();
                			throw $e;
                		}
                		if ($login->Id)
                			$login->Delete();	
                	} else
                		throw $e;
                } catch (Exception $e) {
          			if ($login->Id)
           				$login->Delete();
           				
           			throw $e;
                }
        }
    }

?>