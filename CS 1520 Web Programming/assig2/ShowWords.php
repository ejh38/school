<!DOCTYPE html>
<html>
<head>
<title>List of Words Sent From Server</title>
<link rel = "stylesheet" type = "text/css" href = "wordStyle.css"/>
<script type="text/javascript">
// CS 1520 Summer 2012 
// Script to request a word from a wordserver.  The word is returned
// as a JSON object and then processed in the following way:
//	- If the word has been seen already, increment its count in the
//	  list and in the HTML table
//	- If the word has not yet been seen, add it to the list and to
//	  the HTML table.
// The words are stored in a simple array of Word objects.  A linear search
// done to find a given word [note: an object in Javascript can be used
// to make a hash -- to see more about this Google 'Javascript hash table'

    function requestWord() {
        var httpRequest;
        httpRequest = new XMLHttpRequest();
        if (!httpRequest) {
            alert('Giving up :(Cannot create an XMLHTTP instance');
            return false;
        }
 
        httpRequest.open('GET', 'getWord.php', true);
        httpRequest.setRequestHeader('Content-Type', 'text/xml');
        httpRequest.onreadystatechange = function() { updateList(httpRequest); };
        httpRequest.send(null);
    }

    function updateList(httpRequest)
    {
        if (httpRequest.readyState == 4)
        {
           if (httpRequest.status == 200)
           {
               var data = httpRequest.responseText;
               //alert(data);
               var wordData = JSON.parse(data);
               processWord(wordData.word);
           }
        }
    }

    // Search for the word in the word list.  If found, increment its
    // count and update the table.  If not found, add it to the list and
    // append a new row to the table.
    function processWord(word)
    {
        var found = 0;
        for (var i = 0; i < wordCount; i++)
        {
            if (theWords[i].word == word)
            {
                theWords[i].count++;
                updateWord(i);
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
           theWords[i] = new Word(word);
           addWord(i);
           wordCount++;
        }
    }

    // Make a new Word
    function Word(word)
    {
        this.word = word;
        this.count = 1;
    }
   
    function updateWord(index)
    {
        var T = document.getElementById("theTable");
        var R = T.rows[index];
        var C = R.cells;
        var oldChild = C[1].childNodes[0];
        var txt = document.createTextNode(theWords[index].count);
        C[1].replaceChild(txt, oldChild);
    }

    function addWord(index)
    {
        var T = document.getElementById("theTable");
        var R = T.insertRow(index);
        R.align = 'center';
        var C = R.insertCell(0);
        var txt = document.createTextNode(theWords[index].word);
        C.appendChild(txt);
        C = R.insertCell(1);
        var txt = document.createTextNode(theWords[index].count);
        C.appendChild(txt);
    }
</script>
</head>
<body> 
<center>
<table id = "theTable" border = "1" class="thetable">
</table>
<h2>
<input type = 'button' value = "Get Word" onclick = 'requestWord()'/>
</h2>
</center>
<script type="text/javascript">
    var theWords = new Array(), wordCount = 0, t;
</script>
</body>
</html>
