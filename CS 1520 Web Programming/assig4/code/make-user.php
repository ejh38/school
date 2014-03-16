<?php
	session_start();
?>
<!DOCTYPE html>
<html>
	<head>
		<title>Successfully Made User</title>
		<link rel="stylesheet" type="text/css" href="such-style.css">
	</head>
<body>

<center>
<h1>Congratulations, 
<?php
	echo " $_SESSION[name], ";
?>
you made an account!<br \><i>You're amazing!</i><br \><br \>

<?php
	
		include 'get-db.php';
  	$db = getDB();

  	$query = "select User_ID from Users";
		$result = $db->query($query);
  	$maxUID = $result->num_rows;

		$query = "insert into Users values ('$maxUID', '$_SESSION[name]', '$_SESSION[email]',
																				'$_SESSION[password]', 0, 0)";
    $result = $db->query($query) or die ("Invalid insert " . $db->error);

?>


<h4>
	<a href = "login.php">Go back to the login page</a>
</center>


</body>
</html>