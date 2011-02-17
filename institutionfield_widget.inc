<?php

/**
* Implementation of hook_widget_info().
*/
function institutionfield_widget_info() {
  return array(
    // The machine name of the widget.
    'institutionfield_widget' => array(
      // The human-readable label of the field that will be seen in the Manage fields screen.
      'label' => t('Institution widget'),
      // An array of the field types this widget can be used with.
      'field types' => array('institutionfield'),
      'multiple values' => CONTENT_HANDLE_CORE,
      'callbacks' => array(
        'default value' => CONTENT_CALLBACK_DEFAULT,
      ),
    ),
  );
}

/**
* Implementation of hook_widget().
*/
function institutionfield_widget(&$form, &$form_state, $field, $items, $delta = 0) {
     
    $vid = 12; //Institution vocabulary id
    
    //~ print_r($items[$delta]['year']);
    
    //~ print_r(time());
    
    $default_value = isset($items[$delta]['year']) ? $items[$delta]['year'] : date('Y', time());
    
    $element['institution'] = array(
      '#type' => 'textfield', 
      '#title' => t('Institution'), 
      '#maxlength' => 50, 
      '#autocomplete_path' => 'taxonomy/autocomplete/'.$vid, 
      '#default_value' => $value = isset($items[$delta]['institution']) ? $items[$delta]['institution'] : NULL, 
      '#weight' => -1,
    );
    
    $vid = 13; //Achievement vocabulary id
    
    $element['achievement'] = array(
      '#type' => 'textfield', 
      '#title' => t('Achievement'), 
      '#maxlength' => 50, 
      '#autocomplete_path' => 'taxonomy/autocomplete/'.$vid, 
      '#default_value' => $value = isset($items[$delta]['achievement']) ? $items[$delta]['achievement'] : NULL,
      '#weight' => 0,
    );
    
    $vid = 24; //Degree level vocabulary id
    
    //Load the vocabulary to populate the dropdown select
    $vocabulary = taxonomy_get_tree($vid);
    
    //Create the array to hold possible dropdown values
    $degree_levels = array();
    
    //Populate the industries array_merge
    foreach ($vocabulary as $term) {
      $degree_levels[] = $term->name;
    }
    
    $element['degree_level'] = array(
      '#type' => 'select', 
      '#title' => t('Degree Level'), 
      '#maxlength' => 50,
      '#options' => $degree_levels,
      '#autocomplete_path' => 'taxonomy/autocomplete/'.$vid, 
      '#default_value' => $value = isset($items[$delta]['degree_level']) ? $items[$delta]['degree_level'] : NULL,
      '#weight' => 1,
      '#prefix' => '<div class="field-degree-level">',
      '#suffix' => '</div>',
    );
    
    $element['year'] = array(
      '#type' => 'date_select',
      '#title' => 'Achieved in',
      '#date_format' => 'Y',
      '#date_label_position' => 'within',
      '#date_year_range' => '-50:0',
      '#default_value' => isset($items[$delta]['year']) ? $items[$delta]['year'] : date('Y', time()),
      '#weight'        => 2,
      '#prefix' => '<div class="field-year">',
      '#suffix' => '</div>',
    );
    
    if ($items[$delta]['year'] == 'Current')
      $def_val = 1;
    else $def_val = 0;
    
    $element['currentstudent'] = array(
      '#type' => 'checkbox',
      '#title' => t('I am currently studying here'),
      '#default_value' => $def_val,
      '#weight' => 3,
      '#prefix' => '<div class="field-currentstudent">',
      '#suffix' => '</div>',
    );
 
  // Used so that hook_field('validate') knows where to
  // flag an error in deeply nested forms.
  if (empty($form['#parents'])) {
    $form['#parents'] = array();
  }
  $element['_error_element'] = array(
    '#type' => 'institution',
    '#value' => implode('][', array_merge($form['#parents'], array('institution'))),
  );
 
  return $element;
}


