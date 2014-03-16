<?php
	session_start();


	$type = $_SESSION['type'];

	include 'get-db.php';
	$db = getDB();

	
	$state = $_SESSION['S_ID'];
	$userEmail = $_SESSION['email'];

	$query = "select User_ID from Users where Email = '$userEmail'";
	$result = $db->query($query) or die ("Failed looking up that user_id " . $db->error);
	$result = $result->fetch_array();
	$userID = $result[0];

	$query = "select Correct_Word, Incorrect_Guesses, Guessed_Letters, Current_Word
									 from States where State_ID = '$state'";
	$result = $db->query($query) or die ("Failed looking up that maker_id " . $db->error);
	$result = $result->fetch_array();
	$correctWord = $result['Correct_Word'];
	$incorrectGuesses = $result['Incorrect_Guesses'];
	$guessedLetters = $result['Guessed_Letters'];
	$currentWord = $result['Current_Word'];

	$query = "select RoundsPlayed, RoundsWon
									 from Users where User_ID = '$userID'";
	$result = $db->query($query) or die ("Failed looking up that maker_id " . $db->error);
	$result = $result->fetch_array();
	$roundsPlayed = $result['RoundsPlayed'];
	$roundsWon = $result['RoundsWon'];

	header('Content-type: text/xml');
  echo "<?xml version='1.0' encoding='utf-8'?>";
  echo "<BigThing>";

	echo "<Guessed>".$guessedLetters."</Guessed>";
	echo "<Incorrect>".$incorrectGuesses."</Incorrect>";
	echo "<Current>".$currentWord."</Current>";
	echo "<Rounds>Rounds Played: ".$roundsPlayed."</Rounds>";
	echo "<Won>Rounds Won: ".$roundsWon."</Won>";

	
	if (strcmp($type, "MAKER") == 0) {
		echo "<Correct>".$correctWord."</Correct>";
	
	} else if (strcmp($type, "GUESSER") == 0) {

	}
	echo "</BigThing>";

?>