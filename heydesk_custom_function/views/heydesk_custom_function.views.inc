<?php


/**
 * Implements hook_views_data().
 */
function heydesk_custom_function_views_data() {

  // Здесь идёт связывание моей таблицы с таблицей {node} по ключу nid.
  // Т.е. будет формироваться дополнительное условие вида
  // LEFT JOIN {example_attached_file} ON node.nid = example_attached_file.nid
  $data['heydesk_calendar']['table']['join']['node'] = array(
    'left_field' => 'nid', // Поле (ключ) из таблицы {node}
    'field' => 'pid',      // Поле (ключ) из таблицы {example_attached_file}
  );

  // Теперь указываем поле с данными, которое будет выводиться на экран
  $data['heydesk_calendar']['date_from'] = array(
    'title' => t('Availability (heydesk_celendar)'),
    'help' => 'sort proposal from date interval',
    'group' => t('Node'),
    'filter' => array('handler' => 'heydesk_custom_function_handler_filter_avialablity'), // Добавляем возможность фильтровать по этому полю
    'field'  => array('handler' => 'views_handler_field'), // Добавляем возможность добавлять значение этой колонки как поле во Views
//    'filter' => array('handler' => 'views_handler_filter_string'), // Добавляем возможность фильтровать по этому полю
//    'field'  => array('handler' => 'views_handler_field'), // Добавляем возможность добавлять значение этой колонки как поле во Views
  );
  return $data;
}

///**
// * My custom filter handler
// */
//class heydesk_custom_function_handler_filter_mycustomfilter extends views_handler_filter {
//  function operators() {
//    $operators = parent::operators();
//    // We won't be using regex in our example
//    unset($operators['regular_expression']);
//
//    return $operators;
//  }
//
//  function field_count() {
//    // Set the real field to the title of the node
//    $this->date_from = 'date';
//
//    $field = "$this->heydesk_calendar.$this->heydesk_calendar";
//    return "LENGTH($field)-LENGTH(REPLACE($field,' ',''))+1";
//  }
//
//  function op_between($field) {
//    $field_count = $this->field_count();
//
//    $min = $this->value['min'];
//    $max = $this->value['max'];
//
//    if ($this->operator == 'between') {
//      $this->query->add_where_expression($this->options['group'], "$field_count BETWEEN $min AND $max");
//    }
//    else {
//      $this->query->add_where_expression($this->options['group'], "($field_count <= $min) OR ($field_count >= $max)");
//    }
//  }
//
//  function op_simple($field) {
//    $field_count = $this->field_count();
//
//    $value = $this->value['value'];
//
//    $this->query->add_where_expression($this->options['group'], "$field_count $this->operator $value");
//  }
//}
//
///**
// * Implements hook_field_views_data().
//*/
//function heydesk_custom_function_field_views_data($field) {
//  $data = field_views_field_default_views_data($field);
//
//  foreach ($field['storage']['details']['sql'] as $type => $tables) {
//    foreach ($tables as $table_name => $columns) {
//      if (!isset($columns['updated'])) {
//        continue;
//      }
//
//      $data[$table_name]['table']['group'] = 'Heydesk';
//
//      $data[$table_name][$columns['updated']] = array(
//        'title' => t(''),
//        'help' => 'бла-бла-бла.',
//        'field' => array(
//          'handler' => 'views_handler_field_date',
//          'click sortable' => TRUE,
//        ),
//        'filter' => array(
//          'handler' => 'views_handler_filter_date',
//        ),
//        'sort' => array(
//          'handler' => 'views_handler_sort_date',
//        ),
//      );
//    }
//  }
//
//  return $data;
//}
