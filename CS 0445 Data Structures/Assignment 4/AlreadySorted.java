

public class AlreadySorted implements Assig4able
{
	Integer [] array;
	
	public AlreadySorted(int size)
	{
		array = new Integer[size];
	}	
	
	public void fill()
	{
		for (int i = 0; i < array.length; i++)
			array[i] = i;
	}
	
	public String getOrder()
	{
		return new String("Sorted");
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