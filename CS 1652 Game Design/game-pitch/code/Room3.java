public class Room3 {

	private string difficulty = "medium";

	public Controller input;	
	public Button [] switches;
	public Weapon [] weapon_set;
	public Door door;

	public Room3 {
		setup_room();

		start();
	}

	public void init_controls() {
		input = Controller.REVERSED;
	}

	public void init_switches() {
		switches[0].side = WEST.2
		switches[1].side = WEST.1
		switches[2].side = WEST.3
		switches[3].side = EAST.2

		for (int i = 0; i < 3; i++) {
			switches[i].set_active(false);
		}
	}

	public void start() {
		while (!has_won() {
			input.check_input();

			if (switches[3].is_used()) {
				if (!switches[0].is_used() && 
					!switches[2].is_used() &&
					switches[1].is_used()) {
					Game.load_next_level();
				} 
			} 
			Game.render();		
		}
	}

	public void init_weapons() {
		weapon_set = Weapon.Unarmed;
	}

	public void init_doors() {
		door.side = Door.door_sides.NORTH
		door.set_active(false);
	}

	public void setup_room() {
		init_doors();
		init_controls();
		init_switches();
		init_weapons();
	}

	public boolean has_won() {
		return false;
	}

}
