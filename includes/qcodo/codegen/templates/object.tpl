<OverwriteFlag="true" TargetFilePath="<%= QApplication::$DocumentRoot . DOCROOT_SUBFOLDER %>/includes/data_objects_generated/<%= $objTable->ClassName %>Gen.inc"/>
<?php
	/**
	 * The abstract <%= $objTable->ClassName %>Gen class defined here is
	 * code-generated and contains all the basic CRUD-type functionality as well as
	 * basic methods to handle relationships and index-based loading.
	 *
	 * To use, you should use the <%= $objTable->ClassName %> subclass which
	 * extends this <%= $objTable->ClassName %>Gen class.
	 *
	 * Because subsequent re-code generations will overwrite any changes to this
	 * file, you should leave this file unaltered to prevent yourself from losing
	 * any information or code changes.  All customizations should be done by
	 * overriding existing or implementing new methods, properties and variables
	 * in the <%= $objTable->ClassName %> class.
	 * 
	 * @package <%= $objCodeGen->ApplicationName; %>
	 * @subpackage GeneratedDataObjects
	 * 
	 */
	class <%= $objTable->ClassName %>Gen extends QBaseClass {
		///////////////////////////////
		// COMMON LOAD METHODS
		///////////////////////////////

		/**
		 * Load a <%= $objTable->ClassName %> from PK Info
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if ($objColumn->PrimaryKey) { %>
		 * @param <%= $objColumn->VariableType %> $<%= $objColumn->VariableName %>
	<% } %>
<% } %>
		 * @return <%= $objTable->ClassName %>
		*/
		public static function Load(<%= $objCodeGen->ParameterListFromColumnArray($objTable->PrimaryKeyColumnArray); %>) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
<% foreach ($objTable->PrimaryKeyColumnArray as $objColumn) { %>
			<%= $this->ParameterCleanupFromColumn($objColumn) %>
<% } %>

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
<% foreach ($objTable->ColumnArray as $objColumn) { %>
					<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %>,
<% } %><%--%>
				FROM
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>
				WHERE
<% foreach ($objTable->PrimaryKeyColumnArray as $objColumn) { %>
					<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> = %s AND
<% } %><%-----%>', <%= $objCodeGen->ParameterListFromColumnArray($objTable->PrimaryKeyColumnArray); %>);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return <%= $objTable->ClassName %>::InstantiateDbRow($objDbResult->GetNextRow());
		}



		/**
		 * Internally called method to assist with SQL Query options/preferences for single row loaders.
		 * Any Load (single row) method can use this method to get the Database object.
		 * @param string $objDatabase reference to the Database object to be queried
		 */
		protected static function QueryHelper(&$objDatabase) {
			// Get the Database
			$objDatabase = QApplication::$Database[<%= $objCodeGen->DatabaseIndex; %>];
		}



		/**
		 * Internally called method to assist with SQL Query options/preferences for array loaders.
		 * Any LoadAll or LoadArray method can use this method to setup SQL Query Clauses that deal
		 * with OrderBy, Limit, and Object Expansion.  Strings that contain SQL Query Clauses are
		 * passed in by reference.
		 * @param string $strOrderBy reference to the Order By as passed in to the LoadArray method
		 * @param string $strLimit the Limit as passed in to the LoadArray method
		 * @param string $strLimitPrefix reference to the Limit Prefix to be used in the SQL
		 * @param string $strLimitSuffix reference to the Limit Suffix to be used in the SQL
		 * @param string $strExpandSelect reference to the Expand Select to be used in the SQL
		 * @param string $strExpandFrom reference to the Expand From to be used in the SQL
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @param string $objDatabase reference to the Database object to be queried
		 */
		protected static function ArrayQueryHelper(&$strOrderBy, $strLimit, &$strLimitPrefix, &$strLimitSuffix, &$strExpandSelect, &$strExpandFrom, $objExpansionMap, &$objDatabase) {
			// Get the Database
			$objDatabase = QApplication::$Database[<%= $objCodeGen->DatabaseIndex; %>];

			// Setup OrderBy and Limit Information (if applicable)
			$strOrderBy = $objDatabase->SqlSortByVariable($strOrderBy);
			$strLimitPrefix = $objDatabase->SqlLimitVariablePrefix($strLimit);
			$strLimitSuffix = $objDatabase->SqlLimitVariableSuffix($strLimit);

			// Setup QueryExpansion (if applicable)
			if ($objExpansionMap) {
				$objQueryExpansion = new QQueryExpansion('<%= $objTable->ClassName %>', '<%= $objTable->Name %>', $objExpansionMap);
				$strExpandSelect = $objQueryExpansion->GetSelectSql();
				$strExpandFrom = $objQueryExpansion->GetFromSql();
			} else {
				$strExpandSelect = null;
				$strExpandFrom = null;
			}
		}



		/**
		 * Internally called method to assist with early binding of objects
		 * on load methods.  Can only early-bind references that this class owns in the database.
		 * @param string $strParentAlias the alias of the parent (if any)
		 * @param string $strAlias the alias of this object
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @param QueryExpansion an already instantiated QueryExpansion object (used as a utility object to assist with object expansion)
		 */
		public static function ExpandQuery($strParentAlias, $strAlias, $objExpansionMap, QQueryExpansion $objQueryExpansion) {
			if ($strAlias) {
				$objQueryExpansion->AddFromItem(sprintf('INNER JOIN <%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %> AS <%= $strEscapeIdentifierBegin %>%s__%s<%= $strEscapeIdentifierEnd %> ON <%= $strEscapeIdentifierBegin %>%s<%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %>%s<%= $strEscapeIdentifierEnd %> = <%= $strEscapeIdentifierBegin %>%s__%s<%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objTable->PrimaryKeyColumnArray[0]->Name %><%= $strEscapeIdentifierEnd %>', $strParentAlias, $strAlias, $strParentAlias, $strAlias, $strParentAlias, $strAlias));

<% foreach ($objTable->ColumnArray as $objColumn) { %>
				$objQueryExpansion->AddSelectItem(sprintf('<%= $strEscapeIdentifierBegin %>%s__%s<%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> AS <%= $strEscapeIdentifierBegin %>%s__%s__<%= $objColumn->Name %><%= $strEscapeIdentifierEnd %>', $strParentAlias, $strAlias, $strParentAlias, $strAlias));
<% } %>

				$strParentAlias = $strParentAlias . '__' . $strAlias;
			}

			if (is_array($objExpansionMap))
				foreach ($objExpansionMap as $strKey=>$objValue) {
					switch ($strKey) {
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if ($objColumn->Reference && (!$objColumn->Reference->IsType)) { %>
						case '<%= $objColumn->Name %>':
							try {
								<%= $objColumn->Reference->VariableType %>::ExpandQuery($strParentAlias, $strKey, $objValue, $objQueryExpansion);
								break;
							} catch (QCallerException $objExc) {
								$objExc->IncrementOffset();
								throw $objExc;
							}
	<% } %>
<% } %>
						default:
							throw new QCallerException(sprintf('Unknown Object to Expand in %s: %s', $strParentAlias, $strKey));
					}
				}
		}



		/**
		 * Load all <%= $objTable->ClassNamePlural %>
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return <%= $objTable->ClassName %>[]
		*/
		public static function LoadAll($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			<%= $objTable->ClassName %>::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
<% foreach ($objTable->ColumnArray as $objColumn) { %>
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> AS <%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %>,
<% } %><%--%>
					%s
				FROM
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %> AS <%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>
					%s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return <%= $objTable->ClassName %>::InstantiateDbResult($objDbResult);
		}



		/**
		 * Count all <%= $objTable->ClassNamePlural %>
		 * @return int
		*/
		public static function CountAll() {
			// Call to QueryHelper to Get the Database Object
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) as row_count
				FROM
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>');

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}


		/**
		 * Instantiate a <%= $objTable->ClassName %> from a Database Row.
		 * Takes in an optional strAliasPrefix, used in case another Object::InstantiateDbRow
		 * is calling this <%= $objTable->ClassName %>::InstantiateDbRow in order to perform
		 * early binding on referenced objects.
		 * @param DatabaseRowBase $objDbRow
		 * @param string $strAliasPrefix
		 * @return <%= $objTable->ClassName %>
		*/
		public static function InstantiateDbRow($objDbRow, $strAliasPrefix = null) {
			// If blank row, return null
			if (!$objDbRow)
				return null;

			// Create a new instance of the <%= $objTable->ClassName %> object
			$objToReturn = new <%= $objTable->ClassName %>();
			$objToReturn->__blnRestored = true;

<% foreach ($objTable->ColumnArray as $objColumn) { %>
			$objToReturn-><%= $objColumn->VariableName %> = $objDbRow->GetColumn($strAliasPrefix . '<%= $objColumn->Name %>', '<%= $objColumn->DbType %>');
	<% if (($objColumn->PrimaryKey) && (!$objColumn->Identity)) { %>
			$objToReturn->__<%= $objColumn->VariableName %> = $objDbRow->GetColumn($strAliasPrefix . '<%= $objColumn->Name %>', '<%= $objColumn->DbType %>');
	<% } %>
<% } %><%-%>

			// Instantiate Virtual Attributes
			foreach ($objDbRow->GetColumnNameArray() as $strColumnName => $mixValue) {
				$strVirtualPrefix = $strAliasPrefix . '__';
				$strVirtualPrefixLength = strlen($strVirtualPrefix);
				if (substr($strColumnName, 0, $strVirtualPrefixLength) == $strVirtualPrefix)
					$objToReturn->__strVirtualAttributeArray[substr($strColumnName, $strVirtualPrefixLength)] = $mixValue;
			}

			// Prepare to Check for Early Binding
			if (!$strAliasPrefix)
				$strAliasPrefix = '<%= $objTable->Name %>__';

<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if ($objColumn->Reference && !$objColumn->Reference->IsType) { %>
			// Check for <%= $objColumn->Reference->PropertyName %> Early Binding
			if (!is_null($objDbRow->GetColumn($strAliasPrefix . '<%= $objColumn->Name %>__<%= $objCodeGen->GetTable($objColumn->Reference->Table)->PrimaryKeyColumnArray[0]->Name %>')))
				$objToReturn-><%= $objColumn->Reference->VariableName %> = <%= $objColumn->Reference->VariableType %>::InstantiateDbRow($objDbRow, $strAliasPrefix . '<%= $objColumn->Name %>__');

	<% } %>
<% } %>
			
			return $objToReturn;
		}


		/**
		 * Lookup a VirtualAttribute value (if applicable).  Returns NULL if none found.
		 * @param string $strName
		 * @return string
		*/
		public function GetVirtualAttribute($strName) {
			if (array_key_exists($strName, $this->__strVirtualAttributeArray))
				return $this->__strVirtualAttributeArray[$strName];
			return null;
		}


		/**
		 * Instantiate an array of <%= $objTable->ClassNamePlural %> from a Database Result
		 * @param DatabaseResultBase $objDbResult
		 * @return <%= $objTable->ClassName %>[]
		*/
		public static function InstantiateDbResult(QDatabaseResultBase $objDbResult) {
			$objToReturn = array();

			// If blank resultset, then return empty array
			if (!$objDbResult)
				return $objToReturn;

			// Load up the return array with each row
			while ($objDbRow = $objDbResult->GetNextRow())
				array_push($objToReturn, <%= $objTable->ClassName %>::InstantiateDbRow($objDbRow));

			return $objToReturn;
		}



		///////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Single Load and Array)
		///////////////////////////////////////////////////
<% foreach ($objTable->IndexArray as $objIndex) { %>
	<% if ($objIndex->Unique && !$objIndex->PrimaryKey) { %>
		<%@ index_load_single('objTable', 'objIndex'); %>
	<% } %><% if (!$objIndex->Unique) { %>
		<%@ index_load_array('objTable', 'objIndex'); %>
	<% } %>
<% } %>





		////////////////////////////////////////////////////
		// INDEX-BASED LOAD METHODS (Array via Many to Many)
		////////////////////////////////////////////////////
<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %>
	<%@ index_load_array_manytomany('objTable', 'objManyToManyReference') %>
<% } %>





		//////////////////
		// SAVE AND DELETE
		//////////////////

		<%@ object_save('objTable'); %>

		<%@ object_delete('objTable'); %>

		/**
		 * Delete all <%= $objTable->ClassNamePlural %>
		 * @return void
		*/
		public static function DeleteAll() {
			// Call to QueryHelper to Get the Database Object
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				DELETE FROM
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>');
		}

		/**
		 * Truncate <%= $objTable->Name %> table
		 * @return void
		*/
		public static function Truncate() {
			// Call to QueryHelper to Get the Database Object
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Perform the Query
			$objDatabase->NonQuery('
				TRUNCATE <%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>');
		}





		////////////////////
		// PUBLIC OVERRIDERS
		////////////////////

		<%@ property_get('objTable'); %>

		<%@ property_set('objTable'); %>





		///////////////////////////////
		// ASSOCIATED OBJECTS
		///////////////////////////////

<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %><% if (!$objReverseReference->Unique) { %>
	<%@ associated_object('objTable', 'objReverseReference'); %>
<% } %><% } %>
<% foreach ($objTable->ManyToManyReferenceArray as $objManyToManyReference) { %>
	<%@ associated_object_manytomany('objTable', 'objManyToManyReference'); %>
<% } %>





		///////////////////////////////
		// PROTECTED MEMBER VARIABLES
		///////////////////////////////
		
<% foreach ($objTable->ColumnArray as $objColumn) { %>
		/**
		 * Protected member variable that maps to the database <% if ($objColumn->PrimaryKey) return 'PK '; %><% if ($objColumn->Identity) return 'Identity '; %>column <%= $objTable->Name %>.<%= $objColumn->Name %>
		 * @var <%= $objColumn->VariableType %> <%= $objColumn->VariableName %>
		 */
		protected $<%= $objColumn->VariableName %>;
	<% if ((!$objColumn->Identity) && ($objColumn->PrimaryKey)) { %>

		/**
		 * Protected internal member variable that stores the original version of the PK column value (if restored)
		 * Used by Save() to update a PK column during UPDATE
		 * @var <%= $objColumn->VariableType %> __<%= $objColumn->VariableName %>;
		 */
		protected $__<%= $objColumn->VariableName %>;
	<% } %>

<% } %>
		/**
		 * Protected array of virtual attributes for this object (e.g. extra/other calculated and/or non-object bound
		 * columns from the run-time database query result for this object).  Used by InstantiateDbRow and
		 * GetVirtualAttribute.
		 * @var string[] $__strVirtualAttributeArray
		 */
		protected $__strVirtualAttributeArray = array();

		/**
		 * Protected internal member variable that specifies whether or not this object is Restored from the database.
		 * Used by Save() to determine if Save() should perform a db UPDATE or INSERT.
		 * @var bool __blnRestored;
		 */
		protected $__blnRestored;





		///////////////////////////////
		// PROTECTED MEMBER OBJECTS
		///////////////////////////////

<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if (($objColumn->Reference) && (!$objColumn->Reference->IsType)) { %>
		/**
		 * Protected member variable that contains the object pointed by the reference
		 * in the database column <%= $objTable->Name %>.<%= $objColumn->Name %>.
		 *
		 * NOTE: Always use the <%= $objColumn->Reference->PropertyName %> property getter to correctly retrieve this <%= $objColumn->Reference->VariableType %> object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var <%= $objColumn->Reference->VariableType %> <%= $objColumn->Reference->VariableName %>
		 */
		protected $<%= $objColumn->Reference->VariableName %>;

	<% } %>
<% } %>
<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %>
	<% if ($objReverseReference->Unique) { %>
		/**
		 * Protected member variable that contains the object which points to
		 * this object by the reference in the unique database column <%= $objReverseReference->Table %>.<%= $objReverseReference->Column %>.
		 *
		 * NOTE: Always use the <%= $objReverseReference->ObjectPropertyName %> property getter to correctly retrieve this <%= $objReverseReference->VariableType %> object.
		 * (Because this class implements late binding, this variable reference MAY be null.)
		 * @var <%= $objReverseReference->VariableType %> <%= $objReverseReference->ObjectMemberVariable %>
		 */
		protected $<%= $objReverseReference->ObjectMemberVariable %> = array();
		
		/**
		 * Used internally to manage whether the adjoined <%= $objReverseReference->ObjectDescription %> object
		 * needs to be updated on save.
		 * 
		 * NOTE: Do not manually update this value 
		 */
		protected $blnDirty<%= $objReverseReference->ObjectPropertyName %>;

	<% } %>
<% } %>




		////////////////////////////////////////
		// COLUMN CONSTANTS for OBJECT EXPANSION
		////////////////////////////////////////
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if ($objColumn->Reference && (!$objColumn->Reference->IsType)) { %>
		const Expand<%= $objColumn->Reference->PropertyName %> = '<%= $objColumn->Name %>';
	<% } %>
<% } %>




		////////////////////////////////////////
		// METHODS for WEB SERVICES
		////////////////////////////////////////
		public static function GetSoapComplexTypeXml() {
			$strToReturn = '<complexType name="<%= $objTable->ClassName %>"><sequence>';
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if (!$objColumn->Reference || $objColumn->Reference->IsType) { %>
			$strToReturn .= '<element name="<%= $objColumn->PropertyName %>" type="xsd:<%= QType::SoapType($objColumn->VariableType) %>"/>';
	<% } %><% if ($objColumn->Reference && (!$objColumn->Reference->IsType)) { %>
			$strToReturn .= '<element name="<%= $objColumn->Reference->PropertyName %>" type="xsd1:<%= $objColumn->Reference->VariableType %>"/>';
	<% } %>
<% } %>
			$strToReturn .= '<element name="__blnRestored" type="xsd:boolean"/>';
			$strToReturn .= '</sequence></complexType>';
			return $strToReturn;
		}

		public static function AlterSoapComplexTypeArray(&$strComplexTypeArray) {
			if (!array_key_exists('<%= $objTable->ClassName %>', $strComplexTypeArray)) {
				$strComplexTypeArray['<%= $objTable->ClassName %>'] = <%= $objTable->ClassName %>::GetSoapComplexTypeXml();
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if ($objColumn->Reference && (!$objColumn->Reference->IsType)) { %>
				<%= $objColumn->Reference->VariableType%>::AlterSoapComplexTypeArray($strComplexTypeArray);
	<% } %>
<% } %>
			}
		}

		public static function GetArrayFromSoapArray($objSoapArray) {
			$objArrayToReturn = array();

			foreach ($objSoapArray as $objSoapObject)
				array_push($objArrayToReturn, <%= $objTable->ClassName %>::GetObjectFromSoapObject($objSoapObject));

			return $objArrayToReturn;
		}

		public static function GetObjectFromSoapObject($objSoapObject) {
			$objToReturn = new <%= $objTable->ClassName %>();
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if (!$objColumn->Reference || $objColumn->Reference->IsType) { %>
			if (property_exists($objSoapObject, '<%= $objColumn->PropertyName %>'))
<% if ($objColumn->VariableType != QType::DateTime) { %>
				$objToReturn-><%= $objColumn->VariableName %> = $objSoapObject-><%= $objColumn->PropertyName %>;
<% } %><% if ($objColumn->VariableType == QType::DateTime) { %>
				$objToReturn-><%= $objColumn->VariableName %> = new QDateTime($objSoapObject-><%= $objColumn->PropertyName %>);
<% } %>
	<% } %><% if ($objColumn->Reference && (!$objColumn->Reference->IsType)) { %>
			if ((property_exists($objSoapObject, '<%= $objColumn->Reference->PropertyName %>')) &&
				($objSoapObject-><%= $objColumn->Reference->PropertyName %>))
				$objToReturn-><%= $objColumn->Reference->PropertyName %> = <%= $objColumn->Reference->VariableType %>::GetObjectFromSoapObject($objSoapObject-><%= $objColumn->Reference->PropertyName %>);
	<% } %>
<% } %>
			if (property_exists($objSoapObject, '__blnRestored'))
				$objToReturn->__blnRestored = $objSoapObject->__blnRestored;
			return $objToReturn;
		}

		public static function GetSoapArrayFromArray($objArray) {
			if (!$objArray)
				return null;

			$objArrayToReturn = array();

			foreach ($objArray as $objObject)
				array_push($objArrayToReturn, <%= $objTable->ClassName %>::GetSoapObjectFromObject($objObject, true));

			return $objArrayToReturn;
		}

		public static function GetSoapObjectFromObject($objObject, $blnBindRelatedObjects) {
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if ($objColumn->VariableType == QType::DateTime) { %>
			if ($objObject-><%= $objColumn->VariableName %>)
				$objObject-><%= $objColumn->VariableName %> = $objObject-><%= $objColumn->VariableName %>->__toString(QDateTime::FormatSoap);
	<% } %><% if ($objColumn->Reference && (!$objColumn->Reference->IsType)) { %>
			if ($objObject-><%= $objColumn->Reference->VariableName %>)
				$objObject-><%= $objColumn->Reference->VariableName %> = <%= $objColumn->Reference->VariableType %>::GetSoapObjectFromObject($objObject-><%= $objColumn->Reference->VariableName %>, false);
			else if (!$blnBindRelatedObjects)
				$objObject-><%= $objColumn->VariableName %> = null;
	<% } %>
<% } %>
			return $objObject;
		}
	}
?>