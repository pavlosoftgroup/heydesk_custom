<?php


function social_icon_block_info() {
	$blocks['social_icon'] = array(
		'info' => t('Social icons block'),
		'status' => FALSE,
	);
	return $blocks;
}

function social_icon_block_view($delta = '') {
	switch ($delta) {
		case 'social_icon':
			$block['subject'] = t('Social icon');
			$block['content'] = social_icon_block_contents($delta);
			return $block;
			break;
	}

}

function social_icon_block_configure($delta = '') {
	$form = array();

	switch ($delta) {
		case 'social_icon':
			$form['social_icon_width'] = array(
				'#title' => t('Icons width'),
				'#type' => 'textfield',
				'#size' => 3,
				'#description' => t('Default width 50px'),
				'#default_value' => variable_get('social_icon_width', 50),
				'#suffix' => 'px',
			);
			$form['social_icon_height'] = array(
				'#title' => t('Icons height'),
				'#type' => 'textfield',
				'#size' => 3,
				'#description' => t('Default height 50px'),
				'#default_value' => variable_get('social_icon_height', 50),
				'#suffix' => 'px',
			);
			$form['social_icon_position'] = array(
				'#title' => t('Icons position'),
				'#type' => 'select',
				'#options' => array(
					'gorisontal' => t('Gorisontal'),
					'vertical' => t('Vertical')

				),
				'#size' => 3,
				'#description' => t('Default value 50px'),
				'#default_value' => variable_get('social_icon_position', 'vertical'),
				'#suffix' => 'px',
			);
			break;
	}
	return $form;
}

function social_icon_block_save($delta = '', $edit = array()) {
	switch ($delta) {
		case 'social_icon':
			variable_set('social_icon_width', intval($edit['social_icon_width']));
			variable_set('social_icon_height', intval($edit['social_icon_height']));
			variable_set('social_icon_position', $edit['social_icon_position']);
			break;
	}
	return;
}


function social_icon_block_contents($delta) {
	switch ($delta) {
		case 'social_icon':
			$output = '';
			$entity = entity_load('social_icon');
			$output .= '<div class="social-wrap">';
			foreach ($entity as $icon) {
				// dpm($icon);
				if (isset($icon->icon)) {
					$image_path = file_create_url(file_load($icon->icon)->uri);
				}

				if (isset($icon->hover_icon)) {
					$hover_image_path = file_create_url(file_load($icon->hover_icon)->uri);
				}

				$image = theme_image(array(
					'path' => $image_path,
					'alt' => $icon->title,
					'title' => $icon->title,
					'width' => variable_get('social_icon_width', 50),
					'height' => variable_get('social_icon_height', 50),
					'attributes' => array(
						'class' => array('social_icon'),  //.$icon->id,
						'data-hover-icon' => isset($hover_image_path) ? $hover_image_path : ''
					),
				));

				/*if(isset($hover_image_path)) {
						$hover_icon = theme_image(array(
								'path' => $hover_image_path,
								'alt' => $icon->title,
								'title' => $icon->title,
								'width' => variable_get('social_icon_width', 50),
								'height' => variable_get('social_icon_height', 50),
								'attributes' => array('class' => 'hover_social_icon' . $icon->id),
						));
				}*/

				$link = theme_link(array(
					'text' => $image,
					'path' => $icon->url,
					'options' => array(
						'attributes' => array(
							'class' => 'social_url',
							'title' => $icon->title
						),
						'html' => TRUE
					)
				));
				$output .= $link;

				/* $output .= '<a href="'. $icon->url . '"> ';
				 $output .= '<img src="'. file_create_url(file_load($icon)->uri) . '" ';
				 $output .= 'width="' . variable_get('social_icon_width', 50). 'px" height="'. variable_get('social_icon_height', 50).'px" /></a>';*/
			}
			$output .= '</div>';
			$output .= '<p>
                      E. support@heydesk.com</br>
                      VAT DK38037366.</br>
                      </br>
                      HQ: Heydesk</br>
											Søndergade 8, 2. th</br>
											DK-8000 Aarhus C</br>
											Denmark
                  </p>';
	}
	return $output;
}
