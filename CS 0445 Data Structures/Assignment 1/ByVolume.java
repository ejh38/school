/* -----------------
 * Zach Sadler 
 * Recitation Mon 1:00pm
 * Assignment 1
 * Simple implementation, using super calls
 * and relying on the predefined methods in Product
 */
 
public class ByVolume extends Variable
{
	// also need volume for this one
	private double volume;
	private double price;
	
	// call the super, set the rest
	public ByVolume(String name, double cost, double units)
	{
		super(name);
		price = cost;
		volume = units;
	}
	
	public ByVolume()
	{
		super();
	}
	
	// returns the cost- which is the price times the volume
	public double cost()
	{
		return (price * volume);
	}
	
	// slightly tricky
	public String toString()
	{
		return (super.toString() + " Volume: " + volume + " oz. Price: " + cost());
	}

}