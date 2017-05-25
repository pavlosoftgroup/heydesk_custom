//define(['./loadMap.js'], function(Map) {
//    var Mark = {
//        map_obj: '',
//
//        maps: function(response) {
//            console.log(JSON.parse(response).results[0].geometry.viewport.northeast.lat);
//            map_obj = Map.init();
//            Map.addMarker(map_obj, 49.55035319999999, 25.6225821);
//        },
//
//        ajax: function () {
//
//            var xmlhttp;
//
//            xmlhttp = new XMLHttpRequest();
//
//            xmlhttp.onreadystatechange = function () {
//                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
//                    Mark.maps(xmlhttp.responseText);
//                }
//            }
//
//            xmlhttp.open("POST", "https://maps.googleapis.com/maps/api/geocode/json?address=%D0%91%D0%B0%D0%BD%D0%B4%D0%B5%D1%80%D0%B8+64,+Ternopil,+Ukraine&key=AIzaSyDMgnsp7HMAHLR_ntjubgpnt3A8evQvsgg", true);
//            xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
//            xmlhttp.send();
//        },
//    };
//
//    return Mark.ajax();
//});
////https://maps.googleapis.com/maps/api/geocode/json?address=%D0%91%D0%B0%D0%BD%D0%B4%D0%B5%D1%80%D0%B8+64,+Ternopil,+Ukraine&key=AIzaSyDMgnsp7HMAHLR_ntjubgpnt3A8evQvsgg