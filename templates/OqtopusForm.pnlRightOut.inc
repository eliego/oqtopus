<div class="absolutehoger">

<h5 class="marginheader">Registrerade användare</h5>
	<br />
		<font class="hoger">Användarnamn:</font>
		<?php $this->txtOQUsername->RenderWithError(); ?>								
	<br /><br /><br />
		<font class="hoger">Lösenord:</font>
		<br />
		
		<div class="PasswordError"><?php $this->txtOQPassword->RenderWithError(); ?></div><?php $this->btnOQOk->Render(); ?>
	<br /><br /><br /><br />
		<font class="hoger">Kontakta vår <a href="mailto:support@oqtopus.se">support</a> om du glömt ditt lösenord.</font>
	<br /><br />

<h5 class="marginheader">Skapa ny användare</h5>
	<br />			
		<font class="hoger">För att handla på Oqtopus krävs ett medlemskonto, 
		som du kan registrera gratis här nedan.</font><br /><br />
		<?php $this->btnOQRegisterAsSeller->Render(); ?><?php $this->btnOQRegisterAsBuyer->Render(); ?>
					

</div>