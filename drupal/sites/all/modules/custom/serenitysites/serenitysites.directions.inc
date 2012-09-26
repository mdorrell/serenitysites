<?php
function serenitysites_directions_node_view(&$node) {
  $locationmap_path = drupal_get_path('module', 'locationmap');
  drupal_add_js('http://maps.google.com/maps/api/js?v=3&sensor=false',  array('type' => 'external', 'weight' => 5));
  drupal_add_js($locationmap_path . '/locationmap.js', array('type' => 'file', 'weight' => 6, 'scope' => 'footer'));


  $address = serenitysites_get_address($node->field_directions_address[LANGUAGE_NONE][0]['value']);
  if (!empty($address)) {
    $address = implode(' ', $address);
    $coordinates = locationmap_geocode_for_address($address);

    $locationmap_settings = array(
      'address' => $address,
      'info' => $address,
      'lat' => $coordinates[0],
      'lng' => $coordinates[1],
      'zoom' => variable_get('locationmap_zoom', 14),
      'type' => variable_get('locationmap_type', 'google.maps.MapTypeId.ROADMAP'),
    );
    drupal_add_js(array('locationmap' => $locationmap_settings), 'setting');
    $node->content['map'] = array('#type' => 'markup', '#markup' => theme('locationmap_map'), '#weight' => 10);
    
    $node->content['field_directions_address']['#prefix'] = '<div class="directions-wrapper">' . $node->content['field_directions_address']['#prefix'];
    $node->content['field_directions']['#suffix'] .= '</div>';
  }
}

/**
 * hook_block callback for map block
 */
function serenitysites_map_block_contents() {
  global $language;
  $mapwidth = 250;
  $mapheight = 200;
  $content = '';

  $query = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('n.type', 'directions')
    ->condition('n.status', '1')
    ->condition('n.language', $language->language);
  $nid = $query->execute()->fetchField();
  $node = node_load($nid);

  // Get address and map image for it
  $address = serenitysites_get_address($node->field_directions_address[LANGUAGE_NONE][0]['value']);
  if (!empty($address)) {
    $address = implode(' ', $address);
    $coordinates = locationmap_geocode_for_address($address);
    $url = serenitysites_map_static_image_url($coordinates[0], $coordinates[1], $mapwidth, $mapheight, 13);

    // create the content
    $content = '<h2>Directions</h2>';
    $content .= l('<img src="' . $url . '" alt="Location map" />', 'node/' . $nid, array('html' => TRUE));

    $address_field = $output = field_view_field('node', $node, 'field_directions_address');
    $content .= render($address_field);
  }

  return $content;
}

/**
 * Get address from the fieldcollection id
 */
function serenitysites_get_address($field_collection_id) {
  $address = array();
  $entity = entity_load('field_collection_item', array($field_collection_id));
  if (!empty($entity)) {
    $entity = array_pop($entity);
    $address = array(
      'address' =>$entity->field_directions_street_address[LANGUAGE_NONE][0]['value'],
      'city' => $entity->field_directions_city[LANGUAGE_NONE][0]['value'],
      'state' => $entity->field_directions_state[LANGUAGE_NONE][0]['value'],
      'zip' => $entity->field_directions_zip[LANGUAGE_NONE][0]['value']
    );
  }
  return $address;
}

/**
 * Get static image url
 */
function serenitysites_map_static_image_url($latitude, $longitude, $width = 200, $height = 150, $zoom = 14) {
  $image_url = 'http://maps.googleapis.com/maps/api/staticmap?zoom=' . $zoom;
  $image_url .= "&amp;size={$width}x{$height}";
  $image_url .= '&amp;markers=' . $latitude . ',' . $longitude;
  $image_url .= "&amp;sensor=false";
  return($image_url);
}