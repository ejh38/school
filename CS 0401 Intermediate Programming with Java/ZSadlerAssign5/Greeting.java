// CS 401 Fall 2011
// The Greeting class allows text to be added to a scene.

import java.awt.*;
import java.awt.geom.*;
import java.util.*;

class Greeting implements MyText
{
	private int X, Y;
	private Rectangle2D boundingBox;
	private String text;
	private Font font;
	private Color color;
	private int size;
	private boolean highlighted;
	
	// Create a new Greeting object with some default text
	public Greeting(int startX, int startY, int sz)
	{
		X = startX;
		Y = startY;
		size = sz;
		text = new String("Edit Text");
		font = new Font("Times New Roman", Font.PLAIN, size);
		color = Color.BLACK;
		highlighted = false;
	}
	
	// Alternate constructor which allows a different text String to be used
	public Greeting(int startX, int startY, int sz, String s)
	{
		this(startX, startY, sz);
		setText(s);
	}
	
	// This method is tricky.  We want the user to be able to select the Greeting object
	// to edit / move it, etc.  To do this we need a way to find it.  This can be done with
	// a bounding box, which is actually just a Rectangle2D object.  However, we want the
	// bounding box to be minimally bigger than the actual text, which cannot be done without
	// knowledge of the text, font and graphics environment.  This can be done with the
	// FontMetrics class, as shown below.
	public void draw(Graphics2D g)
	{
		g.setColor(Color.BLACK);
		g.setFont(font);
		FontMetrics f = g.getFontMetrics();
		g.drawString(text, X, Y);  // draw actual text
		boundingBox = f.getStringBounds(text, g);  // get bounding box
		boundingBox.setFrame(X, Y-boundingBox.getHeight(), boundingBox.getWidth(), boundingBox.getHeight());
		if (highlighted)
			g.draw(boundingBox);  // only draw bounding box if highlighted
	}
	
	// Move by simply updating the X and Y values.  These will be utilized when the
	// text is next drawn.
	public void move(int x, int y)
	{
		X = x;
		Y = y;
	}
	
	public void highlight(boolean b)
	{
		highlighted = b;
	}
	
	// Use the bounding box to determine if the Greeting object contains a point.
	public boolean contains(double x, double y)
	{
		return boundingBox.contains(x, y);
	}
	
	// Note that we are adding the text to the end of this object.  This must
	// be taken into account when a scene is being restored.
	public String saveData()
	{
		return ("Greeting:" + X + ":" + Y + ":" + size + ":" + text);
	}
	
	// Set the size and make a new font with that size
	public void resize(int newsize)
	{
		size = newsize;
		font = new Font("Times New Roman", Font.PLAIN, size);
	}
	
	// Set the text
	public void setText(String s)
	{
		text = new String(s);
	}
}	
