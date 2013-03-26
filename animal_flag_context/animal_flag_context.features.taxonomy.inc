<?php
/**
 * @file
 * animal_flag_context.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function animal_flag_context_taxonomy_default_vocabularies() {
  return array(
    'flag_context' => array(
      'name' => 'Flag Context',
      'machine_name' => 'flag_context',
      'description' => 'Stores available flag context',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
