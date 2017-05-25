<?php
  $proposal_entity = node_load($booking->date);
  $user_node = node_load($booking->id);
  $user = user_load($user_node->uid);
  $days = _heydesk_coont_day($booking->date_from, $booking->date_to);
  $status = strip_tags(_heydesk_booking_status($booking->status));
?>
<?php
  if(ctype_digit($booking->price)){
    $price =  '$ ' . $booking->price . ',-';
  } else {
    $price = '$ -' . $booking->price;
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
  .rental-status {
    margin: 30px -60px 0;
    padding: 0 60px;
    border-top: 1px solid #333;
    border-bottom: 1px solid #333;
  }
  .rental-status .status-0 {
    color: #FF0A5E;
  }
  .rental-status .status-2 {
    color: #008E45;
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
            $rental_period =date('d, M - H:i', $booking->date_from) . ' > ' . date('d, M - H:i', $booking->date_to);
            print $rental_period;
          ?>
        </div>
        <div class="rental-price f-left">
          <?php print $price;?>
        </div>
      </div>
      <div class="rental-status lh-60">
        <div class="<?php print 'status-' . $booking->status; ?>">
          <?php
            print t('Status') . ': ' . $status;
          ?>
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
    ?>
    <div class="user-info f-left">
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
    </div>
  </div>
</div>
