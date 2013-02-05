// CS 0445 Spring 2012
// Demonstration of using a simple Bag ADT.  The interface
// we are using is BagInterface from the text.  Remember that we are the
// "client" in this case -- using the ADT without being overly concerned
// with how it was implemented.  We will look at implementation details
// soon.

import java.util.*;
import javax.swing.*;
public class Example4
{
	public static void showFreqs(BagInterface<Integer> bg, int rng)
	{
		System.out.println("Here are the frequencies: ");
		int count = 0;
		for (int i = 0; i < rng; i++)
		{
			Integer curr = new Integer(i);
			int freq = bg.getFrequencyOf(curr);
			System.out.println("Value: " + curr + "  Freq: " + freq);
			count += freq;	
		}
		System.out.println("Total items: " + count);
	}
	
	public static void main(String [] args)
	{
		final int range = 20;
		Random r = new Random();
		BagInterface<Integer> b = new ArrayBag<Integer>(100);
		for (int i = 0; i < 100; i++)
		{
			Integer curr = new Integer(r.nextInt(range));
			b.add(curr);
		}
		showFreqs(b, range);
		System.out.println("Please enter the value to remove: ");
		Scanner s = new Scanner(System.in);
		Integer curr = new Integer(s.nextInt());
		int count = 0;
		// We don't have a method to remove all occurrences of an item,
		// so we need to use a loop
		while (b.contains(curr))
		{
			b.remove(curr);
			count++;
		}
		System.out.println(count + " items removed from Bag");
		showFreqs(b, range);
	}
}