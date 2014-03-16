<!DOCTYPE html>
<html>
 <head>
  <title>Set up Simple DB for 2-person chat</title>
 </head>
 <body>
 <?php
      // CS 1520 Fall 2013
      // Script to set up some simple tables for a 2-person chat session
      $passlist = file("password.php");
      $passwd = rtrim($passlist[1]);
      $passwd = preg_replace('/#/','',$passwd);
      $db = new mysqli('localhost', 'nomad', $passwd, 'nomad');
      if ($db->connect_error):
         die ("Could not connect to db: " . $db->connect_error);
      endif;

      $db->query("drop table Chatters"); 
      $db->query("drop table Messages");

	  // Chatters table has an id for the user and an int for the key
      $result = $db->query(
                "create table Chatters (Chat_ID int primary key not null, Chat_Name varchar(30))") or die ("Invalid: " . $db->error);

      for ($i = 1; $i <= 2; $i++)
      {
          $query = "insert into Chatters values ('$i', NULL)";
          $db->query($query) or die ("Invalid insert " . $db->error);
      } 

	  // Messages has fields for "to", "from" and the message itself.  Initially this
	  // table will be empty - it is filled an emptied by the Chatters during a chat
	  // session.
      $result = $db->query(
                "create table Messages (To_ID int, From_ID int, msg varchar(256))") or die ("Invalid: " . $db->error);

      $tables = array("Chatters"=>array("Chat_ID", "Chat_Name"),
                      "Messages"=>array("To_ID","From_ID","msg"));
      foreach ($tables as $curr_table=>$curr_keys):
         $query = "select * from " . $curr_table; #Define query
         $result = $db->query($query);  #Eval and store result
         $rows = $result->num_rows; #Det. num. of rows
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
