<?php

session_start();

include 'get-db.php';
$db = getDB();

$letter = $_POST['letter'];

$query = "select Correct_Word, Guessed_Letters, Current_Word, Incorrect_Guesses
									 from States where State_ID = '$state'";
$result = $db->query($query) or die ("Failed looking up that maker_id " . $db->error);
$result = $result->fetch_array();
$correctWord = $result['Correct_Word'];
$guessed = $result['Guessed_Letters'];
$wrong = $result['Incorrect_Guesses'];
$current = $result['Current_Word'];

for ($i = 0; $i < strlen($guessed); $i++) {
	if (strcmp($guessed[$i], $letter) == 0)
		return;
}

if (strlen($letter) > 1) {
	return;
}

$guessed .= $letter;


// update the correct spots with your guess
$flag = -1;
for ($i = 0; $i < strlen($correctWord); $i++) {
	if (strcmp($correctWord[$i], $letter) == 0) {
		// we got a match
		$flag = 1;
		$current[$i*2 + 1] = $letter;
	}
}

// if you missed, increment wrong guesses
if ($flag == -1) {
	$wrong++;
}

$query = "UPDATE States
					SET Incorrect_Guesses = '$wrong',
							Current_Word = '$current', Guessed_Letters = '$guessed'
					WHERE State_ID = '$state'";
$result = $db->query($query) or die ("Failed looking up that maker_id " . $db->error);

?>