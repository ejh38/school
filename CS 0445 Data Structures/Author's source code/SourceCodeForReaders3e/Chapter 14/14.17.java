public boolean replace(int givenPosition, T newEntry){   boolean isSuccessful = true;   if ((givenPosition >= 1) && (givenPosition <= numberOfEntries))   {         assert !isEmpty();      Node desiredNode = getNodeAt(givenPosition);      desiredNode.setData(newEntry);   }       else      isSuccessful = false;         return isSuccessful;} // end replace