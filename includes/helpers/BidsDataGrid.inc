<?php
	/**
	 * Sets up some default columns for bids
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class BidsDataGrid extends QDataGrid {
		public function __construct($objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$dgcAd = new QDataGridColumn(_tr('Ad name'), '<?= $_ITEM->GetVirtualAttribute("AdName") ?>');
			$dgcAd->SortByCommand = 'ad.name ASC';
			$dgcAd->ReverseSortByCommand = 'ad.name DESC';
			
			$dgcAmount = new QDataGridColumn(_tr('Amount offered'), '<?= $_ITEM->Amount ?>');
			$dgcAmount->SortByCommand = 'bid.amount ASC';
			$dgcAmount->ReverseSortByCommand = 'bid.amount DESC';
			
			$dgcDiscount = new QDataGridColumn(_tr('Relative discount'), '<?= $_ITEM->Discount ?>%');
			
			//$dgcComments = new QDataGridColumn(_tr('Comments'), '<?= $_ITEM->Comments ? remove space >');
			
			$dgcDeadline = new QDataGridColumn(_tr('Deadline'), '<?= $_ITEM->Deadline && !$_ITEM->Deadline->IsNUll() ? $_ITEM->Deadline->PHPDate(Localization::$DateFormat) : \'-\' ?>');
			$dgcDeadline->SortByCommand = 'bid.deadline ASC';
			$dgcDeadline->ReverseSortByCommand = 'bid.deadline DESC';
			
			$dgcPublicationDate = new QDataGridColumn(_tr('Publication date'), '<?= $_ITEM->PublicationDate && !$_ITEM->PublicationDate->IsNull() ? $_ITEM->PublicationDate->PHPDate(Localization::$DateFormat) : \'-\'?>');
			
			$dgcStatus = new QDataGridColumn(_tr('Status'), '<?= $_CONTROL->GetStatusString($_ITEM->Status) ?>');
			$dgcStatus->SortByCommand = 'bid.status ASC';
			$dgcStatus->ReverseSortByCommand = 'bid.status DESC';
				
			$this->AddColumn($dgcAd);
			$this->AddColumn($dgcAmount);
			$this->AddColumn($dgcDiscount);
			$this->AddColumn($dgcDeadline);
			$this->AddColumn($dgcPublicationDate);
			$this->AddColumn($dgcStatus);
			
			$this->objHeaderRowStyle->CssClass = "BidsDataGrid_HeaderRow";
			$this->objHeaderLinkStyle->CssClass = "BidsDataGrid_HeaderLink";
			$this->objRowStyle->CssClass = "BidsDataGrid_Row";
			$this->objAlternateRowStyle->CssClass = "BidsDataGrid_AlternateRow";		
		}
		
		/**
		 * Fetch describing string for specified bid status
		 *
		 * @param BidStatus $strStatus
		 * @return string
		 */
		protected function GetStatusString($strStatus) {
			switch ($strStatus) {
				case BidStatus::Accepted:
					return _tr('Accepted');
					
				case BidStatus::Denied:
					return _tr('Denied');
					
				case BidStatus::Unanswered:
					return _tr('New');
			}
		}		
	}
?>