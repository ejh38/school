/********************************
 * Zach Sadler
 * zps6@pitt.edu
 * Project 2
 * Cloth Cutting & Dynamic Programming
 ********************************/

public class Cut {

	boolean vertical;
	int position;
	int x;
	int y;
	int absX;
	int absY;
	
	
	// takes the cloth that it performed the cut on,
	// a boolean for vertical or horizontal
	// and where on the cloth it belongs
	// position is an x coordinate for vertical and a y coordinate for horizontal
	public Cut(boolean vert, int pos, int x, int y, int absX, int absY) {
		vertical = vert;
		position = pos;
		this.x = x;
		this.y = y;
		this.absX = absX;
		this.absY = absY;
	}
	
	public String toString() {
		if (vertical) {
			return "vertical " + position + " on " + x + " by " + y;
		}
		else {
			return "horizontal " + position+ " on " + x + " by " + y; 	
		}
	}
}
