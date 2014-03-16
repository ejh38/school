<!DOCTYPE html>
<html>
	<head>
		<title>Password Reminder</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>

<?php

	// If there are no post variables set, then display the first message
	if (!(isset($_POST['submit']) && isset($_POST['email']) && strcmp($_POST['email'], "") != 0)) {
	?>

	Relax man, we'll find your password.<br \>
	Just give me your email and I'll send you your password in plaintext. That's secure, right?
	<br \>
	<br \>
	<br \>

	<center>
	<form action="forgot-password.php" 
	  method="POST">
	Email Address: <input type = "text" name = "email" size = "30"> <br />
	<input type = "submit" name = 'submit' value = "Submit!">
	</center>

<?php
	}

	// otherwise we've submited an email address
	else {
		// so setup the database object
		include 'get-db.php';
  	$db = getDB();

  	// query to see if the email is in there, and they are a maker
  	$query = "select Password, Name from Users where Email = '$_POST[email]'";
  	$result = $db->query($query) or die ("Failed looking up that email " . $db->error);
   	$result = $result->fetch_array();

   	// if we get a match (non-null result, then send the email and tell them)
   	if ($result != NULL) {
			mail("$_POST[email]", "Forgotten Password", "Hey $result[1], your password is $result[0]!");
	
			echo "<center><br \><br \>Email sent! Please check your email for the password, then try"
			?>
			<a href = "login.php">logging in again</a>.
			</center>
			<?php

   	}
   	// otherwise tell them twe didn't find the email, but they can try again
   	else {
			echo "<center><br \><br \>Sorry, but <b>$_POST[email]</b> wasn't found in the system."
				. "<br \><br \>You entered your email incorrectly :\<br \>"
 				. "<a href = \"forgot-password.php\">Try again?</a></center>";
   	}
	}
?>

</body>
</html>