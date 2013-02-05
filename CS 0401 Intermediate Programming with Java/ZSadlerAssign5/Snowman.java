/* CS 0401
 * Zach Sadler
 * Assignment 5
 * Snowman
 */
 
import java.awt.*;
import java.awt.geom.*;
import java.util.*;

class Snowman implements MyShape
{
    private ArrayList<Shape> shapes;// = new ArrayList<Shape>();

	private int x, y, size;
	private Shape s;
	
	private boolean isHighlighted, flag;
	
	public Snowman(int startx, int starty, int siz)
	{
		x = startx;
		y = starty;
		size = siz;
		
		shapes = new ArrayList<Shape>();
		
		s = new Ellipse2D.Double(x, y, size/3, size/3);
		shapes.add(s);
		s = new Ellipse2D.Double(x + size/21, y - size/4, size/4, size/4);
		shapes.add(s);
		s = new Ellipse2D.Double(x + size/11, y - 5*size/12, 2*size/12, 2*size/12);
		shapes.add(s);
		s = new Line2D.Double(x - size/50, y - 5*size/12, x + 35*size/100, y - 5*size/12);
		shapes.add(s);
		s = new Rectangle2D.Double(x + size/8, y - 6*size/12, size/9, size/12);
		shapes.add(s);
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
		g.setColor(Color.white);
		if (!isHighlighted)
			for (Shape s : shapes)
			{
				g.draw(s);
				g.fill(s);
			}
		else
			for (Shape s : shapes)
				g.draw(s);
	}

	// All this method is doing is resetting the X and Y coordinates,
	// and then updating the lines and rectangle to reflect the new
	// location.
	public void move(int dx, int dy)
	{
		int x = dx;
		int y = dy;
		
		shapes = new ArrayList<Shape>();
		s = new Ellipse2D.Double(x, y, size/3, size/3);
		shapes.add(s);
		s = new Ellipse2D.Double(x + size/21, y - size/4, size/4, size/4);
		shapes.add(s);
		s = new Ellipse2D.Double(x + size/11, y - 5*size/12, 2*size/12, 2*size/12);
		shapes.add(s);
		s = new Line2D.Double(x - size/50, y - 5*size/12, x + 35*size/100, y - 5*size/12);
		shapes.add(s);
		s = new Rectangle2D.Double(x + size/8, y - 6*size/12, size/9, size/12);
		shapes.add(s);
		
	}

	// Note the somewhat sneaky way this is implemented.  Note that the
	// move method reconfigures the figure using the current size.  So
	// just call move() using the same X,Y values (i.e. moving 0) which
	// ends up resizing the figure.
	public void resize(int newsize)
	{
		size = newsize;
		move(x, y);
	}
	
	// Note how simple this method is, since the Rectangle2D class
	// already has a contains() method that works as we want it to.
	public boolean contains(double x, double y)
	{
		flag = false;
		for (Shape s : shapes)
		{
			if (s.contains(x, y))
				flag = true;
		}
		return flag;
	}

	// Note how this string is formatted.  Your other classes should
	// format the string in the same way.
	public String saveData()
	{
		return ("Snowman:" + x + ":" + y + ":" + size);
	}
	
	
}