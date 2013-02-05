/* CS 0401 Fall 2011 Java Example 10
   Simple demonstration of using a simple class.  See also IntCircle.java
*/
public class ex10
{
	public static void main (String [] args)
	{
		// Two circle variables, but no objects yet
		IntCircle C1 = null, C2 = null;

		// Now create objects using the CONSTRUCTOR
		C1 = new IntCircle(2);
		C2 = new IntCircle(4);

		IntCircle C3 = new IntCircle();

		// Using the ACCESSORS
		System.out.println(C1.toString() + " Area: " + C1.area() +
			               " Circumference: " + C1.circumference());
		System.out.println(C2 + " Area: " + C2.area() +
			               " Circumference: " + C2.circumference());
		System.out.println(C3 + " Area: " + C3.area() +
			               " Circumference: " + C3.circumference());

		// Using the MUTATOR to change the radius
		C1.setRadius(3);
		System.out.println(C1 + " Area: " + C1.area() +
			" Circumference: " + C1.circumference());

		//C1.setRadius(-10);
		// Note: Since the data is private we are NOT allowed to do the
		// following:
		//C1.radius = -5;
		//System.out.println("Radius: " + C1.radius);
		// Uncomment the lines above to see the resulting error.  This is why
		// we use accessor methods and mutator methods to access the data.
		// Also change the declaration of radius in IntCircle to public to see
		// that the lines above would then be legal.
	}
}
