/*******************************************************
FILE: Matrix3.cpp
AUTHOR: Zach Sadler - zps6
DOES: Added a little functionality for this hw, but
			Mostly the same as the last hw.
********************************************************/

#include <glut/glut.h>
#include "Vector.cpp"

class Matrix3 {

	Vector values[50][50];
	Vector face_norms[50][50];			// there are twice as many face norms as vertices
	Vector vertex_norms[50][50];
	Vector axes[4];

public:
	Vector get_vector(int i, int j) { return values[i][j]; }
	Vector get_face_norm(int i, int j) { return face_norms[i][j]; }
	Vector get_vertex_norm(int i, int j) { return vertex_norms[i][j]; }
	Vector get_axis(int i) { return axes[i]; }

	// to multiply a 4x4 times one of your vectors
	// basically a shortcut for Matrix3.set_vector(Matrix3.get_vector().multiply())
	void multiply(Matrix2, int, int);
	void multiply_all(Matrix2);
	void set_vector(Vector, int, int);
	void set_face_norm(Vector, int, int);
	void set_vertex_norm(Vector, int, int);
	void print(int, int);

	void set_axes(GLdouble);
	void set_axis(int, Vector);
	void multiply_axes(Matrix2);
	void multiply_norms(Matrix2);
} ;

void Matrix3::set_axis(int i, Vector newV) {
	axes[i] = newV;
}

void Matrix3::set_axes(GLdouble size) {
	Vector v0, v1, v2, v3;

	v0.set_vector(0,0,0,1);
	axes[0] = v0;
	v1.set_vector(size,0,0,1);
	axes[1] = v1;
	v2.set_vector(0,size,0,1);
	axes[2] = v2;
	v3.set_vector(0,0,size,1);
	axes[3] = v3;
}

void Matrix3::set_face_norm(Vector a, int i, int j) {
	face_norms[i][j] = a;
}

void Matrix3::set_vertex_norm(Vector a, int i, int j) {
	vertex_norms[i][j] = a;
}

void Matrix3::set_vector(Vector a, int i, int j) {
	values[i][j] = a;
}

void Matrix3::multiply(Matrix2 left, int i, int j) {
	values[i][j].multiply(left);
}

void Matrix3::multiply_axes(Matrix2 left) {
	for (int i = 0; i < 4; i++) {
		axes[i].multiply(left);
	}
}

void Matrix3::multiply_norms(Matrix2 left) {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			face_norms[i][j].multiply(left);
			vertex_norms[i][j].multiply(left);
		}
	}
}

void Matrix3::multiply_all(Matrix2 left) {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			values[i][j].multiply(left);
		}
	}
}

void Matrix3::print(int i, int j) {
	printf("%f\n%f\n%f\n%f\n", values[i][j].get_x(), 
			values[i][j].get_y(), values[i][j].get_z(), values[i][j].get_w());
}
