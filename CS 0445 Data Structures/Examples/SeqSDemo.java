// CS 0445 Spring 2012
// Demonstration of Sequential Search using both an iterative version and a
// recursive version. A trace version of the recursive algorithm is also shown
// so you can better see the behavior of the recursive algorithm.  For the
// sake of simplicity, both versions are generic functions that search an array,
// rather than being within a BagInterface or some other ADT. However, recall that
// the contains() method in the Java BagInterface is in fact a sequential search
// (done iteratively).
// Trace this handout carefully!

import java.io.*;

public class SeqSDemo
{
	private Integer [] data;

	public SeqSDemo() throws IOException
	{
		BufferedReader BR = new BufferedReader(
					new InputStreamReader(System.in));
		System.out.println("Please enter size of the array");
		int num = Integer.parseInt(BR.readLine());
		loadData(num);
		System.out.println("The data is: ");
		for (int i = 0; i < num-1; i++)
		{
			System.out.print(data[i] + ", ");
		}
		System.out.println(data[num-1]);

		System.out.println("Please enter the item to search for:");

		Integer key = new Integer(BR.readLine());
		int loc = seqSearch(data, key);
		if (loc >= 0)
			System.out.println("Iteratively, " + key + " found at index " + loc);
		else
			System.out.println(key + " was not found ");

		loc = recSeqSearch(data, key, 0);
		if (loc >= 0)
			System.out.println("Recursively, " + key + " found at index " + loc);
		else
			System.out.println(key + " was not found ");

		System.out.println("\nTracing recursive version:\n");
		loc = recSeqSearchTr(data, key, 0);
		if (loc >= 0)
			System.out.println("Recursively, " + key + " found at index " + loc);
		else
			System.out.println(key + " was not found ");

	}

	public static void main (String [] args) throws IOException
	{
		SeqSDemo prog = new SeqSDemo();
	}

	public void loadData(int num)
	{
		data = new Integer [num];
		for (int i = 0; i < num; i++)
		{
			Integer item = new Integer((int) (Math.random() * 50000));
			data[i] = item;
		}
	}

    // Note that for this algorithm, the recursive solution and the iterative
    // solution are quite similar in length.  However, also note that there
    // is no loop in the recursive version -- the "iteration" is accomplished
    // through recursive calls of the method.
	public static <T extends Comparable<? super T>> int seqSearch(T [] a, T key)
	{
		for (int i = 0; i < a.length; i++)
			if (a[i].compareTo(key) == 0)
				return i;
		return -1;
	}

	// In this version we need an extra parameter to indicate the current
	// position within the array.  With each recursive call, the position
	// increments by one until either the key is found or we get to the
	// end of the array.  Recursive implementations often need additional
	// parameters so that more state information can be passed from one
	// call to the next.
	public static <T extends Comparable<? super T>> int recSeqSearch(T [] a, T key, int first)
	{
		if (first >= a.length)	// base case not found
			return -1;
		else if (a[first].compareTo(key) == 0)	// base case found
			return first;
		else return recSeqSearch(a, key, first+1);	// recursive case
	}

	// Trace version of recursive sequential search
	public static <T extends Comparable<? super T>> int recSeqSearchTr(T [] a, T key, int first)
	{
		for (int i = first; i < a.length; i++) System.out.print(" ");
		System.out.print("FIRST: " + first + " LAST: " + (a.length-1));

		if (first >= a.length)
		{
			System.out.println(" Base case not found");
			return -1;
		}
		else
		{
			System.out.print(" Key: " + key + " Curr: " + a[first]);
			if (a[first].compareTo(key) == 0)
			{
				System.out.println(" Base case found: Return " + first);
				return first;
			}
			else
			{
				System.out.println(" Recursing... ");
				int ans = recSeqSearchTr(a, key, first+1);
				for (int i = first; i < a.length; i++) System.out.print(" ");
				System.out.println("Passing on " + ans);
				return ans;
			}
		}
	}

}