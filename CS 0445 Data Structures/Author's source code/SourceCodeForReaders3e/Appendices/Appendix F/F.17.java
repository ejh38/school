import java.io.File;import java.io.FileNotFoundException;import java.io.PrintWriter;import java.util.Scanner;/**   A class of methods that create and display a text file of   user-supplied data.   @author Frank M. Carrano*/public class TextFileOperations{   // < The method createTextFile, as given in Listing F-1, appears here. >   // . . .      /** Displays all lines in the named text file.       @param fileName the file name as a string       @return true if the operation is successful */   public static boolean displayFile(String fileName)   {      boolean fileOpened = true;      try      {         Scanner fileData = new Scanner(new File(fileName));         System.out.println("The file " + fileName +                            " contains the following lines:");         while (fileData.hasNextLine())         {            String line = fileData.nextLine();            System.out.println(line);         } // end while         fileData.close();      }      catch (FileNotFoundException e)      {         fileOpened = false; // error opening the file      }            return fileOpened;   } // end displayFile} // end TextFileOperations