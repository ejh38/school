private void rehash(){   TableEntry<K, V>[] oldTable = hashTable;   int oldSize = hashTable.length;   int newSize = getNextPrime(oldSize + oldSize);   hashTable = new TableEntry[newSize]; // increase size of array   numberOfEntries = 0; // reset number of dictionary entries, since                       // it will be incremented by add during rehash   locationsUsed = 0;   // rehash dictionary entries from old array to the new and bigger    // array; skip both null locations and removed entries   for (int index = 0; index < oldSize; index++)   {      if ( (oldTable[index] != null) && oldTable[index].isIn() )         add(oldTable[index].getKey(), oldTable[index].getValue());   } // end for} // end rehash