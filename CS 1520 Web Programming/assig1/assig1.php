<?php 

function __autoload($class) {
     require_once $class . '.php';
}

session_start();
date_default_timezone_set('America/New_York');
?>

<!DOCTYPE html>
<html>
<head>
  <title>CS 1520 Assignment 1 - Zach Sadler - zps6</title>
</head>

<body>

<?php
 /**********************
  * F U N C T I O N S *
  **********************/

// parse the filename given into an array
// by reading line by line, then double exploding as needed
function parseFile($fileName) {
  $key = 0;
  $buffer;
  while (!feof($fileName)) {
    $nextLine = fgets($fileName);

    if (!feof($fileName)) {
      $buffer[$key] = $nextLine;
      $buffer[$key] = explode("^", $buffer[$key]);
      if (isset($buffer[$key][1])) {
        $buffer[$key][1] = explode("|", $buffer[$key][1]);        
      }
      $key++;
    }
  }
  return $buffer;
}

function setupMeetingArray($scheduleBuffer) {
  $ans;

  $numDays = count($scheduleBuffer);

  $temp;
  for ($i = 0; $i < $numDays; $i++) {
    $temp[$i] = $scheduleBuffer[$i][1];
  }

  $tempnum = 0;
  for ($i = 0; $i < count($temp); $i++) {
    for ($j = 0; $j < count($temp[$i]); $j++) {
      $ans[$tempnum] = new Meeting($scheduleBuffer[$i][0], $temp[$i][$j]);
      $tempnum++;
    }
  }

  return $ans;
}

function setupUserArray($usersBuffer, $n, $meetingArray) {
  $ans;

  for ($i = 0; $i < $n; $i++) {
    $ans[$i] = new User($usersBuffer[$i], count($meetingArray));
  }

  return $ans;
}

function generateTable($meetingArray, $userArray) {
  $answer = "<table border=\"1\">";

  $numUsers = count($userArray);


  // set up a flag if we're adding a new user
  $addingNewUser = strcmp($userArray[$numUsers-1], "NEW") == 0;
  $editingUser = strncmp($userArray[$numUsers-1], "EDIT", 4) == 0;
  if ($addingNewUser || $editingUser) {
    $numUsers--;
  }

  $userToEdit = 0;
  if ($editingUser) {
    $userToEdit = substr($userArray[$numUsers], 7);
  }
  
  // we have number of rows equal to the number of users,
  // plus one for the meetings
  // plus one for the buttons
  // plus one for the totals
  for ($i = 0; $i < $numUsers + 3; $i++) {
    $answer .= "<tr>" . "<form action=\"action.php\" method=\"post\">";


    // first and second columns

    // first row
    if ($i == 0) {
      $answer .= "<td>User</td>"."<td>Action</td>";
    }
    // meat rows
    else if ($i > 0 && $i < $numUsers + 1) {

      if ($editingUser && $userToEdit == $i-1) {
        $answer .= makeTextField($userArray[$i-1]->getName());
      }
      else {
        $answer .= "<td>".$userArray[$i-1]->getName()."</td>";
      }

      if (isset($_COOKIE["name"])) {
        if (!$addingNewUser && in_array($userArray[$i-1]->getName(), explode('~', $_COOKIE["name"]))) {
          if ($userToEdit != $i-1) {
            $answer .= makeEditButton($i-1);
          }
          else {
            $answer .= makeSubmitEditButton($userArray[$i-1]->getName());
          }
        }
        else {
          $answer .= "<td> </td>";         
        }
      }
      else {
        $answer .= "<td> </td>";         

      }
    }
    // second to last row
    else if ($i == $numUsers + 1) {
      if ($editingUser) {
        $answer .= "<td>Finish editing</td>" . "<td>to continue</td>";
      }
      else if ($addingNewUser) {
        $answer .= makeTextField();
        $answer .= makeSubmitButton(count($meetingArray));
      }
      else {
        $answer .= "<td> </td>";
        $answer .= makeNewButton();
      }
    }
    // last row
    else {
      $answer .= "<td><b>Total</b></td>"."<td> </td>";
    }

    // the real meat of the columns
    for ($j = 0; $j < count($meetingArray); $j++) {
        
        // the first row of columns
        if ($i == 0) {
          $answer .= "<td>" . $meetingArray[$j] . "</td>";
        }

        // all the real meat of the table
        else if ($i < $numUsers + 1) {
          if ($editingUser && $userToEdit == $i-1) {
            $answer .= makeCheckboxes($j);
          }
          else if ($userArray[$i-1]->hasMeeting($j)) {
            $answer .= "<td>&#x2717;</td>";
          }
          else {
            $answer .= "<td></td>";
          }
        }

        // last two rows
        else if ($i == $numUsers + 1) {
          if ($addingNewUser) {
            $answer .= makeCheckboxes($j);
          }
          else {
            $answer .= "<td></td>";
          }
        }
        // last row - where the totals should be
        else {
          $total = 0;
          for ($k = 0; $k < $numUsers; $k++) {
            if ($userArray[$k]->hasMeeting($j)) {
              $total++;
            }
          }
         $answer .= "<td>" . $total . "</td>";
        }
      }
        $answer .= "</tr>" . "</form>";

  }
  
  return $answer;
}

function makeEditButton($a) {
  return "<td>".
           "<p><input name=\"$a\" type=\"submit\" value=\"Edit\" /></p>".
       "</td>";
}

function makeSubmitButton($a) {
  return "<td>".
           "<p><input name=\"submit\" type=\"submit\" value=\"Submit\" /></p>".
       "</td>";
}

function makeSubmitEditButton($a) {
  return "<td>".
           "<p><input name=\"$a\" type=\"submit\" value=\"Submit Edit\" /></p>".
       "</td>";
}

function makeNewButton() {
  return "<td>".
           "<p><input name=\"new\" type=\"submit\" value=\"New\" /></p>".
       "</td>";
}

function makeTextField() {
  return "<td>".
           "<p><input name=\"name\" type=\"text\" /></p>".
       "</td>";
}

function makeCheckboxes($a) {
  return "<td>".
           "<p><input name=\"checkbox$a\" type=\"checkbox\" /></p>".
       "</td>";
}

 /**********************
  * F U N C T I O N S *
  **********************/


 /**********************
  * T H E      M A I N *
  **********************/


$userArray;       // the array of Users we're currently working with
$meetingArray;    // the array of Meetings we're currently working with

// open the files
$scheduleFile = fopen("schedule.txt", "r+");
$usersFile = fopen("users.txt", "a+");

// read in the files
$scheduleText = parseFile($scheduleFile);
$usersText = parseFile($usersFile);

fclose($scheduleFile);
fclose($usersFile);


$meetingArray = setupMeetingArray($scheduleText);
$userArray = setupUserArray($usersText, count($usersText), $meetingArray);
// pad the users file with 0's where there is no meeting


echo generateTable($meetingArray, $userArray);

?>

</body>
</html>
