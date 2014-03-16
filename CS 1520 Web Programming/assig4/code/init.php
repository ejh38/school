<?php

/* Simple script to setup the database by dropping the old tables,
 * Recreating the ones we'll use,
 * and initializing the Users table with info from the flat file.
 */ 


  // Get the password, then connect to the MySQL server
  include 'get-db.php';
  $db = getDB();
  
  // get rid of the Tables that are already there (if any)
  $db->query("drop table Users");
  $db->query("drop table States");
  $db->query("drop table WaitingUser");
  $db->query("drop table Users_States");


  // then start setting up the tables we'll use
  // this one is for users
  $result = $db->query(
    "create table Users (
        User_ID int primary key not null, 
        Name char(30) not null, 
        Email char(50) not null, 
        Password char(16) not null,
        RoundsPlayed int not null,
        RoundsWon int not null
      )")
  or die ("Invalid: " . $db->error);

  // this is for the game states, only one per game needed
  $result = $db->query(
    "create table States (
        State_ID int primary key not null, 
        Guesser_ID int not null, 
        Maker_ID int not null, 
        Correct_Word char(16) not null,
        Incorrect_Guesses int not null,
        Guessed_Letters char(26) not null,
        Current_Word char(32) not null
      )")
  or die ("Invalid: " . $db->error);

  // connects the Users and States tables
  $result = $db->query(
    "create table WaitingUser (
        WU_ID int primary key not null, 
        U_ID int not null
      )")
  or die ("Invalid: " . $db->error);

  // connects the Users and States tables
  $result = $db->query(
    "create table Users_States (
        US_ID int primary key not null, 
        U_ID int not null, 
        S_ID int not null
      )")
  or die ("Invalid: " . $db->error);

  // setup the initial Makers based on a flat file
  $users = file("Users.txt");
  $counter = -1;
  $superCounter = 0;
  $userInfo;
  foreach ($users as $temp) {
    $temp = rtrim($temp);
    
    if ($counter >= 0) {
      $userInfo[$counter] = $temp;    
    }
    if (strcmp($temp, '#') == 0 && $counter > 0) {
      $counter = 0;
      $query = "insert into Users values ('$superCounter', '$userInfo[0]', '$userInfo[1]', '$userInfo[2]', 0, 0)";
      $db->query($query) or die ("Invalid insert " . $db->error);
      $superCounter++;
    } 
    else {
      $counter++;
    }
  }  

?>


<!DOCTYPE html>
<html>
 <head>
  <title>Users Table Initialization</title>
 </head>
 <body>
  <h1>My Schema Looks like:</h1>

  <?php
                          /****************************
                           ****************************
                           *** Uncomment this to see **
                           *** the Users table that ***
                           *** comes from Users.flat **
                           ****************************
                           ****************************/


$tables = array("Users"=>array("User_ID", "Name", "Email", "Password", "RoundsPlayed", "RoundsWon"),
                  "States"=>array("State_ID", "Guesser_ID", "Maker_ID", "Correct_Word",
                                  "Incorrect_Guesses", "Guessed_Letters", "Current_Word"),
                  "Users_States"=>array("US_ID", "U_ID", "S_ID"),
                  "WaitingUser"=>array("WU_ID", "U_ID"));

        foreach ($tables as $curr_table=>$curr_keys):
           $query = "select * from " . $curr_table; #Define query
           $result = $db->query($query);  #Eval and store result
           $rows = $result->num_rows; #Det. num. of rows
           $keys = $curr_keys;
  ?>
        <table border = "1">
        <caption><?php echo $curr_table;?></caption>
        <tr align = center>
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
                        
                         /****************************
                         ****************************
                         *** Uncomment this to see **
                         *** the Users table that ***
                         *** comes from Users.flat **
                         ****************************
                         ****************************
                          */

  ?>

   <h1><b>The Users table was successfully setup!</b></h1>


   </body>
  </html>
  



