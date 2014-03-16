<?php
 session_start(); 
?>

<!DOCTYPE html>
<html>
	<head>
		<title>You clicked a link!</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<center>


	<?php
		date_default_timezone_set('America/New_York'); 
		// build up the schedule appropriately

	include 'get-db.php';
  $db = getDB();


  $query = "select 
  	Schedules.Name, Schedules_Timeslots.T_ID, Timeslots.Date, Users.User_ID, Users.Name 
  	from 
  	Schedules, Schedules_Timeslots, Timeslots, Users, Users_Schedules
   	where
   	Schedules.Schedule_ID = '$_GET[schedule]' and
   	Schedules.Schedule_ID = Schedules_Timeslots.S_ID and
   	Schedules_Timeslots.T_ID = Timeslots.Timeslot_ID and
   	Users.User_ID = Users_Schedules.U_ID and
   	Users_Schedules.S_ID = '$_GET[schedule]' and
   	Users.Maker = 0
   	";

	$result = $db->query($query) or die ("Schedule not found ");
	
	$tableArray = array("User", "Datetime", "Name");
	$counter = 0;

	while ($row = $result->fetch_row()) {
		$tableArray['Name'] = $row[0];
		$tableArray['User'][$counter/$_GET['timeslots']] = $row[4];
		$tableArray['Datetime'][$counter%$_GET['timeslots']] = $row[2];
		$_SESSION[$row[2]] = $row[1];
		$_SESSION[$row[4]] = $row[3];
		$counter++;
	}
		echo "<h1>Welcome! Here's your schedule, pick which times work for you!</h1>";
		echo "<br \>";	

		?>
	<form action="user-submitted.php" 
      method="POST">

	<table border = "1">
  <caption> <?php echo $tableArray['Name']; ?> </caption>
  	<?php

  	echo "<th>Users</th>";
  	for ($i = 0; $i < count($tableArray['Datetime']); $i++) {
  		$temp = $tableArray['Datetime'][$i];
  		echo "<th>". date_format(new DateTime($temp), 'D, d/m/y \a\t g:i a'). "</th>";
  	}
  	

  	for ($i = 1; $i < count($tableArray['User']) + 1; $i++) {
  		  echo "<tr align = center>";

  		for ($j = 0; $j < count($tableArray['Datetime']) + 1; $j++) {
  			if ($j == 0) {
  				echo "<td>" . $tableArray['User'][$i-1] ."</td>";
  			}
  			else if(strcmp($tableArray['User'][$i-1], $_GET['name']) == 0) {
  				// if its the guy
  				$temps = $tableArray['Datetime'][$j-1];
  				echo "<td>".
           "<p><input name=\"$temps\" type=\"checkbox\" /></p>".
       			"</td>";
  			}
  			else {
  				if (ischecked($_SESSION[$tableArray['Datetime'][$j-1]], 
  								$_SESSION[$tableArray['User'][$i-1]] )) {
  					echo "<td>&#x2717;</td>";
  				}
  				else {
  					echo "<td></td>";
  				}
  			}
  		}
  		echo "</tr>";
  	}


function ischecked($TID, $UID) {
  $db = getDB();

	$query = "select 
  	* 
  	from 
  	Users_Timeslots
  	where
   	Users_Timeslots.U_ID = $UID and
   	Users_Timeslots.T_ID = $TID
   	";

	$result = $db->query($query) or die ("Schedule not found ");
	return ($result->num_rows > 0);
}


	
	$tables = array("Users"=>array("User_ID", "Name", "Email", "Maker", "Password"),
		"Schedules"=>array("Schedule_ID", "Name"),
		"Timeslots"=>array("Timeslot_ID", "Date"),
		"Schedules_Timeslots"=>array("ST_ID", "S_ID", "T_ID"),
		"Users_Schedules"=>array("US_ID", "U_ID", "S_ID"),
		"Users_Timeslots"=>array("UT_ID", "U_ID", "T_ID")
		);
	     
	        foreach ($tables as $curr_table=>$curr_keys):
	           $query = "select * from " . $curr_table; #Define query
	           $result = $db->query($query);  #Eval and store result
	           $rows = $result->num_rows; #Det. num. of rows
	           $keys = $curr_keys;
	  ?>
	        <table border = "1">
	        <caption> <?php echo $curr_table; ?> </caption>
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
	



	?>
</table>

<br \><br \><input type = "submit" name = "<?php echo $_GET['name']; ?>" value = "Submit!">


</form>


</center>
	</body>
	</html>