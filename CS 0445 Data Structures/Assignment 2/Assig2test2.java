/* Zach Sadler
 * Assignment 2
 * Interface to read in the txt file
 * and interpret the results
 */
 
import java.io.*;
import java.util.*;

public class Assig2test2
{
	public static void main(String [] args)
	{
	//---For reading in txt files---//
		String input;				// for nextLine
		int temp1, temp2, temp3;	// arguments for nextInt
		double temp4;				// needed for cost
		Scanner txtScan;			// to read from the txtFile
	//------------End---------------//
				
		int clock = 0;					// global clock
		StackInterface<Crate> stack = new ArrayStack<Crate>();
		StackInterface<Crate> tempStack = new ArrayStack<Crate>();
		Crate tempCrate1, tempCrate2, counterCrate = null; 
		
		boolean keepLooking = false;
		
		
		// Stuff for financial report
 		int recentCrates = 0, recentMoves = 0;
 		double recentBananaCost = 0, recentLaborCost = 0, recentTotal = 0;
 		int totalCrates = 0, totalMoves = 0; 
 		double totalLaborCost = 0, totalBananaCost = 0, totalTotal = 0;
 		
//--------Start of reading in the file--------//
		try{
			String file = args[0];
		txtScan = new Scanner(new File(file));
		
		while (txtScan.hasNextLine())
		{
			input = txtScan.nextLine();
			if (input.equals("receive"))
			{	
			// take in the number of crates, say you're receiving, then receive
				temp1 = txtScan.nextInt();
				
				recentCrates = temp1;
				recentBananaCost = 0;
				recentMoves = 0;
				recentLaborCost = 0;
				recentTotal = 0;
				
				System.out.println("\nReceiving " + temp1 + " crates of bananas");
				for (int i = 0; i < temp1; i++)
				{
					temp2 = txtScan.nextInt();			// exp
					temp3 = txtScan.nextInt();			// count
					temp4 = txtScan.nextDouble();		// cost
					tempCrate1 = new Crate(temp2, temp3, temp4);
					
					recentBananaCost += temp4;
					
					keepLooking = true;
				while (keepLooking)
				{
					if (stack.isEmpty())
					{
						stack.push(tempCrate1);
						recentMoves++;
						keepLooking = false;
					}
					else
					{
						// stack is not empty
						tempCrate2 = stack.peek();
						if (tempCrate1.compareTo(tempCrate2) < 1)
						{
							// if the crate less than/equal to top stack
							if (tempStack.isEmpty())
							{
								// if tempStack is empty, then push onto tempStack
								tempStack.push(tempCrate1);
								recentMoves++;
								keepLooking = false;
							}
							else
							{
								// if tempStack isn't empty
								tempCrate2 = tempStack.peek();
								if (tempCrate1.compareTo(tempCrate2) > -1)
								{
									// if greater than/equal to top tempStack, then push onto tempStack
									tempStack.push(tempCrate1);
									recentMoves++;
									keepLooking = false;
								}
								else
								{
									// if less than top tempStack, pop off of tempStack, push onto stack
									stack.push(tempStack.pop());
									recentMoves++;
								}
							}
						}
						else
						// greater than the top of the Stack
						{
							tempStack.push(stack.pop());
							recentMoves++;
						}
					}
				}
				if (i == (temp1 - 1))
				{
					while (!tempStack.isEmpty())
					{
						stack.push(tempStack.pop());
						recentMoves++;
					}
				}

				}
				
				recentLaborCost += recentMoves;
				recentTotal += recentLaborCost + recentBananaCost;	
			}	
			
			if (input.equals("report"))
			{
				totalCrates 	+= recentCrates;
				totalMoves 		+= recentMoves;
				totalBananaCost += recentBananaCost;
				recentLaborCost  = recentMoves;
				totalLaborCost  += recentLaborCost;
				totalTotal 		+= recentTotal;
				
				System.out.println("\nLickety Splits Financial Statement:");
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
				System.out.println("\t\tTotal: " + totalTotal + "\n");				
						
			}
			
			if (input.equals("display"))
			{
				if (counterCrate != null)	
					System.out.println("\nCurrent crate: " + counterCrate.toString());
				// pop the crates off the stack, putting them in turn onto the tempStack
				// and displaying their information each time
				if (stack.isEmpty())
					System.out.println("No more crates in the stack!");
				else
				{
					System.out.println("Stack crates (top to bottom):");
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
			}			
			if (input.equals("use"))
			{		
				temp1 = txtScan.nextInt();
				System.out.println("\n" + temp1 + " bananas needed for order");
				while (temp1 > 0)
				{
					if (counterCrate == null || counterCrate.getCurr() == 0)
					{
						if (stack.isEmpty())
						{
							System.out.println("Store is out of bananas! The Horror!!");
							temp1 = 0;
						}
						else
						{
							counterCrate = stack.pop();
							System.out.println("Getting crate: " + counterCrate.toString()
														+ " from the stack");
						}
					}
					else
					{
						temp2 = counterCrate.getCurr();
						temp3 = temp1 - temp2;
						if (temp3 <= 0)
						{
							// counterCrate has enough bananas
							counterCrate.useBananas(temp1);
							System.out.println(temp1 + " bananas used from current crate");
							temp1 = 0;
				/*			if (!stack.isEmpty())
								counterCrate = stack.pop();
							else
							{
								System.out.println("Store is out of bananas! The horror!");
							}
				*/		}
						else
						{
							// not enough bananas
							temp1 -= temp2;
							counterCrate.useBananas(temp2);
							System.out.println(temp2 + " bananas used from current crate");
						}	
					}
				}						
					
				
			}
			
			if (input.equals("skip"))
			{	
				clock++;
				System.out.println("\nThe current day is now Day " + clock);
				while (!stack.isEmpty())
				{
					tempCrate1 = stack.pop();
					if (!tempCrate1.isExpired(clock))
					{
						tempStack.push(tempCrate1);
					}
					else
					{
						// explain the crate is expired
						System.out.println("Top crate: " + tempCrate1.toString() + " is expired!");
					}
				}
				while (!tempStack.isEmpty())
				{
					stack.push(tempStack.pop());
				}
			}
			
		} // while hasNextLine
	
		} catch (IOException e)
		{		
			System.out.println("Oh no!");
			System.out.println(e.getStackTrace());		}
		
	
//--------------End file read----------//	
	}
	
}