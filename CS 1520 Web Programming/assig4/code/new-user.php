<?php
	session_start();
?>


<!DOCTYPE html>
<html>
	<head>
		<title>Making a new User</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<form action="new-user.php" 
      method="POST">

<?php
	
	$invalidUsername = "";

	if (isset($_POST['email']) && 
		(!isset($_POST['password']) || strcmp($_POST['password'], "") == 0)) {
		$invalidUsername = "<b>Please enter your password!</b><br \>";
	}
	else if ((!isset($_POST['email']) || strcmp($_POST['email'], "") == 0) &&
	 isset($_POST['password'])) {
		$invalidUsername = "<b>Please enter your email address!</b><br \>";
	}
	else if ((!isset($_POST['name']) || strcmp($_POST['name'], "") == 0) &&
	 isset($_POST['password'])) {
		$invalidUsername = "<b>Please enter your name!</b><br \>";
	}


	else if (isset($_POST['email']) && isset($_POST['password']) 
							&& strcmp($_POST['email'], "") != 0 && strcmp($_POST['password'], "") != 0
							&& isset($_POST['name']) && strcmp($_POST['name'], "") != 0) {
		
		include 'get-db.php';
  	$db = getDB();

  	// query to see if the email address is in there, and they are a maker
  	$query = "select * from Users where Email = '$_POST[email]'";
  	$result = $db->query($query) or die ("Failed looking up that email " . $db->error);
   	$result = $result->fetch_array();

   	// if we get a match (non-null result, then send the email and tell them)
   	if ($result != NULL) {
   		$invalidUsername = "<b>Sorry, someone already has that email address.</b><br \>";
   	}
   	else {
   		$_SESSION['name'] = $_POST['name'];
   		$_SESSION['email'] = $_POST['email'];
   		$_SESSION['password'] = $_POST['password'];
   		header("location: make-user.php"); 
   	}
		
	}
?>


<center>
	<h1> Glad you want to play! Enter your info below!</h1>
	<?php
		echo $invalidUsername;
	?>

	<label for = "email">Email Address:</label> <input type = "text" name = "email" id = "email" size = "50"> <br />	
	<label for = "name">Name:</label> <input type = "text" name = "name" id = "name" size = "30"> <br />
	<div class = "input_box"><label for = "pw">Password:</label> <input type = "password" id = "pw" name = "password" size = "16"> <br /></div>

  <input type = "submit" value = "Submit!">

</div>

</center>
</body>
</html>