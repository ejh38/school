/* CS 0401 Fall 2011 Java Example 8
   This handout demonstrates some issues relating to reference variables and
   using them correctly to access objects.
*/

public class ex8
{
	public static void main (String [] args)
	{
		// The StringBuilder class is related to the String class.  See
		// Section 2.9 in the text for details on the String class.
		// (StringBuilder itself is discussed in Section 10.4.  However, we
		// are just looking at it superficially here.) StringBuilder objects
		// can also store and access strings of text.  However, unlike String
		// class objects, StringBuilder class objects can be modified after
		// they are created.  We will look more at the benefits of each later
		// on.
		StringBuilder S1, S2;
		S1 = new StringBuilder("Hello");
		System.out.println("S1 is " + S1);
		//System.out.println("S2 is " + S2);  // This will give a compilation
		                                      // error
		S2 = S1;
		System.out.println("S2 is " + S2);

		S1.append(" there Java maestros!");
		System.out.println("S2 is " + S2);

		StringBuilder S3 = new StringBuilder("Hello there Java maestros!");
		if (S1 == S2)	// comparing references
			System.out.println(S1.toString() + " == " + S2);
		if (S1 != S3)
			System.out.println(S1 + " != " + S3);
		if (S1.toString().equals(S3.toString()))  // comparing actual strings
			System.out.println(S1 + " equals " + S3);

		S1 = null;  // Now S1 cannot be accessed using the "dot" notation but
		            // S2 still refers to the same object
		//S1.append(" This is not allowed");
		S2.append(" This is ok");
		System.out.println("S1 is " + S1);
		System.out.println("S2 is " + S2);

		// Additional interesting note about the String class:
		// The first initialization below is assigning a String without
		// using the new operator, while the second uses new.  Java
		// Strings cannot be changed (i.e. they are constant), and String
		// literals implicitly create objects that are "interned" -- or
		// shared among all literals that are the same.  Thus, St1 and
		// St3 below are == whereas St1 and St2 are not (since an
		// a new object is made for St2).
		String St1;
		St1 = "Herb";
		String St2 = new String("Herb");
		String St3 = "Herb";

		if (St1 == St2)
			System.out.println("St1 and St2 Equal");
		if (St1 == St3)
			System.out.println("St1 and St3 Equal");

	}
}
