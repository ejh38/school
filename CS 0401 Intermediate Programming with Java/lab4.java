import java.util.*;
public class lab4
{
	public static void main(String [] args)
	{
		Random rd = new Random();
		int counter0 = 0, roll = 1, dice1 = 0, dice2 = 0, dice3 = 0,counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0, counter5 = 0, counter6 = 0, counter7 = 0;
		for(int i = 0; i < 1000; i++)
		{ 
			dice1 = rd.nextInt(2);
			dice2 = rd.nextInt(2);
			dice3 = rd.nextInt(2);
					
			int total = dice3*4 + dice2*2 + dice1*1;
			
			switch(total)
			{
				case 0:
					counter0 = counter0 + 1;
					break;
				case 1:
					counter1 = counter1 + 1;
					break;
				case 2:
					counter2 = counter2 + 1;
					break;
				case 3:
					counter3 = counter3 + 1;
					break;
				case 4:
					counter4 = counter4 + 1;
					break;
				case 5:
					counter5 = counter5 + 1;
					break;
				case 6:
					counter6 = counter6 + 1;
					break;
				case 7:
					counter7 = counter7 + 1;
					break;
			}
		}
		System.out.println(counter0+"\n"+counter1+"\n"+counter2+"\n"+counter3+"\n"+counter4+"\n"+counter5+"\n"+counter6+"\n"+counter7);
	}

}
