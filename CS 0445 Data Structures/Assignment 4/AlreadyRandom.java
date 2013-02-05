import java.util.*;

public class AlreadyRandom implements Assig4able
{
	Integer [] array;
	
	public AlreadyRandom(int size)
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
		return array;
	}

}