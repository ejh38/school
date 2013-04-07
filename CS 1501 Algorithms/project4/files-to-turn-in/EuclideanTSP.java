/* Zach Sadler
 * zps6@pitt.edu
 * Project 4
 * 
 * This guy does all the walk.
 */

import java.util.ArrayList;
import java.util.Random;

public class EuclideanTSP {
	
	public int PIXELS_WIDTH = 720;			// for the GUI panel
	public int PIXELS_HEIGHT = 720;			// change these all you want
	
	int numberOfVertices;
	Random rng;
	boolean [] marked;						// for the DFS
	double length1, length2;				// we output these
	
	
	
	ArrayList<Vertex> vertices;				// this is temporary- is emptied by end
	public ArrayList<Vertex> finishedVerts;	// the finalized list of verts as we've visited them
	public ArrayList<Edge> edges;			// the MST
	public ArrayList<Vertex> tour;			// the MST-walk
	
	// sets up the vertices and allocates space
	public EuclideanTSP(int numberOfVerts) {
		numberOfVertices = numberOfVerts;
		
		// no null pointers for us!
		vertices = new ArrayList<Vertex>(numberOfVertices);
		finishedVerts = new ArrayList<Vertex>(numberOfVertices);
		edges = new ArrayList<Edge>(numberOfVertices - 1);
		rng = new Random(System.nanoTime());					// seed from System time
		tour = new ArrayList<Vertex>(numberOfVertices - 1);
		marked = new boolean[numberOfVertices];
		
		// not sure if necessary, but why not?
		for (int i = 0; i < numberOfVertices; i++) {
			marked[i] = false;
		}
		
		Vertex temp;
		// randomly generate the x,y coords for each vertex
		for (int i = 0; i < numberOfVertices; i++) {
			temp = new Vertex(rng.nextFloat(), rng.nextFloat(), i);
			vertices.add(temp);
		}
	}
	
	// finds the MST
	public void solveMST() {
		// pick an arbitrary vertex and add it to the finished tree
		int arbitraryNum = rng.nextInt(numberOfVertices);
	  	finishedVerts.add(vertices.get(arbitraryNum));
	  	vertices.remove(arbitraryNum);
	  	
	  	// temporary variables
	  	Vertex toAdd = null;
	  	Vertex addTo = null;
	  	double min = Double.MAX_VALUE;
	  	// while we still have vertices to add
	  	while (finishedVerts.size() != numberOfVertices) {
	  		min = Double.MAX_VALUE;
	  		toAdd = null;
	  		addTo = null;
	  		
	  		// PRIM!!!
	  		for (Vertex vert : vertices) {
	  			for (Vertex to : finishedVerts) {
	  				if (vert.distance(to) < min) {
	  					min = vert.distance(to);
	  					toAdd = vert;
	  					addTo = to;
	  				}
	  			}
	  		}
	  		
	  		// this is for our DFS
	  		toAdd.addAdjacency(addTo.id);
	  		addTo.addAdjacency(toAdd.id);
	  		
	  		finishedVerts.add(toAdd);
	  		vertices.remove(toAdd);						// to speed up future loops
	  		Edge tempEdge = new Edge(toAdd, addTo);
	  		edges.add(tempEdge);
	  	}
	  	
	  	// print out the length of the MST
	  	double length = 0;
	  	for (Edge e : edges) {
	  		length += e.length;
	  	}
	  	length1 = length;
	  	System.out.println("Total weight is: " + length);
	
	}
	
	// just a little lookup, would be more optimal if I just used a hash table
	public Vertex getId(int id) {
		for (Vertex v : finishedVerts) {
			if (v.id == id) {
				return v;
			}
		}
		
		System.out.println("Didn't find the id " + id); 
		return null;
	}
	
	// this is called, which calls the recursive method
	public void solveTour() {
		tour.add(getId(0));
		solveTour(0);
	}
	
	// very simple, the DFS algorithm
	public void solveTour(int vertex) {
		marked[vertex] = true;
		for (int w : getId(vertex).adjacentTo) {
			if (!marked[w]) {
				solveTour(w);
				tour.add(getId(w));
			}
		}		
	}
	
	// returns an ArrayList to draw and also prints out the length
	public ArrayList<Edge> getTourEdges() {
		ArrayList<Edge> blah = new ArrayList<Edge>();
		for (int i = 0; i + 1 < tour.size(); i++) {
			blah.add(new Edge(tour.get(i), tour.get(i+1)));
		}
		blah.add(new Edge(tour.get(tour.size() - 1), tour.get(0)));

		double length = 0;
	  	for (Edge e : blah) {
	  		length += e.length;
	  	}
	  	System.out.println("Tour length is: " + length);
	  	length2 = length;
	  	System.out.printf("Tour length is %3f times the MST.\n", (length2/length1));
		return blah;
	}
	
}
