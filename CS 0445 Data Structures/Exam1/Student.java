// CS0445 Spring 2012
// Another subclass of People.  Follows the same ideas discussed
// in the Worker class.  See that class for comments.

public class Student extends People
{
       private String major;
       private double gpa;

       public Student(String s, String d, String major, double gpa)
       {
              super(s, d);
              this.major = new String(major);
              this.gpa = gpa;
       }

       public String toString()
       {
              String firstpart = super.toString();
              return (firstpart + " Major: " + major
                                + " GPA: " + gpa);
       }
}
