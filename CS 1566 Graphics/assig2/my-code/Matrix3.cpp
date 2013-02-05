/*******************************************************
FILE: Matrix3.cpp
AUTHOR: Zach Sadler - zps6
DOES: Acts effectively as the 'Shape' class did in the last assignment.
			It's the data structure that holds the shapes' vertices,
			face normals, and vertex normals.
********************************************************/

#include <glut/glut.h>
#include "Vector.cpp"

class Matrix3 {

	Vector values[50][50];
	Vector face_norms[100][50];			// there are twice as many face norms as vertices
	Vector vertex_norms[50][50];

public:
	Vector get_vector(int i, int j) { return values[i][j]; }
	Vector get_face_norm(int i, int j) { return face_norms[i][j]; }
	Vector get_vertex_norm(int i, int j) { return vertex_norms[i][j]; }

	// to multiply a 4x4 times one of your vectors
	// basically a shortcut for Matrix3.set_vector(Matrix3.get_vector().multiply())
	void multiply(Matrix2, int, int);
	
	void set_vector(Vector, int, int);
	void set_face_norm(Vector, int, int);
	void set_vertex_norm(Vector, int, int);
	void print(int, int);
} ;

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

void Matrix3::print(int i, int j) {
	printf("%f\n%f\n%f\n%f\n", values[i][j].get_x(), 
			values[i][j].get_y(), values[i][j].get_z(), values[i][j].get_w());
}
