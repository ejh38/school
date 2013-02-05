/* CS 0445 Data Structures Spring 2012
   This example demonstrates some simple recursive methods in Java.
   This is largely the same as a handout given in CS 0401 last term.  It
   is meant to review / refresh what you learned about recursion in your
   CS 0401 course
*/  
import java.io.*; 
public class Example7
{
	// Method to generate a string of 2N blanks
	public static String get_indent(int N)
	{
		String S = new String("");
		for (int i = 0; i < N; i++)
			S = S + "  ";
		return S;
	}

	// Recursive calculation of N!.  Note that I reject negative numbers by
	// outputting a message and returning -1.  The calling program can test
	// to see if the result is valid if desired.  Alternatively, I could throw
	// an exception if N is invalid (as shown in the .ppt slides)
	public static int fact(int N)
	{
		if (N < 0)		// Base case -- error (but still a base case)
		{
			System.out.println("Invalid argument");
			return -1;
		}
		else if (N <= 1)	// Base case (N = 1 or N = 0).  Note that we are
							// stopping at N = 1 rather than N = 0 to "save"
			return 1;		// an extra recursive call.  More on the efficiency
							// of recursion will be discussed in CS 0445 and
							// CS 1501.
		else
			return (N * fact(N-1));
	}

	// This method does the same calculations as fact above, but with some
	// extra output to trace its behavior.
	public static int fact_trace(int N)
	{
		String indent = get_indent(N);  // Get a string of spaces to show
						// level of the recursive call through indenting

		System.out.println(indent + "Fact: " + N);
		if (N < 0)
		{
			System.out.println(indent + "Invalid argument");
			return -1;
		}
		else if (N <= 1)
		{
			System.out.println(indent + "Base case: N = " + N);
			System.out.println(indent + "Returning " + N + "! = " + 1);
			return 1;
		}
		else
		{
			System.out.println(indent + "Calling " + (N-1) + "!");
			int rec_ans = fact_trace(N-1);
			System.out.println(indent + "Recursive " + (N-1) + "! = " + rec_ans);
			int ans = N * rec_ans;
			System.out.println(indent + "Returning " + N + "! = " + ans);
			return ans;
		}
	}

	// Another simple example of a recursive method.  This one calculates
	// an integer power of some number.  Note the base case and the
	// recursive case below.
	public static int power(int base, int exp)
	{
		if (exp < 0)
		{
			System.out.println("Invalid exponent");
			return 0;
		}
		else if (exp == 0)
			return 1;
		else
			return (base * power(base, exp-1));
	}

	// Iterative method to calculate an integer power.  Compare this
	// code to the recursive version above.  Note that the "base case"
	// here (exp == 0) occurs when the loop does not iterate at all,
	// compared to the recursive code in which no recursive calls are
	// made.  Each iteration of the loop corresponds to a recursive
	// call in our recursive version.
	public static int pow_loop(int base, int exp)
	{
		if (exp < 0)
		{
			System.out.println("Invalid exponent");
			return 0;
		}
		else
		{
			int ans = 1;
			for (int i = 1; i <= exp; i++)
				ans *= base;
			return ans;
		}
	}

	public static void main (String [] args) throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(
			                                   System.in));
		System.out.print("Enter a non-negative number: ");
		int num = Integer.parseInt(br.readLine());
		int ans = fact(num);
		System.out.println(num + "! = " + ans);
		ans = fact_trace(num);
		System.out.println(num + "! = " + ans);

		System.out.print("Enter an int base: ");
		int base = Integer.parseInt(br.readLine());
		System.out.print("Enter an int exponent: ");
		int exp = Integer.parseInt(br.readLine());
		ans = power(base, exp);
		System.out.println(base + " to the " + exp + " = " + ans);
		ans = pow_loop(base, exp);
		System.out.println(base + " to the " + exp + " = " + ans);
	}

}
