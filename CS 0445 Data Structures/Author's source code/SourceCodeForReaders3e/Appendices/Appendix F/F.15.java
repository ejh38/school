String fileName = "data.txt";Scanner fileData = null;try{   // can throw FileNotFoundException   fileData = new Scanner(new File(fileName));}catch (FileNotFoundException e){   System.out.println("Scanner error opening the file " + fileName);   System.out.println(e.getMessage());   // < Possibly other statements that react to this exception. >}