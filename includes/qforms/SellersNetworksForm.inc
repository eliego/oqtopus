<?php
	/**
	 * Seller can add new networks, see current networks, associated buyers and accept new applications
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage qforms
	 */
	class SellersNetworksForm extends OqtopusForm {
		protected $dtgNetworks;
		protected $btnAdd;
		protected $dtgApplications;
		protected $objNetworkPanel;
		protected $objSeller;
		public $intSelected;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}	
			$this->objSeller = $this->LoadSeller();
			
			Security::VerifyAccess(Actions::ManageNetworks, $this->objSeller);

			$dgcName = new QDataGridColumn(_tr('Network'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_FORM->RenderSelect($_ITEM)) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
			$dgcName->SortByCommand = 'network.name ASC';
			$dgcName->ReverseSortByCommand = 'network.name DESC';
			
			$dgcMemberCount = new QDataGridColumn(_tr('Member count'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->GetVirtualAttribute("MemberCount")) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
			$dgcMemberCount->SortByCommand = '__MemberCount ASC';
			$dgcMemberCount->ReverseSortByCommand = '__MemberCount DESC';
			
			$dgcSimCount = new QDataGridColumn(_tr('Offer count'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->GetVirtualAttribute("SimCount")) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
			
			$dgcBidAmount = new QDataGridColumn(_tr('Sum of all bids'), '<?= ($_FORM->intSelected == $_ITEM->Id ? "<b>" : "") . ($_ITEM->GetVirtualAttribute("BidAmount")) . ($_FORM->intSelected == $_ITEM->Id ? "</b>" : "") ?>');
			
			//$dgcSelectRemove = new QDataGridColumn(null, '<?= $_FORM->RenderRemove($_ITEM) ? >');
			
			
			
			$this->dtgNetworks = new QDataGrid($this, 'dtgNetworks');
			$this->dtgNetworks->Name = _tr('Campaign networks');
			$this->dtgNetworks->UseAjax = true;
			$this->dtgNetworks->Persistent = true;
			$this->dtgNetworks->AddColumn($dgcName);
			$this->dtgNetworks->AddColumn($dgcMemberCount);
			$this->dtgNetworks->AddColumn($dgcSimCount);
			$this->dtgNetworks->AddColumn($dgcBidAmount);
			//$this->dtgNetworks->AddColumn($dgcSelectRemove);
			
			$dgcAppName = new QDataGridColumn(_tr('Company name'), '<?= $_ITEM->Login->CompanyName ?>');
			$dgcLocation = new QDataGridColumn(_tr('Location'), '<?= $_ITEM->Login->City ?>');
			$dgcAcceptDeny = new QDataGridColumn(_tr('Accept?'), '<?= $_FORM->RenderAcceptDenyButtons($_ITEM) ?>');
			$dgcNetwork = new QDataGridColumn(_tr('Network name'), '<?= $_ITEM->Network->Name ?>');
			
			$this->dtgApplications = new QDataGrid($this, 'dtgApplications');
			$this->dtgApplications->Name = _tr('Applications');
			$this->dtgApplications->Persistent = true;
			$this->dtgApplications->AddColumn($dgcAppName);
			$this->dtgApplications->AddColumn($dgcLocation);
			$this->dtgApplications->AddColumn($dgcNetwork);
			$this->dtgApplications->AddColumn($dgcAcceptDeny);			
			
			$this->objNetworkPanel = new NetworkPanel($this, 'objNetworkPanel');
			$this->objNetworkPanel->Callback = array($this, 'CallbackFromNetworkPanel');
			
			$this->btnAdd = new QButton($this, 'btnAdd');
			$this->btnAdd->Text = _tr('New campain');
			$this->btnAdd->CausesValidation = false;
			$this->btnAdd->AddAction(new QClickEvent(), new QAjaxAction('Add'));
			$this->btnAdd->CssClass = 'btnAdd';
		}
		
		protected function Add() {
			$objNetwork = new Network();
			$objNetwork->Seller = $this->objSeller;
			$this->objNetworkPanel->Network = $objNetwork;
			$this->objNetworkPanel->Edit();
		}
		
		
		
		public function RenderAcceptDenyButtons(NetworkUser $objNU) {
			$strAId = 'btnAccept' .$objNU->Id;
			$strDId = 'btnDeny' .$objNU->Id;
			
			if (!(($btnA = $this->GetControl($strAId)) && ($btnD = $this->GetControl($strDId)))) {
				$btnA = new QButton($this->dtgApplications, $strAId);
				$btnA->Text = _tr('Yes');
				$btnA->CausesValidation = false;
				$btnA->AddAction(new QClickEvent(), new JSConfirmAction());
				$btnA->AddAction(new QClickEvent(), new QAjaxAction('AcceptLogin'));
				$btnA->ActionParameter = $objNU->Id;
				$btnA->CssClass = 'btnAccept';

				$btnD = new QButton($this->dtgApplications, $strDId);
				$btnD->Text = _tr('No');
				$btnD->CausesValidation = false;
				$btnD->AddAction(new QClickEvent(), new JSConfirmAction());
				$btnD->AddAction(new QClickEvent(), new QAjaxAction('RemoveLogin'));
				$btnD->ActionParameter = $objNU->Id;
				$btnD->CssClass = 'btnDeny';
			}
			
			return sprintf('%s%s', $btnA->Render(false), $btnD->Render(false));
		}	
		
		/*public function RenderRemove(Network $objNetwork) {
			$strIdR = 'btnRemoveNetwork'.$objNetwork->Id;

			if (!(($btnRemove = $this->GetControl($strIdR)))) {
				$btnRemove = new QButton($this->dtgNetworks, $strIdR);
				$btnRemove->Text = _tr('Determinate');
				$btnRemove->CausesValidation = false;
				$btnRemove->AddAction(new QClickEvent(), new JSConfirmAction());
				$btnRemove->AddAction(new QClickEvent(), new QAjaxAction('Remove'));
				$btnRemove->ActionParameter = $objNetwork->Id;
				$btnRemove->CssClass = 'btnRemove';
			}
			
			$btnRemove->Enabled = !$this->objNetworkPanel->IsEditing;

			return $btnRemove->Render(false);
		}*/
		
		public function RenderSelect(Network $objNetwork) {
			$strIdS = 'btnSelect'.$objNetwork->Id;

			if (!(($btnSelect = $this->GetControl($strIdS)))) {
				$btnSelect = new LinkButton($this->dtgNetworks, $strIdS);
				$btnSelect->Text = $objNetwork->Name;
				$btnSelect->CausesValidation = false;
				$btnSelect->AddAction(new QClickEvent(), new QAjaxAction('Select'));
				$btnSelect->ActionParameter = $objNetwork->Id;
				//$btnSelect->CssClass = 'btnSelect';
			}

			return $btnSelect->Render(false);
		}		
		
		protected function Form_PreRender() {
			$this->btnAdd->Enabled = !$this->objNetworkPanel->IsEditing;
			$objAppExpansionMap[NetworkUser::ExpandLogin] = true;
			$objAppExpansionMap[NetworkUser::ExpandNetwork] = true;
				
			if ($this->dtgApplications->Update)
				$this->dtgApplications->DataSource = $this->objSeller->GetApplicationArray(null, null, $objAppExpansionMap);

			if ($this->dtgNetworks->Update)		
				$this->dtgNetworks->DataSource = $this->objSeller->GetNetworkArrayWithMemberCount($this->dtgNetworks->SortInfo);		
				
			$this->dtgNetworks->MarkAsModified();
		}
		
		protected function AcceptLogin($strFormId, $strControlId, $strParameter) {
			$objNU = $this->dtgApplications->GetObjectFromDataSource('Id', $strParameter);
			$objNU->Status = BidStatus::Accepted;
			$objNU->Save();
			
			$this->dtgApplications->ForceUpdate();
			$this->dtgNetworks->ForceUpdate();
			
			// If we've selected that particular network, we have to update the memberdtg as well
			if ($this->objNetworkPanel->Network && $this->objNetworkPanel->Network->Id == $objNU->NetworkId && $this->objNetworkPanel->Visible)
				$this->objNetworkPanel->Select();
		}
		
		protected function RemoveLogin($strFormId, $strControlId, $strParameter) {
			$objNU = $this->dtgApplications->GetObjectFromDataSource('Id', $strParameter);
			$objNU->Delete();
			
			$this->dtgApplications->ForceUpdate();
		}
		
		protected function Select($strFormId, $strControlId, $strParameter) {
			$objNetwork = $this->dtgNetworks->GetObjectFromDataSource('Id', $strParameter);
			$this->objNetworkPanel->DoEdit(null, null, UserAnswer::Cancel);
			$this->objNetworkPanel->Network = $objNetwork;
			$this->objNetworkPanel->Select();
			$this->intSelected = $objNetwork->Id;
		}
		
		public function CallbackFromNetworkPanel() {
			$this->dtgNetworks->ForceUpdate();
			$this->dtgApplications->ForceUpdate();
			$this->dtgNetworks->MarkAsModified();
			$this->dtgApplications->MarkAsModified();
		}
		
		/*protected function Remove($strFormId, $strControlId, $strParameter) {
			$objNetwork = $this->dtgNetworks->GetObjectFromDataSource('Id', $strParameter);
			$objNetwork->Delete();
			
			$this->dtgApplications->ForceUpdate();
			$this->dtgNetworks->ForceUpdate(); 
			if ($this->objNetworkPanel->Network && $this->objNetworkPanel->Network->Id == $objNetwork->Id)
				$this->objNetworkPanel->Visible = false;
		}*/
	}
?>