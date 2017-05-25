<?php
function heydesk_user_login_submit($form, &$form_state) {
  $username = $form_state['values']['login']['name'];
  $password = $form_state['values']['login']['pass'];
  $account = heydesk_autoficate_user($username, $password);
  if ($account) {
    return TRUE;
  }
  else {
    $form_state['redirect'] = 'error-login';
  }


}

function heydesk_user_login_validation($form, &$form_state) {
  // return array('user_login_name_validate', 'user_login_authenticate_validate', 'user_login_final_validate');

}


function heydesk_form_register_submit($form, &$form_state) {
  $username = $form_state['values']['reg']['mail'];
  $password = $form_state['values']['reg']['pass_conf'];
  $useauto = heydesk_registrate_user($username, $password);
  // $login - heydesk_autoficate_user($username, $password,)
  if ($useauto) {
    $user = user_load($useauto->uid);
    $user_wrapper = entity_metadata_wrapper('user', $user);
    $user_wrapper->field_workspace->set($form_state['values']['workspace']);
    $user_wrapper->save();
    $form_state['redirect'] = 'user/' . $useauto->uid;
  }
}

function heydesk_register_validate($form, &$form_state) {
  // entity_form_field_validate('user', $form, $form_state);
}

//
//
//function heydesk_register_submit($form, &$form_state) {
//
//
//  $username => $form_state['values']['reg']['email'];
//      $password => $form_state['values']['reg ']['pass_conf'];
//$useauro = heydesk_registrate_user($username, $password);
//   if ($useauro) {
//     drupal_set_message(t('You is register'));
//
//     // user_login_finalize($form_state);
//     user_external_login_register($form_state['values']['reg']['email'], 'heydesk_user');
//     $form_state['redirect'] = 'user/' . $username->uid;
//   }
//}


function heydesk_facebook_login_callback() {
  require_once(drupal_get_path('module', 'heydesk_user') . '/facebook/vendor/autoload.php');

  $fb = new Facebook\Facebook([
    'app_id' => variable_get('heydesk_facebook_key', ''),
    'app_secret' => variable_get('heydesk_facebook_secret_key', ''),
    'default_graph_version' => 'v2.8',
    //    'default_access_token' => variable_get('heydesk_facebook_key', '').'|'.variable_get('heydesk_facebook_secret_key', '')


  ]);
  //        die($_SESSION['FBRLH_' . 'state']);
  //  $_SESSION['FBRLH_state']=$_GET['state'];


  $helper = $fb->getRedirectLoginHelper();
  if (isset($_GET['state'])) {
    $helper->getPersistentDataHandler()->set('state', $_GET['state']);
  }


  try {
    $accessToken = $helper->getAccessToken();
  } catch (Facebook\Exceptions\FacebookResponseException $e) {
    // When Graph returns an error
    echo 'Graphs returned an error: ' . $e->getMessage();
    exit;
  } catch (Facebook\Exceptions\FacebookSDKException $e) {
    // When validation fails or other local issues
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  };
  $_SESSION['fb_access_token'] = (string) $accessToken;
  //  $fb->setDefaultAccessToken('user-access-token');
  try {
    // Returns a `Facebook\FacebookResponse` object
    $response = $fb->get('/me?locale=en_US&fields=name,email,picture.type(large),birthday,location,first_name,last_name', $_SESSION['fb_access_token']);
  } catch (Facebook\Exceptions\FacebookResponseException $e) {
    echo 'Graph returned an error: ' . $e->getMessage();
    exit;
  } catch (Facebook\Exceptions\FacebookSDKException $e) {
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  }

  $user_fb = $response->getGraphUser();
  //  $picture = $response->getGraphPicture();
//  var_dump($user_fb['location']);
//  $avatar = $user_fb->getPicture();

//  var_dump($avatar['url']);
  //  var_dump($picture['url']);
//  exit;

  global $user;
  if ($user->uid == 0) {

    if (isset($user_fb['email'])) {
      $emails = db_select('users', 'u')
        ->fields('u', array('uid'))
        ->condition('u.mail', $user_fb['email'])
        ->execute()
        ->fetchCol();
      if (isset($emails[0])) {
        $user = user_load($emails[0]);


        if (isset($user->field_fasebook_id[LANGUAGE_NONE][0])) {

          $username = $user_fb['email'];
          $password = $user_fb['id'] . '@heydesk.com';
          $account = heydesk_autoficate_user($username, $password);
          if ($account) {
            return TRUE;
          }
          else {
            $form_state['redirect'] = 'error-login';
          }
        }
        else {

          $login_link = l(t('Login'), 'user', array('attributes' => array('class' => array(''))));


          $output = ' <div class="linkedin_callback">';
          $output .= '<h1>';
          $output .= t('Your mail is already registered on the site.');
          $output .= '</h1>';
          $output .= '<p>';
          $output .= t('Use the sign in form.');
          $output .= '</p>';
          $output .= '<div class="button">';
          $output .= $login_link;
          $output .= '</div>';
          $output .= '</div>';

          return $output;
        }


      }
      else {
        $birthday = isset($user_fb['birthday']) ? date('Y-m-d H:i:s', strtotime($user_fb['birthday'])) : '';
        $values = array(
          'name' => $user_fb['email'],
          'mail' => $user_fb['email'],
          'pass' => $user_fb['id'] . '@heydesk.com',
          'field_fasebook_id' => array(LANGUAGE_NONE => array(array('value' => $user_fb['id']))),
          'field_facebook_ver' => array(LANGUAGE_NONE => array(array('value' => 1))),
          'field_first_name' => array(LANGUAGE_NONE => array(array('value' => $user_fb['first_name']))),
          'field_surname' => array(LANGUAGE_NONE => array(array('value' => $user_fb['last_name']))),
          'field_date_of_birth ' => array(LANGUAGE_NONE => array(array('value' => $birthday))),
          'status' => 1,
          'init' => $user_fb['email'],
          'roles' => array(
            DRUPAL_AUTHENTICATED_RID => 'authenticated user',
          ),
        );

        $account = user_save('', $values);
        $account->password = $values['pass'];
        $form_state = array();
        $form_state['uid'] = $account->uid;
        user_login_submit(array(), $form_state);
        drupal_goto("user/" . $account->uid);


        // $result =  heydesk_autoficate_user($values['name'], $values['pass'], 'register ');
        //
        return $account;


      }
    }
    else {
      $names = db_select('users', 'u')
        ->fields('u', array('uid'))
        ->condition('u.mail', $user_fb['id'] . '@heydesk.com')
        ->execute()
        ->fetchCol();
      if (isset($names[0])) {
        $user = user_load($names[0]);
        $username = $user_fb['id'] . '@heydesk.com';
        $password = $user_fb['id'] . '@heydesk.com';

        $account = heydesk_autoficate_user($username, $password);
        if ($account) {
          return TRUE;
        }
        else {
          $form_state['redirect'] = 'error-login';
        }


      }
      else {
        $birthday = isset($user_fb['birthday']) ? date('Y-m-d H:i:s', strtotime($user_fb['birthday'])) : '';
        $values = array(
          'name' => $user_fb['name'],
          'mail' => $user_fb['id'] . '@heydesk.com',
          'pass' => $user_fb['id'] . '@heydesk.com',
          'field_fasebook_id' => array(LANGUAGE_NONE => array(array('value' => $user_fb['id']))),
          'field_facebook_ver' => array(LANGUAGE_NONE => array(array('value' => 1))),
          'field_first_name' => array(LANGUAGE_NONE => array(array('value' => $user_fb['first_name']))),
          'field_surname' => array(LANGUAGE_NONE => array(array('value' => $user_fb['last_name']))),
          'field_date_of_birth ' => array(LANGUAGE_NONE => array(array('value' => $birthday))),
          'status' => 1,
          'init' => $user_fb['id'] . '@heydesk.com',
          'roles' => array(
            DRUPAL_AUTHENTICATED_RID => 'authenticated user',
          ),
        );

        $account = user_save('', $values);
        $account->password = $values['pass'];
        $form_state = array();
        $form_state['uid'] = $account->uid;
        user_login_submit(array(), $form_state);
        drupal_goto("user/" . $account->uid);


        // $result =  heydesk_autoficate_user($values['name'], $values['pass'], 'register ');
        //
        return $account;


      }

    }
  }
  else {
    $user = user_load($user->uid);
    $user->field_facebook_ver[LANGUAGE_NONE][0]['value'] = 1;
    $user->field_fasebook_id[LANGUAGE_NONE][0]['value'] = $user_fb['id'];
    $user = user_save($user);
    if ($user) {
      drupal_goto('user/' . $user->uid . '/verifications');
    }


  }

  return $user_fb['id'];


}


function heydesk_facebook_share($proposal) {

  require_once(drupal_get_path('module', 'heydesk_user') . '/facebook/vendor/autoload.php');

  $fb = new Facebook\Facebook([
    'app_id' => variable_get('heydesk_facebook_key', ''),
    'app_secret' => variable_get('heydesk_facebook_secret_key', ''),
    'default_graph_version' => 'v2.8',
    'default_access_token' => variable_get('heydesk_facebook_key', '') . '|' . variable_get('heydesk_facebook_secret_key', '')


  ]);

  $linkData = [
    'link' => 'http:///heydesk.it-dev-lab.com/node/' . $proposal->nid,
    'message' => $proposal->title,
  ];

  $request = new FacebookRequest($_SESSION['fb_access_token'], 'POST', '/http://heydesk.it-dev-lab.com/node/40');

  $response = $request->execute();
  $graphObject = $response->getGraphObject();

  // if(!$_SESSION['fb_access_token']) {

  $helper = $fb->getJavaScriptHelper();

  try {
    $accessToken = $helper->getAccessToken();
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
    echo 'No cookie set or no OAuth data could be obtained from cookie.';
    exit;
  }

  // Logged in
  echo '<h3>Access Token</h3>';
  var_dump($accessToken->getValue());

  $_SESSION['fb_access_token'] = (string) $accessToken;


  try {
    $accessToken = $helper->getAccessToken();
  } catch (Facebook\Exceptions\FacebookResponseException $e) {
    // When Graph returns an error
    echo 'Graphs returned an error: ' . $e->getMessage();
    exit;
  } catch (Facebook\Exceptions\FacebookSDKException $e) {
    // When validation fails or other local issues
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  };
  $_SESSION['fb_access_token'] = (string) $accessToken;
  // }


  try {
    // Returns a `Facebook\FacebookResponse` object
    $response = $fb->post('/me/feed', $linkData, $_SESSION['fb_access_token']);
  } catch (Facebook\Exceptions\FacebookResponseException $e) {
    echo 'Graph returned an error: ' . $e->getMessage();
    exit;
  } catch (Facebook\Exceptions\FacebookSDKException $e) {
    echo 'Facebook SDK returned an error: ' . $e->getMessage();
    exit;
  }

  $graphNode = $response->getGraphNode();

  return $graphNode['id'];

}
