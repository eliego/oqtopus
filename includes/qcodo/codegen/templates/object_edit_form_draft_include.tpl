<TargetFilePath="<%= QApplication::$DocumentRoot . DOCROOT_SUBFOLDER %>/form_drafts/generated/<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_edit.php.inc" OverwriteFlag="true">
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=<?php _p(QApplication::$EncodingType); ?>" />
		<title><?php _p($this->strTitleVerb) ?> <%= $objTable->ClassName %></title>
		<style>
			/* These are all EXAMPLES -- they are meant to be updated/changed/modified */
			TD, BODY { font: 12px <?php _p(QFontFamily::Verdana); ?>; text-align: left; }
			TH { font: 12px <?php _p(QFontFamily::Verdana); ?>; text-align: left; font-weight: bold; }
			.title { font: 30px <?php _p(QFontFamily::Verdana); ?>; font-weight: bold; margin-left: -2px;}
			.title_action { font: 12px <?php _p(QFontFamily::Verdana); ?>; font-weight: bold; margin-bottom: -4px; }
			.warning { color: #ff0000; }
			.instructions { font: 9px <?php _p(QFontFamily::Arial); ?>; font-style: italic; }
			.item_divider { line-height: 16px; }
			.item_label { font: 12px <?php _p(QFontFamily::Verdana); ?>; padding-bottom: 4px; }
			.item_label_disabled { font: 12px <?php _p(QFontFamily::Verdana); ?>; padding-bottom: 4px; color: #999999; }

			.button { font: 10px <?php _p(QFontFamily::Verdana); ?>; font-weight: bold; }
			.listbox { font: 12px <?php _p(QFontFamily::Verdana); ?>; width: 250px; }
			.textbox { font: 12px <?php _p(QFontFamily::Verdana); ?>; width: 250px; }

			.paginator_inactive_step { font-weight: bold; color: #aaaaaa; }
			.paginator_active_step { font-weight: bold; color: #000000; text-decoration: none; }
			.paginator_page { text-decoration: none; color: #000000; padding: 0px 3px 0px 3px; }
			.paginator_selected_page { font-weight: bold; background-color: #ddccff; padding: 0px 3px 0px 3px; border: 1px; border-style: solid; }
		</style>
	</head><body>
	<?php $this->RenderBegin() ?>
		<div class="title_action"><?php _p($this->strTitleVerb); ?></div>
		<div class="title"><?php _t('<%= $objTable->ClassName %>')?></div>
		<br class="item_divider" />

<% foreach ($objTable->ColumnArray as $objColumn) { %><%
	if ($objColumn->DbType == QDatabaseFieldType::Blob) {
		$strToReturn = sprintf('		<?php $this->%s->RenderWithName("Rows=10"); ?>%s<br class="item_divider" />',
			$objCodeGen->FormControlVariableNameForColumn($objColumn), "\n\t\t");
	} else {
		$strToReturn = sprintf('		<?php $this->%s->RenderWithName(); ?>%s<br class="item_divider" />',
			$objCodeGen->FormControlVariableNameForColumn($objColumn), "\n\t\t");
	}
	
	return $strToReturn;
%>

<% } %>
<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %>
	<% if ($objReverseReference->Unique) { %>
		<?php $this-><%= $objCodeGen->FormControlVariableNameForUniqueReverseReference($objReverseReference); %>->RenderWithName(); ?>
		<br class="item_divider" />

	<% } %>
<% } %>
<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %>
		<?php $this-><%= $objCodeGen->FormControlVariableNameForManyToManyReference($objManyToManyReference); %>->RenderWithName(true, "Rows=10"); ?>
		<br class="item_divider" />

<% } %>

		<br />
		<?php $this->btnSave->Render() ?>
		&nbsp;&nbsp;&nbsp;
		<?php $this->btnCancel->Render() ?>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<?php $this->btnDelete->Render() ?>

	<?php $this->RenderEnd() ?>		
	</body>
</html>