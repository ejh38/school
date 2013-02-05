// CS 0445 Example 8
// Simple demo of Mergesort
import java.util.*;
public class Example8
{
	public static Random R = new Random();
	// Fill array with random data
	public static void fillArray(Integer [] A, int range)
	{
		for (int i = 0; i < A.length; i++)
		{
			A[i] = new Integer(R.nextInt(range));
		}
	}

	public static void showArray(Integer [] A)
	{
		for (int i = 0; i < A.length; i++)
		{
			System.out.print(A[i] + " ");
		}
		System.out.println();
	}

	public static void main(String [] args)
	{
		int size = Integer.parseInt(args[0]);
		int range = Integer.parseInt(args[1]);
		Integer [] A = new Integer[size];
		fillArray(A, range);
		showArray(A);
		TextMergeQuick.mergeSort(A, A.length);
		showArray(A);
	}
}


