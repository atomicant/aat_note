<?php
/**
 * @file aat-note-my-notes.tpl.php
 *
 * Theme implementation to display a single Drupal page.
 *
 * Available variables:
 * - $notes - a themed item list of all notes
 * - $delete_link - admin link to delete all notes
 *
 */
?>
<div class="notes">
  <?php print $notes ?>
</div>
<div class="delete-link">
  <?php print $delete_link ?>
</div>
