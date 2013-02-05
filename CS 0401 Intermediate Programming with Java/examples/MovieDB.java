// CS 0401 Lab 7 MovieDB class
// This class is a simple database of Movie objects.  Note the
// instance variables and methods and read the comments carefully.

public class MovieDB
{
	// Note that we have 2 instance variables here -- an array of Movie and
	// an int.  Since Java arrays are of fixed size once they are created,
	// we creating the array of a certain (large) size and then using the
	// int variable to keep track of how many actual movies are in it.  We
	// don't resize here, but we could if we wanted to (as discussed in class).
	private Movie [] theMovies;
	private int numMovies;

	// Initialize this MovieDB
	public MovieDB(int size)
	{
		theMovies = new Movie[size];
		numMovies = 0;
	}

	// Take already created movie and add it to the DB.  This is simply putting
	// the new movie at the end of the array, and incrementing the int to
	// indicate that a new movie has been added.  If no room is left in the 
	// array, indicate that fact.
	public void addMovie(Movie m)
	{
		if (numMovies < theMovies.length)
		{
			theMovies[numMovies] = m;
			numMovies++;
		}
		else
			System.out.println("No room to add movie");
			// Alternatively, as we discussed in lecture, we could resize the
			// array to make room - feel free to try this as an additional
			// exercise.
	}

	// Iterate through the array until the movie is found or the end of the 
	// array is reached.  Note that even though a Movie object has several 
	// components we are searching based on the title alone.  We call the
	// title the "key value" for the Movie.  If the Movie is not found we
	// indicate that fact by returning null.
	public Movie findMovie(String title)
	{
		for (int i = 0; i < numMovies; i++)
		{
			if (theMovies[i].getTitle().equals(title))
				return theMovies[i];
		}
		return null;
	}

	// Return a formatted string containing all of the movies' info.  Note
	// that we are calling the toString() method for each movie in the DB.
	public String toString()
	{
		StringBuffer B = new StringBuffer();
		B.append("Movie List: \n\n");
		for (int i = 0; i < numMovies; i++)
			B.append(theMovies[i].toString() + "\n");
		return B.toString();
	}

	// Similar to the method above, but now we are not formatting the
	// string, so we can write the data to the file.
	public String toStringFile()
	{
		StringBuffer B = new StringBuffer();
		B.append(numMovies + "\n");
		for (int i = 0; i < numMovies; i++)
			B.append(theMovies[i].toStringFile());
		return B.toString();
	}

}



