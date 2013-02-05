/* CS 0401 Fall 2011 Java Example 4
 * This handout demonstrates the Scanner class and how it can be used
 *
 * For more information on the Scanner class, look it up in the standard
 * Java API Documentaion.
*/
import java.util.*; // Make Scanner class accessible.  The import
	// statement in Java allows the classes and interfaces within a
	// package to be used in a program -- it brings them into scope.
	// For more information on Java packages and the import statement,
	// see: http://download.oracle.com/javase/tutorial/java/package/index.html

public class ex4
{
	//  Experiment with this program to see what happens in various
	//  situations.  For example, note what happens if you enter a
	//  floating point number and nextInt() is used, and what happens
	//	if you enter an int and nextDouble() is used.  Note that this
	//	is consistent with the coercions that Java allows as we discussed
	//  in lecture.

	public static void main (String [] args)
	{
		// We create a Scanner object by passing System.in into a
		// method called a constructor (to create a new object).  We'll
		// talk more about classes and objects soon.  For now, use your
		// intuition to see that the statement below will enable us to
		// get tokens from the computer's standard input (i.e. the
		// console).
		Scanner inScan = new Scanner(System.in);

		// The Scanner class works by separating input into tokens, using
		// a pattern as a delimiter.  By default, "whitespace" is the
		// delimiter (this includes blanks, tabs and new lines).  Thus,
		// Scanner will consider one token to end at the next white space
		// and another to begin after the white space.  Note that the
		// white space can consist of multiple characters.
		// Q: What happens if the user keeps entering only white space
		//    (ex: tabs, blanks and <enter>) when a token is being looked
		//     for?  Try it to find out!
		int iVal;
		float fVal;
		double dVal;
		String s1Val;
		String s2Val;

		System.out.print("Please enter an int: ");
		iVal = inScan.nextInt();

		System.out.print("Please enter a float: ");
		fVal = inScan.nextFloat();
		System.out.print("Please enter a double: ");
		dVal = inScan.nextDouble();

		System.out.print("You entered:\n" + iVal + "\n" + fVal + "\n");
		System.out.print(dVal + "\n");

		// Be careful when using the next() and nextLine() methods in the
		// Scanner class.  next() returns the next String token based on the
		// delimiter as explained above.  However, nextLine() returns a
		// String containing everything up until the next "newline
		// character", disposing of that "character".
		// Here are a couple common issues we face using them:
		// --> If we use the default delimiter (white space) we cannot use
		//     next() to read in a String containing blanks (such as a
		//     person's entire name)
		// --> The nextLine() method may return an empty String if all of
		//     the data on the line was already read in as tokens.
		// To see these issues, experiment with the inputs below.  Try
		// entering two strings on the same line, two strings on different
		// lines, a String with a space, etc. and see what the results are.
		System.out.print("Please enter two strings: ");
		s1Val = inScan.next();
		s2Val = inScan.nextLine();
		System.out.print("You entered:" + s1Val + "\nand:" + s2Val + "\n");

		System.out.print("Please enter two more strings: ");
		s1Val = inScan.nextLine();
		s2Val = inScan.next();

		System.out.print("You entered:" + s1Val + "\nand:" + s2Val + "\n");

		System.out.print("Enter something else: ");
		// Prior to reading, we can test to see if the next token in the
		// stream is a specific type.
		if (inScan.hasNextInt())
		{
			iVal = inScan.nextInt();
			System.out.println("You entered the int " + iVal);
		}
		else if (inScan.hasNextFloat())
		{
			fVal = inScan.nextFloat();
			System.out.println("You entered the float " + fVal);
		}
		// Note: After experimentation, I have not been able to get this next
	    // segment to ever execute.  This is because as long as the data is
		// a legally formatted float, the hasNextFloat method above will
		// always succeed, even if the number is too large to fit into a
		// float.  If the number is too large the value infinity (or
		// -infinity) is returned.  If the number has too many digits of
		// precision (ex: 0.111111111111111111111111111111111111) it is
		// truncated.
		else if (inScan.hasNextDouble())
		{
			dVal = inScan.nextDouble();
			System.out.println("You entered the double " + dVal);
		}
		else
		{
			s1Val = inScan.next();
			System.out.println("You entered the string " + s1Val);
		}
	}
}
