/* Zach Sadler
 * Assignment 2
 * Interface to read in the txt file
 * and interpret the results
 */
 
import java.io.*;
import java.util.*;

public class Assig2
{
	public static void main(String [] args)
	{
		String input;				// for nextLine
		int temp1, temp2, temp3;	// arguments for nextInt
		double temp4;				// needed for cost
 		Scanner txtScan;			// to read from the txtFile
 		
 	
 	
		try{
		txtScan = new Scanner(new File("test2-1.txt"));
		
		while (txtScan.hasNextLine())
		{
			input = txtScan.nextLine();
			if (input.equals("receive"))
			{		receive();		}
				
			if (input.equals("report"))
			{		report();		}
			
			if (input.equals("display"))
			{		display();		}
			
			if (input.equals("use"))
			{		use(); 			}
			
			if (input.equals("skip"))
			{		skip();			}
			
		}
	
		} catch (IOException e)
		{		
			System.out.println("Oh no!");
			System.out.println(e.getStackTrace());		}
		
	}
	
	public void receive()
	{
		// take in the number of crates, say you're receiving, then receive
		temp1 = txtScan.nextInt();
		System.out.println("Receiving " + temp1 + " crates of bananas");
		for (int i = 0; i < temp1; i++)
		{
			temp2 = txtScan.nextInt();			// exp
			temp3 = txtScan.nextInt();			// count
			temp4 = txtScan.nextDouble();		// cost
			// make a new crate with these dimensions
		}
	}
	
	public void report()
	{}
	public void display()
	{}
	public void use()
	{
		temp1 = txtScan.nextInt();		// how many to use
	}
	public void skip()
	{}
	
	
}