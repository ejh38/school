import visitor.*;

public class SymbolMethod {

	public Type returnType;
	public boolean isVoid;
	ArrayList<Type> parameters;

	public SymbolMethod(boolean isVoid, Type returnType) {
		this.isVoid = isVoid;
		this.returnType = returnType;
	}

	public void addParameter(Type t) {
		parameters.add(t);
	}

	public int numParameters() {
		return parameters.size();
	}

	public boolean sameParameters(ArrayList<Type> p) {
		return parameters.equals(p);
	}

}