<?php
	require(sprintf('%sphpmailer/class.phpmailer.php', __INCLUDES__));
	abstract class Mail {
		public static function SendMail($objTo, $objFrom, $strSubject, $strBody) {
			$objMail = new PHPMailer();
			$objMail->IsSMTP();
			$objMail->Host = OQTOPUS_MAIL_SMTP_HOST;
			$objMail->From = OQTOPUS_MAIL_FROM_EMAIL;
			$objMail->FromName = $objFrom ? $objFrom->CompanyName : OQTOPUS_MAIL_FROM_NAME;
			if ($objTo instanceof Login)
				$objMail->AddAddress($objTo->Email, $objTo->CompanyName);
			elseif ($objTo instanceof Seller)
				$objMail->AddAddress($objTo->Email, $objTo->SellerName);
			else 
				$objMail->AddAddress($objTo);
			$objMail->Subject = utf8_decode($strSubject);
			$objMail->Body = utf8_decode($strBody);
			
			if (!$objMail->Send())
				throw new Exception("Couldn't send email: ".$objMail->ErrorInfo);
		}
		
		public static function SendNewSearchResult(Search $objSearch) {
			$strMail = 'Hej,

Ett nytt objekt har identifierats på din sökning %s. För att kunna lägga ett bud på objektet måste du logga in på www.oqtopus.se.

 
Väl mött!

Oqtopus
www.oqtopus.se';
		
		$strMail = sprintf($strMail, $objSearch->Name);
		
		self::SendMail($objSearch->Login, null, 'Nytt sökresultat', $strMail);
		}
		
		public static function SendActivationMail(Login $objLogin, $strPass) {
			$strMail = "Hej och välkommen som medlem hos Oqtopus!

För att aktivera detta konto, klicka på länken nedan, eller kopiera den och klista in i din webbläsares adressrad:
http://www.oqtopus.se/ActivateForm/%s/%s


Ditt användarnamn är: %s
Ditt lösenord är: %s

Spara dessa uppgifter! Ditt lösenord kommer aldrig mer visas i klartext.

Är det inte du själv som registrerat dig, eller om du bara vill veta mer om Oqtopus,
är du mer än välkommen att kontakta oss på support@oqtopus.se .

Väl mött!

Oqtopus
www.oqtopus.se";
			
			$strMail = sprintf($strMail, $objLogin->Username, $objLogin->Notes, $objLogin->Username, $strPass);
			
			self::SendMail($objLogin, null, 'Aktivera ditt Oqtopus-konto', $strMail);
		}
		
		public static function SendExceptionMail(Exception $e, $intId) {
			$__exc_objReflection = new ReflectionObject($__exc_objException);

			$__exc_strType = "Exception";
			$__exc_strMessage = $__exc_objException->getMessage();
			$__exc_strObjectType = $__exc_objReflection->getName();

			if ($__exc_objException instanceof QDatabaseExceptionBase) {
				$__exc_objErrorAttribute = new QErrorAttribute("Database Error Number", $__exc_objException->ErrorNumber, false);
				$__exc_objErrorAttributeArray[0] = $__exc_objErrorAttribute;

				if ($__exc_objException->Query) {
					$__exc_objErrorAttribute = new QErrorAttribute("Query", $__exc_objException->Query, true);
					$__exc_objErrorAttributeArray[1] = $__exc_objErrorAttribute;
				}
			}

			$__exc_strFilename = $__exc_objException->getFile();
			$__exc_intLineNumber = $__exc_objException->getLine();
			$__exc_strStackTrace = trim($__exc_objException->getTraceAsString());
		
			$__exc_strMessageBody = htmlentities($__exc_strMessage, ENT_COMPAT, QApplication::$EncodingType);
			$__exc_strMessageBody = str_replace(" ", "&nbsp;", str_replace("\n", "<br />\n", $__exc_strMessageBody));
			$__exc_strMessageBody = str_replace(":&nbsp;", ": ", $__exc_strMessageBody);
			$__exc_objFileArray = file($__exc_strFilename);
		
			$data = sprintf("Message: %s\n\nName: %s\n\nFile: %s\n\nLine: %d\n\n\nTrace:\n%s",
							 $__exc_strMessage, $__exc_strObjectType, $__exc_strFilename, $__exc_intLineNumber, $__exc_strStackTrace);
							 
			self::SendMail(OQTOPUS_EXCEPTION_MAIL, null, $intId, $data);				 
		}
		
		public static function SendBidMail(Bid $objBid) {$str = 'Hej!
Ett nytt bud har lagts på annonsen %s. För att besvara det ber vi dig logga in på www.oqtopus.se och navigera till "BUD".
 
Väl mött!

Oqtopus
www.oqtopus.se';
		
		$strMail = sprintf($str, $objBid->Ad->Name);
		
		self::SendMail($objBid->Ad->Seller, null, 'Nytt bud på annons', $strMail);
		}
		
		public static function SendAppMail(NetworkUser $objNU) {
			$str = 'Hej!
En ny ansökan har kommit in för %s.  För att besvara det ber vi dig gå in på www.oqtopus.se och navigera till "Kampanjnätverk".
 
Väl mött!

Oqtopus
www.oqtopus.se';
			
			$strMail = sprintf($str, $objNU->Network->Name);
			
			self::SendMail($objNU->Login, null, 'Ny ansökan till kampanjnätverk', $strMail);
		}
	}
?>