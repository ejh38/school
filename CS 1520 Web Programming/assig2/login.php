<?php
 session_start(); 
?>

<!DOCTYPE html>
<html>
	<head>
		<title>Schedule Maker Login Page</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>
<form action="login.php" 
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
	else if (isset($_POST['email']) && isset($_POST['password']) 
							&& strcmp($_POST['email'], "") != 0 && strcmp($_POST['password'], "") != 0) {
		
		include 'get-db.php';
  	$db = getDB();

  	// query to see if the email address is in there, and they are a maker
  	$query = "select * from Users where Email = '$_POST[email]' AND Maker = 1
  								 AND Password = '$_POST[password]'";
  	$result = $db->query($query) or die ("Failed looking up that email " . $db->error);
   	$result = $result->fetch_array();

   	// if we get a match (non-null result, then send the email and tell them)
   	if ($result != NULL) {
   		$_SESSION['maker'] = $result;
   		print_r($_SESSION['maker']);
   		header("location: login-handler.php"); 
   	}
   	else {
   		$invalidUsername = "<b>Sorry, invalid username & password combination.</b><br \>";
   	}
		
	}
?>


<center>
	<h1> Holy moley, time to login dude</h1>

<div class = "container">
	<?php
		echo $invalidUsername;
	?>
	<div class = "input_box"><label for = "email">Email Address:</label> <input type = "text" name = "email" id = "email" size = "30"> <br /></div>
  
	<div class = "input_box"><label for = "pw">Password:</label> <input type = "password" id = "pw" name = "password" size = "30"> <br /></div>
  <input type = "submit" value = "Submit!">
</div>
<br />
<br />
<div class = "forgot">
	<a href = "forgot-password.php">Forgot your password?</a>
</div>

</center>





</body>
</html>

