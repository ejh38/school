// CS 0445 Spring 2012
// Comparison of fixed size Bag (ArrayBag) and dynamic size
// list (ResizableArrayBag).  Note that since both implement
// BagInterface, they are functionally equivalent under
// normal circumstances.  The differences become evident when
// the array fills, as discussed in lecture.

public class Example5
{
	// Note the difference in the headers for the addItems method and the
	// showItems method.  The first is a regular method which has a
	// parameterized type as a parameter.  However, the second is actually
	// a generic, parameterized method, which should work for a BagInterface
	// of any Java type.  
	public static void addItems(BagInterface<Integer> B, int N)
	{
		System.out.println("Adding: ");
		for (int i = 1; i <= N; i++)
		{
			Integer newI = new Integer(i);
			if (B.add(newI))
				System.out.println("Added " + newI);
			else
				System.out.println("No room for " + newI);
		}
		System.out.println();
	}
	
	public static <T> void showItems(BagInterface<T> B)
	{
		T [] items = B.toArray();
		for (T x: items)
			System.out.print(x + " ");
		System.out.println();
	}

	public static void main(String [] args)
	{
		BagInterface<Integer> fixBag = new ArrayBag<Integer>(6);
		BagInterface<Integer> dynBag = new ResizableArrayBag<Integer>(6);

		addItems(fixBag, 10);
		addItems(dynBag, 10);
		System.out.println("Fixed Bag contains:");
		showItems(fixBag);
		System.out.println();
		System.out.println("Dynamic Bag contains:");
		showItems(dynBag);
	}
}