import java.util.*;

public class Prob3
{
	public static void main(String [] args)
	{
		Scanner inScan = new Scanner(System.in);
		System.out.print("What number would you like to factor? ");
		int n;
		
		String factorization = "Prime Factorization: ";
		n = inScan.nextInt();
		
		int x = 2;
		while ( n > 1 )
		{
			while (( n % x ) == 0)
			{
				n /= x;
				factorization += Integer.toString(x) + " * ";
			}
			x++;
		}
		
		System.out.print(factorization + "\n");
	}
}