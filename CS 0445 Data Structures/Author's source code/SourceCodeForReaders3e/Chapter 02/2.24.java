	/** Removes one unspecified entry from this bag, if possible.       @return either the removed entry, if the removal               was successful, or null */	public T remove()	{		T result = removeEntry(numberOfEntries - 1);				return result;	} // end remove