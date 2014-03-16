<!DOCTYPE html>
<html>
 <head>
  <title>Initialize Game Assignment DB</title>
 </head>
 <body>
 <?php
      // CS 1520 Fall 2013
      // Script to set up simple game maintenance tables
      $passlist = file("password.php");
      $passwd = rtrim($passlist[1]);
      $passwd = preg_replace('/#/','',$passwd);
      $db = new mysqli('localhost', 'nomad', $passwd, 'nomad');
      if ($db->connect_error):
         die ("Could not connect to db: " . $db->connect_error);
      endif;

      // Table to store the status of each game, identified by an int id
      $db->query("drop table Games"); 

      // Table to store the player information
      $db->query("drop table Players");

      // Table to store assignments of players to games (2 players per game)
      $db->query("drop table Game_Assigs");

      // Table to store single value which is index of next game to be used
      $db->query("drop table Next_Game");

      // Create table for Games
      $result = $db->query(
                "create table Games (Game_ID int primary key not null, Game_Status int not null)") or die ("Invalid: " . $db->error);

      // Set some games to be available
      for ($i = 1; $i <= 3; $i++)
      {
          $query = "insert into Games values ('$i','0')";
          $db->query($query) or die ("Invalid insert " . $db->error);
      } 

      // Create table for Players
      $result = $db->query(
                "create table Players (Player_ID int primary key not null, Player_Name varchar(30) not null, Player_Pass varchar(64) not null)") or die ("Invalid: " . $db->error);
     
      // Read in some players from a file
      $players = file("players.txt");
      foreach ($players as $pstring)
      {
          $pstring = rtrim($pstring);
          $pl = preg_split("/ +/", $pstring);
          $query = "insert into Players values ('$pl[0]','$pl[1]','$pl[2]')";
          $db->query($query) or die ("Invalid insert " . $db->error);
      } 

      // Create table for game assignments, but leave it empty since no games
      // have been assigned yet.
      $result = $db->query(
                "create table Game_Assigs (G_ID int not null, P1_ID int, P2_ID int)") or die ("Invalid: " . $db->error);
      echo "<b>The database has been initialized with the following tables:</b>";
      // Create table for next game and set it to 0
      $result = $db->query(
                "create table Next_Game (Value int not null)") or die ("Invalid: " . $db->error);
      $query = "insert into Next_Game values ('1')";
      $db->query($query) or die ("Invalid insert " . $db->error);

      echo "<br /><br />";

      // Show the tables
      $tables = array("Games"=>array("Game_ID", "Game_Status"),
                      "Players"=>array("Player_ID","Player_Name","Player_Pass"),
                      "Game_Assigs"=>array("G_ID", "P1_ID", "P2_ID"),
		      		  "Next_Game"=>array("Value"));
      foreach ($tables as $curr_table=>$curr_keys):
         $query = "select * from " . $curr_table; 
         $result = $db->query($query); 
         $rows = $result->num_rows;
         $keys = $curr_keys;
?>
      <table border = "1">
      <caption><?php echo $curr_table;?></caption>
      <tr align = "center">
<?php
         foreach ($keys as $next_key):
             echo "<th>$next_key</th>";
         endforeach;
         echo "</tr>"; 
         for ($i = 0; $i < $rows; $i++):  #For each row in result table
             echo "<tr align = center>";
             $row = $result->fetch_array();  #Get next row
             foreach ($keys as $next_key)  #For each column in row
             {
                  echo "<td> $row[$next_key] </td>"; #Write data in col
             }
             echo "</tr>";
         endfor;
         echo "</table><br />";
      endforeach;
?>
 </body>
</html>
