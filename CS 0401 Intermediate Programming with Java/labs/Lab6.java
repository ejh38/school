
import java.util.*;
import java.io.*;

public class Lab6
{
	public static void main(String [] args)
	{
		int num = -1;
		Scanner inScan = new Scanner(System.in);
		
		// loops around until a valid input given for number of elements
		// in the array (won't accept num <= 0)
		do
		{
			System.out.println("How many items would you like?");
			num = inScan.nextInt();
		} while (num <= 0);
		
		// make the array
		double [] array = new double[num];
		
		// populate the array with input from user
		for (int value = 0; value < array.length; value++)
		{
			System.out.println("Enter the value for position " + value);
			array[value] = inScan.nextDouble();
		}
		
		// call the methods given below
		System.out.println("The maximum value is: " + max(array));
		System.out.println("The minimum value is: " + min(array));
		System.out.println("The total sum is: " + sum(array));
		System.out.println("The average is: " + ave(array));
		
	}
	
	public static double max(double [] data)
	{
		double max = data[0];								// use the first value as the comparison
		
		for (double i : data)	// couldn't get the for ( i : Ar ) to work
		{
			if (i > max)
				max = i;
		}
		
		return max;
	}
	
	public static double min(double [] data)
	{
		double min = data[0];
		
		for (double i : data)
		{
			if (i < min)
				min = i;
		}
		
		return min;
	}
	
	public static double sum(double [] data)
	{
		double sum = 0;
		
		for (double i : data)
		{
			sum += i;		
		}
		
		return sum;
	}
	
	public static double ave(double [] data)
	{
		 return sum(data)/data.length;
	}

}
		