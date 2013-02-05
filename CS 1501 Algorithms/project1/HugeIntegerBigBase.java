// Zach Sadler
// Project 1
// zps6@pitt.edu

import java.util.Arrays;


public class HugeIntegerBigBase implements Comparable<HugeIntegerBigBase> {

	public static int DIGIT_OPERATIONS;
	
	public static int POWER_OF_TEN = 1;
	
	private String digitString;
	private int numDigits;
	private int digits[];
	
	public HugeIntegerBigBase(String s) {
		for (; s.charAt(0) == '0' && s.length() > 1;) {
			s = new String(s.substring(1));
		}
		
		digitString = s;
		numDigits = s.length()/POWER_OF_TEN;
		digits = new int[numDigits];
		
		for (int i = 0; i < numDigits; i += POWER_OF_TEN) {
			digits[i] = Integer.parseInt(s.substring(numDigits-i-1, numDigits));
		}
	}
	
	// returns -1 if this < h
	// returns  1 if this > h
	// returns  0 if this == h
	public int compareTo(HugeIntegerBigBase h) {
		// if one has more digits than the other, it's bigger
		if (this.numDigits < h.numDigits) {
			return -1;
		}
		if (this.numDigits > h.numDigits) {
			return 1;
		}		
		// otherwise, go left to right and see if one digit is > the other
		for (int i = this.numDigits - 1; i >= 0; i--) {
			DIGIT_OPERATIONS++;
			DIGIT_OPERATIONS++;
			if (this.digits[i] < h.digits[i]) {
				return -1;			// if so, then we're done
			}
			DIGIT_OPERATIONS++;
			DIGIT_OPERATIONS++;
			if (this.digits[i] > h.digits[i]) {
				return 1;
			}
		}
		// if we made it all the way here then they're equal, so return 0
		return 0;
	}
    
	public HugeIntegerBigBase add(HugeIntegerBigBase h) {
		int [] temp, temp2;

		if (this.numDigits > h.numDigits) {
			// add h to this
			temp = new int[this.numDigits + 1];
			temp2 = Arrays.copyOf(h.digits, this.numDigits); 
			for (int i = 0; i < this.numDigits; i++) {
				DIGIT_OPERATIONS++;
				if ((temp[i] + this.digits[i] + temp2[i]) > 9) {
					temp[i+1]++;		// this part is the carry
				}
				DIGIT_OPERATIONS++;
				temp[i] = (temp[i] + this.digits[i] + temp2[i]) % 10;	// last digit of sum
			}
		}
		else {
			// add this to h
			temp = new int[h.numDigits + 1];
			temp2 = Arrays.copyOf(this.digits, h.numDigits);
			for (int i = 0; i < h.numDigits; i++) {
				DIGIT_OPERATIONS++;
				if ((temp[i] + temp2[i] + h.digits[i]) > 9) {
					temp[i+1]++;		// this part is the carry
				}
				DIGIT_OPERATIONS++;
				temp[i] = (temp[i] + temp2[i] + h.digits[i]) % 10;	// last digit of sum				
			}
		}
	
		StringBuilder build = new StringBuilder();
		for (int i = temp.length - 1; i >= 0; i--) {
			DIGIT_OPERATIONS++;
			build.append(temp[i]);
		}
		
		return new HugeIntegerBigBase(build.toString());
	}
	
	public HugeIntegerBigBase subtract(HugeIntegerBigBase h) {
		//subtracts h from this. Assumes h is not larger than this.
		int [] temp = new int[this.numDigits];
		int [] temp2 = Arrays.copyOf(h.digits, this.numDigits);

		if (this.compareTo(h) < 0) {
			System.out.println("try again man, this was smaller than h");
			return this;
		}
		
		for (int i = 0; i < this.numDigits; i++) {
			DIGIT_OPERATIONS++;
			if (this.digits[i] + temp[i] < temp2[i]) {
				temp[i+1]--;
				temp[i] += 10;
			}
			DIGIT_OPERATIONS++;
			temp[i] = temp[i] + this.digits[i] - temp2[i];
		}
		
		StringBuilder build = new StringBuilder();
		for (int i = temp.length - 1; i >= 0; i--) {
			DIGIT_OPERATIONS++;
			build.append(temp[i]);
		}
		
		return new HugeIntegerBigBase(build.toString());
	}
	
	/*
	public HugeIntegerBigBase seantiply(HugeIntegerBigBase h) {
		System.out.println("this.toString is " + this.toString());
		System.out.println("h.toString is " + h.toString());
		int lol = 0;
		HugeIntegerBigBase a = new HugeIntegerBigBase("0");
		HugeIntegerBigBase b = new HugeIntegerBigBase(this.toString());
		HugeIntegerBigBase i = new HugeIntegerBigBase("1");
		while ( i.compareTo(h) < 1 ) {
			a = a.add(b);

			HugeIntegerBigBase temp = new HugeIntegerBigBase("1");
		//	System.out.println("i is HUUUEEE  " + i);
			lol++;
			i = i.add(temp);
//			System.out.println("i is " + i);

		}
		System.out.println("lol: "+ lol);
		System.out.println("Multiplication result is" + a.toString());
		return a;
	}
	*/
	
	public HugeIntegerBigBase multiply(HugeIntegerBigBase h) {
		HugeIntegerBigBase temp = new HugeIntegerBigBase("0");
		for (int i = 0; i < this.numDigits; i++) {
			for (int j = 0; j < h.numDigits; j++) {
				StringBuilder build = new StringBuilder();
				DIGIT_OPERATIONS++;
				 build.append(this.digits[i]*h.digits[j]);
				for (int k = 0; k < (i + j); k++) {
					build.append("0");
				}
				temp = temp.add(new HugeIntegerBigBase(build.toString()));
			}
		}
		return temp;
	}

	// multiplies this and h using Karatsuba-Ofman multiplication.
	public HugeIntegerBigBase fastMultiply(HugeIntegerBigBase h) {

		// if we're at the base case, then return normal multiply
		if (this.numDigits <= 10 || h.numDigits <= 10) {
			return this.multiply(h);
		}
		
		// find the shorter number of digits between the two
		int n = h.numDigits;
		if (h.numDigits > n) {
			n = this.numDigits;
		}
		
		// pick n based on even or odd
		int midpoint = n/2 + n % 2;
	
		// name a, b, c, d
		HugeIntegerBigBase a = new HugeIntegerBigBase(this.toString().substring(0, this.numDigits - midpoint));
		HugeIntegerBigBase b = new HugeIntegerBigBase(this.toString().substring(this.numDigits - midpoint, this.numDigits));
		HugeIntegerBigBase c = new HugeIntegerBigBase(h.toString().substring(0, h.numDigits - midpoint));
		HugeIntegerBigBase d = new HugeIntegerBigBase(h.toString().substring(h.numDigits - midpoint, h.numDigits));

		// calculate a*c and b*d
		// this is where all the work is
		HugeIntegerBigBase ac = a.fastMultiply(c);			// a*c
		HugeIntegerBigBase bd = b.fastMultiply(d);			// b*d
		
		// tack on zeroes for the 10^n term
		StringBuilder build = new StringBuilder(ac.toString());
		for (int i = 0; i < 2*midpoint; i++) {
			build.append("0");
		}
		HugeIntegerBigBase term2 = new HugeIntegerBigBase(build.toString());	// ac*10^n
		HugeIntegerBigBase term3 = a.add(b);		// (a+b)
		HugeIntegerBigBase term4 = c.add(d);		// (c+d)
		
		// aw man, another recursive call here
		HugeIntegerBigBase term5 = term3.fastMultiply(term4);	// [(a+b)(c+d)]
		term5 = term5.subtract(ac);
		term5 = term5.subtract(bd);						// [(a+b)(c+d) - ac - bd)]
		
		build = new StringBuilder(term5.toString());
		for (int i = 0; i < midpoint; i++) {
			build.append("0");
		}

		HugeIntegerBigBase term6 = new HugeIntegerBigBase(build.toString());	// [(a+b)(c+d) - ac - bd]*10^(n/2)
		
		term2 = term2.add(term6); 		// ac*10^n + [(a+b)(c+d) - ac - bd]*10^(n/2)
		return term2.add(bd);			//  ac*10^n + [(a+b)(c+d) - ac - bd]*10^(n/2) + bd
	}
	
	public String toString() {
		return digitString;
	}
	
}
