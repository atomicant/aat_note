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
  $output = '';
  $items = array();
  $result = db_query('SELECT n.title, an.* FROM {aat_note} an INNER JOIN {node} n ON an.nid = n.nid WHERE an.uid=%d', $account->uid);
  while ($note = db_fetch_object($result)) {
    $items[] = l($note->title, 'node/' . $note->nid) . ' : ' . check_plain($note->note);
  }
  if (count($items)) {
    $output .= theme('item_list', $items);
    $output .= l('Delete all', 'user/'. $account->uid .'/aat-notes/delete');
  }
  return $output;
}

/**
 * Delete all confirm form.
 *
 * @param array $form_state
 *   FAPI form state array
 * @param object $account
 *   User object
 *
 * @return array
 *   FAPI form array
 */
function aat_note_user_notes_delete(&$form_state, $account) {
  $form = array();
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $account->uid,
  );
  // confirm_form(
  //    $form,
  //    $question,
  //    $path,
  //    $description = NULL,
  //    $yes = NULL,
  //    $no = NULL,
  //    $name = 'confirm')
  return confirm_form(
      $form,
      t('Are you sure you want to delete all notes for account %name?', array('%name' => $account->name)),
      'user/'. $account->uid .'/aat-notes',
      t('This action cannot be undone.'),
      t('Delete'),
      t('Cancel'));
}

/**
 * Delete all form submit handler
 */
function aat_note_user_notes_delete_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_query('DELETE FROM {aat_note} WHERE uid=%d', $form_state['values']['uid']);
    $count = db_affected_rows();
    drupal_set_message(format_plural($count, 'One note deleted.', '@count notes deleted.'));
  }
  $form_state['redirect'] = 'user/'. $form_state['values']['uid'] .'/aat-notes';
}
