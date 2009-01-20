<div class="vanstertext">
	<h5 class="marginheader">Kom igång</h5>
		<br />
			
			<font class="TioPix"><b>Hej</b> och välkommen som säljare på Oqtopus. <br><br>	
			Bästa sättet att komma igång är att läsa våra 
			<b><a href="<?php print Navigation::CreateUrl('SellersNewsForm');?>">demofiler</a></b> 
			för säljare. </font><br/><br/>

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

<h5 class="marginheader">Senaste nytt</h5><br/>

<b>Länk: </b><a class="hover" href="<?php print Navigation::CreateUrl('PressForm');?>">Nyheter</a><br/>

<b>Länk: </b><a class="hover" href="<?php print Navigation::CreateUrl('SellersBidsForm');?>"><?php $this->lblBids->Render(); ?>&nbsp;obesvarade bud</a><br/>

<b>Länk: </b><a class="hover" href="<?php print Navigation::CreateUrl('SellersNetworksForm');?>"><?php $this->lblNetworkApplications->Render() ?>&nbsp;ansökningar till kampanjnätverk </a><br/><br/>
<br />

<b>Saldo: </b> Innestånde provision <?php $this->lblDebt->Render() ?>&nbsp;kr.<br/>
<i>En faktura skickas ut när provisionen når 500 kronor.</i>
</div>

</div>