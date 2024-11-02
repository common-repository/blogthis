<?php
/*
Plugin Name: Blogthis!
Plugin URI: http://www.jpstacey.info/blog/files/code/blogthis.zip

Author: J-P Stacey
Author URI: http://www.jpstacey.info/

Description: Control functions for the Blogthis! admin page

*/

// Scalar options
function blogthis_get_names() {
	$s = array();
	$s['scalars'] = array('image_url');
	$s['vectors'] = array('feed_name','feed_text','feed_link');
	return $s;
}

// Sets post - takes it as an argument
function blogthis_set_post($P) {
	$s = blogthis_get_names();

	// Set all scalars
	foreach($s['scalars'] AS $k => $v) {
		update_option('blogthis_'.$v, $P[$v]);
	}

	// Create the vectors array and set
	$a = array();
	for( $i = 0; $i < count($P[$s['vectors'][0]]); $i++) {
		$name = $P[$s['vectors'][0]][$i];
		if (strlen($name) > 0) {
			$a[$name] = array(
				$P[$s['vectors'][1]][$i], $P[$s['vectors'][2]][$i]
			);
		}
	}
	update_option('blogthis_feeds', $a);
}

// Check $_POST - takes it as argument
function blogthis_check_post($P) {

	$s = blogthis_get_names();

	$update_ok = true;

	// Check scalars exist	
	foreach($s['scalars'] AS $k => $v) {
		$update_ok = ($update_ok && isset($P[$v]));
	}

	// Check all vectors exist
	$len = 0;
	foreach($s['vectors'] AS $k => $v) {
		$update_ok = ($update_ok && isset($P[$v]) && is_array($P[$v])
			&& ( ($len==0)||($len==count($P[$v])) )
		);
		$len = count($P[$v]);
	}

	return $update_ok;
	//$_REQUEST['blogthis_error'] = 'Inconsistency: not all the feed configuration was set';
}
?>

