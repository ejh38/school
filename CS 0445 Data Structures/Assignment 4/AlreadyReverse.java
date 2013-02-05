

public class AlreadyReverse implements Assig4able
{
	Integer [] array;
		
	public AlreadyReverse(int size)
	{
		array = new Integer[size];
	}	
	
	public void fill()
	{
		for (int i = array.length - 1; i >= 0; i--)
			array[array.length - 1 - i] = i;
	}
	
	public String getOrder()
	{
		return new String("Reverse Sorted");
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