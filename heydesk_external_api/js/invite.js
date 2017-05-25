(function ($) {

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.heydesk_external = {
        attach: function (context, settings) {
            $('#facebook-invite').click(function(){
                FB.init({
                    appId      : '277096552704598',
                    xfbml      : true,
                    cookie:true,
                    status:true,
                    version    : 'v2.8'
                });

                FB.ui({
                    method: 'apprequests',
                    message: 'Invite your friends'
                });

            });
            //function FacebookInviteFriends()
            //{
            //    FB.ui({
            //        method: 'apprequests',
            //        message: 'Invite your friends'
            //    });
            //};

        }
    };
}(jQuery));