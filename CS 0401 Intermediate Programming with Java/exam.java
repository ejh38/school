import java.util.*;

public class exam
{
	public static int getInteger(Scanner s, int lowerBound)
	{
		Scanner inScan = s;
		int temp = lowerBound;
		
		while (temp <= lowerBound)
		{
			System.out.println("Enter an integer > " + lowerBound);
			temp = inScan.nextInt();
		}
		
		return temp;
	}
	
	public static void main(String [] args)
	{
		Scanner inScan = new Scanner(System.in);
		int a = getInteger(inScan, 0);
		int b = getInteger(inScan, a);
		
		System.out.println("Your numbers are " + a + " and " + b);
	}
}