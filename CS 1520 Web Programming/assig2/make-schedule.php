<?php
 session_start(); 
?>

<!DOCTYPE html>
<html>
	<head>
		<title>(Actually) Make a Schedule!</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<center>

<h1>Awww man, we're making <i>
	<?php
		echo $_SESSION['scheduleName'];
	?>
</i>!</h1>

<?php 
	if (isset($_POST['submit'])) {
		// Start by inserting all of the users into the Users table
		include 'get-db.php';
  	$db = getDB();

  	// find the largest primary key up to this point
  	$query = "select User_ID from Users";
  	$result = $db->query($query);
  	$maxUID = $result->num_rows;

		$query = "select ST_ID from Schedules_Timeslots";
		$result = $db->query($query);
  	$maxSTID = $result->num_rows;

		$query = "select US_ID from Users_Schedules";
		$result = $db->query($query);
  	$maxUSID = $result->num_rows;

		$query = "insert into Users_Schedules values ('$maxUSID', '$_SESSION[User_ID]', '$_SESSION[SID]')";
    $result = $db->query($query) or die ("Invalid insert " . $db->error);
    $maxUSID++;
	    
  	
  	for ($i = 0; $i < $_SESSION['numUsers']; $i++) {

  		$tempname = "name".$i;
  		$tempemail = "email".$i;
	  	$query = "insert into Users values ('$maxUID', '$_POST[$tempname]', '$_POST[$tempemail]', 
	                                          '0', '')";
	    $result = $db->query($query) or die ("Invalid insert " . $db->error);
	    

			$query = "insert into Users_Schedules values ('$maxUSID', '$maxUID', '$_SESSION[SID]')";
	    $result = $db->query($query) or die ("Invalid insert " . $db->error);
	    $maxUSID++;
	    $maxUID++;


	    $bettername = str_replace(" ", "%20", $_POST[$tempname]);

	    mail("$_POST[$tempemail]", "Hey $_POST[$tempname], you got a schedule!", 
	    	"Nice to talk to you $_POST[$tempname]!\n"
	     ."You got a link to a new schedule. Go ahead and follow it here:\n"
."http://cs1520.cs.pitt.edu/~zps6/assig2/user-link.php?name=$bettername&schedule=$_SESSION[SID]&timeslots=$_SESSION[numTimes]");

  	}

  	$query = "select Timeslot_ID from Timeslots";
  	$result = $db->query($query);
  	$maxTID = $result->num_rows;
  	
  	for ($i = 0; $i < $_SESSION['numTimes']; $i++) {

  		$tempslot = "timeslot".$i;
	  	$query = "insert into Timeslots values ('$maxTID', '$_POST[$tempslot]')";
	    $result = $db->query($query) or die ("Invalid insert " . $db->error);
	    
	  	$query = "insert into Schedules_Timeslots values ('$maxSTID', '$_SESSION[SID]', '$maxTID')";
	    $result = $db->query($query) or die ("Invalid insert " . $db->error);
	    $maxSTID++;
	    $maxTID++;
 
  	}
  	header("location: success.php");
	}


?>



<form action="make-schedule.php" 
      method="POST">
<?php
	echo "So please enter your $_SESSION[numTimes] timeslots, as requested.<br \><br \>";
	for ($i = 0; $i < $_SESSION['numTimes']; $i++) {
		$j = $i + 1;
		echo "Date & Time #$j: <input type = \"datetime-local\" name = \"timeslot$i\"> <br \>";
	}
	echo "<br \><br \>";
	echo "And enter your $_SESSION[numUsers] users' names and emails, if you would.<br \><br \>";
	for ($i = 0; $i < $_SESSION['numUsers']; $i++) {
		$j = $i + 1;
		echo "User #$j's Name: <input type = \"text\" name = \"name$i\" size = 30>";
		echo "User #$j's Email: <input type = \"text\" name = \"email$i\" size = 50> <br \>";
	}

?>
<br \>
<br \>
  <input type = "submit" value = "Submit!" name = "submit">



</center>
</body>
</html>