import syntaxtree.*;
import visitor.*;
import java_cup.runtime.Symbol;
import java.io.*;


public class Main {
   public static void main(String [] args) {
      if(args.length != 1) {
			System.err.println("ERROR: Invalid number of command line arguments.");
			System.err.println("Usage: java Calc file.asm");
			System.exit(1);
		}

      try {
         BestParser root = new BestParser(new BestLexer(new FileInputStream(args[0])));
         root.parse();
         new PrettyPrintVisitor().visit(root.finishedProduct);
      }
      catch (Exception e) {
         System.out.println(e.toString());
      }
   }
}