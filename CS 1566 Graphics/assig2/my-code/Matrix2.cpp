/*******************************************************
FILE: Matrix2.cpp
AUTHOR: Zach Sadler - zps6
DOES: Acts as a 4x4 matrix data structure
********************************************************/
#include <glut/glut.h>

class Matrix2 {

	GLdouble values[16];

public:
	GLdouble get_value(int i, int j) { return values[i*4 + j]; }
	GLdouble get(int i) { return values[i]; }

	void multiply(Matrix2);
	void set_matrix(GLdouble []);
	void print();
} ;

void Matrix2::set_matrix(GLdouble vals[16]) {
	for (int i = 0; i < 16; i++) {
		values[i] = vals[i];
	}
}

void Matrix2::multiply(Matrix2 left) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			values[i*4 + j] = left.values[i*4]*values[j];
			for (int k = 1; k < 4; k++) {
				values[i*4 + j] += left.values[i*4 + k]*values[k*4 + j];
			}
		}
	}
}

void Matrix2::print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%f ", values[i*4 + j]);
		}
		printf("\n");
	}
}