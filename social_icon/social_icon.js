Drupal.behaviors.socialIcon = function(context, settings){
    if (!settings) settings = Drupal.settings.socialIcon;
    $('img.social_icon', context).hover(
        function() {
            var hover_icon_src = $(this).data('hover-icon');
            if(hover_icon_src) {
                $(this).attr('src', hover_icon_src);
            }
        },function() {
            $(this).unbind();
        }
    );
};