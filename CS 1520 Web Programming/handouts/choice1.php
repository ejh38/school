<?php
// Get name session variable to use for title
// Then show the weather channel page in an iframe.
// Then show two hyperlinks - one with an option set and one
// without.  If the one without is selected, the ex19.php script
// will prompt the user for a new name.  The other files choice2.php
// and choice3.php have similar logic.
session_start();
$name= $_SESSION["name"];
?>
<!DOCTYPE html>
<head>
<title><?php echo "Weather for $name";?></title>
</head>
<body>
<iframe src="http://www.weather.com" width="800" height="600"></iframe>
<br/>
<a href = "ex16.php?option=input">Make New Selection</a>
<br/>
<a href = "ex16.php">Change User</a>
</body>
</html>
