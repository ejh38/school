private int getHashIndex(K key){   int hashIndex = key.hashCode() % hashTable.length;   if (hashIndex < 0)      hashIndex = hashIndex + hashTable.length;       return hashIndex;} // end getHashIndex