// CS 401 Fall 2011
// MyText interface for Assignment 5
// This interface simply adds one method to MyShape (note that it inherits
// the other methods, so a class implementing MyText must also implement
// all of the MyShape methods)

public interface MyText extends MyShape
{                            
	public void setText(String newText);
	
	/*	Note: saveData is not a new method for this interface, but the format
		requires an additional field for the text.  Thus, for MyText objects,
		the output to saveData will be
		ClassName:X:Y:size:text
		public String saveData();
	*/
}