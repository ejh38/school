public V add(K key, V value){   V oldValue; // value to return   if (isHashTableTooFull())      rehash();       int index = getHashIndex(key);   index = probe(index, key); // check for and resolve collision   // Assertion: index is within legal range for hashTable   assert (index >= 0) && (index < hashTable.length);   if ( (hashTable[index] == null) || hashTable[index].isRemoved())   { // key not found, so insert new entry      hashTable[index] = new TableEntry<K, V>(key, value);      numberOfEntries++;      locationsUsed++;      oldValue = null;   }   else   { // key found; get old value for return and then replace it      oldValue = hashTable[index].getValue();      hashTable[index].setValue(value);   } // end if   return oldValue;} // end add