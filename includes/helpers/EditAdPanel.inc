<?php
	class EditAdPanel extends AdPanel {
		public $pnlAdEdit;	
		public $txtAdName;
		public $txtAdAgeFrom;
		public $txtAdAgeTo;
		public $rblAdSex;
		public $rlbAdArea;
		public $rlbAdSubArea;
		public $rlbAdSubSubArea;
		public $txtAdDesc;
		public $txtAdPrice;
		public $bmcEducations;
		public $bmcSalaries;
		public $bmcSectors;
		public $txtAdReach;
		public $lbAdType;
		public $lbAdSubType;
		public $dtpAdDeadline;
		public $dtpAdPublication;
		public $kwcKeywords;
		public $btnDoAdEdit;
		public $btnCancelAdEdit;
		public $mlbPermissions;
		public $rblPermissions;
		public $btnRemove;
		
		public $btnEditAd;
		public $btnMakeSim;
		
		protected $blnEditMode = false;
		
		/**
		 * This is supposed to store a Callback (string or array, see PHP doc), that gets called when an ad is saved
		 * As argument the Ad::Type is passed
		 *
		 * @var unknown_type
		 */
		protected $objCallback = null;
		
		public function __construct($objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			$this->btnEditAd = new QButton($this);
			$this->btnEditAd->CausesValidation = false;
			$this->btnEditAd->Text = _tr('Edit');
			$this->btnEditAd->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'EditAd'));
			$this->btnEditAd->CssClass='btnEditAd'; 
			
			$this->btnMakeSim = new QButton($this);
			$this->btnMakeSim->CausesValidation = false;
			$this->btnMakeSim->Text = _tr('Make discount');
			$this->btnMakeSim->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'MakeSim'));
			$this->btnMakeSim->CssClass = 'btnMakeSim';
			
			$this->btnRemove = new QButton($this);
			$this->btnRemove->CausesValidation = false;
			$this->btnRemove->Text = _tr('Remove');
			$this->btnRemove->CssClass = 'btnRemoveAds';
			$this->btnRemove->AddAction(new QClickEvent(), new JSConfirmAction());
			$this->btnRemove->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'Delete'));
			
			// Remove MakeBid-btn
			$this->RemoveChildControl($this->btnMakeBid->ControlId, true);
			
			// Initialize ages
				$this->txtAdAgeFrom = new QTextBox($this);
				$this->txtAdAgeFrom->Name = _tr('Target ages');
				$this->txtAdAgeFrom->CssClass='txtAdAgeFrom'; 
				$this->txtAdAgeFrom->Required = false;
				$this->txtAdAgeFrom->MaxLength = 2;
				
				$this->txtAdAgeTo = new QIntegerTextBox($this);
				$this->txtAdAgeTo->CssClass='txtAdAgeTo'; 
				$this->txtAdAgeTo->Required = false;
				$this->txtAdAgeTo->MaxLength = 2;
				
			// Initialize sex
				$this->rblAdSex = new QRadioButtonList($this);
				$this->rblAdSex->Name = _tr('Target sex');
				$this->rblAdSex->Required = false;
				$this->rblAdSex->CssClass = 'rblAdSex';
				$this->rblAdSex->AddItem(_tr('Both'), Sex::Both);
				$this->rblAdSex->AddItem(_tr('Males'), Sex::Males);
				$this->rblAdSex->AddItem(_tr('Females'), Sex::Females);
			
			// Initialize areas, types and subtypes (empty)
				$this->rlbAdArea = new ReferenceListBox(Areas::$Areas, $this);
				$this->rlbAdArea->Name = _tr('State');
				$this->rlbAdArea->CssClass = 'rlbAdArea';
				
				$this->rlbAdSubArea = new ReferenceListBox(Areas::$SubAreas, $this);
				$this->rlbAdSubArea->Name = _tr('City');
				$this->rlbAdSubArea->Parent = $this->rlbAdArea;
				$this->rlbAdSubArea->CssClass = 'rlbAdSubArea';
				
				$this->rlbAdSubSubArea = new ReferenceListBox(Areas::$SubSubAreas, $this);
				$this->rlbAdSubSubArea->Name = _tr('Town');
				$this->rlbAdSubSubArea->Parent = $this->rlbAdSubArea;
				$this->rlbAdSubSubArea->CssClass = 'rlbAdSubSubArea';
				
				$this->lbAdType = new QListBox($this);
				$this->lbAdType->Name = _tr('Type');
				$this->lbAdType->AddAction(new QChangeEvent(), new QAjaxControlAction($this, 'UpdateSubMedia'));
				$this->lbAdType->CssClass = 'lbAdType';
				foreach (MediaType::$MediaType as $value => $name)
					$this->lbAdType->AddItem($name, $value);
					
				$this->lbAdSubType = new QListBox($this);
				$this->lbAdSubType->CssClass = 'lbAdSubType';

			// Initialize educations, sectors, salaries and interests
				$this->bmcEducations = new BitmaskComposite(Education::$Education, $this);
				$this->bmcEducations->Name = _tr('Target education level');
				
				$this->bmcSectors = new BitmaskComposite(Sector::$Sector, $this);
				$this->bmcSectors->Name = _tr('Target proffission');
				
				$this->bmcSalaries = new BitmaskComposite(Salary::$Salary, $this);
				$this->bmcSalaries->Name = _tr('Target salary');
				
			// Initialize name, description, deadline, price and reach
				$this->txtAdName = new QTextBox($this);
				$this->txtAdName->Name = _tr('Name');
				$this->txtAdName->MaxLength = 22;
				$this->txtAdName->CssClass = 'txtAdName';
				
				$this->txtAdDesc = new MultiLineTextBox($this);
				$this->txtAdDesc->RowLimit = 4;
				$this->txtAdDesc->Name = _tr('Description');
				$this->txtAdDesc->CssClass = 'txtAdDesc';

				$this->dtpAdDeadline = new QDateTimePicker($this);
				$this->dtpAdDeadline->Name = _tr('Deadline for ad');
				$this->dtpAdDeadline->DateTimePickerFormat = QDateTimePickerFormat::YearMonthDay;
				$this->dtpAdDeadline->Required = false;
				$this->dtpAdDeadline->CssClass = 'dtpAdDeadline';
				
				$this->dtpAdPublication = new QDateTimePicker($this);
				$this->dtpAdPublication->Name = _tr('Publication date');
				$this->dtpAdPublication->DateTimePickerFormat = QDateTimePickerFormat::YearMonthDay;
				$this->dtpAdPublication->Required = false;
				$this->dtpAdPublication->CssClass = 'dtpAdPublication';
				
				$this->txtAdPrice = new QIntegerTextBox($this);
				$this->txtAdPrice->Name = _tr('Price');
				$this->txtAdPrice->MaxLength = 8;
				$this->txtAdPrice->CssClass = 'txtAdPrice';
				
				$this->txtAdReach = new QIntegerTextBox($this);
				$this->txtAdReach->Name = _tr('Reach');
				$this->txtAdReach->MaxLength = 8;
				$this->txtAdReach->CssClass = 'txtAdReach';
				
			// Initialize keywords
				$this->kwcKeywords = new KeywordsComposite($this);
				$this->kwcKeywords->Required = true;
				$this->kwcKeywords->Name = _tr('Keywords');
				
			// Initialize OK and Cancel buttons
				$this->btnDoAdEdit = new QButton($this);
				$this->btnDoAdEdit->Text = _tr('Ok');
				$this->btnDoAdEdit->AddAction(new QClickEvent(), $objEditAction = new QAjaxControlAction($this, 'DoEditAd'));
				$this->btnDoAdEdit->ActionParameter = UserAnswer::OK;
				$this->btnDoAdEdit->CssClass = 'btnDoAdEdit';
		
				$this->btnCancelAdEdit = new QButton($this);
				$this->btnCancelAdEdit->Text = _tr('Reaset');
				$this->btnCancelAdEdit->AddAction(new QClickEvent(), $objEditAction);
				$this->btnCancelAdEdit->ActionParameter = UserAnswer::Cancel;
				$this->btnCancelAdEdit->CausesValidation = false;			
				$this->btnCancelAdEdit->CssClass = 'btnCancelAdEdit';
				
				$this->rblPermissions = new QRadioButtonList($this);
				$this->rblPermissions->Name = _tr('Ad is available for');
				$this->rblPermissions->Required = true;
				$this->rblPermissions->CssClass = 'rblPermissions';
				$this->rblPermissions->AddItem(_tr('members of these campaign networks only'), PermissionMode::IncludeOnly);
				$this->rblPermissions->AddItem(_tr('everyone but members of these campaign networks'), PermissionMode::Exclude);
				$this->rblPermissions->AddItem(_tr('everyone'), PermissionMode::All, true);
				$this->rblPermissions->AddAction(new QChangeEvent(), new QAjaxControlAction($this, 'ManagePermissions'));
				$this->mlbPermissions = new MultipleListBox($this);
		}
		
		/**
		 * Edit ad info
		 *
		 */
		public function EditAd() {
			// Short hand object reference
			$objAd = $this->objAd;
			
			$this->Visible = true;
				
			// Fill ages
			$this->txtAdAgeFrom->Text = $objAd->StartAge;
			$this->txtAdAgeTo->Text = $objAd->EndAge;
			
			// Select sex, area and type
			$this->rblAdSex->SelectedIndex = -1;
			if ($objSelected = $this->rblAdSex->GetItemByValue($objAd->Sex))
				$objSelected->Selected = true;
				
			$this->rlbAdArea->Selected = $objAd->Area;
			$this->rlbAdSubArea->Selected = $objAd->SubArea;
			$this->rlbAdSubSubArea->Selected = $objAd->SubSubArea;
				
			$this->lbAdType->SelectedIndex = -1;
			if ($objSelected = $this->lbAdType->GetItemByValue($objAd->MediaType))
				$objSelected->Selected = true;
			else // Make sure somthing gets selected
				$this->lbAdType->SelectedIndex = 0;
				
			// Fill subtype with values and select if appropiate
			$this->UpdateSubMedia($this->Form->FormId, $this->lbAdType->ControlId, null);
			if ($objAd->MediaSubType)
				$this->lbAdSubType->GetItemByValue($objAd->MediaSubType)->Selected = true;
		 	
			// Fill deadline, name, description, price and reach
			$this->dtpAdDeadline->Visible = ($objAd->Type == AdType::SIM);
			$this->dtpAdDeadline->DateTime =  new QDateTime($objAd->Deadline);
			
			$this->dtpAdPublication->Visible = ($objAd->Type == AdType::SIM);
			$this->dtpAdPublication->DateTime = $objAd->PublicationDate;
			
			// Fill permissions
			if ($objAd->PermissionMode) {
				$this->rblPermissions->SelectedIndex = -1;
				if ($objAd->PermissionMode)
					$this->rblPermissions->GetItemByValue($objAd->PermissionMode)->Selected = true;
			}
			
			$this->mlbPermissions->RemoveAllItems();	
			foreach ($objAd->Seller->GetNetworkArrayWithSelectedByAd($objAd) as $objNetwork)
				$this->mlbPermissions->AddItem($objNetwork->Name, $objNetwork, (bool)$objNetwork->GetVirtualAttribute('Selected'));
				
			$this->rblPermissions->Visible = $this->mlbPermissions->Visible = ($objAd->Type == AdType::SIM && $this->mlbPermissions->ItemCount);
			
			
			$this->ManagePermissions();
		 	
		 	$this->txtAdName->Text = $objAd->Name;
		 	$this->txtAdDesc->Text = $objAd->Description;			
			$this->txtAdPrice->Text = $objAd->Price;
			$this->txtAdReach->Text = $objAd->Reach;
		 	
			// Select intersts, salaries, sectors and educations
			$this->bmcSalaries->Bitmask = $objAd->Salaries;
			$this->bmcSectors->Bitmask = $objAd->Sectors;
			$this->bmcEducations->Bitmask = $objAd->Educations;
			
			// Fill keywords
			$this->kwcKeywords->Keywords = $objAd->Keywords;
			
			$this->blnEditMode = true;
			$this->blnModified = true;
		}
		
		/*
		 * Save or cancel changes to ad
		 *
		 * @param string $strFormId
		 * @param string $strControlId
		 * @param UserAnswer $intParameter
		 */
		public function DoEditAd($strFormId, $strControlId, $intParameter) {
			$objAd = $this->objAd;
			
			// Did the user press OK?
			if ($intParameter == UserAnswer::OK) {
					// Validate age fields
					if (($this->txtAdAgeFrom->Text || $this->txtAdAgeTo->Text) && !(is_numeric($this->txtAdAgeFrom->Text) && (int)($this->txtAdAgeFrom->Text) <= (int)($this->txtAdAgeTo->Text))) {
						$this->txtAdAgeTo->Warning = _tr('Please specify sane values!');
						QApplication::DisplayAlert(_tr('One of the values are missing or incorrect!'));
						return;
					}
					
					// Validate date fields
					if (!$this->ValidateAdDates()) {
						QApplication::DisplayAlert(_tr('One of the values are missing or incorrect!'));			
						return;
					}
						
				// Save all values
				$objAd->MediaType = $this->lbAdType->SelectedValue;
				$objAd->MediaSubType = ($this->lbAdSubType->SelectedIndex == -1) ? null : $this->lbAdSubType->SelectedValue;
				$objAd->Reach = $this->txtAdReach->Text;
				$objAd->Price = $this->txtAdPrice->Text;
				$objAd->Area = $this->rlbAdArea->Selected;
				$objAd->SubArea = $this->rlbAdSubArea->Selected;
				$objAd->SubSubArea = $this->rlbAdSubSubArea->Selected;
				$objAd->StartAge = $this->txtAdAgeFrom->Text;
				$objAd->EndAge = $this->txtAdAgeTo->Text;
				$objAd->Sex = $this->rblAdSex->SelectedValue;
				$objAd->Name = $this->txtAdName->Text;

				$objAd->Educations = $this->bmcEducations->Bitmask;					
				$objAd->Sectors = $this->bmcSectors->Bitmask;					
				$objAd->Salaries = $this->bmcSalaries->Bitmask;
				
				$objAd->Description = $this->txtAdDesc->Text;
				
				$objAd->Keywords = $this->kwcKeywords->Keywords;
				
				// Save deadline and permissionmode if SIM, and force update of appropiate datagrid
				switch ($objAd->Type) {
					case AdType::SIM:
						// Expires on the end of the deadline day
						if ($this->dtpAdDeadline->DateTime && !$this->dtpAdDeadline->DateTime->IsNull()) {
							$dt = $this->dtpAdDeadline->DateTime;
							$dt->Hour = 23;
							$dt->Minute = 59;
							$dt->Second = 59;

							$objAd->Deadline = $dt->Timestamp;
						} else
							$objAd->Deadline = null;
						
						$objAd->PublicationDate = $this->dtpAdPublication->DateTime;
		
						$objAd->PermissionMode = $this->rblPermissions->SelectedValue;
						break;
				}
				
				
				// Well.. save changes	
				$objAd->Save();		
				
				// Associate with networks, if appropiate (must be after save since it might be a new ad)
				if ($this->mlbPermissions->Visible) {
					$this->objAd->UnassociateAllNetworks();
					for ($i = 0; $i < $this->mlbPermissions->ItemCount; $i++)
						if ($this->mlbPermissions->GetItem($i)->Selected)
							$this->objAd->AssociateNetwork($this->mlbPermissions->GetItem($i)->Value);
				}
				
				// Call callback with adtype as argument!
				call_user_func($this->objCallback, $objAd->Type);
				
				// Update info
				$this->SelectAd();	
			} else
				if (!$this->objAd->Id)
					$this->CloseAd();
			
			$this->blnEditMode = false;
			$this->blnModified = true;
		}		
		
		public function __get($strName) {
			switch ($strName) {
				case 'IsEditing':
					return $this->blnEditMode;
					
				case 'Callback':
					return $this->objCallback;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Callback':
					$this->objCallback = $mixValue;
					break;
					
				case 'Ad':
					$this->btnMakeSim->Visible = ($mixValue->Type == AdType::STD);
					
				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		public function ManagePermissions() {
			$this->mlbPermissions->Enabled = !$this->rblPermissions->GetItemByValue(PermissionMode::All)->Selected;
			$this->mlbPermissions->MarkAsModified();
		}
		
		protected function GetControlHtml() {
			$this->Template = sprintf('%s%s.%s.inc', __TEMPLATES__, __CLASS__, $this->blnEditMode ? 'Edit' : 'NonEdit');
			
			try {
				return parent::GetControlHtml();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
		}
		
		/**
		 * If the selected mediatype has got subtypes, put them in the listbox
		 *
		 * @param string $strFormId
		 * @param string $strControlId
		 * @param string $strParameter
		 */
		public function UpdateSubMedia($strFormId, $strControlId, $strParameter) {
			$this->lbAdSubType->RemoveAllItems();
			if ( $temp = MediaType::$MediaSubType[$this->objChildControlArray[$strControlId]->SelectedValue]) {
				foreach ($temp as $value => $name)
					$this->lbAdSubType->AddItem($name, $value);
				$this->lbAdSubType->Visible = true;
			} else
				$this->lbAdSubType->Visible = false;
		}	

		public function MakeSim($strFormId, $strControlId, $strParameter) {
			$objAd = $this->objAd;
			$objSim = clone $objAd;
			$objSim->Name = $objAd->Name;
			$objSim->Description = $objAd->Description;
			$objSim->Type = AdType::SIM;
			$this->objAd = $objSim;
			$this->EditAd();
		}
		
		public function Delete() {
			$this->objAd->Delete();
			$this->CloseAd();
			call_user_func($this->objCallback, $objAd->Type);
		}
		
		private function ValidateAdDates() {
			if ($this->dtpAdDeadline->DateTime && !$this->dtpAdDeadline->DateTime->IsNull() && $this->dtpAdPublication->DateTime && !$this->dtpAdPublication->DateTime->IsNull()) {
				if ($this->dtpAdDeadline->DateTime->Timestamp > $this->dtpAdPublication->DateTime->Timestamp) {
					$this->dtpAdDeadline->Warning = _tr('Deadline has to be before publication date');
					$this->dtpAdDeadline->MarkAsModified();
					return false;
					
				}
					
			}
			return true;
		}
	}
?>