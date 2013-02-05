// CS 401 Fall 2011
// Simple demo of a Java ArrayList.  See various methods and how they work
// in the code below.

import java.util.*;
public class ArrayL
{
	public static void main(String [] args)
	{
		ArrayList<String> A = new ArrayList<String>();
			// Note how we specify the type to be stored in the ArrayList
		
		// Append some Strings to the end of the ArrayList
		A.add("Wacky");
		A.add("Fun");
		A.add("Get me out of here!");
		
		// "foreach" loop also works with ArrayList -- COOL!
		for (String X: A)
			System.out.println(X);
		System.out.println();			
		
		A.add(1,"Zany");
		
		for (String X: A)
			System.out.println(X);
		System.out.println();
			
		A.remove(0);

		for (int i = 0; i < A.size(); i++)
		{
			System.out.println("At " + i + " we have: " + A.get(i));
		}
		System.out.println();
		
		String entry = new String("More and more fun");
		for (int i = 0; i < 10; i++)
		{
			A.add(entry);
		}
	
		System.out.println("ArrayList A contains: ");
		for (String X: A)
			System.out.println(X);
		System.out.println();
		
		// Various methods search the ArrayList (some examples shown below).  In each
		// case, the methods utilize the equals() method, which must be defined for
		// the class within the ArrayList.  If equals() is not defined for the given
		// class, the seach will use a default equals() method that is based on equality
		// of references.
		boolean found = true;
		int count = 0;
		found = A.remove(entry);
		while (found)
		{
			count++;
			found = A.remove(entry);
		}
		System.out.println("Removed " + count + " references to " + entry);
		System.out.println();
		
		String [] data = {"here", "there", "here", "somewhere", "elsewhere", "here"};
		ArrayList<String> B = new ArrayList<String>();
		for (String X: data)
			B.add(X);
	
		for (int i = 0; i < B.size(); i++)
		{
			System.out.println("At " + i + " we have: " + B.get(i));
		}
		System.out.println();
		
		entry = new String("here");
		count = 0;
		int loc = B.indexOf(entry);
		while (loc >= 0)
		{
			B.remove(loc);
			System.out.println(entry + " deleted from location " + loc);
			loc = B.indexOf(entry);
		}
		System.out.println();
		
		// We can make ArrayLists of any Java class, including classes that
		// we write ourselves.
		ArrayList<IntCircle> newList = new ArrayList<IntCircle>();
		newList.add(new IntCircle(3));
		newList.add(new IntCircle(2));
		newList.add(new IntCircle(1));
		System.out.println("Here are the circles: ");
		for (IntCircle C: newList)
			System.out.println(C);
		
	}
}