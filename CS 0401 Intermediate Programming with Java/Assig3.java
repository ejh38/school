/* Zach Sadler
 * Assignment 3
 * Monday 5:30 pm lab time
 * Hangman game
 */

import java.util.*;
import java.io.*;
import java.lang.*;
import java.math.*;

public class Assig3
{
	public static void main(String [] args) throws IOException
	{
		Scanner inScan = new Scanner(System.in);
		System.out.println("What is the name of the players txt file?");
		String txt = new String(inScan.next());
		
		System.out.println("Loading " + txt + "...");
		
		Scanner txtScan = new Scanner(new File(txt));
		ArrayList<HangPlayer> Players = new ArrayList<HangPlayer>();
		
		String temp = "";
		int temp1, temp2;
		Random rand = new Random();

		
		while (txtScan.hasNextLine())
		{
			temp = txtScan.next();
			txtScan.nextLine();
			temp1 = txtScan.nextInt();
			txtScan.nextLine();
			temp2 = txtScan.nextInt();
			if (txtScan.hasNextLine())
			{
				txtScan.nextLine();
			}
			Players.add(new HangPlayer(temp, temp1, temp2));
		}
				
				
		Boolean exit = false, exit2, flag3;		
		main:
		while (!exit)
		{
			System.out.println("\nWelcome to Hangman!");
			System.out.println("What is your name? (or enter \"q\" to quit)");
			temp = inScan.next();
			if (temp.equalsIgnoreCase("q"))
			{
				exit = true;
				break main;
			}
			
			int index = -1;
			for (int i = 0; i < Players.size(); i++)
			{
				if (Players.get(i).nameToString().equalsIgnoreCase(temp))
					index = i;
			}
			if (index == -1)
			{
				Players.add(new HangPlayer(temp, 0, 0));
				index = Players.size() - 1;
				System.out.println("Glad you decided to play, " + temp);
				System.out.println("Here's how it works:" +
									"\nTry to guess the secret word one " +
									"letter at a time. If you give up you " +
									"can skip an individual word or quit playing.");
				System.out.println("You will also be given five free letters" +
									" that you can use when you get stuck.");
			}
			else
			{
				System.out.println("Nice to have you back, " + temp + "!");
				System.out.println("These are your results so far:");
				System.out.println("\n" + Players.get(index).toString());
			}
			// game starts with the player
			// output player stats
			
			System.out.println("\nWhich word list would you like to load, " + 
									Players.get(index).nameToString() + "?");
			Scanner wordScan = new Scanner(new File(inScan.next()));
			
			WordServer Words = new WordServer(wordScan.nextInt());
			
			Words.loadWords(wordScan);
//			Words.debug();
			
//debug		System.out.println("Here come 15 random words:");
//debug		for (int i = 0; i < 18; i++)
//debug			System.out.println(Words.getNextWord());
				

			
//debug			for (int i = 0; i < Players.size(); i++)
//debug				System.out.println("At " + i + " we have: " + Players.get(i));
			
			String answer;
			char guess, tempCh;
			int misses;
			Boolean cont, flag;
			StringBuilder hanging, guessed;
			exit2 = false;
			
			do {
				answer = new String(Words.getNextWord());
				cont = true;
				misses = 7;
				hanging = new StringBuilder(answer.length());
				guessed = new StringBuilder();
				
				for (int i = 0; i < answer.length(); i++)
					hanging.replace(i, i, "_");
				// this is really the game here
				do {
					clearScreen();
					System.out.println("Your word is:\n" + hanging +"\n");
//					System.out.println(hanging);
					System.out.println("So far you've guessed:\n" + guessed);
//					System.out.println(guessed);
					// pause
					System.out.println("You have " + misses + " miss(es) left.");
					System.out.println("You have " + Players.get(index).freeToInt() +
										" free letters left.\n\n");
					System.out.println("Make a guess!" + 
										"\n(or enter 0 to skip the word)" +
										"\n(or enter 1 to quit the game)" +
										"\n(or enter 2 for a free letter)");					
					// take in the guess, get the first char, capitalize it
					guess = inScan.next().charAt(0);
					if (Character.getNumericValue(guess) == 0)
					{
						cont = false;
						Players.get(index).winOrLose(false);
						System.out.println("Okay, skipping the word, but counting this as a loss.");
						pause();
					}
						
					if (Character.getNumericValue(guess) == 1)
					{
						cont = false;
						exit2 = true;
					}
					
					if (Character.getNumericValue(guess) == 2)
					{
						if (Players.get(index).freeToInt() > 0)
						{
							Players.get(index).useFreeLetter();
							do
							{
								flag3 = false;
								guess = answer.charAt(rand.nextInt(answer.length()));
								System.out.println("guess is: " + guess);
								for (int i = 0; i < answer.length(); i++)
								{
									if (guess == hanging.charAt(i))
										flag3 = true;
								}
							} while (flag3);
						}
						else
						{
							System.out.println("You're out of free letters!");
							System.out.println("I'm counting this as a miss.");
							pause();
						}
					}
			
								
					
					
					guess = Character.toUpperCase(guess);
					inScan.nextLine();
					flag = false;
					
					for (int i = 0; i < answer.length(); i++)
					{
				//		System.out.println("Guess is " + guess +
				//							"charAt is " + answer.charAt(i));
						if (guess == answer.charAt(i))
						{
							hanging.setCharAt(i, guess);
							flag = true;
							if (answer.equals(hanging.toString()))
							{
							cont = false;
							Players.get(index).winOrLose(true);
							System.out.println("Well done! You got it correct!");
							System.out.println("The word was " + answer);
							pause();
							}
						}
					}
					if (flag == false)
						misses--;
						
					flag = false;
					for (int i = 0; i < guessed.length(); i++)
					{
						if (guess == guessed.charAt(i))
						{
							flag = true;
							System.out.println("You've already guessed that!");
							pause();
						}
					}
					if (flag == false)
						guessed.append(guess + " ");
						
					if (misses == 0)
					{
						Players.get(index).winOrLose(false);
						System.out.println("Sorry, you missed that one." +
											"\nThe correct word was " + answer);
						pause();
					}
				
				} while (cont && (misses > 0));
			
			} while (Words.hasNextWord() && (exit2 == false));
			
			System.out.println("\n\nThanks for playing, " + Players.get(index).nameToString() + "!");
			System.out.println("Final results\n" + Players.get(index).toString());
				
				
				
				
				
		
		}
		PrintWriter txtOut = new PrintWriter(new FileOutputStream(txt, false));

		for(int i = 0; i < Players.size(); i++)	
			Players.get(i).save(txtOut);
		// save players back to players.txt
		
		txtOut.close();
	}
	
	public static void pause()
	{
		Scanner pause = new Scanner(System.in);
		System.out.println("\n\n\tPress enter to continue.");
		pause.nextLine();
	}
	
	public static void clearScreen()
	{
		for(int i = 0; i < 25; i++)
			System.out.println();
	}
}