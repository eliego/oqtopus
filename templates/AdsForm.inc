<div class="vanstertext">
<h5 class="marginheader">Att tänka på</h5>
<br/>
<font class="TioPix"> <b>Säljaren</b> ansvarar för alla uppgifter om mediet och annonserna. <br/><br/>
<b>Oqtopus</b> kan utan förvarning radera en annons som uppfattas vara missvisande eller felaktig. <br/><br/>
Se <b><a href="<?php echo Navigation::CreateUrl('SellersDemoForm') ?>">demofilmerna</a></b> 
för mer information om reglerna och hur en annons bör fyllas i.</font>
<br/><br/>
<h5 class="marginheader">Kontakt</h5>

<br>
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
<h5 class="marginheader">Tidsspecifika annonser, erbjudanden mm.</h5>

<br />

<table>
	<tr>
		<td> <?php $this->dtgSIMs->Render(); ?><br/></td>
	</tr>
</table>	
<div class="btnAddSim"><?php	$this->btnAddSim->Render(); ?></div>

<table>
	<tr>
		<td> <?php	$this->objEditSim->Render(); ?> </td>
</tr>
</table>	

</div>

<div class="main">
<h5 class="marginheader">Mallar (icke tidsspecifika annonser)</h5>


<br />


<table>	
	<tr>
		<td> <?php $this->dtgAds->Render(); ?><br/>  </td>
	</tr>
</table>
<div class="btnAddAd"><?php	$this->btnAddAd->Render();  ?></div>
<table>
	<tr>
		<td><?php $this->objEditAd->Render(); ?>  </td>
	</tr>
</table>
	
</div>

</div>

<br /><br /><br /><br /><br /><br /><br /><br /><br /><br />