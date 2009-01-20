
<div class="absolutemain">
<div class="main">
	<h5 class="marginheader">Tidsspecifika annonser, erbjudanden mm.</h5>
		<?php echo('<br>'); $this->dtgSIMs->Render(); echo('<br>'); ?>
		<?php $this->objSimPnl->Render(); ?>
</div>


<div class="main">
	<h5 class="marginheader">Mallar (icke tidsspecifika annonser)</h5>
		<?php $this->dtgAds->Render(); echo('<br><br>'); ?>
		<?php $this->objAdPnl->Render() ?>
</div>

<div class="main">
	<h5 class="marginheader">Kontaktinformation</h5><br /><br />
		<?php $this->lblSellerName->Render() ?>
		<?php $this->pnlSellerInfo->Render(); ?>
</div>

</div>

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

<br/>
	<?php $this->pnlNetwork->Render();?>

</div>
