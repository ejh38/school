String result = "";try{   Double temp = OurMath.squareRoot(value);   result = temp.toString();}catch (SquareRootException e){  // Assertion: value is negative   Double temp = OurMath.squareRoot(-value);   result = temp.toString() + "i";}