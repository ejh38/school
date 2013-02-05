// CS 0445 Spring 2012
// Assignment 1 Bufferer<T> interface
// Carefully read the specifications for each of the operations and
// implement them correctly in your MyBuffer<T> class.

// The overall logic of the Bufferer<T> is the following:
//		Data is logically "consumed" in the same order that it is "produced".
// However, there is no requirement for the physical storage of the actual
// data.  Your only requirement for the MyBuffer<T> class is that all of the
// methods work as specified and that your MyBuffer<T> class have an array as its
// its primary data.  You MAY NOT use ArrayList, Vector or any predefined
// collection class for your MyBuffer<T> data.  However, you may want to use some
// some additional instance variables to keep track of the data effectively.

public interface Bufferer<T>
{
	// Add a new Object to the Bufferer in the next available location.  If
	// all goes well, return true.  If there is no room in the Bufferer for
	// the new item, return false.
	public boolean produceItem(T item);
	
	// Remove and return the "oldest" item in the Bufferer.  If the Bufferer
	// is empty, return null
	public T consumeItem();
	
	// Return true if the Bufferer is full, and false otherwise
	public boolean isFull();
	
	// Return true if the Bufferer is empty, and false otherwise
	public boolean isEmpty();
	
	// Return the number of items currently in the Bufferer
	public int size();

	// Reset the Bufferer to empty status by reinitializing the variables
	// appropriately
	public void clear();
}