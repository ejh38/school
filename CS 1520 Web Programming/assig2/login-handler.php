<?php
 session_start(); 
?>

<!DOCTYPE html>
<html>
	<head>
		<title>Maker Logged In!</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<center>
<form action="login-handler.php" 
      method="POST">

<?php
	$message = "";

	if (isset($_SESSION['maker'])) {
		$curr_maker = $_SESSION['maker'];
	}
	else {
		header("location: login.php");
	}

	if (isset($_POST['submit']) && isset($_POST['choice']) && strcmp($_POST['choice'], "") != 0) {
		if (strcmp($_POST['choice'], "create") == 0) {
			header("location: create-schedule.php");
		}
		else if (strcmp($_POST['choice'], "finalize") == 0) {
			header("location: finalize-schedule.php");
		}
		else if (strcmp($_POST['choice'], "logout") == 0) {
			unset($_SESSION['maker']);
			header("location: login.php");
		}
	}
	else if (isset($_POST['submit'])) {
		$message = "Please make a choice before clicking submit :D<br \>";
	}


	echo	"<h1>Welcome, <i>$curr_maker[Name]</i>, make a choice!</h1><br />";
	echo $message;
	?>
	<h4>
	<input type = "radio" name = "choice" value = "create">Create a Schedule!<br />
	<input type = "radio" name = "choice" value = "finalize">Finalize a Schedule!<br />
	<br />
	<input type = "radio" name = "choice" value = "logout">Log out :(<br />
	</h4>
	<input type = "submit" name = 'submit' value = "Submit!">


</center>
</body>
</html>