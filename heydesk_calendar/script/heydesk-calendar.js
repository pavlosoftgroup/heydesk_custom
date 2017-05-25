(function ($) {
    Drupal.ajax.prototype.commands.active_day_count = function (ajax, response, status) {
        var direction = response.direction;
        var date = response.date;
        console.log(direction);
        var startMonth = $('#cal-from .mini_calendar').attr('data-date-start');
        if (direction == 'next' && date == 'date_from') {
            $('#cal-to .prev-month').addClass('hidden');


        } else {


            $('#mini_date_to-' + localStorage.getItem('month') + '  .day-' + localStorage.getItem('day')).addClass('td_brown');
            if (startMonth == localStorage.getItem('month')) {
                $('#cal-to .prev-month').addClass('hidden');
            }
        }


    };
    Drupal.ajax.prototype.commands.rentday_count = function (ajax, response, status) {
        var month = response.month;
        var direction = response.direction;


        var quantity = Drupal.settings.heydesk_calendar.greenDay;
        // var start = response.start;
        // var startMonth = response.month;
        var daysInMonth = 32 - new Date(2017, month, 32).getDate();
        if (localStorage.getItem('month' == month) && direction == 'next') {
            var start_date = $('#cal-to .td_brown-start').attr('class');
            var start_num = start_date.substring(4, 6);
            var counts = 0;
        } else {
            start_num = 1;
            var counts = localStorage.getItem('cuontDay');

        }
        console.log(localStorage.getItem('month'));
        console.log(localStorage.getItem('day'));

        for (var i = Number(start_num); i < Number(daysInMonth); i++) {
            //     $('#cal-to td.day-' + i).removeClass('td_light-green');

            $('#cal-to td.day-' + i).addClass('td_browns');
        }

        console.log('#mini_date_to-' + localStorage.getItem('month') + '  .day-' + localStorage.getItem('day'));


        var cuontDay = $('.td_browns').length;
        if (direction == 'next') {
            var setCount = parseInt(counts) + parseInt(cuontDay);

        } else {
            var setCount = parseInt(counts) - parseInt(cuontDay);


        }

        localStorage.setItem('cuontDay', setCount);


    };

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.heydesk_calendar = {
        attach: function (context, settings) {

            // $('body', context).ready(function () {
            //
            //     $('.t_calendar').once(function () {

/////////////////////////////////////
            //      if ($(this).find('td').hasClass('status-1') ) {
            //         $(this).find('.spanch-bob').addClass('unavailable_span');
            //
            //      } else if($(this).find('td').hasClass('status-2')){
            //          $(this).find('.spanch-bob').addClass('unavailable_span');
            //      }
            //        else{
            //           $(this).find('.spanch-bob').removeClass('unavailable_span');
            //        }
            //     })
            //   });
            // Find all the secure links inside context that do not have our processed
            // class.
            ///////////////////////////////////////

            $('#cal-from', context).on('click', '.td_light-green', function () {
                var startMonth = 0;
                var colDay = 0;
                localStorage.setItem('cuontDay', 0);
                localStorage.setItem('day', 0);
                localStorage.setItem('month', 0);

                var date = $(this).children('.hiden').text();
                var first_class = $(this).attr('class');
                var day_number = first_class.substring(4, 6);
                $('#cal-from td').removeClass('td_brown');
                $('#cal-to td').removeClass('td_brown');
                //  $('#cal-to td').removeClass('td_browns');
                $(this).toggleClass('td_brown');
                $('#edit-date-from').val(date);
                // console.log(Number(day_number));
                $('.td_brown-start').removeClass('td_brown-start');
                $('#cal-to td.day-' + day_number).addClass('td_brown-start');
                $('.td_dark-green').addClass('td_light-green');
                $('.td_dark-green').removeClass('td_dark-green');
                $('#edit-date-from').css('background', '#DAC0A4');

                for (var i = Number(day_number)-1; i > 0; i--) {
                    $('#cal-to td.day-' + i).removeClass('td_light-green');
                    $('#cal-to td.day-' + i).addClass('td_dark-green');
                }
                var start_date = $('#cal-to .td_brown-start').attr('class');
                var startDay = start_date.substring(4, 6);
                startMonth = $('#cal-from .mini_calendar').attr('data-date-start');


                localStorage.setItem('day', startDay);
                localStorage.setItem('month', startMonth);
                $('#sum-price').text(0);
                $('#price-value').val('');
                $('#count_day').val(0);
                $('#renting-day').text(0);
                $('#edit-date-to').val('');


                // console.log(localStorage.getItem('month'));


            });
            ///////////////

            // $('#cal-to', context).on('click', '.next-month', function () {
            //     console.log(startMonth);
            //
            //
            //     var daysInMonth = 32 - new Date(2013, startMonth, 32).getDate();
            //     var start_date = $('#cal-to .td_brown-start').attr('class');
            //     var start_num = start_date.substring(4, 6);
            //     console.log(daysInMonth);
            //
            //
            // });
            $('#cal-to', context).on('click', '.td_light-green', function () {
                endtMonth = $('#cal-from .mini_calendar').attr('data-date-start');


                $(this).removeClass('td_dark-green');

                var start_date = $('#cal-to .td_brown-start').attr('class');
                if (start_date) {
                    var start_num = start_date.substring(4, 6);

                } else {
                    var start_num = 1;


                }

                var finish_class = $(this).attr('class');
                var day_number = finish_class.substring(4, 6);
                $('.td_browns').removeClass('td_browns');
                //  console.log(day_number);

                for (var i = Number(start_num); i < Number(day_number); i++) {
                    //     $('#cal-to td.day-' + i).removeClass('td_light-green');

                    $('#cal-to td.day-' + i).addClass('td_browns');
                }

                var date = $(this).children('.hiden').text();
                $('#cal-to td').removeClass('td_brown');
                $(this).toggleClass('td_brown');
                $('#edit-date-to').val(date);
                var coll_day = $('.td_browns').length;

                if (localStorage.getItem('month') == endtMonth) {
                    coll_day = parseInt(coll_day) + 1;


                } else {
                    // coll_day = coll_day + 1;
                    coll_day = parseInt(coll_day) + parseInt(localStorage.getItem('cuontDay'));


                }

                if ($('#edit-persons').length > 0) {
                    var human = $(this).val();

                } else {
                    var human = 1;
                }
                //localStorage.setItem('cuontDay', 0);

                var price = Number(Drupal.settings.price) * parseInt(coll_day);
                $('#sum-price').text(price);
                $('#price-value').val(price);
                $('#price-one').val(price);
                $('#renting-day').text(coll_day);
                $('#count_day').val(coll_day);
                $('#edit-date-to').css('background', '#DAC0A4');

            });

            $('#edit-persons', context).on('input', function () {
                if ($('#edit-persons').length > 0) {
                    var human = $(this).val();

                } else {
                    var human = 1;
                }

                var price_one = $('#price-one').val();

                console.log(price_one);

                var price_val = price_one * human;
                $('#sum-price').text(price_val);

                $('#price-value').val(price_val);

            });
            var active_mounts_num = Drupal.settings.mounts_num;

            ////////
            // $('#heydesk-order-form', context).once('mybehavior', function () {
            // Code here will only be applied to $('#some_element')
            // a single time.
            // $('#heydesk-calendar-list',context).find('.page-user-manage-listing-calendar').once('myCustomBehavior', FINCTION()).each(


            //  event on click to show and hide calendar;  page 10
            $('#edit-date-from, #edit-date-to').on('keypress keyup paste', function (event) {
                event.preventDefault();
                event.stopPropagation();
            })
                .prop('autocomplete', 'off')
                .blur(function () {
                    setTimeout(function () {
                        if ($('#edit-date-from').val().length && $('#edit-date-to').val().length) {
                            $('#heydesk-order-form .right_col .button').removeClass('disabled');
                        } else {
                            $('#heydesk-order-form .right_col .button').addClass('disabled');
                        }
                    }, 200);
                });

            $('.form-item-date-from', context).on('click', function (e) {
                e.stopPropagation();
                $(this).children('#edit-date-from').val('').css('border-color', 'black');
                $(this).parents('.select_date').siblings('#cal-from').fadeIn();
                $('#cal-to').fadeOut(250);
            });

            $('body').on('click', function () {
                $('#cal-from').fadeOut(250);
            });
            ////////////

            $('.form-item-date-to', context).on('click', function (e) {
                e.stopPropagation();
                if ($('#edit-date-from').val().length) {
                    $(this).children('#edit-date-to').val('');
                    $(this).parents('.select_date').siblings('#cal-to').fadeIn();
                    $('#edit-date-from').css('border-color', 'black')
                } else {
                    $('#edit-date-from').css('border-color', 'red')
                }
                $('#cal-from').fadeOut(250);
            });

            $('body').on('click', function () {
                $('#cal-to').fadeOut(250);
            });

            $('#heydesk-order-form .right_col .button input').click(function (event) {
                if ($(this).closest('.button').hasClass('disabled')) {
                    event.preventDefault();
                    event.stopPropagation();
                }
            });
//////////////////////////////////////////
// click on block and toggleClass status-0 / status-2; //////////////////////////////
//
            $('.table_dead', context).on('click', function () {

                if ($(this).parents('.poss').hasClass('status-0')) {

                    $(this).parents('.poss').toggleClass('status-0 status-2');
                    $(this).closest('label').siblings('input[value = "0"]').val('2');
                } else if ($(this).parents('.poss').hasClass('status-1')) {

                    $(this).closest('label').siblings('input[value = "1"]').val('2');
                    $(this).parents('.poss').toggleClass('status-1 status-2');
                } else {
                    $(this).parents('.poss').toggleClass('status-2 status-0');
                    $(this).closest('label').siblings('input').val('0');
                }
            });

///////////////////////////////////
// function for show block and  choose time on  click in table;  ////////////

            //  show hidden block on click by item;   //

            $('.spanch-bob', context).on('click', function (e) {

                e.stopPropagation();
                $(this).parents('.form-item').next('.hidden').removeClass('hidden');
                $(this).parents('.form-item').next('.frame_time').show(200);

            });

            $(document).mouseup(function (e) {

                var block = $(this).find('.frame_time');
                if (!block.is(e.target)
                    && block.has(e.target).length === 0) {
                    $(".frame_time").hide(250);
                }
            });

            $('.frame_div--inner').change(function () {

                $(this).parents('.poss').toggleClass('status-0 status-2', false).addClass('status-1');
                $(this).parents('.poss').find('.form-text').val('1');
            });

//////////////////////  select all rows in table;
            $('.select-week').on('click', function () {

                if ($(this).siblings().hasClass('status-1')) {
                    $(this).siblings().removeClass('status-1 status-0');
                    $(this).siblings().addClass('status-2');
                    $(this).siblings().find('input:text').val('2');
                    $(this).children('.circle').addClass('active');

                } else if ($(this).siblings().hasClass('status-0')) {
                    $(this).children('.circle').addClass('active');
                    $(this).siblings().removeClass('status-0 status-1');
                    $(this).siblings().addClass('status-2');
                    $(this).siblings().find('input:text').val('2');

                }
                else {
                    $(this).siblings().removeClass('status-2 status-1');
                    $(this).siblings().addClass('status-0');
                    $(this).siblings().find('input:text').val('0');
                    $(this).children('.circle').removeClass('active');
                }

            });

            /////////////////////////////////////////////////////
            $('.page-user-manage-listing-calendar').find('.wrap_week').on('click', function () {
                $(this).children('.circle').toggleClass('active');
            });

            ////////////////////////////////////////////////////////////  add class to column;
            $('.wrap_week').on('click', function () {

                if ($(this).children('.circle').hasClass("active")) {

                    var th_num = $(this).index();
                    $('.t_calendar tr').each(function () {
                        $(this).children('td').each(function (td_num) {
                            if (td_num == th_num) {
                                $(this).addClass('status-2');
                                $(this).removeClass('status-0 status-1');
                                $(this).find('input:text').val('2');
                            }
                        })
                    })

                }
                else {
                    var th_num = $(this).index();
                    $('.t_calendar tr').each(function () {
                        $(this).children('td').each(function (td_num) {
                            if (td_num == th_num) {
                                $(this).addClass('status-0');
                                $(this).removeClass('status-2 status-1');
                                $(this).find('.spanch-bob').removeClass('unavailable_span');
                                $(this).find('.spanch-bob').removeClass('partially_available_span');
                                $(this).find('input:text').val('0');
                            }
                        })
                    })
                }


            });


            //     })

        }
    };
}(jQuery));
