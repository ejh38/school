// Segment 5.8
/**
   A class that checks whether the parentheses, brackets, and braces 
   in a string occur in left/right pairs.
   
   @author Frank M. Carrano
   @version 3.0
*/
public class BalanceChecker
{
   /** Decides whether the parentheses, brackets, and braces 
       in a string occur in left/right pairs.
       @param expression  a string to be checked
       @return true if the delimiters are paired correctly */
   public static boolean checkBalance(String expression)
   {
      StackInterface<Character> openDelimiterStack = new LinkedStack<Character>();

      int characterCount = expression.length();
      boolean isBalanced = true;
      int index = 0;
      char nextCharacter = ' ';
       
      for (; isBalanced && (index < characterCount); index++)
      {
         nextCharacter = expression.charAt(index);
         switch (nextCharacter)
         {
            case '(': case '[': case '{':
               openDelimiterStack.push(nextCharacter);
               break;
             
            case ')': case ']': case '}':
               if (openDelimiterStack.isEmpty())
                  isBalanced = false;
               else
               {
                  char openDelimiter = openDelimiterStack.pop();
                  isBalanced = isPaired(openDelimiter, nextCharacter);
               } // end if
               break;
             
            default: break;
         } // end switch
      } // end for
       
      if (!openDelimiterStack.isEmpty())
         isBalanced = false;
         
      return isBalanced;
   } // end checkBalance
  
   /** Detects whether two delimiters are a pair of 
       parentheses, brackets, or braces.
       @param open   a character
       @param close  a character
       @return true if open/close form a pair of parentheses, brackets, 
               or braces */
   private static boolean isPaired(char open, char close)
   {
      return (open == '(' && close == ')') ||
             (open == '[' && close == ']') ||
             (open == '{' && close == '}');
   } // end isPaired
} // end BalanceChecker
