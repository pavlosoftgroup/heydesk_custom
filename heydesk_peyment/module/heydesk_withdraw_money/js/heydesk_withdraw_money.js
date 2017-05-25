(function ($) {
    Drupal.behaviors.heydesk_withdraw_money = {
        attach: function (context, settings) {
            $('.card-field').on('input', function () {

                var string = $(this).val().split(" ").join("");
                if (string.length > 0) {
                    string = string.match(new RegExp('.{1,4}', 'g')).join(" ");
                }
                $(this).val(string);

            });
            $('.card-field').on('keypress', function (e) {

                e = e || event;
                if (e.ctrlKey || e.altKey || e.metaKey) return;
                var chr = getChar(e);
                if (chr == null) return;
                if (chr < '0' || chr > '9') {
                    return false;
                }

            });
            $('#edit-amount').on('keypress', function (e) {

                e = e || event;
                if (e.ctrlKey || e.altKey || e.metaKey) return;
                var chr = getChar(e);
                if (chr == null) return;
                if (chr < '0' || chr > '9') {
                    return false;
                }

            });

            function getChar(event) {
                if (event.which == null) {
                    if (event.keyCode < 32) return null;
                    return String.fromCharCode(event.keyCode)
                }

                if (event.which != 0 && event.charCode != 0) {
                    if (event.which < 32) return null;
                    return String.fromCharCode(event.which)
                }
                return null;
            }


        }
    };
})(jQuery);
