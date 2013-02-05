// CS 0445 Spring 2012
// Help program for Assignment 3
// This program will process a string consisting of integers separated by single
// blank characters, parsing and adding the numbers to return a single int for 
// each string.

import java.io.*;
import java.util.*;
public class working2
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
	 			working2 A = new working2(input);
				int result = A.evaluate();
				if (result != -1111111111)
					System.out.println("\n" + input + " = " + result + "\n");
	 		}
	 		else
	 			cont = false;
 		
		}
	}
	
	// instance data is the String containing the numbers and the index
	// I used the same instance variables for Assignment 3
	private int index;
	private String data;
	private Character curr;
	private int leftParens, rightParens;
	private int opCode;
	private boolean error;

	
	public int evaluate()
	{
		int ans = 0;	
		error = false;
		leftParens = 0;
		rightParens = 0;
		curr = getNextChar();
//		System.out.println("I'm here pre -1");
		while (index < data.length() & !curr.equals('.'))
		{
			ans += getExpr();
			index++;
//			System.out.println("I'm here post -1");
		}
	//	if (leftParens != rightParens)
	//	{
	//		error = true;
	//		System.out.println("Your expression was invalid: InvalidExpressionException: Unequal parentheses");
	//	}
		if (error)
			return -1111111111;
		return ans;	
	}
	
	public int getExpr()
	{
		int ans = 0;
		curr = getNextChar();
	//	System.out.println("I'm here pre 0");
		ans += getTerm();
	//	System.out.println("I'm here post 0: ans is " + ans);
		curr = getNextChar();
	//	System.out.println("CURR is " + curr);
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
		index++;
//		System.out.println("I'm here 1: ans is " + ans);
		if (curr.equals(')'))
		{
//			while (curr.equals(')'))
//			{
				System.out.println("End parens!");
				index++;
				//
			//	curr = getNextChar();
				rightParens++;
		//	}
				System.out.println("I'm here 4");
		}
		return ans;
	}
	
	public int getTerm()
	{
		int ans = 0;
		curr = getNextChar();
		// base case is end parens, we are done
	//	if (curr.equals(')'))
	//	{
//			while (curr.equals(')'))
//			{
	//			System.out.println("End parens!");
	//			index++;
				//
	//			curr = getNextChar();
	//			rightParens++;
		//	}
	//			System.out.println("I'm here 4");

	//		return ans;
	//	}
		// 2nd base case is digits, return the digits
		//else
		 if (Character.isDigit(curr))
			{
			System.out.println("I'm here 2");
			return ans + getNum(0);			
				}
		else if (curr.equals('('))
		{
			System.out.println("Got a parens");
			index++;
			leftParens++;
			System.out.println("I'm here pre 3");
			ans += getExpr();
			System.out.println("I'm here post 3: ans is " + ans);

			//return ans + getExpr();
		}
				else
		{
			System.out.println("Your expression was invalid: InvalidExpressionException: Illegal Character");
			error = true;
		//	return ans;
		}
		return ans;
	}		
	
	// Create a new object
	public working2(String line)
	{
		index = 0;
		data = new String(line);
	}
	
	public char getNextChar()
	{
		if (index >= data.length())   // Base case end of String.  Return what we have
		{							// so far
			System.out.println("Your expression was invalid: InvalidExpressionException: Unexpected End of Line 1");
			error = true;
			return '.';
		}
		while(Character.isWhitespace(data.charAt(index)))
		{
			index++;
		}
		return data.charAt(index);
		
	}	

	// Recursively get a number digit by digit from the String.  I have trace code
	// in here to show the process better.
	// The int parameter is necessary because the digits build up to the final 
	// number.
	public int getNum(int val)
	{
		int ans = 0, dig;
	//	System.out.println("val = " + val);
		if (index >= data.length())   // Base case end of String.  Return what we have
		{							// so far
			System.out.println("Your expression was invalid: InvalidExpressionException: Unexpected End of Line 2");
			error = true;
			return val;
		}
		if (!Character.isDigit(data.charAt(index)))   // Base case end of String.  Return what we have
		{							// so far
	//		System.out.println("End of digits, ans = " + val);
			return val;
		}
		else  // Not end, so look at the next character
		{
			char curr = data.charAt(index);
	//		System.out.println("curr = " + curr);
			index++;					// Incrememnt the index
			dig = curr - '0';			// Convert char to int
			val = val * 10 + dig;		// Mult. prev. by 10 and add new digit.
			ans = getNum(val);			// Recursively process rest of number
	//		System.out.println("Recursive ans = " + ans);
			return ans;
		}
	}	
	
}
			
		