<?php
 session_start();
 include 'get-db.php'; 
?>

<!DOCTYPE html>
<html>
	<head>
		<title>Finalize a Schedule!</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<center>

	<h1>Lets finalize a schedule!</h1>
<form action="finalize-schedule.php" 
      method="POST">

<?php
	if (isset($_POST['submit']) && isset($_POST['choice'])) {
	 $db = getDB();

	 $query = "select Users_Timeslots.T_ID
	 					from 
	 					Schedules_Timeslots, Users_Schedules, Users_Timeslots
						where 
						Schedules_Timeslots.S_ID = $_POST[choice] and
						Users_Schedules.S_ID = $_POST[choice] and
						Users_Schedules.U_ID = Users_Timeslots.U_ID and
						Users_Timeslots.U_ID = Users_Timeslots.U_ID
						";

		$result = $db->query($query) or die ("Invalid select " . $db->error);

		print_r($result);


		$things[0] = 0;
		$things[1] = 0;

		for ($i = 0; $i < $result->num_rows; $i++) {
			$temp = $result->fetch_row();
			echo "<br \>row is ";
			print_r($temp);
			$things[$temp[0]]++;
		}
		$things[0] /= 2;
		$things[1] /= 2;

		print_r($things);
	}

	
?>




<?php
 $db = getDB();

//  print_r($_SESSION);

  $User_ID = $_SESSION['maker']['User_ID'];
  //echo "<br \>userid is $User_ID<br \>";

	$query = "select Users_Schedules.S_ID from Users_Schedules
						where 
						Users_Schedules.U_ID = $User_ID
						";

	$result = $db->query($query) or die ("Invalid select " . $db->error);

	echo "<br \><br \>";
//	print_r($result);
	for ($i = 0; $i < $result->num_rows; $i++) {
		$temp = $result->fetch_row();
		$schedulesToedit[$i] = $temp[0];
	}
	echo "<br \>";
	//print_r($schedulesToedit);

	for ($i = 0; $i < count($schedulesToedit); $i++) {
		echo "<input type = \"radio\" name = \"choice\" value = \"$schedulesToedit[$i]\">Finalize Schedule #$schedulesToedit[$i]!<br />";
	}


?>

	<br \>
	<input type = "submit" name = 'submit' value = "Submit!">

</form>
</center>
</body>
</html>