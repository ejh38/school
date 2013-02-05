/*************************************************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * Driver to test different sorting algorithms.
 * Uses an abstract class to access the three different orders.
 *************************************************************/

import java.util.*;
import java.io.*;

public class Assig4
{
	public static void main(String [] args)
	{
		// variables for user input
		int size, trials;
		String fName;
		
		// take in the size, number of trials, and file name
		Scanner inScan = new Scanner(System.in);
		System.out.print("\nEnter array size: ");
		size = inScan.nextInt();
		System.out.print("Enter number of trials: ");
		trials = inScan.nextInt();
		inScan.nextLine();									// flush out the line return
		System.out.print("Enter file name: ");
		fName = inScan.nextLine();
		
		
		FileOutputStream fos = null;						// need this because the try may fail		
		try{
		fos = new FileOutputStream(fName, false);
		} catch (FileNotFoundException E)
		{		System.out.println("Bad file name!");		}	
		
		// this is the real program
		
		System.out.println("Here we go! Time to start crunching!");
		long start = System.nanoTime();	
		try{
		new Assig4(size, trials, fos);
		}
		catch (StackOverflowError e)
		{
			System.out.println("Whoops! StackOverflow! Need to do -Xss ...");
		}
		long delta = (System.nanoTime() - start);
		System.out.println("\nMade it! Full execution took " + delta/1000000000. + " seconds");
	}
	// still need to implement the trace
	boolean trace = false;
	
	PrintWriter toText;
	
	public Assig4(int size, int trials, FileOutputStream fos)
	{	
		if (size <= 20)
			trace = true;
		// make the three arrays, accessing them through the abstract interface
		Assig4ableAbstract randArray = new AlreadyRandomAbstract(size);
		Assig4ableAbstract sortArray = new AlreadySortedAbstract(size);
		Assig4ableAbstract revArray = new AlreadyReverseAbstract(size);

		toText = new PrintWriter(fos);
		
		runTrials(randArray, trials, fos);
		runTrials(sortArray, trials, fos);
		runTrials(revArray, trials, fos);
		
		toText.close();										// don't forget to close the PrintWriter
	}
	
	// this is where the real work is done
	public void runTrials(Assig4ableAbstract array, int trials, FileOutputStream fos)
	{	
		double [] ans = new double[5];
		// reset the ans array
		
		for (int j = 0; j < 5; j++)
			ans[j] = 0;
		
		for (int i = 0; i < trials; i++)
		{
			// this will only fill it at the start of each trial, so that
			// the same random data is used throughout, for example
			array.fill();
			
			if (trace)
			{
				System.out.println("\n\nAlgorithm: Simple Quicksort - pivot = last");
				System.out.println("Array size: " + array.length());
				System.out.println("Data configuration: " + array.getOrder());
				System.out.println("Initial data:");
				array.display();
			}
				
			// This is standard quickSort with pivot = last
			Integer [] temp = array.toArray();
			long start = System.nanoTime();	
			Quick.quickSort(temp, array.length());
			long delta = (System.nanoTime() - start);
			ans[0] += delta/1000000000.;
			if (trace)
			{
				System.out.println("\nData after sorting:");
				for (int j = 0; j < temp.length; j++)
					System.out.print(" " + temp[j]);
				System.out.println("\nTime (in nanoseconds): " + delta);
				System.out.println("Time (in seconds): " + delta/1000000000.);
			
				System.out.println();
				
				System.out.println("Algorithm: Median of 3 - Base case 5");
				System.out.println("Array size: " + array.length());
				System.out.println("Data configuration: " + array.getOrder());
				System.out.println("Initial data:");
				array.display();
			}
			
			// This is median of 3 with base case 5
			temp = array.toArray();
			start = System.nanoTime();	
			TextMergeQuick.quickSort(5, temp, array.length());
			delta = (System.nanoTime() - start);
			ans[1] += delta/1000000000.;
			if (trace)
			{
				System.out.println("\nData after sorting:");
				for (int j = 0; j < temp.length; j++)
					System.out.print(" " + temp[j]);
				System.out.println("\nTime (in nanoseconds): " + delta);
				System.out.println("Time (in seconds): " + delta/1000000000.);

				System.out.println();
				
				System.out.println("Algorithm: Median of 3 - Base case 10");
				System.out.println("Array size: " + array.length());
				System.out.println("Data configuration: " + array.getOrder());
				System.out.println("Initial data:");
				array.display();
			}
			
			// This is median of 3 with base case 10
			temp = array.toArray();
			start = System.nanoTime();	
			TextMergeQuick.quickSort(10, temp, array.length());
			delta = (System.nanoTime() - start);
			ans[2] += delta/1000000000.;
			if (trace)
			{
				System.out.println("\nData after sorting:");
				for (int j = 0; j < temp.length; j++)
					System.out.print(" " + temp[j]);
				System.out.println("\nTime (in nanoseconds): " + delta);
				System.out.println("Time (in seconds): " + delta/1000000000.);

				System.out.println();
				
				System.out.println("Algorithm: Median of 3 - Base case 20");
				System.out.println("Array size: " + array.length());
				System.out.println("Data configuration: " + array.getOrder());
				System.out.println("Initial data:");
				array.display();
			}
			
			// This is median of 3 with base case 20
			temp = array.toArray();
			start = System.nanoTime();	
			TextMergeQuick.quickSort(20, temp, array.length());
			delta = (System.nanoTime() - start);
			ans[3] += delta/1000000000.;
			if (trace)
			{
				System.out.println("\nData after sorting:");
				for (int j = 0; j < temp.length; j++)
					System.out.print(" " + temp[j]);
				System.out.println("\nTime (in nanoseconds): " + delta);
				System.out.println("Time (in seconds): " + delta/1000000000.);

				System.out.println();
				
				System.out.println("Algorithm: Quick with Random Pivot");
				System.out.println("Array size: " + array.length());
				System.out.println("Data configuration: " + array.getOrder());
				System.out.println("Initial data:");
				array.display();
			}
			
			// This is median of 3 with random pivot
			temp = array.toArray();
			start = System.nanoTime();	
			QuickRandPivot.quickSort(temp, array.length());
			delta = (System.nanoTime() - start);
			ans[4] += delta/1000000000.;
			if (trace)
			{
				System.out.println("\nData after sorting:");
				for (int j = 0; j < temp.length; j++)
					System.out.print(" " + temp[j]);
				System.out.println("\nTime (in nanoseconds): " + delta);
				System.out.println("Time (in seconds): " + delta/1000000000.);
			}
		}
		
		ans[0] /= trials;									// divide by number of trials to get average.
		ans[1] /= trials;									// divide by number of trials to get average.
		ans[2] /= trials;									// divide by number of trials to get average.
		ans[3] /= trials;									// divide by number of trials to get average.
		ans[4] /= trials;									// divide by number of trials to get average.
		// trials are done, display the times and such
		
		try{
		toText.println(output("Simple Quicksort - pivot = last", array.length(), array.getOrder(), trials, ans[0]));
		toText.println();
		toText.println(output("Median of 3 - Base case 5", array.length(), array.getOrder(), trials, ans[1]));
		toText.println();
		toText.println(output("Median of 3 - Base case 10", array.length(), array.getOrder(), trials, ans[2]));
		toText.println();
		toText.println(output("Median of 3 - Base case 20", array.length(), array.getOrder(), trials, ans[3]));
		toText.println();
		toText.println(output("Quick with Random Pivot", array.length(), array.getOrder(), trials, ans[4]));
		toText.println();
		}
		catch (Exception E)
		{	System.out.println("Bad filename!");	}
		
	}	
	
	public String output(String algorithm, int size, String order, int trials, double time)
	{
		return new String("Algorithm : " + algorithm + "\nArray Size: " + size + "\nOrder: " + order
								+ "\nNumber of trials: " + trials + "\nAverage Time: " + time + " sec");
	}
		
}