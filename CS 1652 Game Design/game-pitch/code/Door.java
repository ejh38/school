public class Door implements Interactable {

	public int side;

	public enum door_sides = {
		North, South, East, West
	};

	// determines whether the door can be opened and walked through
	public void set_active(boolean a) {
		active = a;
	}

	// answers whether the door has been walked through
	public boolean used() {
		return used;
	}
}