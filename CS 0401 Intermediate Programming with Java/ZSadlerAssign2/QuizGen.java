import java.io.*;
import java.util.*;

public class QuizGen
{
	public static void main(String [] args) throws IOException
	{
		System.out.println("Welcome to the Quiz Generator!\n" +
							"You will be able to make your own quiz, including" +
							" questions, answers, and hints.\n");
		System.out.println("You will be prompted for a question, then an answer," +
							" then a hint.\nAt any time, answer \"exit\" to quit" +
							" without saving, or \"save\" to save up to the previously" +
							" entered question.");
							
		// construct a new inScan object for reading input
		Scanner inScan = new Scanner(System.in);
		
		System.out.println("How many questions would you like in your quiz?");
		int numQuestions = inScan.nextInt();
		inScan.nextLine();
		
		boolean exit = false;
		String temp = "";
		String [] questions = new String[numQuestions];
		String [] answers = new String[numQuestions];
		String [] hints = new String[numQuestions];
		
		loop:
		while (!exit)
		{
			for (int i = 0; i < numQuestions ; i++)
			{
				
				System.out.println("\nEnter question " + (i+1) + ", exactly as you'd like it formatted.");
				questions[i] = inScan.nextLine();
				if (questions[i].equalsIgnoreCase("exit"))
					break loop;
				
				System.out.println("Enter the answer (enter numbers as digits).");
				answers[i] = inScan.nextLine();
				if (answers[i].equalsIgnoreCase("exit"))
					break loop;
			
				System.out.println("Enter a hint (or just write: no hint).");
				hints[i] = inScan.nextLine();
				if (hints[i].equalsIgnoreCase("exit"))
					break loop;
			}
			exit = true;
			
			
// File.createNewFile
				
		}
		
		for (int i = 0; i < numQuestions; i++)
		{
			System.out.println("\n" + questions[i]);
			System.out.println(answers[i]);
			System.out.println(hints[i]);
		}
		
		
		
	}
}