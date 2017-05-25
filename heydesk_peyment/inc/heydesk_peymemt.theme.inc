<?php
/**
 * Returns HTML for a simple table.
 */
function theme_simple($vars) {
  $form = $vars['form'];
  $rows = array();
  foreach (element_children($form) as $id) {
    if (isset($form[$id])) {
      $rows[] = array(
        'data' => array(
          drupal_render($form[$id]['date']),
          drupal_render($form[$id]['remittance']),
          drupal_render($form[$id]['payer_uid']),
          drupal_render($form[$id]['payee_ius']),
          drupal_render($form[$id]['description']),
        ),
        'class' => array(),
      );
    }
  }

  // Шапка таблицы.
  $header = array(
    t('Operation Date'),
    t('Amount'),
    t('Recipient'),
    t('Sender'),
    t('Description'),
  );
  dpm($rows);


  $output = theme('table', array(
    'header' => $form['#header'],
    'rows'  => $rows,
    'empty' => t('Table is empty', array()),
  ));

  $output .= drupal_render_children($form);
  return $output;
}