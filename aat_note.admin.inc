<?php
// $Id$

/**
 * @file
 * Administration page callbacks for the aat_note module.
 */

/**
 * Form builder. Configure annotations.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function aat_note_admin_settings() {
  $form = array();
  // Get an array of node types with internal names as keys and
  // "friendly names" as values. E.g.,
  // array('page' => 'Page', 'story' => 'Story')
  $options = node_get_types('names');

  $form['aat_note_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Users may create notes to these content types'),
    '#options' => $options,
    '#default_value' => variable_get('aat_note_node_types', array('page')),
    '#description' => t('A text field will be available on these content types to make user-specific notes.'),
  );

  return system_settings_form($form);
}

/**
 * Page with user notes
 *
 * @param object $account
 *
 * @return
 *   Rendered page
 */
function aat_note_user_notes($account) {
  $items = array();
  $result = db_query('SELECT n.title, an.* FROM {aat_note} an INNER JOIN {node} n ON an.nid = n.nid WHERE an.uid=%d', $account->uid);
  while ($note = db_fetch_object($result)) {
    $items[] = l($note->title, 'node/' . $note->nid) . ' : ' . check_plain($note->note);
  }
  return theme('item_list', $items);
}
