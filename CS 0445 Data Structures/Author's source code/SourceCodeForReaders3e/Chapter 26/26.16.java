public MaxHeap(T[] entries){   // the cast is safe because the new array contains null entries   @SuppressWarnings("unchecked")   T[] tempHeap = (T[]) new Comparable[entries.length + 1];   heap = tempHeap;   lastIndex = entries.length;   // copy given array to data field   for (int index = 0; index < entries.length; index++)      heap[index + 1] = entries[index];       // create heap   for (int rootIndex = lastIndex/2; rootIndex > 0; rootIndex--)      reheap(rootIndex);} // end constructor