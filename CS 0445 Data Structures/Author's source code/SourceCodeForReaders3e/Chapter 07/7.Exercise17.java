public int f(int n){   int result = 0;   if(f <= 4)      result = 1;   else      result = f(n / 2) + f(n / 4);   return result;} // end f