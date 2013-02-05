// CS 0401 Lab 5 Driver Program
// Compile and run this program to test your MyRectangle class.
// Compare the output of your program with the provided file 
// lab5out.txt

public class Lab5
{
	public static void testInside(MyRectangle R, int x, int y)
	{
		System.out.print("Point (" + x + "," + y + ")");
		if (R.isInside(x, y))
			System.out.println(" is INSIDE " + R);
		else
			System.out.println(" is OUTSIDE " + R);
	}

	public static void main(String [] args)
	{
		MyRectangle R1, R2, R3;

		R1 = new MyRectangle(100, 50, 80, 20);
		R2 = new MyRectangle();
		R3 = new MyRectangle(60, 60, 100, 100);
 
		// In Java, when Objects are printed (as shown below), the toString()
		// method is implicitly called.  Thus the statements below will call
		// toString() for each of the three MyRectangle objects
		System.out.println("R1: " + R1 + " Area: " + R1.area());
		System.out.println("R2: " + R2 + " Area: " + R2.area());
		System.out.println("R3: " + R3 + " Area: " + R3.area());

		int x1 = 120, y1 = 70;
		int x2 = 130, y2 = 110;

		// Verify with a pencil and paper which of these should be true and
		// which should be false.
		testInside(R1, x1, y1);
		testInside(R3, x1, y1);
		testInside(R1, x2, y2);
		testInside(R3, x2, y2);

		R1.setSize(120, 240);
		R3.setPosition(400, 350);
		testInside(R1, x2, y2);
		testInside(R3, x2, y2);
	}
}


