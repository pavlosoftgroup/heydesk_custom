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
<style>
  .listing-popup {
    font-family: 'dosis', sans-serif;
  }
  .boosting-top {
    padding: 40px 60px;
    background-color: #eaeaea;
    border-top-left-radius: 16px;
    border-top-right-radius: 16px;
    font-size: 26px;
    margin-bottom: 50px;
  }
  .f-left {
    float: left;
  }
  .proposal_image {
    width: 210px;
  }
  .proposal_info {
    margin-top: 40px;
  }
  .modal-proposal-address {
    font-size: 20px;
  }
  .proposal-details {
    padding: 0 60px;
    margin-bottom: 40px;
    font-size: 26px;
  }
  .rental-dates {
    width: 75%;
  }
  .rental-price {
    width: 25%;
    text-align: right;
  }
  .lh-40 {
    line-height: 40px;
  }
  .lh-60 {
    line-height: 60px;
  }
  .rental-earn {
    background: linear-gradient(to right, rgba(255, 12, 93, 1) 0%, rgba(255, 137, 63, 1) 100%);
    color: #fff;
    margin: 30px -60px 0;
    padding: 0 60px;
  }
  .user-details {
    padding: 0 60px;
    font-size: 26px;
  }
  .user-photo {
    width: 80px;
  }
  .user-info {
    margin-left: 20px;
  }
</style>
<div class="listing-popup">
  <div class="boosting-top">
    <div class="proposal_image f-left">
      <?php
        $img_url = $proposal_entity->field_photos[LANGUAGE_NONE][0]['uri'];
        print theme('image_style', array('style_name' => 'user_150x150', 'path' => $img_url));
      ?>
    </div>
    <div class="proposal_info f-left">
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
            $address .= ($term->name) ? ucfirst($term->name) .', ' : '';
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
  <div class="proposal-details">
    <div class="rental-info lh-40">
      <div class="rental-days">
        <div>
          <?php
            print t('Rental Price') . ' (' . $days . ' ' .t('days') .')';
          ?>
        </div>
      </div>
      <div class="rental-dates-price">
        <div class="rental-dates f-left">
          <?php
            $rental_period =date('d, M - H:i', $listing->date_from) . ' > ' . date('d, M - H:i', $listing->date_to);
            print $rental_period;
          ?>
        </div>
        <div class="rental-price f-left">
          <?php print $price;?>
        </div>
      </div>
      <div class="rental-earn lh-60">
        <div class="rental-dates f-left">
          <?php print t('You Earn')?>
        </div>
        <div class="rental-price f-left">
          <?php print $price;?>
        </div>
      </div>
    </div>
  </div>
  <div class="user-details">
    <div class="user-photo f-left">
      <?php
        $user_img_url = $user->picture->uri;
        print theme('image_style', array('style_name' => 'user_40x40-copy', 'path' => $user_img_url));
      ?>
    </div>
    <?php
      $user_name = ucfirst($user->field_first_name[LANGUAGE_NONE][0]['value']) . ' ' . ucfirst($user->field_surname[LANGUAGE_NONE][0]['value']);
      $user_mobile = '+' . $user->field_phone_code[LANGUAGE_NONE][0]['value'] . ' ' . $user->field_phone_number[LANGUAGE_NONE][0]['value'];
      $user_email = $user->mail;
      $user_birth = isset($user->field_date_of_birth[LANGUAGE_NONE][0]['value']) ? date('m/d/Y', strtotime($user->field_date_of_birth[LANGUAGE_NONE][0]['value'])) : '';
    ?>
    <div class="user-info f-left">
      <div>
        <span class="f-left"><?php print t('Name') . ':';?></span>
        <span class="f-left"><?php print $user_name;?></span>
      </div>
      <div>
        <span class="f-left"><?php print t('Mobile') . ':';?></span>
        <span class="f-left"><?php print $user_mobile;?></span>
      </div>
      <div>
        <span class="f-left"><?php print t('E-mail') . ':';?></span>
        <span class="f-left"><?php print $user_email;?></span>
      </div>
      <div>
        <span class="f-left"><?php print t('Date of Birth') . ':';?></span>
        <span class="f-left"><?php print $user_birth;?></span>
      </div>
    </div>
  </div>
</div>
