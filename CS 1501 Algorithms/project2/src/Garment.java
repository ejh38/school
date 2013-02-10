
public class Garment {

	int pos_x;
	int pos_y;
	String name;
	int value;

	public Garment(int px, int py, String n, int value) {
		pos_x = px;
		pos_y = py;
		name = n;
		this.value = value;
	}
	
	public String toString() {
		return "[" + name + ", " + pos_x + ", " + pos_y + "]";
	}
	
}
