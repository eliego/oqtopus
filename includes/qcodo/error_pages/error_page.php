<?php
	/*
	 * error_page include file
	 * 
	 * expects the following variables to be set:
	 *	$__exc_strType
	 *	$__exc_strMessage
	 *	$__exc_strObjectType
	 *	$__exc_strFilename
	 *	$__exc_intLineNumber
	 *	$__exc_strStackTrace
	 *
	 * optional:
	 *	$__exc_strRenderedPage
	 *  $__exc_objErrorAttributeArray
	 */

	$__exc_strMessageBody = htmlentities($__exc_strMessage, ENT_COMPAT, QApplication::$EncodingType);
	$__exc_strMessageBody = str_replace(" ", "&nbsp;", str_replace("\n", "<br />\n", $__exc_strMessageBody));
	$__exc_strMessageBody = str_replace(":&nbsp;", ": ", $__exc_strMessageBody);
	$__exc_objFileArray = file($__exc_strFilename);
?>
<html>
	<head>
		<title>PHP <?php print($__exc_strType); ?> - <?php print(htmlentities($__exc_strMessage, ENT_COMPAT, QApplication::$EncodingType)); ?></title>
		<style>
			body { font-family: 'Arial' 'Helvetica' 'sans-serif'; font-size: 11px; }
			a:link, a:visited { text-decoration: none; }
			a:hover { text-decoration: underline; }
			pre { font-family: 'Lucida Console' 'Courier New' 'Courier' 'monospaced'; font-size: 11px; line-height: 13px; }
			.page { padding: 10px; }
			.headingLeft { background-color: #440066; color: #ffffff; padding: 10px 0px 10px 10px; font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif'; font-size: 18px; font-weight: bold; width: 70%; vertical-align: middle; }
			.headingLeftSmall { font-size: 10px; }
			.headingRight { background-color: #440066; color: #ffffff; padding: 0px 10px 10px 10px; font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif'; font-size: 10px; width: 30%; vertical-align: middle; text-align: right; }
			.title { font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif'; font-size: 19px; font-style: italic; color: #330055; }
			.code { background-color: #f4eeff; padding: 1px 10px 1px 10px; }
		</style>
		<script type="text/javascript">
			function RenderPage(strHtml) { document.rendered.strHtml.value = strHtml; document.rendered.submit(); }
			function ToggleHidden(strDiv) { var obj = document.getElementById(strDiv); var stlSection = obj.style; var isCollapsed = obj.style.display.length; if (isCollapsed) stlSection.display = ''; else stlSection.display = 'none'; }
		</script>
	</head>
	<body bgcolor="white" topmargin="0" leftmargin="0" marginheight="0" marginwidth="0"> 

	<table border="0" cellspacing="0" width="100%">
		<tr>
			<td nowrap="nowrap" class="headingLeft"><span class="headingLeftSmall"><?php echo $__exc_strType; ?> in PHP Script<br /></span><?php echo $_SERVER["PHP_SELF"]; ?></div></td>
			<td nowrap="nowrap" class="headingRight">
				<b>PHP Version:</b> <?php echo phpversion(); ?>;&nbsp;&nbsp;<b>Zend Engine Version:</b> <?php echo zend_version(); ?>;&nbsp;&nbsp;<b>Qcodo Version:</b> <?php echo QCODO_VERSION; ?><br />
				<?php if (array_key_exists('OS', $_SERVER)) printf('<b>Operating System:</b> %s;&nbsp;&nbsp;', $_SERVER['OS']); ?><b>Application:</b> <?php echo $_SERVER['SERVER_SOFTWARE']; ?>;&nbsp;&nbsp;<b>Server Name:</b> <?php echo $_SERVER['SERVER_NAME']; ?><br />
				<b>HTTP User Agent:</b> <?php echo $_SERVER['HTTP_USER_AGENT']; ?></td>
		</tr>
	</table>
	
	<div class="page">
		<span class="title"><?php echo $__exc_strMessageBody; ?></span><br />
		<form method="post" action="<?php echo DOCROOT_VIRTUAL_DIRECTORY . DOCROOT_SUBFOLDER ?>/includes/qcodo/error_pages/rendered_page.php" target="blank" name="rendered"><input type="hidden" name="strHtml" value=""></form>

			<b><?php echo  $__exc_strType; ?> Type:</b>&nbsp;&nbsp;
			<?php echo $__exc_strObjectType; ?>
			<br /><br />

<?php
			if (isset($__exc_strRenderedPage)) {
?>
				<script type="text/javascript">RenderedPage = "<?php print(PrepDataForScript($__exc_strRenderedPage)); ?>";</script>
				<b>Rendered Page:</b>&nbsp;&nbsp;
				<a href="javascript:RenderPage(RenderedPage)">Click here</a> to view contents able to be rendered</a>
				<br /><br />
<?php
			}
?>
			<b>Source File:</b>&nbsp;&nbsp;
			<?php echo ($__exc_strFilename); ?>
			&nbsp;&nbsp;&nbsp;&nbsp;<b>Line:</b>&nbsp;&nbsp;
			<?php echo ($__exc_intLineNumber); ?>
			<br /><br />

			<div class="code">
<?php
						print('<pre>');
						for ($__exc_intLine = max(1, $__exc_intLineNumber - 5); $__exc_intLine <= min(count($__exc_objFileArray), $__exc_intLineNumber + 5); $__exc_intLine++) {
							if ($__exc_intLineNumber == $__exc_intLine)
								printf("<font color=red>Line %s:    %s</font>", $__exc_intLine, htmlentities($__exc_objFileArray[$__exc_intLine - 1], ENT_COMPAT, QApplication::$EncodingType));
							else
								printf("Line %s:    %s", $__exc_intLine, htmlentities($__exc_objFileArray[$__exc_intLine - 1], ENT_COMPAT, QApplication::$EncodingType));
						}
						print('</pre>');
?>
			</div><br />
			
<?php
			if (isset($__exc_objErrorAttributeArray))
				foreach ($__exc_objErrorAttributeArray as $__exc_objErrorAttribute) {
					printf("<b>%s:</b>&nbsp;&nbsp;", $__exc_objErrorAttribute->Label);
					$__exc_strJavascriptLabel = str_replace(" ", "", $__exc_objErrorAttribute->Label);
					if ($__exc_objErrorAttribute->MultiLine) {
						printf("\n<a href=\"javascript:ToggleHidden('%s')\">Show/Hide</a>",
							$__exc_strJavascriptLabel);
						printf('<br /><br /><div id="%s" class="code" style="Display: none;"><pre>%s</pre></div><br />',
							$__exc_strJavascriptLabel,
							htmlentities($__exc_objErrorAttribute->Contents, ENT_COMPAT, QApplication::$EncodingType));
					} else
						printf("%s\n<br /><br />\n", htmlentities($__exc_objErrorAttribute->Contents, ENT_COMPAT, QApplication::$EncodingType));
				}
?>

			<b>Call Stack:</b>
			<br><br>
			<div class="code">
				<pre><?php echo $__exc_strStackTrace; ?></pre>
			</div><br />

			<b>Variable Dump:</b>&nbsp;&nbsp;
			<a href="javascript:ToggleHidden('VariableDump')">Show/Hide</a>
			<br /><br />
			<div id="VariableDump" class="code" style="Display: none;">
<?php
				print('<pre>');

				// Dump All Variables
				foreach ($GLOBALS as $__exc_Key => $__exc_Value) {
					// TODO: Figure out why this is so strange
					if (isset($__exc_Key))
						if ($__exc_Key != "_SESSION")
							global $$__exc_Key;
				}

				$__exc_ObjVariableArray = get_defined_vars();
				$__exc_ObjVariableArrayKeys = array_keys($__exc_ObjVariableArray);
				sort($__exc_ObjVariableArrayKeys);

				$__exc_StrToDisplay = "";
				$__exc_StrToScript = "";
				foreach ($__exc_ObjVariableArrayKeys as $__exc_Key) {
					if ((strpos($__exc_Key, "__exc_") === false) && (strpos($__exc_Key, "_DATE_") === false) && ($__exc_Key != "GLOBALS") && !($__exc_ObjVariableArray[$__exc_Key] instanceof QForm)) {
						try {
							if (($__exc_ObjVariableArray[$__exc_Key] instanceof QControl) || ($__exc_ObjVariableArray[$__exc_Key] instanceof QForm))
								$__exc_StrVarExport = htmlentities($__exc_ObjVariableArray[$__exc_Key]->VarExport(), ENT_COMPAT, QApplication::$EncodingType);
							else
								$__exc_StrVarExport = htmlentities(var_export($__exc_ObjVariableArray[$__exc_Key], true), ENT_COMPAT, QApplication::$EncodingType);

							$__exc_StrToDisplay .= sprintf("  <a href=\"javascript:RenderPage(%s)\" title=\"%s\">%s</a>\n", $__exc_Key, $__exc_StrVarExport, $__exc_Key);
							$__exc_StrToScript .= sprintf("  %s = \"<pre>%s</pre>\";\n", $__exc_Key, PrepDataForScript($__exc_StrVarExport));
						} catch (Exception $__exc_objExcOnVarDump) {
							$__exc_StrToDisplay .= sprintf("  Fatal error:  Nesting level too deep - recursive dependency?\n", $__exc_objExcOnVarDump->Message);
						}
					}
				}

				print $__exc_StrToDisplay;
				print ('</pre>');
				printf('<script type="text/javascript">%s</script>', $__exc_StrToScript);
?>
			</diV><br />

			<hr width="100%" size="1" color="#dddddd" />
			<center><i><?php echo $__exc_strType; ?> Report Generated:&nbsp;&nbsp;<?php echo date('l, F j Y, g:i:s A'); ?></i></center>
		</font>
	</div>
	</body>
</html>