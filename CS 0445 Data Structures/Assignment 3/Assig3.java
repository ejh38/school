/******************************************
 * Zach Sadler
 * zps6@pitt.edu
 * CS 0445 Assignment 3
 * Takes in expressions, one line at a time, and evaluates them
 * using recursion. Has some exception handling, error codes,
 * but can also print out multiple errors.
 ******************************************/

import java.io.*;
import java.util.*;
public class Assig3
{
	public static void main(String [] args)
	{	
		Scanner inScan = new Scanner(System.in);
 		boolean cont = true;
 		String input;
 		while (cont)
 		{
	 		System.out.println("Please enter an expression (or type 'quit' to quit):");
 			input = new String(inScan.nextLine());
 			if (!input.equals("quit"))
	 		{
	 			// evaluating each line in a try/catch block, so in case the index goes out of bounds
	 			// (this typically happens with whitespace at the end of the string)
	 			try{
	 			Assig3 A = new Assig3(input);
				int result = A.evaluate();
				if (result != -1111111111)		// this is for error checking : -1111111111 is the return value on an error

					System.out.println(input + " = " + result + "\n");
	 			}
	 			catch (Exception E)
	 			{
	 				System.out.println("Your expression was invalid: InvalidExpressionException: Ended with a space");
	 			}
	 		}
	 		else
	 			cont = false;
		}
		System.out.println("\n\nGoodbye! Have a nice day!");
	}
	
	// leftParens, rightParens for parens checking
	// index, data, curr used throughout for position within the string
	// error used for homemade exceptions
	private int index, leftParens, rightParens;
	private String data;
	private Character curr;
	private boolean error;
	
	public int evaluate()
	{		
		int ans = 0;						// initialize variables
		error = false;
		leftParens = 0;
		rightParens = 0;
		curr = getNextChar();
		while (index < data.length() & !curr.equals('.'))
		{
			ans += getExpr();				// keep going through, adding on expressions
			index++;						// this is necessary to keep it looking
		}
		if (leftParens != rightParens)		// parens checking
		{
			error = true;
			System.out.println("Your expression was invalid: InvalidExpressionException: Unequal parentheses");
		}
		if (error)
			return -1111111111;				// this is the error code for main
		return ans;							// if no error, return the answer!
	}
	
	public int getExpr()
	{
		int ans = 0;						// initialize this individual expression to 0
		curr = getNextChar();				// get the next char
		ans += getTerm();					// every expr begins with a term
		curr = getNextChar();				
		// back from getTerm, now we check if there's an op (term op term)
		
		if (curr.equals('+'))				
		{
			index++;
			curr = getNextChar();
			ans += getTerm();
		}
		if (curr.equals('*'))
		{
			index++;
			curr = getNextChar();
			ans *= getTerm();
		}
		if (curr.equals('-'))
		{
			index++;
			curr = getNextChar();
			ans -= getTerm();
		}
		if (curr.equals('/'))
		{
			index++;
			curr = getNextChar();
			ans /= getTerm();
		}
		if (curr.equals('%'))
		{
			index++;
			curr = getNextChar();
			ans %= getTerm();
		}
		// now we either did the term op term, or there was no 'op term'
		// either way, check for a closing parens
		curr = getNextChar();
		if (curr.equals(')'))
		{
			while (curr.equals(')'))
			{
				index++;					// increment past the parens
				curr = getNextChar();
				rightParens++;
			}
		}
		return ans;							// return the term or term op term
	}
	
	public int getTerm()
	{
		int ans = 0;						// initialize this term to 0
		curr = getNextChar();
		if (Character.isDigit(curr))		// if we find a digit, get the rest (if there are some)
			return ans + getNum(0);			// calls the function from A3Help (with slight modifications)
		else if (curr.equals('('))			// if we don't find a digit, but a parens, then get the associated expr
		{			
			index++;
			leftParens++;
			ans += getExpr();
		}
		else								// if we don't get a digit or a parens, we have an illegal character
		{
			System.out.println("Your expression was invalid: InvalidExpressionException: Illegal Character");
			error = true;
		}
		return ans;							// return the digits or (expr)
	}		
	
	// Create a new object
	public Assig3(String line)
	{
		index = 0;
		data = new String(line);
	}
	
	public char getNextChar()
	{
		if (index >= data.length()) 	    // We hit the end of the string while looking for something else
		{								
			System.out.println("Your expression was invalid: InvalidExpressionException: Unexpected End of Line 1");
			error = true;
			return '.';
		}
		// skip all the whitespace
		while(Character.isWhitespace(data.charAt(index)))
			index++;
		return data.charAt(index);	
	}	

	// the getNum function from A3Help, with slight modifications
	public int getNum(int val)
	{
		int ans = 0, dig;
		if (index >= data.length())  		// We hit the end of the string while looking for a digit. This happens rarely.
		{									
			System.out.println("Your expression was invalid: InvalidExpressionException: Unexpected End of Line 2");
			error = true;
			return val;
		}
		if (!Character.isDigit(data.charAt(index)))   // Base case end of String.  Return what we have
		{	
			return val;
		}
		else  // Not end, so look at the next character
		{
			char curr = data.charAt(index);
			index++;					// Incrememnt the index
			dig = curr - '0';			// Convert char to int
			val = val * 10 + dig;		// Mult. prev. by 10 and add new digit.
			ans = getNum(val);			// Recursively process rest of number
			return ans;
		}
	}	
}		