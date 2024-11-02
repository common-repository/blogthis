<?php
/*
Plugin Name: Blogthis
Plugin URI: http://www.jpstacey.info/blog/files/code/blogthis.zip

Author: J-P Stacey
Author URI: http://www.jpstacey.info/

Description: Adds a set of blog-this links: links to digg, del.icio.us and technorati by default. The images reside in wp-content/plugins/blogthis-icons/ and need to have the same name as the key in the $a_blogthis_links (see the source for more details).

*/

// Root image URL
add_option('blogthis_image_url', '/wp-content/plugins/blogthis/', 'URL for Blogthis! images', 'yes');

// The blogthis links - default values
add_option('blogthis_feeds', array(
		'digg' => array(
			'Digg it', 'http://digg.com/submit?phase=2'
				.'&amp;url=!PERMALINK!'
				.'&amp;title=!TITLE!'
		),
		'delicious' => array(
			'del.icio.us', 'http://del.icio.us/post?v=3'
				.'&amp;url=!PERMALINK!'
				.'&amp;title=!TITLE!'
		),
		'technorati' => array(
			'Technorati?',
			'http://technorati.com/cosmos/search.html?'
				.'url=!PERMALINK!'
		)
	),
	'Default Blogthis! feeds', 'no'
);

// Some container elements
$h_blogthis_container = 'div class="blog-this"';
$h_blogthis_title = 'Blog this:';
$h_blogthis_links_container = 'ul class="blog-this-links"';
$h_blogthis_link_wrapper = 'li';

// Open and close these container elements
function blogthis_open($txt) {
	return '<'.$txt.'>';
}
function blogthis_close($txt) {
	return '</'.preg_replace('/^(\S+).*/','\1',$txt).'>';
}

// Replace the elements of the URLs with the necessaries
function blogthis_link ($link) {
	$link = preg_replace('/!TITLE!/', urlencode(get_the_title()), $link);
	$link = preg_replace('/!PERMALINK!/', urlencode(get_permalink()), $link);
	return $link;
}

// Main
function wp_blogthis() {
	// Bring in all the variables defined up there
	global 
		$h_blogthis_container, 
		$h_blogthis_title,
		$h_blogthis_links_container,
		$h_blogthis_link_wrapper;

	// Write some opening tags and the title
	echo blogthis_open($h_blogthis_container);
	echo $h_blogthis_title;
	echo blogthis_open($h_blogthis_links_container);

	// Loop over the bloggables
	$a_blogthis_links = get_option('blogthis_feeds');
	foreach ($a_blogthis_links AS $k => $v) { 
		$i = get_option('blogthis_image_url').$k.'.gif';
		$t = $v[0];
		$l = '<a href="'.blogthis_link($v[1]).'"';

		echo blogthis_open($h_blogthis_link_wrapper)
			.$l.' class="img"><img '
			.'src="'.$i.'">'.$t.'</a>'
		.blogthis_close($h_blogthis_link_wrapper);
	}
	echo blogthis_close($h_blogthis_links_container);
	echo blogthis_close($h_blogthis_container);
}

// Meta info
function blogthis_meta($what) {
	switch($what):
		case 'title':
			return 'Blogthis!';
		break;
		case 'blank_feed':
			return 'BLOGTHIS-NEW';
		break;
	endswitch;
	return "";
}

// Admin
function blogthis_admin() {
	include("admin-page.inc");
}

// Add to admin
function blogthis_add_to_admin() {
	if (function_exists('add_options_page')) {
		add_submenu_page('plugins.php', blogthis_meta('title'), blogthis_meta('title'), 1, basename(__FILE__), 'blogthis_admin');
	}
}
add_action('admin_menu','blogthis_add_to_admin');


?>
