<?php
	/**
	 * This is actually sort of a wrapper class for QPanel, defaulting to having labels and stuff defined, for showing info about a specified Ad
	 * 
	 * Automatically adjusts if the ad's a SIM or STD'
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class AdPanel extends QPanel { // Shitty template engine requires all controls to be declared public
		public $lblAdName;
		public $lblAdType;
		public $lblAdPrice;
		public $lblAdReach;
		public $pnlAdDesc;
		public $lblAdArea;
		public $lblAdAges;
		public $lblAdSex;
		public $pnlAdSectors;
		public $pnlAdSalaries;
		public $pnlAdEducations;
		public $lblAdDeadline;
		public $lblAdPublication;
		public $pnlAdKeywords;
		public $lblBidInfo;
		public $btnMakeBid;
		public $btnAdClose;
		
		// pnlMakeBid
		public $pnlMakeBid;
		public $txtBidAmount;
		public $dtpBidDeadline;
		public $dtpBidPublicationDate;
		public $btnBidOk;
		public $btnBidCancel;
		public $txtBidTax;
		public $txtBidTotal;
		public $lblName;
		public $lblPrice;
		
		
		protected $objAd;
				
		public function __construct($objParent, $strControlId = null) {
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			// Set up everything..
				$this->Visible = false;
				$this->Template = sprintf('%s%s.inc', __TEMPLATES__, __CLASS__);									
				
				$this->lblAdName = new QLabel($this);
				$this->lblAdName->Name = _tr('Name');		
				$this->lblAdName->CssClass = 'lblAdName';
								
				$this->lblAdType = new QLabel($this);
				$this->lblAdType->Name = _tr('Type');
				$this->lblAdType->CssClass = 'lblAdType';
				
				$this->lblAdPrice = new QLabel($this);
				$this->lblAdPrice->Name = _tr('Requested price');
				$this->lblAdPrice->CssClass = 'lblAdPrice';
				
				$this->lblAdReach = new QLabel($this);
				$this->lblAdReach->Name = _tr('Reach');
				$this->lblAdReach->CssClass = 'lblAdReach';
					
				$this->pnlAdEducations = new QPanel($this);
				$this->pnlAdEducations->AllowHtml = true;
				$this->pnlAdEducations->Name = _tr('Target education level');
				$this->pnlAdEducations->AutoRenderChildren = true;
				$this->pnlAdEducations->CssClass = 'pnlAdEducations';
				
				$this->pnlAdSalaries = new QPanel($this);
				$this->pnlAdSalaries->AllowHtml = true;
				$this->pnlAdSalaries->Name = _tr('Target salary');
				$this->pnlAdSalaries->AutoRenderChildren = true;
				$this->pnlAdSalaries->CssClass = 'pnlAdSalaries';
				
				$this->pnlAdSectors = new QLabel($this);
				$this->pnlAdSectors->AllowHtml = true;
				$this->pnlAdSectors->Name = _tr('Target proffission');
				$this->pnlAdSectors->AutoRenderChildren = true;
				$this->pnlAdSectors->CssClass = 'pnlAdSectors';
				
				$this->pnlAdDesc = new QLabel($this);
				$this->pnlAdDesc->Name = _tr('Description');
				$this->pnlAdDesc->CssClass = 'pnlAdDesc';
			
				$this->lblAdArea = new QLabel($this);
				$this->lblAdArea->Name = _tr('Area');
				$this->lblAdArea->CssClass = 'lblAdArea';
				
				$this->lblAdAges = new QLabel($this);
				$this->lblAdAges->Name = _tr('Target ages');
				$this->lblAdAges->CssClass = 'lblAdAges';
					
				$this->lblAdSex = new QLabel($this);	
				$this->lblAdSex->Name = _tr('Target sex');
				$this->lblAdSex->CssClass = 'lblAdSex';
				
				$this->lblAdDeadline = new QLabel($this);
				$this->lblAdDeadline->Name = _tr('Deadline for ad');
				$this->lblAdDeadline->CssClass = 'lblAdDeadline';
				
				$this->lblAdPublication = new QLabel($this);
				$this->lblAdPublication->Name = _tr('Publication date');
				$this->lblAdPublication->CssClass = 'lblAdDeadline';
				
				$this->pnlAdKeywords = new QPanel($this);
				$this->pnlAdKeywords->Name = _tr('ActualKeywords');
				$this->pnlAdKeywords->CssClass = 'pnlAdKeywords';
				
				$this->btnMakeBid = new QButton($this);
				$this->btnMakeBid->Text = _tr('Place a bid');
				$this->btnMakeBid->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'MakeBid'));
				$this->btnMakeBid->CausesValidation = false;
				$this->btnMakeBid->CssClass = 'btnMakeBid';
				
				$this->btnAdClose = new QButton($this);
				$this->btnAdClose->Text = _tr('Cancel');
				$this->btnAdClose->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'CloseAd'));
				$this->btnAdClose->CausesValidation = false;			
				$this->btnAdClose->CssClass = 'btnAdClose';
				
				// Initialize pnlMakeBid
				$this->pnlMakeBid = new QPanel($this);
				$this->pnlMakeBid->Visible = false;	
				$this->pnlMakeBid->CssClass = 'pnlMakeBid';		
				$this->pnlMakeBid->Template = sprintf('%s%s.pnlMakeBid.inc', __TEMPLATES__, __CLASS__);		

								
				$this->lblBidInfo = new QLabel($this->pnlMakeBid);
				$this->lblBidInfo->CssClass = 'lblBidInfo';
				
				$this->txtBidAmount = new QIntegerTextBox($this->pnlMakeBid);
				$this->txtBidAmount->Name = _tr('Amount');
				$this->txtBidAmount->CssClass = 'txtBidAmount';
				$this->txtBidAmount->AddAction(new QKeyUpEvent(400), new QAjaxControlAction($this, 'UpdateTax'));
				
				$this->dtpBidDeadline = new QDateTimePicker($this->pnlMakeBid);
				$this->dtpBidDeadline->DateTimePickerFormat = QDateTimePickerFormat::YearMonthDay;
				$this->dtpBidDeadline->Name = _tr('Deadline');
				$this->dtpBidDeadline->Required = false;
				$this->dtpBidDeadline->CssClass = 'dtpBidDeadline';
				
				$this->dtpBidPublicationDate = new QDateTimePicker($this->pnlMakeBid);
				$this->dtpBidPublicationDate->DateTimePickerFormat = QDateTimePickerFormat::YearMonthDay;
				$this->dtpBidPublicationDate->Required = false;
				$this->dtpBidPublicationDate->Name = _tr('Publication date');
				$this->dtpBidPublicationDate->CssClass = 'dtpBidDeadline';
				
				$this->btnBidCancel = new QButton($this->pnlMakeBid);
				$this->btnBidCancel->Text = _tr('Cancel');
				$this->btnBidCancel->CausesValidation = false;
				$this->btnBidCancel->AddAction(new QClickEvent(), $objBidAction = new QAjaxControlAction($this, 'DoMakeBid'));
				$this->btnBidCancel->ActionParameter = UserAnswer::Cancel;
				$this->btnBidCancel->CssClass = 'btnBidCancel';
				
				$this->btnBidOk = new QButton($this->pnlMakeBid);
				$this->btnBidOk->Text = _tr('Offer');
				$this->btnBidOk->PrimaryButton = true;
				$this->btnBidOk->AddAction(new QClickEvent(), $objBidAction);
				$this->btnBidOk->ActionParameter = UserAnswer::OK;
				$this->btnBidOk->CausesValidation = false;			
				$this->btnBidOk->CssClass = 'btnBidOk';
				
				$this->lblName = new QLabel($this->pnlMakeBid);
				$this->lblPrice = new QLabel($this->pnlMakeBid);
				
				$this->txtBidTax = new QLabel($this->pnlMakeBid);
				$this->txtBidTax->Enabled = false;
				$this->txtBidTax->Text = '0';
				//$this->txtBidTax->Width = 10;
				
				$this->txtBidTotal = new QLabel($this->pnlMakeBid);
				$this->txtBidTotal->Enabled = false;
				$this->txtBidTotal->Text = '0';
				//$his->txtBidTotal->Width = 10;
		}
		
		/**
		 * Actually select an ad -  place ad data in the same
		 *
		 */
		public function SelectAd() {
			$objAd = $this->objAd;
			
			// Unhide
			$this->Visible = true;
			
			// Set up name
			$this->lblAdName->Text = $objAd->Name;

			// Set up Mediatype
			if ($objAd->MediaSubType)
				$this->lblAdType->Text = sprintf('%s -> %s', MediaType::$MediaType[$objAd->MediaType], MediaType::$MediaSubType[$objAd->MediaType][$objAd->MediaSubType]);
			else 
				$this->lblAdType->Text = sprintf('%s', MediaType::$MediaType[$objAd->MediaType]);
			
			// Set up Price, Reach, Description and Area
			$this->lblAdPrice->Text = $objAd->Price;
			$this->lblAdReach->Text = $objAd->Reach;
			$this->pnlAdDesc->Text = $objAd->Description;
			$this->lblAdArea->Text = sprintf('%s', Areas::$Areas[$objAd->Area]);
			if ($objAd->SubArea)
				$this->lblAdArea->Text .= sprintf(', %s', Areas::$SubAreas[$objAd->Area][$objAd->SubArea]);
			if ($objAd->SubSubArea)
				$this->lblAdArea->Text .= sprintf(', %s', Areas::$SubSubAreas[$objAd->Area][$objAd->SubArea][$objAd->SubSubArea]);
				
			// Set up salaries, sectors, educations
			$this->pnlAdSalaries->Text = BitmaskComposite::GetHtmlList($objAd->Salaries, Salary::$Salary);
			$this->pnlAdSectors->Text = BitmaskComposite::GetHtmlList($objAd->Sectors, Sector::$Sector);
			$this->pnlAdEducations->Text = BitmaskComposite::GetHtmlList($objAd->Educations, Education::$Education);
			
			if ($objAd->StartAge && $objAd->EndAge)
				$this->lblAdAges->Text = sprintf(_tr('%d to %d years old'), $objAd->StartAge, $objAd->EndAge);
			else
				$this->lblAdAges->Text = 'Ospecificerat';
		
			// Set up sex
			switch ($objAd->Sex) {
				case Sex::Males:
					$this->lblAdSex->Text = _tr('Males');
					break;
					
				case Sex::Females:
					$this->lblAdSex->Text = _tr('Females');
					break;
				
				case Sex::Both:
					$this->lblAdSex->Text = _tr('Both');
					break;
					
				default:
					$this->lblAdSex->Text = 'Ospecificerat';
			}
			
			// Set up keywords
			$strKeywords = '';
			foreach ($objAd->Keywords as $strKeyword)
				$strKeywords .= sprintf('%s%s, ', mb_strtoupper(mb_substr($strKeyword, 0, 1)), mb_substr($strKeyword, 1));
				
			$this->pnlAdKeywords->Text = sprintf('%s', substr($strKeywords, 0, -2));
			
			if (!$this->pnlAdKeywords->Text)
				$this->pnlAdKeywords->Text = 'Ospecificerat';
			
			// Set up permissions
			$this->btnMakeBid->Visible = Security::CheckAccess(Actions::MakeBid, $objAd);
		
			// Set up and show deadline if it's a SIM-ad, hide otherwise
			if ($objAd->Type == AdType::SIM && $objAd->Deadline) {
				$this->lblAdDeadline->Text = Localization::FormatTimestamp($objAd->Deadline);
				$this->lblAdDeadline->Visible = true;
			} else
				$this->lblAdDeadline->Visible = false;
				
			if ($objAd->Type == AdType::SIM && $objAd->PublicationDate) {
				$this->lblAdPublication->Text = $objAd->PublicationDate->PHPDate(Localization::$DateFormat);
				$this->lblAdPublication->Visible = true;
			} else 
				$this->lblAdPublication->Visible = false;
		}		
		
		/**
		 * Display pnlMakeBid
		 *
		 */
		public function MakeBid() {
			//Security::VerifyAccess(Actions::MakeBid, $this->objAd);
			
			// Clear fields
			$this->txtBidAmount->Text = '';
			$this->dtpBidDeadline->DateTime = null;
			$this->dtpBidPublicationDate->DateTime = null;
			
			$this->txtBidTax->Text = '0';
			$this->txtBidTotal->Text = '0';
			
			$this->pnlMakeBid->Visible = true;
			$this->dtpBidPublicationDate->Visible = !(bool)$this->objAd->PublicationDate;
			
			$this->lblBidInfo->Visible = false;
			$this->txtBidAmount->Enabled = true;
				$this->dtpBidDeadline->Enabled = true;
				$this->dtpBidPublicationDate->Enabled = true;
				$this->btnBidOk->Enabled = true;

				$this->lblName->Text = $this->lblAdName->Text;
				$this->lblPrice->Text = $this->lblAdPrice->Text;
				
			$this->btnAdClose->Enabled = false;
			$this->btnMakeBid->Enabled = false;
		}
		
		/**
		 * Save the new bid to database
		 *
		 * @param string $strFormId
		 * @param string $strControlId
		 * @param string $intParameter
		 */
		public function DoMakeBid($strFormId, $strControlId, $strParameter) {
			if ($strParameter == UserAnswer::OK && ($blnValid = ($this->txtBidAmount->Validate() && $this->dtpBidDeadline->Validate() && $this->ValidateBidDates() && $this->dtpBidPublicationDate->Validate()))) {					
				$objBid = new Bid();
				$objBid->Amount = $this->txtBidAmount->Text;
				
				// Bid expires at the end of the deadline day 
				if ($this->dtpBidDeadline->DateTime && !$this->dtpBidDeadline->DateTime->IsNull()) {
					$objBid->Deadline = $this->dtpBidDeadline->DateTime;
					$objBid->Deadline->Hour = 23;
					$objBid->Deadline->Minute = 59;
					$objBid->Deadline->Second = 59;
				}
				
				if ($this->dtpBidPublicationDate->DateTime && !$this->dtpBidPublicationDate->DateTime->IsNull())
					$objBid->PublicationDate = $this->dtpBidPublicationDate->DateTime;
					
				if ($this->objAd->PublicationDate)
					$objBid->PublicationDate = $this->objAd->PublicationDate;
				
				$objBid->Ad = $this->objAd;
				$objBid->Status = BidStatus::Unanswered;
				$objBid->ContactedBuyer = 0;
				
				if (Security::Current())
					$objBid->Login = Security::Current();
					
				$objBid->Save();
				
				$this->lblBidInfo->Text = _tr('Your bid is now saved');
				$this->lblBidInfo->Visible = true;
				$this->txtBidAmount->Enabled = false;
				$this->dtpBidDeadline->Enabled = false;
				$this->dtpBidPublicationDate->Enabled = false;
				$this->btnBidOk->Enabled = false;
			}
			if ($strParameter != UserAnswer::OK) {
				$this->pnlMakeBid->Visible = false;
				$this->btnAdClose->Enabled = true;
				$this->btnMakeBid->Enabled = true;
			}
		}
		
		private function ValidateBidDates() {
			if ($this->dtpBidDeadline->DateTime && !$this->dtpBidDeadline->DateTime->IsNull() && $this->dtpBidPublicationDate->DateTime && !$this->dtpBidPublicationDate->DateTime->IsNull()) {
				if ($this->dtpBidDeadline->DateTime->Timestamp > $this->dtpBidPublicationDate->DateTime->Timestamp) {
					$this->dtpBidDeadline->Warning = _tr('Deadline has to be before publication date');
					$this->dtpBidDeadline->MarkAsModified();
					return false;
					
				}
					
			}
			return true;
		}

		/**
		 * Hide pnlAd
		 *
		 */
		public function CloseAd() {
			$this->Visible = false;
			$this->objAd = null;
		}
		
		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Ad':
					$this->objAd = $mixValue;
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
				case 'IsBidding':
					return $this->pnlMakeBid->Visible;
					
				case 'Ad':
					return $this->objAd;
					
				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $e) {
						$e->IncrementOffset();
						throw $e;
					}
			}
		}
		
		/**
		 * To be called on form load
		 *
		 */
		public function Reset() {
			$this->lblBidInfo->Visible = false;
		}
		
		/**
		 * Calculate tax and total, and display
		 *
		 */
		public function UpdateTax() {
			$this->txtBidTax->Text = round($this->txtBidAmount->Text * OQTOPUS_BID_TAX);
			$this->txtBidTotal->Text = $this->txtBidTax->Text + $this->txtBidAmount->Text;
		}
	}
?>