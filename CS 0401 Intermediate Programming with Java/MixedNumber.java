// CS 401 Fall 2011
// Implementing MixedNumber class using composition.  I am using Lewis/Loftus'
// RationalNumber class as an instance variable.  See RationalNumber.java for
// more details on the RationalNumber class.  Compare this implementation
// to MixedNumber2 (which uses inheritance) to see implementation differences.

public class MixedNumber
{
	private int whole;
	private RationalNumber frac;
	// Constructor to take a whole number part, numerator and denominator
	// to generate a new MixedNumber.  This method works in the following way:
	// First, a MixedNumber is made just from the "fraction" part of the
	// parameters (in case it is an improper fraction).  Then the "whole" part
	// is added to get the final MixedNumber.  For example, given the call
	// MixedNumber(4, 11, 3), we build the MixedNumber in the following way:
	//    tempfrac = 11/3
	//    tempmix = 3 2/3
	//    whole = 4 + 3 = 7
	//    frac = 2/3
	// FINAL RESULT: 7 2/3  
	public MixedNumber(int w, int num, int denom)
	{
		RationalNumber tempfrac = new RationalNumber(num, denom);
		MixedNumber tempmix = new MixedNumber(tempfrac);
		whole = w + tempmix.whole;
		frac = tempmix.frac;
	} 
	// Constructor to generate new MixedNumber from RationalNumber object.
	// Note that we access the numerator and denominator of the RationalNumber
	// via accessor methods, since they are private to the RationalNumber
	// class.  For example, given the call MixedNumber(13/4),
	// we build the MixedNumber in the following way:
	//    num = 13
	//    denom = 4
	//    whole = 3
	//    frac = RationalNumber(13 % 4, 4) = 1/4
	// FINAL RESULT: 3 1/4 
	public MixedNumber(RationalNumber f)
	{
		int num = f.getNumerator();
		int denom = f.getDenominator();
		whole = num/denom;
		frac = new RationalNumber(num % denom, denom);
	}
	// Accessor (note it is NOT a mutator) to generate a new MixedNumber
	// that is the sum of the current MixedNumber and the rightOp
	// parameter.  The addition is done in the following way:  The whole
	// number parts are added and the RationalNumber parts are added
	// separately.  Then the sum of the RationalNumbers is converted into 
	// a new MixedNumber, and the sum of the whole number parts is added 
	// to it.
	public MixedNumber add(MixedNumber rightOp)
	{ 
		int newWhole = whole + rightOp.whole;
		RationalNumber newFrac = frac.add(rightOp.frac);
		MixedNumber temp = new MixedNumber(newFrac);
		temp.whole += newWhole;
		return temp;
	} 

	// Other arithemetic operators all follow the same technique:  The
	// idea is to do the arithmetic totally in terms of the already defined
	// RationalNumber arithmetic operators, then convert back to MixedNumber.

	public MixedNumber subtract(MixedNumber rightOp)
	{
		// Store current MixedNumber as a RationalNumber
		RationalNumber leftWholeFrac = new RationalNumber(whole, 1);
		RationalNumber left = leftWholeFrac.add(frac);

		// Store argument MixedNumber as a RationalNumber
		RationalNumber rightWholeFrac = new RationalNumber(rightOp.whole, 1);
		RationalNumber right = rightWholeFrac.add(rightOp.frac);

		// Subtract the two and return the result
		RationalNumber diff = left.subtract(right);
		return (new MixedNumber(diff));
	}

	public MixedNumber multiply(MixedNumber rightOp)
	{
		// Store current MixedNumber as a RationalNumber
		RationalNumber leftWholeFrac = new RationalNumber(whole, 1);
		RationalNumber left = leftWholeFrac.add(frac);

		// Store argument MixedNumber as a RationalNumber
		RationalNumber rightWholeFrac = new RationalNumber(rightOp.whole, 1);
		RationalNumber right = rightWholeFrac.add(rightOp.frac);

		// Multiply the two and return the result
		RationalNumber prod = left.multiply(right);
		return (new MixedNumber(prod));
	}

	public MixedNumber divide(MixedNumber rightOp)
	{
		RationalNumber leftWholeFrac = new RationalNumber(whole, 1);
		RationalNumber left = leftWholeFrac.add(frac);
		RationalNumber rightWholeFrac = new RationalNumber(rightOp.whole, 1);
		RationalNumber right = rightWholeFrac.add(rightOp.frac);
		RationalNumber quot = left.divide(right);
		return (new MixedNumber(quot));
	}

	public boolean equals(MixedNumber rightOp)
	{
		return (whole == rightOp.whole &&
			frac.equals(rightOp.frac));
	}

	public String toString()
	{
		return (whole + " " + frac.toString());
	}
} 
