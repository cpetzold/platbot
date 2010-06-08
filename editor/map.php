<?php
	header('Cache-Control: no-cache, must-revalidate');
	header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');
	header('Content-type: application/json');
	header("Content-Disposition: attachment; filename=\"{$_GET['n']}.map\";\n\n");
	echo $_GET['t'];
?>