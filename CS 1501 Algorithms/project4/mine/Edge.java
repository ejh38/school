/* Zach Sadler
 * zps6@pitt.edu
 * Project 4
 * 
 * Simple wrapper
 */
public class Edge {

	public Vertex u;
	public Vertex v;
	
	public double length;
	
	public Edge(Vertex from, Vertex to) {
		u = from;
		v = to;
		// distance formula son!!
		length = from.distance(to);
	}
	
	public String toString() {
		return new String("Edge from " + u.toString() + " to " + v.toString());
	}
	
}
