<html>
<head>
   <title>Processing multiple submits in PHP</title>
</head>
<body>
<?php
   // CS 1520 Summer 2013
   // Simply determine which submit was actually entered and show it
   $subs = array("Submit0", "Submit1", "Submit2");
   foreach ($subs as $value):
       if (isset($_POST[$value])):
           echo "You submitted $value <br />";
       endif;
   endforeach;
   echo "Your POST variables are: <br />";
   foreach ($_POST as $key => $value):
       echo "Key: $key   Value: $value <br />";
   endforeach;
?>
</body>
</html>
