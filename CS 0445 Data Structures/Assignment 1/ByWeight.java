/* -----------------
 * Zach Sadler 
 * Recitation Mon 1:00pm
 * Assignment 1
 * Simple implementation, using super calls
 * and relying on the predefined methods in Product
 */
 
public class ByWeight extends Variable
{
	// this needed weight
	private double weight;
	private double price;
	
	// call super, set the rest
	public ByWeight(String name, double cost, double units)
	{
		super(name);
		price = cost;
		weight = units;
	}
	
	public ByWeight()
	{
		super();
	}
	
	// cost = price * weight
	public double cost()
	{
		return (price * weight);
	}
	
	// use super, display weight, cost accessor
	public String toString()
	{
		return (super.toString() + " Weight: " + weight + " oz. Price: " + cost());
	}

}