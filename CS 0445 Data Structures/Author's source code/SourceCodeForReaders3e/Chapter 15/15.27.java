public T next(){   if (hasNext())   {      wasNextCalled = true;      T nextEntry = list[nextIndex];      nextIndex++; // advance iterator      return nextEntry;   }   else      throw new NoSuchElementException("Illegal call to next();" +                                       "iterator is after end of list.");} // end next