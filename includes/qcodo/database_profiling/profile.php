<?php
	/* Qcodo Development Framework for PHP
	 * http://www.qcodo.com/
	 * 
	 * The Qcodo Development Framework is distributed by QuasIdea Development, LLC
	 * under the terms of The MIT License.  More information can be found at
	 * http://www.opensource.org/licenses/mit-license.php
	 * 
	 * Copyright (c) 2001 - 2006, QuasIdea Development, LLC
	 * 
	 * Permission is hereby granted, free of charge, to any person obtaining a copy of
	 * this software and associated documentation files (the "Software"), to deal in
	 * the Software without restriction, including without limitation the rights to
	 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	 * of the Software, and to permit persons to whom the Software is furnished to do
	 * so, subject to the following conditions:
	 * 
	 * The above copyright notice and this permission notice shall be included in all
	 * copies or substantial portions of the Software.
	 * 
	 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	 * SOFTWARE.
	 */

	require('../../prepend.inc');
	$intDatabaseIndex = $_POST['intDatabaseIndex'];
	$strProfileData = $_POST['strProfileData'];
	$strReferrer = $_POST['strReferrer'];
	
	$objProfileArray = unserialize(base64_decode($strProfileData));
	$objProfileArray = QType::Cast($objProfileArray, QType::ArrayType);
	if ((count($objProfileArray) % 2) != 0)
		throw new Exception('Database Profiling data appears to have been corrupted.');
?>
<html>
	<head>
		<title>Qcodo Development Framework - Database Profiling Tool</title>
		<style>
			body { font-family: 'Arial' 'Helvetica' 'sans-serif'; font-size: 14px; }
			a:link, a:visited { text-decoration: none; }
			a:hover { text-decoration: underline; }

			pre { font-family: 'Lucida Console' 'Courier New' 'Courier' 'monospaced'; font-size: 11px; line-height: 13px; }
			.page { padding: 10px; }

			.headingLeft {
				background-color: #446644;
				color: #ffffff;
				padding: 10px 0px 10px 10px;
				font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif';
				font-size: 18px;
				font-weight: bold;
				width: 70%;
				vertical-align: middle;
			}
			.headingLeftSmall { font-size: 10px; }
			.headingRight {
				background-color: #446644;
				color: #ffffff;
				padding: 0px 10px 10px 10px;
				font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif';
				font-size: 10px;
				width: 30%;
				vertical-align: middle;
				text-align: right;
			}
			.title { font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif'; font-size: 19px; font-style: italic; color: #330055; }
			.code { background-color: #f4eeff; padding: 1px 10px 1px 10px; }
			
			.function { font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif'; font-size: 12px; font-weight: bold; }
			.function_details { font-family: 'Verdana' 'Arial' 'Helvetica' 'sans-serif'; font-size: 10px; color: #777777; }
		</style>
		<script type="text/javascript">
			function Toggle(spanId) {
				var obj = document.getElementById(spanId);

				if (obj) {
					if (obj.style.display == "block") {
						// Make INVISIBLE
						obj.style.display = "none";
					} else {
						// Make VISIBLE
						obj.style.display = "block";
					}
				}
			}
			
			function ShowAll() {
				for (var intIndex = 1; intIndex < <?php echo count($objProfileArray) ?>; intIndex = intIndex + 2) {
					var obj = document.getElementById('query' + intIndex);
					obj.style.display = "block";
				}
			}
			
			function HideAll() {
				for (var intIndex = 1; intIndex < <?php echo count($objProfileArray) ?>; intIndex = intIndex + 2) {
					var obj = document.getElementById('query' + intIndex);
					obj.style.display = "none";
				}
			}
		</script>
	</head>
	<body topmargin="0" leftmargin="0" marginheight="0" marginwidth="0"> 

		<table border="0" cellspacing="0" width="100%">
			<tr>
				<td nowrap="nowrap" class="headingLeft"><span class="headingLeftSmall">Qcodo Development Framework <?= QCODO_VERSION ?><br /></span>Database Profiling Tool</div></td>
				<td nowrap="nowrap" class="headingRight">
					<b>Database Index:</b> <?php echo $intDatabaseIndex ?>;&nbsp;&nbsp;<b>Database Type:</b> <?php echo QApplication::$ConnectionStringArray[$intDatabaseIndex]['adapter'] ?><br />
					<b>Database Server:</b> <?php echo QApplication::$ConnectionStringArray[$intDatabaseIndex]['server'] ?>;&nbsp;&nbsp;<b>Database Name:</b> <?php echo QApplication::$ConnectionStringArray[$intDatabaseIndex]['database'] ?><br />
					<b>Profile Generated From:</b> <?php echo $strReferrer ?>
				</td>
			</tr>
		</table><br />

		<div class="page">

			<b>There were <?php echo count($objProfileArray) / 2 ?> queries that were performed.</b>
			<br />
			<a href="javascript: ShowAll()" class="function_details">Show All</a>
			 &nbsp;&nbsp;|&nbsp;&nbsp; 
			<a href="javascript: HideAll()" class="function_details">Hide All</a>
			<br /><br /><br />
<?php
			for ($intIndex = 0; $intIndex < count($objProfileArray); $intIndex++) {
				$objDebugBacktrace = $objProfileArray[$intIndex][2];
				$intIndex++;
				$strQuery = $objProfileArray[$intIndex];

				$objArgs = (array_key_exists('args', $objDebugBacktrace)) ? $objDebugBacktrace['args'] : array();
				$strClass = (array_key_exists('class', $objDebugBacktrace)) ? $objDebugBacktrace['class'] : null;
				$strType = (array_key_exists('type', $objDebugBacktrace)) ? $objDebugBacktrace['type'] : null;
				$strFunction = (array_key_exists('function', $objDebugBacktrace)) ? $objDebugBacktrace['function'] : null;
				$strFile = (array_key_exists('file', $objDebugBacktrace)) ? $objDebugBacktrace['file'] : null;
				$strLine = (array_key_exists('line', $objDebugBacktrace)) ? $objDebugBacktrace['line'] : null;

				for ($intArgIndex = 0; $intArgIndex < count($objArgs); $intArgIndex++) {
					$objArgs[$intArgIndex] = sprintf("'%s'", $objArgs[$intArgIndex]);
				}
?>
				<span class="function">
					Called by <?php echo $strClass . $strType . $strFunction . '(' . implode(', ', $objArgs) . ')' ?>
				</span>
				 &nbsp;&nbsp;|&nbsp;&nbsp; 
				<a href="javascript: Toggle('query<?php echo $intIndex ?>')" class="function_details">Show/Hide</a>
				<br />
				<span class="function_details"><b>File: </b><?php echo $strFile ?>; &nbsp;&nbsp;<b>Line: </b><?php echo $strLine ?>
				</span><br />
				<div class="code" id="query<?php echo $intIndex; ?>" style="display: none"><pre><?php echo $strQuery ?></pre></div>
				<br /><br />
<?php
			}
?>

		</div>
	</body>
</html>