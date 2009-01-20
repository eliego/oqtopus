<?php
	/**
 	 * Form to browse currently available offers
 	 *
 	 */
	class BrowseForm extends OqtopusForm {
		protected $dtgData;
		protected $intMediaType;
		protected $intMediaSubType;
		protected $objSearch;
		protected $slblBrowsing;
		
		protected function Form_Create() {
			try {
				parent::Form_Create();
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			Security::VerifyAccess(Actions::Browse);
			
			$this->objSearch = new Search();
			
			$this->objSearch->MediaType = isset($_GET['arg1']) ? $_GET['arg1'] : null;
			$this->objSearch->MediaSubType = isset($_GET['arg2']) ? $_GET['arg2'] : null;
			
			$this->slblBrowsing = new SimpleLabel($this);
			if (isset($_GET['arg1']))
				$this->slblBrowsing->Text = MediaType::$MediaType[$_GET['arg1']];
			if (isset($_GET['arg2']))
				$this->slblBrowsing->Text .= ' - '.MediaType::$MediaSubType[$_GET['arg1']][$_GET['arg2']];

			
			$this->dtgData = new SellersDataGrid($this->objSearch, $this, 'dtgData');
			$this->dtgData->UseAjax = true;
			$this->dtgData->RemoveColumn(4);
		}
		
	}
?>