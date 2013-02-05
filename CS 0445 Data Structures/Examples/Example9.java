// CS 0445 Example 9
// Demonstration of simple QuickSort algorithm and author's median of three  
// version.  Note that both sort the data correctly.  However, we don't see
// here how much work each takes for the sort.

import javax.swing.*;

public class Example9 implements Runnable
{
	// Fill an array with the numbers entered by the user.  Do this by
	// splitting the String on single spaces into an array of Strings.
	// Then parse each of the Strings into an int.  No error checking is
	// done, so if there is a problem with the input (not valid numbers
	// or even if there is more than one blank between numbers or an extra
	// blank at the end) the program will crash.

	public Integer [] storeA;
	public void fillArray(String s)
	{
		String [] data = s.split(" ");
		storeA = new Integer[data.length];
		for (int i = 0; i < data.length; i++)
		{
			storeA[i] = new Integer(Integer.parseInt(data[i]));
		}
	}

	public void copyArray(Integer [] newA)
	{
		for (int i = 0; i < storeA.length; i++)
			newA[i] = storeA[i];
	}

	public void showArray(Integer [] A)
	{
		for (int i = 0; i < A.length; i++)
		{
			System.out.print(A[i] + " ");
		}
		System.out.println();
	}

	public void run()
	{
		Integer [] A1 = new Integer[storeA.length], A2 = new Integer[storeA.length];
		copyArray(A1);
		System.out.println("Before simple Quicksort");
		showArray(A1);
		Quick.quickSort(A1, A1.length);
		System.out.println("After simple Quicksort");
		showArray(A1);
		System.out.println();
		copyArray(A2);
		System.out.println("Before Med-of-3 Quicksort");
		showArray(A2);
		TextMergeQuick.quickSort(A2, A2.length);
		System.out.println("After Med-of-3 Quicksort");
		showArray(A2);
		System.exit(0);
	}

	public Example9()
	{
		String input = JOptionPane.showInputDialog(null, 
			           "Enter some integers, separated by blanks");
		fillArray(input);
	}

	public static void main(String [] args)
	{
		// A thread is used here so that the size of the run-time stack can be
		// increased.  Don't worry about the theory of how the Threading works,
		// but here are the basics of how to use it:
		//		The class on which the Thread will run must implement the
		// Runnable interface, as shown in the header above
		//		The run() method is the only method in the Runnable interface,
		// and it is where the "work" will be done, as shown above
		//		The Thread is started by passing the Runnable object into it
		// and calling the start() method, as shown below.
		Example9 E = new Example9();
		(new Thread(E)).start();
	}
}


