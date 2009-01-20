<?php
	class AdsForm extends OqtopusForm {
		protected $dtgSIMs;
		protected $dtgAds;

		protected $btnAddAd;
		protected $btnAddSim;
		
		protected $objEditAd;
		protected $objEditSim;	
		
		protected $objCache;
		protected $objSeller;
		protected $objSelectedAd;
		
		public $intSelected;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->objCache = new ObjectCache();
			
			$this->objSeller = $this->LoadSeller();
			
			Security::VerifyAccess(Actions::ManageAds, $this->objSeller);
			
			$this->objEditAd = new EditAdPanel($this, 'objEditAd');
			$this->objEditAd->Callback = array($this, 'UpdateDTGs');
			$this->objEditSim = new EditAdPanel($this, 'objEditSim');
			$this->objEditSim->Callback = $this->objEditAd->Callback;
			
			// Initialize add ad buttons
				$this->btnAddAd = new QButton($this, 'btnAddAd');
				$this->btnAddAd->Text = _tr('Create price');
				$this->btnAddAd->AddAction(new QClickEvent(), $objAddAction = new QAjaxAction('AddAd'));
				$this->btnAddAd->ActionParameter = AdType::STD;
				$this->btnAddAd->CausesValidation = false;
				
				$this->btnAddSim = new QButton($this, 'btnAddSim');	
				$this->btnAddSim->Text = _tr('Create discount');
				$this->btnAddSim->AddAction(new QClickEvent(), $objAddAction);
				$this->btnAddSim->ActionParameter = AdType::SIM;
				$this->btnAddSim->CausesValidation = false;	
				
			// Initialize datagridcolumns
				//$dgcMediaType = new QDataGridColumn(_tr('Medium'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . (MediaType::$MediaType[$_ITEM->MediaType]) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ? >');
				//$dgcMediaType->SortByCommand = 'media_type';
			
				$dgcMediaSubType = new QDataGridColumn(_tr('Medium'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->MediaSubType ? MediaType::$MediaSubType[$_ITEM->MediaType][$_ITEM->MediaSubType] : "-") . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcMediaSubType->SortByCommand = 'media_sub_type';
			
				$dgcName = new QDataGridColumn(_tr('Name'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_FORM->CreateSelectButton($_ITEM, $_CONTROL)) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcName->SortByCommand = 'name ASC';
				$dgcName->ReverseSortByCommand = 'name DESC';
			
				$dgcReach = new QDataGridColumn(_tr('Reach'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->Reach) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcReach->SortByCommand = 'reach ASC';
				$dgcReach->ReverseSortByCommand = 'reach DESC';
			
				$dgcPrice = new QDataGridColumn(_tr('Requested price'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->Price) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcPrice->SortByCommand = 'price ASC';
				$dgcPrice->ReverseSortByCommand = 'price DESC';
			
				$dgcArea = new QDataGridColumn(_tr('Area'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . (Areas::$Areas[$_ITEM->Area]) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
				$dgcArea->SortByCommand = 'area';
			
				$dgcEndDate = new QDataGridColumn(_tr('Deadline'), '<?= $_ITEM->Deadline ? ($_ITEM->IsExpired() ? sprintf("<span class=\"ExpiredAd\">%s</span>", Localization::FormatTimestamp($_ITEM->Deadline)) : Localization::FormatTimestamp($_ITEM->Deadline)) : "-"?>');
				$dgcEndDate->SortByCommand = 'deadline ASC';
				$dgcEndDate->ReverseSortByCommand = 'deadline DESC';
		
				//$dgcSelect = new QDataGridColumn(null, '<?= $_FORM->CreateRemoveButton($_ITEM, $_CONTROL) ? >');
				
			// Initialize datagrids
				$this->dtgAds = new QDataGrid($this, 'dtgAds2');
				$objAdPag = new QPaginator($this->dtgAds);
				$objAdPag->CssClass='Resultat';
				$this->dtgAds->AddColumn($dgcName);
				//$this->dtgAds->AddColumn($dgcMediaType);
				$this->dtgAds->AddColumn($dgcMediaSubType);
				$this->dtgAds->AddColumn($dgcReach);
				$this->dtgAds->AddColumn($dgcPrice);
				$this->dtgAds->AddColumn($dgcArea);
				//$this->dtgAds->AddColumn($dgcSelect);
				$this->dtgAds->Name = _tr('Prices');
				$this->dtgAds->UseAjax = true;
				$this->dtgAds->Persistent = true;
				$this->dtgAds->Paginator = $objAdPag;
				$this->dtgAds->ItemsPerPage = 6;
				
				$this->dtgSIMs = new QDataGrid($this, 'dtgSIMs2');
				$objSIMPag = new QPaginator($this->dtgSIMs);
				$objSIMPag->CssClass='Resultat';
				$this->dtgSIMs->AddColumn(clone $dgcName);			
				//$this->dtgSIMs->AddColumn(clone $dgcMediaType);
				$this->dtgSIMs->AddColumn(clone $dgcMediaSubType);
				$this->dtgSIMs->AddColumn(clone $dgcReach);
				$this->dtgSIMs->AddColumn(clone $dgcPrice);
				$this->dtgSIMs->AddColumn(clone $dgcArea);
				$this->dtgSIMs->AddColumn($dgcEndDate);
				//$this->dtgSIMs->AddColumn(clone $dgcSelect);
				$this->dtgSIMs->Name = _tr('Discounts');
				$this->dtgSIMs->UseAjax = true;
				$this->dtgSIMs->Persistent = true;
				$this->dtgSIMs->Paginator = $objSIMPag;
				$this->dtgSIMs->ItemsPerPage = 6;				
		
				$objtemp=$this->dtgSIMs->HeaderRowStyle;
				$objtemp->CssClass = "BidsDataGrid_HeaderRow";
				
				$objtemp=$this->dtgSIMs->HeaderLinkStyle;
				$objtemp->CssClass = "BidsDataGrid_HeaderLink";
				
				$objtemp=$this->dtgSIMs->RowStyle;
				$objtemp->CssClass = "BidsDataGrid_Row";
				
				$objtemp=$this->dtgSIMs->AlternateRowStyle;
				$objtemp->CssClass = "BidsDataGrid_AlternateRow";
		
				$objtemp=$this->dtgAds->HeaderRowStyle;
				$objtemp->CssClass = "BidsDataGrid_HeaderRow";
				
				$objtemp=$this->dtgAds->HeaderLinkStyle;
				$objtemp->CssClass = "BidsDataGrid_HeaderLink";
				
				$objtemp=$this->dtgAds->RowStyle;
				$objtemp->CssClass = "BidsDataGrid_Row";
				
				$objtemp=$this->dtgAds->AlternateRowStyle;
				$objtemp->CssClass = "BidsDataGrid_AlternateRow";
		}
		
		public function Form_Load() {
			/**
			 * We have to load this on every refresh, otherwise PHP doesn't get that it's the same object as stored in cache (necessary for cache)
			 * We also have to put it in the EditAds again - by the same reason. This is safe as long as only objSellers ads are visible - otherwise catastrophic
			 */
			$this->objSeller = $this->LoadSeller();
			if ($this->objEditAd->Ad)
				$this->objEditAd->Ad->Seller = $this->objSeller;
				
			if ($this->objEditSim->Ad)
				$this->objEditSim->Ad->Seller = $this->objSeller;
		}
		
		protected function Form_PreRender() {
			if ($this->dtgAds->Update) {
				$this->dtgAds->TotalItemCount = count(Ad::LoadArrayBySellerAndType($this->objSeller, AdType::STD, true));
				$this->dtgAds->DataSource = Ad::LoadArrayBySellerAndType($this->objSeller, AdType::STD, true, $this->dtgAds->SortInfo, $this->dtgAds->LimitInfo);
			}
				
			if ($this->dtgSIMs->Update) {
				$this->dtgSIMs->TotalItemCount = count(Ad::LoadArrayBySellerAndType($this->objSeller, AdType::SIM, true));
				$this->dtgSIMs->DataSource = Ad::LoadArrayBySellerAndType($this->objSeller, AdType::SIM, true, $this->dtgSIMs->SortInfo, $this->dtgSIMs->LimitInfo);
			}
			
			$this->dtgAds->MarkAsModified();
			$this->dtgSIMs->MarkAsModified();
			$this->btnAddAd->Enabled = $this->btnAddSim->Enabled = !($this->objEditAd->IsEditing || $this->objEditSim->IsEditing);
		}
		
		protected function Form_Invalid() {
			QApplication::DisplayAlert(_tr('One of the values are missing or incorrect!'));
		}

		/**
		 * Render select-button for ad
		 *
		 * @param Ad $objAd
		 * @param QControl $objParent
		 */
/*		public function CreateRemoveButton($objAd, $objParent) {
			$id2 = "btnRemove" . $objAd->Id;
			
			$btnRemove = null;
			if (!($btnRemove = $this->GetControl($id2))) {
				
				$btnRemove = new QButton($objParent, $id2);
				$btnRemove->CausesValidation = false;
				$btnRemove->AddAction(new QClickEvent(), new JSConfirmAction());
				$btnRemove->AddAction(new QClickEvent(), new QAjaxAction('RemoveAd'));
				$btnRemove->Text = _tr('Remove');
				$btnRemove->ActionParameter = $objAd->Id;
				$btnRemove->CssClass = 'btnRemoveAds';
			}
			
			$btnRemove->Enabled = !($this->objEditAd->IsEditing || $this->objEditSim->IsEditing);
			return $btnRemove->Render(false);
		}	*/

		public function CreateSelectButton($objAd, $objParent) {
			$id = "btnSelect" . $objAd->Id;
			
			$btnSelect = null;
			if (!(($btnSelect = $this->getControl($id)))) {
				$btnSelect = new LinkButton($objParent, $id);
				$btnSelect->CausesValidation = false;
				$btnSelect->AddAction(new QClickEvent(), new QAjaxAction('ChooseAd'));
				$btnSelect->Text = $objAd->Name;
				$btnSelect->ActionParameter = $objAd->Id;
				//$btnSelect->CssClass = 'btnSelect';
			}
		
			return $btnSelect->Render(false);
		}
			
		/**
		 * Edit ad info
		 *
		 */
		protected function ChooseAd($strFormId, $strControlId, $strParameter) {
			// Short hand object reference
			$objAd = $this->dtgAds->GetObjectFromDataSource('Id', $strParameter);
			if (!$objAd)
				$objAd = $this->dtgSIMs->GetObjectFromDataSource('Id', $strParameter);
			if (!$objAd)
				throw new NoSuchObjectException();
			
			$this->objSelectedAd = $objAd;
			$this->intSelected = $objAd->Id;
			
			$this->objEditAd->DoEditAd(null, null, UserAnswer::Cancel);
			$this->objEditSim->DoEditAd(null, null, UserAnswer::Cancel);
			
			switch ($objAd->Type) {
				case AdType::STD:
					if ($this->objEditSim->Visible)
						$this->objEditSim->CloseAd();
						
					$this->objEditAd->Ad = $objAd;
					$this->objEditAd->SelectAd();
					break;
					
				case AdType::SIM:
					if ($this->objEditAd->Visible)
						$this->objEditAd->CloseAd();
						
					$this->objEditSim->Ad = $objAd;
					$this->objEditSim->SelectAd();
					break;
			}
		}
		
		/**
		 * Create new Ad
		 *
		 * @param string $strFormId
		 * @param string $strControlid
		 * @param AdType $strParameter
		 */
		protected function AddAd($strFormId, $strControlid, $strParameter) {
			if ($objCacheAd = $this->objSeller->CacheAd)
				$objAd = clone $objCacheAd;
			else
				$objAd = new Ad();
				
			$objAd->Seller = $this->objSeller;
			$objAd->Type = $strParameter;
			
			switch ($objAd->Type) {
				case AdType::STD:
					if ($this->objEditSim->Visible)
						$this->objEditSim->CloseAd();
						
					$this->objEditAd->Ad = $objAd;
					$this->objEditAd->EditAd();
					break;
					
				case AdType::SIM:
					if ($this->objEditAd->Visible)
						$this->objEditAd->CloseAd();
						
					$this->objEditSim->Ad = $objAd;
					$this->objEditSim->EditAd();
					break;
			}
		}
		
		/**
		 * Delete selected ad
		 *
		 */
/**		protected function RemoveAd($strFormId, $strControlId, $strParameter) {
			// Short hand object reference
			$objAd = $this->dtgAds->GetObjectFromDataSource('Id', $strParameter);
			if (!$objAd)
				$objAd = $this->dtgSIMs->GetObjectFromDataSource('Id', $strParameter);
			if (!$objAd)
				throw new NoSuchObjectException();
				
			$objAd->Delete();
			
			switch ($objAd->Type) {
				case AdType::SIM:
					$this->dtgSIMs->ForceUpdate();
					break;
					
				case AdType::STD:
					$this->dtgAds->ForceUpdate();
					break; 
			}
			
			// If open, close
			if ($this->objEditAd->Ad && $this->objEditAd->Ad->Id == $objAd->Id)
				$this->objEditAd->CloseAd();
		}*/
		
		
		public function UpdateDTGs($strType) {
			
					$this->dtgSIMs->ForceUpdate();
			$this->dtgSIMs->MarkAsModified();		
					$this->dtgAds->ForceUpdate();
					$this->dtgAds->MarkAsModified();
		}
	}
?>