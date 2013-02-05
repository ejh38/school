/*	Zach Sadler
	Monday 5:30 lab time
	Assignment 2 
	This file is for the Player object and has accessors, mutators,
	and a toString method
*/

import java.io.*;
import java.util.*;

public class Player
{
	
	private String name;
	private int numRight, numWrong;
	private boolean played;			//
	private Scanner players;
	
	// default constructor, won't ever get called
	public Player()
	{
		name = "Anonymous";
		numRight = 0;
		numWrong = 0;
	}
	
	// constructor that will be called
	public Player(String f)
	{
		name = f;
		numRight = 0;
		numWrong = 0;
	}
	
	// this single mutator automatically increments the correct variable,
	// numRight or numWrong, based on whether the answer is correct
	public void rightOrWrong(boolean a)
	{
		if (a == true)
			numRight++;
		else
			numWrong++;
	}
	
	// accessor to get to the private variable numRight
	public int howManyRight()
	{
		return numRight;
	}
	
	// accessor to get to the private variable numWrong
	public int howManyWrong()
	{
		return numWrong;
	}
	
	// formats and returns the whole individual player stats
	public String toString()
	{
		StringBuilder S = new StringBuilder();
		S.append(name);
		S.append("\nNumber right: " + numRight);
		S.append("\nNumber wrong: " + numWrong);
		S.append("\nPercent right: " + 100*((double) numRight) / (numRight + numWrong)); 
		return S.toString();
	}

	
	// scans through players.txt to find the player
	// if the player has played then it reads in
	// numRight, numWrong and saves them to the player object
	public boolean hasPlayed() throws IOException
	{
		players = new Scanner(new File("players.txt"));
		String temp = "";
		played = false;

		while (players.hasNextLine())
		{
			temp = players.next();

			if (temp.equalsIgnoreCase(name))
			{
				played = true;
				numRight = players.nextInt();
				numWrong = players.nextInt();	
			}

		}
		return played;
	}
	
	// scans players.txt and sums all the numRights
	public int totalRight() throws IOException
	{
		players = new Scanner(new File("players.txt"));
		String temp = "";
		int right = 0;
		while (players.hasNextLine())
		{
			temp = players.next();
			right += players.nextInt();
			temp = players.next();
		}
		
		return right;
	}
	
	// this method is nearly identical to the previous one, but
	// because you can only return one variable it's necessary to do this
	// (with arrays they could both be returned at once)
	public int totalWrong() throws IOException
	{
		players = new Scanner(new File("players.txt"));
		String temp = "";
		int wrong = 0;
		while (players.hasNextLine())
		{
			temp = players.next();
			temp = players.next();
			wrong += players.nextInt();
		}
		
		return wrong;
	}	
		
		
	
}