// CS 401 Lab 7 Movie class
import java.text.*;
import java.util.*;
public class Movie
{
	private String title;
	private String director;
	private String studio;
	private double gross;

	// Constructor -- take 4 arguments and make a new Movie
	public Movie(String t, String d, String s, double g)
	{
		title = new String(t);
		director = new String(d);
		studio = new String(s);
		gross = g;
	}

	// Return a formatted string version of this Movie
	public String toString()
	{

		StringBuffer B = new StringBuffer();
		B.append("Title: " + title + "\n");
		B.append("Director: " + director + "\n");
		B.append("Studio: " + studio + "\n");
		NumberFormat formatter = NumberFormat.getCurrencyInstance(Locale.US);
		B.append("Gross: " + formatter.format(gross) + "\n");
		return B.toString();
	}

	// Return an unformatted string version of this Movie
	public String toStringFile()
	{
		StringBuffer B = new StringBuffer();
		B.append(title + "\n");
		B.append(director + "\n");
		B.append(studio + "\n");
		B.append(gross + "\n");
		return B.toString();
	}

	// Accessor to return title of this Movie
	public String getTitle()
	{
		return title;
	}
}
