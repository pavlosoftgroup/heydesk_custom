<?php


function hyedesk_messenger_block_info() {
  $blocks['hyedesk_messenger_info'] = array(
    'info' => t('Messenger block Info'),
    'status' => FALSE,
  );
  return $blocks;
}

function hyedesk_messenger_block_view($delta = '') {
  switch ($delta) {
    case 'hyedesk_messenger_info':
      $block['subject'] = t('Social icon');
      $block['content'] = hyedesk_messenger_block_contents($delta);
      return $block;
      break;
  }
}

function hyedesk_messenger_block_contents($delta) {
  global $user;
  $count = db_select('hyedesk_messenger', 'hm')
    //  ->fields('hm.id')
    ->condition('hm.sid',  $user->uid)
    ->condition('hm.status', '1')
    ->countQuery()
    ->execute()
    ->fetchField();
  $counts = $count != 0 ? '<div class="couht_messages">' . $count . '</div>' : '';
  switch ($delta) {
    case 'hyedesk_messenger_info':
      $output = l('<div id="messanger">' . $counts . '<i class="fa fa-envelope-o" aria-hidden="true"></i></div>', 'user/' . $user->uid . '/messages', array(
        'html' => TRUE,
      ));
      return $output;
      break;
  }
}