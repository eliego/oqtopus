			$this->col<%= $objColumn->PropertyName %> = new QDataGridColumn(QApplication::Translate('<%= QConvertNotation::WordsFromCamelCase($objColumn->PropertyName) %>'), '<?= $_FORM->dtg<%= $objTable->ClassName %>_<%= $objColumn->PropertyName %>_Render($_ITEM); ?>', 'SortByCommand="<%= $objColumn->Name %> ASC"', 'ReverseSortByCommand="<%= $objColumn->Name %> DESC"');