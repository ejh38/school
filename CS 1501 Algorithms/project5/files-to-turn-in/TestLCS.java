//////////////////////////////////////////////////////////////////////
///
/// Contents: Test LCS program.
/// Author:   John Aronis
/// Date:     December 2009
///
//////////////////////////////////////////////////////////////////////

/// This file tests the LCS program two ways:
/// 
///   - First, it looks for the LCS "hello_world" in a pair of strings.
/// 
///   - Second, it times the program with longer and longer inputs.
/// 
/// To demonstrate the program is actually quadratic, the square of the
/// length of the strings is divided out of the timing results of the
/// second tests.  The result should be constant.

import java.util.Date ;
import java.util.Random ;

public class TestLCS {

  public static int START_LENGTH = 10 ;
  public static int INCREMENT_LENGTH = 10 ;
  public static int ITERATIONS = 100 ;

  public static void main(String[] args) {
    String word1, word2 ;
    word1 = "h<werefdsll<oxcsfd_vwoadsrlt<rdsdaas++dqwe" ;
    word2 = "phl>kelil>iop_owoklrplkm=poi=ljkll=kjppd" ;
    System.out.println("A SIMPLE TEST THAT YOU WILL RECOGNIZE...") ;
    System.out.println( "  " + LCS.findLCS(word1,word2) ) ;
    System.out.println("THIS SHOULD DEMONSTRATE THAT TIME/LENGTH^2 IS (ROUGHLY) CONSTANT...") ;
    for (int length=START_LENGTH ; true ; length+=INCREMENT_LENGTH ) {
      word1 = word(length) ;
      word2 = word(length) ;
      start() ;
      for (int iteration=0 ; iteration<ITERATIONS ; iteration++) {
        LCS.findLCS(word1,word2) ;
      }
      System.out.printf("  Length = %4d     Time/Length^2 = %10f \n", length, (float)(elapsed())/(float)(length*length)) ;
    }
  }

  public static String word(int length) {
    String result = "" ;
    Random r = new Random() ;
    char c ;
    for (int i=0 ; i<length ; i++) { result += (char)(97 + r.nextInt(26)) ; }
    return result ;
  }

  public static long zero ;
  public static void start() { zero = (new Date()).getTime() ; }
  public static long elapsed() { return (new Date()).getTime() - zero ; }

}

/// End-of-File
