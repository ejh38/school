 	// Locates a given entry within this bag.	// Returns a reference to the node containing the entry, if located,	// or null otherwise.	private Node getReferenceTo(T anEntry)	{		boolean found = false;		Node currentNode = firstNode;				while (!found && (currentNode != null))		{			if (anEntry.equals(currentNode.data))				found = true;			else				currentNode = currentNode.next;		} // end while     		return currentNode;	} // end getReferenceTo	/** Removes one occurrence of a given entry from this bag, if possible.       @param anEntry  the entry to be removed       @return true if the removal was successful, or false otherwise */   public boolean remove(T anEntry) 	{		boolean result = false;      Node nodeN = getReferenceTo(anEntry);            if (nodeN != null)      {         nodeN.data = firstNode.data; // replace located entry with entry in first node                  remove();                    // remove first node         result = true;      } // end if         		return result;	} // end remove