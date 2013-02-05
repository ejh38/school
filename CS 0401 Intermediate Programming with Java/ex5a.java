/* CS 0401 Fall 2011 Java Example 5a (compare to Example 5b)
   This handout demonstrates some Java control statements, including if statement
   and while loop.  It will read in some scores from a user and then determine the
   average.

   In this version, the user knows how many scores there are and the number of
   scores is read in initially.
*/
import java.util.Scanner; // Make Scanner class accessible

public class ex5a
{
	public static void main (String [] args)
	{
		Scanner inScan = new Scanner(System.in);

		int numItems;
		double currItem = 0.0;
		double sum = 0.0, ave;

		System.out.println("How many scores are there?");
		numItems = inScan.nextInt();

		int count = 0;
		while (count < numItems)  // Keep looping until numItems items have
								  // been read in
		{
			System.out.println("Enter item " + count);
			currItem = inScan.nextDouble();
			if (currItem >= 0.0 && currItem <= 100.0)  // only "count" the
				           // item if it has a valid value.  Because of this
				           // restriction, the actual loop could iterate many
				           // more than numItem times

			{
				sum += currItem;
				count++;
			}
			else
			{
				System.out.println("Data was invalid -- not counted");
			}
		}

		if (numItems > 0)  // make sure we don't divide by zero
		{
			ave = sum / numItems;
			System.out.println("The average of " + numItems + " items is " + ave);
		}
		else
			System.out.println("No data was entered");
	}


}
