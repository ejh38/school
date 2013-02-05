// CS 0401 Fall 2011
// Help Program for Assignment 4
// This program demonstrates use of the HangFigure class, which you must
// use in your graphical version of the HangMan game.  See more comments
// below.
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;

public class A4Help
{
	// Declare some instance variables
	private JFrame theFrame;
	private MyPanel drawPanel;  // JPanel to "hold" the figure.  See comments in the
								// MyPanel class below

	private JPanel buttonPanel;	// JPanel to hold the buttons
	
	private JButton button1, button2;
	private HangFigure f;
	private Random R;

	public A4Help()
	{
		R = new Random();
		theFrame = new JFrame("Assignment 4 Help Program");
		drawPanel = new MyPanel(300, 300);
		buttonPanel = new JPanel();
		button1 = new JButton("New Figure");
		button2 = new JButton("Add Chunk");
		// We need a figure before we can add a chunk, so set the "Add Chunk"
		// button to be disabled.
		button2.setEnabled(false);
		MyListener ml = new MyListener();
		button1.addActionListener(ml);
		button2.addActionListener(ml);
		buttonPanel.setLayout(new GridLayout(1, 2));
		buttonPanel.add(button1);
		buttonPanel.add(button2);
		
		theFrame.add(buttonPanel, BorderLayout.NORTH);
		theFrame.add(drawPanel, BorderLayout.CENTER);
		theFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		theFrame.pack();
		theFrame.setVisible(true);
	}

	class MyListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			// For button1, create a new randomly placed HangFigure
			// and draw the first chunk, then repaint the panel.  I
			// am positioning the figure so it will fit in the window.
			if (e.getSource() == button1)
			{
				int sz = R.nextInt(80);
				int x = R.nextInt(drawPanel.getWidth()-sz);
				int y = R.nextInt(drawPanel.getHeight()-3*sz);
				f = new HangFigure(x, y, sz);
				f.addChunk();
				button2.setEnabled(true);
				drawPanel.repaint();  	// The repaint() method requests the system to
										// refresh the panel.  This implicitly will
						// generate a call to the paintComponent() method for the panel.
						// So, we put all the code for drawing into that method.  See the
						// details in the MyPanel class below.
			}
			else
			{
			// For button2, first make sure f is not null (to avoid
			// NullPointerException), then draw the next chunk and
			// repaint the panel.  If the figure is complete, disable the
			// Add Chunk button.
				if (f != null)
				{
					f.addChunk();
					if (f.isComplete())
						button2.setEnabled(false);
					drawPanel.repaint();
				}
			}
		}
	}

	// This inner class is a subclass of JPanel.  It is used to draw the figure so
	// that the graphics do not interfere with the components (ex: buttons) in the
	// JFrame.
	class MyPanel extends JPanel
	{
		private int width, height;
		public MyPanel(int w, int h)
		{
			width = w;
			height = h;
		}

		// This method is implicitly called through the JFrame to see how much
		// space the JPanel needs.  Otherwise, the JPanel will be given a default,
		// very small size.
		public Dimension getPreferredSize()
		{
			return new Dimension(width, height);
		}

		// This method is implictly called every time the panel must be refreshed.
		// It will happen automatically if the window is minimized and then opened
		// again, or if it is covered and then exposed.  We can also request that it
		// be done at other times by calling the repaint() method, as shown above.
		public void paintComponent (Graphics g) // Pass the graphics object
												// to the Panel so it can
												// draw its shapes
		{
			super.paintComponent(g);         // don't forget this line!
			Graphics2D g2d = (Graphics2D) g;
			if (f != null)		// Note that we are calling the draw() method in
				f.draw(g2d);	// in the HangFigure class and passing the
								// Graphics2D object into it.  This way, our JPanel
						// does not have to know the specifics of how to draw the
						// figure -- it only has to know that the figure has a
						// draw() method.  See the draw() method in HangFigure for
						// more details.
		}
	}

	public static void main(String [] args)
	{
		new A4Help();
	}
}
