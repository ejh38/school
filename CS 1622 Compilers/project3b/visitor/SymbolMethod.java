package visitor;

import visitor.*;
import syntaxtree.*;
import java.util.ArrayList;

public class SymbolMethod {

	public String name;
	public Type returnType;
	ArrayList<SymbolVariable> parameters;
	SymbolClass parent;

	public SymbolMethod(String n, Type returnType) {
		name = n;
		this.returnType = returnType;
		parameters = new ArrayList<SymbolVariable>();
	}

	public String toString() {
		return name;
	}

	public void addParameter(SymbolVariable t) {
		parameters.add(t);
	}

	public void addParent(SymbolClass p) {
		parent = p;
	}

	public int numParameters() {
		return parameters.size();
	}

	public boolean sameParameters(ArrayList<SymbolVariable> p) {
		return parameters.equals(p);
	}

}