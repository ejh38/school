// CS 0445 Spring 2012
// Simple class (not using graphics) to review some of the
// syntax and semantics of Java classes

public class MyRectangle
{
	private int xOrig, yOrig;    // most data is declared to be
	private int width, height;   // private

	public MyRectangle(int x, int y, int w, int h)
	{
		xOrig = x; yOrig = y;   // constructor
		width = w; height = h;
	}

	public int area()              // public methods allow other
	{                              // classes and the main program
		return (width * height);   // to indirectly access an
	}                              // object.  This is an accessor.

	public String toString()       // toString method allows for
	{                              // text "output" of an object

		String s = "Origin: (" + xOrig + "," + yOrig + ")" +
			" Width: " + width + " Height: " + height;
		return s;
	}

	public boolean equals(MyRectangle arg)  // are objects the same?
	{                                       // Note that the parameter
		boolean ans;                        // is a value parameter

		// Since the instance variables are primitive types, we can
		// use the == operator to compare them.  If they were reference
		// types (i.e. this class was created using composition), we
		// would use the equals() method for the instance data as well.
		if ((xOrig == arg.xOrig) && (yOrig == arg.yOrig) &&
			(width == arg.width) && (height == arg.height))
			ans = true;
		else
			ans = false;

		// Demo of Java value parameters
		// arg = new MyRectangle(0,0,0,0);  // This would not change actual
											// parameter even if uncommented
		return ans;
	}

	public boolean contains(int x, int y)  // another boolean method
	{
		if ((x >= xOrig) && (x <= xOrig + width) &&
			(y >= yOrig) && (y <= yOrig + height))
			return true;
		else
			return false;
	}

	// These methods are mutators -- they allow the data within an object
	// to be changed without violating the private nature of the data (i.e.
	// the user does not have direct access to the data itself)
	public void setWidth(int w)
	{	width = w;
	}

	public void setHeight(int h)
	{	height = h;
	}
}