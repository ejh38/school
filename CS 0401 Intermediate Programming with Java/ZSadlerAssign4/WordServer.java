/* Zach Sadler
 * Word Server class for Assig3.java
 * Monday 5:30 Lab time
 */
 
import java.util.*;
import java.math.*;
import java.io.*; 
 
public class WordServer
{
	private Random rand = new Random();

	private String [] words;
	private String [] played;
//	private String temp = "";
	private int temp;
	private int index;
	
	public WordServer(int num)
	{
		 words = new String[num];
		 played = new String[num];
		 index = 0;
	} 
	
	public void loadWords(Scanner S)
	{
		for (int i = 0; i < words.length; i++)
		{
			S.nextLine();
			words[i] = S.next().toUpperCase();
			played[i] = new String("");
		}
	}
	
	public void debug()
	{
		for (String data : words)
			System.out.println(data);
	}
	
	public Boolean hasNextWord()
	{
		if (played[played.length-1].equals(""))
			return true;
		return false;
	}
	
	// this works
	public String getNextWord()
	{	
		// while played is not full
		while (true)
		{
			temp = rand.nextInt(words.length);
			
			// if the prospective word hasn't been played
			if (!hasBeenPlayed(words[temp]))
			{
				played[index] = words[temp];
				index++;
//debug			System.out.println(temp);
				return words[temp];
			}
		}
	}
	
	public Boolean hasBeenPlayed(String S)
	{
		for (String data : played)
		{
			if (data.equals(S))
				return true;
		}
		
		return false;
	}
}