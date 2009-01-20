<h5 class="marginheaderAdPanel">Information om nätverket </h5>
<br />
	<table class="TioPix">
		<tr>
			<td class="tdPanelAd4"><?php	$_CONTROL->lblName->Render();	?></td>
			<td class="tdAuto"><div class="desc"><?php	$_CONTROL->lblDescription->Render();	?></div></td>
		</tr>
	</table>

<table class="TioPix">
	<tr>
		<td class="tdPanelAd4"><?php	$_CONTROL->dtgAssociations->Render();	?></td>
	</tr>
</table>	
<div class="CloseNonEditNetworkPanelBtn"><?php	$_CONTROL->btnEditNetwork->Render(); $_CONTROL->btnRemove->Render(); $_CONTROL->btnNetworkClose->Render(); ?></div>
