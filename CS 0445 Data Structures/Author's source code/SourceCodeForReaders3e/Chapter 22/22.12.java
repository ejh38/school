public V remove(K key){   V removedValue = null;   int index = getHashIndex(key);   index = locate(index, key);   if (index != -1)   { // key found; flag entry as removed and return its value      removedValue = hashTable[index].getValue();      hashTable[index].setToRemoved();      numberOfEntries--;   } // end if   // else key not found; return null   return removedValue;} // end remove