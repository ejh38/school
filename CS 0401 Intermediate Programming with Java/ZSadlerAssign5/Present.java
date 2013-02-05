/* CS 0401
 * Zach Sadler
 * Assignment 5
 * Present
 */
 
import java.awt.*;
import java.awt.geom.*;
import java.util.*;

class Present implements MyShape
{
	private Polygon base, ribbon;

	private int x, y, size;
	
	private boolean isHighlighted;
	
	public Present(int startx, int starty, int siz)
	{
		x = startx;
		y = starty;
		size = siz;
		
		base = new Polygon();
		base.addPoint(x, y);
		base.addPoint(x, y - size);
		base.addPoint(x - size, y - size);
		base.addPoint(x - size, y);
		ribbon = new Polygon();
		ribbon.addPoint(x, y - 3*size/7);
		ribbon.addPoint(x, y - 4*size/7);
		ribbon.addPoint(x - 3*size/7, y-4*size/7);
		ribbon.addPoint(x - 3*size/7, y - size);
		ribbon.addPoint(x - 4*size/7, y - size);
		ribbon.addPoint(x - 4*size/7, y - 4*size/7);
		ribbon.addPoint(x - size, y - 4*size/7);
		ribbon.addPoint(x - size, y - 3*size/7);
		ribbon.addPoint(x - 4*size/7, y - 3*size/7);
		ribbon.addPoint(x - 4*size/7, y);
		ribbon.addPoint(x - 3*size/7, y);
		ribbon.addPoint(x - 3*size/7, y - 3*size/7);
		ribbon.addPoint(x, y - 3*size/7);
	}
	
	public void highlight(boolean b)
	{
		isHighlighted = b;
	}
	
	public void draw(Graphics2D g)
	{
		g.setColor(Color.blue);
		if (isHighlighted)
			g.draw(base);
		else
			g.fill(base);
		g.setColor(Color.red);
		if (isHighlighted)
			g.draw(ribbon);
		else
			g.fill(ribbon);
	}

	public void move(int dx, int dy)
	{
		int deltaX = dx - x;
		int deltaY = dy - y;
		base.translate(deltaX, deltaY);
		ribbon.translate(deltaX, deltaY);
		x = dx;
		y = dy;
	}
	
	public boolean contains(double x, double y)
	{
		if (base.contains(x,y))
			return true;
		if (ribbon.contains(x,y))
			return true;
		return false;
	}
	
	public void resize(int newsize)
	{
		size = newsize;
		base = new Polygon();
		base.addPoint(x, y);
		base.addPoint(x, y - size);
		base.addPoint(x - size, y - size);
		base.addPoint(x - size, y);
		ribbon = new Polygon();
		ribbon.addPoint(x, y - 3*size/7);
		ribbon.addPoint(x, y - 4*size/7);
		ribbon.addPoint(x - 3*size/7, y-4*size/7);
		ribbon.addPoint(x - 3*size/7, y - size);
		ribbon.addPoint(x - 4*size/7, y - size);
		ribbon.addPoint(x - 4*size/7, y - 4*size/7);
		ribbon.addPoint(x - size, y - 4*size/7);
		ribbon.addPoint(x - size, y - 3*size/7);
		ribbon.addPoint(x - 4*size/7, y - 3*size/7);
		ribbon.addPoint(x - 4*size/7, y);
		ribbon.addPoint(x - 3*size/7, y);
		ribbon.addPoint(x - 3*size/7, y - 3*size/7);
		ribbon.addPoint(x, y - 3*size/7);

		
	}
	
	public String saveData()
	{
		return ("Present:" + x + ":" + y + ":" + size);
	}

}