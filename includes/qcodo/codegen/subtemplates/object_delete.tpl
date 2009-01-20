		/**
		 * Delete this <%= $objTable->ClassName %>
		 * @return void
		*/
		public function Delete() {
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($this->', '))', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)
				throw new QUndefinedPrimaryKeyException('Cannot delete this <%= $objTable->ClassName %> with an unset primary key.');

			// Call to QueryHelper to Get the Database Object
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %>
	<% if ($objReverseReference->Unique) { %>
		<% if (!$objReverseReference->NotNull) { %>
			<% $objReverseReferenceTable = $objCodeGen->TableArray[strtolower($objReverseReference->Table)]; %>
			<% $objReverseReferenceColumn = $objReverseReferenceTable->ColumnArray[strtolower($objReverseReference->Column)]; %>
			// Update the adjoined <%= $objReverseReference->ObjectDescription %> object (if applicable) and perform the unassociation

			// Optional -- if you **KNOW** that you do not want to EVER run any level of business logic on the disassocation,
			// you *could* override Delete() so that this step can be a single hard coded query to optimize performance.
			if ($objAssociated = <%= $objReverseReference->VariableType %>::LoadBy<%= $objReverseReferenceColumn->PropertyName %>(<%= $objCodeGen->ImplodeObjectArray(', ', '$this->', '', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)) {
				$objAssociated-><%= $objReverseReferenceColumn->PropertyName %> = null;
				$objAssociated->Save();
			}
		<% } %><% if ($objReverseReference->NotNull) { %>
			<% $objReverseReferenceTable = $objCodeGen->TableArray[strtolower($objReverseReference->Table)]; %>
			<% $objReverseReferenceColumn = $objReverseReferenceTable->ColumnArray[strtolower($objReverseReference->Column)]; %>
			// Update the adjoined <%= $objReverseReference->ObjectDescription %> object (if applicable) and perform a delete

			// Optional -- if you **KNOW** that you do not want to EVER run any level of business logic on the disassocation,
			// you *could* override Delete() so that this step can be a single hard coded query to optimize performance.
			if ($objAssociated = <%= $objReverseReference->VariableType %>::LoadBy<%= $objReverseReferenceColumn->PropertyName %>(<%= $objCodeGen->ImplodeObjectArray(', ', '$this->', '', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)) {
				$objAssociated->Delete();
			}
		<% } %>
	<% } %>
<% } %>

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>
				WHERE
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if ($objColumn->PrimaryKey) { %>
					<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> = ' . $objDatabase->SqlVariable($this-><%= $objColumn->VariableName %>) . ' AND
	<% } %>
<% } %><%-----%>');
		}