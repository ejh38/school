import java.util.Arrays;import java.util.Iterator;import java.util.NoSuchElementException;public class SortedArrayDictionary<K extends Comparable<? super K>, V>              implements DictionaryInterface<K, V>{//  < Data fields as shown in Listing 20-1 of Segment 20.2 >	private Entry<K, V>[] dictionary; // array of unsorted entries	private int numberOfEntries; 	private final static int DEFAULT_CAPACITY = 25;	//  < Constructors analogous to those in Listing 20-1 >	public SortedArrayDictionary()	{		this(DEFAULT_CAPACITY);	} // end default constructor		public SortedArrayDictionary(int initialCapacity)	{      // the cast is safe because the new array contains null entries      @SuppressWarnings("unchecked")      Entry<K, V>[] tempDictionary = (Entry<K, V>[])new Entry[initialCapacity];      dictionary = tempDictionary;		numberOfEntries = 0;	} // end constructor   //  . . .   public V add(K key, V value)   {   // . . . < See Segment 20.11. >   } // end add   //  < Implementations of other methods in DictionaryInterface >   //  . . .   //  < The private class Entry, as shown in Listing 20-1. >} // end SortedArrayDictionary