<?php
  $proposal_entity = node_load($listing->date);
  $user = user_load($listing->uid);
  $days = _heydesk_coont_day($listing->date_from, $listing->date_to);
?>
<?php
  if(ctype_digit($listing->price)){
    $price =  '$ ' . $listing->price . ',-';
  } else {
    $price = '$ -' . $listing->price;
  }
?>
<div class="listing-popup">
  <div class="boosting-top">
    <div class="proposal_view">
      <div class="proposal_image">
        <?php
          $img_url = $proposal_entity->field_photos[LANGUAGE_NONE][0]['uri'];
          print theme('image_style', array('style_name' => 'user_150x150', 'path' => $img_url));
        ?>
      </div>
      <div class="proposal_info">
        <div class="modal-proposal-title">
          <?php print $proposal_entity->title;?>
        </div>
        <div class="modal-proposal-address">
          <i class="fa fa-map-marker" aria-hidden="true"></i>
          <?php
            $address = '';
            if(isset($proposal_entity->field_address[LANGUAGE_NONE][0]['value'])){
              $address .= $proposal_entity->field_address[LANGUAGE_NONE][0]['value'] .', ';
            }
            if(isset($proposal_entity->field_sities[LANGUAGE_NONE][0]['tid'])){
              $term = taxonomy_term_load($proposal_entity->field_sities[LANGUAGE_NONE][0]['tid']);
              $address .= ucfirst($term->name) .', ';
            }
            if(isset($proposal_entity->field_country[LANGUAGE_NONE][0]['tid'])){
              $term = taxonomy_term_load($proposal_entity->field_country[LANGUAGE_NONE][0]['tid']);
              $address .= ucfirst($term->name);
            }
            print $address;
          ?>
        </div>
      </div>
    </div>
  </div>
  <div class="proposal-details">
    <div class="rental-info">
      <div class="rental-days">
        <span>
          <?php
            print t('Rental Price') . ' (' . $days . ' ' .t('days') .')';
          ?>
        </span>
      </div>
      <div class="rental-dates-price">
        <span class="rental-dates">
          <?php
            $rental_period =date('d, M - H:i', $listing->date_from) . ' > ' . date('d, M - H:i', $listing->date_to);
            print $rental_period;
          ?>
        </span>
        <span class="rental-price">
          <?php print $price;?>
        </span>
      </div>
      <div class="rental-earn">
        <span class="earn-text">
          <?php print t('You Earn')?>
        </span>
        <span class="earn-price">
          <?php print $price;?>
        </span>
      </div>
    </div>
  </div>
  <div class="user-details">
    <div class="user-photo">
      <?php
        $user_img_url = $user->picture->uri;
        print theme('image_style', array('style_name' => 'user_40x40', 'path' => $user_img_url, 'attributes' => array('class' => array('user-image'))));
      ?>
    </div>
    <?php
      $user_name = ucfirst($user->field_first_name[LANGUAGE_NONE][0]['value']) . ' ' . ucfirst($user->field_surname[LANGUAGE_NONE][0]['value']);
      $user_mobile = '+' . $user->field_phone_code[LANGUAGE_NONE][0]['value'] . ' ' . $user->field_phone_number[LANGUAGE_NONE][0]['value'];
      $user_email = $user->mail;
      $user_birth = date('m/d/Y', strtotime($user->field_date_of_birth[LANGUAGE_NONE][0]['value']));
      // $user_booking = '';
    ?>
    <div class="user-info">
      <div>
        <span><?php print t('Name') . ':';?></span>
        <span><?php print $user_name;?></span>
      </div>
      <div>
        <span><?php print t('Mobile') . ':';?></span>
        <span><?php print $user_mobile;?></span>
      </div>
      <div>
        <span><?php print t('E-mail') . ':';?></span>
        <span><?php print $user_email;?></span>
      </div>
      <div>
        <span><?php print t('Date of Birth') . ':';?></span>
        <span><?php print $user_birth;?></span>
      </div>
      <!-- <div>
        <span><?php print t('Booking Date') . ':';?></span>
        <span><?php print $user_booking;?></span>
      </div> -->
    </div>
  </div>
</div>
