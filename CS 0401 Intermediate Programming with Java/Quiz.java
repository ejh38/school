// CS 0401 Fall 2011
// Quiz class to be used with Assignment 2
// You must use this class exactly as specified, with no changes to the code
/* The Quiz will read data from a file formatted as follows:
question1
answer1
question2
answer2
...
*/
// Be sure to format your questions file correctly (note: make sure you do not have
// an extra empty line at the end of your file -- this will cause an error)

import java.io.*;
import java.util.*;

public class Quiz
{
	private String fName;
	private Scanner theFile;
	private boolean onQ;
	
	// Create a new Quiz object by opening the associated file.  Note that this
	// method throws an IOException, so in the method that calls it you must also
	// have in the header "throws IOException".  We will discuss how to handle
	// these exceptions later.
	public Quiz(String f) throws IOException
	{
		fName = new String(f);
		theFile = new Scanner(new File(fName));
		onQ = true;
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

}