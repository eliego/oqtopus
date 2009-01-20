<?php
	/**
	 * Buyer can manage his networks
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage qforms
	 */
	class BuyersNetworksForm extends OqtopusForm {
		protected $dtgAssociations;
		protected $dtgData;
		protected $objLogin;
		protected $objCache;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			$this->objLogin = $this->LoadLogin();
			
			Security::VerifyAccess(Actions::ManageNetworks, $this->objLogin);
			
			$this->objCache = new ObjectCache();
			
			$dgcSellerName = new QDataGridColumn(_tr('Sellers name'), '<?= $_ITEM->GetVirtualAttribute("SellerName") ?>');
			$dgcNetworkName = new QDataGridColumn(_tr('Networks name'), '<?= $_ITEM->GetVirtualAttribute("NetworkName") ?>');
			$dgcRemove = new QDataGridColumn('', '<?= $_FORM->RenderRemoveButton($_ITEM) ?>');
			
			$this->dtgAssociations = new QDataGrid($this, 'dtgAssociations');
			$this->dtgAssociations->AddColumn($dgcSellerName);
			$this->dtgAssociations->AddColumn($dgcNetworkName);
			$this->dtgAssociations->AddColumn($dgcRemove);
			$this->dtgAssociations->Persistent = true;
			
			$dgcMediaType = new QDataGridColumn(_tr('Medium'), '<?= MediaType::$MediaType[$_ITEM->MediaType] ?>');
			$dgcMediaType->SortByCommand = 'media_type';
		
			$dgcName = new QDataGridColumn(_tr('Ad name'), '<?= $_ITEM->Name ?>');
			$dgcName->SortByCommand = 'name ASC';
			$dgcName->ReverseSortByCommand = 'name DESC';
		
			$dgcReach = new QDataGridColumn(_tr('Reach'), '<?= $_ITEM->Reach ?>');
			$dgcReach->SortByCommand = 'reach ASC';
			$dgcReach->ReverseSortByCommand = 'reach DESC';
		
			$dgcPrice = new QDataGridColumn(_tr('Requested price'), '<?= $_ITEM->Price ?>');
			$dgcPrice->SortByCommand = 'price ASC';
			$dgcPrice->ReverseSortByCommand = 'price DESC';
		
			$dgcArea = new QDataGridColumn(_tr('Area'), '<?= Areas::$Areas[$_ITEM->Area] ?>');
			$dgcArea->SortByCommand = 'area';
		
			$dgcEndDate = new QDataGridColumn(_tr('Publication date'), '<?= $_ITEM->PublicationDate && !$_ITEM->PublicationDate->IsNull() ? $_ITEM->PublicationDate->PHPDate(Localization::$DateFormat) : "-"?>');
			$dgcEndDate->SortByCommand = 'publication_date ASC';
			$dgcEndDate->ReverseSortByCommand = 'publication_date DESC';
			
			$dgcDeadline = new QDataGridColumn(_tr('Deadline'), '<?= $_ITEM->Deadline ? ($_ITEM->IsExpired() ? sprintf("<span class=\"ExpiredAd\">%s</span>", Localization::FormatTimestamp($_ITEM->Deadline)) : Localization::FormatTimestamp($_ITEM->Deadline)) : "-"?>');
			$dgcDeadline->SortByCommand = 'deadline ASC';
			$dgcDeadline->ReverseSortByCommand = 'deadline DESC';			
		
			$dgcSeller = new QDataGridColumn(_tr('Sellers name'), '<?= sprintf(\'<a href="%s">%s</a>\', Navigation::CreateURL("ProfileForm", $_ITEM->SellerId, $_ITEM->Id), $_ITEM->Seller->SellerName) ?>');
			
			$this->dtgData = new QDataGrid($this);
			$this->dtgData->AddColumn($dgcSeller);
			$this->dtgData->AddColumn($dgcName);			
			$this->dtgData->AddColumn($dgcMediaType);
			$this->dtgData->AddColumn($dgcReach);
			$this->dtgData->AddColumn($dgcPrice);
			$this->dtgData->AddColumn($dgcArea);
			$this->dtgData->AddColumn($dgcEndDate);
			$this->dtgData->AddColumn($dgcDeadline);
			$this->dtgData->Persistent = true;
		}
		
		protected function Form_PreRender() {
			if ($this->dtgAssociations->Update)
				$this->dtgAssociations->DataSource = $this->objLogin->GetNetworkUserArrayWithSellerNameAndNetworkName('__SellerName, __NetworkName');
			
			if ($this->dtgData->Update)
				$this->dtgData->DataSource = $this->objLogin->GetAvailableOffers($this->dtgData->SortInfo);
		}
		
		public function RenderRemoveButton(NetworkUser $objNU) {
			$strId = $objNU->Id . 'btnRemove';
			
			if (!($btnRemove = $this->GetControl($strId))) {
				$btnRemove = new QButton($this->dtgAssociations, $strId);
				$btnRemove->Text = _tr('Delete');
				$btnRemove->CssClass = 'btnBuyersRemoveNetwork';
				$btnRemove->CausesValidation = false;
				$btnRemove->AddAction(new QClickEvent(), new JSConfirmAction());
				$btnRemove->AddAction(new QClickEvent(), new QAjaxAction('Remove'));
				$btnRemove->ActionParameter = $this->objCache->storeObject($objNU);
			}
			
			return $btnRemove->Render(false);
		}
		
		protected function Remove($strFormId, $strControlId, $strParameter) {
			$objNU = $this->objCache->getObject($strParameter);
			$objNU->Delete();
			$this->dtgAssociations->ForceUpdate();
			$this->dtgData->ForceUpdate();
		}
	}
?>
