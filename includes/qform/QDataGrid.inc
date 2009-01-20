<?php
	class QDataGrid extends QDataGridBase  {
		
		protected $blnPersistent = false;
		protected $blnUseAjax = true;
		
		protected function GetHeaderRowHtml() {
			$objHeaderStyle = $this->objRowStyle->ApplyOverride($this->objHeaderRowStyle);

			$strToReturn = sprintf('<tr %s>', $objHeaderStyle->GetAttributes());
			$intColumnIndex = 0;
			if ($this->objColumnArray) foreach ($this->objColumnArray as $objColumn) {
				if ($objColumn->SortByCommand) {						
					// This Column is Sortable
					$strArrowImage = "";
					$strName = $objColumn->Name;

					if ($intColumnIndex == $this->intSortColumnIndex) {
						if ($this->intSortDirection == 0)
							$strArrowImage = sprintf(' <img src="/adds/sort_arrow.png" width="7" height="7" alt="Sorted">');
						else
							$strArrowImage = sprintf(' <img src="/adds/sort_arrow_reverse.png" width="7" height="7" alt="Reverse Sorted">');
					}
					
					$this->strActionParameter = $intColumnIndex;

					$strToReturn .= sprintf('<th %s><a href="" %s%s>%s</a>%s</th>',
						$this->objHeaderRowStyle->GetAttributes(),
						$this->GetActionAttributes(),
						$this->objHeaderLinkStyle->GetAttributes(),
						$strName,
						$strArrowImage);
				} else
					$strToReturn .= sprintf('<th %s>%s</th>', $this->objHeaderRowStyle->GetAttributes(), $objColumn->Name);
				$intColumnIndex++;
			}
			$strToReturn .= '</tr>';

			return $strToReturn;
		}		
		
		public function __construct($objParentObject, $strControlId = null) {
			try {
				parent::__construct($objParentObject, $strControlId);
			} catch (QCallerException  $objExc) {
				$objExc->IncrementOffset();
				throw $objExc;
			}
			
			
			$this->objHeaderRowStyle->CssClass = "BidsDataGrid_HeaderRow";
			$this->objHeaderLinkStyle->CssClass = "BidsDataGrid_HeaderLink";
			$this->objRowStyle->CssClass = "BidsDataGrid_Row";
			$this->objAlternateRowStyle->CssClass = "BidsDataGrid_AlternateRow";	
		}
		
		public function ForceUpdate() {
			$this->objDataSource = null;
		}
		
		protected function GetControlHtml() {
			// Table Tag
			$strStyle = $this->GetStyleAttributes();
			if ($strStyle)
				$strStyle = sprintf('style="%s" ', $strStyle);
			$strToReturn = sprintf('<table id="%s" %s%s>', $this->strControlId, $this->GetAttributes(), $strStyle);

			// Header Row (if applicable)
			if ($this->blnShowHeader)
				$strToReturn .= $this->GetHeaderRowHtml();

			// DataGrid Rows
			$this->intCurrentRowIndex = 0;
			if ($this->objDataSource)
				foreach ($this->objDataSource as $objObject)
					$strToReturn .= $this->GetDataGridRowHtml($objObject);
					
			
			// Paginator Row (if applicable)
			if ($this->objPaginator)
				$strToReturn .= $this->GetPaginatorRowHtml($this->objPaginator);

			// Footer Row (if applicable)
			if ($this->blnShowFooter)
				$strToReturn .= $this->GetFooterRowHtml();

			// Finish Up
			$strToReturn .= '</table>';
			
			if (!$this->blnPersistent)
				$this->objDataSource = null;
				
			return $strToReturn;
		}
		
		protected function GetPaginatorRowHtml($objPaginator) {
			$strToReturn = sprintf('<tr><td colspan="%s"><table cellspacing="0" cellpadding="0" border="0" width="100%%"><tr><td width="50%%" valign="bottom" style="font-size: 10px;">', count($this->objColumnArray));

			if ($this->TotalItemCount > 0) {
				$intStart = (($this->PageNumber - 1) * $this->ItemsPerPage) + 1;
				$intEnd = $intStart + count($this->DataSource) - 1;
				$strToReturn .= sprintf($this->strLabelForPaginated,
					$intStart,
					$intEnd,
					$this->TotalItemCount);
			} else {
				$intCount = count($this->objDataSource);
				if ($intCount == 0)
					$strToReturn .= sprintf($this->strLabelForNoneFound);
				else if ($intCount == 1)
					$strToReturn .= sprintf($this->strLabelForOneFound);
				else
					$strToReturn .= sprintf($this->strLabelForMultipleFound, $intCount);
			}

			$strToReturn .= '</td><td width="50%" valign="bottom" style="font-size: 10px; text-align: right;">';
			$strToReturn .= $objPaginator->Render(false);
			$strToReturn .= '</td></tr></table></td></tr>';
			
			return $strToReturn;
		}
		
		// Parse the _POST to see if the user is requesting a change in the sort column or page
		public function Sort_Click($strFormId, $strControlId, $strParameter) {
			if (strlen($strParameter)) {
				// Sorting
				$intColumnIndex = QType::Cast($strParameter, QType::Integer);
				$objColumn = $this->objColumnArray[$intColumnIndex];
				
				// First, reset pagination (if applicable)
				if ($this->objPaginator)
					$this->PageNumber = 1;

				// First, make sure the Column is Sortable
				if ($objColumn->SortByCommand) {
					// It is
					
					// Are we currently sorting by this column?
					if ($this->intSortColumnIndex == $intColumnIndex) {
						// Yes we are currently sorting by this column
						
						// In Reverse?
						if ($this->intSortDirection == 1) {
							// Yep -- unreverse the sort
							$this->intSortDirection = 0;
						} else {
							// Nope -- can we reverse?
							if ($objColumn->ReverseSortByCommand)
								$this->intSortDirection = 1;
						}
					} else {
						// Nope -- so let's set it to this column
						$this->intSortColumnIndex = $intColumnIndex;
						$this->intSortDirection = 0;
					}
					if ($this->blnPersistent) {
						if ($this->objParentControl)
							$this->objParentControl->MarkAsModified();
						$this->objDataSource = null;
					}
				} else {
					// It isn't -- clear all sort properties
					$this->intSortDirection = 0;
					$this->intSortColumnIndex = -1;
				}
			}
		}


		public function __set($strName, $mixValue) {
			switch ($strName) {
				case 'Persistent':
					$this->blnPersistent = (bool)$mixValue;
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
				case 'Persistent':
					return $this->blnPersistent;
					
				case 'Update':
					return ($this->objDataSource === null) ? true : false;
					
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
		 * Get a specific item from DataSource
		 * 
		 * This is sort of a very ugly way to implement som caching-functionality
		 *
		 * @param string $strColumnName
		 * @param mixed $mixValue
		 */
		public function GetObjectFromDataSource($strColumnName, $mixValue) {
			if ($this->objDataSource) {
				foreach ($this->objDataSource as $obj)
					if ($obj->$strColumnName == $mixValue)
						return $obj;
			} else 
				return null;
		}
	}
	
?>