/** 
    An interface for the ADT list.
    Entries in the list have positions that begin with 1.

   @author Frank M. Carrano
   @version 3.0
*/
public interface ListInterface<T>
{
   /** Adds a new entry to the end of this list.
       Entries currently in the list are unaffected.
       The list’s size is increased by 1.
       @param newEntry the object to be added as a new entry */
   public void add(T newEntry);
   
   /** Adds a new entry at a specified position within this list.
       Entries originally at and above the specified position
       are at the next higher position within the list.
       The list’s size is increased by 1.
       @param newPosition  an integer that specifies the desired
                           position of the new entry
       @param newEntry  the object to be added as a new entry
       @return true if the addition is successful, or
               false if newPosition < 1, or newPosition > getLength() + 1 */
   public boolean add(int newPosition, T newEntry);
   
   /** Removes the entry at a given position from this list.
       Entries originally at positions higher than the given
       position are at the next lower position within the list,
       and the list’s size is decreased by 1.
       @param givenPosition  an integer that indicates the position of
                             the entry to be removed
       @return a reference to the removed entry or null, if either
               the list was empty, givenPosition < 1, or
               givenPosition > getLength() */
   public T remove(int givenPosition);
   
   /** Removes all entries from this list. */
   public void clear();
   
   /** Replaces the entry at a given position in this list.
       @param givenPosition  an integer that indicates the position of
                             the entry to be replaced
       @param newEntry  the object that will replace the entry at the
                        position givenPosition
       @return true if the replacement occurs, or false if either the
               list is empty, givenPosition < 1, or
               givenPosition > getLength() */
   public boolean replace(int givenPosition, T newEntry);
   
   /** Retrieves the entry at a given position in this list.
       @param givenPosition  an integer that indicates the position of
                             the desired entry
       @return a reference to the indicated entry or null, if either
               the list is empty, givenPosition < 1, or
               givenPosition > getLength() */
   public T getEntry(int givenPosition);
   
   /** Sees whether this list contains a given entry.
       @param anEntry the object that is the desired entry
       @return true if the list contains anEntry, or false if not */
   public boolean contains(T anEntry);
   
   /** Gets the length of this list.
       @return the integer number of entries currently in the list */
       public int getLength();
       
   /** Sees whether this list is empty.
       @return true if the list is empty, or false if not */
       public boolean isEmpty();
       
   /** Retrieves all entries that are in this list in the order in which
       they occur in the list. */
   public T[] toArray();   
} // end ListInterface
