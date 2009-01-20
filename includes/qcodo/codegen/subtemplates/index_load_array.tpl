	<% $objColumnArray = $objCodeGen->GetColumnArray($objTable, $objIndex->ColumnNameArray); %>
		/**
		 * Load an array of <%= $objTable->ClassName %> objects,
		 * by <%= $objCodeGen->ImplodeObjectArray(', ', '', '', 'PropertyName', $objCodeGen->GetColumnArray($objTable, $objIndex->ColumnNameArray)) %> Index(es)
<% foreach ($objColumnArray as $objColumn) { %> 
		 * @param <%= $objColumn->VariableType %> $<%= $objColumn->VariableName %>
<% } %>
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return <%= $objTable->ClassName %>[]
		*/
		public static function LoadArrayBy<%= $objCodeGen->ImplodeObjectArray('', '', '', 'PropertyName', $objColumnArray); %>(<%= $objCodeGen->ParameterListFromColumnArray($objColumnArray); %>, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			<%= $objTable->ClassName %>::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
<% foreach ($objColumnArray as $objColumn) { %>
			<%= $this->ParameterCleanupFromColumn($objColumn, true) %>
<% } %>

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
				WHERE
<% foreach ($objColumnArray as $objColumn) { %>
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> %s AND
<% } %><%-----%>
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				<%= $objCodeGen->ParameterListFromColumnArray($objColumnArray); %>,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return <%= $objTable->ClassName %>::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count <%= $objTable->ClassNamePlural %>
		 * by <%= $objCodeGen->ImplodeObjectArray(', ', '', '', 'PropertyName', $objCodeGen->GetColumnArray($objTable, $objIndex->ColumnNameArray)) %> Index(es)
<% foreach ($objColumnArray as $objColumn) { %> 
		 * @param <%= $objColumn->VariableType %> $<%= $objColumn->VariableName %>
<% } %>
		 * @return int
		*/
		public static function CountBy<%= $objCodeGen->ImplodeObjectArray('', '', '', 'PropertyName', $objColumnArray); %>(<%= $objCodeGen->ParameterListFromColumnArray($objColumnArray); %>) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
<% foreach ($objColumnArray as $objColumn) { %>
			<%= $this->ParameterCleanupFromColumn($objColumn, true) %>
<% } %>

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>
				WHERE
<% foreach ($objColumnArray as $objColumn) { %>
					<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> %s AND
<% } %><%-----%>', <%= $objCodeGen->ParameterListFromColumnArray($objColumnArray); %>);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
			$strDbRow = $objDbResult->FetchRow();
			return QType::Cast($strDbRow[0], QType::Integer);
		}