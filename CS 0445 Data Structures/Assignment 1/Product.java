// CS 0445 Spring 2012
// Assignment 1
// Base class for Assigment 1.  Read this over carefully and implement
// the subclasses as described in the Assignment sheet.

// Note that Product implements the two interfaces shown below.  As you
// know the Comparable interface contains the single method compareTo(),
// as shown below.  However, there are no explicit methods that need to 
// be implemented for the Serializable interface -- in this case it is
// simply a tag that indicates that the class can be read and written
// using the readObject() and writeObject() methods.  Interface
// implementations are inherited, so you do not have to implement these
// in any of your subclasses.
import java.io.Serializable;
public abstract class Product extends Object implements Comparable<Product>,
														Serializable
{
       private String name;  // Name of product

       public Product (String n)
       {
		   name = new String(n);
       }

       public Product()
       {
		   name = null;
	   }

       // This method must be correctly implemented in the subclasses
       public abstract double cost();

       public boolean equals(Object rhs)
       {
              Product p = (Product) rhs;
              return (name.equals(p.name));
       }

       // You must override this method appropriately in the subclasses.
       // However, since name is private, you must still call this version
       // using super as described in class.
       public String toString()
       {
              return ("Name: " + name);
       }

       public int compareTo(Product rhs)
       {
              if (this.cost() < rhs.cost()) return -1;
              else if (this.cost() == rhs.cost()) return 0;
              else return 1;
       }
}
