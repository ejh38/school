<?php

	function waitingQueue($userEmail) {
		$db = getDB();

		$query = "select User_ID from Users where Email = '$userEmail'";
		$result = $db->query($query) or die ("Failed looking up that email " . $db->error);
		$result = $result->fetch_array();
		$userID = $result[0];

		$query = "select * from WaitingUser";
		$result = $db->query($query) or die ("Failed looking up waiting user " . $db->error);
		$result = $result->fetch_array();

		// if we don't get a match, then noone else is already in the queue
		if ($result == NULL) {
			// so insert ourselves
			$query = "insert into WaitingUser values ('0', '$userID')";
    	$result = $db->query($query) or die ("Invalid insert " . $db->error);
    	return 0;
		}
		else {
			// otherwise we need to make a new game with us two 
			$oldID = $result['U_ID'];
			if ($oldID == $userID) {
				// something got kinda messed up, so just return without adjusting the table
				return 0;
			}
			else {
				// it really is someone else
				
				// so check out the current games
				$query = "select State_ID from States";
    		$result = $db->query($query) or die ("Invalid select " . $db->error);
    		$maxSID = $result->num_rows;

    		// and insert this one in
				$query = "insert into States values ('$maxSID', '$userID', '$oldID',
																				'', 0, '', '')";
		    $result = $db->query($query) or die ("Invalid insert " . $db->error);

		    // do the same for Users_States
		    // so check out the current 
				$query = "select US_ID from Users_States";
    		$result = $db->query($query) or die ("Invalid select " . $db->error);
    		$maxUSID = $result->num_rows;

				$query = "insert into Users_States values ('$maxUSID', '$oldID', '$maxSID')";
		    $result = $db->query($query) or die ("Invalid insert " . $db->error);

		    $maxUSID++;
				$query = "insert into Users_States values ('$maxUSID', '$userID', '$maxSID')";
		    $result = $db->query($query) or die ("Invalid insert " . $db->error);


		    // remove the old user from the queue
		    $query = "delete from WaitingUser";
		    $result = $db->query($query) or die ("Invalid delete " . $db->error);

		    return 1;
			}

		}
	}