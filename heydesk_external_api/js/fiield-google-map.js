(function ($) {

// Store our function as a property of Drupal.behaviors.
    Drupal.behaviors.heydesk_external_api = {
        attach: function (context, settings) {


            // $('.fbshare', context).onclick = function() {
            //     FB.ui({
            //         method: 'share',
            //         display: 'popup',
            //         href: 'https://developers.facebook.com/docs/',
            //     }, function(response){});
            // }

            var placeAllItem = Drupal.settings.heydesk_external_api.proposalMapArray;
            var googleApiKey = Drupal.settings.heydesk_external_api.apiKey;
            $.getScript('https://maps.googleapis.com/maps/api/js?key=' + googleApiKey + '&callback=initMap', function (data, textStatus, jqxhr) {
                if($('[id^=proposal-map]').length){
                    $.each(placeAllItem, function (index, value) {
                        var arr = Object.values(value);
                        var addressNode = arr[0][0];
                        var idBlockMap = arr[0][1];


                        function initialize(address) {
                            var geocoder = new google.maps.Geocoder();
                            geocoder.geocode({'address': address}, function (results, status) {
                                if (status == google.maps.GeocoderStatus.OK) {
                                    getPosition(results[0].geometry.location.lat(), results[0].geometry.location.lng());
                                } else {
                                    getPosition(0, 0);
                                }
                            });
                        }

                        function getPosition(lat, lng) {


                            var myLatLng = {lat: lat, lng: lng};
                            var mapCanvas = document.getElementById(idBlockMap, context);
                            var mapOptions = {
                                center: myLatLng,
                                zoom: 16,
                                mapTypeId: google.maps.MapTypeId.ROADMAP
                            }
                            var marker = new google.maps.Marker({
                                position: myLatLng,
                                map: map
                            });
                            var map = new google.maps.Map(mapCanvas, mapOptions);
                            marker.setMap(map);
                        }
                        google.maps.event.addDomListener(window, 'load', initialize(addressNode));
                    });
                }
            });


        }
    };
}(jQuery));
