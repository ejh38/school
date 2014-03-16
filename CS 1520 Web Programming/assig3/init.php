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
  $db->query("drop table Words");


  // then start setting up the tables we'll use
  // this one is for makers & users
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


  // this one is for schedules
  $result = $db->query(
    "create table Words (
      Word_ID int primary key not null, 
      Word char(5) not null
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


  $words = file("words5.txt");
  $superCounter = 0;
  foreach ($words as $temp) {
    $word = rtrim($temp);
    $query = "insert into Words values ('$superCounter', '$word')";
    $db->query($query) or die ("Invalid insert " . $db->error);
    $superCounter++;
  } 


/* JULIE MASTER PLAN OP STATUS SWAG

***CHECK*** Get the database initialized,
***CHECK*** get the login working (from assig2)
***CHECK*** get the new user working (see assig1)
***CHECK*** get the 'home page' working (see assig2)
***CHECK*** get the 'get word' function working (see his handouts getWord setWord)
get lingo going
get money
get paid
get shellis

*/
?>


<!DOCTYPE html>
<html>
 <head>
  <title>Users Table Initialization</title>
 </head>
 <body>

  <?php
                          /****************************
                           ****************************
                           *** Uncomment this to see **
                           *** the Users table that ***
                           *** comes from Users.flat **
                           ****************************
                           ****************************

  $tables = array("Users"=>array("User_ID", "Name", "Email", "Password", "RoundsPlayed", "RoundsWon"),
                  "Words"=>array("Word_ID", "Word"));
     
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
                        
                         ****************************
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
  



