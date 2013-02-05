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
	
	public String winsToString()
	{
		return Integer.toString(wins);
	}
	
	public String lossToString()
	{
		return Integer.toString(losses);
	}
	
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
	
	public void useFreeLetter()
	{
		free--;
	}
	
	public void winOrLose(Boolean w)
	{
		if (w)
			wins++;
		else
			losses++;
	}
	
}