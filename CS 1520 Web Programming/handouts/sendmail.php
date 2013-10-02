<!DOCTYPE html>
<html>
<head>
<title>Send Mail Results</title>
</head>
<body>
<?php
  # Always a good idea to strip the tags
  $sender = strip_tags($_POST["sender"]);
  $receiver = strip_tags($_POST["receiver"]);
  $subj = strip_tags($_POST["subject"]);
  $msg = strip_tags($_POST["msg"]);

  # Now we are verifying that the sender and receiver are both
  # somewhat valid.  We don't actually check to see if the ids
  # are valid, but we check the host to see if it is at least
  # a valid host.
 
  # Separate id from host by exploding on the @
  $sendarr = explode('@', $sender);
  $recarr = explode('@', $receiver);
  $sendhost = $sendarr[1];
  $rechost = $recarr[1];

  $valid = 1;
  # Use getmxrr to test to see if the host is valid
  # Look up getmxrr in the online PHP manual for more information
  # If getmxrr fails the host could still be valid -- we can use
  # gethostbyname to check.  gethostbyname returns the ip address of
  # the host or the original argument if the host is not found.  Thus,
  # if the value returned is the same as the parameter, the host was
  # not found.
  if (!getmxrr($sendhost, $mxhostsend))
  {
      if ($sendhost == gethostbyname($sendhost))
      {
          echo "<b>Sender's email address is invalid</b><br />";
          $valid = 0;
      }
  }
  if (!getmxrr($rechost, $mxhostrec))
  {
      if ($rechost == gethostbyname($rechost))
      {
          echo "<b>Receiver's email address is invalid</b><br />";
          $valid = 0;
      }
  }
  if ($valid)
  {
      $sendfield = "From: $sender";
      mail($receiver, $subj, $msg, $sendfield);
      echo "<br /><b>Mail sent to $receiver from $sender!</b><br />";
  }
  else
  {
      echo "<br /><b>Mail was NOT sent to $receiver from $sender!</b><br />";
  }
?>
</body>
</html>