<?php

/**
 * @file
 * Definition of views_plugin_argument_default.
 */

/**
 * @defgroup views_argument_default_plugins Views argument default plugins
 * @{
 * Allow specialized methods of filling in arguments when they aren't provided.
 *
 * @see hook_views_plugins()
 */

/**
 * The fixed argument default handler; also used as the base.
 */
class views_argument_default_flag extends views_plugin_argument_default {
  
  /**
   * Define the options form to enable selection of flags.
   */

  function options_form(&$form, &$form_state) {
 
    // Load all flags and types of each flag.
    $flags = flag_get_flags('taxonomy_term');
    // Combine all types (=vocabs) into one option array.
    $flag_types = array();
    $flag_options = array();
    foreach ($flags as $flagname => $value) {
      // $flag_types is the array storing all vocabs.
      $flag_types = array_merge($flag_types, $value->types);
      // $flag_options is the array storing all possible Flags.
      $flag_options[$flagname] = $flagname;
    }
    $form['flags'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Choose the Flags'),
      '#options' => $flag_options,
      '#process' => array('form_process_checkboxes'),
      '#default_value' => $this->options['flags'],
    );
    $form['vocabularies'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Choose the Vocabularies'),
      '#options' => drupal_map_assoc($flag_types),
      '#process' => array('form_process_checkboxes'),
      '#default_value' => $this->options['vocabularies'],
    );
    $form['fallback'] = array(
      '#type' => 'textfield',
      '#title' => t('Fallback value'),
      '#description' => t('Value to use, when no item is flagged'),
      '#default_value' => $this->options['fallback'],
    );
    $form['multiple_operator'] = array(
      '#type' => 'select',
      '#options' => array(
        '+' => 'OR',
        ',' => 'AND',
      ),
      '#title' => t('Operator for multiple values'),
      '#default_value' => $this->options['multiple_operator'],
    );
  }

  /**
   * Return all possible options for the view and provide default values.
   */
  function option_definition() { 
    $options = parent::option_definition();
    $options['flags'] = array('default' => array());
    $options['vocabularies'] = array('default' => array());
    $options['fallback'] = array('default' => 'all');
    $options['multiple_operator'] = array('default' => '+');
    return $options;
  }
  /**
   * Provide the default form form for submitting options.
   */
  function options_submit(&$form, &$form_state, &$options = array()) {
    // We filter the options on only selected ones.
    $options['flags'] = array_filter($options['flags']);
    $options['vocabularies'] = array_filter($options['vocabularies']);
  }

  /**
   * This function controls what to return to the contextual filter.
   */
  function get_argument() { 
    // Get available flag types from the system.
    $flags = flag_get_flags('taxonomy_term');

    // Get all User flags.
    $user_flags = flag_get_user_flags('taxonomy_term');
    
    // This array will collect all Term IDs which will be filtered.
    $tids = array();
    
    // Get the vocab foreach flag.
    foreach ($flags as $flagname => $flag) {
      // We only proceed with this flag, if it has been selected and the current
      // user has flagged terms with that flag.
      if (!empty($this->options['flags'][$flagname]) && !empty($user_flags[$flagname])) {
        // Get all tids from the user flags.
        $user_tids = array_keys($user_flags[$flagname]);
        $vocabs = array();
        // Check  which vocabularies are valid for this handler.
        foreach ($flag->types as $vocab) {
          if (!empty($this->options['vocabularies'][$vocab])) {
            $vocabs[] = $vocab;
          }
        }
        // We add the valid terms of the flag set to our default argument list.
        $valid_tids = _views_flag_context_filter_tids_on_vocabularies($user_tids, $vocabs);
        $tids = array_merge($tids, $valid_tids);
      }
    }
    // If no tids are valid, we can fallback to a given value.
    if (empty($tids)) {
      // Fall back to the exception value (by default this is 'all')
      return $this->options['fallback'];
    }
    // If there are term ids available we return them by concating the terms
    // with the multiple operator (AND or OR).
    else {
      return implode($this->options['multiple_operator'], $tids);
    }
  }

  /**
   * Initialize this plugin with the view and the argument is is linked to.
   */
  function init(&$view, &$argument, $options) {
    parent::init($view, $argument, $options);
  }


}
