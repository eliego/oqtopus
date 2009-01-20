<?php
	class SearchForm extends OqtopusForm {
		protected $pnlSearch;
		protected $pnlResults;
		protected $txtKeyword;
		//protected $lbKeywordMode;
		protected $lbReachMode;
		protected $lbPriceMode;
		protected $txtReach;
		protected $txtPrice;
		protected $txtAge;
		protected $lbSex;
		protected $rlbArea;
		protected $rlbSubArea;
		protected $rlbSubSubArea;
		protected $lbMediaType;
		protected $lbMediaSubType;
		protected $cblSendEmail;
		protected $btnOk;
		protected $lbSalary;
		protected $lbSector;
		protected $lbEducation;
		protected $lblMediaHeader;
		protected $lblConsumerHeader;
		protected $intCounter = 0;
		
		protected $objResults = array();
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			Security::VerifyAccess(Actions::Search);
			
			$this->pnlResults = new QPanel($this, 'pnlResults');
			$this->pnlResults->AutoRenderChildren = true;
			
			$this->pnlSearch = new MinimizablePanel($this, 'pnlSearch');
			$this->pnlSearch->Template = sprintf("%s%s.pnlSearch.inc", __TEMPLATES__, __CLASS__);
			$this->pnlSearch->MinimizedHeight = 110;
			$this->pnlSearch->MinLabel = _tr('Simple');
			$this->pnlSearch->MaxLabel = _tr('Advanced');
			
			$this->txtKeyword = new QTextBox($this->pnlSearch, "txtKeyword");
			$this->txtKeyword->Name = _tr("Keyword");
			//$this->txtKeyword->LoadMethod = 'LoadKeywordHints';
			$this->txtKeyword->Required = false;
			$this->txtKeyword->AddAction(new QEnterKeyEvent(null, "qcodo.getControl('txtKeyword').value != ''"), new QAjaxAction('NewSearch'));
			$this->txtKeyword->AddAction(new QEnterKeyEvent(), new QTerminateAction());
			
/*			$this->lbKeywordMode = new QListBox($this->pnlSearch, 'lbKeywordMode');
			$this->lbKeywordMode->AddItem(_tr('All of the words'), KeywordMode::Och);
			$this->lbKeywordMode->AddItem(_tr('One of the words'), KeywordMode::Eller);*/
			
			$this->lbReachMode = new QListBox($this->pnlSearch, "lbReachMode");
			$this->lbReachMode->AddItem(_tr("Greater than"), SearchParameterMode::GT);
			$this->lbReachMode->AddItem(_tr("Less than"), SearchParameterMode::LT);
			
			$this->lbPriceMode = new QListBox($this->pnlSearch, 'lbPriceMode');
			$this->lbPriceMode->AddItem(_tr("Greater than"), SearchParameterMode::GT);
			$this->lbPriceMode->AddItem(_tr("Less than"), SearchParameterMode::LT);
									
			$this->txtReach = new QIntegerTextBox($this->pnlSearch, 'txtReach');
			$this->txtReach->Name = _tr("Reach");
			$this->txtReach->ErrorClass = 'SpecialError';
			$this->txtReach->Required = false;
			
			$this->txtPrice = new QIntegerTextBox($this->pnlSearch, 'txtPrice');
			$this->txtPrice->Name = _tr("Requested price");
			$this->txtPrice->ErrorClass = 'SpecialError';
			$this->txtPrice->Required = false;

			$this->txtAge = new QIntegerTextBox($this->pnlSearch, 'txtAge');
			$this->txtAge->Name = _tr('Target age');
			$this->txtAge->Required = false;
			
			$this->lbSex = new QListBox($this->pnlSearch, 'lbSex');
			$this->lbSex->Name = _tr("Target sex");
			$this->lbSex->AddItem(_tr("Doesn't matter"), null, true);
			$this->lbSex->AddItem(_tr("Males"), Sex::Males);
			$this->lbSex->AddItem(_tr('Females'), Sex::Females);
			$this->lbSex->AddItem(_tr('Both'), Sex::Both);
			
			$this->rlbArea = new ReferenceListBox(Areas::$Areas, $this->pnlSearch, 'rlbArea');
			$this->rlbArea->Name = _tr('State');
			$this->rlbArea->NullName = _tr("Doesn't matter");
			
			$this->rlbSubArea = new ReferenceListBox(Areas::$SubAreas, $this->pnlSearch, 'rlbSubArea');
			$this->rlbSubArea->Name = _tr('City');
			$this->rlbSubArea->Parent = $this->rlbArea;
			$this->rlbSubArea->NullName = $this->rlbArea->NullName;
			$this->rlbSubArea->strParentName = 'län';
			
			$this->rlbSubSubArea = new ReferenceListBox(Areas::$SubSubAreas, $this->pnlSearch, 'rlbSubSubArea');
			$this->rlbSubSubArea->Name = _tr('Town');
			$this->rlbSubSubArea->Parent = $this->rlbSubArea;
			$this->rlbSubSubArea->NullName = $this->rlbSubArea->NullName;
			$this->rlbSubSubArea->strParentName = 'kommun';
			
			$this->lbMediaType = new QListBox($this->pnlSearch, 'lbMediaType');
			$this->lbMediaType->Name = _tr("Medium");
			$this->lbMediaType->AddAction(new QChangeEvent(), new QAjaxAction('UpdateSubMedia'));
			$this->lbMediaType->AddItem(_tr("Doesn't matter"), null, true);
			foreach (MediaType::$MediaType as $value => $name)
				$this->lbMediaType->AddItem($name, $value);
				
			$this->lbMediaSubType = new QListBox($this->pnlSearch, 'lbMediaSubType');
			$this->lbMediaSubType->Name = _tr("Submedium");
			$this->lbMediaSubType->AddItem(_tr("Choose medium first"), null);
					
			// Only show if we're logged in and can save searches
			$this->cblSendEmail = new QCheckBox($this->pnlSearch, 'cblSendEmail');
			$this->cblSendEmail->Text = _tr("Send me an email when a new matching ad is registered");
			$this->cblSendEmail->Checked = true;
			
			$this->btnOk = new QImageButton($this->pnlSearch, 'btnOk');
			$this->btnOk->AlternateText = _tr("Search");
			$this->btnOk->ImageUrl = ('/adds/sok.png');
			$this->btnOk->AddAction(new QClickEvent(), new QAjaxAction('NewSearch'));
			
			$this->lbEducation = new QListBox($this->pnlSearch, 'lbEducation');
			$this->lbEducation->Name = _tr('Education');
			$this->lbEducation->AddItem(_tr("Doesn't matter"), null, true);
			foreach (Education::$Education as $value => $name)
				$this->lbEducation->AddItem($name, $value);
				
			$this->lbSector = new QListBox($this->pnlSearch, 'lbSector');
			$this->lbSector->Name = _tr('Proffession');
			$this->lbSector->AddItem(_tr("Doesn't matter"), null, true);
			foreach (Sector::$Sector as $value => $name)
				$this->lbSector->AddItem($name, $value);
				
			$this->lbSalary = new QListBox($this->pnlSearch, 'lbSalary');
			$this->lbSalary->Name = _tr('Salary');
			$this->lbSalary->AddItem(_tr("Doesn't matter"), null, true);
			foreach (Salary::$Salary as $value => $name) 
				$this->lbSalary->AddItem($name, $value);
				
			$this->lblMediaHeader = new QLabel($this->pnlSearch, 'lblMediaHeader');
			$this->lblMediaHeader->Text = _tr('Media selection');
			
			$this->lblConsumerHeader = new QLabel($this->pnlSearch, 'lblConsumerHeader');
			$this->lblConsumerHeader->Text = _tr('Consumer selection');
			
			// Start panel minimized, but keep showing txtKeyword
			$this->pnlSearch->AlwaysShow($this->txtKeyword);
			$this->pnlSearch->AlwaysShow($this->cblSendEmail);
			$this->pnlSearch->AlwaysShow($this->btnOk);
			$this->pnlSearch->changeState();
			
			// Load saved searches
			foreach (Security::Current()->GetSearchArray() as $objSearch)
				$this->ShowSearch($objSearch);
		}
		
		protected function NewSearch() {
			$objSearch = new Search();
			if ($this->txtAge)
				$objSearch->Age = $this->txtAge->Text;
			if ($this->lbSex->SelectedValue)
				$objSearch->Sex = $this->lbSex->SelectedValue;
			if ($this->rlbArea->Selected)
				$objSearch->Area = $this->rlbArea->Selected;
			if ($this->rlbSubArea->Selected)
				$objSearch->SubArea = $this->rlbSubArea->Selected;
			if ($this->rlbSubSubArea->Selected)
				$objSearch->SubSubArea = $this->rlbSubSubArea->Selected;
			if ($this->lbMediaType->SelectedValue)
				$objSearch->MediaType = $this->lbMediaType->SelectedValue;
			if ($this->lbMediaSubType->SelectedValue)
				$objSearch->MediaSubType = $this->lbMediaSubType->SelectedValue;
			if ($this->lbSalary->SelectedValue)
				$objSearch->Salary = $this->lbSalary->SelectedValue;
			if ($this->lbSector->SelectedValue)
				$objSearch->Sector = $this->lbSector->SelectedValue;
			if ($this->lbEducation->SelectedValue)
				$objSearch->Education = $this->lbEducation->SelectedValue;
			if ($this->txtPrice->Text) {
				$objSearch->PriceMode = $this->lbPriceMode->SelectedValue;
				$objSearch->Price = $this->txtPrice->Text;
			} if ($this->txtReach->Text) {
				$objSearch->ReachMode = $this->lbReachMode->SelectedValue;
				$objSearch->Reach = $this->txtReach->Text;
			} if ($this->txtKeyword->Text) {
				$strKs = array();
				foreach (explode(' ', $this->txtKeyword->Text) as $strK)
					if ($strK)
						$strKs[] = trim($strK);
				$objSearch->Keywords = $strKs;
				$objSearch->KeywordMode = KeywordMode::Och;
			}

			$objSearch->SendEmail = (int)$this->cblSendEmail->Checked;
			$objSearch->LoginId = Security::Current()->Id;
			$objSearch->Save();
			
			$this->ShowSearch($objSearch);	
		}
		
		private function ShowSearch($objSearch)
		{
			$this->intCounter++;
			if (!$objSearch->Name)
				$objSearch->Name = sprintf(_tr('Search %d'), $this->intCounter);
			$objResultBox = new SearchComposite($objSearch, $this->pnlResults);
			$objResultBox->CssClass = "objResultBox";
			$objResultBox->ItemsPerPage = OQTOPUS_SEARCH_RESULTS_PER_PAGE;
			$objResultBox->MinimizedHeight = 17;
		}
		
		protected function UpdateSubMedia($strFormId, $strControlId, $strParameter) {
			$this->lbMediaSubType->RemoveAllItems();
			if ($this->GetControl($strControlId)->SelectedValue && $temp = MediaType::$MediaSubType[$this->GetControl($strControlId)->SelectedValue]) {
				$this->lbMediaSubType->AddItem(_tr("Doesn't matter"), null, true);
				foreach ($temp as $value => $name)
					$this->lbMediaSubType->AddItem($name, $value);
				$this->lbMediaSubType->Visible = true;
			} else
				$this->lbMediaSubType->Visible = false;
		}
		
		public static function LoadKeywordHints() { // we have to be a bit ugly here - using qcodo for each hint-request causes unserializing of all objects - fucks performance too much
			return 'test';
		}
	}	
?>