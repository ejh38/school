<?php
 session_start(); 
?>

<!DOCTYPE html>
<html>
	<head>
		<title>Make a Schedule!</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<center>

<?php
	$errorMessage = "";
	if (isset($_POST['name']) && isset($_POST['numUsers']) &&
		(!isset($_POST['numTimes']) || strcmp($_POST['numTimes'], "") == 0)) {
		$errorMessage = "<b>Please enter the number of timeslots!</b><br \>";
	}
	else if ((!isset($_POST['name']) || strcmp($_POST['name'], "") == 0) &&
	 isset($_POST['numTimes']) && isset($_POST['numUsers'])) {
		$errorMessage = "<b>Please enter the name of the schedule!</b><br \>";
	}
	else if ((!isset($_POST['numUsers']) || strcmp($_POST['numUsers'], "") == 0) &&
	 isset($_POST['numTimes']) && isset($_POST['name'])) {
		$errorMessage = "<b>Please enter the number of users!</b><br \>";
	}


	else if (isset($_POST['name']) && isset($_POST['numTimes']) 
							&& strcmp($_POST['name'], "") != 0 && strcmp($_POST['numTimes'], "") != 0) {
		$_SESSION['scheduleName'] = $_POST['name'];
		$_SESSION['numTimes'] = $_POST['numTimes'];
		$_SESSION['numUsers'] = $_POST['numUsers'];


		include 'get-db.php';
  	$db = getDB();

  	$query = "select Schedule_ID from Schedules";
  	$result = $db->query($query);
  	$maxSID = $result->num_rows;

  	$_SESSION['SID'] = $maxSID;

  	$query = "insert into Schedules values ('$maxSID', '$_SESSION[scheduleName]')";
	  $result = $db->query($query) or die ("Invalid insert " . $db->error);
	    

		header("location: make-schedule.php");
	}
?>


	<h1>Time to make your schedule! Wooooh!</h1>
	<br />
	So here's the deal: enter the name of the schedule, how many timeslots you're going to want to fill in, and how many users you'll add to the schedule, then we'll take it from there!
	<br />	
	<br />
	<form action="create-schedule.php" 
	  method="POST">
	<?php
	 	echo $errorMessage;
	?>
	Schedule Name: <input type = "text" name = "name" size = "30"> <br />
	Number of Timeslots: <input type = "text" name = "numTimes" size = "5"><br />
	Number of Users: <input type = "text" name = "numUsers" size = "5"><br />
	<input type = "submit" name = 'submit' value = "Submit!">
	</center>


</center>
</body>
</html>