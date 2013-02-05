// CS 445 Spring 2012
// SaveRestore interface.  This interface allows the contents of the
// current collection of data to be written to a file as objects using
// the writeObject() method of the ObjectOutputStream class and to be
// read as objects using the readObject() method of the ObjectInputStream
// class.  See more details below.

public interface SaveRestore
{
	// Write all of the objects in this collection to the file with name
	// specified below.  The objects should be written using an
	// ObjectOutputStream and the writeObject() method.  The method should
	// not remove the data from the collection or otherwise change the
	// collection in any way.  If all goes well, return true.  If any error
	// occurs in the writing process, return false.
	public boolean saveToFile(String fileName);

	// Read all of the objects from the file specified into the current
	// collection.  Before reading you should clear any objects from the
	// collection.  The objects should be read using an ObjectInputStream
	// and the readObject() method.  If all goes well, return true.  If
	// any error occurs in the reading process, return false.
	public boolean restoreFromFile(String fileName);
}
