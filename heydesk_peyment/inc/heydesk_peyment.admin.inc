<?php

/**
 * Implements hook_theme().
 */
function heydesk_peymemt_theme() {
  return array(
    'simple' => array(
      'render element' => 'form',
      'file' => 'heydesk_peymemt.theme.inc',
    ),
  );
}

function heydesk_peymemt_get_all_payment() {
  return db_select('heydesk_peyment_remittance', 'hp')// Добавление возможности постраничного вывода.
  ->extend('PagerDefault')// Добавление возможности сортировки вместе с orderByHeader().
  ->extend('TableSort')->fields('hp', array(
    'id',
    'payer_uid',
    'payee_ius',
    'remittance',
    'date',
    'description',
    'payment'
  ))//    ->condition('hp.status', NODE_PUBLISHED)
  // Ограничиваем отображение нод тремя строками.
  //    ->limit(20)
  // Сортировка по шапке таблицы.
  //    ->orderByHeader($header)
  ->execute()->fetchCol;
}

function heydesk_peymemt_admin_page_form() {
  $site_account_value = entity_load('heydesk_peyment_account', array(9999999));
  $rows = array();
  //  dpm($site_account_value);
  //  if (!$site_account_value) {
  //
  //    $account = _heydesk_user_cash_account_create(9999999);
  //    $site_account_value= 0;
  //
  //
  //
  //  }

  //  $form['site_account'] = array(
  //    '#type' => 'markup',
  //    '#markup' => t('Site Cache Account: $ ') . $site_account_value[9999999]->expanse,
  //  );

  //  $reports = entity_load('heydesk_peyment', array());
  //  $reports = db_select('heydesk_peyment_remittance', 'hp')
  //    ->fields('hp', array())
  //    ->orderBy('hp.date', 'DESC')
  //    ->execute()
  //    ->fetchAll();

  $header = array(
    array('data' => t('Operation Date')),
    array('data' => t('Amount')),
    array('data' => t('RecipieFnt')),
    array('data' => t('Sender')),
    t('Description'),
  );
  //  $header = array(
  //    array('data' => t('Operation Date'), 'field' => 'hp.date'),
  //    array('data' => t('Amount'), 'field' => 'hp.remittance'),
  //    array('data' => t('RecipieFnt'), 'field' => 'hp.payer_uid'),
  //    array('data' => t('Sender'), 'field' => 'hp.payee_ius'),
  //    t('Description'),
  //  );
//  $bank = array(
//    'owner_id' => 9999999,
//    'expanse' => 0,
//    'status_key' => '',
//    'status' => 1,
//    'name' => t('Heydesk Site')
//  );
//  $account_heydesk = entity_create('heydesk_peyment_account', $bank);

  $reports = heydesk_peymemt_get_all_payment();
  $reports = entity_load('heydesk_peyment');
  dpm($reports);
  //  $form['peyment_table'] = array(
  //    '#type' => 'container',
  //    '#theme' => 'simple',
  //    // Передаем header в функцию темизации simple.
  //    '#header' => $header,
  //  );

  foreach ($reports as $rid => $report) {
    $description = $report->description . ' ' . $report->payment;


    $payer = $report->payer_uid != 0 ? user_load($report->payer_uid) : FALSE;
    $sendler = $report->payee_ius != 0 ? user_load($report->payee_ius) : FALSE;
    if (!$payer) {
      $peyer_markup = t('User Deleted');

    }
    elseif ($report->payer_uid == 0) {
      $peyer_markup = t('Bank');


    }
    else {
      $peyer_markup = l($payer->name, 'user/' . $payer->uid, array(
        'attributes' => array(
          'class' => array(
            'dark_link'
          )
        )
      ));

    }
    //    dsm($sendler);

    if (!$payer) {
      $peyer_markup = t('User Deleted');

    }
    elseif ( $report->payee_ius == 9999999) {
      $sendler_markup = t('Hydesk Site');

    }
    else {

      $sendler_markup = l($sendler->name, 'user/' . $sendler->uid, array(
        'attributes' => array(
          'class' => array(
            'dark_link'
          )
        )
      ));
    }

    $rows[] = array(
      date('d-m-Y H:i', $report->date),
      $report->remittance,
      $peyer_markup,
      $sendler_markup,
      $description
    );


    //    $form['peyment_table'][$rid]['date'] = array(
    //      '#markup' => date('d-m-Y H:i', $report->date),
    //    );
    //
    //
    //    $form['peyment_table'][$rid]['remittance'] = array(
    //      '#markup' => $report->remittance,
    //    );
    //
    //
    //    $form['peyment_table'][$rid]['payer_uid'] = array(
    //      '#markup' => $peyer_markup,
    //    );
    //
    //
    //    $form['peyment_table'][$rid]['payee_ius'] = array(
    //      '#markup' => $sendler_markup,
    //    );
    //
    //
    //    $form['peyment_table'][$rid]['description'] = array(
    //      '#markup' => $description,
    //    );


  }
  //  $form['pager']['#markup'] = theme('pager');

  //  dpm($form);
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'empty' => t('Table is empty', array()),
  ));
  return $output;


}
