import java.util.Iterator;import java.util.Scanner;public class Concordance{   private DictionaryInterface<String, ListWithIteratorInterface<Integer>> wordTable;             public Concordance()   {      wordTable = new SortedDictionary<String, ListWithIteratorInterface<Integer>>();   } // end default constructor   /** Reads a text file of words and creates a concordance.      @param data  a text scanner for the text file of data */   public void readFile(Scanner data)   {   // . . . < See Segment 19.20. >   } // end readFile   /** Displays words and the lines in which they occur. */   public void display()   {   // . . . < See Segment 19.21. >   } // end display} // end Concordance