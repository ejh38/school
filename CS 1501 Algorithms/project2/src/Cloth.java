import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;

public class Cloth extends JPanel {

	int width;
	int height;
	int pixels;
	Color BACKGROUND = Color.yellow ;
	Color FOREGROUND = Color.black ;	
	
	ArrayList<Cut> cuts = new ArrayList<Cut>(10);
	
	public Cloth(int w, int h, int p) {
		width = w;
		height = h;
		pixels = p;
	}
	
	public void drawCut(Cut a) {
		cuts.add(a);
		this.repaint();
	}
	
	public void paintComponent(Graphics g) {
	    super.paintComponent(g) ;
	    g.setColor(BACKGROUND) ;
	    g.fillRect(0,0,width*pixels,height*pixels) ;
	    g.setColor(FOREGROUND) ;
	   
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
	   
	}
	
	public void drawGarment(Garment a) {
		// do the drawing
	}
	
}
