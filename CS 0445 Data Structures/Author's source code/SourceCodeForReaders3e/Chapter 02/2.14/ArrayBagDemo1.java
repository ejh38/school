/** 
    A test of the methods add, toArray, and isFull, as defined
    in the first draft of the class ArrayBag.
    @author Frank M. Carrano
*/
public class ArrayBagDemo1
{
	public static void main(String[] args) 
	{
   // a bag that is not full
		BagInterface<String> aBag = new ArrayBag1<String>();
      
      // tests on an empty bag
 		testIsFull(aBag, false);

      // adding strings
		String[] contentsOfBag1 = {"A", "A", "B", "A", "C", "A"};
		testAdd(aBag, contentsOfBag1);
 		testIsFull(aBag, false);

   // a bag that will be full
		aBag = new ArrayBag1<String>(7);
      System.out.println("\nA new empty bag:");

      // tests on an empty bag
 		testIsFull(aBag, false);

      // adding strings
		String[] contentsOfBag2 = {"A", "B", "A", "C", "B", "C", "D"};
		testAdd(aBag, contentsOfBag2);
 		testIsFull(aBag, true);
	} // end main
	
   // Tests the method add.
	private static void testAdd(BagInterface<String> aBag, String[] content)
	{
		System.out.print("Adding to the bag: ");
		for (int index = 0; index < content.length; index++)
		{
			aBag.add(content[index]);
         System.out.print(content[index] + " ");
		} // end for
      System.out.println();
      
		displayBag(aBag);
	} // end testAdd

   // Tests the method isFull.
   // correctResult indicates what isFull should return.   
	private static void testIsFull(BagInterface<String> aBag, boolean correctResult)
	{
      System.out.print("\nTesting the method isFull with ");
      if (correctResult)
         System.out.println("a full bag:");
      else
         System.out.println("a bag that is not full:");
      
      System.out.print("isFull finds the bag ");
      if (correctResult && aBag.isFull())
			System.out.println("full: OK.");
		else if (correctResult)
			System.out.println("not full, but it is full: ERROR.");
		else if (!correctResult && aBag.isFull())
			System.out.println("full, but it is not full: ERROR.");
		else
			System.out.println("not full: OK.");
	} // end testIsFull

   // Tests the method toArray while displaying the bag.
	private static void displayBag(BagInterface<String> aBag)
	{
		System.out.println("The bag contains the following string(s):");		
		Object[] bagArray = aBag.toArray();
		for (int index = 0; index < bagArray.length; index++)
		{
			System.out.print(bagArray[index] + " ");
		} // end for
		
		System.out.println();
	} // end displayBag
} // end ArrayBagDemo1
