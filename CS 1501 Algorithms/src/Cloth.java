/********************************
 * Zach Sadler
 * zps6@pitt.edu
 * Project 2
 * Cloth Cutting & Dynamic Programming
 ********************************/

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.ConcurrentModificationException;
import javax.swing.JPanel;

public class Cloth extends JPanel {

	int width;		// width of the cloth
	int height;		// and the height!
	int pixels;		// offsets to multiply the unit cloth by
	
	ArrayList<Cut> cuts = new ArrayList<Cut>();
	ArrayList<Garment> garments = new ArrayList<Garment>();
	
	public Cloth(int w, int h, int p) {
		width = w;
		height = h;
		pixels = p;
		setPreferredSize(new Dimension(width*pixels, height*pixels));
	}
	
	// kind of funky - adds the cut to the ArrayList
	// and then repaints the scene
	public void drawCut(Cut a) {
		cuts.add(a);
		this.repaint();
	}
	
	// also funky, same deal as drawcut
	public void drawGarment(Garment a) {
		garments.add(a);
		this.repaint();
	}
	
	// this is what JPanel wants, so we give it to it
	public void paintComponent(Graphics g) {
	    super.paintComponent(g);
	    g.setColor(Color.gray);	// yellow background
	    g.fillRect(0,0,width*pixels,height*pixels);
	    g.setColor(Color.black);	// black lines
	    
	    try {
		    for (Cut c: cuts) {
		    	if (c.vertical) {
		    		g.drawLine( pixels*c.absX + pixels*c.position, 
		    				    pixels*c.absY, 
		    					pixels*c.absX + pixels*c.position, 
		    					pixels*c.absY + pixels*c.y);	
		    	}
		    	else {
		    		g.drawLine( pixels*c.absX, 
		    				    pixels*c.absY + pixels*c.position, 
		    				    pixels*c.absX + pixels*c.x, 
		    				    pixels*c.absY + pixels*c.position);	
		    	}
		    }
		    
		    for (Garment rect: garments) { 
		    	if (rect != null) {
				    g.setColor(Color.orange);		// blue garments
			    	g.fillRect(pixels*rect.pos_x + 1, pixels*rect.pos_y + 1, pixels*rect.width - 1, pixels*rect.height - 1);
				    g.setColor(Color.black);	// white text
			    	g.drawString(rect.name, pixels*rect.pos_x + pixels/2, pixels*rect.pos_y + pixels/2);
		    	}
		    }
	    } catch (ConcurrentModificationException e) {
	    	// do nothing, because we're fine
	    	// System.out.println("Nothing to see here, move along.");
	    }
	   
	}

}
