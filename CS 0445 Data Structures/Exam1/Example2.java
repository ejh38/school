// CS 0445 Spring 2012.  Demonstration of Java classes and objects,
// inheritance and polymorphism, arrays and interfaces.  There is
// a lot of material that is reviewed here, so read over the code
// and comments VERY carefully!

public class Example2
{
      public static void main(String [] args)
      {
             People [] P;   // Declaring an array variable.  Recall
                            // that at this point NO OBJECTS exist!

             P = new People[6]; // Now an array object exists, but no
                            // People objects exist, so the array is
                            // an array of null references.  The People
                            // objects must be allocated individually.

             P[0] = new People("Herb", "1/1/1972");  // allocate a People
                            // object using the constructor and put it into
                            // the zeroth location of the array.

             P[1] = new Worker("Bart", "3/18/1959", 85000);
                  // Even though P is an array of
                  // People, it can still be assigned Worker and (below)
                  // Student objects, since these classes are subclasses
                  // of the People class.  In Java, the more specific (sub)
                  // class objects are ALWAYS assignable to the less
                  // specific (super) class variables.  Note that even
                  // though the references are all People references, the
                  // underlying objects are still Worker and (below)
                  // Student.  A question that arises, is what effect, if
                  // any, does accessing a subclass object through a
                  // superclass variable have?

                  // INSTANCE VARIABLES:
                  // As discussed in lecture, when accessing a subclass
                  // object through a superclass reference, only the
                  // instance variables that are defined in the superclass
                  // may be accessed.  Thus, even if the salary instance
                  // variable in Worker were declared as public, it could
                  // still not be accessed through the array of People P,
                  // but it COULD be accessed through an array of Worker.

                  // INSTANCE METHODS
                  // Instance methods in a subclass with new prototypes (or
                  // headers) are not accessible through superclass
                  // references.   Thus, the setSalary() method in Worker
                  // cannot be called via a People variable.  However,
                  // if a method were originally defined in People and
                  // then overridden in Worker (such as toString()), the
                  // subclass version of the method is used.  This is the
                  // idea of polymorphism in its truest sense, and allows
                  // a great deal of functionality for the programmer.

             P[2] = new Worker("Zeke", "6/9/1961", 45000);
             //P[2].setSalary(75000.0);  // Not allowed
             ((Worker) P[2]).setSalary(50000.0); // This is ok
             Worker newW = (Worker) P[2];
		     newW.setSalary(60000.0);   // This is also ok

             P[3] = new Student("Bill", "4/3/1985", "CS", 3.5);
             P[4] = new Student("Mary", "5/8/1983", "English", 3.8);
             P[5] = new People("Alice", "11/21/1976");

             for (int i = 0; i < 6; i++)
                 System.out.println(P[i]);  // This will implicitly
                                            // call the toString()
                        // method for each object.  Note that, due to
                        // method overriding, this produces a different
                        // action for People, Worker and Student objects.

             System.out.println();

             SortArray.selectionSort(P, P.length);  // call sorting function
					// To sort we are using the SortArray class as
					// implemented in code segment 8.6 from Chapter 8
					// of the Carrano text.  We will discuss sorting
					// in more detail later, but for now we will look at
					// the code just to see the object-oriented ideas.  We
					// will also discuss the specifics of the selectionSort
					// header (and its generic implications) later in the
					// term.

             for (int i = 0; i < 6; i++)     // Print sorted items
                 System.out.println(P[i]);

             System.out.println();

             // Sorting method works for array of any Comparable objects.
             // Primitive types are not Comparable, but their wrapper classes
             // are.

             Integer [] intarray = new Integer[20];
             for (int i = 0; i < intarray.length; i++)
                      intarray[i] = new Integer((7*i)%(intarray.length));
             for (int i = 0; i < intarray.length; i++)
                      System.out.print(intarray[i] + ",");
             System.out.println();
             SortArray.selectionSort(intarray, intarray.length);
             for (int i = 0; i < intarray.length; i++)
                      System.out.print(intarray[i] + ",");
             System.out.println();

      }
}