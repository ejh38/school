// CS 0445 Spring 2012
// Assig1A driver program.  This program must work as is with your
// MyBuffer class.  Look carefully at all of the method calls so that
// you create your MyBuffer methods correctly.  For example, note the
// constructor calls and the toString() method call.
public class Assig1A
{
	public static void main(String [] args)
	{
		// Testing constructor
		Bufferer<Integer> theBuff = new MyBuffer<Integer>(5);

		// Testing produceItem
		for (int i = 0; i < 6; i++)
		{
			Integer newItem = new Integer(2 * i);
			if (!(theBuff.isFull()))
			{
				theBuff.produceItem(newItem);
				System.out.println(newItem + " added to buffer");
			}
			else
			{
				System.out.println("No room for " + newItem);
			}
		}

		// Testing the SaveRestore interface
		((SaveRestore)theBuff).saveToFile("A1A.out");
		theBuff.clear();
		System.out.println("The buffer has " + theBuff.size() + " items");
		boolean empty = theBuff.isEmpty();
		if (empty)
			System.out.println("The buffer is empty");

		((SaveRestore)theBuff).restoreFromFile("A1A.out");

		System.out.println("Buffer restored");

		// Teseting consumeItem
		while (!(theBuff.isEmpty()))
		{
			Integer oldItem = (Integer) theBuff.consumeItem();
			System.out.println(oldItem + " retrieved from buffer");
		}
		Integer noItem = (Integer) theBuff.consumeItem();
		if (noItem == null)
			System.out.println("Nothing in the buffer");

		// Testing array management
		Bufferer<String> theBuff2 = new MyBuffer<String>(5);
		int count = 1;
		String theItem = new String("Item " + count);
		System.out.println("Producing " + theItem);
		theBuff2.produceItem(theItem);
		for (int i = 0; i < 8; i++)
		{
			count++;
			theItem = new String("Item " + count);
			System.out.println("Producing " + theItem);
			theBuff2.produceItem(theItem);
			theItem = (String) theBuff2.consumeItem();
			System.out.println("Consuming " + theItem);
		}
		int sz = theBuff2.size();
		System.out.println("There are " + sz + " items in the buffer");

		// This code will test the toString() method and the Reverser
		// interface.
		MyBuffer<Integer> newBuff = new MyBuffer<Integer>(10);
		Reverser R = (Reverser) newBuff;
		for (int i = 0; i < 8; i++)
		{
			newBuff.produceItem(new Integer(i));
		}
		System.out.println(newBuff.toString());
		R.reverse();
		System.out.println(newBuff.toString());
		Integer bogus = newBuff.consumeItem();
		bogus = newBuff.consumeItem();
		bogus = newBuff.consumeItem();
		newBuff.produceItem(new Integer(8));
		System.out.println(newBuff.toString());
		R.reverse();
		System.out.println(newBuff.toString());
	}
}
