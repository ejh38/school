<?php
   // CS 1520
   // Very simple script to initialize a MySQL table
   $passlist = file("password.php");
   $passwd = rtrim($passlist[1]);
   $passwd = preg_replace('/#/','',$passwd);
   $db = new mysqli('localhost', 'nomad', $passwd, 'nomad');
   if ($db->connect_error): 
       die ("Could not connect to db: " . $db->connect_error); 
   endif;
   $result = $db->query("drop table CD");
   $result = $db->query("create table CD (id int primary key not null, title char(30) not null, artist char(30))") or die ("Invalid: " . $db->error);
 
   $query = "insert into CD values (1, 'Version 2.0', 'Garbage')"; 
   $db->query($query) or die ("Invalid insert " . $db->error); 

   $query = "insert into CD values (2, 'Substance', 'Joy Division')";
   $db->query($query) or die ("Invalid insert " . $db->error); 

   $query = "insert into CD values (3, 'U2', 'Zooropa')"; 
   $db->query($query) or die ("Invalid insert " . $db->error);
?>
<html>
   <head>
       <title>Generating a Simple Table</title>
   </head>
   <body>
<?php
   echo "CDs should be set up properly";
?>
   </body>
</html> 
