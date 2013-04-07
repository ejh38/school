/* Zach Sadler
 * zps6@pitt.edu
 * Project 4
 * 
 * Where I draw and also handle keyboard input
 */

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.ConcurrentModificationException;
import javax.swing.JPanel;


public class DrawPanel extends JPanel{

	int pixelWidth;
	int pixelHeight;
	ArrayList<Vertex> verts;
	public ArrayList<Edge> mst;
	public ArrayList<Edge> tour;
	
	// toggles
	public boolean drawVerts = true;
	public boolean drawMST = true;
	public boolean drawTour = true;
	
	InputHandler handler;
	
	public DrawPanel(int pixelWidth, int pixelHeight, ArrayList<Vertex> verts, ArrayList<Edge> edges, ArrayList<Edge> tour) {
		this.pixelHeight = pixelHeight;
		this.pixelWidth = pixelWidth;
		this.verts = verts;
		mst = edges;
		this.tour = tour;
		
		// this lets us do keyboard input
		handler = new InputHandler();
		addKeyListener(handler);
		this.setFocusable(true);
		this.grabFocus();
		
		// size itself appropriately
		setPreferredSize(new Dimension(pixelWidth, pixelHeight));
	}
	
	// paint that shit!
	public void paintComponent(Graphics g) {
	    super.paintComponent(g);
	    g.setColor(Color.white);	// white background
	    g.fillRect(0,0,pixelWidth,pixelHeight);
	    
	    g.setColor(Color.blue);	// blue squares
	    
	    try {
	    
	    	// if toggled
	    	if (drawVerts) {
			    for (Vertex v : verts) {
			    	// paint the home city green
			    	if (v.id == 0) {
			    		g.setColor(Color.GREEN);
			    		g.fillRect((int)(v.x*pixelWidth - 4), (int)(v.y*pixelHeight - 4), 8, 8);
			    		g.setColor(Color.blue);	// blue squares		
			    	}
			    	// and the rest slightly smaller
			    	else {
			    		g.fillRect((int)(v.x*pixelWidth - 2), (int)(v.y*pixelHeight - 2), 4, 4);
			    	}
			    }
	    	}

	    	// if toggled
		    if (drawMST) {
			    g.setColor(Color.black);	// black lines
			    for (Edge e : mst) {
			    	g.drawLine((int)(e.u.x*pixelWidth), (int)(e.u.y*pixelHeight), (int)(e.v.x*pixelWidth), (int)(e.v.y*pixelHeight));
			    }
		    }

		    // if toggled
		    if (drawTour) {
			    g.setColor(Color.red);	// black lines
			    for (Edge e : tour) {
			    	g.drawLine((int)(e.u.x*pixelWidth), (int)(e.u.y*pixelHeight), (int)(e.v.x*pixelWidth), (int)(e.v.y*pixelHeight));
			    }
		    }
	    
	    } catch (ConcurrentModificationException e) {
	    	// do nothing, not an issue
	    }
	    
	}
	
	// very simple, just toggles the toggles 
	private class InputHandler extends KeyAdapter
	{
	    public void keyPressed(KeyEvent e) 
		{
	    	if (e.getKeyCode() == KeyEvent.VK_1) {
	    		drawVerts = !drawVerts;
	    	}
	    	if (e.getKeyCode() == KeyEvent.VK_2) {
	    		drawMST = !drawMST;
	    	}
	    	if (e.getKeyCode() == KeyEvent.VK_3) {
	    		drawTour = !drawTour;
	    	}
		}
	}

	
}
