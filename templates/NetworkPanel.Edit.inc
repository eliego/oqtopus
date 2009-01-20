<h5 class="marginheaderAdPanel">Inställningar - Kampanjnätverk </h5>
<table class="TioPix">
	<tr>
		<td class="tdPanelAd4"><?php	$_CONTROL->txtName->RenderWithName();	?></td>
		<td class="tdPanelAd4"><?php	$_CONTROL->txtDescription->RenderWithName();	?></td>
	</tr>
</table>

<?php	$_CONTROL->dtgAssociations->Render();	?>
<div class="CloseEditNetworkPanelBtn">
		<?php	$_CONTROL->btnNetworkOk->Render(); 
		$_CONTROL->btnNetworkCancel->Render(); ?>
	</div>
<br />