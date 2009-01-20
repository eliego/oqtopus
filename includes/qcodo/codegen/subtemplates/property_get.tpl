		/**
		 * Override method to perform a property "Get"
		 * This will get the value of $strName
		 *
		 * @param string $strName Name of the property to get
		 * @return mixed
		 */
		public function __get($strName) {
			switch ($strName) {
				///////////////////
				// Member Variables
				///////////////////
<% foreach ($objTable->ColumnArray as $objColumn) { %>
				case '<%= $objColumn->PropertyName %>':
					/**
					 * Gets the value for <%= $objColumn->VariableName %> <% if ($objColumn->Identity) return '(Read-Only PK)'; else if ($objColumn->PrimaryKey) return '(PK)'; else if ($objColumn->Timestamp) return '(Read-Only Timestamp)'; else if ($objColumn->Unique) return '(Unique)'; else if ($objColumn->NotNull) return '(Not Null)'; %>
					 * @return <%= $objColumn->VariableType %>
					 */
					return $this-><%= $objColumn->VariableName %>;

<% } %>

				///////////////////
				// Member Objects
				///////////////////
<% foreach ($objTable->ColumnArray as $objColumn) { %>
	<% if (($objColumn->Reference) && (!$objColumn->Reference->IsType)) { %>
				case '<%= $objColumn->Reference->PropertyName %>':
					/**
					 * Gets the value for the <%= $objColumn->Reference->VariableType %> object referenced by <%= $objColumn->VariableName %> <% if ($objColumn->Identity) return '(Read-Only PK)'; else if ($objColumn->PrimaryKey) return '(PK)'; else if ($objColumn->Unique) return '(Unique)'; else if ($objColumn->NotNull) return '(Not Null)'; %>
					 * @return <%= $objColumn->Reference->VariableType %>
					 */
					try {
						if ((!$this-><%= $objColumn->Reference->VariableName %>) && (!is_null($this-><%= $objColumn->VariableName %>)))
							$this-><%= $objColumn->Reference->VariableName %> = <%= $objColumn->Reference->VariableType %>::Load($this-><%= $objColumn->VariableName %>);
						return $this-><%= $objColumn->Reference->VariableName %>;
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

	<% } %>
<% } %>
<% foreach ($objTable->ReverseReferenceArray as $objReverseReference) { %>
	<% if ($objReverseReference->Unique) { %>
		<% $objReverseReferenceTable = $objCodeGen->TableArray[strtolower($objReverseReference->Table)]; %>
		<% $objReverseReferenceColumn = $objReverseReferenceTable->ColumnArray[strtolower($objReverseReference->Column)]; %>
				case '<%= $objReverseReference->ObjectPropertyName %>':
					/**
					 * Gets the value for the <%= $objReverseReference->VariableType %> object that uniquely references this <%= $objTable->ClassName %>
					 * by <%= $objReverseReference->ObjectMemberVariable %> (Unique)
					 * @return <%= $objReverseReference->VariableType %>
					 */
					try {
						if (!$this-><%= $objReverseReference->ObjectMemberVariable %>)
							$this-><%= $objReverseReference->ObjectMemberVariable %> = <%= $objReverseReference->VariableType %>::LoadBy<%= $objReverseReferenceColumn->PropertyName %>(<%= $objCodeGen->ImplodeObjectArray(', ', '$this->', '', 'VariableName', $objTable->PrimaryKeyColumnArray) %>);
						return $this-><%= $objReverseReference->ObjectMemberVariable %>;
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}

	<% } %>
<% } %>

				default:
					try {
						return parent::__get($strName);
					} catch (QCallerException $objExc) {
						$objExc->IncrementOffset();
						throw $objExc;
					}
			}
		}