/**    A class of bags whose entries are stored in a chain of linked nodes.    The bag is never full.    @author Frank M. Carrano    @version 3.0*/public class LinkedBag<T> implements BagInterface<T>{	private Node firstNode;       // reference to first node	private int numberOfEntries;	public LinkedBag()	{		firstNode = null;      numberOfEntries = 0;	} // end default constructor	/** Adds a new entry to this bag.	    @param newEntry  the object to be added as a new entry	    @return true */	public boolean add(T newEntry)	{		// To be defined	} // end add	/** Sees whether this bag is full.		 @return false */	public boolean isFull() 	{		// To be defined	} // end isFull		/** Retrieves all entries that are in this bag.	    @return a newly allocated array of all the entries in the bag */	public T[] toArray()	{		// To be defined	} // end toArray	/** Sees whether this bag is empty.	    @return true if the bag is empty, or false if not */	public boolean isEmpty() 	{		return numberOfEntries == 0;	} // end isEmpty	/** Gets the number of entries currently in this bag.	    @return the integer number of entries currently in the bag */	public int getCurrentSize() 	{		// To be defined	} // end getCurrentSize	/** Counts the number of times a given entry appears in this bag.		 @param anEntry  the entry to be counted		 @return the number of times anEntry appears in the bag */	public int getFrequencyOf(T anEntry) 	{		// To be defined	} // end getFrequencyOf	/** Tests whether this bag contains a given entry.		 @param anEntry  the entry to locate		 @return true if the bag contains anEntry, or false otherwise */	public boolean contains(T anEntry)	{		// To be defined	} // end contains      /** Removes all entries from this bag. */	public void clear() 	{		// To be defined	} // end clear		/** Removes one unspecified entry from this bag, if possible.       @return either the removed entry, if the removal               was successful, or null */	public T remove()	{		// To be defined	} // end remove		/** Removes one occurrence of a given entry from this bag, if possible.       @param anEntry  the entry to be removed       @return true if the removal was successful, or false otherwise */   public boolean remove(T anEntry) 	{		// To be defined	} // end remove	private class Node 	{	   private T    data; // entry in bag	   private Node next; // link to next node      private Node(T dataPortion)		{			this(dataPortion, null);			} // end constructor				private Node(T dataPortion, Node nextNode)		{			data = dataPortion;			next = nextNode;			} // end constructor	} // end Node} // end LinkedBag