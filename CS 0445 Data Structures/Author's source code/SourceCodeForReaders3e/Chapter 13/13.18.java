public void add(T newEntry){   list.add(newEntry);} // end addpublic boolean add(int newPosition, T newEntry){   boolean isSuccessful = true;   if ((newPosition >= 1) && (newPosition <= list.size() + 1))       list.add(newPosition - 1, newEntry);	    else      isSuccessful = false;         return isSuccessful;} // end add