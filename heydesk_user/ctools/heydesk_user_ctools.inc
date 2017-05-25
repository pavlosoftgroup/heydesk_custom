<?php
/**
 *  Implementation of hook_menu()
 */
//function heydesk_ctools_menu() {
//  $items = array();
//
//
//
//  return $items;
//}

/**
 * @param null $js
 * @return array
 */
function heydesk_ctools_validator_page_callback($form, &$form_state, $js = NULL) {

  heydesk_ctools_popup_style();
  $quey = db_select('field_data_field_phone_number', 'fn')
    ->fields('fn', array('entity_id'))
    ->condition('fn.field_phone_number_value', $form_state['values']['mobile_number']['mobile'])
    ->execute()
    ->fetchAll();

  if (isset($quey[0])) {
    $output = array();

    $popup_content = t('This phone number has been already used by another user');
    $output[] = ctools_modal_command_display(t('Validate'), $popup_content);
    // Выводим сформированное окно в браузере.
    print ajax_render($output);
    drupal_exit();

  }
  else{
    $_SESSION['mobile']['code'] = $form_state['values']['mobile_number']['code'];
    $_SESSION['mobile']['mobile'] = $form_state['values']['mobile_number']['mobile'];
     $_SESSION['response'] = heydesk_external_api_sms_callback($form_state['values']['mobile_number']['code'] . $form_state['values']['mobile_number']['mobile']);

    $form_state = array(
      'title' => t('Mobile Verification'),
      'ajax' => TRUE,
      'build_info' => array(
        'args' => array(),
      ),
    );

    //  dsm($form_state);
    form_load_include($form_state, 'inc', 'heydesk_user', 'ctools/validator.pages');

    $commands = ctools_modal_form_wrapper('validator_mobile_site_form', $form_state);
    print ajax_render($commands);
    drupal_exit();

    //  if (!empty($form_state['executed'])) {
    //    $commands = array();
    //
    //    $commands[] = ajax_command_html('#messages-wrapper', theme('status_messages'));
    //
    //    $commands[] = ctools_modal_command_dismiss();
    //  }
    //
    //  return array('#type' => 'ajax', '#commands' => $commands);
  }
}

/**
 * Implements hook_block_info().
 */
function heydesk_ctools_block_info() {
  $blocks['heydesk_ctools_validator'] = array(
    'info' => t('Mobile Verification'),
    'cache' => DRUPAL_NO_CACHE,
  );

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function heydesk_ctools_block_view($delta = '') {
  $block = array();

  if ($delta == 'heydesk_ctools_validator') {


    _heydesk_ctools_include_modal();

    $block['content'] = ctools_modal_text_button(t('Mobile Verification'), 'ctools/nojs/validator', t('Mobile Verification'), 'ctools-modal-heydesk_ctools-contact-style');
  }

  return $block;
}


/**
 *Popup’s setings function.
 */

function heydesk_ctools_popup_style() {

  static $added = FALSE;

  if ($added == FALSE) {

    $added = TRUE;

    // Підключаємо необхідні бібліотеки

    ctools_include('modal');

    ctools_include('ajax');

    ctools_modal_add_js();

    // Задаємо налаштування для попапа

    $heydesk_popup_style = array(
      'small-popup-style' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 560,
          'height' => 'auto',
          'addHeight' => 400,
        ),
        'modalOptions' => array(
          'opacity' => (float) 0.8,
          'background-color' => '#000000',
        ),
        'closeText' => '',
        'loadingText' => '',
        'animation' => 'fadeIn',
        'modalTheme' => 'heydesk_popup_custom_theme',
        'animationSpeed' => 'fast',
      ),
      'comment-popup-style' => array(
        'modalSize' => array(
          'type' => 'fixed',
          'width' => 600,
          'height' => 'auto',
          'addHeight' => 600,
        ),
        'modalOptions' => array(
          'opacity' => (float) 0.8,
          'background-color' => '#000000',
        ),
        'closeText' => '',
        'loadingText' => '',
        'animation' => 'fadeIn',
        'modalTheme' => 'heydesk_popup_custom_theme',
        'animationSpeed' => 'fast',
      ),
      'first-popup-style' => array(

        'modalSize' => array(

          'type' => 'fixed', // Тип попапа.

          'width' => 475, // Ширина

          'height' => 'auto', // Висота

          'addHeight' => 700, // Максимальна висота

        ),
        'modalOptions' => array(

          'opacity' => (float) 0.8, // Прозорість заднього фону

          'background-color' => '#000000', // Колір заднього фону

        ),
        'closeText' => '',
        // Текст для кнопки «close»

        'loadingText' => '',
        // Текст при завантаженні попапа

        'animation' => 'fadeIn',
        // Тип анімації

        'modalTheme' => 'heydesk_popup_custom_theme',
        // Назва теми, яку слід підключити

        'animationSpeed' => 'fast',
        // Швидкість анімації попапа

      ),

    );

    drupal_add_js($heydesk_popup_style, 'setting');
    ctools_add_js('small_popup_theme', 'heydesk_custom_function');


    ctools_add_js('heydesk_popup_style', 'heydesk_user');

  }

}