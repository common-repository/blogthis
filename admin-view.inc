<?php
/*
Plugin Name: Blogthis!
Plugin URI: http://www.jpstacey.info/blog/files/code/blogthis.zip

Author: J-P Stacey
Author URI: http://www.jpstacey.info/

Description: View functions for the Blogthis! admin page

*/

// Some view functions
function blogthis_help_td($txt) {
	echo '<td style="font-size: 0.8em; font-style: italic">'.$txt.'</td>';
}
function blogthis_error($e) {
	echo '<p style="font-weight: bold; color: red">'.$e.'</p>';
}
function blogthis_label($name,$text) {
	echo '<th scope="row"><label for="input-'.htmlspecialchars($name).'"
		id="label-'.htmlspecialchars($name).'">'.htmlspecialchars($text).'</label></th>';
}
function blogthis_input($name, $form_name, $value, $len) {
	echo '<td><input name="'.$form_name.'" id="input-'.htmlspecialchars($name).'" size="'.$len.'"
		value="'.htmlspecialchars($value).'"/></td>';
}
?>