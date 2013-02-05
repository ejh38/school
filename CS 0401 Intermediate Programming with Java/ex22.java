// CS 0401 Fall 2011
// Demonstration of polymorphism in Java
// Look carefully at the different subclasses and the methods that are
// defined.  Note especially:
//		The move() method is overridden at each level in the hierarchy.
// Thus, a call to move() for a given object will execute its appropriate
// move behavior.
//		The characteristics() method is also overridden, but note that
// it is calling the superclass version of the method as well -- this allows
// us to utilize both the new (subclass) version of a method and the old
// (superclass) version of a method in the same call.
//		Class Fish adds an extra instance variable and method (plus an enum
// type).  See comments below and course notes for access restrictions on 
// these items.

class Animal
{
	// Private but still inherited -- thus it is part of all subclass objects
	// but cannot be directly accessed by them.
	private String name;

	public Animal(String n)
	{
		name = new String(n);
	}

	public void characteristics()
	{
		System.out.println("I am alive");
	}

	public void move()
	{
		System.out.println("I Move");
	}

	public String toString()
	{
		return new String("My name is " + name + " and I am a " + getClass());
	}
}

class Fish extends Animal
{
	// Extra enum type and instance variable defined here.  See getWaterType()
	// method for more information.
	public static enum WaterType {freshWater, saltWater}

	private WaterType myWater;

	public Fish(String n, WaterType w)
	{
		super(n);
		myWater = w;
	}

	// Consider this question: What happens on a call to "super"
	// if the method is not defined in the direct superclass.  The answer
	// is that the call reverts up the class hierarchy until a superclass
	// version of the method is found.  To demonstrate this, comment out
	// the method below and then see what happens in the call to
	// characteristics in the subclass Shark.

	public void characteristics()
	{
		super.characteristics();
		System.out.println("I have fins");
		System.out.println("I like " + myWater);
	}

	// This method is defined in class Fish, which means it is only accessible
	// in this class or below in the hierachy.  Thus, even if the object is
	// Fish, if the reference is Animal, this method cannot be called.  See
	// more information below.
	public WaterType getWaterType()
	{
		return myWater;
	}

	public void move()
	{
		System.out.println("I swim");
	}
}

class Shark extends Fish
{
	public Shark(String n, WaterType w)
	{
		super(n, w);
	}

	public void characteristics()
	{
		super.characteristics();
		System.out.println("I am carnivorous");
	}
}

class Bird extends Animal
{
	public Bird(String n)
	{
		super(n);
	}

	public void characteristics()
	{
		super.characteristics();
		System.out.println("I have feathers");
	}

	public void move()
	{
		System.out.println("I fly");
	}
}

class Ostrich extends Bird
{
	public Ostrich(String n)
	{
		super(n);
	}

	public void characteristics()
	{
		super.characteristics();
		System.out.println("I have long legs");
	}

	public void move()
	{
		System.out.println("I run");
	}
}

class Person extends Animal
{
	public Person(String n)
	{
		super(n);
	}

	// The characteristics method is not defined here, so the one from
	// Animal class will be used.

	public void move()
	{
		System.out.println("I walk");
	}
}

public class ex22
{
	public static void main(String [] args)
	{
		Animal [] A = new Animal[8];
		A[0] = new Animal("Herb");
		A[1] = new Bird("Tweety");
		A[2] = new Fish("Nemo", Fish.WaterType.freshWater);
		A[3] = new Person("Marge");
		A[4] = new Ostrich("Big");
		A[5] = new Person("Hector");
		A[6] = new Shark("Lenny", Fish.WaterType.saltWater);
		A[7] = new Fish("Oscar", Fish.WaterType.saltWater);

		for (int i = 0; i < A.length; i++)
		{
			System.out.println(A[i]);
			A[i].characteristics();
			A[i].move();

			// The code below will NOT work, since getWaterType is defined
			// initially in subclass Fish, NOT in superclass Animal.
			// Remove the comments to see the result.
			/*
			if (A[i] instanceof Fish)
				System.out.println(A[i].getWaterType() + " is fun!");
			*/

			// This code is fine -- we are checking the class using the
			// instanceof operator and then casting the reference before
			// calling the method.  Note that instanceof returns true if
			// the object is the class named or ANY SUBCLASS of it.
			if (A[i] instanceof Fish)
			{
				Fish F = (Fish) A[i];
				System.out.println(F.getWaterType() + " is fun!");
			}
			System.out.println();
		}
	}
}


