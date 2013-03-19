///
/// Contents: Test BSTOptimizer methods.
/// Author:   John Aronis
/// Date:     February 2013
///

import java.util.ArrayList ;
import java.util.Random ;

public class TestBSTOptimizer {

  public static int MIN_KEYS      = 10 ;
  public static int MAX_KEYS      = 100 ;
  public static int INCREMENT     = 1 ;
  public static int MIN_FREQUENCY = 1 ;
  public static int MAX_FREQUENCY = 10000 ;

  public static void main(String[] args) {

    Random R = new Random() ;
    BinaryTree bestBST ;
    BSTOptimizer optimizer ;

    System.out.println("CREATE SMALL EXAMPLE") ;
    optimizer = new BSTOptimizer() ;
    optimizer.addKey("A",4) ;
    optimizer.addKey("B",2) ;
    optimizer.addKey("C",1) ;
    optimizer.addKey("D",3) ;
    optimizer.addKey("E",5) ;
    optimizer.addKey("F",2) ;
    optimizer.addKey("G",1) ;

    System.out.println("RUN SMALL EXAMPLE WITH MEMOIZATION") ;
    optimizer.MEMOIZE = true ;
    optimizer.CALLS = 0 ;
    bestBST = optimizer.optimize() ;
    System.out.println( "  Optimal BST: " + bestBST) ;
    System.out.println( "  Cost: " + bestBST.cost) ;
    System.out.println( "  Recursive calls: " + optimizer.CALLS ) ;

    System.out.println("RUN SMALL EXAMPLE WITHOUT MEMOIZATION") ;
    optimizer.MEMOIZE = false ;
    optimizer.CALLS = 0 ;
    bestBST = optimizer.optimize() ;
    System.out.println( "  Optimal BST: " + bestBST) ;
    System.out.println( "  Cost: " + bestBST.cost) ;
    System.out.println( "  Recursive calls: " + optimizer.CALLS ) ;

    System.out.println("TEST RUNTIME WITH MEMOIZATION (KEYS CALLS CALLS/KEYS^3)") ;
    for (int keys=MIN_KEYS ; keys<=MAX_KEYS ; keys+=INCREMENT) {
      optimizer = new BSTOptimizer() ;
      optimizer.MEMOIZE = true ;
      optimizer.CALLS = 0 ;
      for (int k=0 ; k<keys ; k++) optimizer.addKey("KEY-"+k,R.nextInt(MAX_FREQUENCY)) ;
      bestBST = optimizer.optimize() ;
      System.out.printf("  %4d  %10d  %15f \n", keys, optimizer.CALLS, (float)optimizer.CALLS/(keys*keys*keys)) ;
    }

    System.out.println("TEST RUNTIME WITHOUT MEMOIZATION (KEYS CALLS CALLS/KEYS^3)") ;
    for (int keys=MIN_KEYS ; keys<=MAX_KEYS ; keys+=INCREMENT) {
      optimizer = new BSTOptimizer() ;
      optimizer.MEMOIZE = false ;
      optimizer.CALLS = 0 ;
      for (int k=0 ; k<keys ; k++) optimizer.addKey("KEY-"+k,R.nextInt(MAX_FREQUENCY)) ;
      bestBST = optimizer.optimize() ;
      System.out.printf("  %4d  %10d  %15f \n", keys, optimizer.CALLS, (float)optimizer.CALLS/(keys*keys*keys)) ;
    }

  }

}

/// End-of-File

