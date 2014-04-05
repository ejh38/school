package visitor;

import visitor.*;
import syntaxtree.*;

public class SymbolVariable {

	String name;
	Type type;
	SymbolMethod parentMethod;

	public SymbolVariable(String n, Type t) {
		name = n;
		type = t;
	}

	public String toString() {
		return name;
	}

	public void addParent(SymbolMethod p) {
		parentMethod = p;
	}

	public boolean correctType(Type t) {
		return type.equals(t);
	}

}