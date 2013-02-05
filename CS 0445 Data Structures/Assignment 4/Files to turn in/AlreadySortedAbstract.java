/*************************************************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * This is the class for data which is in order: Sorted
 *************************************************************/

public class AlreadySortedAbstract extends Assig4ableAbstract 
{
	
	public AlreadySortedAbstract(int size)
	{
		array = new Integer[size];
	}
	
	public void fill()
	{
		for (int i = 1; i <= array.length; i++)
			array[i-1] = i;
	}
	
	public String getOrder()
	{
		return new String("Sorted");
	}

}
