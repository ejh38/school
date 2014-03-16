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

   $query = "select RoundsPlayed, RoundsWon from Users where Email = '$_SESSION[email]'";
   $result = $db->query($query);
   
   $rows = $result->num_rows;
   if ($rows >= 1):
      header('Content-type: application/json');
      $row = $result->fetch_array();
      $data["Rounds"] = $row["RoundsPlayed"];
      $data["Wins"] = $row["RoundsWon"];
      $data["Email"] = $_SESSION["email"];
      $ans = json_encode($data);
      echo "$ans";
   else:
      die ("DB Error");
   endif;
?>
