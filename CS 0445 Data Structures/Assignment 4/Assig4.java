/***************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * Driver to test different sorting
 * algorithms
 ****************************/
 
import java.util.*;
import java.io.*;

public class Assig4
{
	public static void main(String [] args)
	{
		int size, trials;
		String fName;
		Scanner inScan = new Scanner(System.in);
		System.out.print("\nEnter array size: ");
		size = inScan.nextInt();
		System.out.print("Enter number of trials: ");
		trials = inScan.nextInt();
		inScan.nextLine();									// flush out the line return
		System.out.print("Enter file name: ");
		fName = inScan.nextLine();
		System.out.println(fName);
		
		new Assig4(size, trials, fName);
	}
	
	boolean trace = false;
	
	public Assig4(int size, int trials, String fName)
	{	
		if (size <= 20)
			trace = true;
		// make the three arrays
		Integer [] randArray = new Integer[size];
		Integer [] sortArray = new Integer[size];
		Integer [] revArray = new Integer[size];
		
		// initialize them
		randArray = fillRandArray(randArray);
		sortArray = fillSortArray(sortArray);
		revArray = fillRevArray(revArray);

		displayArray(randArray);
	/*	
		double ans = 0;
		for (int i = 0; i < trials; i++)
		{
			randArray = fillRandArray(randArray);
			long start = System.nanoTime();	
			Quick.quickSort(randArray, randArray.length);
			long delta = (System.nanoTime() - start);
			ans += delta/1000000000.;
			System.out.println(delta);
		}
		ans /= trials;									// divide by number of trials to get average.
		System.out.println(output("Quick", size, "Random", trials, ans));
	*/
		runTrials(randArray, trials, fName);	
		
	}
	
	public void runTrials(Integer [] array, int trials, String fName)
	{	
		double ans = 0;
		String algorithm = new String("Quick");
		String order = new String("Random");
		
		for (int i = 0; i < trials; i++)
		{
			array = fillRandArray(array);
			long start = System.nanoTime();	
			Quick.quickSort(array, array.length);
			long delta = (System.nanoTime() - start);
			ans += delta/1000000000.;
			System.out.println(delta);
		}
		ans /= trials;									// divide by number of trials to get average.
		try{
		PrintWriter toText = new PrintWriter(new FileOutputStream(fName, false));
		toText.println(output(algorithm, array.length, order , trials, ans));
		toText.println();
		toText.close();
		}
		catch (Exception E)
		{	System.out.println("Bad filename!");	}
	}
		
	
	public Integer [] fillRandArray(Integer [] array)
	{
		Random rng = new Random();
		for (int i = 0; i < array.length; i++)
			array[i] = rng.nextInt();

		return array;
	}
		
	public int [] fillSortArray(int [] array)
	{
		for (int i = 0; i < array.length; i++)
			array[i] = i;
			
		return array;
	}
		
	public int [] fillRevArray(int [] array)
	{
		for (int i = array.length - 1; i > 0; i--)
			array[array.length - 1 - i] = i;
			
		return array;
	}	
	
	public void displayArray(Integer [] array)
	{
		for (int i = 0; i < array.length; i++)
			System.out.print(" " + array[i]);
	}	
	
	public String output(String algorithm, int size, String order, int trials, double time)
	{
		return new String("Algorithm : " + algorithm + "\nArray Size: " + size + "\nOrder: " + order
								+ "\nNumber of trials: " + trials + "\nAverage Time: " + time);
	}
		
		
}