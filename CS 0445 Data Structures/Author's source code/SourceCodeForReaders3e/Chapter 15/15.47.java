public int nextIndex(){   int result;   if (hasNext())      result = nextIndex;   else      result = numberOfEntries;       return result;} // end nextIndexpublic int previousIndex(){   int result;   if (hasPrevious())      result = nextIndex - 1;    else      result = -1;       return result;} // end previousIndex