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
	//---For reading in txt files---//
		String input;				// for nextLine
		int temp1, temp2, temp3;	// arguments for nextInt
		double temp4;				// needed for cost
		Scanner txtScan;			// to read from the txtFile
	//------------End---------------//
				
		int clock = 1;					// global clock
		StackInterface<Crate> stack = new ArrayStack<Crate>();
		StackInterface<Crate> tempStack = new ArrayStack<Crate>();
		Crate tempCrate1, tempCrate2; 
		
		boolean keepLooking = false;
		
		
		// Stuff for financial report
 		int recentCrates = 0, recentBananaCost = 0, recentMoves = 0, recentLaborCost = 0, recentTotal = 0;
 		int totalCrates = 0, totalBananaCost = 0, totalMoves = 0, totalLaborCost = 0, totalTotal = 0;
 		
//--------Start of reading in the file--------//
		try{
		txtScan = new Scanner(new File("test2-1.txt"));
		
		while (txtScan.hasNextLine())
		{
			input = txtScan.nextLine();
			if (input.equals("receive"))
			{	
			// take in the number of crates, say you're receiving, then receive
				temp1 = txtScan.nextInt();
				System.out.println("Receiving " + temp1 + " crates of bananas");
				keepLooking = false;
				for (int i = 0; i < temp1; i++)
				{
					temp2 = txtScan.nextInt();			// exp
					temp3 = txtScan.nextInt();			// count
					temp4 = txtScan.nextDouble();		// cost
					tempCrate1 = new Crate(temp2, temp3, temp4);
					// find where to put it on the stack
					while (keepLooking & !stack.isEmpty())
					{
						tempCrate2 = stack.peek();
						if (tempCrate1.compareTo(tempCrate2) < 1)
						{
							stack.push(tempCrate1);
							recentMoves++;
							keepLooking = false;
						}
						else 
						{
							tempCrate2 = stack.pop();
							tempStack.push(tempCrate2);
							recentMoves++;
						}
					}
					while (!tempStack.isEmpty())
					{
						tempCrate2 = tempStack.pop();
						stack.push(tempCrate2);
						recentMoves++;
					}
					if (stack.isEmpty())
					{
						stack.push(tempCrate1);
						recentMoves++;
						keepLooking = true;
					}
					
					keepLooking = true;		
				}
			}
						
			if (input.equals("report"))
			{
				totalCrates 	+= recentCrates;
				totalMoves 		+= recentMoves;
				totalBananaCost += recentBananaCost;
				recentLaborCost  = recentMoves;
				totalLaborCost  += recentLaborCost;
				totalTotal 		+= recentTotal;
				
				System.out.println("Lickety Splits Financial Statement:");
				System.out.println("\tMost Recent Shipment:");
				System.out.println("\t\tCrates: " + recentCrates);
				System.out.println("\t\tBanana cost: " + recentBananaCost);
				System.out.println("\t\tLabor (moves): " + recentMoves);
				System.out.println("\t\tLabor cost: " + recentLaborCost);
				System.out.println("\t\t---------------------");
				System.out.println("\t\tTotal: " + recentTotal);
				System.out.println("\n\tOverall Expenses:");
				System.out.println("\t\tCrates: " + totalCrates);
				System.out.println("\t\tBanana cost: " + totalBananaCost);
				System.out.println("\t\tLabor (moves): " + totalMoves);
				System.out.println("\t\tLabor cost: " + totalLaborCost);
				System.out.println("\t\t---------------------");
				System.out.println("\t\tTotal: " + totalTotal);						
			}
			
			if (input.equals("display"))
			{
				System.out.println("Here's what I've got");
				// pop the crates off the stack, putting them in turn onto the tempStack
				// and displaying their information each time
				while (!stack.isEmpty())
				{
					tempCrate1 = stack.pop();
					tempStack.push(tempCrate1);
					System.out.println(tempCrate1.toString());
				}
				// then put them back on
				while (!tempStack.isEmpty())
				{
					tempCrate1 = tempStack.pop();
					stack.push(tempCrate1);
				}
			}
			
			if (input.equals("use"))
			{		}
			
			if (input.equals("skip"))
			{	
				clock++;
			}
			
		}
	
		} catch (IOException e)
		{		
			System.out.println("Oh no!");
			System.out.println(e.getStackTrace());		}
		
	
//--------------End file read----------//	
	}
	
}