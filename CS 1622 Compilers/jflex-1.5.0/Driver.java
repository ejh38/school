import java.io.*;

public class Driver {
	
	public static void main(String [] args) throws Exception {

		if (args.length != 1) {
			System.out.println("Hey man, please give a command-line argument." +
												 "\nTry 'java Driver PROGRAM_NAME'.");
			System.exit(0);
		}

		Zps6PrettiestPrinter steve = new Zps6PrettiestPrinter(new FileInputStream(args[0]));

		steve.yylex();

		System.out.println("\n\n\nAll done! Exiting.");
		return;
	}
}