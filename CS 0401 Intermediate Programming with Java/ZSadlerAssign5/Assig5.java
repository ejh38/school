// CS 401 Fall 2011
// Zach Sadler
// Assignment 5
// Holiday greeting card

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.awt.print.*;

// Create enum types that will be useful in the program
enum Figures {TREE,SNOWFLAKE,GREETING,SNOWMAN,PRESENT,HOUSE};
enum Mode {NONE,DRAW,SELECTED,MOVING,PASTING};

// Code extracted from Oracle Java Example programs.  See link below for full code:
// http://docs.oracle.com/javase/tutorial/2d/printing/examples/PrintUIWindow.java
class thePrintPanel implements Printable
{
	JPanel panelToPrint;
	
	public int print(Graphics g, PageFormat pf, int page) throws
                                                        PrinterException
    {
        if (page > 0) { /* We have only one page, and 'page' is zero-based */
            return NO_SUCH_PAGE;
        }

        /* User (0,0) is typically outside the imageable area, so we must
         * translate by the X and Y values in the PageFormat to avoid clipping
         */
        Graphics2D g2d = (Graphics2D)g;
        g2d.translate(pf.getImageableX(), pf.getImageableY());

        /* Now print the window and its visible contents */
        panelToPrint.printAll(g);

        /* tell the caller that this page is part of the printed document */
        return PAGE_EXISTS;
    }
    
    public thePrintPanel(JPanel p)
    {
    	panelToPrint = p;
    }
}

public class Assig5
{	
	private ShapePanel drawPanel;
	private JPanel buttonPanel;
	private JButton draw;
	private JRadioButton makeTree, makeFlake, makeGreet;
	private JRadioButton makeHouse, makeSnowman, makePresent;
	private ButtonGroup shapeGroup;
	private Figures currShape;
	private JLabel msg;
	private JMenuBar theBar;
	private JMenu fileMenu, editMenu;
	private JMenuItem menuNew, menuOpen, menuSave, menuSaveAs, menuPrint, menuExit;
	private JMenuItem menuCut, menuCopy, menuPaste;
	private JPopupMenu popper;
	private JMenuItem delete, resize;
	private JFrame theWindow;
	
	// This ArrayList is used to store the shapes in the program.
	// It is specified to be of type MyShape, so objects of any class
	// that implements the MyShape interface can be stored in here.
	// See Section 8.13 in your text for more info on ArrayList.
	private ArrayList<MyShape> shapeList;	
	private MyShape newShape;
	
	private JFileChooser fc;
	
	private boolean saved, edited, copying;
	private PrintWriter txtFile;
	private File file;
	private String temp; //copiedShape;
	private String [] tempAr, copyInfo;
	private Scanner txtScan;
	private int selectedIndex = -1, selindex;
	private MyShape tempShape, copiedShape;
	private Mode mode;   // Keep track of the current Mode

	
	public A5Help()
	{
		drawPanel = new ShapePanel(720, 576);
		buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridLayout(3, 3));

		draw = new JButton("Draw");

		ButtonHandler bhandler = new ButtonHandler();
		draw.addActionListener(bhandler);

		buttonPanel.add(draw);
		msg = new JLabel("");
		buttonPanel.add(msg);
		
		// this is just for formatting to keep it a 3x3 grid
		buttonPanel.add(new JLabel(""));

		makeTree = new JRadioButton("Tree", false);
		makeFlake = new JRadioButton("Snowflake", true);
		makeGreet = new JRadioButton("Greeting", false);
		makeSnowman = new JRadioButton("Snowman", false);
		makePresent = new JRadioButton("Present", false);
		makeHouse = new JRadioButton("House", false);

		RadioHandler rhandler = new RadioHandler();
		makeTree.addItemListener(rhandler);
		makeFlake.addItemListener(rhandler);
		makeGreet.addItemListener(rhandler);
		makeSnowman.addItemListener(rhandler);
		makePresent.addItemListener(rhandler);
		makeHouse.addItemListener(rhandler);

		buttonPanel.add(makeFlake);
		buttonPanel.add(makeTree);
		buttonPanel.add(makeGreet);
		buttonPanel.add(makeSnowman);
		buttonPanel.add(makePresent);
		buttonPanel.add(makeHouse);

		// A ButtonGroup allows a set of JRadioButtons to be associated
		// together such that only one can be selected at a time
		shapeGroup = new ButtonGroup();
		shapeGroup.add(makeFlake);
		shapeGroup.add(makeTree);
		shapeGroup.add(makeGreet);
		shapeGroup.add(makeSnowman);
		shapeGroup.add(makePresent);
		shapeGroup.add(makeHouse);

		currShape = Figures.SNOWFLAKE;
		drawPanel.setMode(Mode.NONE);

		theWindow = new JFrame("Zach Sadler - Assignment 5");
		Container c = theWindow.getContentPane();
		drawPanel.setBackground(Color.lightGray);
		c.add(drawPanel, BorderLayout.NORTH);
		c.add(buttonPanel, BorderLayout.SOUTH);

		// Note how the menu is created.  First we make a JMenuBar, then
		// we put a JMenu in it, then we put JMenuItems in the JMenu.  We
		// can have multiple JMenus if we like.  JMenuItems generate
		// ActionEvents, just like JButtons, so we just have to link an
		// ActionListener to them.
		theBar = new JMenuBar();
		theWindow.setJMenuBar(theBar);
		fileMenu = new JMenu("File");
		theBar.add(fileMenu);

		// everything for the 'file' menu
		menuNew = new JMenuItem("New");
		menuOpen = new JMenuItem("Open");
		menuSave = new JMenuItem("Save");
		menuSaveAs = new JMenuItem("Save As");
		menuPrint = new JMenuItem("Print");
		menuExit = new JMenuItem("Exit");
		fileMenu.add(menuNew);
		fileMenu.add(menuOpen);
		fileMenu.add(menuSave);
		fileMenu.add(menuSaveAs);
		fileMenu.add(menuPrint);
		fileMenu.add(menuExit);
		menuNew.addActionListener(bhandler);
		menuOpen.addActionListener(bhandler);
		menuSave.addActionListener(bhandler);
		menuSaveAs.addActionListener(bhandler);
		menuPrint.addActionListener(bhandler);
		menuExit.addActionListener(bhandler);
		
		
		// everything for the 'edit' menu
		editMenu = new JMenu("Edit");
		theBar.add(editMenu);
		
		menuCut = new JMenuItem("Cut");
		menuCopy = new JMenuItem("Copy");
		menuPaste = new JMenuItem("Paste");
		editMenu.add(menuCut);
		editMenu.add(menuCopy);
		editMenu.add(menuPaste);
		menuCut.addActionListener(bhandler);
		menuCopy.addActionListener(bhandler);
		menuPaste.addActionListener(bhandler);
		menuCut.setEnabled(false);
		menuCopy.setEnabled(false);
		menuPaste.setEnabled(false);

		// JPopupMenu() also holds JMenuItems.  To see how it is actually
		// brought out, see the mouseReleased() method in the ShapePanel class
		// below.
		popper = new JPopupMenu();
		delete = new JMenuItem("Delete");
		resize = new JMenuItem("Resize");
		delete.addActionListener(bhandler);
		resize.addActionListener(bhandler);
		popper.add(delete);
		popper.add(resize);
		
		theWindow.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		theWindow.pack();
		theWindow.setVisible(true);
	}

	public static void main(String [] args)
	{
		new A5Help();
	}

	// See Section 7.5 for information on JRadioButtons.  Note that the
	// text uses ActionListeners to handle JRadioButtons.  Clicking on
	// a JRadioButton actually generates both an ActionEvent and an
	// ItemEvent.  I am using the ItemEvent here.  To handle the event,
	// all I am doing is changing a state variable that will affect the
	// MouseListener in the ShapePanel.
	private class RadioHandler implements ItemListener
	{
		public void itemStateChanged(ItemEvent e)
		{
			if (e.getSource() == makeTree)
				currShape = Figures.TREE;
			else if (e.getSource() == makeFlake)
				currShape = Figures.SNOWFLAKE;
			else if (e.getSource() == makeGreet)
				currShape = Figures.GREETING;
			else if (e.getSource() == makeSnowman)
				currShape = Figures.SNOWMAN;
			else if (e.getSource() == makePresent)
				currShape = Figures.PRESENT;
			else if (e.getSource() == makeHouse)
				currShape = Figures.HOUSE;
		}
	}

	// Note how the draw button and moveIt menu item are handled 
	// -- we again simply set the state in the panel so that the mouse will 
	// actually do the work.  The state needs to be set back in the mouse
	// listener.
	private class ButtonHandler implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if (e.getSource() == draw)
			{
				drawPanel.setMode(Mode.DRAW);
				msg.setText("Use mouse to position shape.");
				draw.setEnabled(false);
			}
			else if (e.getSource() == delete)
			{
				boolean ans = drawPanel.deleteSelected();
				if (ans)
				{
					msg.setText("Shape deleted.");
					drawPanel.repaint();
				}
			}
			else if (e.getSource() == resize)
			{
				int newsize = Integer.parseInt(JOptionPane.showInputDialog("Resize to what? (enter an integer)"));					
				boolean answer = drawPanel.resizeSelected(newsize);
				if (answer)
				{
					msg.setText("Shape resized.");
					drawPanel.repaint();
				}
			}
			
			else if (e.getSource() == menuNew)
			{
				if (edited)
				{
					if (JOptionPane.showConfirmDialog(null, "You have unsaved changes.\nWould you like to save?",																  "Save Changes?", JOptionPane.YES_NO_OPTION) == 0)
					{
						if (!saved)
						{
							
							temp = JOptionPane.showInputDialog("Enter your file name");
							if (temp != null)
							{
								file = new File(temp);
								saved = true;
							}
						} 
						if (saved)
						{
							try
							{
								txtFile = new PrintWriter(new FileOutputStream(file, false));		
								for (MyShape s : shapeList)
									txtFile.println(s.saveData());
							}
							catch (FileNotFoundException eee)
							{
								msg.setText("Got an exception here");
							}
							edited = false;
							txtFile.close();
						}	
					}
						
				}
				shapeList = new ArrayList<MyShape>();
				drawPanel.repaint();
				edited = false;
				saved = false;			
			}
					
			else if (e.getSource() == menuOpen)
			{
				if (edited)
				{
					if (JOptionPane.showConfirmDialog(null, "You have unsaved changes.\nWould you like to save?",																  "Save Changes?", JOptionPane.YES_NO_OPTION) == 0)
					{
						if (!saved)
						{
							
							temp = JOptionPane.showInputDialog("Enter your file name");
							if (temp != null)
							{
								file = new File(temp);
								saved = true;
							}
						} 
						if (saved)
						{
							try
							{
								txtFile = new PrintWriter(new FileOutputStream(file, false));		
								for (MyShape s : shapeList)
									txtFile.println(s.saveData());
							}
							catch (FileNotFoundException eee)
							{
								msg.setText("Got an exception here");
							}
							edited = false;
							txtFile.close();
						}	
					}
						
				}
				fc = new JFileChooser();		
				int returnVal = fc.showOpenDialog(theWindow);

     		    if (returnVal == JFileChooser.APPROVE_OPTION) 
     		    {
        	    	file = fc.getSelectedFile();
        			shapeList = new ArrayList<MyShape>();
        			try
        			{
	        			txtScan = new Scanner(file);
        			}
        			catch (FileNotFoundException eeeee)
        			{}
 	      			while (txtScan.hasNextLine())
        			{
        				temp = txtScan.nextLine();
						tempAr = temp.split(":"); 
        				if (tempAr[0].equals("Tree"));
	        				newShape = new Tree(Integer.parseInt(tempAr[1]), Integer.parseInt(tempAr[2])
	        										, Integer.parseInt(tempAr[3]));
	        			if (tempAr[0].equals("House"))
	        				newShape = new House(Integer.parseInt(tempAr[1]), Integer.parseInt(tempAr[2])
	        										, Integer.parseInt(tempAr[3]));
	        			if (tempAr[0].equals("Snowman"))
	        				newShape = new Snowman(Integer.parseInt(tempAr[1]), Integer.parseInt(tempAr[2])
	        										, Integer.parseInt(tempAr[3]));
	        			if (tempAr[0].equals("Snowflake"))
	        				newShape = new Snowflake(Integer.parseInt(tempAr[1]), Integer.parseInt(tempAr[2])
	        										, Integer.parseInt(tempAr[3]));
	        			if (tempAr[0].equals("Present"))
	        				newShape = new Present(Integer.parseInt(tempAr[1]), Integer.parseInt(tempAr[2])
	        										, Integer.parseInt(tempAr[3]));
	        			if (tempAr[0].equals("Greeting"))
	        			{
	        				newShape = new Greeting(Integer.parseInt(tempAr[1]), Integer.parseInt(tempAr[2])
	        										, Integer.parseInt(tempAr[3]));
	        				((MyText) newShape).setText(tempAr[4]);
	        			}
	        			shapeList.add(newShape);
	        			drawPanel.repaint();
        			}
 		       		txtScan.close();
          	    	msg.setText("Succesfully loaded file");
          	    	saved = true;
          	    	edited = false;
	
        		} 
        		else 
        		{
					msg.setText("No file loaded");	
        		}
        	}
        	
        	
        	else if (e.getSource() == menuSave)
        	{
				if (edited)
				{
					if (!saved)
					{
						
						temp = JOptionPane.showInputDialog("Enter your file name");
						if (temp != null)
						{
							file = new File(temp);
							saved = true;
						}
					} 
					if (saved)
						try
						{
							txtFile = new PrintWriter(new FileOutputStream(file, false));		
							for (MyShape s : shapeList)
								txtFile.println(s.saveData());
						}
						catch (FileNotFoundException eee)
						{
							msg.setText("Got an exception here");
							edited = false;
							txtFile.close();
						}
								
				}
        	}
			
			else if (e.getSource() == menuSaveAs)
			{
				temp = JOptionPane.showInputDialog("Enter your file name");
				if (temp != null)
				{
					file = new File(temp);
					saved = true;
				try
				{
					txtFile = new PrintWriter(new FileOutputStream(file, false));		
					for (MyShape s : shapeList)
						txtFile.println(s.saveData());
					edited = false;
					txtFile.close();
				}
				catch (FileNotFoundException eee)
				{
					msg.setText("Got an exception here");
				}
				}
					
			}
			
			
			else if (e.getSource() == menuPrint)
			{
				Printable thePPanel = new thePrintPanel(drawPanel); 
			    PrinterJob job = PrinterJob.getPrinterJob();
         		job.setPrintable(thePPanel);
         		boolean ok = job.printDialog();
         		if (ok) 
         		{
             	 	try {
                  		job.print();
             		} 
             		catch (PrinterException ex) {
              		/* The job did not successfully complete */
             		}
             	}
            }
			else if (e.getSource() == menuExit)
			{
				if (edited)
				{
					if (JOptionPane.showConfirmDialog(null, "You have unsaved changes.\nWould you like to save?",																  "Save Changes?", JOptionPane.YES_NO_OPTION) == 0)
					{
						if (!saved)
						{
							
							temp = JOptionPane.showInputDialog("Enter your file name");
							if (temp != null)
							{
								file = new File(temp);
								saved = true;
							}
						} 
						if (saved)
						{
							try
							{
								txtFile = new PrintWriter(new FileOutputStream(file, false));		
								for (MyShape s : shapeList)
									txtFile.println(s.saveData());
							}
							catch (FileNotFoundException eee)
							{
								msg.setText("Got an exception here");
							}
							edited = false;
							txtFile.close();
						}	
					}
						
				}
				System.exit(0);
			}
		
			else if (e.getSource() == menuCopy)
			{
				String copyString = shapeList.get(selindex).saveData();
				copyInfo = copyString.split(":");
				copying = true;
				menuCopy.setEnabled(false);
				menuCut.setEnabled(false);
				menuPaste.setEnabled(true);
			}
			
			else if (e.getSource() == menuCut)
			{
				String copyString = shapeList.get(selindex).saveData();
				copyInfo = copyString.split(":");
				shapeList.remove(selindex);

				copying = true;
				drawPanel.repaint();
				menuCopy.setEnabled(false);
				menuCut.setEnabled(false);
				menuPaste.setEnabled(true);
				
			}
			
			else if (e.getSource() == menuPaste)
			{
				mode = Mode.PASTING;
				msg.setText("Click where you want to paste");
				draw.setEnabled(false);
				menuPaste.setEnabled(false);
			}
					
					
								
		}
	}

	// Here we are extending JPanel.  This way we can use all of the
	// properties of JPanel (including generating MouseEvents) and also
	// add new instance data and methods, as shown below.  Since this is
	// an inner class, it can access instance variables from the A5Help
	// class if necessary.
	private class ShapePanel extends JPanel
	{
		
		// These instance variables are used to store the desired size
		// of the panel
		private int prefwid, prefht;

		// Store index of the selected MyShape.  This allows the Shape
		// to be moved and updated.

		// Keep track of positions where mouse is moved on the display.
		// This is used by mouse event handlers when moving the shapes.
		private int x1, y1, x2, y2; 
		
		private boolean popped; // has popup menu been activated?

		public ShapePanel (int pwid, int pht)
		{
			shapeList = new ArrayList<MyShape>(); // create empty ArrayList
			selindex = -1;
		
			prefwid = pwid;	// values used by getPreferredSize method below
			prefht = pht;   // (which is called implicitly).  This enables
			// the JPanel to request the room that it needs.
			// However, the JFrame is not required to honor
			// that request.

			setOpaque(true);// Paint all pixels here (See API)

			setBackground(Color.lightGray);

			addMouseListener(new MyMouseListener());
			addMouseMotionListener(new MyMover());
			popped = false;
		}  // end of constructor

		// This class is extending MouseAdapter.  MouseAdapter is a predefined
		// class that implements MouseListener in a trivial way (i.e. none of
		// the methods actually do anything).  Extending MouseAdapter allows
		// a programmer to implement only the MouseListener methods that
		// he/she needs but still satisfy the interface (recall that to
		// implement an interface one must implement ALL of the methods in the
		// interface -- in this case I do not need 3 of the 5 MouseListener
		// methods)
		private class MyMouseListener extends MouseAdapter
		{
			public void mousePressed(MouseEvent e)
			{
				x1 = e.getX();  // store where mouse is when clicked
				y1 = e.getY();

				if (!e.isPopupTrigger() && mode == Mode.PASTING)
				{	
						if (copyInfo[0].equals("Tree"))
	        				newShape = new Tree(Integer.parseInt(copyInfo[1]), Integer.parseInt(copyInfo[2])
	        										, Integer.parseInt(copyInfo[3]));
	        			if (copyInfo[0].equals("House"))
	        				newShape = new House(Integer.parseInt(copyInfo[1]), Integer.parseInt(copyInfo[2])
	        										, Integer.parseInt(copyInfo[3]));
	        			if (copyInfo[0].equals("Snowman"))
	        				newShape = new Snowman(Integer.parseInt(copyInfo[1]), Integer.parseInt(copyInfo[2])
	        										, Integer.parseInt(copyInfo[3]));
	        			if (copyInfo[0].equals("Snowflake"))
	        				newShape = new Snowflake(Integer.parseInt(copyInfo[1]), Integer.parseInt(copyInfo[2])
	        										, Integer.parseInt(copyInfo[3]));
	        			if (copyInfo[0].equals("Present"))
	        				newShape = new Present(Integer.parseInt(copyInfo[1]), Integer.parseInt(copyInfo[2])
	        										, Integer.parseInt(copyInfo[3]));
	        			if (copyInfo[0].equals("Greeting"))
	        			{
	        				newShape = new Greeting(Integer.parseInt(copyInfo[1]), Integer.parseInt(copyInfo[2])
	        										, Integer.parseInt(copyInfo[3]));
	        				((MyText) newShape).setText(copyInfo[4]);
	        			}

					
					shapeList.add(newShape);
					shapeList.get(shapeList.size()-1).move(x1,y1);
					unSelect();
					copying = false;
					draw.setEnabled(true);
					menuPaste.setEnabled(false);
					mode = Mode.NONE;
					msg.setText("Pasted succesfully");
					repaint();
					edited = true;
				}
				
				if (!e.isPopupTrigger() && (mode == Mode.NONE ||
										    mode == Mode.SELECTED)) // left click and
				{												    // either NONE or
					if (selindex >= 0)								// SELECTED mode
					{
						unSelect();			// unselect previous shape
						mode = Mode.NONE;
					}
					selindex = getSelected(x1, y1);  // find shape mouse is
													 // clicked on
					if (selindex >= 0)
					{
						mode = Mode.SELECTED;  	// Now in SELECTED mode for shape
						
						// Check for double-click.  If so, show dialog to update text of
						// the current text shape (will do nothing if shape is not a MyText)
						MyShape curr = shapeList.get(selindex);
						if (curr instanceof MyText && e.getClickCount() == 2)
						{
							String newText = JOptionPane.showInputDialog(theWindow, "Enter new text [Cancel for no change]");
							if (newText != null)
								((MyText) curr).setText(newText);
						}
					}
					repaint();	
				}
				else if (e.isPopupTrigger() && selindex >= 0)  // if button is
				{								               // the popup menu
					popper.show(ShapePanel.this, x1, y1);      // trigger, show
					popped = true;							   // popup menu
				}											  
			}
			public void mouseReleased(MouseEvent e)
			{
				if (mode == Mode.DRAW) // in DRAW mode, create the new Shape
				{					   // and add it to the list of Shapes
					if (currShape == Figures.TREE)
					{
						newShape = new Tree(x1,y1,60);
					}
					else if (currShape == Figures.SNOWFLAKE)
					{
						newShape = new Snowflake(x1,y1,10);
					}
					else if (currShape == Figures.GREETING)
					{
						newShape = new Greeting(x1,y1,30);
					}
					else if (currShape == Figures.HOUSE)
					{
						newShape = new House(x1, y1, 100);
					}
					else if (currShape == Figures.PRESENT)
					{
						newShape = new Present(x1, y1, 40);
					}
					else if (currShape == Figures.SNOWMAN)
					{
						newShape = new Snowman(x1, y1, 125);
					}
					
					
					addShape(newShape);
					draw.setEnabled(true);  // Set interface back to
					mode = Mode.NONE;			 // "base" state
					msg.setText("");
					edited = true;
				}
				
				// In MOVING mode, set mode back to NONE and unselect shape (since 
				// the move is now finished).
				else if (mode == Mode.MOVING) 
				{
					mode = Mode.NONE;
					unSelect();  
					draw.setEnabled(true);
					msg.setText("");
					repaint();
				}
				else if (e.isPopupTrigger() && selindex >= 0) // if button is
				{							// the popup menu trigger, show the
					popper.show(ShapePanel.this, x1, y1); // popup menu
				}

					
				
				popped = false;  // unset popped since mouse is being released
			}
		}

		// the MouseMotionAdapter has the same idea as the MouseAdapter
		// above, but with only 2 methods.  The method not implemented
		// here is mouseMoved
		private class MyMover extends MouseMotionAdapter
		{
			public void mouseDragged(MouseEvent e)
			{
				x2 = e.getX();   // store where mouse is now
				y2 = e.getY();

				// Note how easy moving the shapes is, since the "work"
				// is done within the various shape classes.  All we do
				// here is call the appropriate method.  However, we don't 
				// want to accidentally move the selected shape with a right click
				// so we make sure the popup menu has not been activated.
				if ((mode == Mode.SELECTED || mode == Mode.MOVING) && !popped)
				{
					MyShape s = shapeList.get(selindex);
					mode = Mode.MOVING;
					s.move(x2, y2);
				}
				repaint();	// Repaint screen to show updates
			}
		}

		// Check to see if point (x,y) is within any of the shapes.  If
		// so, select that shape and highlight it so user can see.
		// This version of getSelected() always considers the shapes from
		// beginning to end of the ArrayList.  Thus, if a shape is "under"
		// or "within" a shape that was previously created, it will not
		// be possible to select the "inner" shape.  In your assignment you
		// must redo this method so that it allows all shapes to be selected.
		// Think about how you would do this.
		private int getSelected(double x, double y)
		{                                 
			for (int i = 0; i < shapeList.size(); i++)
			{
				if ((shapeList.get(i).contains(x, y)) && (i != selectedIndex || (shapeList.get(i) instanceof MyText)))
				{
					shapeList.get(i).highlight(true); 
					selectedIndex = i;
					selindex = selectedIndex;
					if (!copying)
					{
						menuCopy.setEnabled(true);
						menuCut.setEnabled(true);
						menuPaste.setEnabled(false);
					}
					return i;
				}
			}
			selectedIndex = -1;
			return -1;
		}
		
		public void unSelect()
		{
			if (selindex >= 0)
			{
				shapeList.get(selindex).highlight(false);
				selindex = -1;
				menuCopy.setEnabled(false);
				menuCut.setEnabled(false);
				if (copying)
					menuPaste.setEnabled(true);
			}
		}
		
		public boolean deleteSelected()
		{
			if (selindex >= 0)
			{
				shapeList.remove(selindex);
				selindex = -1;
				return true;
			}
			else return false;
		}
		
		public boolean resizeSelected(int newsize)
		{
			if (selindex >= 0)
			{
				shapeList.get(selindex).resize(newsize);
				selindex = -1;
				return true;
			}
			else return false;
		}

		public void setMode(Mode newMode)            // set Mode
		{
			mode = newMode;
		}

		private void addShape(MyShape newshape)      // Add shape
		{
			shapeList.add(newshape);
			repaint();	// repaint so we can see new shape
		}

		// Method called implicitly by the JFrame to determine how much
		// space this JPanel wants
		public Dimension getPreferredSize()
		{
			return new Dimension(prefwid, prefht);
		}

		// This method enables the shapes to be seen.  Note the parameter,
		// which is implicitly passed.  To draw the shapes, we in turn
		// call the draw() method for each shape.  The real work is in the draw()
		// method for each MyShape
		public void paintComponent (Graphics g)    
		{
			super.paintComponent(g);         // don't forget this line!
			Graphics2D g2d = (Graphics2D) g;
			for (int i = 0; i < shapeList.size(); i++)
			{
				shapeList.get(i).draw(g2d);
			}
		}
	} // end of ShapePanel
}