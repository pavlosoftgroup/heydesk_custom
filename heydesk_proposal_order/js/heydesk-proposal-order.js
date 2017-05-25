(function ($) {


    Drupal.behaviors.heydesk_proposal_order = {
        attach: function (context, settings) {

         

            $(document).ajaxSuccess(function (event, request, settings) {
                //console.log(settings);
                var buttonSubmit = '';
                var hidenInputId = '';
                switch (settings.extraData['_triggering_element_name']) {
                    case "img_cart_front_upload_button":
                        buttonSubmit = 'edit-img-cart-front-ajax-wrapper';
                        break;
                    case  "img_cart_security_upload_button":
                        buttonSubmit = 'edit-img-cart-security-ajax-wrapper';
                        break;
                    case 'img_cart_back_upload_button':
                        buttonSubmit = 'edit-img-cart-back-ajax-wrapper';
                        break;
                    case 'profile_upload_button':
                        buttonSubmit = 'edit-profile-ajax-wrapper';
                        break;
                    case "img_cart_front_remove_button":
                        buttonSubmit = 'edit-img-cart-front-ajax-wrapper';
                        hidenInputId = '#edit-img-cart-front-upload';
                        break;
                    case  "img_cart_security_remove_button":
                        buttonSubmit = 'edit-img-cart-security-ajax-wrapper';
                        hidenInputId = '#edit-img-cart-security-upload';

                        break;
                    case 'img_cart_back_remove_button':
                        buttonSubmit = 'edit-img-cart-back-ajax-wrapper';
                        hidenInputId = '#edit-img-cart-back-upload';

                        break;
                    case 'profile_remove_button':
                        buttonSubmit = 'edit-profile-ajax-wrapper';
                        hidenInputId = '#edit-profile-upload'

                        break;

                }
                var wripper = '#' + buttonSubmit;
                //var buttonActSubmit = '#' + settings.extraData['_triggering_element_name'];
                $(wripper, context).once('ajax', function () {


                    if (settings.extraData['_triggering_element_value'] == 'Remove') {


                        $(".third-form " + wripper + " label", context).append('<div class="no_image"></div>');
                        $('.third-form ' + hidenInputId, context).wrap('<div class="wrap_user_profile_but">Choose File</div>');


                    } else {
                        $(wripper + ' .no_image', context).remove();


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



            $('.db_datepicker').datepicker({
                dateFormat: 'dd.mm.yy'
            }).datepicker('widget').wrap('<div class="ll-skin-melon "/>');

            $('.dd_datepicker').datepicker({
                dateFormat: 'dd.mm.yy'
            }).datepicker('widget').wrap('<div class="ll-skin-melon "/>');

            //$(document).ajaxSuccess(function() {
            //});

            //var val_price =  Drupal.settings.heydesk_proposal_order.val_price;

            //var addPrice = $('[id|=input]:checkbox', context);
            ////////////////
            // if ( $("input:checkbox").attr("class") == "left-checkbox" ) {
            //     var boxes = $(this);
            // }
            //
            // $("input:checkbox").on("change", function(){
            //     var theArray = new Array();
            //     for (var i=0;i<boxes.length;i++) {
            //         var box = boxes[i];
            //         if ($(box).prop('checked')) {
            //             theArray[theArray.length] = prices[i];
            //         }
            //     }
            //     showValues(theArray);
            // });
            //
            // var showValues = function(array) {
            //     var text = "";
            //     if(array.length == 0) text += "�� ���� ������� �� ������";
            //     for(var i = 0; i < array.length; i++) {
            //         var val_price = $('.price-form span').text();
            //         val_price = val_price + value;
            //     }
            //
            //     $('.price-form span').html(val_price);
            // };
            ////////////////////\
            // var arrKey = $(this,{
            //     var parent = $(this).parent([id|="edit-extras"]);
            //     var  arrayKey = $(parent[parent.length - 1]);
            //
            // })

            $('.form-wrapper label').on('click', function () {
                var prices = Drupal.settings.heydesk_proposal_order.prices;


                //  var val = arrayKey(this),
                //      priceLabel = prices[val],
                //      nullPrice = $('.price-form span').text();
                //  console.log(val);
                //  if ($(this~input).prop('checked')) {
                //      var summ = nullPrice + priceLabel;
                //      $('.price-form span').text(summ);
                //
                //  }
                //  else
                //  {
                //      var summ = nullPrice - priceLabel;
                //      $('.price-form span').text(summ);
                //
                //  }

                var parentId = $(this).parents('[id|="edit-extras"]');
                var myCheckbox = $(this).siblings('[id|="edit-extras"]');
                var idClick = parentId.attr('id');
                var lastSymbol = idClick.charAt(idClick.length - 1);
                var myPrice = prices[lastSymbol];

                var nullPrice = $('.price-form span').text();

                var summ = parseInt(nullPrice) + parseInt(myPrice);

                var minus = parseInt(nullPrice) - parseInt(myPrice);


                if (myCheckbox.prop("checked")) {
                    $('.price-form span').text(minus);
                } else {
                    $('.price-form span').text(summ);
                }


            });


        }
    };
})(jQuery);
