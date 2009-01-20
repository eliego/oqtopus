<?php
	class QTreeNavItem extends QControl {
		protected $blnExpanded = false;
		protected $strName;
		protected $mixValue;
		protected $blnSelected = false;

		protected $blnUseAjax = true;
		protected $intIndentWidth = 15;
		protected $strTagName = 'div';

		protected $lblToggle;
		protected $lblName;
		
		protected $objParentTreeNav;

		public function __construct($strName, $mixValue, $blnExpanded, $objParentObject, $strControlId = null) {
			if ((!($objParentObject instanceof QTreeNav)) &&
				(!($objParentObject instanceof QTreeNavItem)))
				throw new QCallerException('QTreeNavItem can only have QTreeNav or QTreeNavItem as a parent');
			parent::__construct($objParentObject, $strControlId);
			
			if ($objParentObject instanceof QTreeNav)
				$this->objParentTreeNav = $objParentObject;
			else
				$this->objParentTreeNav = $objParentObject->objParentTreeNav;
			
			$this->strName = $strName;
			$this->mixValue = $mixValue;
			$this->blnExpanded = $blnExpanded;

			$this->lblToggle = new QLabel($this, $this->strControlId . 'Tgl');
			$this->lblName = new QLabel($this, $this->strControlId . 'Nam');

//			$this->objParentTreeNav->AddTreeNavItem($this);
		}

		public function ParsePostData() {}
		public function Validate() {return true;}

		protected function RenderChildTreeNavItems($blnDisplayOutput = true) {
			$strToReturn = "";

			foreach ($this->GetChildTreeNavItems() as $objControl)
				if (!$objControl->Rendered)
					$strToReturn .= $objControl->Render($blnDisplayOutput);

			if ($blnDisplayOutput) {
				print ($strToReturn);
				return null;
			} else
				return $strToReturn;
		}

		protected function GetChildTreeNavItems() {
			$objChildControls = $this->objForm->GetChildControls($this);
			$objToReturn = array();
			foreach ($objChildControls as $objChildControl)
				if ($objChildControl instanceof QTreeNavItem)
					array_Push($objToReturn, $objChildControl);
			return $objToReturn;
		}

		public function GetControlHtml() {
			$this->lblName->Text = $this->strName;

			$this->lblToggle->RemoveAllActions('onclick');
			$this->lblName->RemoveAllActions('onclick');
					
			$strChildren = '';
			$objChildControls = $this->GetChildTreeNavItems();
			if (count($objChildControls)) {
				// We have children: we must show either collapsed or expanded
				if ($this->blnExpanded) {
					$this->lblToggle->Text = sprintf('<img id="%s_image" src="%s/includes/qform/assets/treenav_expanded.png" width="11" height="11" alt=""/>',
						$this->strControlId, DOCROOT_VIRTUAL_DIRECTORY . DOCROOT_SUBFOLDER);

					$strChildren = sprintf('<%s id="%s_sub" style="margin-left: %spx">%s</%s>',
						$this->strTagName,
						$this->strControlId,
						$this->intIndentWidth,
						$this->RenderChildTreeNavItems(false),
						$this->strTagName);

					$this->lblToggle->AddAction(new QClickEvent(), new QJavaScriptAction(sprintf("treenavToggleImage('%s')", $this->strControlId)));
//					$this->lblToggle->AddAction(new QClickEvent(), new QJavaScriptAction())
//					foreach ($objChildControls as $objChildControl)
//						$this->lblToggle->AddAction(new QClickEvent(), new QToggleDisplayAction($objChildControl));
					
				} else {
					$this->lblToggle->Text = sprintf('<img src="%s/includes/qform/assets/treenav_not_expanded.png" width="11" height="11" alt=""/>',
						DOCROOT_VIRTUAL_DIRECTORY . DOCROOT_SUBFOLDER);
					$this->lblToggle->RemoveAllActions('onclick');
					
					if ($this->blnUseAjax) {
						$this->lblToggle->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'lblToggle_Click'));
					} else {
						$this->lblToggle->AddAction(new QClickEvent(), new QServerControlAction($this, 'lblToggle_Click'));
					}
				}
			} else {
				$this->lblToggle->Text = sprintf('<img src="%s/includes/qform/assets/treenav_child.png" width="11" height="11" alt=""/>',
					DOCROOT_VIRTUAL_DIRECTORY . DOCROOT_SUBFOLDER);
			}
			
			if ($this->blnUseAjax) {
				$this->lblName->AddAction(new QClickEvent(), new QAjaxControlAction($this, 'lblName_Click'));
			} else {
				$this->lblName->AddAction(new QClickEvent(), new QServerControlAction($this, 'lblName_Click'));
			}
			
			$this->lblName->SetCustomStyle('cursor', 'pointer');
			$this->lblToggle->SetCustomStyle('cursor', 'pointer');

//			if ($this->objParentControl->ControlId != $this->objParentTreeNav->ControlId) {
//				$this->lblName->AddControlToMove();
//				$this->lblName->RemoveAllDropZones();
//				$this->lblName->AddDropZone($this->objParentTreeNav->DropZoneGrouping);
//				$this->lblName->RemoveAllActions('onqcodomove');
//				$this->lblName->AddAction(new QMoveEvent(), new QAjaxControlAction($this, 'lblName_Move'));
//			}
//			$this->objParentTreeNav->DropZoneGrouping->AddControl($this->lblName);

			if ($this->blnSelected) {
				$strToReturn = sprintf('<%s id="%s">%s%s%s</%s>',
					$this->strTagName,
					$this->strControlId,
					$this->lblToggle->Render(false),
					$this->lblName->Render(false, 'CssClass=' . $this->objParentTreeNav->SelectedCssStyle),
					$strChildren,
					$this->strTagName);
			} else {
				$strToReturn = sprintf('<%s id="%s">%s%s%s</%s>',
					$this->strTagName,
					$this->strControlId,
					$this->lblToggle->Render(false),
					$this->lblName->Render(false, 'CssClass=""'),
					$strChildren,
					$this->strTagName);
			}
			return $strToReturn;
		}

		public function lblName_Move($strFormId, $strControlId, $strParameter) {
			// Figure out the new Parent TreeNavItem
			$objNewParentTreeNavItem = $this->lblName->ParentControl->ParentControl;
			$objFolder = Folder::Load($this->mixValue);
			$intNewParentFolderId = $objNewParentTreeNavItem->mixValue;

			// First, cleanup
			$this->lblName->SetParentControl($this);
			$this->lblName->Position = QPosition::NotSet;

			// Then, make sure the new ParentFolderId is not a childfolder of this current folder;
			if (true) {
				// Next, do the save
				$objFolder->ParentFolderId = $intNewParentFolderId;
				$objFolder->Save();

				// Finally, update the treenavs and labels and such
				$this->SetParentControl($objNewParentTreeNavItem);
				$this->ParentControl->Expanded = true;
			}

//			$this->objForm->tnvTest_Setup();
		}

		public function lblName_Click($strFormId, $strControlId, $strParameter) {
			$this->objParentTreeNav->SelectedItem = $this;

			$objActionControl = $this->objParentTreeNav;

			// Pull up the set of Actions to run (regardless of the Form's calltype)
			$objActions = array_merge($objActionControl->GetAllActions('QChangeEvent', 'QAjaxAction'), 
				$objActionControl->GetAllActions('QChangeEvent', 'QServerAction'));
			$strId = $_POST['Qform__FormControl'];

			if ($objActions) foreach ($objActions as $objAction) {
				if ($strMethodName = $objAction->MethodName) {
					$this->objForm->TriggerMethod($strId, $strMethodName);
				}
			}
		}

		public function lblToggle_Click($strFormId, $strControlId, $strParameter) {
			$this->blnExpanded = true;
			$this->MarkAsModified();
		}

		/////////////////////////
		// Public Properties: GET
		/////////////////////////
		public function __get($strName) {
			switch ($strName) {
				case "Expanded": return $this->blnExpanded;
				case "Name": return $this->strName;
				case "Value": return $this->mixValue;
				case "Selected": return $this->blnSelected;
				case "ParentTreeNav": return $this->objParentTreeNav;
				case "NameLabel": return $this->lblName;

				default:
					try {
						return parent::__get($strName);
					} catch (CallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}

		public function SetSelectedFlag($blnSelected) {
			if ($this->blnSelected != $blnSelected) {
				$this->blnSelected = $blnSelected;
				if ($blnSelected)
					$this->lblName->CssClass = $this->objParentTreeNav->SelectedCssStyle;
				else
					$this->lblName->CssClass = null;
			}
		}

		/////////////////////////
		// Public Properties: SET
		/////////////////////////
		public function __set($strName, $mixValue) {
			$this->blnModified = true;

			switch ($strName) {
				case "Expanded":
					try {
						$this->blnExpanded = QType::Cast($mixValue, QType::Boolean);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "Selected":
					try {
						$this->blnSelected = QType::Cast($mixValue, QType::Boolean);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "Name":
					try {
						$this->strName = QType::Cast($mixValue, QType::String);
						break;
					} catch (QInvalidCastException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
				case "Value":
					$this->mixValue = $mixValue;
					break;

				default:
					try {
						parent::__set($strName, $mixValue);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
					break;
			}
		}
	}
?>