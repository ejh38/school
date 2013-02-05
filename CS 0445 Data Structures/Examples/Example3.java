// CS 0401 Spring 2012
// Simple example demonstrating Java generics via parameterized types.
// See MyArray.java for more comments
public class Example3
{
	public static String [] stringData = {"PA", "OH", "NY", "WV", "NH", "MD", "NJ"}; 
	public static void main(String [] args)
	{
		// Note the three variable declarations below.  Each is the same
		// fundamental type (MyArray) but with different generic parameters.
		MyArray<String> S = new MyArray<String>(5);
		MyArray<Integer> I = new MyArray<Integer>(10);
		MyArray<MyRectangle> R;
		R = new MyArray<MyRectangle>(3);

		for (int i = 0; i < S.length(); i++)
			S.set(i, stringData[i]);

		for (int i = 0; i < I.length(); i++)
			I.set(i, new Integer(i));
	
		R.set(0, new MyRectangle(0, 0, 20, 40));
		R.set(1, new MyRectangle(0, 0, 40, 20));
		R.set(2, new MyRectangle(40, 40, 25, 25));

		showData(S);
		showData(I);
		showData(R);

		// We can also show everything using the toString() method for the
		// MyArray class.  This method may not always be defined for a collection
		// class, but it is in this case.
		System.out.println(R.toString());
	}

	// Java also allows for generic methods.  In this case, the
	// method will work for any MyArray type.
	public static <T> void showData(MyArray<T> A)
	{
		System.out.println("Here is the data: ");
		for (int i = 0; i < A.length(); i++)
			System.out.println(A.get(i));
		System.out.println();
	}
}