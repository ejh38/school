<?php
//  CS 1520 JQuery Primitive Chat Example
//  Script to process user logins
//  As with several of these other scripts, it would be better to lock tables
//  between the "read" and "write" of the table to make sure the tables stay
//  consistent.

   $passlist = file("password.php");
   $passwd = rtrim($passlist[1]);
   $passwd = preg_replace('/#/','',$passwd);
   $db = new mysqli('localhost', 'nomad', "$passwd", 'nomad');
   if ($db->connect_error):
     die ("Could not connect to db " . $db->connect_error);
   endif;

   // Set header for xml document and add root tag
   header('Content-type: text/xml');
   echo "<?xml version='1.0' encoding='utf-8'?>";
   echo "<IDResponse>";
      
   // Select NULL Chatters
   $query = "select * from Chatters where Chat_Name IS NULL order by Chat_ID"; 
   $result = $db->query($query);
   $rows = $result->num_rows;
   // Both slots are taken, return unavailable
   if ($rows == 0)
   {
      echo "<Result>Unavailable</Result>";
   }
   else
   {
      echo "<Result>Available</Result>";
      $row = $result->fetch_array();
      $id = $row["Chat_ID"];
      $myName = $_POST["name"];
      if ($id == 1)  // First NULL slot is id 1 - this is the first user
      {
          echo "<myID>1</myID>";
          echo "<yourID>2</yourID>";
      }
      else  // This is the second user
      {
          echo "<myID>2</myID>";
          echo "<yourID>1</yourID>";
      }
      $query = "update Chatters set Chat_Name = '$myName' where Chat_ID = '$id'";
      $result = $db->query($query);
   }
   echo "</IDResponse>";
?>
