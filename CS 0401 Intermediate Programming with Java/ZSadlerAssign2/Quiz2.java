// CS 0401 Fall 2011
// Zach Sadler
// Quiz class to be used with Assignment 2
// This is the extra credit version that incorporates hints
/* The Quiz will read data from a file formatted as follows:
question1
answer1
hint1
question2
answer2
hint2
...
*/
// Be sure to format your questions file correctly (note: make sure you do not have
// an extra empty line at the end of your file -- this will cause an error)

import java.io.*;
import java.util.*;

public class Quiz2
{
	private String fName;
	private Scanner theFile;
	private boolean onQ, hintGiven;
	
	// Create a new Quiz object by opening the associated file.  Note that this
	// method throws an IOException, so in the method that calls it you must also
	// have in the header "throws IOException".  We will discuss how to handle
	// these exceptions later.
	public Quiz2(String f) throws IOException
	{
		fName = new String(f);
		theFile = new Scanner(new File(fName));
		onQ = true;
	 	hintGiven = false;		// initializes hintGiven
	}
	
	// Are there any questions left in the file?  Note that if there is an empty
	// line at the end of the file, this will erroneously think there is another
	// question
	public boolean hasAQuestion()
	{
		return theFile.hasNextLine();
	}
			
	// Make sure qetQuestion and getAnswer alternate so we can keep track of where
	// we are in the process
	public String getQuestion()
	{
		if (!onQ)
		{
			System.out.println("Need an answer first");
			return null;
		}
		else if (theFile.hasNextLine())
			{
				onQ = false;
				hintGiven = false;			// resets hintGiven for each new question
				return theFile.nextLine();
			}
			else
			{
				System.out.println("End of file reached");
				return null;
			}
	}
	
	public String getAnswer()
	{
		if (onQ)
		{
			System.out.println("Need a question first");
			return null;
		}
		else if (theFile.hasNextLine())
			{
				onQ = true;
				return theFile.nextLine();
			}
			else
			{
				System.out.println("End of file reached");
				return null;
			}
	}	

// extra credit: the hint method
	public String getHint()
	{
		if (!hintGiven)
		{
			hintGiven = true;
			return theFile.nextLine();
		}
		else if (theFile.hasNextLine())
			{
				hintGiven = false;
				return null;
			}
			else
				return null;
			
	} 
	
}