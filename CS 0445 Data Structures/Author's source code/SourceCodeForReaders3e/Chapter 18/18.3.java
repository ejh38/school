public boolean contains(T anEntry){   boolean found = false;   for (int index = 0; !found && (index < numberOfEntries); index++)   {      if (anEntry.equals(list[index]))         found = true;   } // end for   return found;} // end contains