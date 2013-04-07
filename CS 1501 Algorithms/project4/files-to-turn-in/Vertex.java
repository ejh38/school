/* Zach Sadler
 * zps6@pitt.edu
 * Project 4
 * 
 * Simple wrapper for coord's and a list of adjacent vertices
 */

import java.util.ArrayList;

public class Vertex {
	
	// the coords of the city
	public double x;	
	public double y;
	
	// for depth-first searching
	public int id;
	public ArrayList<Integer> adjacentTo;
	
	public Vertex(float X, float Y, int id) {
		x = X;
		y = Y;
		this.id = id;
		adjacentTo = new ArrayList<Integer>();
	}
	
	// simple distance formula
	public double distance(Vertex to) {
		return Math.sqrt((this.x - to.x)*(this.x - to.x) + (this.y - to.y)*(this.y - to.y));
	}
	
	public String toString() {
		return new String(x + ", " + y);
	}
	
	public void addAdjacency(int addThis) {
		adjacentTo.add(addThis);
	}
	
}
