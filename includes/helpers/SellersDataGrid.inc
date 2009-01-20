<?php
	/**
	 * Custom DataGrid which the usual columns for sellers already added
	 *
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class SellersDataGrid extends QDataGrid {
		protected $objSearch;
		
		public function __construct($objSearch, $objParent, $strControlId = null) {
			if (!($objSearch instanceof Search))
				throw new WrongParametersException(_tr("First argument must be a Search object"));
							
			try {
				parent::__construct($objParent, $strControlId);
			} catch (QCallerException $e) {
				$e->IncrementOffset();
				throw $e;
			}
			
			$this->objSearch = $objSearch;
			
			$dgcSeller = new QDataGridColumn(_tr('Seller'), '<a href="<?= Navigation::CreateUrl("ProfileForm", $_ITEM) ?>"><?= $_ITEM->SellerName ?></a>');
			$dgcSeller->SortByCommand = 'seller_name ASC';
			$dgcSeller->ReverseSortByCommand = 'seller_name DESC';

			$dgcPrice = new QDataGridColumn(_tr('Requested price'), '<?= $_CONTROL->RenderAttribute($_ITEM->GetVirtualAttribute("MinPrice"), $_ITEM->GetVirtualAttribute("MaxPrice")) ?>');
			$dgcPrice->SortByCommand = '__MinPrice ASC';
			$dgcPrice->ReverseSortByCommand = '__MaxPrice DESC';
			
			$dgcReach = new QDataGridColumn(_tr('Reach'), '<?= $_CONTROL->RenderAttribute($_ITEM->GetVirtualAttribute("MinReach"), $_ITEM->GetVirtualAttribute("MaxReach")) ?>');
			$dgcReach->SortByCommand = '__MinReach ASC';
			$dgcReach->ReverseSortByCommand = '__MaxReach DESC';
			
			$dgcAreas = new QDataGridColumn(_tr('Areas'), '<?= BitmaskComposite::GetHtmlList($_ITEM->GetVirtualAttribute("Areas"), Areas::$Areas) ?>');
			
			$dgcMediaTypes = new QDataGridColumn(_tr('Mediatypes'), '<?= BitmaskComposite::GetHtmlList($_ITEM->GetVirtualAttribute("Medias"), MediaType::$MediaType) ?>');
			
			$objPag = new QPaginator($this);
		
			$this->AddColumn($dgcSeller);
			$this->AddColumn($dgcPrice);
			$this->AddColumn($dgcReach);
			$this->AddColumn($dgcAreas);
			$this->AddColumn($dgcMediaTypes);
			$this->Paginator = $objPag;
					
			$this->TotalItemCount = count($this->objSearch->DoSearch());
		}
		
		public function GetControlHtml() {
			if (!$this->Persistent || $this->Update)
				$this->DataSource = $this->objSearch->DoSearch($this->SortInfo, $this->LimitInfo);
				
			return parent::GetControlHtml();
		}
		
		/**
		 * Render an aiitrubte as MIN - MAX or just ATTRIBUTE
		 *
		 * @param int $intMinAttr
		 * @param int $intMaxAttr
		 */
		protected function RenderAttribute($intMinAttr, $intMaxAttr) {
			if ($intMinAttr == $intMaxAttr)
				return $intMinAttr;
			else 
				return sprintf('%d - %d', $intMinAttr, $intMaxAttr);
		}
	}
?>
