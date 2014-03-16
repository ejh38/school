<?php

session_start();

include 'get-db.php';
$db = getDB();

$word = $_POST['word'];
$currWord = " ";
for ($i = 0; $i < strlen($word); $i++) {
	$currWord = $currWord . "_ ";
}
$state = $_SESSION['S_ID'];

$query = "UPDATE States
					SET Correct_Word = '$word', Incorrect_Guesses = '0',
							Current_Word = '$currWord', Guessed_Letters = ''
					WHERE State_ID = '$state'";
$result = $db->query($query) or die ("Failed looking up that maker_id " . $db->error);

?>