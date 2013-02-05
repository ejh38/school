import java.util.*;

public class Lab3
{
	public static void main(String [] args)
	{
		Scanner inScan = new Scanner(System.in);
		
		int base, big=0, temp=0, temp2;
		System.out.print("Enter an integer base >> ");
		base = inScan.nextInt();
		
		while (base > 1)
		{
			while (big <= 0)
			{
				System.out.print("\nEnter a positive integer X >> ");
				big = inScan.nextInt();
			}
			
			temp2 = big;
			
			for(temp = 0; temp2 >= base; temp++)
			{
				temp2 /= base;
			}
			
			System.out.println("log  " + big + " = " + temp);
			System.out.print("   " + base);
			System.out.println("\n\n");
			
			System.out.print("Enter an integer base >> ");
			base = inScan.nextInt();
			big = 0; temp = 0;
		}
	}
}