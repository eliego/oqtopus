<?php
	/**
	 * Very simple map class, actually just implementing a standard array
	 * 
	 * @author Kung den Knege <kungdenknege@gmail.com>
	 * @package oqtopus
	 * @subpackage helpers
	 */
	class ObjectCache {
		/**
		 * Array to store objects =)
		 *
		 * @var object[]
		 */
		private $ar = array();
		
		/**
		 * Store a new object
		 *
		 * @param object $obj
		 * @return int
		 */
		public function storeObject($obj) {
			$this->ar[] = $obj;
			return count($this->ar);
		}
		
		/**
		 * Fetch an object
		 *
		 * @param int $id
		 * @return object
		 */
		public function getObject($id) {
			if (sizeof($this->ar) < $id)
				throw new NoSuchObjectException();
				
			return $this->ar[$id - 1];
		}
		
		public function getByProperty($strKey, $mixValue) {
			for ($i = 0; $i < sizeof($this->ar); $i++)
				if ($this->arr[$i]->$strKey === $mixValue)
					return $i + 1;
					
			return false;
		}
	}

?>