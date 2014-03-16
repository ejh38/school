<?php

session_start();

include 'get-db.php';
$db = getDB();

$state = $_SESSION['S_ID'];

$query = "select Correct_Word, Current_Word, Incorrect_Guesses, Maker_ID, Guesser_ID
									 from States where State_ID = '$state'";
$result = $db->query($query) or die ("Failed looking up that maker_id " . $db->error);
$result = $result->fetch_array();
$correctWord = $result['Correct_Word'];
$incorrect = $result['Incorrect_Guesses'];
$current = $result['Current_Word'];
$maker = $result['Maker_ID'];
$guesser = $result['Guesser_ID'];


// start as won
$flag = 1;

for ($i = 0; $i < strlen($correctWord); $i++) {
	if ($correctWord[$i] != $current[$i*2 + 1]) {
		$flag = 0;	// not won yet
		break;
	}
}

if ($incorrect >= 7) {
	$flag = -1;	// game over, you lost
}

if ($flag == 0) {
	return;
}

$query = "select RoundsPlayed, RoundsWon from Users where User_ID = '$guesser'";
$result = $db->query($query) or die ("Failed looking up that guesser " . $db->error);
$result = $result->fetch_array();
$guessPlayed = $result['RoundsPlayed'];
$guessWon = $result['RoundsWon'];

$query = "select RoundsPlayed, RoundsWon from Users where User_ID = '$maker'";
$result = $db->query($query) or die ("Failed looking up that maker " . $db->error);
$result = $result->fetch_array();
$makerPlayed = $result['RoundsPlayed'];
$makerWon = $result['RoundsWon'];

$guessPlayed++;
$makerPlayed++;


if ($flag == 1) {
	// you win
	// game is over
	$guessWon++;
}
else {
	$makerWon++;
}


	$query = "update Users 
						SET RoundsPlayed = '$guessPlayed', RoundsWon = '$guessWon'
						where User_ID = '$guesser'";
	$result = $db->query($query) or die ("Failed updating up that guesser " . $db->error);
	
	$query = "update Users 
						SET RoundsPlayed = '$makerPlayed', RoundsWon = '$makerWon'
						where User_ID = '$maker'";
	$result = $db->query($query) or die ("Failed updating up that maker " . $db->error);
	
	$query = "update States 
						SET Guesser_ID = '$maker', Maker_ID = '$guesser',
								Correct_Word = 0, Incorrect_Guesses = 0, Guessed_Letters = ' ',
								Current_Word = '' 
						where State_ID = '$state'";
	$result = $db->query($query) or die ("Failed updating state " . $db->error);

?>