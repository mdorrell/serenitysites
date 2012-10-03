<?php

/**
 * Display correct menu for "language"
 */
function serenitysites_main_main_block_contents() {
  global $language;

  $menu_name = 'main-menu';
  if ($language->language != 'en') {
    $menu_name = 'menu-main-menu-' . str_replace('.', '-', $language->language);
  }
  
  $main_menu_tree = menu_tree($menu_name); 
	$content = '<div id="main-menu">' . drupal_render($main_menu_tree) . '</div>';
  return $content;
}