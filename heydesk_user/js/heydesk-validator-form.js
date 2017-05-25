(function ($) {


    Drupal.behaviors.heydesk_user_validate_form = {
        attach: function (context, settings) {


            $(document).ajaxSuccess(function (event, request, settings) {
                var wripperId = '';
                var hidenInputId = '';
                switch (settings.extraData['_triggering_element_name']) {
                    case "id_validator_photo_profile_remove_button":
                        wripperId = '#edit-id-validator-photo-profile-ajax-wrapper';
                        hidenInputId = '#edit-id-validator-photo-profile-upload--2';

                        break;
                    case  "id_validator_photo_img_cart_front_remove_button":
                        wripperId = '#edit-id-validator-photo-img-cart-front-ajax-wrapper';
                        hidenInputId = '#edit-id-validator-photo-img-cart-front-upload--2';

                        break;
                    case 'id_validator_photo_img_cart_back_remove_button':
                        wripperId = '#edit-id-validator-photo-img-cart-back-ajax-wrapper';
                        hidenInputId = '#edit-id-validator-photo-img-cart-back-upload--2';

                        break;
                    case 'id_validator_photo_img_cart_security_remove_button':
                        wripperId = '#edit-id-validator-photo-img-cart-security-ajax-wrapper';
                        hidenInputId = '#edit-id-validator-photo-img-cart-security-upload--2';

                        break;
                    case "id_validator_photo_profile_upload_button":
                        wripperId = '#edit-id-validator-photo-profile-ajax-wrapper';
                        break;
                    case  "id_validator_photo_img_cart_front_upload_button":
                        wripperId = '#edit-id-validator-photo-img-cart-front-ajax-wrapper';

                        break;
                    case 'id_validator_photo_img_cart_back_upload_button':
                        wripperId = '#edit-id-validator-photo-img-cart-back-ajax-wrapper';

                        break;
                    case 'id_validator_photo_img_cart_security_upload_button':
                        wripperId = '#edit-id-validator-photo-img-cart-security-ajax-wrapper';

                        break;

                }
                //var buttonActSubmit = '#' + settings.extraData['_triggering_element_name'];
                var wripperForm = $("#edit-id-validator-photo .fieldset-wrapper");
                $(wripperId, context).once('ajax', function () {


                    console.log(settings.extraData['_triggering_element_value']);

                    if (settings.extraData['_triggering_element_value'] == 'Remove') {
                        //console.log(hidenInputId);



                        $(wripperId + " label", context).append('<div class="no_image"></div>');
                        $(hidenInputId, context).wrap('<div class="wrap_user_profile_but">Choose File</div>');


                    } else {
                        //console.log(settings);

                        $(wripperId + ' .no_image', context).remove();


                    }
                });

                //for (var key in settings.extraData) {
                //console.log(key);
                //console.log(settings.extraData['_triggering_element_name']);
                //var wriper = settings.extraData['_triggering_element_name'];


                //if ( settings.wriper == "ajax/test.html" ) {
                //+
                //xhr.responseText );
                //}
                //}


            });





        }
    };
})(jQuery);

