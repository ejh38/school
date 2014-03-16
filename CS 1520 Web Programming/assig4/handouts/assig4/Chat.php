<!DOCTYPE html>
<html>
<head>
<title>Chat with a Friend</title>
<script src="http://code.jquery.com/jquery-latest.js"></script>
<script type="text/javascript">
// CS 1520 Fall 2013 -- Simple JQuery script to do a VERY PRIMITIVE
// chat between two users.  See also:
//	getID.php - script to assign ids to users
//	processMessage.php - script to receive message from a user and put it
//		into the DB
//	getMessage.php - script to get message that were submitted and remove
//		them from the DB
//  setChat.php - script to set up the initial DB.  I do not log out users
//      so you need this script to reset things also.

    // Initially show the login div and hide the interactive div
    $(document).ready(function() {
       $("div#interactive").hide();
       $("div#login").show();
    });

    // Get the message from the input text element and submit it to the
    // server via ajax.  Receive an ack to make sure the message was
    // received.
    function sendMessage() 
    {
        var msg = $("input[name=message]").val();
        args = {"msg":msg, "sender":myID}; 
        $.post("processMessage.php", args,
            function (data) {
               var res = $(data).find("Result").text();
               if (res == "OK")
                  $("input[name=message]").val("");
               else
                  alert("Message not processed");
            }
        );  
    }

    // Connect to the server and obtain an id.  This id will then be used
    // for submitting and retrieving messages.  Once the id is received, hide 
    // the login div and show the div for submitting messages.  Finally, set
    // the timer to start checking for messages.
    function connectToServer() 
    {
        var myname = $("input[name=name]").val();
		var arg = {"name":myname};
        $.post("getID.php", arg,
            function (data) {
	       	   var res = $(data).find("Result").text();
               if (res == "Available")
               {
	         	  myID = $(data).find("myID").text();
                  yourID = $(data).find("yourID").text();
                  $("div#login").hide();
                  $("div#interactive").show();
                  document.title = "Chat Script for " + myname + " ID: " + myID;
                  t = setTimeout("checkForMessage()",500);
               }
               else
                  alert("Could not connect");
	    	}
        );  
    }

    // Check with the server for any messages using AJAX. If no messages are
    // present do nothing.  If one or more messages are present, append them
    // all to the text area.
    function checkForMessage()
    {
        var arg = {"req":myID};	
		$.post("getMessage.php", arg,
            function(data) {
               var flag = $(data).find("Result").text();
               if (flag == "Available")
               {
	           	   var msgs = $(data).find("message");
                   for (var i = 0; i < msgs.length; i++)
		  		   {
                       var sender = $(msgs[i]).find("sender").text();
                       var data = $(msgs[i]).find("contents").text();
                       var currText = sender + ": " + data; 
                       var textA = $("#canvas");
                       var oldText = textA.val();
                       textA.val(oldText + "\n" + currText);
                       // Command I found on the Web to scroll to the bottom
                       // of the textarea.
                       textA.scrollTop(textA[0].scrollHeight - textA.height());
                   }
               }
               t = setTimeout("checkForMessage()",1000);
            }
        );
    }
</script>
</head>
<body> 
<div id="interactive">
<h2>Primitive Chat 1.0 in Progress</h2>
Enter your message: <input type = "text" name = "message" size="60" value = "">
<input type = 'button' id="enter" value = "Enter" onclick = 'sendMessage()'><br/>
<textarea id = "canvas" rows="10" cols="70"></textarea>
</div>
<div id="login">
<h2>Welcome to Primitive Chat 1.0</h2>
Enter your name: <input type = "text" name = "name" value = "">
<input type = 'button' value = "Enter" onclick = 'connectToServer()'><br/>
</div>
<script type="text/javascript">
    var myID, yourID; 
    var t;
</script>
</body>
</html>
