///
/// Contents: Test Cloth-Cutter Program
/// Author:   John Aronis
/// Date:     May 2012
///

import java.util.ArrayList ;
import javax.swing.* ;
import java.util.Date ;

public class TestClothCutter {

  public static int SYNC = 500 ;
  public static int SLEEP = 300 ;

  public static void main(String[] args) {

    ArrayList<Pattern> patterns = new ArrayList<Pattern>() ;
    patterns.add(new Pattern(2,2,1,"A")) ;
    patterns.add(new Pattern(2,6,4,"B")) ;
    patterns.add(new Pattern(4,2,3,"C")) ;
    patterns.add(new Pattern(5,3,5,"D")) ;
    int width = 30 ;
    int height = 15 ;
    int pixels = 30 ;

    ClothCutter cutter = new ClothCutter(width,height,patterns) ;
    cutter.optimize() ;
    System.out.println( cutter.value() ) ;
    System.out.println( cutter.garments() ) ;

    Cloth cloth = new Cloth(width,height,pixels) ;
    JFrame frame = new JFrame("A Bolt of Fabulously Expensive Silk") ;
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE) ;
    frame.getContentPane().add(cloth) ;
    frame.pack() ;
    frame.setVisible(true) ;
    sleep(SYNC) ;
    for (Cut c : cutter.cuts()) { sleep(SLEEP) ; cloth.drawCut(c) ; }
    sleep(SYNC) ;
    for (Garment g : cutter.garments()) { sleep(SLEEP) ; cloth.drawGarment(g) ; }

  }

  public static void sleep(long milliseconds) {
    Date d ;
    long start, now ;
    d = new Date() ;
    start = d.getTime() ;
    do { d = new Date() ; now = d.getTime() ; } while ( (now - start) < milliseconds ) ;
  }

}

/// End-of-File

