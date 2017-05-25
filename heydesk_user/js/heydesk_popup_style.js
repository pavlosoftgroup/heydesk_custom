Drupal.theme.prototype.heydesk_popup_custom_theme = function () {
    var html = '';
    html += '<div id="ctools-modal" class="popups-box my-first-popup">';
    html += ' <div class="ctools-modal-content my-popup ">';
    html += '      <div class="modal-header">';
    html += '        <a class="close" href="#">';
    html += '        </a>';
    html += '      </div>';
    html += ' <span class="popups-close"><a class="close" href="#"></a></span>';
    html += ' <div class="modal-msg"></div>';
    html += ' <div id="modal-content" class="modal-content popups-body"></div>';
    html += ' </div>';
    html += '</div>';
    return html;
}