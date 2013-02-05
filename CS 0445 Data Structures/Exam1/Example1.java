// CS 0445 Spring 2012 Example 1
// This program reviews some of the basic syntax and functionality
// of the Java language, especially classes and objects

public class Example1  // Recall that all declaractions must be within
	// a class, and that each file can have only one public class, but 
	// possibly other private classes can be in the same file
{
	// Recall that static methods are not part of objects, but rather
	// are part of the class itself.  Thus, they do not have access to
	// implicit data within the objects
	public static void checkData(MyRectangle r1, MyRectangle r2)
	{
		// Recall that the == operator in Java compares primitive types
		// correctly, but for reference types it compares the references,
		// NOT the objects.  Be careful to avoid this common mistake.
		if (r1 == r2)
			System.out.println(r1 + " and\n" +r2+ "\nare the same object");
		else
			System.out.println(r1 + " and\n" +r2+ "\nare diff. objects");
		System.out.println();

		// To compare objects, we typically use the equals() method.  This
		// method is defined in the Object class, and we override it in our
		// classes to compare objects as we wish.  See the MyRectangle class
		// for more information on this method.
		if (r1.equals(r2))   // method call
			System.out.println(r1 + " and\n" +r2+ "\nare equal objects");
		else
			System.out.println(r1 + " and\n" +r2+ "\nare not equal");
		System.out.println("\n");
	}

	public static void main(String [] args) // Note syntax of main
	{
		// Recall that all objects in Java are dynamic, so that
		// you must declare variables and then create objects
		// to store in them, as shown below
		MyRectangle rec1, rec2, rec3, rec4;
		rec1 = new MyRectangle(15, 5, 20, 22);
		rec2 = new MyRectangle(20, 10, 100, 50);
		rec3 = new MyRectangle(20, 10, 100, 50);
		// The statement below is NOT creating a new object.  Rather, it is
		// setting reference rec4 to the same object that rec3 was set to.
		rec4 = rec3;

		checkData(rec1, rec2);
		checkData(rec2, rec3);
		checkData(rec3, rec4);

		rec3.setWidth(75); // mutate rec3, changing its width
		checkData(rec2, rec3);
		// Note that the check below still has the same result as before.
		// Since rec3 and rec4 refer to the same object, mutating that
		// object through either rec3 or rec4 still mutates the same object.
		checkData(rec3, rec4);

		int a1 = rec1.area();
		System.out.println("Rec1: " + rec1);
		System.out.println("Rec 1 Area: " + a1);
		System.out.println();
		for (int i = 0; i < 30; i++)          // Nested loops
		{
			for (int j = 0; j < 70; j++)
			{
				if (rec1.contains(j, i))
					System.out.print("*");
				else
					System.out.print("-");
			}
			System.out.println();
		}
	}
}


