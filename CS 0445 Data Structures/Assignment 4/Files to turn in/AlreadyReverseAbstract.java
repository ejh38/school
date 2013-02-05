/*************************************************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * This is the class for data which is in order: Reverse Sorted
 *************************************************************/

public class AlreadyReverseAbstract extends Assig4ableAbstract 
{
	
	public AlreadyReverseAbstract(int size)
	{
		array = new Integer[size];
	}
	
	public void fill()
	{
		for (int i = array.length; i > 0; i--)
			array[array.length - i] = i;
	}

	public String getOrder() 
	{
		return new String("Reverse Sorted");
	}

}
