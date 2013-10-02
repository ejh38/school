public class Room1 {

	private string difficulty = "very easy";

	public Door door;
	public Controller input;
	public Weapon [] weapon_set;

	public Room1 {
		setup_room();

		start();
	}

	public boolean has_won() {
		if (door.is_used()) {
			return true;
		}
		return false;
	}

	public void init_doors() {
		door.side = Door.door_sides.NORTH;
		door.set_active(true);
	}

	public void init_controls() {
		input = Controller.default;
	}

	public void init_weapons() {
		weapon_set = Weapon.Unarmed;
	}

	public void start() {
		while (!has_won()) {
			input.check_input();
			Game.render();		
		}

		Game.load_next_level();
	}

	public void setup_room() {
		init_doors();
		init_controls();
		init_weapons();
	}

}
