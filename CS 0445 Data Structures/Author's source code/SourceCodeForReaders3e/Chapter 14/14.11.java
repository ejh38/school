public boolean add(int newPosition, T newEntry) // OutOfMemoryError possible	                                                 {   boolean isSuccessful = true;   if ((newPosition >= 1) && (newPosition <= numberOfEntries + 1))    {	      Node newNode = new Node(newEntry);      if (newPosition == 1)                // case 1      {         newNode.setNextNode(firstNode);							         firstNode = newNode;      }      else									       // case 2: list is not empty      {                                    // and newPosition > 1         Node nodeBefore = getNodeAt(newPosition - 1);         Node nodeAfter = nodeBefore.getNextNode();         newNode.setNextNode(nodeAfter);         nodeBefore.setNextNode(newNode);      } // end if	         numberOfEntries++;   }   else      isSuccessful = false;         return isSuccessful;} // end add