/*************************************************************
 * Zach Sadler
 * zps6@pitt.edu
 * Assignment 4
 * This is the base abstract class for the three different types
 * of data order: Sorted, Reverse Sorted, and Random
 *************************************************************/

import java.util.*;

public abstract class Assig4ableAbstract 
{
	
	protected Integer [] array;

	public abstract void fill();
	
	public abstract String getOrder();

	public int length()
	{
		return array.length;
	}
	
	public void display()
	{
		for (int i = 0; i < array.length; i++)
			System.out.print(" " + array[i]);
	}

	public Integer [] toArray()
	{
		return Arrays.copyOf(array, array.length);
	}
	
}
