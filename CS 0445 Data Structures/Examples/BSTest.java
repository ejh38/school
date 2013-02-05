// CS 0445 Spring 2012
// Demonstration of Binary Search using both an iterative version and
// a recursive version.  A recursive version of Sequential Search is
// also shown.  Trace versions of recursive Binary Search and recursive
// Sequential Search are shown to indicate the recursive calls and
// behavior of the algorithms.  Trace this handout carefully!

import java.util.*;
import java.io.*;

public class BSTest implements Runnable
{
	private Integer [] data;
	private int bicomps, brcomps, scomps, reps, num, bifound, 
		brfound, sfound;
	private Integer item;
       
	public BSTest() throws IOException
	{
		bicomps = 0; brcomps = 0; scomps = 0; // initialize total comps to 0
		reps = 1000;  // how many searches will we try?
		bifound = 0; brfound = 0; sfound = 0;

		BufferedReader BR = new BufferedReader(
			new InputStreamReader(System.in));
		System.out.println("Please enter size of array: ");
		num = Integer.parseInt(BR.readLine());
		loadData(num);
		(new Thread(this)).start();
	}

	// I am using a Thread to run this program so that I can set the run-time stack to
	// be larger.  Don't worry about the mechanics of using Threads here.   The
	// important thing is what is being executed in this method.
	public void run()
	{
		int loc;
		Integer item;
		for (int iter = 0; iter < reps; iter++)
		{
			item = new Integer((int) (Math.random() * 50000));
			loc = binarySearchi(data, item);
			if (loc >= 0)
				bifound++;
			loc = binarySearchr(data, item, 0, data.length-1);
			if (loc >= 0)
				brfound++;
			loc = recSeqSearch(data, item, 0);
			if (loc >= 0)
				sfound++;
		}
		double biave = (double)bicomps/reps;
		double brave = (double)brcomps/reps;
		double save = (double)scomps/reps;

		System.out.println("Iterative Binary Search: ");
		System.out.println("    Total comps: " + bicomps);
		System.out.println("    Ave. comps: " + biave);
		System.out.println("    Found: " + bifound + " out of " + reps);
		System.out.println("Recursive Binary Search: ");
		System.out.println("    Total comps: " + brcomps);
		System.out.println("    Ave. comps: " + brave);
		System.out.println("    Found: " + brfound + " out of " + reps);
		System.out.println("Recursive Sequential Search: ");
		System.out.println("    Total comps: " + scomps);
		System.out.println("    Ave. comps: " + save);
		System.out.println("    Found: " + sfound + " out of " + reps);
		System.out.println();
		if (num <= 32)
		{
			System.out.println("Now tracing recursive Searches");
			item = new Integer((int) (Math.random() * 50000));
			loc = binarySearchTr(data, item, 0, data.length-1);
			if (loc >= 0)
				System.out.println(item + " has been found at loc " + loc);
			else
				System.out.println(item + " is not present ");
			System.out.println();
			// See previous handout (SeqSDemo.java) for method below
			loc = SeqSDemo.recSeqSearchTr(data, item, 0);
			if (loc >= 0)
				System.out.println(item +  " has been found at loc " + loc);
			else
				System.out.println(item + " is not present ");
		}
	}
   
	public static void main (String [] args) throws IOException
	{
		BSTest prog = new BSTest();
	}

	public void loadData(int num)
	{
		data = new Integer[num];
		for (int i = 0; i < num; i++)
		{
			Integer item = new Integer((int) (Math.random() * 50000));
			data[i] = item;
		}
		Arrays.sort(data);
		bicomps = 0; brcomps = 0; scomps = 0;
		System.out.println("Data loaded");
	}
 
	// In iterative Binary Search (with which you should already be familiar)
	public <T extends Comparable<? super T>> int binarySearchi (T [] a, T obj) 
	{
		int low = 0;
		int high = a.length-1;
		while (low <= high) 
		{
			bicomps++;  
			int mid = (low + high)/2;
			T midItem = a[mid];
			int res = midItem.compareTo(obj);
			if (res < 0)
				low = mid + 1;
			else if (res > 0)
				high = mid - 1;
			else
				return mid;
		}
		return -1;
	}

	public <T extends Comparable<? super T>> int binarySearchr (T [] a, T obj, int low, int high) 
	{
		int ans;
		if (low <= high)  // if (low > high) the BASE CASE is reached
		{
			brcomps++;  // consider one comparison for each
			// CALL of the method

			int mid = (low + high)/2;
			T midItem = a[mid];

			// Note the recursive calls below -- we are calling the
			// same method, but using different parameters to
			// indicate a change in "size" of the array.  In reality
			// the physical array does not change -- we are simply
			// considering smaller and smaller pieces of it
			int res = midItem.compareTo(obj);
			if (res < 0)
				return(binarySearchr(a, obj, mid + 1, high));
			else if (res > 0)
				return(binarySearchr(a, obj, low, mid - 1));
			else
				return mid;
		}
		return -1;
	}
       
	public <T extends Comparable<? super T>> int binarySearchTr (T [] a, T obj, int low, int high) 
	{
		for (int i = low; i < high; i++) System.out.print(" ");
		System.out.print("LOW: " + low + " HIGH:" + high);

		int ans, temp;
		if (low <= high) 
		{
			int mid = (low + high)/2;
			T midItem = a[mid];
			System.out.print(" MID: " + mid);
			System.out.print(" KEY: " + obj + " MIDITEM: " + midItem);
                     
			int res = midItem.compareTo(obj);
			if (res < 0)
			{
				System.out.println(" RECURSE RIGHT");
				temp = binarySearchTr(a, obj, mid + 1, high);
				for (int i = low; i < high; i++) System.out.print(" ");
				System.out.println("PASSING ON " + temp);
				return (temp);
			}
			else if (res > 0)
			{
				System.out.println(" RECURSE LEFT");
				temp = binarySearchTr(a, obj, low, mid - 1);
				for (int i = low; i < high; i++) System.out.print(" ");
				System.out.println("PASSING ON " + temp);
				return (temp);
			}
			else
				return mid;
		}
		System.out.println(" BASE CASE: Return -1");
		return -1;
	}

	// This is the same recursive sequential search as in SeqSDemo.java.  However,
	// I needed it as an instance method here so it could modify the scomps variable.
	public <T extends Comparable<? super T>> int recSeqSearch(T [] a, T key, int first)
	{
		if (first >= a.length)
			return -1;
		scomps++;
		if (a[first].compareTo(key) == 0)
			return first;
		else return recSeqSearch(a, key, first+1);
	}
}