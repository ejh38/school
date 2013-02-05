public V add(K key, V value){   V result = null;   int keyIndex = locateIndex(key);   if (keyIndex < numberOfEntries)   {      // key found; return and replace old value      result = dictionary[keyIndex].getValue();      dictionary[keyIndex].setValue(value);   }   else   {      ensureCapacity();      dictionary[numberOfEntries] = new Entry<K, V>(key, value);      numberOfEntries++;   } // end if   return result;} // end addprivate int locateIndex(K key){   int index = 0;   while ( (index < numberOfEntries) && !key.equals(dictionary[index].getKey()) )      index++;       return index;} // end locateIndex