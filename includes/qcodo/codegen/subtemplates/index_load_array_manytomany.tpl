		/**
		 * Load an array of <%= $objManyToManyReference->VariableType %> objects for a given <%= $objManyToManyReference->ObjectDescription %>
		 * via the <%= $objManyToManyReference->Table %> table
		 * @param <%= $objManyToManyReference->OppositeVariableType %> $<%= $objManyToManyReference->OppositeVariableName %>
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return <%= $objManyToManyReference->VariableType %>[]
		*/
		public static function LoadArrayBy<%= $objManyToManyReference->ObjectDescription %>($<%= $objManyToManyReference->OppositeVariableName %>, $strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			<%= $objTable->ClassName %>::ArrayQueryHelper($strOrderBy, $strLimit, $strLimitPrefix, $strLimitSuffix, $strExpandSelect, $strExpandFrom, $objExpansionMap, $objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$<%= $objManyToManyReference->OppositeVariableName %> = $objDatabase->SqlVariable($<%= $objManyToManyReference->OppositeVariableName %>);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
				%s
<% foreach ($objTable->ColumnArray as $objColumn) { %>
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %> AS <%= $strEscapeIdentifierBegin %><%= $objColumn->Name %><%= $strEscapeIdentifierEnd %>,
<% } %><%--%>
					%s
				FROM
					(<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %> AS <%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>,
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %> AS <%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>)
					%s
				WHERE
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Column %><%= $strEscapeIdentifierEnd %> = <%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objTable->PrimaryKeyColumnArray[0]->Name %><%= $strEscapeIdentifierEnd %> AND
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->OppositeColumn %><%= $strEscapeIdentifierEnd %> = %s
				%s
				%s', $strLimitPrefix, $strExpandSelect, $strExpandFrom,
				$<%= $objManyToManyReference->OppositeVariableName %>,
				$strOrderBy, $strLimitSuffix);

			// Perform the Query and Instantiate the Result
			$objDbResult = $objDatabase->Query($strQuery);
			return <%= $objTable->ClassName %>::InstantiateDbResult($objDbResult);
		}

		/**
		 * Count <%= $objTable->ClassNamePlural %> for a given <%= $objManyToManyReference->ObjectDescription %>
		 * via the <%= $objManyToManyReference->Table %> table
		 * @param <%= $objManyToManyReference->OppositeVariableType %> $<%= $objManyToManyReference->OppositeVariableName %>
		 * @return int
		*/
		public static function CountBy<%= $objManyToManyReference->ObjectDescription %>($<%= $objManyToManyReference->OppositeVariableName %>) {
			// Call to ArrayQueryHelper to Get Database Object and Get SQL Clauses
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Properly Escape All Input Parameters using Database->SqlVariable()
			$<%= $objManyToManyReference->OppositeVariableName %> = $objDatabase->SqlVariable($<%= $objManyToManyReference->OppositeVariableName %>);

			// Setup the SQL Query
			$strQuery = sprintf('
				SELECT
					COUNT(*) AS row_count
				FROM
					<%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>,
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>
				WHERE
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Column %><%= $strEscapeIdentifierEnd %> = <%= $strEscapeIdentifierBegin %><%= $objTable->Name %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objTable->PrimaryKeyColumnArray[0]->Name %><%= $strEscapeIdentifierEnd %> AND
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>.<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->OppositeColumn %><%= $strEscapeIdentifierEnd %> = %s
			', $<%= $objManyToManyReference->OppositeVariableName %>);

			// Perform the Query and Return the Count
			$objDbResult = $objDatabase->Query($strQuery);
            $strDbRow = $objDbResult->FetchRow();
            return QType::Cast($strDbRow[0], QType::Integer);
		}