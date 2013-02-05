// CS 0401 Fall 2011
// Very simple class example

public class IntCircle
{
	// instance variable is private.  This means that we can access it within
	// this class, but NOT outside the class
	private int radius;

	// constructor.  Note that there is no return type
	public IntCircle(int r)
	{
		radius = r;
	}

	// default constructor.  This is "overloading" the constructor method.  We
	// will discuss overloading in more detail soon
	public IntCircle()
	{}

	// accessor to return the area of the circle
	public double area()
	{
		return (Math.PI * radius * radius);
	}

	// accessor to return the cirumference of the circle
	public double circumference()
	{
		return (2 * Math.PI * radius);
	}

	// accessor to return the circle information as a String
	public String toString()
	{
		return ("Radius: " + radius);
	}

	// mutator to change the radius
	public void setRadius(int r)
	{
		if (r >= 0)
			radius = r;
		else
			System.out.println("Illegal value " + r + " for radius");
	}
}