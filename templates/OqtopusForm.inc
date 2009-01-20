<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>

<head>
<title>OQTOPUS</title>

<link href="/adds/<?php echo($this->CssFile); ?>" rel="stylesheet" type="text/css"/>

<META name="verify-v1" content="rKh4QaQzfJeKjrP0qIuTlPscIHS+h91jfLaz8XRqPAk=" />

</head>
<body>

<?php $this->RenderBegin(); ?>
<div id="box"> 


<a href="<?php print Navigation::HomeUrl();?>"><div id="symbol"></div></a>
 
  
<div id="meny1">
    <ul id="meny1">
     
	 <li><a href="<?php print Navigation::CreateUrl('AboutCompanyForm');?>"> Om företaget</a></li> 
	 <li><a href="<?php print Navigation::CreateUrl('PressForm');?>">Press</a></li> 
	 <li><a href="<?php print Navigation::CreateUrl('CustomerForm');?>">Kunder</a></li>
	 <li><a href="<?php print Navigation::CreateUrl('ContactForm');?>">Kontakt</a></li>
            
    </ul>
  </div>



 

    <?php $this->mcMenu->Render(); ?>


<div class="vanster"> 

<?php $this->RenderInnerPage(); ?>
</div>


<div class="hoger"><?php $this->pnlRightOut->Render(); $this->pnlRightIn->Render(); ?>
</div>

</div>
<?php $this->RenderEnd(); ?>
</body>

	<script src="http://www.google-analytics.com/urchin.js" type="text/javascript"></script>
	
	<script type="text/javascript">
		_uacct = "UA-799885-2";
		urchinTracker();
	</script>


</html>