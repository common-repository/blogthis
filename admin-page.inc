<?php
/*
Plugin Name: Blogthis!
Plugin URI: http://www.jpstacey.info/blog/files/code/blogthis.zip

Author: J-P Stacey
Author URI: http://www.jpstacey.info/

Description: Admin page for Blogthis! plugin

*/

// Control functions
include("admin-control.inc");
// View functions
include("admin-view.inc");

if (blogthis_check_post($_POST)) {
	blogthis_set_post($_POST);
}

?><div class="wrap">
	<form method="post">
		<h2><?php echo blogthis_meta('title')?> configuration</h2>

		<?php if (isset($_REQUEST['blogthis_error'])) { blogthis_error($_REQUEST['blogthis_error']); } ?>

		<fieldset name="meta">
			<legend>General config</legend>
		<table class="optiontable"> 
			<tr valign="top"> 
				<?php blogthis_label('image_url', 'Relative/absolute URL for images') ?>
				<?php blogthis_input('image_url', 'image_url', get_option('blogthis_image_url'), 25) ?>
				<?php blogthis_help_td('If your blog sits at e.g. www.x.com/foo/, then this URL should start 
				"/foo/wp-content/...". Otherwise the default should work fine. Remember the slash at the end!')?>
			</tr>
		</table>
		</fieldset>

		<?php $a_feeds = get_option('blogthis_feeds');

			// Get keys of array, and push a blank key on the end
			$a_names = array_keys($a_feeds);
			array_push($a_names,blogthis_meta('blank_feed'));

			foreach ($a_names AS $kk => $k) {
				// Config for blank feed at end
				if ($k != blogthis_meta('blank_feed')) {
					$n = $k;
					$v = $a_feeds[$k];
				} else {
					$n = '';
					$v = array("", "");
				}
		?>
		<fieldset name="feeds-<?php echo $k ?>">
			<legend><?php if(strlen($n)) { ?>Feed configuration '<?php echo $k; ?>'<?php } else { ?>New feed (fill 
				in name to create)<?php } ?></legend>
		<table class="optiontable">
			<tr valign="top"> 
				<?php blogthis_label('feed-name-'.$k, 'Feed name') ?>
				<?php blogthis_input('feed-name-'.$k, 'feed_name[]', $n, 15) ?>
				<?php blogthis_help_td('This is the image filename, less ".gif"') ?>
			</tr>

			<?php if(strlen($n)) { ?><tr valign="top">
				<th scope="row"><b>Image preview</b></th>
				<td><img src="<?php echo get_option('blogthis_image_url').$k.'.gif'?>"
					alt="If you can't see the image, check the URL config and the feed name"/></td>
			</tr><?php } ?>

			<tr valign="top">
				<?php blogthis_label('feed-text-'.$k, 'Accompanying text') ?>
				<?php blogthis_input('feed-text-'.$k, 'feed_text[]', $v[0], 25) ?>
			</tr>

			<tr valign="top">
				<?php blogthis_label('feed-text-'.$k, 'Feed URL') ?>
				<?php blogthis_input('feed-text-'.$k, 'feed_link[]', $v[1], 25) ?>
				<?php blogthis_help_td('This URL has special strings - e.g. !TITLE! and !PERMALINK! - replaced
				before being output in a '.blogthis_meta('title').' link') ?>
			</tr>

		</table>
		</fieldset>

		<?php } ?>

		<div class="submit"><input type="submit" name="Submit" value="Update Options &raquo;" /></div>

	</form>
</div>
