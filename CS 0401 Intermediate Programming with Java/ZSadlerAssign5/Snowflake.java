// CS 401 Fall 2011
// Snowflake class implementation of the MyShape interface.  Use this
// example to help you with the other shape classes for your project.
// See comments below for more information.

import java.awt.*;
import java.awt.geom.*;
import java.util.*;

class Snowflake implements MyShape
{
	// Build a Snowflake using composition.  We are using 4 lines to
	// represent our Snowflake
	private Line2D line1, line2, line3, line4;

	// The predefined Line2D class has a contains() method but it
	// always returns false (since a line has no area).  However, we
	// need our Snowflake to to have area, so I am using a Rectangle2D
	// as a "box" around the Snowflake.  This is used for the
	// contains() method, but it is not drawn, so the user does not
	// see it at all.  This is a good example of data hiding -- the
	// user of a Snowflake does not need to know that a Rectangle2D
	// is even present in the object.
	private Rectangle2D perimeter;

	// X,Y position
	private int X, Y;

	// size of the Snowflake
	private int size;

	private boolean isHighlighted;

	// Create a new Snowflake.  Note how the endpoints of the four
	// lines are set to give the Snowflake a nice shape.  Also note
	// that the perimeter variable is set to allow the Snowflake to have
	// area (for selecting purposes).
	public Snowflake(int startX, int startY, int sz)
	{
		X = startX;
		Y = startY;
		size = sz;
		line1 = new Line2D.Double(X,Y,X-size,Y-size);
		line2 = new Line2D.Double(X-size,Y,X,Y-size);
		line3 = new Line2D.Double(X-size/2,Y+size/2,X-size/2,Y-3*size/2);
		line4 = new Line2D.Double(X+size/2,Y-size/2,X-3*size/2,Y-size/2);
		perimeter = new Rectangle2D.Double(X-size,Y-size,size,size);
		isHighlighted = false;
	}

	public void highlight(boolean b)
	{
		isHighlighted = b;
	}

	// Draw the Snowflake "onto" the Graphics2D parameter that is passed
	// in.  This method will be called from a JFrame or JPanel, which
	// is where the Graphics2D object originates.  Since a Snowflake is
	// really just 4 lines, draw each of the lines.  See the Line2D class
	// and the Shape interface for more information.
	public void draw(Graphics2D g)
	{
		if (!isHighlighted)
			g.setColor(Color.white);
		else
			g.setColor(Color.red);
		g.draw(line1);
		g.draw(line2);
		g.draw(line3);
		g.draw(line4);

	}

	// All this method is doing is resetting the X and Y coordinates,
	// and then updating the lines and rectangle to reflect the new
	// location.
	public void move(int x, int y)
	{
		X = x;
		Y = y;
		line1.setLine(X,Y,X-size,Y-size);
		line2.setLine(X-size,Y,X,Y-size);
		line3.setLine(X-size/2,Y+size/2,X-size/2,Y-3*size/2);
		line4.setLine(X+size/2,Y-size/2,X-3*size/2,Y-size/2);
		perimeter.setFrame(X-size,Y-size,size,size);
	}

	// Note the somewhat sneaky way this is implemented.  Note that the
	// move method reconfigures the figure using the current size.  So
	// just call move() using the same X,Y values (i.e. moving 0) which
	// ends up resizing the figure.
	public void resize(int newsize)
	{
		size = newsize;
		move(X,Y);
	}
	
	// Note how simple this method is, since the Rectangle2D class
	// already has a contains() method that works as we want it to.
	public boolean contains(double x, double y)
	{
		return perimeter.contains(x,y);
	}

	// Note how this string is formatted.  Your other classes should
	// format the string in the same way.
	public String saveData()
	{
		return ("Snowflake:" + X + ":" + Y + ":" + size);
	}
}