/* Zach Sadler
 * Assignment 2
 * Crate class
 */
 
public class Crate implements Comparable<Crate>
{
	private int expDate, initCount, currCount;
	private double cost;
	
	public Crate(int exp, int init, double price)
	{
		expDate = exp;
		initCount = init;
		currCount = init;
		cost = price;
	}
	
	public int getExp()
	{
		return expDate;
	}
	
	public int getInit()
	{
		return initCount;
	}
	
	public int getCurr()
	{
		return currCount;
	}
	
	public double getCost()
	{
		return cost;
	}
	
	// returns -1 if this.exp < rhs.exp, 0 if equal, 1 if greater
	public int compareTo(Crate rhs)
	{
		if (getExp() < rhs.getExp())
			return -1;
		if (getExp() == rhs.getExp())
			return 0;
		return 1;
	}
	
	public boolean useBananas(int n)
	{
		currCount -= n;
		return (currCount >= 0);
	}
	
	// returns true if expired, false if not
	public boolean isExpired(int day)
	{
		return (expDate < day);
	}
	
	public String toString()
	{
		return new String("Expires:" + expDate + "  Start Count:" + initCount 
									  + "  Remain:" + currCount + "  Cost:" + cost);
	}
	
} 