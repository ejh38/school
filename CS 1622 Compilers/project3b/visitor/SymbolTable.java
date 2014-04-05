package visitor;

import java.util.*;

public class SymbolTable {

	Stack<String> symbols;
	Hashtable<String, LinkedList<Object>> table;

	public SymbolTable() {
		symbols = new Stack<String>();
		table = new Hashtable<String, LinkedList<Object>>();
	}

	public SymbolTable(Stack<String> symbols, Hashtable<String, LinkedList<Object>> table) {
		this.table = table;	
		this.symbols = symbols;
	}

	public String toString() {
		return table.toString();
	}

	public void addSymbol(String name, Object value) {
		symbols.push(name);
		
		LinkedList<Object> potentialMatches = table.get(name);
		if (potentialMatches == null) {
			// no match, so make a new list for it
			potentialMatches = new LinkedList<Object>();
		}
		// add the value to the list, and the list to the hashtable
		potentialMatches.add(value);
		table.put(name, potentialMatches);
	}

	// either return the last symbol added to the list with that name
	// or null if we don't have any
	public Object getSymbol(String name) {
		LinkedList<Object> potentialMatches = table.get(name);
		if (potentialMatches == null) {
			return null;
		}
		else {
			return potentialMatches.getLast();
		}
	}

	// we push an illegal identifier on as a delimiter
	public void pushScope() {
		symbols.push("#rekt");
	}

	// we will go through our symbol stack, popping off until
	// we hit the delimiter. as we pop, we remove the corresponding
	// objects from the hashtable
	public void destroyScope() {
		String top = symbols.pop();
		while (!top.equals("#rekt")) {
			LinkedList<Object> potentialMatches = table.get(top);
			potentialMatches.removeLast();

			// if we removed the last object from the list, pop off the whole list
			if (potentialMatches.size() == 0) {
				table.remove(top);
			}

			top = symbols.pop();
		}
	}

}