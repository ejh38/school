/* CS0445 Spring 2012
   Defining a class which implements an interface.  Class People is
   fairly straightforward, with a single constructor that assigns
   a new String and a date to the current object.  Note in the header
   that it "implements Comparable<People>".  Recall that a single class
   may in fact implement many interfaces.  In this case the interface
   contains a parameter that enables us to specify the type that will
   be compared to this object.  See Appendix D in the Carrano
   text for more details.
   
   Note that People is also a simple example of composition -- since
   it has a String instance variable and a Date instance variable.
   However, the access to these is limited to their public variables
   and methods.
*/

import java.util.*;
import java.text.*;

public class People implements Comparable<People>
					// Note that the interface has a parameter, which
					// enables us to require objects that will be
					// compared to this to be of type People.  This way,
					// if compareTo is called with an object of some
					// other type as a parameter, a compilation error
					// will occur.
{
	private String name;   // name and dob are both private
	private Date dob;

	public People(String s, String d)
	{
		name = new String(s);

		// Java has a fairly convoluted way of parsing and assigning dates.
		// This is to allow variation for how dates are represented in
		// different parts of the world and in different formats even within
		// the same country.  If the date is incorrectly formatted, a
		// ParseException will occur.  This is similar in idea to the
		// NumberFormatException that occurs if, for example, we call
		// Integer.parseInt() on an incorrectly formatted int value.
		DateFormat df = DateFormat.getDateInstance(DateFormat.SHORT);
		try 
		{
			dob = df.parse(d);
		}
		catch (ParseException e)
		{
			dob = null;
		}
	}

	// Note that age() is a method rather than an instance variable.  This
	// way we will not have to change the data as the person "ages".  Also
	// note that age() is not taking into account leap years, so there is
	// a slight chance that it could occasionally be incorrect.  The nice
	// thing about inheritance is that if you ever want to "fix" this method
	// you will not have to do anything to the Student or Worker classes,
	// since they will inherit the new version.
	public int age()
	{
		long dobtime = dob.getTime();  // get time in milliseconds of dob
		     // (this is the number of milliseconds relative to the
		     // "epoch", which is Jan. 1, 1970 (at 00:00:00 o'clock)
		
		long currtime = System.currentTimeMillis();  // get current time,
		     // also in milliseconds

		long difftime = currtime - dobtime;
		difftime = difftime/1000;  // convert to seconds
		difftime = difftime/(24 * 3600);  // convert to days
		difftime = difftime/365;  // convert to years.  Note that we may
				// be slightly off here due to leap years.  To be more
				// exact the calculations would be MUCH more complex
		return (int) difftime;
	}

	public String toString()  // called implicitly as mentioned before
	{
		return ("Name: " + name + " Age: " + age());
	}

	/* In the Comparable interface, the argument to compareTo is the
	 * generic parameter T.  However, since in the class header above,
	 * People is substituted for T, we can in turn use People in the
	 * method below.
	*/
	public int compareTo(People rhs)
	{
		if (age() > rhs.age()) return 1;
		else if (age() < rhs.age()) return -1;
		else return 0;

		// Recall that compareTo is interpreted in the following
		// way
		//       Left < Right --> returns negative
		//       Left == Right --> returns 0
		//       Left > Right --> returns positive
		// If we had wanted to compare objects based on name rather than
		// the age(), we could have used the compareTo method as defined
		// for the String class, or simply
		//		 return (name.compareTo(rhs.name));
	}
}
