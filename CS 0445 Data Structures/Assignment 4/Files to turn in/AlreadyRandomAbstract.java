/*************************************************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * This is the class for data which is in order: Random
 *************************************************************/

import java.util.Random;

public class AlreadyRandomAbstract extends Assig4ableAbstract 
{
	
	public AlreadyRandomAbstract(int size)
	{
		array = new Integer[size];
	}		
	
	public void fill()
	{
		Random rng = new Random();
		for (int i = 0; i < array.length; i++)
			array[i] = rng.nextInt();
	}

	public String getOrder() 
	{
		return new String("Random");
	}

}
