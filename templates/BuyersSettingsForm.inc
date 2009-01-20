<div class="absolutemain">
	<div class="main">
		<h5 class="marginheader">Kontaktuppgifter</h5>

		<br/>
		<?php	$this->lblSellerName->Render();	?>
		<br/><br/>
	
	<table class="TioPix">
		<tr>
			<td><?php	$this->lblSellerOrgNr->RenderWithName(); ?><br/><br/></td>
			<td class="tdPanelAd1"></td>
			<td class="tdPanelAd4"><?php	$this->lblInfo->Render(); ?></td>
		</tr>

	<tr>
		<td class="tdPanelAd4"><?php	$this->txtSellerContactName->RenderWithName(); ?></td>
		<td class="tdPanelAd4"><?php	$this->txtSellerContactPhone->RenderWithName(); ?></td>
		<td class="tdPanelAd4"><?php	$this->txtSellerContactEmail->RenderWithName(); ?></td>
	</tr>
	<tr>
		<td class="tdPanelAd4"><?php	$this->txtSellerContactAdress->RenderWithName(); ?></td>
		<td class="tdPanelAd4"><?php $this->txtSellerContactPostal->RenderWithname(); ?></td>
		<td class="tdPanelAd1"><?php $this->txtSellerContactCity->RenderWithName(); ?></td>
	</tr>	
</table>

	<div class="EditSellerInfo"><?php	$this->btnCancelEditSellerInfo->Render(); $this->btnDoEditSellerInfo->Render(); ?></div>

</div>

<div class="main">
	 <h5 class="marginheader">Ändra lösenord</h5>
<br />
<table class="TioPix">
	<tr>
		<td class="tdPanelAd4"><?php	$this->txtOldPass->RenderWithName();	?></td>
		<td class="tdPanelAd4"><?php	$this->txtNewPass->RenderWithName();	?></td>
		<td class="tdPanelAd4"><?php	$this->txtNewPass2->RenderWithName();	?></td>
		<td class="tdPanelAd4"><?php	$this->lblPassInfo->Render();	?></td>		
	</tr>
</table>
<div class="ChangePass"><?php	$this->btnDoChangePass->Render();	?></div>
</div>

</div>


<div class="vanstertext">
	<h5 class="marginheader">Lösenord mm</h5>
		<br />	
		<font class="TioPix">Tänk på att flera åtgärder på Oqtopus är <b>juridiskt</b> och <b>ekonomiskt bind- ande</b>. 
		Var därför försiktig med vilka som får tillgång till kontouppgifterna.<br/><br/>
		
		Kontakta <b><a href="mailto:support@oqtopus.se">supporten</a></b> 
		omgående om du misstänker att kontot har missbrukats.</font>

<br/><br/>
<h5 class="marginheader">Kontakt</h5>
<br/>

<font class="TioPix">
<b>Oqtopus</b><br>
S:t Eriksgatan 63<br/>
Box 8069 <br/>
104 20 Stockholm<br><br>

<b>Växel:</b> 08-545 285 80<br/>
<b>Fax:</b> 08-545 285 81<br/>
<b>Mejl:</b> <a href="mailto:support@oqtopus.se">support@oqtopus.se</a>
</font>


</div>

