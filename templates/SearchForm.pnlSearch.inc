<div class="absolutesearch">

<h5 class="marginheader">Sök</h5>
<?php
$this->txtKeyword->Render();
$this->btnOk->Render();
$this->lblMediaHeader->Render();
$this->lbMediaType->RenderWithName();
$this->lbMediaSubType->RenderWithName();
$this->rlbArea->RenderWithName();
$this->rlbSubArea->RenderWithName();
$this->rlbSubSubArea->RenderWithName();

$this->txtReach->RenderWithName();
$this->lbReachMode->RenderWithName(); 

$this->txtPrice->RenderWithName();
$this->lbPriceMode->Render();

$this->lblConsumerHeader->Render();

$this->txtAge->RenderWithName();
$this->lbSex->RenderWithName();

$this->lbEducation->RenderWithName();
$this->lbSector->RenderWithName();
$this->lbSalary->RenderWithName();

$this->cblSendEmail->RenderWithName();

?>

</div>