public Object clone(){   LList<T> theCopy = null;   try   {      theCopy = (LList<T>) super.clone();   }   catch (CloneNotSupportedException e)   {      throw new Error(e.toString());   }   // copy underlying chain of nodes   if (firstNode == null) // if chain is empty   {      theCopy.firstNode = null;   }   else   {      // make a copy of the first node      theCopy.firstNode = (Node)firstNode.clone();      // make a copy of the rest of chain      Node newRef = theCopy.firstNode;      Node oldRef = firstNode.getNextNode();      for (int count = 2; count <= numberOfEntries; count++)      {         // clone node and its data; link clone to new chain         newRef.setNextNode((Node)oldRef.clone());         newRef = newRef.getNextNode();         oldRef = oldRef.getNextNode();      } // end for   } // end if   return theCopy;} // end clone