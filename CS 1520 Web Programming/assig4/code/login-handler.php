<?php
 session_start(); 
 ?>
<!DOCTYPE html>
<html>
	<head>
		<title>LINGO Player Logged In!</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<center>
	<h4>
	<a href = "lingo.html">Play LINGO!</a><br />
	<a href = "login.php">Log out :(</a><br />
	</h4>

</center>
 <?php

  include 'get-db.php';
  $db = getDB();
                          /****************************
                           ****************************
                           *** Uncomment this to see **
                           *** the Users table that ***
                           *** comes from Users.flat **
                           ****************************
                           ****************************/


$tables = array("Users"=>array("User_ID", "Name", "Email", "Password", "RoundsPlayed", "RoundsWon"),
                  "States"=>array("State_ID", "Guesser_ID", "Maker_ID", "Correct_Word",
                                  "Incorrect_Guesses", "Guessed_Letters", "Current_Word"),
                  "Users_States"=>array("US_ID", "U_ID", "S_ID"),
                  "WaitingUser"=>array("WU_ID", "U_ID"));

        foreach ($tables as $curr_table=>$curr_keys):
           $query = "select * from " . $curr_table; #Define query
           $result = $db->query($query);  #Eval and store result
           $rows = $result->num_rows; #Det. num. of rows
           $keys = $curr_keys;
  ?>
        <table border = "1">
        <caption><?php echo $curr_table;?></caption>
        <tr align = center>
  <?php
           foreach ($keys as $next_key):
               echo "<th>$next_key</th>";
           endforeach;
           echo "</tr>"; 
           for ($i = 0; $i < $rows; $i++):  #For each row in result table
               echo "<tr align = center>";
               $row = $result->fetch_array();  #Get next row
               foreach ($keys as $next_key)  #For each column in row
               {
                    echo "<td> $row[$next_key] </td>"; #Write data in col
               }
               echo "</tr>";
           endfor;
           echo "</table><br />";
        endforeach;
                        
                         /****************************
                         ****************************
                         *** Uncomment this to see **
                         *** the Users table that ***
                         *** comes from Users.flat **
                         ****************************
                         ****************************
                          */

  ?>


</body>
</html>