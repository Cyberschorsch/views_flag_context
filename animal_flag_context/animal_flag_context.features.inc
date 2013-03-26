<?php
/**
 * @file
 * animal_flag_context.features.inc
 */

/**
 * Implements hook_views_api().
 */
function animal_flag_context_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function animal_flag_context_flag_default_flags() {
  $flags = array();
  // Exported flag: "Favorite".
  $flags['favorite_animl'] = array(
    'content_type' => 'taxonomy_term',
    'title' => 'Favorite',
    'global' => '0',
    'types' => array(
      0 => 'flag_context',
    ),
    'flag_short' => 'Mark as favorite animal',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unmark as favorite animal',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '1',
        1 => '2',
      ),
      'unflag' => array(
        0 => '1',
        1 => '2',
      ),
    ),
    'weight' => 0,
    'show_on_entity' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'api_version' => 2,
    'module' => 'animal_flag_context',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
