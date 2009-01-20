	<% $objColumnArray = $objCodeGen->GetColumnArray($objTable, $objIndex->ColumnNameArray); %>
		/**
		 * Load a single <%= $objTable->ClassName %> object,
		 * by <%= $objCodeGen->ImplodeObjectArray(', ', '', '', 'PropertyName', $objCodeGen->GetColumnArray($objTable, $objIndex->ColumnNameArray)) %> Index(es)
<% foreach ($objColumnArray as $objColumn) { %> 
		 * @param <%= $objColumn->VariableType %> $<%= $objColumn->VariableName %>
<% } %>
		 * @return <%= $objTable->ClassName %>
		*/
		public static function LoadBy<%= $objCodeGen->ImplodeObjectArray('', '', '', 'PropertyName', $objColumnArray); %>(<%= $objCodeGen->ParameterListFromColumnArray($objColumnArray); %>) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
<% foreach ($objColumnArray as $objColumn) { %>
			<%= $this->ParameterCleanupFromColumn($objColumn, true) %>
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
<% foreach ($objColumnArray as $objColumn) { %>
					<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> %s AND
<% } %><%-----%>', <%= $objCodeGen->ParameterListFromColumnArray($objColumnArray); %>);

			// Perform the Query and Instantiate the Row
			$objDbResult = $objDatabase->Query($strQuery);
			return <%= $objTable->ClassName %>::InstantiateDbRow($objDbResult->GetNextRow());
		}