import java.util.*;

public class factor
{
	public static void main(String [] args)
	{
		int num;
		int a=1;
		int b=c=0;
		int factors[] = new int[10];
		int factors2[] = new int[20];
		System.out.print("What would you like to factor: ");
		num = inScan.nextInt();
		int workingNum=num;
		
		while (workingNum > 1)
		{
			a++;
			while (workingNum % a) == 0
			{
				workingNum /= a;
				factors[b] = a;
				factors2[c] = 