<?php
 session_start(); 
?>

<!DOCTYPE html>
<html>
	<head>
		<title>User submitted</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<center>

<?php
	include 'get-db.php';
  $db = getDB();

	$query = "select UT_ID from Users_Timeslots";
	$result = $db->query($query);
	$maxUTID = $result->num_rows;	

	end($_POST);
	$username = each($_POST);
	$username = str_replace('_', ' ', $username);

//	echo "$username[0] is ". $_SESSION[$username[0]];
	$usernum = $_SESSION[$username[0]];

	reset($_POST);

	for ($i = 0; $i < count($_POST) - 1; $i++) {
		$datetime = each($_POST);
		$datetime[0] = str_replace('_', ' ', $datetime[0]);
	//	echo "<br \>datetime is $datetime[0]<br \>";
		$timeslotnum = $_SESSION[$datetime[0]];

	//	echo "which corresponds to slot $timeslotnum";

		$query = "insert into Users_Timeslots values ('$maxUTID', $usernum,'$timeslotnum')";
		$db->query($query) or die ("Invalid insert " . $db->error);

		$maxUTID++;
	}
	


?>

<h1>Hooray! Your entry was added to the schedule!</h1>
<br \><br \>
<h3>Now kindly leave :D</h3>



</center>
</body>
</html>