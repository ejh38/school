/*  Zach Sadler
	Monday 5:30 lab time
	Assignment 2
	Quiz game that takes input from the user, reads input from files,
	writes output to files, and tracks scores across all players
*/


import java.io.*;
import java.util.*;

public class Assig2
{

	public static void main(String [] args) throws IOException
	{
		String name = "", answer = "", correct = "";
		boolean exit = false;
		Scanner inScan = new Scanner(System.in);
		
		game:			// this label lets me break out mid-loop
		while (!exit)
		{		
		System.out.println("Welcome to the quiz game!");

		System.out.print("What's your name? (or type exit to quit) >> ");
		name = inScan.next();
		if (name.equals("exit"))
		{
			exit = true;
			break game;			// lets you break out of the labeled loop
		}
		Player P1 = new Player(name);		// create the Player object
		
		if (P1.hasPlayed())
			System.out.println("\n" + name + ", you've already played!");
		else
		{
			System.out.println("Welcome, " + name + "! Time to take the quiz.\n");
			System.out.println("You will have two tries to answer each question.");
//			System.out.println("A hint will be given after your first incorrect guess.");
			System.out.println("If the answer is a number, please give the answer with digits, not words.");
			
			Quiz game = new Quiz("questions.txt");		// creates a quiz object based on the questions file
			
			while (game.hasAQuestion())
			{
				System.out.println("\n" + game.getQuestion());
				answer = inScan.next();
				correct = game.getAnswer();		// stores the correct answer so you only call getAnswer once
				
				if (!answer.equalsIgnoreCase(correct))
				{
					System.out.println("Sorry, that is wrong.");
//					System.out.println("Here's a hint: " + game.getHint());
					
					System.out.println("Please try again.");
					answer = inScan.next();
					if (!answer.equalsIgnoreCase(correct))
					{
						System.out.println("Sorry, you got this question wrong.");
						System.out.println("The correct answer is " + correct);
					}
				}
				
				if (answer.equalsIgnoreCase(correct))
						System.out.println("Correct!");

				P1.rightOrWrong(answer.equalsIgnoreCase(correct));	// adds one to numRight or numWrong
			}
			
			PrintWriter savePlayer = new PrintWriter(new FileOutputStream("players.txt",true));
			savePlayer.println();			// skips to the next line
			savePlayer.println("" + name);
			savePlayer.println("" + P1.howManyRight());
			savePlayer.print("" + P1.howManyWrong());		// print instead of println because of println above
			savePlayer.close();
			
		}
				
		results(P1, name);	// this executes regardless of whether P1 has played or not
		
		}
	
	}
		

	// this outputs the results the player and overall totals
	public static void results(Player P1, String name) throws IOException
	{
			double percent;

			System.out.println("Here are your stats:\n");
			System.out.println(P1.toString());				// outputs all the player stats
			System.out.println("\nOverall stats:");
			System.out.println(P1.totalRight() + " right and " +
										 P1.totalWrong() + " wrong.");
			percent = 100 * ((double) P1.totalRight()) / (P1.totalRight() + P1.totalWrong());
			System.out.println("Percent right: " + 
									String.format("%.5g%n", percent) + "\n\n");
						// String.formt makes it show five decimal places of the double
	}
		
}