<!DOCTYPE html>
<html>
<head>
<title>CS 1520 PHP Example 17</title>
</head>
<body>
<?php
  # Simple PHP Script to input and test a date. 
  date_default_timezone_set('America/New_York');  
  if (isset($_POST["date"])):
     $date = strip_tags(stripslashes($_POST["date"]));
     echo "Your entered date is $date <br />";
     $test = strtotime($date);
     if ($test === -1):
        echo "Your date was invalid <br />";
     else:
        $phpdate = date("D F j Y", $test);
        echo "The date is $phpdate <br />";
     endif;
     if (isvaliddate($date)):
        echo "Using reg. exp. test, the date is $date <br />";
     else:
        echo "Using reg. exp. test, the date is invalid <br />";
     endif;
  endif;

  // Function from regular-expressions.info site, modified for PHP
  function isvaliddate($date)
  {
    $test = "/^((19|20)\d\d)[- \/.](0[1-9]|1[012])[- \/.](0[1-9]|[12][0-9]|3[01])$/";
  if (preg_match($test,$date,$results)) {
    echo "Match is "; print_r($results); echo "<br/>";
    if ($results[4] == 31 && ($results[3] == 4 || $results[3] == 6 ||
                              $results[3] == 9 || $results[3] == 11))
    {
        return "";
    }
    else if ($results[4] >= 30 && $results[3] == 2)
    {
        return "";
    }
    else if ($results[3] == 2 && $results[4] == 29)
    { 
        if  (($results[1] % 4 != 0))
            return "";
        else if (($results[1] % 100 == 0) && ($results[1] % 400 != 0)) 
            return "";
        else return $results[0];
    }
    else return $results[0];
  }
}
?>
<form action="ex17.php" 
      method="POST">
      Please enter a date: 
      <input type = "text" name = "date">
      <input type = "submit" value = "Process">
</form>
</body>
</html>
