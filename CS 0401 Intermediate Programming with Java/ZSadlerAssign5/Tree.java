// CS 401 Fall 2011
// Tree class as another implementation of the MyShape interface.
// This class also uses composition, with 2 Polygons being the primary
// components of a Tree object.  For more information on Polygons, see
// the Java API.

import java.awt.*;
import java.awt.geom.*;
import java.util.*;

class Tree implements MyShape
{
	// Represent a Tree in two parts -- a Polygon for the top part 
	// (the branches) and another Polygon for the trunk.  Since the
	// trunk is rectangular, a Rectangle2D could have been used, but
	// to keep consistent (especially with the move() method) I used
	// Polygon objects for both.
	private Polygon canopy;
	private Polygon trunk;

	// X, Y and size instance variables
	private int X, Y;
	private int size;

	private boolean isHighlighted;
	
	// Create a new Tree object.  Note how the Polygons are built,
	// adding one point at a time to each.  If you plot the points out
	// on paper you will see how the shapes are formed.
	public Tree(int startX, int startY, int sz)
	{
		X = startX;
		Y = startY;
		size = sz;

		canopy = new Polygon();
		canopy.addPoint(X,Y);
		canopy.addPoint(X-size,Y);
		canopy.addPoint(X-size/2,Y-5*size/3);
		trunk = new Polygon();
		trunk.addPoint(X-3*size/8,Y);
		trunk.addPoint(X-5*size/8,Y);
		trunk.addPoint(X-5*size/8,Y+size/2);
		trunk.addPoint(X-3*size/8,Y+size/2);
	}

	public void highlight(boolean b)
	{
		isHighlighted = b;
	}

	// The Polygon class can also be drawn with a predefined method in
	// the Graphics2D class.  There are two versions of this method:
	// 1) draw() which only draws the outline of the shape
	// 2) fill() which draws a solid shape
	// In this class the draw() method is used when the object is
	// highlighted.
	public void draw(Graphics2D g)
	{
		g.setColor(Color.green);
		if (isHighlighted)
			g.draw(canopy);
		else
			g.fill(canopy);
		g.setColor(Color.orange);
		if (isHighlighted)
			g.draw(trunk);
		else
			g.fill(trunk);
	}

	// Looking at the API, we see that Polygon has a translate() method
	// which can be useful to us.  All we have to do is calculate the
	// difference of the new (x,y) and the old (X,Y) and then call
	// translate() for both parts of the tree.
	public void move(int x, int y)
	{
		int deltaX = x - X;
		int deltaY = y - Y;
		canopy.translate(deltaX, deltaY);
		trunk.translate(deltaX, deltaY);
		X = x;
		Y = y;
	}

	// Polygon also has a contains() method, so this method is also
	// simple
	public boolean contains(double x, double y)
	{
		if (canopy.contains(x,y))
			return true;
		if (trunk.contains(x,y))
			return true;
		return false;
	}

	// The move() method for the Polygons that are in Tree are not
	// reconfigured like in Snowflake, so we can't use the trick used
	// there.  Instead, we just create new Polygons with the new size.
	// The old ones will be garbage collected by the system.
	public void resize(int newsize)
	{
		size = newsize;
		canopy = new Polygon();
		canopy.addPoint(X,Y);
		canopy.addPoint(X-size,Y);
		canopy.addPoint(X-size/2,Y-5*size/3);
		trunk = new Polygon();
		trunk.addPoint(X-3*size/8,Y);
		trunk.addPoint(X-5*size/8,Y);
		trunk.addPoint(X-5*size/8,Y+size/2);
		trunk.addPoint(X-3*size/8,Y+size/2);
	}

	// Note again the format
	public String saveData()
	{
		return ("Tree:" + X + ":" + Y + ":" + size);
	}
}
