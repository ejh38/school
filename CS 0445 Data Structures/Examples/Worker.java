// CS 0445 Spring 2012
// Class Worker inherits all of the data and methods (and interface
// implementations) from People, and adds an additional instance
// variable and an additional method.  It also overrides the toString()
// method to display it properly

public class Worker extends People  // recall syntax for inheritance
{
       private double salary;

       public Worker(String s, String d, double salary)
       {
              super(s, d);     // call the superclass constructor
                               // (People) to set up the first two
                   // instance variables.  If used, a call to a
                   // superclass constructor must be the FIRST thing
                   // done in a constructor.  Note also that, since
                   // the instance variables in People are private,
                   // they are not directly visible in subclasses.
                   // Thus, we could not directly initialize those
                   // variables in this constructor.

              // name = new String(s);  // could do this if name were
		                                // protected rather than private

              this.salary = salary;  // this is a reference to the current
                                     // object to avoid ambiguity (since
                                     // here salary is both an instance
                                     // variable and a parameter)
       }

       public String toString()  // overriding toString() method
       {
              String firstpart = super.toString();  // call to super
                                                    // toString()
                     // method to get string rep. of name and age.  Since
		             // age() is public, we could call it directly from
		             // here, but name is a private variable, so using
		             // super is the only way to get it from here.

              return (firstpart + " Salary: " + salary);
       }

       public void setSalary(double newsal)  // This method is newly
       {                            // defined in Worker, so it must be
              salary = newsal;      // be accessed through a Worker (or
       }                            // subclass) reference.
}
