
public class Pattern {

	int width;
	int height;
	int value;
	String name;
	
	public Pattern(int width, int height, int v, String n) {
		this.width = width;
		this.height = height;
		value = v;
		name = n;
	}
	
	public String toString() {
		return name;
	}
	
}
