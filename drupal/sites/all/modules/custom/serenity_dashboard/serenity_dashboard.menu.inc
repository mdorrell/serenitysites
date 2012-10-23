<?php
/**
 * hook_menu callback for serentiy dashboard page
 */
function serenity_dashboard_page() {
  global $language;
  
  $menu_name = 'menu-main-menu-u-18'; // . $language->language;
  $menu = menu_load($menu_name);

  module_load_include('inc', 'menu', 'menu.admin');
  $form = drupal_get_form('menu_overview_form', $menu);
	$content = $form;
	return $content;
}