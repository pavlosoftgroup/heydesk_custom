(function ($) {
    /**
     * Command to dismiss the modal.
     */
    Drupal.ajax.prototype.commands.example_modal_dismiss = function (ajax, response, status) {
        setTimeout(function () {
            Drupal.CTools.Modal.dismiss();
            $('link.ctools-temporary-css').remove();
        }, response.delay);
    }

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.heydesk_custom_function = {
        attach: function (context, settings) {

            $('#modal', context).once(function () {
                $('.linked-in').wrap("<div class='wrap_linkedin_submit'></div>");
                $('#modal').find('.or').wrap("<div class='wrap_line'></div>");
                $('#modal').find('#edit-reg-submit').wrap("<div class='wrap_modal button'><a></a></div>");
                $('#modal').find('#edit-login-submit').wrap("<div class='wrap_modal button'><a></a></div>");
            });

            $('.front', context).once(function () {
                $('#search-block-form').find('#edit-submit').wrap('<div class="first_page_search_button"><span></span></div>');
            });

            $('#heydesk-user-users-profile-form', context).once(function () {
                $('.page-user-profile').find('.button-submit').wrap("<div class='wrap_profile_button button'><a></a></div>");
            });

            $('#heydesk-proposal-prices-form', context).once(function () {
                $('#heydesk-proposal-prices-form').find('#edit-prices-submit').wrap("<div class='wrap_profile_button button'><a></a></div>");
            });

            $('#heydesk-proposal-setting-form', context).once(function () {
                $('#heydesk-proposal-setting-form').find('#edit-setting').find('#edit-submit').wrap("<div class='wrap_settings button'><a></a></div>");
                $('#heydesk-proposal-setting-form').find('#edit-yes').wrap("<div class='wrap_listing_button'></div>");
                $('#heydesk-proposal-setting-form').find('#edit-no').wrap("<div class='wrap_listing_button'></div>");
            });

            $('#heydesk-calendar-list', context).once(function () {
                $('#heydesk-calendar-list').find('#edit-calendar-submit').wrap('<div class="wrap_calendar_button button"><a></a></div>');
                $('#heydesk-calendar-list').find('.wrap_week').prepend('<span class="circle"></span>');
                $('#heydesk-calendar-list').find('.select-week').append('<span class="circle"></span>');
            });

            $('#heydesk-user-setting-profile-form').find('#edit-submit').wrap("<div class='wrap_edit_button button'><a></a></div>");

            $('[id^=views-exposed-form-sity]', context).once(function () {
                var $amenities = $('.views-widget-filter-field_minimum_rental_period_value, .views-widget-filter-date_filter, .views-widget-sort-by, .views-widget-sort-order');
                $amenities.wrapAll('<div class="wrap_main_amenities_select"></div>');
                $('.views-submit-button').find('#edit-submit-sity').wrap('<span class="area_search_button--main"></span>');
                //  var filters = $('#edit-field-wi-fi-value-wrapper, #edit-field-furniture-value-wrapper, #edit-field-kitchen-value-wrapper, #edit-field-conference-room-value-wrapper, #edit-field-parking-value-wrapper, #edit-field-cubicles-value-wrapper, #edit-field-dog-friendly-value-wrapper');
                //  filters.wrapAll('<div class="wrap_main_filter_search"></div>');
            });
//////////////////////////
            $('.log-in-list-now').attr('href', '#');
            // remove event when push enter;
           $('.page-proposal-order').on('keyup keypress', 'form input[type="text"]', function(e){
               var keyCode = e.keyCode || e.which;
               if (keyCode === 13) {
                e.preventDefault();
                return false;
                }
           });
            ///////////check input type form and  wrap div;
               $('.third-form, #edit-id-validator', context).once(function () {
                  if ($("input:file").is(".form-file")) {
                     $("input:file").wrap('<div class="wrap_user_profile_but">Choose file</div>');
                     $('.inline-block label').append('<div class="no_image"></div>');
                  };
                  var findPicOnStep = $('#edit-profile-ajax-wrapper img');
                  var findPicOnValidate = $('#edit-id-validator img');
                  if (findPicOnStep.length > 0) {
                     $('#edit-profile-ajax-wrapper').find('.no_image').remove();
                  };
                  if (findPicOnValidate.length > 0) {
                     $('#edit-id-validator #edit-id-validator-photo-profile-ajax-wrapper').find('.no_image').remove();
                  }
               });
               $('.profile_pic', context).once(function () {
                  if ($("input:file").is(".form-file")) {
                     $("input:file").wrap('<div class="wrap_user_profile_but">Choose file</div>');
                     $('#edit-picture-ajax-wrapper label').append('<div class="no_image"></div>');
                  }
               });


            $('#edit-persons', context).change(function () {
                var checkStatusButton = $('.proposal_right-side .right_col .button');
                var editDateTo = $('#edit-date-to');

                if ($(this).val() >= 1 && editDateTo.val().length >= 1) {
                    checkStatusButton.removeClass('disabled');
                }
                else if ($(this).val() <= 0) {
                    checkStatusButton.addClass('disabled');

                } else {
                    return;
                }
            });
            //show and hide map by hover;
            $('.photos', context).hover(
                function () {
                    $(this).children('[id|=photos-content]', context).css('display', 'none');

                },
                function () {
                    $(this).children('[id|=photos-content]', context).css('display', 'block');

                });

//////////////////////////////// location Type SElect;

            $('select[id^=edit-field-location-type-value]').once(function () {
                console.log(1);
                var locationType = $(this);
                var numberOfOptions = $(this).children('option').length;

                $(this).addClass('select-hidden');
                $(this).wrap('<div class="select"></div>');
                $(this).after('<div class="select-styled"></div>');


                var styledSelect = $(this).next('div.select-styled');
                styledSelect.text($(this).children('option').eq(0).text());

                var list = $('<ul />', {
                    'class': 'select-options'
                }).insertAfter(styledSelect);

                for (var i = 0; i < numberOfOptions; i++) {
                    $('<li />', {
                        text: $(this).children('option').eq(i).text(),
                        rel: $(this).children('option').eq(i).val()
                    }).appendTo(list);
                }

                var listItems = list.children('li');

                styledSelect.click(function (e) {
                    e.stopPropagation();
                    $('div.select-styled.active').not(this).each(function () {
                        $(this).removeClass('active').next('ul.select-options').hide();
                    });
                    $(this).toggleClass('active').next('ul.select-options').toggle();
                });

                listItems.click(function (e) {
                    e.stopPropagation();
                    styledSelect.text($(this).text()).removeClass('active');
                    $(this).val($(this).attr('rel'));
                    list.hide();
                    $(this).parent('.select-options').siblings('.select-styled').css('background', '#DAC0A4');
                });

                $(document).click(function () {
                    styledSelect.removeClass('active');
                    list.hide();
                });

            });
/////////////////////////////////////  deskType Select;

            $('select[id^=edit-field-desk-type-value]').once(function () {

                var deskType = $(this);
                var numberOfOptions = $(this).children('option').length;

                $(this).addClass('select-hidden');
                $(this).wrap('<div class="select"></div>');
                $(this).after('<div class="select-styled"></div>');

                var styledSelect = $(this).next('div.select-styled');
                styledSelect.text($(this).children('option').eq(0).text());

                var list = $('<ul />', {
                    'class': 'select-options'
                }).insertAfter(styledSelect);

                for (var i = 0; i < numberOfOptions; i++) {
                    $('<li />', {
                        text: $(this).children('option').eq(i).text(),
                        rel: $(this).children('option').eq(i).val()
                    }).appendTo(list);
                }

                var listItems = list.children('li');

                styledSelect.click(function (e) {
                    e.stopPropagation();
                    $('div.select-styled.active').not(this).each(function () {
                        $(this).removeClass('active').next('ul.select-options').hide();
                    });
                    $(this).toggleClass('active').next('ul.select-options').toggle();
                });

                listItems.click(function (e) {
                    e.stopPropagation();
                    styledSelect.text($(this).text()).removeClass('active');
                    $(this).val($(this).attr('rel'));
                    list.hide();
                    $(this).parent('.select-options').siblings('.select-styled').css('background', '#DAC0A4');
                });

                $(document).click(function () {
                    styledSelect.removeClass('active');
                    list.hide();
                });
            });
///////////////////////
            $('select[id^=edit-from]').once(function () {

                var editTimeFrom = $(this);
                var numberOfOptions = $(this).children('option').length;

                $(this).addClass('select-hidden');
                $(this).wrap('<div class="select"></div>');
                $(this).after('<div class="select-styled"></div>');

                var styledSelect = $(this).next('div.select-styled');
                styledSelect.text($(this).children('option').eq(0).text());

                var list = $('<ul />', {
                    'class': 'select-options'
                }).insertAfter(styledSelect);

                for (var i = 0; i < numberOfOptions; i++) {
                    $('<li />', {
                        text: $(this).children('option').eq(i).text(),
                        rel: $(this).children('option').eq(i).val()
                    }).appendTo(list);
                }

                var listItems = list.children('li');

                styledSelect.click(function (e) {
                    e.stopPropagation();
                    $('div.select-styled.active').not(this).each(function () {
                        $(this).removeClass('active').next('ul.select-options').hide();
                    });
                    $(this).toggleClass('active').next('ul.select-options').toggle();
                });

                listItems.click(function (e) {
                    e.stopPropagation();
                    styledSelect.text($(this).text()).removeClass('active');
                    $(this).val($(this).attr('rel'));
                    list.hide();
                    $(this).parent('.select-options').siblings('.select-styled').css('background', '#DAC0A4');
                    var getValue = styledSelect.text();
                    var inputValue = $('#edit-from-val').val(getValue);
                });

                $(document).click(function () {
                    styledSelect.removeClass('active');
                    list.hide();
                });

            });

////////////////////
            $('select[id^=edit-to]').once(function () {

                var editTimeTo = $(this);
                var numberOfOptions = $(this).children('option').length;

                $(this).addClass('select-hidden');
                $(this).wrap('<div class="select"></div>');
                $(this).after('<div class="select-styled"></div>');

                var styledSelect = $(this).next('div.select-styled');
                styledSelect.text($(this).children('option').eq(0).text());

                var list = $('<ul />', {
                    'class': 'select-options'
                }).insertAfter(styledSelect);

                for (var i = 0; i < numberOfOptions; i++) {
                    $('<li />', {
                        text: $(this).children('option').eq(i).text(),
                        rel: $(this).children('option').eq(i).val()
                    }).appendTo(list);
                }

                var listItems = list.children('li');

                styledSelect.click(function (e) {
                    e.stopPropagation();
                    $('div.select-styled.active').not(this).each(function () {
                        $(this).removeClass('active').next('ul.select-options').hide();
                    });
                    $(this).toggleClass('active').next('ul.select-options').toggle();
                });

                listItems.click(function (e) {
                    e.stopPropagation();
                    styledSelect.text($(this).text()).removeClass('active');
                    $(this).val($(this).attr('rel'));
                    list.hide();
                    $(this).parent('.select-options').siblings('.select-styled').css('background', '#DAC0A4');
                    var getValue = styledSelect.text();
                    var inputValue = $('#edit-to-val').val(getValue);
                });

                $(document).click(function () {
                    styledSelect.removeClass('active');
                    list.hide();
                });

            });
////////////////////////

/////////////////// customize select in main search panel;
            $('select[id^=edit-date-filter]').once(function () {

                var editDateFilter = $(this);
                var numberOfOptions = $(this).children('option').length;

                $(this).addClass('select-hidden');
                $(this).wrap('<div class="select"></div>');
                $(this).after('<div class="select-styled"></div>');

                var styledSelect = $(this).next('div.select-styled');
                styledSelect.text($(this).children('option').eq(0).text());

                var list = $('<ul />', {
                    'class': 'select-options'
                }).insertAfter(styledSelect);

                for (var i = 0; i < numberOfOptions; i++) {
                    $('<li />', {
                        text: $(this).children('option').eq(i).text(),
                        rel: $(this).children('option').eq(i).val()
                    }).appendTo(list);
                }

                var listItems = list.children('li');

                styledSelect.click(function (e) {
                    e.stopPropagation();
                    $('div.select-styled.active').not(this).each(function () {
                        $(this).removeClass('active').next('ul.select-options').hide();
                    });
                    $(this).toggleClass('active').next('ul.select-options').toggle();
                });

                listItems.click(function (e) {
                    e.stopPropagation();
                    styledSelect.text($(this).text()).removeClass('active');
                    $(this).val($(this).attr('rel'));
                    list.hide();
                    $(this).parent('.select-options').siblings('.select-styled').css('background', '#DAC0A4');
                });

                $(document).click(function () {
                    styledSelect.removeClass('active');
                    list.hide();
                });

            });
//////////////////////
            $('select[id^=edit-field-minimum-rental-period-value]').once(function () {

                var editRentalPeriod = $(this);
                var numberOfOptions = $(this).children('option').length;

                $(this).addClass('select-hidden');
                $(this).wrap('<div class="select"></div>');
                $(this).after('<div class="select-styled"></div>');

                var styledSelect = $(this).next('div.select-styled');
                styledSelect.text($(this).children('option').eq(0).text());

                var list = $('<ul />', {
                    'class': 'select-options'
                }).insertAfter(styledSelect);

                for (var i = 0; i < numberOfOptions; i++) {
                    $('<li />', {
                        text: $(this).children('option').eq(i).text(),
                        rel: $(this).children('option').eq(i).val()
                    }).appendTo(list);
                }

                var listItems = list.children('li');

                styledSelect.click(function (e) {
                    e.stopPropagation();
                    $('div.select-styled.active').not(this).each(function () {
                        $(this).removeClass('active').next('ul.select-options').hide();
                    });
                    $(this).toggleClass('active').next('ul.select-options').toggle();
                });

                listItems.click(function (e) {
                    e.stopPropagation();
                    styledSelect.text($(this).text()).removeClass('active');
                    $(this).val($(this).attr('rel'));
                    list.hide();
                    $(this).parent('.select-options').siblings('.select-styled').css('background', '#DAC0A4');
                });

                $(document).click(function () {
                    styledSelect.removeClass('active');
                    list.hide();
                });

            });
///////////////////////
            $('select[id^=edit-sort-by]').once(function () {

                var editSortBy = $(this);
                var numberOfOptions = $(this).children('option').length;

                $(this).addClass('select-hidden');
                $(this).wrap('<div class="select"></div>');
                $(this).after('<div class="select-styled"></div>');

                var styledSelect = $(this).next('div.select-styled');
                styledSelect.text($(this).children('option').eq(0).text());

                var list = $('<ul />', {
                    'class': 'select-options'
                }).insertAfter(styledSelect);

                for (var i = 0; i < numberOfOptions; i++) {
                    $('<li />', {
                        text: $(this).children('option').eq(i).text(),
                        rel: $(this).children('option').eq(i).val()
                    }).appendTo(list);
                }

                var listItems = list.children('li');

                styledSelect.click(function (e) {
                    e.stopPropagation();
                    $('div.select-styled.active').not(this).each(function () {
                        $(this).removeClass('active').next('ul.select-options').hide();
                    });
                    $(this).toggleClass('active').next('ul.select-options').toggle();
                });

                listItems.click(function (e) {
                    e.stopPropagation();
                    styledSelect.text($(this).text()).removeClass('active');
                    $(this).val($(this).attr('rel'));
                    list.hide();
                    $(this).parent('.select-options').siblings('.select-styled').css('background', '#DAC0A4');
                });

                $(document).click(function () {
                    styledSelect.removeClass('active');
                    list.hide();
                });

            });


        }
    };
}(jQuery));
(function ($) {
    Drupal.behaviors.AlingnPopup = {
        attach: function () {
            popup = $('#modalContent');
            // ������� ������������ �������� � �������� ������.
            function alignCenter() {
                // ������ ������������ ����.
                var wpopup = popup.width();
                var hpopup = popup.height();

                // ������ ����.
                var hwindow = $(window).height();
                var wwindow = $(window).width();
                var Left = Math.max(40, parseInt($(window).width() / 2 - wpopup / 2));
                var Top = Math.max(40, parseInt($(window).height() / 2 - hpopup / 2));

                if (hwindow < hpopup) {
                    popup.css({'position': 'absolute'});
                }
                else {
                    popup.css({'position': 'fixed'});
                }
                popup.css({'left': Left, 'top': Top});
            };

            alignCenter();

            $(window).resize(function () {
                alignCenter();
            });


            popup.resize(function () {
                alignCenter();
            });
        }
    }
}(jQuery));
