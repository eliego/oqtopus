<div class="vanstertext">
<h5 class="marginheader">Kreditupplysningar</h5>
<br />	
<font class="TioPix">Oqtopus genomför <b>kredit- upplysningar</b> på alla företag som deltar i budgivningen på annonser.  
<br /><br />

Alla bud på Oqtopus.se är <b>bindande</b>.
<br /><br />
När ett bud accepterats är det <b>säljarens</b> uppgift att kontakta köparen.  
<br /><br />
 </font>

<h5 class="marginheader">Bud av misstag</h5>
<br />
<font class="TioPix">Om ett bud har lagts av misstag är det viktigt att du kontaktar 
<b><a href="mailto:support@oqtopus.se">supporten</a></b> omedelbart.</font><br /><br />

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

<div class="absolutemain">
<div class="main">
	<h5 class="marginheader">Besvarade sedan senaste inloggning</h5><br/>
		<?php
			$this->dtgNewBids->Render();
		?>
</div>

<div class="main">
	<h5 class="marginheader">Obesvarade</h5><br/>
		<?php
			$this->dtgPendingBids->Render();
		?>
</div>

<div class="main">
	<h5 class="marginheader">Tidigare besvarade</h5><br/>
		<?php
			$this->dtgOldBids->Render();
		?>
</div>

<div class="main">
	<h5 class="marginheader">Förfallna</h5><br/>
		<?php
			$this->dtgExpiredBids->Render();
		?>
</div>

</div>