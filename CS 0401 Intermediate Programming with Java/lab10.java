// CS 0401 Fall 2011
// Lab 10
// You must modify this file so that it works as described in the lab handout.
import java.util.*;
import java.io.*;
public class lab10
{
	public static void main(String [] args)
	{
		Scanner inScan, fScan = null;
		int [] A = new int[5];
		inScan = new Scanner(System.in);
		boolean flag;
		do{
			flag = true;
			System.out.println("Please enter the file to read from: ");
			String fName = inScan.nextLine();
			try{
			fScan = new Scanner(new File(fName));

			} catch (FileNotFoundException e) {
				System.out.println("Your file is invalid -- please re-enter");
				flag = false;
			}
		} while (!flag);
		String nextItem;
		int nextInt = 0;
		int i = 0;
		
		String temp;
		int [] B;

		while (fScan.hasNextLine())
		{
			flag = true;
			nextItem = fScan.nextLine();
			try
			{	
				nextInt = Integer.parseInt(nextItem);

			} catch (NumberFormatException e)
			{
				System.out.println(nextItem + " is not an integer -- invalid");
				flag = false;
				i--;
			}
			if (flag);
			{
				try{
					A[i] = nextInt;

				}	catch (ArrayIndexOutOfBoundsException e)
					{
						System.out.println("Resizing array from " + A.length + " to " + 2*A.length);
						B = new int[2*A.length];
						for (int k = 0; k < A.length; k++)
						{
							B[k] = A[k];
						}
						A = B;
						A[i] = nextInt;
					}
					i++;

			}

		}
		

		System.out.println("Here are your " + i + " items:");
		for (int j = 0; j < i; j++)
		{
			System.out.println(A[j] + " ");
		}
	}
}

