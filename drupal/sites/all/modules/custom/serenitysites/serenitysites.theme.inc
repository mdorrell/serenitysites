<?php

/**
 * make a multicolumn ul list or links
 */
function theme_ul_list_columns($vars) {

  // Init array
  $arr = array();
  for($x=0; $x<$vars['numcol']; $x++){
    $arr[$x] = '';
  }

  //populate array with $numcol columns
  $count = 0;
  foreach ($vars['rows'] as $row) {
    $row = array_merge((array)$row, array('from_popup' => TRUE));
    $arr[$count % $vars['numcol']] .= theme($vars['link_theme'], $row);
    $count++;
  }

  //create html $content, wrapping array content in ul tags
  $content = '';
  for ($x=0; $x<count($arr); $x++) {
    $class = ($x % 2 == 0) ? 'odd' : 'even';
    $content .= '<ul class="' . $class . '">' . $arr[$x] . '</ul>';
  }

  return $content;
}

/**
 * theme the obit archive links
 */
function theme_obit_archive_link($vars) {
  $path = 'obituaries/archive/' . $vars['year'] . '/' . $vars['month_num'];
  $link_class = ($_GET['q'] == $path) ? 'active' : NULL;
  $link = '';
  if ($vars['from_popup']) {
    $link = '<li>' . l(t($vars['month']).' '.$vars['year'], $path, array(array('attributes' => array('class' => $link_class)))) . '</li>';
  }
  else {
    $counts = $vars['count'];
    $link = '<li>' . l(t($vars['month']), $path, array(array('attributes' => array('class' => $link_class)))) . ' (' . $counts . ')</li>';
  }

  return $link;
}
