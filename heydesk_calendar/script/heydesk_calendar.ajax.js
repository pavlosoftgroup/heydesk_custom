(function ($) {

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.ajax_heydesk_calendar = {
        attach: function (context, settings) {
            // Drupal.ajax.prototype.commands.calehdar_generate = function (ajax, response, status) {
            //     // response.data is a value setted in 'data' key of command on PHP side.
            //     if (response.data) {
            //         var wrapper = response.wrapper;
            //         var calendar = response.calendar;
            //
            //
            //
            //         $(wrapper).replaceWith( calendar );
            //
            //     }
            // };
        }
    };
}(jQuery));
