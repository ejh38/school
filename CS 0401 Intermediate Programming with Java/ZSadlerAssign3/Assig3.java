/* Zach Sadler
 * Assignment 3
 * Monday 5:30 pm lab time
 * Hangman game main program
 * Implements HangPlayer, WordServer, and two text files
 */

import java.util.*;
import java.io.*;
import java.lang.*;
import java.math.*;		// used only to generate a random free letter

public class Assig3
{
	public static void main(String [] args) throws IOException
	{
		Scanner inScan = new Scanner(System.in);
		System.out.println("What is the name of the players txt file?");
		// stores the players txt file to 'txt'
		String txt = new String(inScan.next());
		
		System.out.println("Loading " + txt + "...");
		
		Scanner txtScan = new Scanner(new File(txt));
		ArrayList<HangPlayer> Players = new ArrayList<HangPlayer>();
		
		// temporary String used throughout the program
		String temp = "";
		// these temporary integers allow me to construct
		// the HangPlayer objects after reading in from txt
		int temp1, temp2;
		
		// this is used only for free letters, not to
		// pick a random word from the WordServer
		Random rand = new Random();

		
		// reads in all the players to the ArrayList of HangPlayers
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
				
		// declare some flags/sentinels which are used for loops
		Boolean exit = false, exit2, flag3;		
		
		// this allows me to immediately break out if they type
		// 'q' or 'Q'
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
			
			// start it negative so it's obvious if it's not found
			int index = -1;
			for (int i = 0; i < Players.size(); i++)
			{
				if (Players.get(i).nameToString().equalsIgnoreCase(temp))
					index = i;
			}
			
			// if the name isn't found in the players file
			// then add a new player
			if (index == -1)
			{
				Players.add(new HangPlayer(temp, 0, 0));
				index = Players.size() - 1;
				
				// explanation of game for new players
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
				// welcome back old players
				System.out.println("Nice to have you back, " + temp + "!");
				System.out.println("These are your results so far:");
				System.out.println("\n" + Players.get(index).toString());
			}
			
			System.out.println("\nWhich word list would you like to load, " + 
									Players.get(index).nameToString() + "?");
			Scanner wordScan = new Scanner(new File(inScan.next()));
			
			// create WordServer of size specified by the
			// words file
			WordServer Words = new WordServer(wordScan.nextInt());
			
			Words.loadWords(wordScan);

			
			String answer;
			char guess;
			int misses;
			
			// more flags
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
					// all of the output
					System.out.println("Your word is:\n" + hanging +"\n");
					System.out.println("So far you've guessed:\n" + guessed);
					System.out.println("You have " + misses + " miss(es) left.");
					System.out.println("You have " + Players.get(index).freeToInt() +
										" free letters left.\n\n");
					System.out.println("Make a guess!" + 
										"\n(or enter 0 to skip the word)" +
										"\n(or enter 1 to quit the game)" +
										"\n(or enter 2 for a free letter)");					
					// take in the guess, get the first char, capitalize it
					guess = inScan.next().charAt(0);
					
					// special case #1
					// if the guess is 0, then skip the word, and count as loss
					if (Character.getNumericValue(guess) == 0)
					{
						cont = false;
						Players.get(index).winOrLose(false);
						System.out.println("Okay, skipping the word, but counting " +
											"this as a loss.");
						pause();
					}
					
					// special case #2
					// if the guess is 1, then quit out	
					if (Character.getNumericValue(guess) == 1)
					{
						cont = false;
						exit2 = true;
					}
					
					// special case #3
					// if the guess is 2 then give a free letter
					if (Character.getNumericValue(guess) == 2)
					{
						// if they have free letters
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
									// this is so it doesn't give a free
									// letter that you've already guessed
									if (guess == hanging.charAt(i))
										flag3 = true;
								}
							} while (flag3);
						}
						// if they don't have free letters left
						else
						{
							System.out.println("You're out of free letters!");
							System.out.println("I'm counting this as a miss.");
							pause();
						}
					}
			
								
					
					// make their guess upper case so it matches
					// the upper case words in the WordServer
					guess = Character.toUpperCase(guess);
					inScan.nextLine();
					flag = false;
					
					// check to see if their guess matches
					// any of the characters in the answer
					for (int i = 0; i < answer.length(); i++)
					{
						if (guess == answer.charAt(i))
						{
							hanging.setCharAt(i, guess);
							flag = true;
							
							// this is the win condition
							// it's inside this loop so that it is only
							// checked when the player gets a guess right
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
					
					// if they got it wrong, they get a miss
					if (flag == false)
						misses--;
						
					flag = false;
					
					// if they reguess a word
					for (int i = 0; i < guessed.length(); i++)
					{
						if (guess == guessed.charAt(i))
						{
							flag = true;
							System.out.println("You've already guessed that!");
							pause();
						}
					}
					
					// as long as they haven't already guessed their
					// guess before, append it to the guessed
					// stringbuilder and add a space as seperation
					if (flag == false)
						guessed.append(guess + " ");
					
					// this is the loss condition	
					if (misses == 0)
					{
						Players.get(index).winOrLose(false);
						System.out.println("Sorry, you missed that one." +
											"\nThe correct word was " + answer);
						pause();
					}
				
				} while (cont && (misses > 0));
			
			} while (Words.hasNextWord() && (exit2 == false));
			
			// once the player quits or reaches the end of the WordServer
			System.out.println("\n\nThanks for playing, " + Players.get(index).nameToString() + "!");
			System.out.println("Final results\n" + Players.get(index).toString());
				
		} 
		// after the user types 'q' and quits
		
		PrintWriter txtOut = new PrintWriter(new FileOutputStream(txt, false));

		for(int i = 0; i < Players.size(); i++)	
			Players.get(i).save(txtOut);
		// save players back to players.txt
		
		txtOut.close();
	}
	
	// for formatting
	public static void pause()
	{
		Scanner pause = new Scanner(System.in);
		System.out.println("\n\n\tPress enter to continue.");
		pause.nextLine();
	}
	
	// for formatting
	public static void clearScreen()
	{
		for(int i = 0; i < 25; i++)
			System.out.println();
	}
}