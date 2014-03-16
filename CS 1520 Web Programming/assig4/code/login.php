<?php
 session_start(); 

 	if (isset($_POST['choice'])) {
	 	unset($_POST['choice']);
	}
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
  	$query = "select * from Users where Email = '$_POST[email]'
  								 AND Password = '$_POST[password]'";
  	$result = $db->query($query) or die ("Failed looking up that email " . $db->error);
   	$result = $result->fetch_array();

   	// if we get a match (non-null result, then send the email and tell them)
   	if ($result != NULL) {
   		$_SESSION['email'] = $_POST["email"];

   		// see if there is another waiting user
   		include 'user-queue.php';
   		if (waitingQueue($_POST["email"]) == 1) {
   			header("location: hangman.html"); 
   		}
   		else {
   	
				include 'wait-loop.php';
 				$ans = checkForOtherUser($_POST["email"]);
 				header("location: hangman.html");
 	 		}


   	}
   	else {
   		$invalidUsername = "<b>Sorry, invalid username & password combination.</b><br \>";
   	}
		
	}
?>

<!DOCTYPE html>
<html>
	<head>
		<link rel = "stylesheet" type = "text/css" href = "such-style.css"/>
		<title>HANGMAN!!!!! Login Page</title>
	</head>
<body>
<form action="login.php" 
      method="POST">


<center>
	<h1> Holy moley, time to login dude</h1><br>
	<h2> Please note, if you appear to stall after logging in, it's just waiting for another user.</h2>

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
	<a href = "forgot-password.php">Forgot your password?</a><br \>
	<a href = "new-user.php">Make a new account!</a>
</div>

</center>





</body>
</html>

