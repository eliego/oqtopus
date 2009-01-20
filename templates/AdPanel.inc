<h5 class="marginheaderAdPanel">Information om annonsen</h5>
<br />
<?php $_CONTROL->pnlMakeBid->Render(); ?>		
	<table class="TioPix">
		<tr>
			<td class="tdAuto"><?php $_CONTROL->lblAdName->Render(); ?></td>
			<td class="tdWidth"></td>		
			<td class="tdAuto"><div class="desc"><?php $_CONTROL->pnlAdDesc->Render(); ?></div></td>
		</tr>
	</table>
	
	<table class="TioPix">
		<tr>
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdType->RenderWithName(); ?></td>
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdArea->RenderWithName(); ?></td>
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdReach->RenderWithName(); ?></td>
		</tr>
		<tr>
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdSex->RenderWithName();  ?></td>
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdPrice->RenderWithName(); ?></td>
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdAges->RenderWithName(); ?></td>
		</tr
		<tr>
			<td class="tdPanelAd4"><?php $_CONTROL->pnlAdEducations->RenderWithName(); ?></td>
			<td class="tdPanelAd4"><?php $_CONTROL->pnlAdSectors->RenderWithname(); ?></td>
			<td class="tdPanelAd4"><?php $_CONTROL->pnlAdSalaries->RenderWithName(); ?></td>
		</tr>
		<tr>	
			<td class="tdPanelAd4"><?php $_CONTROL->pnlAdKeywords->RenderWithName(); ?></td>	
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdDeadline->RenderWithName(); ?></td>
			<td class="tdPanelAd4"><?php $_CONTROL->lblAdPublication->RenderWithName(); ?></td>
		</tr>
	</table>
<div class="CloseAdPanelBtn"><?php $_CONTROL->btnMakeBid->Render(); $_CONTROL->btnAdClose->Render(); ?></div>