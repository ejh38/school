/* -----------------
 * Zach Sadler 
 * Recitation Mon 1:00pm
 * Assignment 1
 * Implemented so that there is always the oldest
 * item at the 0th position, and the newest in the
 * numEntries position. Dynamically adjusts so that
 * there is (hopefully) never nullspace in the front
 */
 
import java.io.*;

public class MyBuffer<T> implements Bufferer<T>, SaveRestore, Reverser
{
	// all the needed instance data
	private T[] array;
	private final int defaultCapacity = 10;
	private int numEntries;
	
	// no default constructor since one is never used in the driver
	public MyBuffer(int capacity)
	{
		numEntries = 0;
		@SuppressWarnings("unchecked")
		array = (T[]) new Object[capacity];
	}
	
	// adds a new item into the numEntries position, then
	// returns true if the array isn't full, false else
	public boolean produceItem(T item)
	{
		if (isFull())
			return false;
		else
		{
			array[numEntries] = item;
			numEntries++;
			return true;
		}
	}
	
	// if the array is empty, then return null
	// otherwise just pop off the 0th item,
	// which should be non-null, shift the entries
	// decrement numEntries, and return the item
	// Note that it doesn't actually delete the item,
	// shift() does the actual work
	public T consumeItem()
	{
		if (isEmpty())
			return null;
		else
		{
			T temp = array[0];
			shift();
			numEntries--;
			return temp;
		}
	}
	
	
	// this is an awesome, private method that I use often
	// it is used to get rid of whitespace in the front, and
	// simply shifts all entries to the left one, except for the
	// first entry, which it skips
	private void shift()
	{
		@SuppressWarnings("unchecked")
		T[] temp = (T[]) new Object[array.length];
		for (int i = 0; i < array.length - 1; i++)
		{
			temp[i] = array[i+1];
		}
		array = temp;
	}
			
	
	// Return true if the Bufferer is full, and false otherwise
	public boolean isFull()
	{
		if (array.length == numEntries)
			return true;
		return false;
	}
	
	// Return true if the Bufferer is empty, and false otherwise
	public boolean isEmpty()
	{
		if (numEntries == 0)
			return true;
		return false;
	}
	
	// Return the number of items currently in the Bufferer
	public int size()
	{
		return numEntries;
	}

	// Resets numEntries and then sets the array to
	// a new, empty array of the same length
	public void clear()
	{
		numEntries = 0;
		array = (T[]) new Object[array.length];
	}
		
	// Uses a FileOutputStream and ObjectOutputStream,
	// straight out of the API. It writes all of the
	// non-null items to the file, with a try/catch block
	// that prints out the exception just in case one occurs
	public boolean saveToFile(String fileName)
	{
		try
		{
			FileOutputStream fos = new FileOutputStream(fileName);
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			for (int i = 0; i < array.length; i++)
			{
				if (array[i] != null)
					oos.writeObject(array[i]);
			}
			oos.close();			
		}
		catch (Exception e)
		{
			System.out.println(e.getStackTrace());
			return false;
		}
		return true;
	}

	// Again, straight from the API, and in a try-catch block
	// this time it reads in all the entries (even if they're null),
	// but it is unlikely that a null one snuck in
	public boolean restoreFromFile(String fileName)
	{
		try
		{
			FileInputStream fis = new FileInputStream(fileName);
			ObjectInputStream ois = new ObjectInputStream(fis);
			clear();
			for (int i = 0; i < array.length; i++)
			{
				array[i] = (T) ois.readObject();
				numEntries++;
			}

			ois.close();
		}
		catch (Exception e)
		{
//			System.out.println(e.getStackTrace());
			return false;
		}
		return true;
	}
	
	// This one takes advantage of shift.
	// Copy the old array into a new, temporary one
	// and shift for each null space, to make sure that you have
	// contiguous, non-null entries.
	public void reverse()
	{
		@SuppressWarnings("unchecked")
		T[] temp = (T[]) new Object[array.length];
		for (int i = 0; i < array.length; i++)
		{
			temp[array.length - (i + 1)] = array[i];
		}
		array = temp;
		for (int i = 0; i < array.length; i++)
		{
			if (array[0] == null)
				shift();
		}
	}
	
	// Display each non-null entry	
	public String toString()
	{
		String temp = "Here is the buffer:\n";
		for (int i = 0; i < array.length; i++)
		{
			if (array[i] != null)
			{
				temp += (array[i] + " ");
			}
		}
		return temp;
	}

}