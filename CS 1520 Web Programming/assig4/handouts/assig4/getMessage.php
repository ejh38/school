<?php
//  CS 1520 Fall 2013
//  This script will retrieve all messages sent to the requestor and then
//  remove them from the DB.  If no messages are present send back an
//  "unavailable" message.

   $passlist = file("password.php");
   $passwd = rtrim($passlist[1]);
   $passwd = preg_replace('/#/','',$passwd);
   $db = new mysqli('localhost', 'nomad', "$passwd", 'nomad');
   if ($db->connect_error):
     die ("Could not connect to db " . $db->connect_error);
   endif;

   header('Content-type: text/xml');
   echo "<?xml version='1.0' encoding='utf-8'?>";
   echo "<MessageResult>";
      
   // Query all messages sent to requestor's id, also getting the name of the sender
   $reqID = $_POST["req"];
   $query = "select Messages.msg, Chatters.Chat_Name from Messages, Chatters where Messages.To_ID = '$reqID' and Messages.From_ID = Chatters.Chat_ID"; 
   $result = $db->query($query);
   $rows = $result->num_rows;

   // If no messages are there, indicate that.  Otherwise, put all messages
   // into an XML document, then delete them from the DB.  Note that to improve
   // this script we should lock the table before the initial select up until
   // the delete so that we do not delete any messages that are added between
   // the select and the delete.
   if ($rows == 0)
   {
      echo "<Result>Unavailable</Result>";
   }
   else
   {
      echo "<Result>Available</Result>";
      for ($i = 0; $i < $rows; $i++)
      {
          $row = $result->fetch_array();
          $sender = $row["Chat_Name"];
          $msg = $row["msg"];
          echo "<message>";
          echo "<sender>$sender</sender>";
          echo "<contents>$msg</contents>";
          echo "</message>";
      }
      if ($reqID == 1)
	  	  $sendID = 2;
      else
          $sendID = 1;
      $query = "delete from Messages where From_ID = '$sendID'";
      $result = $db->query($query);
   }
   echo "</MessageResult>";
?>
