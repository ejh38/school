<!DOCTYPE html>
<html>

<?php 

if (isset($_POST['submit']) && isset($_POST['name']) && strcmp($_POST['name'], "") != 0) {

	$fp = fopen("users.txt", "r+");
	$counter = 0;
	while (!flock($fp, LOCK_EX) && $counter < 100) {
		$counter++;
	}

	if ($counter < 100) {
		fseek($fp, -7, SEEK_END);
		fwrite($fp, "       ");
		fseek($fp, -7, SEEK_END);
		fwrite($fp, "$_POST[name]^");

		$firstTime = 1;
		foreach ($_POST as $key => $value) {
			if (strcmp(substr($key, 0, 8), "checkbox") == 0)  {
				if ($firstTime == 1) {
					fwrite($fp, substr($key, 8));	
					$firstTime = 0;
				}
				else {
					fwrite($fp, "|" . substr($key, 8));
				}
			}
		}

		if ($firstTime == 1) {
			fwrite($fp, "-1");
		}

		setcookie("name", $_COOKIE["name"]."~".$_POST['name'], time()+60*60*24*30);

		fwrite($fp, "\n");
	}
	flock($fp, LOCK_UN);
	fclose($fp);
}

else if (isset($_POST['new'])) { // button name
	$fp = fopen("users.txt", "a");

	while (!flock($fp, LOCK_EX) && $counter < 100) {
		$counter++;
	}

	if ($counter < 100) {
		fwrite($fp, "NEW^-1\n");
	}
	flock($fp, LOCK_UN);
	fclose($fp);
}

else {
	
	$submitEdit = 0;
	$userToEdit;
	$newName; 
	foreach ($_POST as $key => $value) {
		if ($_POST[$key] == 'Edit') {
			$userToEdit = $key;

			$fp = fopen("users.txt", "a");
			while (!flock($fp, LOCK_EX) && $counter < 100) {
				$counter++;
			}

			if ($counter < 100) {

				fwrite($fp, "EDIT:::" . $userToEdit . "\n");
			}
			flock($fp, LOCK_UN);
			fclose($fp);
		}
		if ($_POST[$key] == 'Submit Edit') {
			$submitEdit = 1;
			$userToEdit = $key;
			$newName = $userToEdit;

			if (isset($_POST['name'])) {
				$newName = $_POST['name'];
				setcookie("name", $_COOKIE["name"]."~".$_POST['name'], time()+60*60*24*30);
			}
		}
	}

	if ($submitEdit == 1) {
		$replaceString = $newName;
		$firstTime = 1;

		foreach ($_POST as $key => $value) {

			// make the replace string
			if (strcmp(substr($key, 0, 8), "checkbox") == 0)  {
				if ($firstTime == 1) {
					$replaceString .= "^". substr($key, 8);
					$firstTime = 0;
				}
				else if ($firstTime == 0) {
					$replaceString .= "|" . substr($key, 8);
				}
			}
		}

		if ($firstTime == 1) {
			$replaceString .= "^";
		}

		$fp = fopen("users.txt", "r");
		while (!flock($fp, LOCK_EX) && $counter < 100) {
			$counter++;
		}

		if ($counter < 100) {

			$ans = "";
			$pattern = '/' . $userToEdit . '\^[\|0-9]*/';


			while (!feof($fp)) {
			  $line = fgets($fp);
			  if (strcmp(substr($line, 0, 4), "EDIT") != 0) { 
			  		echo $ans. "<br>";
				  $ans .= preg_replace($pattern, $replaceString, $line);
				}
			}
			fclose($fp);
			$fp = fopen("users.txt", "w");
			$retries = 0;
			fwrite($fp, $ans);
		}
		flock($fp, LOCK_UN);
		fclose($fp);

	}
}



header("Location: assig1.php");
?>

</html>