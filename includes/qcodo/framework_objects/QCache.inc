<?php
	class QCache extends QBaseClass {
		public static $CachePath;

		protected $strNamespace;
		protected $strKey;
		protected $strExtension;
		protected $strCheckFilesArray;

		public function __construct($strNamespace, $strKey, $strExtension = 'txt', $mixCheckFiles = null) {
			$this->strNamespace = trim(strtolower($strNamespace));
			$this->strKey = md5(trim(strtolower($strKey)));
			$this->strExtension = trim(strtolower($strExtension));

			if (is_array($mixCheckFiles))
				$this->strCheckFilesArray = $mixCheckFiles;
			else if ($mixCheckFiles)
				$this->strCheckFilesArray = array($mixCheckFiles);
			else
				$this->strCheckFilesArray = array();
		}

		public function GetData() {
			// First, ensure that the cache file exits
			if (file_exists($this->GetFilePath())) {
				
				// Now, get the current md5 of the checkfiles
				$strMd5 = $this->GetCheckFilesMd5();

				// If No CheckFiles, the delete cache file and return false
				if ($strMd5 === false) {
					unlink($this->GetFilePath());
					return false;
				}
				
				// If MD5 File doesn't exist or if the values don't match, delete and return
				$strMd5File = $this->GetFilePath() . '.md5';
				if (!file_exists($strMd5File) ||
					($strMd5 != file_get_contents($strMd5File))) {
					unlink($this->GetFilePath());
					return false;
				}

				// If we're here, return the contents of the cache file
				return file_get_contents($this->GetFilePath());
			} else
				return false;
		}

		public function SaveData($strData) {
			if (!is_dir($this->GetCacheDirectory()))
				mkdir($this->GetCacheDirectory());
			file_put_contents($this->GetFilePath(), $strData);
			file_put_contents($this->GetFilePath() . '.md5', $this->GetCheckFilesMd5());
		}

		public function GetFilePath() {
			return sprintf('%s/%s/%s.%s', QCache::$CachePath, $this->strNamespace, $this->strKey, $this->strExtension);
		}

		protected function GetCheckFilesMd5() {
			$intFoundFileCount = 0;
			$strData = '';
			foreach($this->strCheckFilesArray as $strCheckFile) {
				if (file_exists($strCheckFile)) {
					$intFoundFileCount++;
					$strData .= md5_file($strCheckFile);
				}
			}
			
			if ($intFoundFileCount == 0)
				return false;
			else
				return $intFoundFileCount . '_' . $strData;
		}

		protected function GetCacheDirectory() {
			return sprintf('%s/%s', QCache::$CachePath, $this->strNamespace);
		}
	}

	QCache::$CachePath = QApplication::$DocumentRoot . DOCROOT_SUBFOLDER . '/includes/cache';	
?>