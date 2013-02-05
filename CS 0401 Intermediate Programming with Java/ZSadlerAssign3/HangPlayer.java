/* Zach Sadler
 * Hangman Class file for Assig3.java
 * Monday 5:30 Lab time
 */

import java.util.*;
import java.io.*;

public class HangPlayer
{
	private String name;
	private int wins, losses, free;		
			
			
	public HangPlayer(String n, int w, int l)
	{
		name = n;
		wins = w;
		losses = l;
		// everyone gets 5 free letters
		free = 5;
	}
	
	public String toString()
	{
		return new String("Name: " + name + "\nWins: " + wins +
								"\nLosses: " + losses);
	}
	
	public String nameToString()
	{
		return name;
	}
	
	// simple way to find out how many free letters are left
	public int freeToInt()
	{
		return free;
	}
	
	public void save(PrintWriter a) throws IOException
	{
		a.println(name);
		a.println(wins);
		a.println(losses);
	}
	
	// mutator to decrease the free letters after each one is used
	public void useFreeLetter()
	{
		free--;
	}
	
	// either increments wins or decrements losses
	// bassed on the argument passed in
	public void winOrLose(Boolean w)
	{
		if (w)
			wins++;
		else
			losses++;
	}
	
}