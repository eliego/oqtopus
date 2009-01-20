<h5 class="marginheader">Lägg bud</h5>
<br />
<table class="TioPix">
	<tr>
		<td class="tdAuto"><font><b>Annonsen ska publiceras: </b></font></td>		
		<td class="tdAuto"><?php $_CONTROL->ParentControl->dtpBidPublicationDate->RenderWithError(); ?><br /></td>
	</tr>
	<tr>
		<td class="tdAuto"><font><b>Svara mig senast: </b></font><br /></td>
		<td class="tdAuto"><?php $_CONTROL->ParentControl->dtpBidDeadline->RenderWithError(); ?></td>
	</tr>
	<tr>
		<td class="tdAuto"><font><b>Jag erbjuder: </b></font></td>
		<td class="tdAuto"><?php $_CONTROL->ParentControl->txtBidAmount->RenderWithError(); ?><br /></td>
	</tr>
	<tr>
	<td class="tdAuto"></td>
	<td class="tdAuto"><font class="TioPix">Totalt: <?php $_CONTROL->ParentControl->txtBidTotal->Render(); ?> 
SEK varav moms <?php $_CONTROL->ParentControl->txtBidTax->Render(); ?> SEK<br /><br /><i>Vissa organisationsmedier <br />
																					med mera är momsfria att<br /> 
																					annonsera i.</i></font></td>
	</tr>
</table>
<br /><br />
<?php $_CONTROL->ParentControl->lblBidInfo->Render(); $_CONTROL->ParentControl->lblName->Render(); $_CONTROL->ParentControl->lblPrice->Render(); ?>
<div class="PanelMakeBid">	<?php $_CONTROL->ParentControl->btnBidOk->Render(); $_CONTROL->ParentControl->btnBidCancel->Render(); ?></div>
