(function ($) {

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.heydesk_payment_qiuckpay = {
        attach: function (context, settings) {

            

            QuickPay.Embedded.Form($('#heydesk-proposal-order-form', context), {
                merchant_id: 31215,
                agreement_id: 121403,
                brandChanged: function(brand) {
                    $('.card-brand').html(brand);
                },
                beforeCreateToken: function(form) {
                    $('input.error').removeClass('error');
                    $('#heydesk-proposal-order-form button').html('Please wait...');
                },
                failure: function(form, source, message) {
                    if (source === 'validation') {
                        for (var i = 0; i < message.length; i++) {
                            $('input[data-quickpay=' + message[i] + ']').addClass('error');
                        }
                    } else {
                        alert(source + ': ' + message);
                    }
                    $('#heydesk-proposal-order-form button').html('Pay');
                }
            });

        }
    }

})(jQuery);