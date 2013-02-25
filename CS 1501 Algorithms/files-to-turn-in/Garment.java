/********************************
 * Zach Sadler
 * zps6@pitt.edu
 * Project 2
 * Cloth Cutting & Dynamic Programming
 ********************************/

public class Garment {

	int pos_x;
	int pos_y;
	String name;
	
	int width;
	int height;

	public Garment(int px, int py, String n) {
		pos_x = px;
		pos_y = py;
		name = n;
	}
	
	public void setDimensions(int width, int height) {
		this.width = width;
		this.height = height;
	}
	
	public String toString() {
		return "[" + name + ", " + pos_x + ", " + pos_y + "]";
	}
	
}
