Drupal.theme.prototype.small_popup_theme= function () {
    var html = '';
    html += '<div id="ctools-modal" class="popups-box my-popup">';
    html += ' <div class="ctools-modal-content my-popup ">';
    html += ' <span class="popups-close"><a class="close" href="#"></a></span>';
    html += ' <div class="modal-msg"></div>';
    html += ' <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
    html += ' </div>';
    html += '</div>';
    return html;
};
