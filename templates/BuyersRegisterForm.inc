<div class="vanstertext">
<h5 class="marginheader">Kontakt</h5><font class="TioPix">
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



<div class="absolutemain">
<div class="main">

<h5 class="marginheader">Registrera säljkonto</h5>
<br/>
<table>
	<tr>
		<td class="tdPanelAd1"><?php	$this->txtUsername->RenderWithName(); ?></td>
		<td class="tdPanelAd1"><?php	$this->txtPassword->RenderWithName(); ?></td>
		<td class="tdPanelAd1"><?php	$this->txtPassword2->RenderWithName(); ?></td>
	</tr>
	<tr>
		<td class="tdPanelAd1"><?php	$this->txtFirstName->RenderWithName(); ?></td>
		<td class="tdPanelAd1"><?php	$this->txtSecondName->RenderWithName(); ?></td>
	    <td class="tdPanelAd1"><?php   $this->txtPhone->RenderWithName(); ?></td>
	</tr>
	<tr>
		<td class="tdPanelAd1"><?php	$this->txtCompanyName->RenderWithName(); ?></td>		
		<td class="tdPanelAd1"><?php	$this->txtOrgNumber->RenderWithName(); ?></td>
	    <td class="tdPanelAd1"><?php  $this->txtEmail->RenderWithName(); ?></td>
	</tr>
</table>


<table>
	<tr>
	<td class="tdPanelAd1"><?php   $this->txtAddress->RenderWithName(); ?></td>
	<td class="tdPanelAd1"><?php   $this->txtPostal->RenderWithName(); ?></td>
	<td class="tdPanelAd1"><?php   $this->txtCity->RenderWithName(); ?></td>
	</tr>
</table>
<?php   echo('<br>'); $this->btnOk->RenderWithName();	?>

<br/>
<?php $this->lblInfo->Render(); ?>
</div>

</div>