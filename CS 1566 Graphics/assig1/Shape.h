/*
 *  shape.h
 *  GLUT_test
 *
 *  Created by Zach Sadler on 8/31/12.
 *  Copyright 2012 Zaxcoding. All rights reserved.
 *
 */

class Shape
{
	double x, y;
	signed short type;
	
	public:
		Shape();
		Shape(short a, double b, double c);

	double get_x() { return x; }
	double get_y() { return y; }
	short get_type() { return type; }
	
	protected:
	double x, y;
	short type;		// 1 = rect, -1 = circ
	
};