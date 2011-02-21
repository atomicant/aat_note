<?php
// $Id$

/**
 * @file
 * This file holds the theme functions for aat_note module
 *
 */

/**
 * Theme function for aat_note_entry_form
 */ 
function theme_aat_note_entry_form($form) {
  $output = '';
  $output .= '<div id="aat-note-entry-form">';
  $output .= drupal_render($form['aat_note']);
  $output .= '</div>';
  $output .= drupal_render($form);
  return $output;
}
