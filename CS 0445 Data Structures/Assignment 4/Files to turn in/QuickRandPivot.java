/*************************************************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * This is the simple Quick.java version of QuickSort, but with
 * A pivot chosen randomly. A significant speed increase was found
 * When I adjusted the Random rand = new Random(); call to be static
 * Instead of calling it during each partition.
 * The idea is you find a random index, swap it with the last,
 * then do the same sort as Quick.java.
 *************************************************************/

import java.util.*;

public class QuickRandPivot
{
	public static <T extends Comparable<? super T>>
		   void quickSort(T[] array, int n)
	{
		quickSort(array, 0, n-1);
	} // end quickSort

	public static <T extends Comparable<? super T>>
		   void quickSort(T[] array, int first, int last)
	{
		if (first < last)
		{
			// create the partition: Smaller | Pivot | Larger
			int pivotIndex = partition(array, first, last);
			
			// sort subarrays Smaller and Larger
			quickSort(array, first, pivotIndex-1);
			quickSort(array, pivotIndex+1, last);
		} // end if
	}  // end quickSort

	static Random rand = new Random();
	
	private static <T extends Comparable<? super T>>
	        int partition(T[] a, int first, int last)
	{
		
		int pivotIndex = first + rand.nextInt(last - first + 1);
		swap(a, pivotIndex, last);
		pivotIndex = last;
		T pivot = a[last];

		// determine subarrays Smaller = a[first..endSmaller]
		//                 and Larger  = a[endSmaller+1..last-1]
		// such that elements in Smaller are <= pivot and 
		// elements in Larger are >= pivot; initially, these subarrays are empty

		int indexFromLeft = first; 
		int indexFromRight = last - 1;

		boolean done = false;
		while (!done)
		{
			// starting at beginning of array, leave elements that are < pivot; 
			// locate first element that is >= pivot
			while (a[indexFromLeft].compareTo(pivot) < 0)
				indexFromLeft++;

			// starting at end of array, leave elements that are > pivot; 
			// locate first element that is <= pivot

			while (a[indexFromRight].compareTo(pivot) > 0 && indexFromRight > first)
				indexFromRight--;

			// Assertion: a[indexFromLeft] >= pivot and 
			//            a[indexFromRight] <= pivot.

			if (indexFromLeft < indexFromRight)
			{
				swap(a, indexFromLeft, indexFromRight);
				indexFromLeft++;
				indexFromRight--;
			}
			else 
				done = true;
		} // end while

		// place pivot between Smaller and Larger subarrays
		swap(a, pivotIndex, indexFromLeft);
		pivotIndex = indexFromLeft;

		// Assertion:
		// Smaller = a[first..pivotIndex-1]
		// Pivot = a[pivotIndex]
		// Larger  = a[pivotIndex + 1..last]

		return pivotIndex; 
	}  // end partition

	private static void swap(Object [] a, int i, int j)
	{
		Object temp = a[i];
		a[i] = a[j];
		a[j] = temp; 
	} // end swap
}