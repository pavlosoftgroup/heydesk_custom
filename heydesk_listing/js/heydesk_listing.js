(function ($) {
    Drupal.behaviors.heydesk_listing = {
        attach: function (context, settings) {
            function atoprint(aId) {
                var atext = document.getElementById(aId).innerHTML;
                var captext = window.document.title;
                var alink = window.document.location;
                var prwin = open('');
                prwin.document.open();
                prwin.document.writeln('<html><head><title>������ ��� ������<\/title><\/head><body text="#000000" bgcolor="#FFFFFF"><div onselectstart="return false;" oncopy="return false;">');
                prwin.document.writeln('<div style="margin-bottom:5px;"><a href="javascript://" onclick="window.print();">������<\/a> � <a href="javascript://" onclick="window.close();">������� ����<\/a><\/div><hr>');
                prwin.document.writeln('<h1>'+captext+'<\/h1>');
                prwin.document.writeln(atext);
                prwin.document.writeln('<hr><div style="font-size:8pt;margin-top:20px;">� ������ SzenProgs.ru<\/div>');
                prwin.document.writeln('<div style="font-size:8pt;">�������� ���������: '+alink+'<\/div>');
                prwin.document.writeln('<div style="margin-top:5px;"><a href="javascript://" onclick="window.print();">������<\/a> � <a href="javascript://" onclick="window.close();">������� ����<\/a><\/div>');
                prwin.document.writeln('<\/div><\/body><\/html>');
            }


        }
    };
})(jQuery);