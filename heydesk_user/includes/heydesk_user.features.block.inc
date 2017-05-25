<?php
//
//
//function heydesk_user_block_info() {
//  $blocks['heydesk_user_listing'] = array(
//    'info' => t('Features Listing (admin block)'),
//    'status' => TRUE,
//  );
//  return $blocks;
//}
//
//function heydesk_user_block_view($delta = '') {
//  switch ($delta) {
//    case 'heydesk_user_listing':
//      $block['subject'] = t('Features Listing (admin block)');
//      $block['content'] = hyedesk_user_listing_block_contents($delta);
//      return $block;
//      break;
//  }
//}
//
//function heydesk_user_block_contents($delta) {
//  global $user;
//
//  switch ($delta) {
//    case 'heydesk_user_listing':
//      $output = '<div id="features-listing_block"><div class="left-collumn">';
//      $output .= '<div class="fearst-text">' . t('Boost your workspace and Featured Listings get more rentals') . '</div>';
//      $output .= '<div class="red-text">' . t('Now you can highlight your workspace in search results!') . '</div>';
//      $output .= '<div class="small-text">' . t('You choose your personal ad text, and the period during
//which you want the top spot in the search results and
//highlighting on the front.') . '</div>';
//      $output .= '<div class="title-text">' . t('How to do it:') . '</div>';
//      $output .= '<div class="lost-text">' . t('1. Press the "Boost" 2. Enter your ad text and select period
//3. Pay with your Heydesk account') . '</div>';
//      $output .= '';
//      $output .= '';
//      $output .= '';
//      $output .= '</div><div class="right-collumn">';
//      $output .= '<div class="images_feature"></div>';
//      $output .= '';
//      $output .= '';
//      $output .= '</div></div>';
//
//
//      return $output;
//      break;
//  }
//}