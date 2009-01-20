<?php
	class NetworkPanel extends QPanel {
		protected $objNetwork;
		protected $blnEditMode = false;
		protected $objCallback;
		
		protected $blnVisible = false;
		
		public $lblName;
		public $lblDescription;
		public $btnEditNetwork;
		public $btnNetworkClose;
		
		public $txtName;
		public $txtDescription;
		public $btnNetworkOk;
		public $btnNetworkCancel;
		public $btnRemove;
		
		public $dtgAssociations;
		
		public function __construct($objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->lblName = new QLabel($this);
			$this->lblName->Name = _tr('Name');
			$this->lblName->CssClass = 'lblName';
				
			$this->lblDescription = new QLabel($this);
			$this->lblDescription->Name = _tr('NetworkDescription');
			$this->lblDescription->CssClass = 'lblDescription';
			
			$this->btnEditNetwork = new QButton($this);
			$this->btnEditNetwork->Text = _tr('Edit');
			$this->btnEditNetwork->CausesValidation = false;
			$this->btnEditNetwork->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'Edit'));
			$this->btnEditNetwork->CssClass = 'btnEditNetwork';
			
			$this->btnNetworkClose = new QButton($this);
			$this->btnNetworkClose->Text = _tr('Close');
			$this->btnNetworkClose->CausesValidation = false;
			$this->btnNetworkClose->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'Close'));
			$this->btnNetworkClose->CssClass = 'btnNetworkClose';
			
			$this->txtName = new QTextBox($this, 'txtNetworkName');
			$this->txtName->Name = $this->lblName->Name;
			$this->txtName->MaxLength = 22;
			
			$this->txtDescription = new MultiLineTextBox($this, 'txtNetworkDescription');
			$this->txtDescription->Name = $this->lblDescription->Name;
			$this->txtDescription->TextMode = QtextMode::MultiLine;
			$this->txtDescription->MaxLength = 400;
			$this->txtDescription->RowLimit = 4;
			$this->txtDescription->CssClass = 'txtDescription';
			
			$this->btnNetworkOk = new QButton($this);
			$this->btnNetworkOk->Text = _tr('Ok');
			$this->btnNetworkOk->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'DoEdit'));
			$this->btnNetworkOk->ActionParameter = UserAnswer::OK;
			$this->btnNetworkOk->CssClass = 'btnNetworkOk';
			
			$this->btnNetworkCancel = new QButton($this);
			$this->btnNetworkCancel->Text = _tr('Cancel');
			$this->btnNetworkCancel->CausesValidation = false;
			$this->btnNetworkCancel->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'DoEdit'));
			$this->btnNetworkCancel->ActionParameter = UserAnswer::Cancel;
			$this->btnNetworkCancel->CssClass = 'btnNetworkCancel';
			
			$dgcName = new QDataGridColumn(_tr('User Company'), '<?= $_ITEM->Login->CompanyName ?>');
			$dgcName->CssClass = 'limited';
			$dgcRemove = new QDataGridColumn(null, '<?=$_CONTROL->ParentControl->RenderRemoveButton($_ITEM) ?>');
			
			$this->dtgAssociations = new QDataGrid($this);
			$this->dtgAssociations->CssClass = 'dtgAssociations';
			$this->dtgAssociations->Name = _tr('Users');
			$this->dtgAssociations->Persistent = true;
			$this->dtgAssociations->AddColumn($dgcName);
			$this->dtgAssociations->AddColumn($dgcRemove);
			$objPag = new QPaginator($this->dtgAssociations);
			$this->dtgAssociations->Paginator = $objPag;
			$this->dtgAssociations->CssClass = 'dtgAssociations';
			
			$this->btnRemove = new QButton($this);
			$this->btnRemove->CausesValidation = false;
			$this->btnRemove->Text = _tr('Remove');
			$this->btnRemove->CssClass = 'btnRemoveAds';
			$this->btnRemove->AddAction(new QClickEvent(), new JSConfirmAction());
			$this->btnRemove->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'Delete'));
		}
		
		public function Close() {
			$this->blnVisible = false;
			$this->blnModified = true;
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Network':
					$this->objNetwork = $mixValue;
					$this->dtgAssociations->ForceUpdate();
					break;
					
				case 'Callback':
					$this->objCallback = $mixValue;
					break;
					
				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		public function __get($strName) {
			switch ($strName) {
				case 'IsEditing':
					return $this->blnEditMode;
					
				case 'Callback':
					return $this->objCallback;
					
				case 'Network':
					return $this->objNetwork;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		public function Select() {
			$this->lblName->Text = $this->objNetwork->Name;
			$this->lblDescription->Text = $this->objNetwork->Description;
			$this->dtgAssociations->ForceUpdate();
			$this->blnVisible = true;
			$this->blnModified = true;
		}
		
		protected function GetControlHtml() {
			$this->Template = sprintf('%s%s.%s.inc', __TEMPLATES__, __CLASS__, $this->blnEditMode ? 'Edit' : 'NonEdit');
			if ($this->objNetwork && $this->dtgAssociations->Update) {
				$objAssExpansionMap[NetworkUser::ExpandLogin] = true;
				$this->dtgAssociations->TotalItemCount = count($this->objNetwork->GetNetworkUserArrayByStatus(BidStatus::Accepted));
				$this->dtgAssociations->DataSource = $this->objNetwork->GetNetworkUserArrayByStatus(BidStatus::Accepted , null, $this->dtgAssociations->LimitInfo, $objAssExpansionMap);
			}
			
			try {
				return parent::GetControlHtml();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
		}
		
		public function Edit() {
			$this->txtDescription->Text = $this->objNetwork->Description;
			$this->txtName->Text = $this->objNetwork->Name;
			
			$this->blnEditMode = true;
			$this->blnVisible = true;
			$this->blnModified = true;
		}
		
		public function DoEdit($strFormId, $strControlId, $strParameter) {
			if ($strParameter == UserAnswer::OK) {
				$this->objNetwork->Name = $this->txtName->Text;
				$this->objNetwork->Description = $this->txtDescription->Text;
				$this->objNetwork->Save();
				
				call_user_func($this->objCallback);
				
				$this->Select();
			} else
				if (!$this->objNetwork->Id) // If the user has cancelled a new ad, there's nothing to show in default view; therefore hide
					$this->blnVisible = false;
			
			$this->blnEditMode = false;
			$this->blnModified = true;
		}
		
		public function RenderRemoveButton(NetworkUser $objNU) {
			$strId = 'btnRemove' . $objNU->Id;
			
			if (!($btnRemove = $this->Form->GetControl($strId))) {
				$btnRemove = new QButton($this->dtgAssociations, $strId);
				$btnRemove->Text = _tr('Remove');
				$btnRemove->CausesValidation = false;
				$btnRemove->AddAction(new QClickEvent(), new JSConfirmAction());
				$btnRemove->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'RemoveLogin'));
				$btnRemove->ActionParameter = $objNU->Id;
				$btnRemove->CssClass = 'btnRemoveFromNetwork';
			}
			
			return $btnRemove->Render(false);
		}
		
		public function RemoveLogin($strFormId, $strControlId, $strParameter) {
			$objNU = $this->dtgAssociations->GetObjectFromDataSource('Id', $strParameter);
			$objNU->Delete();
			
			$this->dtgAssociations->ForceUpdate();
			$this->blnModified = true; 
			
			call_user_func($this->objCallback);
		}
		
		public function Delete() {
			$this->objNetwork->Delete();
			$this->Close();
			call_user_func($this->objCallback);
		}
	}
?>