// CS 0445 Spring 2012
// Comparison of Power function done iteratively, recursively in a simple
// way, and using Divide and Conquer.  The BigInteger class is used here so
// that we can get some very large numbers.

import java.math.BigInteger;
import java.io.*;

public class Power
{
    private BigInteger pow1mults, pow2mults, pow3mults;
    public static final BigInteger zero = BigInteger.ZERO;
    public static final BigInteger one = BigInteger.ONE;
    public static final BigInteger two = new BigInteger("2");

    public Power() throws IOException
    {
          pow1mults = zero;
          pow2mults = zero;
          pow3mults = zero;

          BufferedReader indata = new BufferedReader(
                         new InputStreamReader(System.in));
          System.out.println("Enter the integer base: ");
          BigInteger base = new BigInteger(indata.readLine());
          System.out.println("Enter the integer exponent: ");
          BigInteger exp = new BigInteger(indata.readLine());
          BigInteger ans;
          ans = Pow1(base, exp);
          System.out.println(base + "^" + exp + " iter: " + ans);
          System.out.println("Requires " + pow1mults + " mults ");
          ans = Pow2(base, exp);
          System.out.println(base + "^" + exp + " rec: " + ans);
          System.out.println("Requires " + pow2mults + " mults ");
          ans = Pow3(base, exp);
          System.out.println(base + "^" + exp + " div/conq: " + ans);
          System.out.println("Requires " + pow3mults + " mults ");
    }

    public static void main (String [] args) throws IOException
    {
          Power P = new Power();
    }

	// Use a simple for loop to calculate X^N
    public BigInteger Pow1(BigInteger X, BigInteger N)
    {
          BigInteger i, temp;
          temp = one;

       // If using regular ints, the loop below would look like:
       // for (i = 1; i <= N; i++)

          for (i = one; i.compareTo(N) <= 0; i = i.add(one))
          {
               temp = temp.multiply(X);
               pow1mults = pow1mults.add(one);
          }
          return temp;
    }

	// Use a simple recursive function to calculate X^N -- although
	// recursive the effect of this method is very similar to that
	// of Pow1 above.
    public BigInteger Pow2(BigInteger X, BigInteger N)
    {
          if (N.compareTo(zero) == 0)
                return new BigInteger("1");
          else
          {
                pow2mults = pow2mults.add(one);
                return X.multiply(Pow2(X, N.subtract(one)));
                      // X * Pow2(X, N-1)
          }
    }

	// Divide and conquer function to calculate X^N
    public BigInteger Pow3(BigInteger X, BigInteger N)
    {
          if (N.compareTo(zero) == 0)
                return new BigInteger("1");
          {
                BigInteger NN = N.divide(two);
                BigInteger temp = Pow3(X, NN);
                pow3mults = pow3mults.add(one);
                if ((N.mod(two)).compareTo(zero) == 0) // N is even
                {
                    return (temp.multiply(temp));      // temp * temp
                }
                else                                   // N is odd
                {
                    pow3mults = pow3mults.add(one);
                    BigInteger MM = temp.multiply(temp);
                    return (MM.multiply(X));           // X * temp * temp
                }
          }
    }

}