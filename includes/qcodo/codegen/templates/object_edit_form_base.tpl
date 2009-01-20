<TargetFilePath="<%= QApplication::$DocumentRoot . DOCROOT_SUBFOLDER %>/includes/forms_generated/<%= $objTable->ClassName %>EditFormBase.inc" OverwriteFlag="true"/>
<?php
	/**
	 * This is the abstract Form class for the Create, Edit, and Delete functionality
	 * of the <%= $objTable->ClassName %> class.  This code-generated class
	 * contains all the basic Qform elements to display an HTML form that can
	 * manipulate a single <%= $objTable->ClassName %> object.
	 *
	 * To take advantage of some (or all) of these control objects, you
	 * must create a new Form which extends this <%= $objTable->ClassName %>EditFormBase
	 * class.
	 *
	 * Any and all changes to this file will be overwritten with any subsequent re-
	 * code generation.
	 * 
	 * @package <%= $objCodeGen->ApplicationName; %>
	 * @subpackage FormBaseObjects
	 * 
	 */
	abstract class <%= $objTable->ClassName %>EditFormBase extends QForm {
		// General Form Variables
		protected $<%= $objCodeGen->VariableNameFromTable($objTable->Name); %>;
		protected $strTitleVerb;
		protected $blnEditMode;

		// Controls for <%= $objTable->ClassName %>'s Data Fields
<% foreach ($objTable->ColumnArray as $objColumn) { %>
		protected $<%= $objCodeGen->FormControlVariableNameForColumn($objColumn); %>;
<% } %>

		// Other ListBoxes (if applicable) via Unique ReverseReferences and ManyToMany References
<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %>
	<% if ($objReverseReference->Unique) { %>
		protected $<%= $objCodeGen->FormControlVariableNameForUniqueReverseReference($objReverseReference); %>;
	<% } %>
<% } %>
<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %>
		protected $<%= $objCodeGen->FormControlVariableNameForManyToManyReference($objManyToManyReference); %>;
<% } %>

		// Button Actions
		protected $btnSave;
		protected $btnCancel;
		protected $btnDelete;

		protected function Setup<%= $objTable->ClassName %>() {
			// Lookup Object PK information from Query String (if applicable)
			// Set mode to Edit or New depending on what's found
<% foreach ($objTable->PrimaryKeyColumnArray as $objColumn) { %>
			$<%= $objColumn->VariableName %> = QApplication::QueryString('<%= $objColumn->VariableName %>');
<% } %>
			if (<% foreach ($objTable->PrimaryKeyColumnArray as $objColumn) { %>($<%= $objColumn->VariableName %>) || <% } %><%----%>) {
				$this-><%= $objCodeGen->VariableNameFromTable($objTable->Name); %> = <%= $objTable->ClassName %>::Load(<% foreach ($objTable->PrimaryKeyColumnArray as $objColumn) { %>($<%= $objColumn->VariableName %>), <% } %><%--%>);

				if (!$this-><%= $objCodeGen->VariableNameFromTable($objTable->Name) %>)
					throw new Exception('Could not find a <%= $objTable->ClassName %> object with PK arguments: ' . <% foreach ($objTable->PrimaryKeyColumnArray as $objColumn) { %>$<%= $objColumn->VariableName %> . ', ' . <% } %><%----------%>);

				$this->strTitleVerb = QApplication::Translate('Edit');
				$this->blnEditMode = true;
			} else {
				$this-><%= $objCodeGen->VariableNameFromTable($objTable->Name); %> = new <%= $objTable->ClassName %>();
				$this->strTitleVerb = QApplication::Translate('Create');
				$this->blnEditMode = false;
			}
		}

		protected function Form_Create() {
			// Call Setup<%= $objTable->ClassName %> to either Load/Edit Existing or Create New
			$this->Setup<%= $objTable->ClassName %>();

			// Create/Setup Controls for <%= $objTable->ClassName %>'s Data Fields
<% foreach ($objTable->ColumnArray as $objColumn) { %>
			$this-><%= $objCodeGen->FormControlVariableNameForColumn($objColumn) %>_Create();
<% } %>

			// Create/Setup ListBoxes (if applicable) via Unique ReverseReferences and ManyToMany References
<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %>
	<% if ($objReverseReference->Unique) { %>
			$this-><%= $objCodeGen->FormControlVariableNameForUniqueReverseReference($objReverseReference) %>_Create();
	<% } %>
<% } %>
<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %>
			$this-><%= $objCodeGen->FormControlVariableNameForManyToManyReference($objManyToManyReference) %>_Create();
<% } %>

			// Create/Setup Button Action controls
			$this->btnSave_Create();
			$this->btnCancel_Create();
			$this->btnDelete_Create();
		}

		// Protected Create Methods
<% foreach ($objTable->ColumnArray as $objColumn) { %><%
	// Use the "control_create_" subtemplates to generate the code
	// required to create/setup the control.
	$mixArguments = array(
		'objColumn' => $objColumn,
		'strObjectName' => $objCodeGen->VariableNameFromTable($objTable->Name),
		'strControlId' => $objCodeGen->FormControlVariableNameForColumn($objColumn)
	);

	// Figure out WHICH "control_create_" to use
	if ($objColumn->Identity) {
		$strTemplateFilename = 'identity';
	} else if ($objColumn->Timestamp) {
		$strTemplateFilename = 'identity';
	} else if ($objColumn->Reference) {
		if ($objColumn->Reference->IsType)
			$strTemplateFilename = 'type';
		else
			$strTemplateFilename = 'reference';
	} else {
		$strTemplateFilename = $objColumn->VariableType;
	}
	
	// Get the subtemplate and evaluate
	$strTemplateFilename = sprintf('%s%s%scontrol_create_%s.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPath, $strTemplateFilename);
	$strToReturn = $objCodeGen->EvaluateTemplate(file_get_contents($strTemplateFilename), $mixArguments) . "\n";
	$strToReturn .= "\n";
	return $strToReturn;
%><% } %>
<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %><%
	if ($objReverseReference->Unique) { 
		// Use the "control_create_" subtemplates to generate the code
		// required to create/setup the control.
		$mixArguments = array(
			'objReverseReference' => $objReverseReference,
			'objTable' => $objTable,
			'strObjectName' => $objCodeGen->VariableNameFromTable($objTable->Name),
			'strControlId' => $objCodeGen->FormControlVariableNameForUniqueReverseReference($objReverseReference)
		);
		// Get the subtemplate and evaluate
		$strTemplateFilename = sprintf('%s%s%scontrol_create_unique_reversereference.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPath);
		$strToReturn = $objCodeGen->EvaluateTemplate(file_get_contents($strTemplateFilename), $mixArguments) . "\n";
		$strToReturn .= "\n";
		return $strToReturn;
	} else
		return null;
%><% } %>
<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %><%
	// Use the "control_create_manytomany_reference" subtemplate to generate the code
	// required to create/setup the control.
	$mixArguments = array(
		'objManyToManyReference' => $objManyToManyReference,
		'objTable' => $objTable,
		'strObjectName' => $objCodeGen->VariableNameFromTable($objTable->Name),
		'strControlId' => $objCodeGen->FormControlVariableNameForManyToManyReference($objManyToManyReference)
	);
	// Get the subtemplate and evaluate
	$strTemplateFilename = sprintf('%s%s%scontrol_create_manytomany_reference.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPath);
	$strToReturn = $objCodeGen->EvaluateTemplate(file_get_contents($strTemplateFilename), $mixArguments) . "\n";
	$strToReturn .= "\n";
	return $strToReturn;
%><% } %>

		// Setup btnSave
		protected function btnSave_Create() {
			$this->btnSave = new QButton($this);
			$this->btnSave->Text = QApplication::Translate('Save');
			$this->btnSave->AddAction(new QClickEvent(), new QServerAction('btnSave_Click'));
			$this->btnSave->PrimaryButton = true;
		}

		// Setup btnCancel
		protected function btnCancel_Create() {
			$this->btnCancel = new QButton($this);
			$this->btnCancel->Text = QApplication::Translate('Cancel');
			$this->btnCancel->AddAction(new QClickEvent(), new QServerAction('btnCancel_Click'));
			$this->btnCancel->CausesValidation = false;
		}

		// Setup btnDelete
		protected function btnDelete_Create() {
			$this->btnDelete = new QButton($this);
			$this->btnDelete->Text = QApplication::Translate('Delete');
			$this->btnDelete->AddAction(new QClickEvent(), new QConfirmAction(sprintf(QApplication::Translate('Are you SURE you want to DELETE this %s?'), '<%= $objTable->ClassName %>')));
			$this->btnDelete->AddAction(new QClickEvent(), new QServerAction('btnDelete_Click'));
			$this->btnDelete->CausesValidation = false;
			if (!$this->blnEditMode)
				$this->btnDelete->Visible = false;
		}
		
		// Protected Update Methods
		protected function Update<%= $objTable->ClassName; %>Fields() {
<% foreach ($objTable->ColumnArray as $objColumn) { %><%
	if ((!$objColumn->Identity) && (!$objColumn->Timestamp)) {
		// Use the "control_create_" subtemplates to generate the code
		// required to create/setup the control.
		$mixArguments = array(
			'objColumn' => $objColumn,
			'strObjectName' => $objCodeGen->VariableNameFromTable($objTable->Name),
			'strControlId' => $objCodeGen->FormControlVariableNameForColumn($objColumn)
		);
	
		// Figure out WHICH "control_create_" to use
		if ($objColumn->Reference) {
			if ($objColumn->Reference->IsType)
				$strTemplateFilename = 'type';
			else
				$strTemplateFilename = 'reference';
		} else switch ($objColumn->VariableType) {
			case QType::Boolean:
				$strTemplateFilename = 'checkbox';
				break;
			case QType::DateTime:
				$strTemplateFilename = 'calendar';
				break;
			default:
				$strTemplateFilename = 'textbox';
				break;
		}
		
		// Get the subtemplate and evaluate
		$strTemplateFilename = sprintf('%s%s%scontrol_update_%s.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPath, $strTemplateFilename);
		return $objCodeGen->EvaluateTemplate(file_get_contents($strTemplateFilename), $mixArguments) . "\n";
	} else
		return null;
%><% } %>
<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %><%
	if ($objReverseReference->Unique) {
		// Use the "control_update_unique_reversereference" subtemplate to generate the code
		// required to create/setup the control.
		$mixArguments = array(
			'objReverseReference' => $objReverseReference,
			'strObjectName' => $objCodeGen->VariableNameFromTable($objTable->Name),
			'strControlId' => $objCodeGen->FormControlVariableNameForUniqueReverseReference($objReverseReference)
		);
	
		// Get the subtemplate and evaluate
		$strTemplateFilename = sprintf('%s%s%scontrol_update_unique_reversereference.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPath);
		return $objCodeGen->EvaluateTemplate(file_get_contents($strTemplateFilename), $mixArguments) . "\n";
	} else
		return null;
%><% } %>
		}

<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %><%
		// Use the "control_update_manytomany_reference" subtemplate to generate the code
		// required to create/setup the control.
		$mixArguments = array(
			'objManyToManyReference' => $objManyToManyReference,
			'strObjectName' => $objCodeGen->VariableNameFromTable($objTable->Name),
			'strControlId' => $objCodeGen->FormControlVariableNameForManyToManyReference($objManyToManyReference)
		);

		// Get the subtemplate and evaluate
		$strTemplateFilename = sprintf('%s%s%scontrol_update_manytomany_reference.tpl', QApplication::$DocumentRoot, DOCROOT_SUBFOLDER, QCodeGen::SubTemplatesPath);
		return $objCodeGen->EvaluateTemplate(file_get_contents($strTemplateFilename), $mixArguments) . "\n";
%><% } %>

		// Control ServerActions
		protected function btnSave_Click($strFormId, $strControlId, $strParameter) {
			$this->Update<%= $objTable->ClassName; %>Fields();
			$this-><%= $objCodeGen->VariableNameFromTable($objTable->Name); %>->Save();

<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %>
			$this-><%= $objCodeGen->FormControlVariableNameForManyToManyReference($objManyToManyReference); %>_Update();
<% } %>

			QApplication::Redirect('<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_list.php');
		}

		protected function btnCancel_Click($strFormId, $strControlId, $strParameter) {
			QApplication::Redirect('<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_list.php');
		}

		protected function btnDelete_Click($strFormId, $strControlId, $strParameter) {
<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %>
			$this-><%= $objCodeGen->VariableNameFromTable($objTable->Name) %>->UnassociateAll<%= $objManyToManyReference->ObjectDescriptionPlural %>();
<% } %>

			$this-><%= $objCodeGen->VariableNameFromTable($objTable->Name); %>->Delete();

			QApplication::Redirect('<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_list.php');
		}
	}
?>