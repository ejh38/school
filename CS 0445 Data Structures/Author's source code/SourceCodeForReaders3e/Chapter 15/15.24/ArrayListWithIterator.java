import java.util.Iterator;import java.util.NoSuchElementException;public class ArrayListWithIterator<T> implements                                       ListWithIteratorInterface<T>{   private T[] list; // array of list entries   private int numberOfEntries;   private static final int DEFAULT_INITIAL_CAPACITY = 25;   public ArrayListWithIterator()   {      this(DEFAULT_INITIAL_CAPACITY);   } // end default constructor   public ArrayListWithIterator(int initialCapacity)   {      numberOfEntries = 0;      // the cast is safe because the new array contains null entries      @SuppressWarnings("unchecked")      T[] tempList = (T[])new Object[initialCapacity];      list = tempList;   } // end constructor   //  < Implementations of the methods of the ADT list go here;   //    you can see them in Chapter 13, beginning at Segments 13.5. >   //  . . .   public Iterator<T> getIterator()   {      return new IteratorForArrayList();   } // end getIterator   //  < Segment 15.25 begins a description of the following inner class. >   private class IteratorForArrayList implements Iterator<T>   {      private int nextIndex;      private boolean wasNextCalled; // needed by remove      private IteratorForArrayList()      {         nextIndex = 0;         wasNextCalled = false;      } // end default constructor      //    < Implementations of the methods in the interface Iterator go here;      //      you can see them in Segments 15.26 through 15.28. >      //    . . .   } // end IteratorForArrayList} // end ArrayListWithIterator