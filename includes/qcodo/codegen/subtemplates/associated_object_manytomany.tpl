		<% $objManyToManyReferenceTable = $objCodeGen->TableArray[strtolower($objManyToManyReference->AssociatedTable)]; %>
		// Related Many-to-Many Objects' Methods for <%= $objManyToManyReference->ObjectDescription %>
		//-------------------------------------------------------------------

		/**
		 * Gets all many-to-many associated <%= $objManyToManyReference->ObjectDescriptionPlural %> as an array of <%= $objManyToManyReference->VariableType %> objects
		 * @param string $strOrderBy
		 * @param string $strLimit
		 * @param array $objExpansionMap map of referenced columns to be immediately expanded via early-binding
		 * @return <%= $objManyToManyReference->VariableType %>[]
		*/ 
		public function Get<%= $objManyToManyReference->ObjectDescription %>Array($strOrderBy = null, $strLimit = null, $objExpansionMap = null) {
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($this->', '))', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)
				return array();

			return <%= $objManyToManyReference->VariableType %>::LoadArrayBy<%= $objManyToManyReference->OppositeObjectDescription %>($this-><%= $objTable->PrimaryKeyColumnArray[0]->VariableName %>, $strOrderBy, $strLimit, $objExpansionMap);
		}

		/**
		 * Counts all many-to-many associated <%= $objManyToManyReference->ObjectDescriptionPlural %>
		 * @return int
		*/ 
		public function Count<%= $objManyToManyReference->ObjectDescriptionPlural %>() {
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($this->', '))', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)
				return 0;

			return <%= $objManyToManyReference->VariableType %>::CountBy<%= $objManyToManyReference->OppositeObjectDescription %>($this-><%= $objTable->PrimaryKeyColumnArray[0]->VariableName %>);
		}

		/**
		 * Associates a <%= $objManyToManyReference->ObjectDescription %>
		 * @param <%= $objManyToManyReference->VariableType %> $<%= $objManyToManyReference->VariableName %>
		 * @return void
		*/ 
		public function Associate<%= $objManyToManyReference->ObjectDescription %>(<%= $objManyToManyReference->VariableType %> $<%= $objManyToManyReference->VariableName %>) {
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($this->', '))', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)
				throw new QUndefinedPrimaryKeyException('Unable to call Associate<%= $objManyToManyReference->ObjectDescription %> on this unsaved <%= $objTable->ClassName %>.');
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($' . $objManyToManyReference->VariableName . '->', '))', 'PropertyName', $objManyToManyReferenceTable->PrimaryKeyColumnArray) %>)
				throw new QUndefinedPrimaryKeyException('Unable to call Associate<%= $objManyToManyReference->ObjectDescription %> on this <%= $objTable->ClassName %> with an unsaved <%= $objManyToManyReferenceTable->ClassName %>.');

			// Call to QueryHelper to Get the Database Object
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				INSERT INTO <%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %> (
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Column %><%= $strEscapeIdentifierEnd %>,
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->OppositeColumn %><%= $strEscapeIdentifierEnd %>
				) VALUES (
					' . $objDatabase->SqlVariable($this-><%= $objTable->PrimaryKeyColumnArray[0]->VariableName %>) . ',
					' . $objDatabase->SqlVariable($<%= $objManyToManyReference->VariableName %>-><%= $objManyToManyReferenceTable->PrimaryKeyColumnArray[0]->PropertyName %>) . '
				)
			');
		}

		/**
		 * Unassociates a <%= $objManyToManyReference->ObjectDescription %>
		 * @param <%= $objManyToManyReference->VariableType %> $<%= $objManyToManyReference->VariableName %>
		 * @return void
		*/ 
		public function Unassociate<%= $objManyToManyReference->ObjectDescription %>(<%= $objManyToManyReference->VariableType %> $<%= $objManyToManyReference->VariableName %>) {
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($this->', '))', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)
				throw new QUndefinedPrimaryKeyException('Unable to call Unassociate<%= $objManyToManyReference->ObjectDescription %> on this unsaved <%= $objTable->ClassName %>.');
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($' . $objManyToManyReference->VariableName . '->', '))', 'PropertyName', $objManyToManyReferenceTable->PrimaryKeyColumnArray) %>)
				throw new QUndefinedPrimaryKeyException('Unable to call Unassociate<%= $objManyToManyReference->ObjectDescription %> on this <%= $objTable->ClassName %> with an unsaved <%= $objManyToManyReferenceTable->ClassName %>.');

			// Call to QueryHelper to Get the Database Object
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>
				WHERE
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Column %><%= $strEscapeIdentifierEnd %> = ' . $objDatabase->SqlVariable($this-><%= $objTable->PrimaryKeyColumnArray[0]->VariableName %>) . ' AND
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->OppositeColumn %><%= $strEscapeIdentifierEnd %> = ' . $objDatabase->SqlVariable($<%= $objManyToManyReference->VariableName %>-><%= $objManyToManyReferenceTable->PrimaryKeyColumnArray[0]->PropertyName %>) . '
			');
		}

		/**
		 * Unassociates all <%= $objManyToManyReference->ObjectDescriptionPlural %>
		 * @return void
		*/ 
		public function UnassociateAll<%= $objManyToManyReference->ObjectDescriptionPlural %>() {
			if (<%= $objCodeGen->ImplodeObjectArray(' || ', '(is_null($this->', '))', 'VariableName', $objTable->PrimaryKeyColumnArray) %>)
				throw new QUndefinedPrimaryKeyException('Unable to call UnassociateAll<%= $objManyToManyReference->ObjectDescription %>Array on this unsaved <%= $objTable->ClassName %>.');

			// Call to QueryHelper to Get the Database Object
			<%= $objTable->ClassName %>::QueryHelper($objDatabase);

			// Perform the SQL Query
			$objDatabase->NonQuery('
				DELETE FROM
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Table %><%= $strEscapeIdentifierEnd %>
				WHERE
					<%= $strEscapeIdentifierBegin %><%= $objManyToManyReference->Column %><%= $strEscapeIdentifierEnd %> = ' . $objDatabase->SqlVariable($this-><%= $objTable->PrimaryKeyColumnArray[0]->VariableName %>) . '
			');
		}