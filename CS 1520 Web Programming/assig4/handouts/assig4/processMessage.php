<?php
// CS 1520 Fall 2013
// Script to add a message to the Chat DB
// This will insert a message into the DB and then send an ack back
// to the client that submitted it.

   $passlist = file("password.php");
   $passwd = rtrim($passlist[1]);
   $passwd = preg_replace('/#/','',$passwd);
   $db = new mysqli('localhost', 'nomad', "$passwd", 'nomad');
   if ($db->connect_error):
     die ("Could not connect to db " . $db->connect_error);
   endif;

   header('Content-type: text/xml');
   echo "<?xml version='1.0' encoding='utf-8'?>";
   echo "<SubmitResult>";
      
   // Get necessary IDs
   $sendID = $_POST["sender"];
   if ($sendID == 1)
       $otherID = 2;
   else
       $otherID = 1;
   $msg = $_POST["msg"];
   $query = "insert into Messages values ('$otherID' , '$sendID', '$msg')";
   $result = $db->query($query);
   if ($result)
   {
      echo "<Result>OK</Result>";
   }
   else
   {
      echo "<Result>Error</Result>";
   }
   echo "</SubmitResult>";
?>
