<?php
	// This class is meant to be a date-picker.  It will essentially render an uneditable HTML textbox
	// as well as a calendar icon.  The idea is that if you click on the icon or the textbox,
	// it will pop up a calendar in a new small window.
	// * "Date" is a Date object for the specified date.

	class QDateTimePickerExt extends QDateTimePicker {
		///////////////////////////
		// Private Member Variables
		///////////////////////////
		protected $intMinimumDay = 1;
		protected $intMinimumMonth = 1;
		protected $now;
		
		//////////
		// Methods
		//////////
		
		public function __construct($objParent, $strId = null, $dtNow = null) {
			try {
				parent::__construct($objParent, $strId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->now = $dtNow ? $dtNow : new QDateTime(QDateTime::Now);
			$this->AddAction(new QChangeEvent(), new QAjaxControlAction($this, 'date_Change'));
			$this->date_Change();
		}
		public function date_Change() {
            if($this->DateTime ) {
                if($this->DateTime->Year > $this->now->Year) {
                    $this->MinimumMonth = 1;
                    $this->MinimumDay = 1;
                } else if($this->DateTime->Year == $this->now->Year) {
                    $this->MinimumMonth = $this->now->Month ;
                    $this->MinimumDay = $this->now->Day;
                }            
                if($this->DateTime->Month > $this->now->Month) {
                    $this->MinimumDay = 1;
                }            
            } else {
                $this->DateTime = new QDateTime(QDateTime::Now);
                $this->MinimumYear = $this->now->Year;
                $this->MinimumMonth = $this->now->Month;
                $this->MinimumDay = $this->now->Day;
            }
		}
				
		protected function GetControlHtml() {
			$strAttributes = $this->GetAttributes();

			$strStyle = $this->GetStyleAttributes();
			if ($strStyle)
				$strAttributes .= sprintf(' style="%s"', $strStyle);
				
			$strCommand = sprintf(' onchange="Qcodo__DateTimePicker_Change(\'%s\', this);"', $this->strControlId);

			if ($this->dttDateTime) {
				$dttDateTime = $this->dttDateTime;
			} else {
				$dttDateTime = new QDateTime();
			}

			$strToReturn = '';

			// Generate Date-portion
			switch ($this->strDateTimePickerType) {
				case QDateTimePickerType::Date:
				case QDateTimePickerType::DateTime:
				case QDateTimePickerType::DateTimeSeconds:
					// Month
					$strMonthListbox = sprintf('<select name="%s_lstMonth" id="%s_lstMonth"%s%s>', $this->strControlId, $this->strControlId, $strAttributes, $strCommand);
					if (!$this->blnRequired)
						$strMonthListbox .= '<option value="">--</option>';
					for ($intMonth = $this->intMinimumMonth; $intMonth <= 12; $intMonth++) {
						if ((!$dttDateTime->IsDateNull() && ($dttDateTime->Month == $intMonth)) || ($this->intSelectedMonth == $intMonth))
							$strSelected = ' selected="selected"';
						else
							$strSelected = '';
						$strMonthListbox .= sprintf('<option value="%s"%s>%s</option>',
							$intMonth,
							$strSelected,
							date('M', mktime(0, 0, 0, $intMonth, 1, 2000)));
					}
					$strMonthListbox .= '</select>';

					// Day
					$strDayListbox = sprintf('<select name="%s_lstDay" id="%s_lstDay"%s%s>', $this->strControlId, $this->strControlId, $strAttributes, $strCommand);
					if (!$this->blnRequired)
						$strDayListbox .= '<option value="">--</option>';
					if ($dttDateTime->IsDateNull()) {
						if ($this->blnRequired) {
							// New DateTime, but we are required -- therefore, let's assume January is preselected
							for ($intDay = $this->MinimumDay; $intDay <= 31; $intDay++) {
								$strDayListbox .= sprintf('<option value="%s">%s</option>', $intDay, $intDay);
							}
						} else {
							// New DateTime -- but we are NOT required
							
							// See if a month has been selected yet.
							if ($this->intSelectedMonth) {
								$intSelectedYear = ($this->intSelectedYear) ? $this->intSelectedYear : 2000;
								$intDaysInMonth = date('t', mktime(0, 0, 0, $this->intSelectedMonth, 1, $intSelectedYear));
								for ($intDay = $this->intMinimumDay; $intDay <= $intDaysInMonth; $intDay++) {
									if (($dttDateTime->Day == $intDay) || ($this->intSelectedDay == $intDay))
										$strSelected = ' selected="selected"';
									else
										$strSelected = '';
									$strDayListbox .= sprintf('<option value="%s"%s>%s</option>',
										$intDay,
										$strSelected,
										$intDay);
								}
							} else {
								// It's ok just to have the "--" marks and nothing else
							}
						}
					} else {
						$intDaysInMonth = $dttDateTime->PHPDate('t');
						for ($intDay = $this->intMinimumDay; $intDay <= $intDaysInMonth; $intDay++) {
							if (($dttDateTime->Day == $intDay) || ($this->intSelectedDay == $intDay))
								$strSelected = ' selected="selected"';
							else
								$strSelected = '';
							$strDayListbox .= sprintf('<option value="%s"%s>%s</option>',
								$intDay,
								$strSelected,
								$intDay);
						}
					}
					$strDayListbox .= '</select>';
					
					// Year
					$strYearListbox = sprintf('<select name="%s_lstYear" id="%s_lstYear"%s%s>', $this->strControlId, $this->strControlId, $strAttributes, $strCommand);
					if (!$this->blnRequired)
						$strYearListbox .= '<option value="">--</option>';
					for ($intYear = $this->intMinimumYear; $intYear <= $this->intMaximumYear; $intYear++) {
						if (/*!$dttDateTime->IsDateNull() && */(($dttDateTime->Year == $intYear) || ($this->intSelectedYear == $intYear)))
							$strSelected = ' selected="selected"';
						else
							$strSelected = '';
						$strYearListbox .= sprintf('<option value="%s"%s>%s</option>', $intYear, $strSelected, $intYear);
					}
					$strYearListbox .= '</select>';

					// Put it all together
					switch ($this->strDateTimePickerFormat) {
						case QDateTimePickerFormat::MonthDayYear:
							$strToReturn .= $strMonthListbox . '&nbsp;' . $strDayListbox . '&nbsp;' . $strYearListbox;
							break;
						case QDateTimePickerFormat::DayMonthYear:
							$strToReturn .= $strDayListbox . '&nbsp;' . $strMonthListbox . '&nbsp;' . $strYearListbox;
							break;
						case QDateTimePickerFormat::YearMonthDay:
							$strToReturn .= $strYearListbox . '&nbsp;' . $strMonthListbox . '&nbsp;' . $strDayListbox;
							break;
					}
			}

			switch ($this->strDateTimePickerType) {
				case QDateTimePickerType::DateTime:
				case QDateTimePickerType::DateTimeSeconds:
					$strToReturn .= '&nbsp;&nbsp;&nbsp;';
			}

			switch ($this->strDateTimePickerType) {
				case QDateTimePickerType::Time:
				case QDateTimePickerType::TimeSeconds:
				case QDateTimePickerType::DateTime:
				case QDateTimePickerType::DateTimeSeconds:
					// Hour
					$strHourListBox = sprintf('<select name="%s_lstHour" id="%s_lstHour"%s>', $this->strControlId, $this->strControlId, $strAttributes);
					if (!$this->blnRequired)
						$strHourListBox .= '<option value="">--</option>';
					for ($intHour = 0; $intHour <= 23; $intHour++) {
						if (!$dttDateTime->IsTimeNull() && ($dttDateTime->Hour == $intHour))
							$strSelected = ' selected="selected"';
						else
							$strSelected = '';
						$strHourListBox .= sprintf('<option value="%s"%s>%s</option>',
							$intHour,
							$strSelected,
							date('H', mktime($intHour, 0, 0, 1, 1, 2000)));
					}
					$strHourListBox .= '</select>';


					// Minute
					$strMinuteListBox = sprintf('<select name="%s_lstMinute" id="%s_lstMinute"%s>', $this->strControlId, $this->strControlId, $strAttributes);
					if (!$this->blnRequired)
						$strMinuteListBox .= '<option value="">--</option>';
					for ($intMinute = 0; $intMinute <= 59; $intMinute++) {
						if (!$dttDateTime->IsTimeNull() && ($dttDateTime->Minute == $intMinute))
							$strSelected = ' selected="selected"';
						else
							$strSelected = '';
						$strMinuteListBox .= sprintf('<option value="%s"%s>%02d</option>',
							$intMinute,
							$strSelected,
							$intMinute);
					}
					$strMinuteListBox .= '</select>';


					// Seconds
					$strSecondListBox = sprintf('<select name="%s_lstSecond" id="%s_lstSecond"%s>', $this->strControlId, $this->strControlId, $strAttributes);
					if (!$this->blnRequired)
						$strSecondListBox .= '<option value="">--</option>';
					for ($intSecond = 0; $intSecond <= 59; $intSecond++) {
						if (!$dttDateTime->IsTimeNull() && ($dttDateTime->Second == $intSecond))
							$strSelected = ' selected="selected"';
						else
							$strSelected = '';
						$strSecondListBox .= sprintf('<option value="%s"%s>%02d</option>',
							$intSecond,
							$strSelected,
							$intSecond);
					}
					$strSecondListBox .= '</select>';
					
					
					// PUtting it all together
					if (($this->strDateTimePickerType == QDateTimePickerType::DateTimeSeconds) ||
						($this->strDateTimePickerType == QDateTimePickerType::TimeSeconds))
						$strToReturn .= $strHourListBox . '&nbsp;:&nbsp;' . $strMinuteListBox . '&nbsp;:&nbsp;' . $strSecondListBox;
					else
						$strToReturn .= $strHourListBox . '&nbsp;:&nbsp;' . $strMinuteListBox;
			}

			return sprintf('<span id="%s">%s</span>', $this->strControlId, $strToReturn);
		}

		/////////////////////////
		// Public Properties: GET
		/////////////////////////
		public function __get($strName) {
			switch ($strName) {
				// MISC
				case "MinimumDay": return $this->intMinimumDay;
				case "MinimumMonth": return $this->intMinimumMonth;

				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		/////////////////////////
		// Public Properties: SET
		/////////////////////////
		public function __set($strName, $mixValue) {
			$this->blnModified = true;

			switch ($strName) {
				// MISC
				case "MinimumDay":
					try {
						$this->intMinimumDay = QType::Cast($mixValue, QType::String);
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
					break;
				case "MinimumMonth":
					try {
						$this->intMinimumMonth = QType::Cast($mixValue, QType::String);
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
					break;
				default:
					try {
						parent::__set($strName, $mixValue);
						break;
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}
	}
?>