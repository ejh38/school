/*
 *  shape.cpp
 *  GLUT_test
 *
 *  Created by Zach Sadler on 8/31/12.
 *  Copyright 2012 Zaxcoding. All rights reserved.
 *
 */

class Shape {
	double *x, *y;
	signed short *type;
	
public:
	double get_x() { return *x; }
	double get_y() { return *y; }
	double get_type() { return *type; }
	
	void set_x(double);
	void set_y(double);
	void set_type(signed short);
	Shape();
	Shape(signed short, double, double);
};

Shape::Shape()
{
}

Shape::Shape(signed short a, double b, double c) {
	type = new signed short;
	*type = a;
	x = new double;
	y = new double;
	*x = b;
	*y = c;
}

void Shape::set_x(double a)
{
	*x = a;
}

void Shape::set_y(double a)
{
	*y = a;
}

void Shape::set_type(signed short a)
{
	*type = a;
}

