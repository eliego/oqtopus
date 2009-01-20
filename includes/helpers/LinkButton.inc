<?php
	class LinkButton extends QLinkButton {
		public function Render($bln) {
			if ($bln) {
				echo parent::GetControlHtml();
			} else 
				return parent::GetControlHtml();
		}
	}
?>