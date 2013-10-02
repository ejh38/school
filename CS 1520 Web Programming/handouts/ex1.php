<!DOCTYPE html>
<html>
 <head>
	<title>Simple PHP Example</title>
 </head>
 <body>
 <?php
	$text = file("ex1.txt");
	echo "<h3>";
	foreach ($text as $line)
	{
            $line = rtrim($line);  // trim off newline
	    	$line = preg_replace("/Text/i", "PHP", $line);
                                   // change "Text" to "PHP"

            // convert text url to actual html link
	    	if (preg_match("/http/", $line))
				echo "<a href='$line'>Soliloquy Analysis</a>";
            else
	    		echo "$line<br/>";
	}
	echo "</h3>";
 ?>
 </body>
</html>
