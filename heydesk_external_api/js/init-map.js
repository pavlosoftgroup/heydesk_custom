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
            var placeToShow = Drupal.settings.heydesk_external_api.placeToShow;
            //console.log('Alert');

            function initialize(address) {
                var geocoder =  new google.maps.Geocoder();
                geocoder.geocode( { 'address': address}, function(results, status) {
                    if (status == google.maps.GeocoderStatus.OK) {
                        getPosition(results[0].geometry.location.lat(), results[0].geometry.location.lng());
                    } else {
                        getPosition(0, 0);
                    }
                });
            }

            function getPosition(lat, lng) {
                var  id_block_map = Drupal.settings.heydesk_external_api.idBlockMmap;
                //console.log(id_block_map);


                var myLatLng = {lat: lat, lng: lng};
                var mapCanvas = document.getElementById(id_block_map);
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

//додаємо карту до нашого блоку в темплейті
            google.maps.event.addDomListener(window, 'load', initialize(placeToShow));


        }
    };
}(jQuery));
