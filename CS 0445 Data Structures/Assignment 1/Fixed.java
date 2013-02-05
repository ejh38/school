/* -----------------
 * Zach Sadler 
 * Recitation Mon 1:00pm
 * Assignment 1
 * Simple implementation, using super calls
 * and relying on the predefined methods in Product
 */


public class Fixed extends Product
{
	// all that's needed for data
	private double price;
	
	// call super, then set the price
	public Fixed(String name, double cost)
	{
		super(name);
		price = cost;
	}
	
	public Fixed()
	{
		super();
	}
	
	// for fixed, just return price
	public double cost()
	{
		return price;
	}
	
	// call super then add price
	public String toString()
	{
		return (super.toString() + " Price: " + cost());
	}
	
}