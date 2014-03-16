<?php
   // CS 1520
   // Simple script to retrieve a random word from the database as a
   // JSON object and return it to the requestor.  You may want to use this
   // or something like it for Assignment 4
   $passlist = file("password.php");
   $passwd = rtrim($passlist[1]);
   $passwd = preg_replace('/#/','',$passwd);
   $db = mysql_connect('localhost', 'nomad', "$passwd");
   if ($db):
      mysql_select_db('nomad');
   else:
      die ("Could not connect to db " . mysql_error());
   endif;
   $query = "select word from Words order by rand() limit 1";
   $result = mysql_query($query);
   $rows = mysql_num_rows($result);
   if ($rows >= 1):
      header('Content-type: application/json');
      $row = mysql_fetch_array($result);
      $data["word"] = $row["word"];
      $ans = json_encode($data);
      echo "$ans";
   else:
      die ("DB Error");
   endif;
?>
