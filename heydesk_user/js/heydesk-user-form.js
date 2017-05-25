(function ($) {
    Drupal.behaviors.heydesk_user_form = {
        attach: function (context, settings) {
            //
            // $('.db_datepicker', context).datepicker({
            //     dateFormat: 'dd.mm.yy'
            // });
            // $('.dd_datepicker', context).datepicker({
            //     dateFormat: 'dd.mm.yy'
            // });
            $('.id_number_datepicker', context).datepicker({
                dateFormat: 'dd.mm.yy'
            });
            $('.date_of_birth_datepicker', context).datepicker({
                dateFormat: 'dd.mm.yy'
            });


            $(document).ajaxSuccess(function (event, request, settings) {
                if (settings.extraData['_triggering_element_value'] == 'Remove') {

                    //console.log(context);
                    $("#heydesk-user-users-profile-form #edit-picture-ajax-wrapper label", context).append('<div class="no_image"></div>');
                    $('#heydesk-user-users-profile-form #edit-picture-upload', context).wrap('<div class="wrap_user_profile_but">Choose File</div>');

                } else {

                    $('#edit-picture-ajax-wrapper .no_image', context).remove();
                }

            });


        }
    };
})(jQuery);
