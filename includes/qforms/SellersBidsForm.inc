<?php
	/**
	 * See all bids on a sellers ads
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage qforms
	 */
	class SellersBidsForm extends OqtopusForm {
		protected $dtgNewBids;
		protected $objSeller;
		protected $dtgOldBids;
		
		// Former ToContactForm
		protected $pnlContact;
		protected $lbBuyer;
		protected $lblPhone;
		protected $btnRemove;
		protected $btnClose;
		
		// pnlEmail
		protected $pnlEmail;
		protected $txtSubject;
		protected $txtBody;
		protected $btnSend;
		protected $chkRemove;
		protected $lblMail;
		
		protected $objCache;
		protected $objBid;
		
		public function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->objSeller = $this->LoadSeller();

			Security::VerifyAccess(Actions::ManageBids, $this->objSeller);			
			
			$dgcPrice = new QDataGridColumn(_tr('Requested price'), '<?= $_ITEM->GetVirtualAttribute("AdPrice") ?>');
			$dgcProvision = new QDataGridColumn(_tr('Oqtopus provision'), '<?= $_ITEM->Provision ?>');
			$dgcWorthy = new QDataGridColumn(_tr('Credit worthy'), '<?= $_ITEM->Login->Worthy ? _tr("Passed") : _tr("Failed") ?>');
			$dgcAccept = new QDataGridColumn(_tr('Accept?'), '<?= $_FORM->RenderAnswerButton(BidStatus::Accepted, $_ITEM, $_CONTROL) . $_FORM->RenderAnswerButton(BidStatus::Denied, $_ITEM, $_CONTROL); ?>');
			//$dgcDeny = new QDataGridColumn(null, '<?= $_FORM->RenderAnswerButton(BidStatus::Denied, $_ITEM, $_CONTROL) ? >');
					
			$this->dtgNewBids = new BidsDataGrid($this, 'dtgNewBids');
			$this->dtgNewBids->Name = _tr('Unanswered bids');
			$this->dtgNewBids->RemoveColumn(5);
			$this->dtgNewBids->AddColumnAt(1, $dgcPrice);
			$this->dtgNewBids->AddColumnAt(4, $dgcProvision);
			$this->dtgNewBids->AddColumn($dgcWorthy);
			$this->dtgNewBids->RemoveColumn(3);
			
			$this->dtgNewBids->AddColumn($dgcAccept);
			//$this->dtgNewBids->AddColumn($dgcDeny);
			$this->dtgNewBids->Persistent = true;
			
			$dgcContacted = new QDataGridColumn(null,'<?= $_ITEM->Status == BidStatus::Accepted && $_ITEM->ContactedBuyer == 0 ? $_FORM->RenderContactButton($_ITEM, $_CONTROL) : "-" ?>');
			
			$dgcBuyer = new QDataGridColumn(_tr('Buyer'), '<?= $_ITEM->GetVirtualAttribute("BuyerName") ?>');
			
			$dgcAnswerComments = new QDataGridColumn(_tr('Answer comments'), '<?= $_ITEM->StatusComment ?>');
			
			$dgcAnswerTimestamp = new QDataGridColumn(_tr('Answered'), '<?= $_ITEM->AnswerTimestamp->PHPDate(Localization::$DateFormat); ?>');
			$dgcAnswerTimestamp->SortByCommand = 'answer_timestamp ASC';
			$dgcAnswerTimestamp->ReverseSortByCommand = 'answer_timestamp DESC';
			
			$this->dtgOldBids = new BidsDataGrid($this, 'dtgOldBids');
			$this->dtgOldBids->Name = _tr('Answered bids');
			$this->dtgOldBids->RemoveColumn(3);
			$this->dtgOldBids->RemoveColumn(2);
			$this->dtgOldBids->AddColumnAt(3, $dgcBuyer);
			$this->dtgOldBids->AddColumn($dgcAnswerTimestamp);
			$this->dtgOldBids->AddColumn($dgcContacted);
			$this->dtgOldBids->Persistent = true;
			$this->dtgOldBids->SortColumnIndex = 5;
			$this->dtgOldBids->SortDirection = 1;
			
			$this->objCache = new ObjectCache();
			
			// Former ToContactForm:
			$this->pnlContact = new QPanel($this);
			$this->pnlContact->Template = sprintf('%s%s.pnlContact.inc', __TEMPLATES__, __CLASS__);
			$this->pnlContact->Visible = false;
			
			$this->lblPhone = new QLabel($this->pnlContact, 'lblPhone');
			$this->lblPhone->Name = _tr('Call');
			
			$this->btnRemove = new QButton($this->pnlContact, 'btnMarkAsContacted');
			$this->btnRemove->Text = _tr('Mark as contacted');
			$this->btnRemove->AddAction(new QClickEvent(), new QAjaxAction('MarkContacted'));
			$this->btnRemove->CausesValidation = false;
			
			$this->pnlEmail = new QPanel($this->pnlContact, 'pnlEmail');
			$this->pnlEmail->Template = sprintf('%s%s.pnlEmail.inc', __TEMPLATES__, __CLASS__);
			
			$this->txtSubject = new QTextBox($this->pnlEmail, 'txtSubject');
			$this->txtSubject->Name = _tr('Subject');
			
			$this->txtBody = new QTextBox($this->pnlEmail, 'txtBody');
			$this->txtBody->Name = _tr('Body');
			$this->txtBody->TextMode = QTextMode::MultiLine;
			
			$this->btnSend = new QButton($this->pnlContact, 'btnSend');
			$this->btnSend->Text = _tr('Send');
			$this->btnSend->AddAction(new QClickEvent(), new QAjaxAction('Send'));
			
			$this->btnClose = new QButton($this->pnlContact, 'btnClose');
			$this->btnClose->Text = _tr('Cancel');
			$this->btnClose->AddAction(new QClickEvent(), new QAjaxAction('Close'));
			$this->btnClose->CausesValidation = false;
			
			$this->lblMail = new QLabel($this->pnlEmail, 'lblMail');
		}
		
		public function Form_PreRender() {
			$objExp[Bid::ExpandLogin] = true;
			if ($this->dtgNewBids->Update)
				$this->dtgNewBids->DataSource = Bid::LoadArrayForSellersNewBids($this->objSeller->Id, $this->dtgNewBids->SortInfo, null, $objExp);
				
			if ($this->dtgOldBids->Update)
				$this->dtgOldBids->DataSource = Bid::LoadArrayForSellersOldBids($this->objSeller->Id, $this->dtgOldBids->SortInfo);
		}
		
		/**
		 * Render the answer button
		 *
		 * @param UserAnswer $intAnswer
		 * @param Bid $objBid
		 * @param QBaseClass $objParent
		 * @return string
		 */
		public function RenderAnswerButton($intAnswer, Bid $objBid, QBaseClass $objParent) {
			$strId = 'AnswerButton' . $intAnswer . $objBid->Id;
			
			$btn = null;
			if (!($btn = $this->GetControl($strId))) {
				$btn = new QButton($objParent, $strId);
				$btn->Text = $this->GetButtonStringForAnswer($intAnswer);
				$btn->CausesValidation = false;
				$btn->AddAction(new QClickEvent(), new JSConfirmAction());
				$btn->AddAction(new QClickEvent(), new QAjaxAction('DoAnswer'));
				$btn->ActionParameter = $intAnswer . "|" . $this->objCache->StoreObject($objBid);
				$btn->CssClass = 'btnSellersBidsForm';
			}
			$btn->Enabled = !$this->pnlContact->Visible;
			
			$str = $btn->Render(false);
			
			return $str;
		}
		
		/**
		 * Get text for button depending on action
		 *
		 * @param UserAnswer $intAnswer
		 * @return string
		 */
		protected function GetButtonStringForAnswer($intAnswer) {
			switch ($intAnswer) {
				case BidStatus::Denied:
					return _tr('No');
					
				case BidStatus::Accepted:
					return _tr('Yes');
			}
		}
		
		/**
		 * Answer a bid
		 *
		 * @param string $strFormId
		 * @param string $strControlId
		 * @param UserAnswer $strParameter
		 */
		protected function DoAnswer($strFormId, $strControlId, $strParameter) {
			$strTemp = explode('|', $strParameter);
			$intAnswer = $strTemp[0];
			$objBid = $this->objCache->getObject((int)$strTemp[1]);
	
			$objBid->Status = $intAnswer;
				
			$objBid->AnswerTimestamp = new QDateTime(QDateTime::Now);
			$objBid->Save();
			
			$this->dtgNewBids->ForceUpdate();
			$this->dtgOldBids->ForceUpdate();
		}
		
		protected function MarkContacted() {
			$objBid = $this->objBid;
			$objBid->ContactedBuyer = 1;
			$objBid->Save();
			$this->dtgOldBids->ForceUpdate();
			$this->dtgNewBids->MarkAsModified();
			$this->pnlContact->Visible = false;
		}
		
		protected function Send() {
			$objBid = $this->objBid;
			Mail::SendMail($objBid->Login, Security::Current(), $this->txtSubject->Text, $this->txtBody->Text);
				$this->MarkContacted();
				
			$this->txtBody->Text = '';
			$this->txtSubject->Text = '';
		}		
		
		public function RenderContactButton(Bid $objBid, QControl $objParent) {
			$id = 'btnContact' . $objBid->Id;
			
			if (!($btnContact = $this->GetControl($id))) {
				$btnContact = new QButton($objParent, $id);
				$btnContact->CausesValidation = false;
				$btnContact->Text = _tr('Contact buyer');
				$btnContact->AddAction(new QClickEvent(), new QAjaxAction('ContactBuyer'));
				$btnContact->ActionParameter = $objBid->Id;
			}
			
			$btnContact->Enabled = !$this->pnlContact->Visible;
			
			return $btnContact->Render(false);
		}
		
		protected function ContactBuyer($strFormId, $strControlId, $strParameter) {
			$this->objBid = $this->dtgOldBids->GetObjectFromDataSource('Id', $strParameter);
			$this->txtSubject->Text = sprintf(_tr('The bid on $%d for ad %s from seller %s'), $this->objBid->Amount, $this->objBid->Ad->Name, $this->objSeller->SellerName);
			$this->lblPhone->Text = $this->objBid->Login->Phone;
			$this->pnlContact->Visible = true;
			$this->dtgNewBids->MarkAsModified();
			$this->dtgOldBids->MarkAsModified();
		}
		
		protected function Close() {
			$this->pnlContact->Visible = false;
			$this->dtgNewBids->MarkAsModified();
			$this->dtgOldBids->MarkAsModified();
		}
	}
?>