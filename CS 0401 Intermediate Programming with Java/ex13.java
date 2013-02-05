// CS 0401 Fall 2011
// Demonstration of 2-D arrays in Java
// Note that the arrays do NOT have to be "rectangular".  Though it
// is traditional to make all of the rows the same length, this is
// not required in Java, as you can see below.
public class ex13
{
	// Fill the array.  Note that this will work regardless of the
	// dimensions of the array, since the inner loop bases its number
	// of iterations on the length of the current row.
	public static void fill(int [][] B)
	{
		for (int i = 0; i < B.length; i++)
			for (int j = 0; j < B[i].length; j++)
				B[i][j] = i + j;
	}

	// Print the array.  Same idea with regard to dimensions
	public static void print(int [][] B)
	{
		for (int i = 0; i < B.length; i++)
		{
			for (int j = 0; j < B[i].length; j++)
			{
				System.out.print(B[i][j] + " ");
			}
			System.out.println();
		}
	}
	public static void main(String [] args)
	{
		int [][] A1, A2;
		int rows = 4;
		int cols = 8;

		A1 = new int[rows][cols];
		fill(A1);
		print(A1);

		A2 = new int [5][];

		// Make each row of this array one item larger than the
		// previous row
		for (int i = 0; i < A2.length; i++)
		{
			A2[i] = new int[i+1];
		}
		// Use the same fill and print methods
		fill(A2);
		print(A2);
	}
}