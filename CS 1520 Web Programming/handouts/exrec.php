<!DOCTYPE html>
<html>
 <head>
  <title>PHP Examples - Recitation</title>
 </head>
 <body>
 <?php
	// Simple intro to Perl-style regular expressions
	function nl()
	{
		echo "<br />";
	}
	
	// time
	echo "Example Time <br>";
	$subject="00:00:15 0:56:25 95:00:25 11:15:09 15:96:22 20:15:10 ";
	$pattern = "/([01][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])/";
	if (preg_match_all($pattern, $subject, $result, PREG_OFFSET_CAPTURE)):
		echo "$pattern was found: \n";
		print_r($result);
		nl();
	endif;
	
	//zip code
	echo "Example Zip-code <br>";
	$subject="15221-abcd 12345 12345-123 12345-1234 1235 54263 54263-4321";
	$pattern = "/\d{5}(-\d{4})?/";
	if (preg_match_all($pattern, $subject, $result, PREG_OFFSET_CAPTURE)):
		echo "$pattern was found: \n";
		print_r($result);
		nl();
	endif;
 ?>
 </body>
</html>
