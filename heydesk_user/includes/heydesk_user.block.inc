<?php
drupal_load('module', 'user');


function heydesk_user_block_info() {
  $blocks['heydesk_user_register'] = array(
    'info' => t('User Registration'),
    'status' => TRUE,
    'weight' => 0,
    'visibility' => 1,

  );
  $blocks['heydesk_user_account_links'] = array(
    'info' => t('Heydesk User Menu'),
    'status' => TRUE,
    'weight' => 0,
    'visibility' => 0,
    'region' => 'disable',
  );
  $blocks['heydesk_user_pay_account_block'] = array(
    'info' => t('Heydesk User Bill Account Block'),
    'status' => TRUE,
    'weight' => 0,
    'visibility' => 0,
    'region' => 'disable',

  );
  $blocks['heydesk_user_listing'] = array(
    'info' => t('Features Listing (admin block)'),
    'status' => TRUE,
  );
  $blocks['heydesk_user_proposal_mini'] = array(
    'info' => t('Mini Proposal Block'),
    'weight' => 0,
    'visibility' => 0,
    'region' => 'disable',
    'status' => TRUE,
  );
  $blocks['heydesk_user_invite'] = array(
    'info' => t('User Invite Block'),
    'weight' => 0,
    'visibility' => 0,
    'region' => 'disable',
    'status' => TRUE,
  );
  return $blocks;
}

function heydesk_user_block_view($delta = '') {
  switch ($delta) {
    case 'heydesk_user_proposal_mini':
      $block['subject'] = t('Mini Proposal Block');
      $block['content'] = heydesk_user_block_content($delta);
      return $block;
      break;
    case 'heydesk_user_register':
      $block['subject'] = t('User Registration');
      $block['content'] = heydesk_user_block_content($delta);
      return $block;
      break;

    case 'heydesk_user_account_links':
      $block['subject'] = t('Heydesk User Menu');
      $block['content'] = heydesk_user_block_content($delta);
      return $block;
      break;
    case 'heydesk_user_pay_account_block':
      $block['subject'] = t('User Bill Account Block');
      $block['content'] = heydesk_user_block_content($delta);
      return $block;
      break;
    case 'heydesk_user_listing':
      $block['subject'] = t('Features Listing (admin block)');
      $block['content'] = heydesk_user_block_content($delta);
      return $block;
      break;
    case 'heydesk_user_invite':
      $block['subject'] = t('User Invite Block');
      $block['content'] = heydesk_user_block_content($delta);
      return $block;
      break;
  }
}

function heydesk_invite_form($form, $form_state) {
  $form['email'] = array(
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('Enter Email Address')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send Invitations'),
    '#prefix' => '<div class="button"><a>',
    '#suffix' => '</a></div>',
    '#submit' => array('heydesk_invite_form_submit'),

  );


  return $form;

}

function heydesk_invite_form_submit($form, &$form_submit) {
  global $base_url;
  global $user;
  $invite_id = 100000 + (int) $user->uid;
  $invite_link = $base_url . '/invite/' . $invite_id;
  $link = l(variable_get('site_name', 'Heydesk'), $base_url . '/invite/' . $invite_id);
  $send = drupal_mail('system', 'mail', $form_submit['values']['email'], language_default(), array(
    'context' => array(
      'subject' => t('Invite Heydesk'),
      'message' => t('Something like join this platform that I am using @link', array('@link' => $invite_link)),
    )
  ));
}

function heydesk_user_block_content($delta) {
  global $user;
  global $base_url;
  $user_profile = user_load($user->uid);
  switch ($delta) {
    case 'heydesk_user_invite':
      drupal_add_js('http://connect.facebook.net/en_US/all.js');
      drupal_add_js(drupal_get_path('module', 'heydesk_external_api') . '/js/invite.js');

      $output = ' <div class="invite_wrapper">';
      $output .= '<div class="top">';
      $output .= '<h1>Spread The Word !</h1>';
      $output .= '<p>Together we can make it better</p>';
      $output .= '<div>';
      $output .= '<a class=\'login\' href=\'https://accounts.google.com/o/oauth2/auth?client_id=846515019155-vea9c05gm9s1mlhg9dqjikhogke3e10c.apps.googleusercontent.com&redirect_uri=http://heydesk.it-dev-lab.com/oauth2&scope=https://www.google.com/m8/feeds/&response_type=code\'>';
      $output .= '<div class="gmail">';
      $output .= '<div></div>';

      //      $output .= '<img src="" alt="">';
      $output .= '<p>Invite from Gmail</p>';
      $output .= '</div>';
      $output .='</a>';
      $output .= '<a href="mailto:">';
      $output .= '<div class="outlook">';
      $output .= '<div></div>';
      //      $output .= '<img src="" alt="">';
      $output .= '<p>Invite from Outlook</p>';
      $output .= '</div>';
      $output .= '</a>';
      $output .= '</div>';
      $output .= '</div>';
      $output .= '<div class="middle">';
      $output .= '<h4>Invite Friends via Email</h4>';
      $invite_form = drupal_get_form('heydesk_invite_form');
      $output .= render($invite_form);
      //      $output .= '<form class="">';
      //      $output .= '<input type="text" name="" value="" placeholder="Enter Email Address">';
      //      $output .= '<div class="button">';
      //      $output .= '<input type="submit" name="" value="Send Invitations">';
      //      $output .= '</div>';
      //      $output .= '</form>';
      $output .= '<div class="buttons">';
      $output .= '<div class="fbook" id="facebook-invite"><a href="#">Facebook</a></div>';
      $output .= '<div class="twit"><a target="_blank" href="https://twitter.com/share?url='.$base_url.'&text=Something like join this platform that I am using&hashtags=heydeask">Twitter</a></div>';
      $output .= '<div class="linkdin"><a href="">Linked In</a></div>';
      $output .= '</div>';
      $output .= '</div>';
      $output .= '<div class="foot">';
      $output .= '<p>Or Copy Your Personal Link</p>';
      $invite_id = 100000 + (int) $user->uid;
      $output .= '<div class="personal_link">' . $base_url . '/invite/' . $invite_id . '</div>';
      $output .= '</div>';
      $output .= '</div>';
      return $output;

      break;
    case 'heydesk_user_proposal_mini':
      $proposal = arg(4);
      $proposal = node_load($proposal);
//      dpm($proposal);
      $output = '';
      $body = field_view_field('node', $proposal, 'field_location_description', array(
        'label' => 'hidden',
        'type' => 'text_summary_or_trimmed',
        'settings' => array('trim_length' => 50),
      ));
      $output .= theme('image_style', array(
        'style_name' => 'proposal_200x170',
        'path' => file_uri_target($proposal->field_photos[LANGUAGE_NONE][0]['uri']),
        'title' => $proposal->title,
        'alt' => $proposal->title
      ));
      $output .= '<h3>' . $proposal->title . '</h3>';
      //      $output .= '<p class="description">';
      $output .= render($body);
      //      $output .= '</p>';
      $output .= '<p class="point_adress"><i class="fa fa-map-marker" aria-hidden="true"></i>';
      $output .= $proposal->field_address[LANGUAGE_NONE][0]['value'] . ', ' . _term_name($proposal->field_sities[LANGUAGE_NONE][0]['tid']) . ', ' . _term_name($proposal->field_country[LANGUAGE_NONE][0]['tid']);
      $output .= '</p>';


      return $output;
      break;


    case 'heydesk_user_listing':
      $output = '<div id="features-listing_block"><div class="left-collumn">';
      $output .= '<div class="fearst-text">' . t('Boost your workspace and Featured Listings get more rentals') . '</div>';
      $output .= '<div class="red-text">' . t('Now you can highlight your workspace in search results!') . '</div>';
      $output .= '<div class="small-text">' . t('You choose your personal ad text, and the period during
which you want the top spot in the search results and
highlighting on the front.') . '</div>';
      $output .= '<div class="title-text">' . t('How to do it:') . '</div>';
      $output .= '<div class="lost-text">';
      $output .= '<div>' . t('1. Press the "Boost"') . '</div>';
      $output .= '<div>' . t('2. Enter your ad text and select period"') . '</div>';
      $output .= '<div>' . t('3. Pay with your Heydesk account') . '</div>';
      $output .= '</div>';
      $output .= '';
      $output .= '';
      $output .= '';
      $output .= '';
      $output .= '</div><div class="right-collumn">';
      $output .= '<h5 class="manege-listing-featured-title">' . t('Featured Listing') . '</h5>';
      $output .= views_embed_view('sity', 'block_2');
      $output .= '';
      $output .= '';
      $output .= '</div></div>';


      return $output;
      break;
    case 'heydesk_user_pay_account_block':
      heydesk_ctools_popup_style();

      $query = db_select('heydesk_peyment_account', 'pa')
        ->fields('pa', array('expanse'))
        ->condition('pa.owner_id', $user->uid)
        ->execute()
        ->fetchCol();

      $output = '<div class="grey-block">';
      $output .= '<div class="summa">';
      $output .= '<h3>' . t('Your Heydesk Balance') . '</h3>';
      $output .= '<span class="costarible">$  -</span>';
      $output .= '<div class="price-num">';
      if ($query) {
        $output .= $query[0];
      }
      $output .= '</div>';
      $output .= '</div>';
      $output .= '</div>';
      $output .= '<a class="deposit_button" href="/user/' . $user->uid . '/deposit">' . t('Deposit') . '</a>';
      $output .= '<a class="earning_button" href="/user/' . $user->uid . '/earnings">' . t('Earnings') . '</a>';
      $output .= '<a class="withdraw_button ctools-use-modal ctools-modal-modal-popup-medium" href="/user/' . $user->uid . '/withdraw-money/nojs">' . t('Withdraw Money') . '</a>';



      return $output;
      break;

    case 'heydesk_user_register':
      $output = drupal_get_form('heydesk_user_register_form');
      return $output;
      break;
    case 'heydesk_user_account_links':

      $balance = db_select('heydesk_peyment_account', 'pa')
        ->fields('pa', array('expanse'))
        ->condition('pa.owner_id', $user->uid)
        ->execute()
        ->fetchCol();
      $balance = isset($balance[0]) ? $balance[0] : 0;
      $balance = '<span class="banamce-menu">$ ' . $balance . '</span>';
      $output = '<div id="user_top_menu">';
      $output .= '<div class="name_header">';

      //      $name_user = drupal_render(field_view_field('user', $user_profile, 'field_surname', array('label' => 'hidden')));
      $output .= _heydesk_user_name($user->uid);
      $output .= l(t('View Profile'), 'user/' . $user->uid, array('attributes' => array('class' => array('red_link'))));
      $output .= '</div>';
      $output .= l(t('Invite Your Friends'), 'node/106', array('attributes' => array('id' => 'mail-invites')));
      $output .= l(t('Manage Listings'), 'user/' . $user->uid . '/manage-listing');
      $output .= l(t('Your Balance') . $balance, 'user/' . $user->uid . '/balance', array(
        'html' => TRUE
      ));
      $output .= l(t('Verifications'), 'user/' . $user->uid . '/verifications');
      $output .= l(t('Listings Overview'), 'user/' . $user->uid . '/listing-overview');
      $output .= l(t('Booking Overview'), 'user/' . $user->uid . '/booking-overview');
      $output .= l(t('Account Settings'), 'user/' . $user->uid . '/setting');
      $output .= l(t('Log Out'), 'user/logout');


      $output .= '';
      $output .= '';
      $output .= '';
      $output .= '';
      $output .= '';
      $output .= '';
      $output .= '';


      $output .= '</div>';
      //      $output .= '</div>';


      //      $output .= '</div>';

      return $output;
      break;
  }
}

function heydesk_user_register_form($form, &$form_state) {
  global $user;
  global $base_url;


  $form['top_button'] = array(
    '#type' => 'markup',
    '#markup' => '<div id="user-form-button"><a href="#sign_up" id="sign_up_button">' . t('Sign Up') . '</a><a href="#log_in" id="log_in_button">' . t('Log In') . '</a><div class="close"></div></div>',
  );

  $form['first'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="register-form show_this" id="sign_up">'
  );

  $form['header'] = array(
    '#type' => 'fieldset',

  );

  $form['header']['up'] = array(
    '#type' => 'merkup',
    '#markup' => '<div class="up-button">' . t('Sign Up') . '</div>'
  );
  $form['header']['in'] = array(
    '#type' => 'merkup',
    '#markup' => '<div class="in-button">' . t('Sign In') . '</div>'
  );
  $form['body'] = array(
    '#type' => 'fieldset',

  );
  $markup = '<div class="top_form">' . t('Are You Renting or Searching for Workspace?') . '</div>';
  $markup .= '<div class="top_bottom_form">' . t('* Please select one, you can always change it later in your dashboard') . '</div>';
  $form['body']['top'] = array(
    '#type' => 'markup',
    '#markup' => $markup,
  );
  // $two_button = '<div class="top"><div class="left_image"><span></span><div class="text">' . t('Renting Out a Work Space') . '</div></div>';
  // $two_button .= '<div class="right_image"><span></span><div class="text">' . t('Searching for a Work Space') . '</div></div></div>';

  // $form['body']['title'] = array(
  //   '#type' => 'markup',
  //   '#markup' => $two_button,
  // );

  $active = array(
    0 => '<div class="icon"></div><div class="text">Renting Out a Work Space</div>',
    1 => '<div class="icon"></div><div class="text">Searching for a Work Space</div>'
  );
  $form['workspace'] = array(
    '#type' => 'radios',
    '#default_value' => 0,
    '#options' => $active,
  );

  $form['social'] = array(
    '#type' => 'fieldset',
  );
  $form['social']['facebook'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="facebook_button">' . heydesk_facebook_login() . '</div>',

  );
  //  $form['social']['facebook'] = array(
  //    '#type' => 'submit',
  //    '#value' => t('Log in with Facebook'),
  //    '#attributes' => array('class' => array('facebook_button')),
  //    '#submit' => array('heydesk_facebook_login')
  //  );
  $linkedin_link = '?response_type=code&client_id=' . variable_get('heydesk_linkedin_key', '') . '&redirect_uri=' . $base_url . '%2Flinkedin&scope=r_basicprofile%20r_emailaddress';
  $form['social']['linkedin'] = array(
    '#type' => 'link',
    '#title' => t('Sign in with Linked In'),
    '#href' => 'https://www.linkedin.com/oauth/v2/authorization' . $linkedin_link,
    '#options' => array(
      'attributes' => array(
        'class' => array('linked-in')
      ),
      'html' => TRUE
    ),
    //  '#markup' => '<script type="in/Login"></script>',
    //  '#value' => t('Sign in with Linked In'),
    //  '#attributes' => array('class' => array('linkedin_button')),
    //  '#submit' => array('heydesk_linkedin_login')
  );
  $form['or'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="or">or</div>',
  );
  $form['reg'] = array(
    '#type' => 'markup',
    '#tree' => TRUE,
  );

  $form['reg']['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Mail')
  );

  $form['reg']['pass_conf'] = array(
    '#type' => 'password_confirm',
    //  '#title' => t('Password Confirm')
  );

  $form['reg']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Sign Up'),
    '#attributes' => array('class' => array('button-submit')),
    '#validate' => array('heydesk_register_validate'),
    '#submit' => array('heydesk_form_register_submit'),
  );
  $form['first_2'] = array(
    '#type' => 'markup',
    '#markup' => '</div><div class="login-form show_this" id="log_in" >',
  );


  $form['social_login'] = array(
    '#type' => 'fieldset',
  );
  $form['social_login']['facebook'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="facebook_button">' . heydesk_facebook_login() . '</div>',

  );
  //  $form['social']['facebook'] = array(
  //    '#type' => 'submit',
  //    '#value' => t('Log in with Facebook'),
  //    '#attributes' => array('class' => array('facebook_button')),
  //    '#submit' => array('heydesk_facebook_login')
  //  );
  $linkedin_link = '?response_type=code&client_id=' . variable_get('heydesk_linkedin_key', '') . '&redirect_uri=' . $base_url . '%2Flinkedin&scope=r_basicprofile%20r_emailaddress';
  $form['social_login']['linkedin'] = array(
    '#type' => 'link',
    '#title' => t('Sign in with Linked In'),
    '#href' => 'https://www.linkedin.com/oauth/v2/authorization' . $linkedin_link,
    '#options' => array(
      'attributes' => array(
        'class' => array('linked-in')
      ),
      'html' => TRUE
    ),
    //  '#markup' => '<script type="in/Login"></script>',
    //  '#value' => t('Sign in with Linked In'),
    //  '#attributes' => array('class' => array('linkedin_button')),
    //  '#submit' => array('heydesk_linkedin_login')
  );
  $form['or_login'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="or">or</div>',
  );

  $form['login'] = array(
    '#type' => 'markup',
    '#tree' => TRUE,

  );

  $form['login']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('* Mail')
  );
  $form['login']['pass'] = array(
    '#type' => 'password',
    '#title' => t('* Password')
  );
  $form['login']['text'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="text_every">' . t('Still haven’t got an account?') . '<div class="bottom_texr">' . t('Sign Up Now !') . '</div></div>',
  );
  $form['#validate'] = user_login_default_validators();

  $form['login']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Log In'),
    '#attributes' => array('class' => array('button-submit')),
    '#validate' => array('heydesk_user_login_validation'),
    '#submit' => array('heydesk_user_login_submit'),
    '#suffix' => l(t('Forgot Password'), 'user/password'),
  );
  $form['first_3'] = array(
    '#type' => 'markup',
    '#markup' => '</div>',
  );

  return $form;
}


//    $user = user_load($id);
//    user_login_finalize();
//    $email_gen = $form_state['values']['reg']['pass_conf'];
//    $user = user_save('', $newuser);
//    if (user_authenticate($email_gen, $pass_gen)) :
//      $user_object = user_load_by_name($email_gen);
//      $form_state = array();
//      $form_state['uid'] = $user_object->uid;
//      return true;
//
//    $autofication = user_authenticate($form_state['values']['reg']['email'], $form_state['values']['reg']['pass_conf']);
//    $user_object = user_load_by_name($form_state['values']['reg']['email']);
//    $form_state = array();
//    $form_state['uid'] = $user_object->uid;
//    $useauro = user_login_submit(array(), $form_state);
//
//    if ($useauro) {
//      $user->password = $pass; // Add plain text password into user account to generate mail tokens.
//      _user_mail_notify('register_no_approval_required', $user);
//
//      drupal_set_message('DONE!');
//      $form_state['redirect'] = 'user/' . $user->uid;
//    }
//    else {
//      drupal_set_message('Missed!');
//      $form_state['redirect'] = 'user';
//
//      //    break;
//    }


//
//
//function heydesk_drupal_register_submit_old($form, &$form_state) {
//
//
//  $admin = $form_state['values']['administer_users'];
//
//  if (!variable_get('user_email_verification', TRUE) || $admin) {
//    $pass = $form_state['values']['reg']['pass'];
//  }
//  else {
//    $pass = user_password();
//  }
//  $notify = !empty($form_state['values']['notify']);
//
//  // Remove unneeded values.
//  form_state_values_clean($form_state);
//
//  $form_state['values']['reg']['pass'] = $pass;
//  $form_state['values']['init'] = $form_state['values']['reg']['mail'];
//
//  $account = $form['#user'];
//
//  entity_form_submit_build_entity('user', $account, $form, $form_state);
//
//  // Populate $edit with the properties of $account, which have been edited on
//  // this form by taking over all values, which appear in the form values too.
//  $edit = array_intersect_key((array) $account, $form_state['values']);
//  $account = user_save($account, $edit);
//
//  // Terminate if an error occurred during user_save().
//  if (!$account) {
//    drupal_set_message(t("Error saving user account."), 'error');
//    $form_state['redirect'] = '';
//    return;
//  }
//  $form_state['user'] = $account;
//  $form_state['values']['uid'] = $account->uid;
//
//  watchdog('user', 'New user: %name (%email).', array(
//    '%name' => $form_state['values']['reg']['mail'] . mt_rand(5, 15),
//    '%email' => $form_state['values']['reg']['mail']
//  ), WATCHDOG_NOTICE, l(t('edit'), 'user/' . $account->uid . '/edit'));
//
//  // Add plain text password into user account to generate mail tokens.
//  $account->password = $pass;
//
//  // New administrative account without notification.
//  $uri = entity_uri('user', $account);
//  if ($admin && !$notify) {
//    drupal_set_message(t('Created a new user account for <a href="@url">%name</a>. No e-mail has been sent.', array(
//      '@url' => url($uri['path'], $uri['options']),
//      '%name' => $account->name
//    )));
//  }
//  // No e-mail verification required; log in user immediately.
//  elseif (!$admin && !variable_get('user_email_verification', TRUE) && $account->status) {
//    _user_mail_notify('register_no_approval_required', $account);
//    $form_state['uid'] = $account->uid;
//    user_login_submit(array(), $form_state);
//    drupal_set_message(t('Registration successful. You are now logged in.'));
//    $form_state['redirect'] = '';
//  }
//  // No administrator approval required.
//  elseif ($account->status || $notify) {
//    $op = $notify ? 'register_admin_created' : 'register_no_approval_required';
//    _user_mail_notify($op, $account);
//    if ($notify) {
//      drupal_set_message(t('A welcome message with further instructions has been e-mailed to the new user <a href="@url">%name</a>.', array(
//        '@url' => url($uri['path'], $uri['options']),
//        '%name' => $account->name
//      )));
//    }
//    else {
//      drupal_set_message(t('A welcome message with further instructions has been sent to your e-mail address.'));
//      $form_state['redirect'] = '';
//    }
//  }
//  // Administrator approval required.
//  else {
//    _user_mail_notify('register_pending_approval', $account);
//    drupal_set_message(t('Thank you for applying for an account. Your account is currently pending approval by the site administrator.<br />In the meantime, a welcome message with further instructions has been sent to your e-mail address.'));
//    $form_state['redirect'] = 'user/' . $account->uid;
//  }
//}


function heydesk_facebook_login_old() {
  require_once(drupal_get_path('module', 'heydesk_user') . '/facebook/vendor/autoload.php');

  global $base_url;
  $fb = new Facebook\Facebook([
    'app_id' => variable_get('heydesk_facebook_key', ''),
    'app_secret' => variable_get('heydesk_facebook_secret_key', ''),
    'default_graph_version' => 'v2.8',

  ]);

  $_SESSION['FBRLH_state'] = $_GET['state'];
  //  $_SESSION['FBRLH_state']=$_GET['state'];


  $helper = $fb->getRedirectLoginHelper();

  $permissions = ['email']; // Optional permissions
  $loginUrl = $helper->getLoginUrl($base_url . '/facebook', $permissions);

  //  print ('<a href="' . htmlspecialchars($loginUrl) . '">Log in with Facebook!</a>');
  // $form_state['redirect'] = $loginUrl;
  $link = l(t('Facebook Log In'), $loginUrl, array('attributes' => array('class' => array('facebook_button'))));
  //  $link ='<a href="' . htmlspecialchars($loginUrl) . '">Log in with Facebook!</a>';
  return $link;


}


function heydesk_facebook_login_callback_old() {
  //          die($_SESSION['FBRLH_' . 'state']);
  //  die($_SESSION['FBRLH_' . 'state']);
  if (!session_id()) {
    session_start();
  }

  require_once(drupal_get_path('module', 'heydesk_user') . '/facebook/vendor/autoload.php');
  //  $_SESSION['FBRLH_state'] = $_GET['state'];

  $fb = new Facebook\Facebook([
    'app_id' => variable_get('heydesk_facebook_key', ''),
    'app_secret' => variable_get('heydesk_facebook_secret_key', ''),
    'default_graph_version' => 'v2.8',

  ]);
  //    $_SESSION['FBRLH_state'] = $_GET['state'];

  $helper = $fb->getRedirectLoginHelper();

  try {
    $accessToken = $helper->getAccessToken();
    //    die($_SESSION['FBRLH_' . 'state']);
  } catch (Facebook\Exceptions\FacebookResponseException $e) {
    // When Graph returns an error
    echo 'Graph returned an error: ' . $e->getMessage();
    exit;
  } catch (Facebook\Exceptions\FacebookSDKException $e) {
    // When validation fails or other local issues
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  }

  if (!isset($accessToken)) {
    if ($helper->getError()) {
      header('HTTP/1.0 401 Unauthorized');
      echo "Error: " . $helper->getError() . "\n";
      echo "Error Code: " . $helper->getErrorCode() . "\n";
      echo "Error Reason: " . $helper->getErrorReason() . "\n";
      echo "Error Description: " . $helper->getErrorDescription() . "\n";
    }
    else {
      header('HTTP/1.0 400 Bad Request');
      echo 'Bad request';
    }
    exit;
  }

  // Logged in
  echo '<h3>Access Token</h3>';
  var_dump($accessToken->getValue());

  // The OAuth 2.0 client handler helps us manage access tokens
  $oAuth2Client = $fb->getOAuth2Client();

  // Get the access token metadata from /debug_token
  $tokenMetadata = $oAuth2Client->debugToken($accessToken);
  echo '<h3>Metadata</h3>';
  var_dump($tokenMetadata);

  // Validation (these will throw FacebookSDKException's when they fail)
  $tokenMetadata->validateAppId(variable_get('heydesk_facebook_key', '')); // Replace {app-id} with your app id
  // If you know the user ID this access token belongs to, you can validate it here
  //$tokenMetadata->validateUserId('123');
  $tokenMetadata->validateExpiration();

  if (!$accessToken->isLongLived()) {
    // Exchanges a short-lived access token for a long-lived one
    try {
      $accessToken = $oAuth2Client->getLongLivedAccessToken($accessToken);
    } catch (Facebook\Exceptions\FacebookSDKException $e) {
      echo "<p>Error getting long-lived access token: " . $helper->getMessage() . "</p>\n\n";
      exit;
    }

    echo '<h3>Long-lived</h3>';
    var_dump($accessToken->getValue());
  }

  $_SESSION['fb_access_token'] = (string) $accessToken;


}

function no_login_fb($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield0',
    '#default_value' => '',
  );
  return $form;
}

////////////////////////////////

function heydesk_facebook_login() {
  global $base_url;

  $url_callback = $base_url . '/facebook';
  require_once(drupal_get_path('module', 'heydesk_user') . '/facebook/app/FacebookApp.php');
  $fb = new Facebook\Facebook([
    'app_id' => variable_get('heydesk_facebook_key', ''),
    'app_secret' => variable_get('heydesk_facebook_secret_key', ''),
    'default_graph_version' => 'v2.8',


  ]);
  $helper = $fb->getRedirectLoginHelper();

  $permissions = ['email, publish_actions']; // Optional permissions
  //  die($_SESSION['FBRLH_' . 'state']);
  $loginUrl = $helper->getLoginUrl($url_callback, $permissions);
  $link = l(t('Facebook Log In'), $loginUrl, array('attributes' => array('class' => array('wrap_fbook_submit'))));


  //  return '<a href="' . htmlspecialchars($loginUrl) . '">Log in with Facebook!</a>';
  return $link;

}


