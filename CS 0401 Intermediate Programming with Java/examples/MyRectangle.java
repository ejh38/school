// CS 401 Lab 5
// Fill in the indicated code sections to complete this class.  Then test it
// by compiling and executing Lab5.java.

public class MyRectangle
{
	// Declare instance variables here
	
	private int startX, startY, width, height;
	
	public MyRectangle()
	{
		// Default constructor -- initialize all instance variables
		// to 0
		startX = 0; 
		startY = 0; 
		width = 0; 
		height = 0;
	}

	public MyRectangle(int x, int y, int w, int h)
	{
		// Initialize instance variables based on parameters shown.
		// Be careful to get the order correct!
		startX = x;
		startY = y;
		width = w;
		height = h;
		
	}

	public int area()
	{
		// Return the area of this Rectangle
		return width*height;
	}

	// I have written this method for you.  Note how a StringBuilder is
	// utilized, since (as we discussed in lecture) it can be modified
	// without having to create a new object each time (unlike a String).
	public String toString()
	{
		StringBuilder S = new StringBuilder();
		S.append("Width: " + width);
		S.append(" Height: " + height);
		S.append(" X: " + startX);
		S.append(" Y: " + startY);
		return S.toString();
	}

	public boolean isInside(int x, int y)
	{
		// This is the trickiest of the methods to write.  This should
		// return true if point (x,y) is anywhere within the borders of the
		// current MyRectangle (including the borders themselves).  Use a
		// pencil and paper to figure out how this can be determined with
		// just a few simple relational operations.
		
		if ((x >= startX && x <= (startX + width)) &&
			 (y >= startY && y <= (startY + height)) )
			return true;
		else
			return false;
		
		
	}

	public void setSize(int w, int h)
	{
		// Update width and height as shown
		width = w;
		height = h;
	}

	public void setPosition(int x, int y)
	{
		// Update startX and startY as shown
		startX = x;
		startY = y;
	}

}
