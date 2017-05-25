(function ($) {

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.heydesk_favorite = {
        attach: function (context, settings) {
            $('body', context).ready(function () {
                $('.favorite-node-item').children('.info').removeClass('col-lg-3');
                $('.favorite-node-item').children('.info').addClass('col-lg-4');
            });
        }
    };
}(jQuery));
