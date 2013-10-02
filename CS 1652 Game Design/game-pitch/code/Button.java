public class Button implements Interactable {

	public int side;

	public enum button_sides = {
		NORTH_1, NORTH_2, NORTH_3, 
		SOUTH_1, SOUTH_2, SOUTH_3, 
		EAST_1,  EAST_2,  EAST_3, 
		WEST_1, WEST_2, WEST_3
	};

	// determines whether a button can be pressed
	public void set_active(boolean a) {
		active = a;
	}

	// answers whether a button is currently pressed in
	public boolean used() {
		return used;
	}

}