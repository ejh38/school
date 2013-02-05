/* CS 0401 Fall 2011 Java Example 9
   This example demonstrates the idea of encapsulation of data and operations
   in a single Object, and of data abstraction.   The class used is the
   StringBuffer class.  Note the comments in various places below.  Note in
   particular comments about CONSTRUCTORS, ACCESSORS and MUTATORS.

   For a LOT more information on the StringBuilder class, including the full
   list of available methods see the documentation in the Java API Online:
   http://download.oracle.com/javase/6/docs/api/
*/
public class ex9
{
	public static void showInfo(StringBuilder S)
	{
		// All of the methods used here are ACCESSORS -- they are used
		// to access properties of the objects, without changing them.
		System.out.printf("Data: %-12s Length: %-3d Capacity: %-3d \n",
			              S.toString(), S.length(), S.capacity());

		// Mutate object that S references.  This is clearly not a good
		// idea in a method called "showInfo" -- it is just for demo purposes.
		// Uncomment the line to see its (side) effect.
		//S.append("BOGUS");

		// Assign S to a new object -- value parames keep this from affecting
		// the argument
		S = new StringBuilder("ZANY");
	}
	public static void main (String [] args)
	{
		StringBuilder S1, S2, S3;
		S1 = new StringBuilder();	// Create an empty StringBuilder using a
									// CONSTRUCTOR
		S2 = new StringBuilder("abstraction");	// Create a StringBuilder that
									// has some initial data in it, using
									// a different CONSTRUCTOR.
		showInfo(S1);	showInfo(S2);
		System.out.println();

		// The append() method is a MUTATOR.  Mutators alter the object in some
		// way.  In this case, they are adding additional characters to the
		// StringBuffer
		S1.append("wacky");
		S2.append(" contraption");
		showInfo(S1);  showInfo(S2);
		System.out.println();

		// insert() is another MUTATOR.  Note in the second line below we are
		// also using an ACCESSOR.  The idea is to insert "distraction " after the
		// first space in the previous string.
		S1.insert(0, "very ");
		S2.insert(S2.indexOf(" ")+1, "distraction ");

		showInfo(S1);	showInfo(S2);
		System.out.println();

		// Recall from our previous discussions about reference types and the
		// implications of using them.  Here S3 and S1 are now different
		// variables referencing the SAME StringBuilder object.  Thus when we
		// MUTATE S3 using the reverse() method, and then print S1, we see that
		// that object has been reversed.
		S3 = S1;
		S3.reverse();
		showInfo(S1);
	}
}
