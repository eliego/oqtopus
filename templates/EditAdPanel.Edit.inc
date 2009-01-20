<h5 class="marginheaderAdPanel">Annonsspecifikation</h5>

<br/>

<table class="TioPix">
	<tr>
		
		<td class="tdPanelAd4"><?php $_CONTROL->txtAdName->RenderWithName(); ?>
		<br/><br/><?php $_CONTROL->txtAdDesc->RenderWithName(); ?><br/><br/><?php $_CONTROL->rblPermissions->RenderWithName(); echo('<br>'); $_CONTROL->mlbPermissions->Render(); ?></td>
							
		<td class="tdPanelAd4"><?php $_CONTROL->lbAdType->RenderWithName();
		echo('<br><br>');  $_CONTROL->lbAdSubType->Render(); ?>
		<br/><br/><br/><?php $_CONTROL->rlbAdArea->RenderWithName(); echo('<br><br>');
		 						$_CONTROL->rlbAdSubArea->RenderWithName(); echo('<br><br>');
		 						$_CONTROL->rlbAdSubSubArea->RenderWithName(); ?></td>

		
		
		<td class="tdPanelAd4"><?php $_CONTROL->txtAdReach->RenderWithName(); ?>
		<br/><br/><br/><?php $_CONTROL->txtAdPrice->RenderWithName(); ?>
		<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
		<?php $_CONTROL->dtpAdPublication->RenderWithName() ?>
		<br/><br/><?php $_CONTROL->dtpAdDeadline->RenderWithName(); ?></td>
</tr>
</table>

<h5 class="marginheaderAdPanel">Målgruppsspecifikation</h5>
<br />
<table class="TioPix">
	<tr>
		<td class="tdPanelAd4"><?php $_CONTROL->txtAdAgeFrom->RenderWithName(); echo(' - '); $_CONTROL->txtAdAgeTo->RenderWithError(); ?></td>
		<td class="tdPanelAd4"><?php $_CONTROL->rblAdSex->RenderWithName();  ?></td>
		</tr>
</table>

<table class="TioPix">
	<tr>
		<td class="tdAuto"><?php $_CONTROL->bmcSalaries->RenderWithName(); ?></td>			
		<td class="tdPanelAd1"></td>
		<td class="tdAuto"><?php $_CONTROL->bmcSectors->RenderWithName(); ?></td>
	</tr>
	<tr>
		<td class="tdAuto"><?php $_CONTROL->bmcEducations->RenderWithName(); ?></td>
		<td class="tdPanelAd1"></td>
		<td class="tdAuto"><?php $_CONTROL->kwcKeywords->RenderWithName(); ?></td>
	</tr>
</table>
<div class="EditAdPanel"><?php $_CONTROL->btnCancelAdEdit->Render(); $_CONTROL->btnDoAdEdit->Render(); ?></div>