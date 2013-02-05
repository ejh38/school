/* CS 0401
 * Assignment 4
 * Zach Sadler
 * A graphical version of Assignment 3: Hangman
 */
 
import java.util.*;
import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Assig4
{
	// these are all for the GUI
	JFrame theWindow;
	JPanel upperPanel, lowerPanel;
	JPanel textPanel, buttonPanel, playerPanel;
	private JLabel statusLabel, infoLabel, wordLabel, guessesLabel;
	JLabel playerName, playerWin, playerLoss;
	JLabel c1, c2, c3, c4, c5;
	MyPanel hangPanel;
	JButton b1, b2, b3;
	JTextField textBox;
	Container thePane;
	MyListener theListener;
	HangFigure hangman;
	
	// flags for game state: flag1 is for
	// whether the game has started or not
	// (flag1 = true means it has)
	
	// flag2 is for whether b1 says end player
	// or end game (flag2 = true means end player)
	
	// flag3 is for whether the player is on a word
	// (flag3 = true means on a word)
	boolean flag1, flag2, flag3;
	
	
	//---------- Start of copy from assig3---------//
	
	
	// more flags, these are for the loops from assig3
	boolean cont, flag;
	boolean exit2 = false;

	WordServer Words;
	StringBuilder hanging, guessed;
	PrintWriter txtOut;
	Scanner txtScan, wordScan;
	ArrayList<HangPlayer> Players = new ArrayList<HangPlayer>();
		
	// temporary String used throughout the program
	String temp = "";
	String answer;
	char guess;
	
	// these temporary integers allow me to construct
	// the HangPlayer objects after reading in from txt
	int temp1, temp2, index;

	//-----------End of copy from assig3-----------------//
			

	// sets up the GUI	
	public Assig4()
	{		
		theWindow = new JFrame("Assignment 4 - Zach Sadler");

		// create the hangPanel as a MyPanel
		// which is defined lower down
		hangPanel = new MyPanel(100, 150);
		
		// creating buttons
		buttonPanel = new JPanel();
		b1 = new JButton("Start Game");
		b2 = new JButton("End Game");
		b2.setEnabled(false);
		b3 = new JButton("New Word");
		b3.setEnabled(false);
		
		// creating listener and linking buttons to it
		theListener = new MyListener();
		b1.addActionListener(theListener);
		b2.addActionListener(theListener);
		b3.addActionListener(theListener);
		
		// adding the buttons to the buttonPanel
		buttonPanel.setLayout(new GridLayout(3, 1));
		buttonPanel.add(b1);
		buttonPanel.add(b2);
		buttonPanel.add(b3);

		// The player panel I created to show the current
		// player's name, wins, and losses
		playerPanel = new JPanel();
		playerPanel.setLayout(new GridLayout(3,1));
		playerName = new JLabel("No player loaded");
		playerWin = new JLabel("");
		playerLoss = new JLabel("");
		playerName.setFont(new Font("Helvetica", Font.BOLD, 16));
		playerWin.setFont(new Font("Helvetica", 0, 16));
		playerLoss.setFont(new Font("Helvetica", 0, 16));
		
		// adding the labels to the playerPanel
		playerPanel.add(playerName);
		playerPanel.add(playerWin);
		playerPanel.add(playerLoss);	
		
		// these are the constant labels that don't
		// change at all through the execution of the
		// program. I create them seperately so I only
		// have to change the actual status/info/word etc.
		c1 = new JLabel(" Game Status:");
		c2 = new JLabel(" Game Info:");
		c3 = new JLabel(" Current Word:");
		c4 = new JLabel(" Your Guesses:");
		c5 = new JLabel(" Current Guess:");
		c1.setFont(new Font("Helvetica", Font.BOLD, 22));
		c2.setFont(new Font("Helvetica", Font.BOLD, 22));
		c3.setFont(new Font("Helvetica", Font.BOLD, 22));
		c4.setFont(new Font("Helvetica", Font.BOLD, 22));
		c5.setFont(new Font("Helvetica", Font.BOLD, 22));		

		// these are the other labels, the ones
		// that I will update throughout execution
		// which display the word, guesses, info, status, etc.
		textPanel = new JPanel();
		textPanel.setLayout(new GridLayout(5,2));
		statusLabel = new JLabel("Game hasn't started.");
		infoLabel = new JLabel("Welcome to Hangman!");
		wordLabel = new JLabel("");
		wordLabel.setFont(new Font("Helvetica", Font.PLAIN, 28));
		guessesLabel = new JLabel("");
		
		// the textPanel is a 5 row, 2 column grid
		// so I alternate between adding the constant
		// text and the dynamic test
		textPanel.add(c1);
		textPanel.add(statusLabel);
		textPanel.add(c2);
		textPanel.add(infoLabel);
		textPanel.add(c3);
		textPanel.add(wordLabel);
		textPanel.add(c4);
		textPanel.add(guessesLabel);
		
		// this is the JTextField where the player
		// will input their guesses. I initialize it
		// to 15 column width to make the panel a nice size
		textBox = new JTextField();
		textBox.setColumns(15);
		textBox.setEditable(false);
		textPanel.add(c5);
		textPanel.add(textBox);
		textBox.addActionListener(theListener);
		
		// can't close the window - have to quit through
		// the 'end game' button so game can be saved
		theWindow.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		thePane = theWindow.getContentPane();
		thePane.setLayout(new GridLayout(2, 1));
		
		// create the upperPanel from the text and hang
		upperPanel = new JPanel();
		upperPanel.setLayout(new GridLayout(1,2));
		upperPanel.add(textPanel);
		upperPanel.add(hangPanel);
		
		// create the lowerPanel from the buttons,
		// an empty one for spacing, and the player panel
		lowerPanel = new JPanel();
		lowerPanel.setLayout(new GridLayout(1,3));
		lowerPanel.add(buttonPanel);
		lowerPanel.add(new JPanel());
		lowerPanel.add(playerPanel);
		
		thePane.add(upperPanel);
		thePane.add(lowerPanel);
		
		theWindow.pack();
		theWindow.setVisible(true);

	}
	
	class MyListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			// try/catch block in case players.txt isn't found
			try
			{		
				txtScan = new Scanner(new File("players.txt"));
			} catch (IOException eee)
			{}

			//
			//--------------Start of button 1---------//
			//
			if (e.getSource() == b1)
			{
				// game hasn't started- ie, b1 is 'Start Game'
				if (!flag1)
				{
					JOptionPane.showMessageDialog(null, "Players file loaded succesfully");
					
					// set flag1 to true since game has started
					flag1 = true;
					
					// this is straight from assig3
					// reads in all the players to the ArrayList of HangPlayers
					// each time has to flush the txtScan
					// input stream by calling nextLine()
					while (txtScan.hasNextLine())
					{
						temp = txtScan.next();
						txtScan.nextLine();
						temp1 = txtScan.nextInt();
						txtScan.nextLine();
						temp2 = txtScan.nextInt();
						if (txtScan.hasNextLine())
							txtScan.nextLine();
						Players.add(new HangPlayer(temp, temp1, temp2));
					}
					
					statusLabel.setText("Ready for the next player.");
					b1.setText("Next player");
					b2.setEnabled(true);
				}
				else
				// they click 'next player'
				{
					textBox.setText("");
					
					// by default, assume the player isn't found
					index = -1;
					temp = JOptionPane.showInputDialog("What is your name?");					
					for (int i = 0; i < Players.size(); i++)
					{
						// case insensitivity
						if (Players.get(i).nameToString().equalsIgnoreCase(temp))
							index = i;
					}
			
					// if the name isn't found in the players file
					// then add a new player, and set the index
					// to the last position (size - 1)
					if (index == -1)
					{
						Players.add(new HangPlayer(temp, 0, 0));
						index = Players.size() - 1;
						JOptionPane.showMessageDialog(null, "Glad to have you play, " + temp);
					}
					else
					{
					// welcome back old players
						JOptionPane.showMessageDialog(null, "Welcome back, " + temp);
					}
					
					statusLabel.setText("Game in progress for " + Players.get(index).nameToString()
																		 + ".");
					b1.setEnabled(false);
					b2.setText("End Player");
					flag2 = true;
					b3.setEnabled(true);
					
					// this is for my playerPanel
					playerName.setText("Current Player: " + Players.get(index).nameToString());
					playerWin.setText("Wins: \t" + Players.get(index).winsToString());
					playerLoss.setText("Losses: \t" + Players.get(index).lossToString());
					
					
					temp = JOptionPane.showInputDialog("Which word file would you like to use?");
					
					// another try/catch block to try and
					// find the specified word file they give
					try
					{
						wordScan = new Scanner(new File(temp));
					} catch(IOException eeee)
					{}
					
					Words = new WordServer(wordScan.nextInt());	
					Words.loadWords(wordScan);
					
					infoLabel.setText("Ready for the next word.");
				}
			}		
			//	 				
			//--------------End of button 1-------------//
			//
			
			//
			//-----------Start of button 2-------------//
			//
			if (e.getSource() == b2)
			{
				// if b2 says 'end game'
				if (!flag2)
				{
					// if game hasn't started then just quit
					// (no need to save anything)
					if (!flag1)
					{
						if (JOptionPane.showConfirmDialog(null, "Are you sure you want to quit?",																  "End Game", JOptionPane.YES_NO_OPTION) == 0)
							System.exit(0);	
					}
					else
					// have to save the data otherwise
					{
						// if they click yes- quit
						if (JOptionPane.showConfirmDialog(null, "Are you sure you want to quit?",																  "End Game", JOptionPane.YES_NO_OPTION) == 0)
						{
							// another try/catch to save the players file
							try{
								txtOut = new PrintWriter(new FileOutputStream("players.txt", false));

								for(int i = 0; i < Players.size(); i++)	
									Players.get(i).save(txtOut);
								// save players back to players.txt
								// make sure to close out the PrintWriter
								
								txtOut.close();
							} catch (IOException eeeeeee)
							{}
							System.exit(0);
						}
					}	
				}
				
				// if b2 says 'end player'
				else
				{
					// if they click yes- stop playing
					if (JOptionPane.showConfirmDialog(null, "Are you sure you want to stop playing?" +
															"\nIf you're on a word this will be a loss.",
														"End Player", JOptionPane.YES_NO_OPTION) == 0)
					{
						textBox.setText("");
						
						// if they were on a word, they get a loss
						if (flag3)
						{
							Players.get(index).winOrLose(false);
							flag3 = false;
							playerLoss.setText("Losses: \t" + Players.get(index).lossToString());
						}
						JOptionPane.showMessageDialog(null, "Final Results for " + 
														Players.get(index).nameToString() +
														"\nWins: " + Players.get(index).winsToString() +
														"\nLosses: " + Players.get(index).lossToString());
						
						// adjust labels and buttons
						statusLabel.setText("Ready for the next player.");
						b1.setText("Next player");
						b1.setEnabled(true);
						b2.setText("End Game");
						flag2 = false;
						b3.setEnabled(false);
						textBox.setEditable(false);
						
						// adjust the playerPanel
						playerName.setText("Current Player: ");
						playerWin.setText("Wins:");
						playerLoss.setText("Losses:");
						wordLabel.setText("");
						guessesLabel.setText("");
						

					}
				}	
										
			}
			//
			//-------------End of button 2-------//
			//
			
			//
			//----------Start of button 3----------//
			//
			if (e.getSource() == b3)
			{
				// if they're on a word
				if (flag3)
				{
					// if they click yes- skip the word
					if (JOptionPane.showConfirmDialog(null, "Are you sure you want to take a loss" + 
													"\nand skip the current word?", "New Word",
													JOptionPane.YES_NO_OPTION) == 0)
					{
						Players.get(index).winOrLose(false);
						playerLoss.setText("Losses: \t" + Players.get(index).lossToString());
						infoLabel.setText("Sorry. Answer is below.");
						wordLabel.setText(answer);
						textBox.setText("");
						
						// now they're no longer on a word
						flag3 = false;
					}
				}
				
				// if they aren't on a word
				if (!flag3)
				{
					// now they are
					flag3 = true;
					playerName.setText("Current Player: " + Players.get(index).nameToString());
					playerWin.setText("Wins: \t" + Players.get(index).winsToString());
					playerLoss.setText("Losses: \t" + Players.get(index).lossToString());
					
					infoLabel.setText("");
					
					// this is from assig3 
					answer = new String(Words.getNextWord());
					hanging = new StringBuilder(answer.length());
					for (int i = 0; i < answer.length(); i ++)
						hanging.replace(i, i, "?");
						
					guessed = new StringBuilder();
					wordLabel.setText(hanging.toString());
					guessesLabel.setText(guessed.toString());
					textBox.setEditable(true);
					
					// these numbers seem to display the HangFigure correctly
					hangman = new HangFigure(200, 25, 45);
					hangPanel.repaint();
					
					// a nice touch-> automatically points them at the textbox
					textBox.requestFocus();
				}
			}
			//
			//----------End of button 3----------//
			//
			
			//
			//---------Start of textBox-----------//	
			//
			if (e.getSource() == textBox)
			{
				// from assig3, 'flag' is used for
				// a number of things
				flag = false;
				
				// only read the first character of their
				// guess and convert it to uppercase
				guess = textBox.getText().charAt(0);
				guess = Character.toUpperCase(guess);
									
				// if they reguess a letter
				for (int i = 0; i < guessed.length(); i++)
				{
					if (guess == guessed.charAt(i))
					{
						flag = true;
						infoLabel.setText("You've already guessed " + guess);
					}
				}
				// as long as they haven't already guessed their
				// guess before, append it to the guessed
				// stringbuilder and add a space as seperation
				if (flag == false)
					guessed.append(guess + " ");	
				
				// if flag is still false then
				// they haven't reguessed, so check
				// to see if it is a correct guess	
				if (!flag)
				{
					for (int i = 0; i < answer.length(); i++)
					{
						// the guess is found in the answer
						if (guess == answer.charAt(i))
						{
							hanging.setCharAt(i, guess);
							flag = true;
							infoLabel.setText(guess + " is correct!");
							// this is the win condition
							// it's inside this loop so that it is only
							// checked when the player gets a guess right
							if (answer.equals(hanging.toString()))
							{
								// they get it right
								Players.get(index).winOrLose(true);
								textBox.setEditable(false);
								infoLabel.setText("Correct! Great work!");
								playerWin.setText("Wins: \t" + Players.get(index).winsToString());
								// no longer on a word
								flag3 = false;
							}
						} 
					}
				}
				// at this point, flag is false if
				// they have entered an original guess
				// (not a repeat), and it is incorrect
				if (!flag)
				{
					// add to the hangman, tell them
					// they're wrong, and check to see if
					// they've lost
					hangman.addChunk();
					hangPanel.repaint();
					infoLabel.setText(guess + " is wrong.");
					if (hangman.isComplete())
					{
						Players.get(index).winOrLose(false);
						// show them the answer by filling in 
						// hanging with the correct characters
						// taken from the answer string
						infoLabel.setText("Sorry. Answer is below.");
						for (int i = 0; i < answer.length(); i++)
							hanging.setCharAt(i, answer.charAt(i));

						textBox.setEditable(false);
						// no longer on a word
						flag3 = false;
						playerLoss.setText("Losses: \t" + Players.get(index).lossToString());
					}
				}
				
				// after each guess, update the hanging word,
				// the guesses, and reset the textbox to be empty
				wordLabel.setText(hanging.toString());
				guessesLabel.setText(guessed.toString());
				textBox.setText("");

			}
			//
			//-------End of textBox----------//
			//
			
		}
		//
		//--------End of actionPerformed------//
		//
		
	}
	//
	//------------End of MyListener---------//
	//
	
	
	// this is taken nearly unchaged from A4Help
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
			
			// the one adjustment is here
			// where I used the name of my hangFigure
			
			if (hangman != null)		// Note that we are calling the draw() method in
				hangman.draw(g2d);	// in the HangFigure class and passing the
								// Graphics2D object into it.  This way, our JPanel
						// does not have to know the specifics of how to draw the
						// figure -- it only has to know that the figure has a
						// draw() method.  See the draw() method in HangFigure for
						// more details.
		}
	}

	// a nice one-line main
	public static void main(String [] args)
	{
		new Assig4();
	}
		
}