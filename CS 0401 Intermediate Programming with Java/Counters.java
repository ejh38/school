// CS 0401 Fall 2011
// This handout includes some additional useful graphical features.

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Counters
{
	private JFrame theWindow;

	// A JPanel is similar to a JFrame, except it does not have title
	// bar.  Panels are often used to subdivide windows, as we are doing
	// here.
	private JPanel topPanel;
	private JPanel bottomPanel;

	// These declarations are similar to those in other handouts
	private JButton b1, b2, b3, b4;
	private JLabel c1, c2, c3, total;

	// Sometimes it is not clear if a variable should be a method variable
	// or an instance variable.  If the variable needs to be accessed directly
	// in more than one method, it cannot be a method variable.  However, it
	// can still be an instance variable even if it is accessed in only one
	// method (mostly for clarity to the reader of the program).  Below is an
	// example of each case.  Both thePane and theListener are only accessed
	// directly in the constructor.  However, thePane is an instance variable
	// and theListener is a method variable.
	private Container thePane;
	private int count1, count2, count3, sum;
	
	public Counters()
	{
		// With two Panels in our window, we can now set the layout
		// for each one differently.  Our "top" panel has the GridLayout
		// shown below and our "bottom" panel has a different GridLayout.
		topPanel = new JPanel();
		topPanel.setLayout(new GridLayout(2,3));
		b1 = new JButton("PUSH 1");
		b2 = new JButton("PUSH 2");
		b3 = new JButton("PUSH 3");
		CountListener theListener = new CountListener();  // Since we link our
			// CountListener to our buttons, it does not matter that the method
			// variable will go away after the method ends -- the object
			// survives and can still be used.
		b1.addActionListener(theListener);
		b2.addActionListener(theListener);
		b3.addActionListener(theListener);
		
		// Add the buttons to the panel just like we added them to the
		// content pane of the JFrame in earlier handouts
		topPanel.add(b1);
		topPanel.add(b2);
		topPanel.add(b3);
	
		// In order to center the data in our label, we use the
		// setHorizontalAlignment method as shown below.  For more
		// information on this, see JLabel in the API.
		c1 = new JLabel("0");
		c1.setHorizontalAlignment(SwingConstants.CENTER);
		c2 = new JLabel("0");
		c2.setHorizontalAlignment(SwingConstants.CENTER);
		c3 = new JLabel("0");
		c3.setHorizontalAlignment(SwingConstants.CENTER);
		topPanel.add(c1);
		topPanel.add(c2);
		topPanel.add(c3);

		count1 = 0; count2 = 0; count3 = 0;
		sum = 0;

		// Set up the labels and button in the bottom panel
		bottomPanel = new JPanel();
		bottomPanel.setLayout(new GridLayout(2, 1));
		total = new JLabel("0");
		total.setHorizontalAlignment(SwingConstants.CENTER);
		//total.setFont(new Font("TimesRoman", Font.BOLD, 50));

		b4 = new JButton("Click to Quit");
		// Note that we are not even saving the listener object below
		// in a variable.  We don't actually need a separate variable
		// since it is being attached to the JButton -- we have access
		// to it through the JButton.
		b4.addActionListener(new QuitListener());
		bottomPanel.add(total);
		bottomPanel.add(b4);
		
		theWindow = new JFrame("Counting with Buttons");
		theWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		thePane = theWindow.getContentPane();

		// Now the components are placed using BorderLayout.  This
		// divides the window into 5 sections, as discussed in the
		// text
		thePane.add(topPanel, BorderLayout.NORTH);
		thePane.add(bottomPanel, BorderLayout.SOUTH);
		theWindow.pack();
		theWindow.setVisible(true);
	}

	// We are again using an inner class here so that we can access
	// components from within the listener.  Note the different ways
	// of getting the int counts into the String of the label
	class CountListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if (e.getSource() == b1)
			{
				count1++;
				c1.setText(String.valueOf(count1));
			}
			else if (e.getSource() == b2)
			{
				count2++;
				c2.setText("" + count2);
			}
			else if (e.getSource() == b3)
			{
				count3++;
				c3.setText(String.valueOf(count3));
			}
			sum = count1 + count2 + count3;
			total.setText("" + sum);
		}
	}

	class QuitListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			System.exit(0);
		}
	}

	public static void main(String [] args)
	{
		new Counters();
	}
}

