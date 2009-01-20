<?php
	/**
	 * All news for sellers
	 *
	 */
	class SellersNewsForm extends OqtopusForm {
		protected $objSeller;
		
		protected $lblBids;
		protected $lblNetworkApplications;
		protected $lblDebt;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			$this->objSeller = $this->LoadSeller();
			
			Security::VerifyAccess(Actions::ViewNews, $this->objSeller);
			
			$this->lblBids = new SimpleLabel($this, 'lblBids');
			$this->lblBids->Text = $this->objSeller->CountBidsByStatus(BidStatus::Unanswered);
			
			$this->lblNetworkApplications = new SimpleLabel($this, 'lblNetworkApplications');
			$this->lblNetworkApplications->Text = $this->objSeller->CountNetworkApplicationsByStatus(BidStatus::Unanswered);
			
			$this->lblDebt = new SimpleLabel($this, 'lblDebt');
			$this->lblDebt->Text = $this->objSeller->Debt;
		}
	}
?>