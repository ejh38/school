/* -----------------
 * Zach Sadler 
 * Recitation Mon 1:00pm
 * Assignment 1
 * Simple implementation, using super calls
 * and relying on the predefined methods in Product
 */
 
public abstract class Variable extends Product
{
	// Passes it along to Product
	public Variable (String n)
	{
		super(n);
	}
	
	// Same thing
	public Variable()
	{
		super();
	}
	
	// Overloaded, but only so it can use super
	public String toString()
	{
		return super.toString();
	}
}		