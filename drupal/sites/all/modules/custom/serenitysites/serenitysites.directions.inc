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
