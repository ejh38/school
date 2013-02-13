
public class Garment {

	int pos_x;
	int pos_y;
	String name;

	public Garment(int px, int py, String n) {
		pos_x = px;
		pos_y = py;
		name = n;
	}
	
	public String toString() {
		return "[" + name + ", " + pos_x + ", " + pos_y + "]";
	}
	
}
