<?php

function validator_mobile_site_form($form, &$form_state) {

  $form['validator'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enter Code in SMS'),
    '#attributes' => array('class' => array('row')),
//    '#tree' => TRUE
  );
//  $form['validator']['error_markup'] = array(
//    '#type' => 'markup',
//    '$markup' => '<div class="error"></div>'
//  );
  $form['validator']['coder'] = array(
    '#type' => 'textfield',
    '#attributes' => array('class' => array('cg-fg-4')),
    '#size' => 5,

  );
//  $form['validator']['number'] = array(
//    '#type' => 'fieldset',
//    '#attributes' => array('class' => array('df-df-7')),
//    '#size' => 7,
//
//  );
  $form['validator']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Validate'),
    '#ajax' => array(
//      'wrapper' => 'body',
      'callback' => 'validator_mobile_site_form_submit',
    ),
  );
  return $form;
}

function validator_mobile_site_form_submit($form, &$form_state) {

  $status_code = heydesk_external_api_sms_response($form_state['values']['coder'], $_SESSION['response']);
//dpm($status_code);
  //  drupal_add_js('https://payment.quickpay.net/embedded/v1/quickpay.js');
  heydesk_ctools_popup_style();

  $commands = array();

  if ($status_code == 0) {
    dpm($status_code);
    global $user;
    $user = user_load($user->uid);
    $user->field_mobile_varifity[LANGUAGE_NONE][0]['value'] = 1;
    $user->field_phone_code[LANGUAGE_NONE][0]['value'] =  $_SESSION['mobile']['code'];
    $user->field_phone_number[LANGUAGE_NONE][0]['value'] = $_SESSION['mobile']['mobile'];
    $user = user_save($user);

    unset($_SESSION['response']);
    unset($_SESSION['mobile']);




  }
  $commands[] = ctools_ajax_command_reload();
  //  else {
//    $html = t('Invalide code');
//    $commands[] = ajax_command_prepend('#validator-mobile-site-form legend span', $html);
//
//  }
  return array('#type' => 'ajax', '#commands' => $commands);


}