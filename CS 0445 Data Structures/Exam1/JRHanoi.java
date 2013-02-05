// CS 0445 Spring 2012
// Demonstration of the Towers of Hanoi problem
// This handout demonstrates using recursion to solve a problem that does not
// have a straightforward non-recursive solution.  This program uses a lot of
// somewhat advanced features of Java to make a nice interactive user interface. 
// Note that the actual Towers of Hanoi solution is extremely short (see method
// solveHanoi()).

// As far as this code goes, some improvements can definitely be made (ex: 
// handling exceptions).  However it does adequately show how Hanoi is solved 
// and just how many moves are required to solve it.  See additional comments 
// below.

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;

public class JRHanoi extends JFrame implements Runnable
{
     private Tower [] theTowers;
     private ShapePanel drawPanel;
     private JPanel bPanel, tPanel;
     private JLabel info;
     private JButton playGame, runDemo;
     private JButton [] towerButtons;
     private int size, destTower, moves, delay;
     private Rectangle2D currDisk;
     private Thread runThread;
     private boolean selected;

     public JRHanoi()
     {
            super("Interactive Towers of Hanoi");
            drawPanel = new ShapePanel(400, 300);

            playGame = new JButton("Play Game");
            runDemo = new JButton("Run Demo");

            ButtonHandler bhandler = new ButtonHandler();
            playGame.addActionListener(bhandler);
            runDemo.addActionListener(bhandler);

            TowerHandler thandler = new TowerHandler();
            bPanel = new JPanel();
            bPanel.setLayout(new GridLayout(1,3));

            towerButtons = new JButton[3];
            for (int i = 0; i < 3; i++)
            {
                 towerButtons[i] = new JButton("Tower " + i);
                 towerButtons[i].setVisible(false);
                 towerButtons[i].setEnabled(false);
                 towerButtons[i].addActionListener(thandler);
                 bPanel.add(towerButtons[i]);
            }

            tPanel = new JPanel();
            tPanel.setLayout(new GridLayout(3,1));

            info = new JLabel("Welcome to the Towers of Hanoi", 
				                          (int) CENTER_ALIGNMENT);

            tPanel.add(runDemo);
            tPanel.add(playGame);
            tPanel.add(info);

            Container c = getContentPane();
            c.add(drawPanel, BorderLayout.CENTER);
            c.add(tPanel, BorderLayout.NORTH);
            c.add(bPanel, BorderLayout.SOUTH);

            theTowers = new Tower[3];
            runThread = null;

            setSize(480, 445);
            setVisible(true);
     }

 // Note that by far MOST of the code for this program deals with the graphics
 // and the user interface.  The short subprogram below actually solves the
 // Towers of Hanoi problem.  It is so short because it calls itself recursively,
 // as you can see in the code.  If you want to read over the code that handles
 // the graphics and interaction, feel free to do so.  However, the important
 // part of the program that you should understand is the recursive method
 // below, and how it in just a few lines solves a quite difficult problem.
 // This is possible because of how recursion is implemented using activation
 // records and the run-time stack, as we discussed in lecture.

     public void solveHanoi(int currsize, int start, int middle, int end)
     {
            if (currsize == 1)	// If we have only one disk, move it from start
            {					// to end directly
                  theTowers[start].move(theTowers[end]);
                  moves++;
            }
            else	// If we have more than one disk: 
					// 1) recursively move N-1 disks from start to middle, 
					// 2) move last disk from start to end directly
					// 3) recursivly move N-1 disks from middle to end
			{
                  solveHanoi(currsize-1, start, end, middle);
                  theTowers[start].move(theTowers[end]);
                  moves++;
                  solveHanoi(currsize-1, middle, start, end);
            }
     }

     public void run()
     {
            moves = 0;
            solveHanoi(size, 0, 1, 2);
            playGame.setEnabled(true);
            runDemo.setEnabled(true);
            info.setText("The Demo solved Hanoi in " + moves + " moves");
     }


     public static void main(String [] args)
     {
            JRHanoi win = new JRHanoi();

            win.addWindowListener(
                new WindowAdapter()
                {
                    public void windowClosing(WindowEvent e)
                    { System.exit(0); }
                }
            );
     }

     private class ButtonHandler implements ActionListener
     {
            public void actionPerformed(ActionEvent e)
            {
                 if (e.getSource() == runDemo)
                 {
                       playGame.setEnabled(false);
                       runDemo.setEnabled(false);
                       do
                       {
                             size = Integer.parseInt(
                                   JOptionPane.showInputDialog(JRHanoi.this,
                                                       "How many disks? (<= 10)"));
                       } while (size < 1 || size > 10);

                       do
                       {
                             delay = Integer.parseInt(
                                  JOptionPane.showInputDialog(JRHanoi.this,
                                                              "Delay between moves?"));
                       } while (delay < 0);
                       for (int i = 0; i < 3; i++)
                            theTowers[i] = new Tower(size, i);
                       theTowers[0].fill();

                       info.setText("Running demonstration...please wait until it finishes");
                       if (runThread == null || (!runThread.isAlive()))
                       {
                            runThread = new Thread(JRHanoi.this);
                            runThread.start();
                       }
                       repaint();
                 }
                 else if (e.getSource() == playGame)
                 {
                       if (playGame.getText() == "Play Game")
                       {
                             playGame.setText("Stop Game");
                             runDemo.setEnabled(false);
                             do
                             {
                                   size = Integer.parseInt(
                                          JOptionPane.showInputDialog(JRHanoi.this,
                                                       "How many disks? (<= 10)"));
                             } while (size < 1 || size > 10);

                             do
                             {
                                   destTower = Integer.parseInt(
                                          JOptionPane.showInputDialog(JRHanoi.this,
                                                       "Destination Tower? (1 or 2)"));
                             } while (destTower != 1 && destTower != 2);


                             for (int i = 0; i < 3; i++)
                                  theTowers[i] = new Tower(size, i);
                             theTowers[0].fill();

                             for (int i = 0; i < 3; i++)
                             {
                                  towerButtons[i].setVisible(true);
                             }
                             towerButtons[0].setEnabled(true);
                             selected = false;
                             moves = 0;

                             info.setText("Select Tower to REMOVE disk from");
                       }
                       else if (playGame.getText() == "Stop Game")
                       {
                             for (int i = 0; i < 3; i++)
                             {
                                  towerButtons[i].setVisible(false);
                                  towerButtons[i].setEnabled(false);
                                  theTowers[i] = null;
                             }
                             playGame.setText("Play Game");
                             runDemo.setEnabled(true);
                             info.setText("Welcome to the Towers of Hanoi");
                       }
                 }
                 repaint();
            }
     }

     private class TowerHandler implements ActionListener
     {
            public void actionPerformed(ActionEvent e)
            {
                 for (int i = 0; i < 3; i++)
                 {
                      if (e.getSource() == towerButtons[i])
                      {
                            if (!selected)
                            {
                                 selected = true;
                                 currDisk = theTowers[i].remove();
                                 int wid = (int) currDisk.getWidth();
                                 for (int j = 0; j < 3; j++)
                                 {
                                      if (theTowers[j].isEmpty() ||
                                               wid < theTowers[j].topWidth())
                                            towerButtons[j].setEnabled(true);
                                      else
                                            towerButtons[j].setEnabled(false);
                                 }
                                 info.setText("Select Tower to ADD disk to");
                            }
                            else
                            {
                                 selected = false;
                                 moves++;
                                 theTowers[i].add(currDisk);
                                 if (i == destTower && theTowers[i].isFull())
                                 {
                                       info.setText("Congratulations, you have WON in " + moves + " moves");
                                       for (int j = 0; j < 3; j++)
                                       {
                                            towerButtons[j].setVisible(false);
                                       }
                                       runDemo.setEnabled(true);
                                       playGame.setText("Play Game");
                                 }
                                 else
                                 {
                                     for (int j = 0; j < 3; j++)
                                     {
                                         if (!theTowers[j].isEmpty())
                                              towerButtons[j].setEnabled(true);
                                         else
                                              towerButtons[j].setEnabled(false);
                                     }
                                     info.setText("Select Tower to REMOVE disk from");
                                 }
                            }
                            repaint();
                            break;
                      }
                 }
            }
     }

     private class ShapePanel extends JPanel
     {

         private int prefwid, prefht;

         public ShapePanel (int pwid, int pht)
         {

             prefwid = pwid;
             prefht = pht;
         }

         public Dimension getPreferredSize()
         {
             return new Dimension(prefwid, prefht);
         }

         public void paintComponent (Graphics g)
         {
             super.paintComponent(g);
             Graphics2D g2d = (Graphics2D) g;
             for (int i = 0; i < 3; i++)
                  if (theTowers[i] != null)
                      theTowers[i].draw(g2d);
         }
     }

     private class Tower
     {
         public final int MAXWIDTH = 120, HEIGHT = 25;
         private Rectangle2D [] disks;
         private int number, xoffset;

         public Tower(int maxsize, int id)
         {
             disks = new Rectangle2D[maxsize];
             number = 0;
             xoffset = (id * (MAXWIDTH + 35)) + 20;
         }

         public void fill()
         {
             int width = MAXWIDTH;
             for (int i = 0; i < disks.length; i++)
             {
                    int x = xoffset + (MAXWIDTH - width)/2;
                    int y = 300 - ((i+1) * HEIGHT);
                    disks[i] = new Rectangle2D.Double(x, y, width, 25);
                    width = width - 10;
             }
             number = disks.length;
         }

         public boolean isFull()
         {
             return (number == disks.length);
         }

         public void move(Tower dest)
         {
             try
             {
                 Thread.sleep(delay);
             }
             catch(InterruptedException e) {}

             Rectangle2D curr = this.remove();
             dest.add(curr);
             repaint();
         }

         public Rectangle2D remove()
         {
             Rectangle2D curr = disks[number - 1];
             number--;
             return curr;
         }

         public void add(Rectangle2D curr)
         {
             int width = (int) curr.getWidth();
             int x = xoffset + (MAXWIDTH - width)/2;
             int y = 300 - ((number+1) * HEIGHT);
             curr.setFrame(x, y, width, 25);
             disks[number] = curr;
             number++;
         }

         public boolean isEmpty()
         {
             return (number == 0);
         }

         public int topWidth()
         {
             return ( (int) disks[number-1].getWidth());
         }

         public void draw(Graphics2D g2d)
         {
             for (int i = 0; i < number; i++)
             {
                  g2d.setColor(Color.red);
                  g2d.fill(disks[i]);
                  g2d.setColor(Color.black);
                  g2d.draw(disks[i]);
             }
         }

    }

}

