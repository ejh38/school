public boolean equals(Object other){   boolean result;   if (other instanceof Name)   {      Name otherName = (Name)other;      result = first.equals(otherName.first) &&                last.equals(otherName.last);   } // end if   return result;} // end equals