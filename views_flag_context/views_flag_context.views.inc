<?php

/**
 * Implements hook_views_plugins().
 */
function views_flag_context_views_plugins() {
  $plugin = array(
    'argument default' => array(
      'views_argument_default_flag' => array(
        'title' => t('Default Flags'),
        'handler' => 'views_argument_default_flag',
        'path' => drupal_get_path('module', 'views_flag_context') . '/handlers',
      ),
    ),
  );
  return $plugin;
}

