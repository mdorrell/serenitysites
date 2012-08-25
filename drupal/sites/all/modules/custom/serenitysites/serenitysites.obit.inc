<?php
/**
 * Archive filter for obituaries page
 */
function serenitysites_obit_archive_block_contents() {
  global $language;

  $query = db_select('node', 'n');
  $query->join('field_data_field_obit_date', 'od', 'od.entity_id = n.nid');
  $query->condition('n.type', 'obituary', '=')
    ->condition('n.status', 1, '=')
    ->condition('n.language', $language->language, '=')
    ->groupBy('year')
    ->groupBy('month')
    ->orderBy('year', 'DESC')
    ->orderBy('month_num', 'DESC');

  $query->addExpression("date_format(od.field_obit_date_value, '%M')", 'month');
  $query->addExpression("date_format(od.field_obit_date_value, '%m')", 'month_num');
  $query->addExpression("date_format(od.field_obit_date_value, '%Y')", 'year');
  $query->addExpression("count(*)", 'count');


  $modal_query = clone $query;
  $result = $query->execute();
  
  $count = 0;
  $total_count = $result->rowCount();
  $content = '<ul>';
  foreach ($result as $row) {
    //$content .= '<li>' . l($row->month, 'obituaries/archive/' . $row->year . '/' . $row->month_num) . '</li>';
    $content .= theme('obit_archive_link', (array)$row);
    $count++;
    if ($count >= 5) {
      break;
    }
  }  

  $content .= "</ul>";

  if ($total_count > 5) {
    $content .= '<a href="#" class="show-more">View All</a>';
    $modal_result = $modal_query->execute();
    $content .= theme('ul_list_columns', array('rows' => $modal_result, 'numcol' => 4, 'link_theme' => 'obit_archive_link'));
          
  }
   
  return $content;
}
