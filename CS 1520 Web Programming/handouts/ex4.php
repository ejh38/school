<!DOCTYPE html>
<html>
 <head>
  <title>Fourth PHP Example</title>
 </head>
 <body>
 <?php
      /* PHP Comments can be in the style of C, C++/Java or Perl
         This multiline comment is in the C style */
      // The C++ / Java style is also fine
      # And the Perl style works as well (in case you are interested)

      // Note that with double quotes the variables are interpolated
      // into the string but with single quotes the variable names are
      // put into the strings.  If double-quotes are used, we can 
      // prevent interpolation by putting a backslash before the
      // variable name, as shown.
      // Also note something about the \n in the first two lines below:
      // 	With double-quotes, the \n produces a newline character
      // as we are used to seeing with C++ or Java
      //	With single-quote, the \n produces the characters \ and n
      //
      // 	However, in NEITHER case does a new line show up on the web
      // page, since newlines are ignored by the html parser -- we need a
      // <br/> to get a newline on the web page.
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 
      $x = 50;
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 
      echo '$x is $x and is type ', gettype($x), '<br/>\n'; 
      $x = $x * 1000000000;
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 
      $x = 10;
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 
      $x += 1.350;
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 
      echo var_dump($x), "<br />\n";
      $x = "hello " . $x;
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 
      echo var_dump($x), "<br />\n";
      echo "Here are the first three characters: <br/>";
      echo "$x[0] $x[1] $x[2] <br />";
      $y = $x;
      $x = $y == "hello 11";
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 
      $x = $y == "hello 11.35";
      echo "\$x is $x and is type ", gettype($x), "<br/>\n"; 

      $x = 1234;
      echo var_dump($x) . "<br/>\n";
      if (is_int($x))
	   echo "I am an int<br/>\n";
      else
	   echo "I am NOT an int<br/>\n";
      if (is_string($x))
	   echo "I am a string<br/>\n";
      else
	   echo "I am NOT a string<br/>\n";
      if (is_numeric($x))
	   echo "I am numeric<br/>\n";
      else
	   echo "I am NOT numeric<br/>\n";
      $x = "wacky1234";
      echo var_dump($x), "<br/>\n";
      if (is_int($x))
	   echo "I am an int<br/>\n";
      else
	   echo "I am NOT an int<br/>\n";
      if (is_string($x))
	   echo "I am a string<br/>\n";
      else
	   echo "I am NOT a string<br/>\n";
      if (is_numeric($x))
	   echo "I am numeric<br/>\n";
      else
	   echo "I am NOT numeric<br/>\n";
 ?>
</body>
</html>
