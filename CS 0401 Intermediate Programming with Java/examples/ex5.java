/* CS 0401 Fall 2010 Java Example 5
   This example demonstrates the switch statement as well as simple formatting
   of numeric output.
*/
import java.util.*;
import java.text.*;  // Needed for formatting "money" values -- see below

public class ex5
{
	public static void main (String [] args)
	{
		Scanner inScan = new Scanner(System.in);

		String title;
		int stars;
		double gross;
		boolean valid;
		NumberFormat formatter = NumberFormat.getCurrencyInstance(Locale.US);
			// This formatter is actually an Object that allows us to format
			// numbers.  We will cover objects a bit later -- then this
			// will make more sense.  For now just see how to do it so you
			// can use it for your Assignment 1.  Note the line here and then
			// the use below.  Also note Section 3.10 of the text, where it
			// shows how to use another formatting object, DecimalFormat

		// As we discussed in lecture, one way of handling a conditional loop
		// is to have two separate inputs -- one to determine if the user
		// wants to continue and one for the actual input.
		System.out.println("Welcome to the Movie Tracker Program");
		System.out.print("Would you like to rate a movie? (yes/no): ");
		String test = inScan.next();
		while (!test.equals("no"))
		{
			inScan.nextLine();  // This line will simply get rid of the
					// carriage return that was left in the input stream
					// after the previous call to next().  As discussed
					// in lecture, we need this because otherwise the
					// nextLine() call below would return an empty string.
			System.out.print("Please enter the movie name: ");
			title = inScan.nextLine();
			System.out.print("Please enter number of stars (0-5): ");
			stars = inScan.nextInt();
			System.out.print("Please enter the gross: ");
			gross = inScan.nextDouble();
			System.out.println();

			valid = true;
			// Note how the switch is set up -- each case must be a constant
			// integer and must be specified separately.  A break is necessary
			// after a case to make the cases exclusive.  Otherwise, the
			// execution will just continue through all of the cases (i.e.
			// matching a case only indicates the "starting point" of the
			// execution, not the stopping point)
			switch (stars)
			{
				case 0:
				case 1:
					System.out.println(title + " is a bomb!");
					System.out.println("Don't waste your money!");
					break;
				case 2:
					System.out.println(title + " is only fair.");
					System.out.println("Wait for the DVD");
					break;
				case 3:
				case 4:
					System.out.println(title + " is pretty good.");
					System.out.println("Worth the entry price");
					break;
				case 5:
					System.out.println(title + " is excellent!");
					System.out.println("See it again!");
					break;
				default:
					System.out.println("Your input was invalid!");
					valid = false;
			}
			// Note that I am checking to see if the number of stars is
			// valid before printing out the gross.  However, I do NOT check
			// to make sure the gross value was valid (ex: what if it is
			// negative) and if any numeric data are entered incorrectly
			// the whole program will crash!  Later we will see how to handle
			// these problems nicely.

			// The method call format() produces a nice formatting of double
			// values to look like money values.  Note the syntax.  We will
			// discuss classes, objects and methods in more detail soon.
			if (valid)
			{
				System.out.println("Total Gross: " + formatter.format(gross));
				System.out.println();
			}
			System.out.print("Would you like to rate a movie? (yes/no): ");
			test = inScan.next();
		}
	}

}
