<?php 
	session_start();
	
	include 'get-db.php';
	$db = getDB();

	$userEmail = $_SESSION['email'];

	$query = "select User_ID from Users where Email = '$userEmail'";
	$result = $db->query($query) or die ("Failed looking up that user_id " . $db->error);
	$result = $result->fetch_array();
	$userID = $result[0];

	$query = "select S_ID from Users_States where U_ID = '$userID'";
	$result = $db->query($query) or die ("Failed looking up that s_id " . $db->error);
	$result = $result->fetch_array();
	$S_ID = $result['S_ID'];

	$query = "select Maker_ID, Guesser_ID from States where State_ID = '$S_ID'";
	$result = $db->query($query) or die ("Failed looking up that maker_id " . $db->error);
	$result = $result->fetch_array();
	$makerID = $result['Maker_ID'];
	$Guesser_ID = $result['Guesser_ID'];

	$_SESSION['S_ID'] = $S_ID;

	header('Content-type: text/xml');
  echo "<?xml version='1.0' encoding='utf-8'?>";
 	echo "<Type>";

	if ($makerID == $userID) {
		echo "MAKER";
		$_SESSION['type'] = "MAKER";
	}
	else if ($Guesser_ID == $userID) {
		echo "GUESSER";
		$_SESSION['type'] = "GUESSER";
	}

	echo "</Type>";

?>