<?php


function checkForOtherUser($userEmail) {

	$db = getDB();

	$query = "select User_ID from Users where Email = '$userEmail'";
	$result = $db->query($query) or die ("Failed looking up that email " . $db->error);
	$result = $result->fetch_array();
	$userID = $result[0];

	while (1) {

		$query = "select U_ID from Users_States where U_ID = '$userID'";
		$result = $db->query($query) or die ("Failed looking up waiting user " . $db->error);
		$result = $result->fetch_array();

		// this means we're good
		if ($result != NULL) {
					return;
		}
	}
}


?>