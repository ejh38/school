public class Room2 {

	private string difficulty = "easy";

	public Controller input;
	public Weapon [] weapon_set;
	public Door [] doors;

	public Room2 {
		setup_room();

		start();
	}

	public void init_controls() {
		input = Controller.default;
	}

	public void start() {
		while (!has_won() {
			input.check_input();
			
			if (doors[0].used()) {
				System.out.println("Not this one.");	
			}
			Game.render();		
		}
		Game.load_next_level();
	}

	public void init_weapons() {
		weapon_set = Weapon.Unarmed;
	}

	public void init_doors() {
		doors[0].side = Door.door_sides.EAST;
		doors[0].set_active(false);

		doors[1].side = Door.door_sides.WEST;
		doors[1].set_active(false);
	}

	public void setup_room() {
		init_doors();
		init_controls();
		init_weapons();
	}

	public boolean has_won() {
		if (doors[1].is_used()) {
			return true;
		}
		return false;
	}
}
