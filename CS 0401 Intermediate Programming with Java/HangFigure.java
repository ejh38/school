// CS 0401 Fall 2011
// Use this class with Assignment 4 to graphically represent your
// hangman figure.  See comments below.
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;

public class HangFigure
{
	private int xLoc, yLoc; // Where is the figure located?
	private Shape [] chunks;// Store the actual chunks
	private int numChunks;	// How many chunks have been generated so far?
	private int size;		// What is the size scale of the figure?

	public HangFigure(int x, int y, int sz)
	{
		xLoc = x;
		yLoc = y;
		size = sz;
		chunks = new Shape[7];
		for (int i = 0; i < chunks.length; i++)
			chunks[i] = null;
		numChunks = 0;
	}
	
	// Add a new chunk to the figure.  Note that the chunks differ, so everyone's favorite
	// control structure is used to determine which chunk to draw at each step.  The size
	// variable is used to scale the figure.  Once all of the chunks have been generated,
	// the switch turns into a "no-op"
	public void addChunk()
	{
		switch (numChunks)
		{
			case 0:
				chunks[numChunks++] = new Ellipse2D.Double(xLoc, yLoc, size, size);
				break;
			case 1:
				chunks[numChunks++] = new Line2D.Double(xLoc + size/2, yLoc + size, xLoc + size/2, yLoc + 2*size);
				break;
			case 2:
				chunks[numChunks++] = new Line2D.Double(xLoc + size/2, yLoc + 3*size/2, xLoc, yLoc + size);
				break;
			case 3:
				chunks[numChunks++] = new Line2D.Double(xLoc + size/2, yLoc + 3*size/2, xLoc + size, yLoc + size);
				break;
			case 4:
				chunks[numChunks++] = new Line2D.Double(xLoc + size/2, yLoc + 2*size, xLoc, yLoc + 3*size);
				break;
			case 5:
				chunks[numChunks++] = new Line2D.Double(xLoc + size/2, yLoc + 2*size, xLoc + size, yLoc + 3*size);
				break;
			case 6:
				chunks[numChunks++] = new Ellipse2D.Double(xLoc + size / 4, yLoc + 3*size/5, size/2, size/4);
				break;
		}
	}
	
	// Check to see if the Figure is complete or not
	public boolean isComplete()
	{
		return numChunks == chunks.length;
	}

	// This method will draw the figure to a graphical context.  Note that only non-null
	// values are drawn and that the predefined draw() method within the Graphics2D class
	// is used to draw the actual chunks.  The draw() method in Graphics2D can draw any 
	// figure that implements the Shape interface.  For more info, look up Graphics2D and
	// Shape in the Java API
	public void draw(Graphics2D g)
	{
		for (int i = 0; i < numChunks; i++)
		{
			if (chunks[i] != null)
			{
				g.draw(chunks[i]);
			}
		}
	}
}