/* Zach Sadler
 * zps6@pitt.edu
 * Project 4
 * 
 * Test driver to demonstrate the MST and tour.
 */

import javax.swing.JFrame;

public class DemonstrateTSP  {
	public static void main(String [] args) {
		if (args.length != 1) {
			System.out.println("Invalid input!");
			System.out.println("I need a single command-line argument for number of vertices.");
			System.exit(0);
		}
		
		// some instructions on the terminal in case people don't README
		System.out.println("Zach Sadler - project4 - zps6" + 
						   "\nThe green city is the home city.\n" +
						   "Controls:" + "\n'1' - toggle City visibility" +
						   "\n'2' - toggle MST visibility" +
							"\n'3' - toggle Tour visibility");
		
		// make a new solver with size equal to the command line argument
		EuclideanTSP solver = new EuclideanTSP(Integer.parseInt(args[0]));
		solver.solveMST();
		solver.solveTour();

		// setup the GUI
		JFrame frame = new JFrame("Zach Sadler - zps6 - Project 4") ;
	    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE) ;
		DrawPanel drawIt = new DrawPanel(solver.PIXELS_WIDTH, solver.PIXELS_HEIGHT, solver.finishedVerts, 
																		solver.edges, solver.getTourEdges());
	    frame.add(drawIt) ;
	    frame.pack() ;
		frame.setLocation(100, 100);
	    frame.setVisible(true) ;
	    
	    // because your keyboard presses will update what needs to be drawn
	    while (true) {
	    	frame.repaint();
	    }
	}
}
