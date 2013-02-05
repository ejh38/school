/***************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * Driver to test different sorting
 * algorithms
 ****************************/
 
import java.util.*;
import java.io.*;

public class Assig4interface
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
		
		FileOutputStream fos = null;
		try{
		fos = new FileOutputStream(fName, false);
		} catch (Exception E)
		{}
		new Assig4interface(size, trials, fos);
	}
	
	boolean trace = false;
	PrintWriter toText;
	
	public Assig4interface(int size, int trials, FileOutputStream fos)
	{	
		if (size <= 20)
			trace = true;
		// make the three arrays
		Assig4able randArray = new AlreadyRandom(size);
		Assig4able sortArray = new AlreadySorted(size);
		Assig4able revArray = new AlreadyReverse(size);

		// initialize them
		randArray.fill();
		sortArray.fill();
		revArray.fill();

		randArray.display();
		toText = new PrintWriter(fos);
		
		runTrials(randArray, trials, fos);
		runTrials(sortArray, trials, fos);
		System.out.println("okay");
		runTrials(revArray, trials, fos);
		
		toText.close();

		
	}
	
	public void runTrials(Assig4able array, int trials, FileOutputStream fos)
	{	
		double ans;
		String algorithm = new String("Quick");
		
		ans = 0;
		for (int i = 0; i < trials; i++)
		{
			array.fill();
			Integer [] temp = array.toArray();
			long start = System.nanoTime();	
			System.out.println("okay2");
			Quick.quickSort(temp, array.length());
			long delta = (System.nanoTime() - start);
			ans += delta/1000000000.;
			//System.out.println(delta);
		}
		ans /= trials;									// divide by number of trials to get average.
		try{
		toText.println(output(algorithm, array.length(), array.getOrder(), trials, ans));
		toText.println();
		}
		catch (Exception E)
		{	System.out.println("Bad filename!");	}
			
	}	
	
	public String output(String algorithm, int size, String order, int trials, double time)
	{
		return new String("Algorithm : " + algorithm + "\nArray Size: " + size + "\nOrder: " + order
								+ "\nNumber of trials: " + trials + "\nAverage Time: " + time);
	}
		
		
}