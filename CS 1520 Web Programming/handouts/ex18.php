<!DOCTYPE html> 
<html>
<head>
<title>CS 1520 PHP Example 18</title>
</head>
<body>
<?php
  # Simple PHP Script to input a sentence and break it into words.
  
  if (isset($_POST["sentence"])):
     $sent = strip_tags(stripslashes($_POST["sentence"]));
     echo "Your entered sentence is: $sent <br />";
     $words = preg_split("/\W+/", $sent);
     foreach ($words as $value):
          echo "$value <br/> ";
     endforeach;
  endif;
?>
<form action="ex18.php" 
      method="POST">
      Please enter a sentence: 
      <input type = "text" name = "sentence">
      <input type = "submit" value = "Process">
</form>
</body>
</html>
