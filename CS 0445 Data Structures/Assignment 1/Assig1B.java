// CS 0445 Spring 2012
// Assig1B driver program.  This program must work as is with your
// MyBuffer class and Product class hierarchy.  Look at the code 
// carefully to help you to determine the correct implementation of
// your classes.

import java.util.*;

public class Assig1B
{
	public static void main(String [] args)
	{
		MyBuffer<Product> theBuff = new MyBuffer<Product>(8);

		initData(theBuff);

		System.out.println("Buffer Initialized");

		theBuff.saveToFile("A1A.out");
		System.out.println("Buffer Saved to File");

		theBuff.clear();
		System.out.println("Buffer Cleared");

		theBuff.restoreFromFile("A1A.out");
		System.out.println("Buffer restored");

		Object [] theData = new Object[theBuff.size()];
		int count = 0;
		while (!(theBuff.isEmpty()))
		{
			theData[count] = theBuff.consumeItem();
			count++;
		}

		System.out.println("Here is the data:");
		for (int i = 0; i < theData.length; i++)
		{
			System.out.println(theData[i]);
		}
		System.out.println();

		System.out.println("Sorting the data");
		Arrays.sort(theData);
		System.out.println();

		System.out.println("Here is the data:");
		for (int i = 0; i < theData.length; i++)
		{
			System.out.println(theData[i]);
		}
	}

	public static void initData(Bufferer<Product> buff)
	{
		Variable v = new ByVolume("Bleach", 0.01, 128);
		buff.produceItem(v);
		v = new ByVolume("Milk", 0.02, 128);
		buff.produceItem(v);
		Product p = new Fixed("TV", 800.0);
		buff.produceItem(p);
		p = new Fixed("DVD", 200.0);
		buff.produceItem(p);
		v = new ByWeight("Sugar", 0.005, 80);
		buff.produceItem(v);
		v = new ByWeight("Salt", 0.01, 400);
		buff.produceItem(v);
	}

}
