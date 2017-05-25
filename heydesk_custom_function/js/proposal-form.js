(function ($) {
  Drupal.behaviors.heydeskProposalForm = {
    attach: function (context, settings) {
      var showAmenitiesSelect = $('.add-edit-amenities-buttons').find('span');
      var amenitiesSelectWrapper = $('#edit-field-amenities-all').find('.form-item-field-amenities-all-und');
      var amenitiesSelectedSave = amenitiesSelectWrapper.find('.button');
      var amenitiesSelectedItemWrapper = $('#edit-field-amenities-all-amenities-container-amenities-list');

      if (amenitiesSelectWrapper.find('input:checkbox:checked').length) {
        amenitiesSelectedItemWrapper.html('');
        amenitiesSelectWrapper.find('input:checkbox:checked').each(function (index, el) {
          $('<div>')
            .text($(el).val())
            .addClass('amenities-selected-item')
            .appendTo(amenitiesSelectedItemWrapper);
        });
        showAmenitiesSelect.parent().addClass('add-opened');
      } else {
        showAmenitiesSelect.parent().removeClass('add-opened');
      }

      showAmenitiesSelect.click(function () {
        amenitiesSelectWrapper.show();
      });

      amenitiesSelectedSave.click(function () {
        if (amenitiesSelectWrapper.find('input:checkbox:checked').length) {
          amenitiesSelectedItemWrapper.html('');
          amenitiesSelectWrapper.find('input:checkbox:checked').each(function (index, el) {
            $('<div>')
              .text($(el).val())
              .addClass('amenities-selected-item')
              .appendTo(amenitiesSelectedItemWrapper);
          });
          showAmenitiesSelect.parent().addClass('add-opened');
        } else {
          showAmenitiesSelect.parent().removeClass('add-opened');
        }
        amenitiesSelectWrapper.hide();
      });

      var photoField = $('#edit-field-photos');
      var photoListWrapper = $('#preview-photo-list');
      photoListWrapper.find('.proposal-photo-item').addClass('empty').html('');
      var imageTable = photoField.find('table.tabledrag-processed.tableheader-processed');
      imageTable.find('.image-widget-data').find('img').each(function () {
        $(this).remove();
      });

      imageTable.find('.image-preview').find('img').each(function () {
        var firstImageWrap = photoListWrapper.find('.proposal-photo-item.empty').first();
        var image = $(this).clone();
        var submitBtn = $(this).closest('tr').find('input[type="submit"]');
        if (firstImageWrap.length) {
          firstImageWrap.removeClass('empty')
        } else {
          firstImageWrap = $('<div>')
            .addClass('proposal-photo-item')
            .appendTo(photoListWrapper);
        }
        firstImageWrap
          .html(image)
          .append('<i class="fa fa-times"></i>')
          .find('i')
          .on('click', function(){
            submitBtn.mousedown();
          })
      });
      var imageInput = photoField.find('input.form-file');
      $(document).ajaxSuccess(function (event, xhr, settings) {
        if (settings.url.match(/^\/file\/ajax\/field_photos\/und/)) {
          var photoListWrapper = $('#preview-photo-list');
          photoListWrapper.find('.proposal-photo-item').addClass('empty').html('');
          var imageTable = $('#edit-field-photos').find('table.tabledrag-processed.tableheader-processed');
          imageTable.find('.image-widget-data').find('img').each(function () {
            $(this).remove();
          });
          imageTable.find('.image-preview').find('img').each(function () {
            var firstImageWrap = photoListWrapper.find('.proposal-photo-item.empty').first();
            var image = $(this).clone();
            var submitBtn = $(this).closest('tr').find('input[type="submit"]');
            if (firstImageWrap.length) {
              firstImageWrap.removeClass('empty')
            } else {
              firstImageWrap = $('<div>')
                .addClass('proposal-photo-item')
                .appendTo(photoListWrapper);
            }
            firstImageWrap
              .html(image)
              .append('<i class="fa fa-times"></i>')
              .find('i')
              .on('click', function(){
                submitBtn.mousedown();
              })
          });
        }
      });
      var photoButton = $('#field-photos-proposal-button');
      photoButton.unbind('click');
      photoButton.click(function () {
        imageInput.click();
      });
    }
  };
})(jQuery);
