
public class Cut {

	boolean vertical;
	int position;
	
	// takes the cloth that it performed the cut on,
	// a boolean for vertical or horizontal
	// and where on the cloth it belongs
	// position is an x coordinate for vertical and a y coordinate for horizontal
	public Cut(boolean vert, int pos) {
		vertical = vert;
		position = pos;
	}
	
	public String toString() {
		if (vertical) {
			return "vertical " + position;
		}
		else {
			return "horizontal " + position; 	
		}
	}
}
