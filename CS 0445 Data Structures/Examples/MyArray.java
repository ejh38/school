// CS 0445 Spring 2012
// Simple generic type in Java.  This type allows the user
// to create an array of objects of a specific, arbitrary
// type.  Later on we will look at a more useful class, the
// ArrayList, which has this same idea, but with a lot more
// functionality.

public class MyArray<T>  // Parameter passed to the type
{
	private T [] theArray;  // Parameter used for array data

	public MyArray(int size)
	{
		// Note the way this array is created here.  It would
		// seem more straightforward to have the following
		// assignment:
		//theArray = new T[size];
		// However, this is not allowed in Java so we have to
		// create it as shown below:
		theArray = (T[]) new Object[size];
	}

	// We make length() a method rather than a public instance
	// variable.
	public int length()
	{
		return theArray.length;
	}

	// Standard "get and set" methods to retrieve a value and to
	// assign a value.  Note that they do not check array bounds
	// so if the index is invalid an ArrayIndexOutOfBoundsException
	// will be thrown.
	public T get(int i)
	{
		return theArray[i];
	}

	public void set(int i, T data)
	{
		theArray[i] = data;
	}
	
	public String toString()
	{
		StringBuilder S = new StringBuilder();
		for (int i = 0; i < theArray.length; i++)
		{
			S.append(theArray[i] + "\n");
		}
		return S.toString();
	}
	
}