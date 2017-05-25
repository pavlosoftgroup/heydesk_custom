(function ($) {

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.heydesk_user = {
        attach: function (context, settings) {
            var save = Drupal.settings.save_prise;

            $("#demo", context).freshslider({
                range: false, // true or false
               //  step: 1,
                text: true,
               //  min: 1,

               unit: 0, // the unit which slider is considering
                enabled: true, // true or false
                value: save, // a number if unranged , or 2 elements array contains low and high value if ranged
                onchange: function (low, high) {


                    var showValue = $('.fscaret').text();
                    $('#edit-prices-choose').val(showValue);

                  //   $('.page-user-manage-listing-prices').find('#hour').children('.values').text(showValue / 8);
                    $('.page-user-manage-listing-prices').find('#day').children('.values').text(showValue);
                    $('.page-user-manage-listing-prices').find('#day-3').children('.values').text(showValue * 3);
                    $('.page-user-manage-listing-prices').find('#week').children('.values').text(showValue * 7);
                    $('.page-user-manage-listing-prices').find('#week-2').children('.values').text(showValue * 14);
                    $('.page-user-manage-listing-prices').find('#week-4').children('.values').text(showValue * 28);


                     //  $('#edit-prices-choose').on('input', function showConsole(){
                     //     var showValue = $('.fscaret').text();
                     //     if ($(this).val() == 0) {
                     //        $(this).val() == 1;
                     //        showValue == $(this);
                     //     } else {
                     //        return;
                     //     }
                     //   });
                } // callback function when slider caret's changed, onchange(low, high) for ranged, and onchange(value) for unranged


            });
        }
    };
}(jQuery));
