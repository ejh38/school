public static <T extends Comparable<? super T>>       void mergeSort(T[] a, int first, int last){   // the cast is safe because the new array contains null entries   @SuppressWarnings("unchecked")   T[] tempArray = (T[])new Comparable<?>[a.length]; // unchecked cast   mergeSort(a, tempArray, first, last);} // end mergeSort