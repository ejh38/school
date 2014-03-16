<?php
 session_start(); 
?>


<?php
   // CS 1520
   // Simple script to retrieve a random word from the database as a
   // JSON object and return it to the requestor.  You may want to use this
   // or something like it for Assignment 4
   include 'get-db.php';
   $db = getDB();

   $query = "update Users 
            SET RoundsPlayed='$_POST[roundsPlayed]', RoundsWon='$_POST[roundsWon]'
            where Email ='$_POST[email]'";
   $result = $db->prepare($query);
   $result->execute();
?>
