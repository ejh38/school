<?php

// This guy grabs our password, makes a new mysqli object, and returns it
function getDB() {
	$passlist = file("definitely-not-password-that-would-be-silly.php");
  $passwd = rtrim($passlist[1]);
  $passwd = preg_replace('/#/','',$passwd);
  $db = new mysqli('localhost', 'SadlerZ', $passwd, 'SadlerZ');
  if ($db->connect_error) {
     die ("Could not connect to db: " . $db->connect_error);
  }
  else {
	  return $db;
  }
}
?>