/* CS 0401
 * Zach Sadler
 * Assignment 5
 * House
 */
 
import java.awt.*;
import java.awt.geom.*;
import java.util.*;

class House implements MyShape
{
	private Polygon base, roof, door;

	private int x, y, size;
	
	private boolean isHighlighted;
	
	public House(int startx, int starty, int siz)
	{
		x = startx;
		y = starty;
		size = siz;
		
		base = new Polygon();
		base.addPoint(x, y);
		base.addPoint(x, y - 2*size/3);
		base.addPoint(x - size, y - 2*size/3);
		base.addPoint(x - size, y);
		roof = new Polygon();
		roof.addPoint(x, y - 2*size/3);
		roof.addPoint(x - size/2, y - size);
		roof.addPoint(x - size, y - 2*size/3);
		door = new Polygon();
		door.addPoint(x - 2*size/5, y);
		door.addPoint(x - 2*size/5, y - size/3);
		door.addPoint(x - 3*size/5, y - size/3);
		door.addPoint(x - 3*size/5, y);
		
	}
	
	public void highlight(boolean b)
	{
		isHighlighted = b;
	}
	
	public void draw(Graphics2D g)
	{
		g.setColor(Color.white);
		if (isHighlighted)
			g.draw(base);
		else
			g.fill(base);
		g.setColor(Color.black);
		if (isHighlighted)
			g.draw(roof);
		else
			g.fill(roof);
		g.setColor(Color.red);
		if (isHighlighted)
			g.draw(door);
		else
			g.fill(door);
	}

	public void move(int dx, int dy)
	{
		int deltaX = dx - x;
		int deltaY = dy - y;
		base.translate(deltaX, deltaY);
		roof.translate(deltaX, deltaY);
		door.translate(deltaX, deltaY);
		x = dx;
		y = dy;
	}
	
	public boolean contains(double x, double y)
	{
		if (base.contains(x,y))
			return true;
		if (roof.contains(x,y))
			return true;
		return false;
	}
	
	
	public void resize(int newsize)
	{
		size = newsize;
		base = new Polygon();
		base.addPoint(x, y);
		base.addPoint(x, y - 2*size/3);
		base.addPoint(x - size, y - 2*size/3);
		base.addPoint(x - size, y);
		roof = new Polygon();
		roof.addPoint(x, y - 2*size/3);
		roof.addPoint(x - size/2, y - size);
		roof.addPoint(x - size, y - 2*size/3);
		door = new Polygon();
		door.addPoint(x - 2*size/5, y);
		door.addPoint(x - 2*size/5, y - size/3);
		door.addPoint(x - 3*size/5, y - size/3);
		door.addPoint(x - 3*size/5, y);
		
	}
	
	public String saveData()
	{
		return ("House:" + x + ":" + y + ":" + size);
	}
}