			$this->col<%= $objColumn->PropertyName %> = new QDataGridColumn(QApplication::Translate('<%= QConvertNotation::WordsFromCamelCase($objColumn->PropertyName) %>'), '<?= $_FORM->dtg<%= $objTable->ClassName %>_<%= $objColumn->Reference->PropertyName %>_Render($_ITEM); ?>');