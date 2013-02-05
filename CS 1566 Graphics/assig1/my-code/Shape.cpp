/**************************************************************************
File: Shape.cpp
Does: Acts as the data structure for Assignment 1
Author: Zach Sadler - zps6@pitt.edu
Date: 9/6/12
**************************************************************************/

class Shape {
		double x, y;						// for position
		signed short type;			// rectangle or circle -> 1 is rect, -1 is circ
		double width, height;		// for rectangles, or radius_x, radius_y for circles
		double color;						// used for the strobe effect

		double y_velocity, x_velocity;	// for physics!
	
	public:
		double get_x() { return x; }
		double get_y() { return y; }
		double get_type() { return type; }
		double get_y_velocity() { return y_velocity; }
		double get_x_velocity() { return x_velocity; }

		double get_width() { return width; }
		double get_height() { return height; }
		double get_color() { return color; }
		
		void set_x(double);
		void set_y(double);
		void set_type(signed short);
		void set_y_velocity(double);
		void set_x_velocity(double);

		void set_width(double);
		void set_height(double);
		void set_color(double);

		void set_shape(signed short, double, double, double, double);
		void handle_gravity(double, double, double, double);
};

// the calculations done to determine the new x and y velocities
void Shape::handle_gravity(double timer_speed, double deaccel_amount, double gravity, double stopping_point) {

	if (y_velocity != 0)									// if you're moving
		y_velocity += gravity*timer_speed;	// then keep being affected by gravity

	if (y < stopping_point) {										// if you've fallen through
		y = stopping_point;												// then go back to the 'bottom', (which is different for circs and rects)
		y_velocity = deaccel_amount - y_velocity;			// and bounce back up with less velocity
	}
	else if ((y != stopping_point && y + y_velocity > stopping_point) || y_velocity < 0) {		// if you're moving
		y -= y_velocity * timer_speed + gravity * timer_speed * timer_speed / 2;								// then fall according to physics!
		
		x += x_velocity * timer_speed;																	// move in the x direction
		if ((type == 1 && x < 0) || (type == -1 && x - width < 0)) {		// if you hit the left wall
			x = 0;																												// then go to it
			if (type == -1)									
				x = 0 + width;																							// slightly differently if a circle
			x_velocity = -deaccel_amount * .9 - x_velocity;								// and bounce off the wall with less velocity
		}
		if (x + width > 1) {																						// same for the right wall
			x = 1 - width;																								// except both rects and circs behave the same on this wall
			x_velocity = deaccel_amount * .9 - x_velocity;								// bounce back to the left!
		}
	}
}

// basically the constructor,
// a shape is basically uncounted if it has type 0 (or != 1 or -1)
void Shape::set_shape(signed short a, double b, double c, double d, double e) {
	 type = a;
	 x = b;
	 y = c;
	 width = d;
	 height = e;
}

void Shape::set_x(double a) {
	x = a;
}

void Shape::set_y(double a) {
	y = a;
}

void Shape::set_type(signed short a) {
	type = a;
}

void Shape::set_y_velocity(double a) {
	y_velocity = a;
}

void Shape::set_x_velocity(double a) {
	x_velocity = a;
}

void Shape::set_width(double a) {
	width = a;
}

void Shape::set_height(double a) {
	height = a;
}

void Shape::set_color(double a) {
	color = a;
}
