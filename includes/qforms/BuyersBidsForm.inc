<?php
	/**
	 * A form where a buyer can see all bids he've made
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage qforms
	 */
	class BuyersBidsForm extends OqtopusForm {
		protected $dtgNewBids;
		protected $dtgOldBids;
		protected $dtgPendingBids;
		protected $dtgExpiredBids;
		
		protected $objLogin;
		
		public function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			if (isset($_GET['arg1']))
				$this->objLogin = Login::Load($_GET['arg1']);
			else
				$this->objLogin = Security::Current();
				
			if (!$this->objLogin)
				throw new NoSuchObjectException();
				
			Security::VerifyAccess(Actions::ManageBids, $this->objLogin);								
				
			$dgcAnswerComments = new QDataGridColumn(_tr('Answer comments'), '<?= $_ITEM->StatusComment ?>');
			
			$dgcSeller = new QDataGridColumn(_tr('Seller name'), '<a href="<?= Navigation::CreateUrl("ProfileForm", $_ITEM->GetVirtualAttribute("SellerId")) ?>"><?= $_ITEM->GetVirtualAttribute("SellerName") ?></a>');
			
			$this->dtgNewBids = new BidsDataGrid($this, 'dtgNewBids');
			$this->dtgNewBids->RemoveColumn(3);
			$this->dtgNewBids->RemoveColumn(2);			
			$this->dtgNewBids->AddColumnAt(0, $dgcSeller);
			$this->dtgNewBids->Name = _tr('Bids answered since last login');
			$this->dtgNewBids->Persistent = true;
			$this->dtgNewBids->CssClass='middle';
			
			$this->dtgOldBids = new BidsDataGrid($this, 'dtgOldBids');
			$this->dtgOldBids->RemoveColumn(3);
			$this->dtgOldBids->RemoveColumn(2);
			$this->dtgOldBids->AddColumnAt(0, clone $dgcSeller);			
			$this->dtgOldBids->Name = _tr('Bids answered in the past');
			$this->dtgOldBids->Persistent = true;
			$this->dtgOldBids->CssClass='middle';
			
			$this->dtgPendingBids = new BidsDataGrid($this, 'dtgPendingBids');
			$this->dtgPendingBids->RemoveColumn(5);
			$this->dtgPendingBids->RemoveColumn(2);
			$this->dtgPendingBids->AddColumnAt(0, clone $dgcSeller);
			$this->dtgPendingBids->Name = _tr('Pending bids');
			$this->dtgPendingBids->Persistent = true;
			$this->dtgPendingBids->CssClass='middle';
			
			$this->dtgExpiredBids = new BidsDataGrid($this, 'dtgExpiredBids');
			$this->dtgExpiredBids->RemoveColumn(5);			
			//$this->dtgExpiredBids->RemoveColumn(4);
			$this->dtgExpiredBids->RemoveColumn(2);
			$this->dtgExpiredBids->AddColumnAt(0, clone $dgcSeller);
			$this->dtgExpiredBids->Name = _tr('Expired bids');
			$this->dtgExpiredBids->Persistent = true;
			$this->dtgExpiredBids->CssClass='middle';
		}
		
		public function Form_PreRender() {
			if ($this->dtgNewBids->Update)
				$this->dtgNewBids->DataSource = Bid::LoadArrayForBuyersAnsweredBids($this->objLogin->Id, Security::Current() ? Security::Current()->LastLogin : new QDateTime(QDateTime::Now), TimeComparisonMode::After, $this->dtgNewBids->SortInfo);
				
			if ($this->dtgOldBids->Update)
				$this->dtgOldBids->DataSource = Bid::LoadArrayForBuyersAnsweredBids($this->objLogin->Id, Security::Current() ? Security::Current()->LastLogin : new QDateTime(QDateTime::Now), TimeComparisonMode::Before, $this->dtgOldBids->SortInfo);
				
			if ($this->dtgPendingBids->Update)
				$this->dtgPendingBids->DataSource = Bid::LoadArrayForBuyersPendingBids($this->objLogin->Id, TimeComparisonMode::After, $this->dtgPendingBids->SortInfo);
				
			if ($this->dtgExpiredBids->Update)
				$this->dtgExpiredBids->DataSource = Bid::LoadArrayForBuyersPendingBids($this->objLogin->Id, TimeComparisonMode::Before, $this->dtgExpiredBids->SortInfo);
		}
	}
?>