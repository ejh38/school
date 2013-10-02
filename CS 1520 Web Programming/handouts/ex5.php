<!DOCTYPE html>
<html>
 <head>
  <title>Fifth PHP Example</title>
 </head>
 <body>
 <?php
      # Here are a few PHP predefined variables 
      echo $_SERVER["HTTP_HOST"], "<br/>";
      echo $_SERVER["SERVER_SOFTWARE"], "<br/>";
      echo $_SERVER["SCRIPT_FILENAME"], "<br/>";
      echo $_POST, "<br/>";
      # The output from the loop below shows all of the $_SERVER
      # values for this execution.  We will discuss how the loop
      # works shortly (after discussing arrays).  Note that if we
      # substitute POST for SERVER, the output will be empty, since
      # in this script there are no POST parameters.  When we process
      # forms, POST will not be empty and we will extract values from it
      echo "Values in the \$_SERVER Variable: <br/>";
      foreach ($_SERVER as $key => $val)
      {
           echo "$key has value $val <br/>";
      }
   
      # The phpinfo() function is very useful, showing the configuration
      # information about the server.
      phpinfo();
  ?>
 </body>
</html>
