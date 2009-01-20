<TargetFilePath="<%= QApplication::$DocumentRoot . DOCROOT_SUBFOLDER %>/form_drafts/generated/<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_list.php.inc" OverwriteFlag="true">
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=<?php _p(QApplication::$EncodingType); ?>" />
		<title><?php _t('List All'); ?> <%= $objTable->ClassNamePlural %></title>
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
		<div class="title_action"><?php _t('List All'); ?></div>
		<div class="title"><?php _t('<%= $objTable->ClassNamePlural %>'); ?></div>
		<br class="item_divider" />

		<?php $this->dtg<%= $objTable->ClassName %>->Render() ?>
		<br />
		<a href="<%= QConvertNotation::UnderscoreFromCamelCase($objTable->ClassName) %>_edit.php"><?php _t('Create a New'); echo ' '; _t('<%= $objTable->ClassName %>');?></a>
		 &nbsp;|&nbsp;
		<a href="<?php _p(DOCROOT_VIRTUAL_DIRECTORY . DOCROOT_SUBFOLDER) ?>/form_drafts/index.php"><?php _t('Go to "Form Drafts"'); ?></a>

	<?php $this->RenderEnd() ?>
	</body>
</html>