<html>
<head>
   <title>Processing multiple forms in PHP</title>
</head>
<body>
<?php
   // CS 1520 Summer 2013
   // Determine the form that was submitted by the value passed into
   // the "submit" field.  Use simple regular expression handling to
   // extract the integer from the string.
   $form = $_POST["submit"];
   preg_match("/[0-9]+/", $form, $result);
   $val = $result[0];
   echo "You submitted form $val <br />";
   echo "Your POST variables are: <br />";
   foreach ($_POST as $key => $value):
       echo "Key: $key   Value: $value <br />";
   endforeach;
?>
</body>
</html>
