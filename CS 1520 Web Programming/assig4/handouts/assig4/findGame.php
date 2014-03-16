<!DOCTYPE html>
<html>
<head>
<title>PHP Game Assignment Results</title>
</head>
<body>
<?php
   // CS 1520 Fall 2013
   // Script to assign players in pairs to "games".  In this case a new
   // page is returned with the assignment, but it could be modified to return
   // raw data for use with AJAX.  Also note that nothing is done here to
   // reset any of the data.  To do that you should run the setGame.php script.
   // No table locking is done here either, which probably should be done to ensure
   // that the DB stays consistent.
   $passlist = file("password.php");
   $passwd = rtrim($passlist[1]);
   $passwd = preg_replace('/#/','',$passwd);
   $db = new mysqli('localhost', 'nomad', "$passwd", 'nomad');
   if ($db->connect_error):
      die ("Could not connect to db " . $db->connect_error);
   endif;

   // Get and check the player name and password. Note that we are not handling
   // SQL Injection here and we probably should be doing that.
   $name = rtrim($_POST["name"]);
   $pass = rtrim($_POST["pass"]);
   $query = "select Player_ID from Players where Player_Name = '$name' and Player_Pass = '$pass'";
   $result =  $db->query($query) or die ("Invalid query" . $db->error);
   $rows = $result->num_rows;
   if ($rows < 1):
       echo "<br/><h3><center>You are not an authorized user!<br/>";
       echo "<a href = \"getGame.html\">Try Again</a></h3>";
       die("</body></html>");
   endif;
   $row = $result->fetch_array();
   $id = $row["Player_ID"];
   $query = "select G_ID from Game_Assigs where P1_ID='$id' or P2_ID='$id'";
   $result = $db->query($query) or die ("Invalid query" . $db->error);
   $rows = $result->num_rows;
   if ($rows == 1):
       $row = $result->fetch_array();
       $id = $row["G_ID"];
       echo "<h3>You are already in Game $id</h3>";
       die("</body></html>");
   endif;

   $query = "select Value from Next_Game";  // Get next game id
   $result = $db->query($query);
   $row = $result->fetch_array();
   $next_game = $row["Value"];  
   if ($next_game == -1):  // No games left
       echo "<br/><h3>There are no available games!  Sorry!<br/>";
       echo "<a href = \"getGame.html\">Try Again</a></h3>";
       die("</body></html>");
   endif;

   // Get the game assignments for the "next game"
   $query = "select P1_ID, P2_ID from Game_Assigs where Game_Assigs.G_ID = '$next_game'";
   $result =  $db->query($query) or die ("Invalid query" . $db->error);
   $rows = $result->num_rows;
   if ($rows == 0): // no assignments yet, so this player is the
                    // first player in the next game 
       $query = "insert into Game_Assigs values ('$next_game','$id', '0')";
       $result =  $db->query($query) or die ("Invalid query" . $db->error);
       $query = "update Games set Game_Status = '1' where Game_ID = '$next_game'";
       $result =  $db->query($query) or die ("Invalid query" . $db->error);
       echo "<h3>You are Player 1 in Game $next_game</h3>";
       die("</body></html>");
   endif;

  // This player is the second player in game
  $query = "update Game_Assigs set P2_ID = '$id' where G_ID = '$next_game'";
  $result =  $db->query($query) or die ("Invalid query" . $db->error);
  echo "<h3>You are Player 2 in Game $next_game</h3>";

  // Since this game is "full" we must move to the next available game
  // If no games are left, set Next_Game appropriately
  $query = "select Game_ID from Games where Game_Status = '0'";
  $result =  $db->query($query) or die ("Invalid query" . $db->error);
  $rows = $result->num_rows;
  if ($rows == 0): // No games remaining
       $query = "update Next_Game set Value = '-1'";
       $result =  $db->query($query) or die ("Invalid query" . $db->error);
  else:  // Get next available game id
       $row = $result->fetch_array();
       $next_game = $row["Game_ID"];
       $query = "update Next_Game set Value = '$next_game'";
       $result =  $db->query($query) or die ("Invalid query" . $db->error);
  endif;   
?>
</form>
</body>
</html>
