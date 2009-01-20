<?php

class AuthenticationException extends Exception {
    private $iError;
    
    public function __construct($strMess, $iError) {
        parent::__construct($strMess);
        $this->iError = $iError;
    }
    
    public function __get($strName) {
        switch ($strName) {
            case "ErrorCause":
                return $this->iError;
            
            default:
                $r = new ReflectionClass($this);
                throw new QUndefinedPropertyException("GET", $r->getName(), $strName);
                break;
        }
    }
}
?>