/* CS 0401 Fall 2011 Java Example 3
   This handout demonstrates simple Java types, variables and expressions.  It also
   shows some issues regarding Java numeric types.
*/

public class ex3
{
      public static void main (String [] args)
	  {
          int base = 15, height = 10;
		  float area1, area2;
		  double area3;
		  area1 = 1/2 * base * height;    // looks right, but is wrong due to
		                                  // integer division -- 1/2 is actually
		                                  // zero
		  //area2 = 1.0/2 * base * height;// this one also looks right,
		                                  // but it will actually give a
		                // compilation error because the literal 1.0 is double
		                // and the type of area2 is float.  Recall that in Java we
		                // cannot assign more precise values to less precise
		                // variables.  To correct this we need to either declare the
		                // variable as a double or to cast the answer to a float.
		                // The difference is that a double variable has more
		                // precision than a float (i.e. can represent more digits).
		  area2 = (float) (1.0/2 * base * height);
		  area3 = 1.0/2 * base * height;

		  System.out.println("Triangle area (wrong) = " + area1);
		  System.out.println("Triangle area (right) = " + area2);
		  System.out.println("Triangle area (double) = " + area3);

		  double value = 2.7182818;
		  double round2DigitA = value * 10 + 0.5 / 10;  // This is wrong for a
		         // number of reasons.  The most obvious one is that the formula
		         // is incorrect -- in order to round we need to truncate to the
		         // number of digits we want, and no trunction is done here.

		  double round2DigitB = (int) value * 100 + 0.5 / 100; // This is wrong
		         // because of precedence -- the division is performed before the
		         // addition, which is not what we want.

		  double round2DigitC = (int) (value * 100 + 0.5) / 100; // Now we have
		         // the formula correct, but still have an incorrect answer due to
		         // integer division

		  double round2DigitD = (int) (value * 100 + 0.5) / 100.0;  // Finally we
		         // get the right answer

		  System.out.println("Value = " + value);
		  System.out.println("Rounded to two digits (wrong) = " + round2DigitA);
		  System.out.println("Rounded to two digits (wrong) = " + round2DigitB);
		  System.out.println("Rounded to two digits (wrong) = " + round2DigitC);
		  System.out.println("Rounded to two digits (right) = " + round2DigitD);

		  // The different integer types in Java have different sizes in memory and
		  // their ranges are correspondingly different.  Byte has one byte, short
		  // has two, int 4 and long 8.  However, the types all allow both positive
		  // and negative numbers, so the maximum positive value that can be stored
		  // is roughly 1/2 the number of total values.  For example, consider the
		  // byte type:
		  //      8 bits can store up to 2^8 = 256 different values
		  //        0 (all 0s)
		  //        1 to 127 positive values (leftmost digit is a 0)
		  //        -1 to -128 negative values (leftmost digit is a 1)
		  // If a value that is too large is cast into a smaller type, the most
		  // significant bits will simply be removed, and the value stored will be
		  // based on the remaining digits (this is why you get the "loss of
		  // of precision error" if you do not explicitly cast the value").  For
		  // example, consider the values below.

		  int i1 = 32767, i2 = 32768, i3 = 32769;
		  short s1, s2, s3; byte b1, b2, b3;
		  s1 = (short) i1;  s2 = (short) i2;  s3 = (short) i3;
		  b1 = (byte) i1;  b2 = (byte) i2;  b3 = (byte) i3;

		  // The largest positive short value is 32767, and when we attempt to
		  // store 32768 in s2, it is actually stored as a negative, since the
		  // leftmost digit that remains after casting is a 1.  A similar thing
		  // occurs for the casting to byte.  You will learn more about how binary
		  // data is stored and manipulated in the CS 0447 course.

		  System.out.println("i1 = " + i1 + " s1 = " + s1 + " b1 = " + b1);
		  System.out.println("i2 = " + i2 + " s2 = " + s2 + " b2 = " + b2);
		  System.out.println("i3 = " + i3 + " s3 = " + s3 + " b3 = " + b3);
		  
		  int i = 10, j = 10;
		  int m = i++;
		  int n = ++j;
		  System.out.println("i:" + i + " j:" + j + " m:" + m + " n:" + n);

      }
}
