<?php
	/**
	 * All news for buyers
	 *
	 */
	class BuyersNewsForm extends OqtopusForm {
		
		protected $objLogin;
		protected $lblAnsweredBids;
		protected $lblOffers;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			$this->objLogin = $this->LoadLogin();
			Security::VerifyAccess(Actions::ViewNews, $this->objLogin);
			
			$this->lblAnsweredBids = new SimpleLabel($this);
			$this->lblAnsweredBids->Text = count(Bid::LoadArrayForBuyersAnsweredBids($this->objLogin->Id, $this->objLogin->LastLogin, TimeComparisonMode::After));
			
			$this->lblOffers = new SimpleLabel($this);
			$this->lblOffers->Text = count($this->objLogin->GetAvailableOffers());
		}
	}
?>