/*******************************************************
FILE: Vector.cpp
AUTHOR: Zach Sadler - zps6
DOES: A pretty simple 4x1 vector class, that has some support
			for vector operations.
********************************************************/
				
class Vector {

	GLdouble x, y, z, w;

public:
	GLdouble get_x() { return x; }
	GLdouble get_y() { return y; }
	GLdouble get_z() { return z; }
	GLdouble get_w() { return w; }

	// the pseudo-constructor
	void set_vector(GLdouble, GLdouble, GLdouble, GLdouble);
	
	// operations
	void dot_product(Vector);
	void dot_product_2(GLdouble, GLdouble, GLdouble, GLdouble);
	void multiply(Matrix2);
	void normalize();

	// helpful for debugging
	void print();

	// more operations
	Vector cross_product(Vector);
	Vector subtract(Vector);
	Vector plus(Vector);
	Vector scale(GLdouble);

} ;

void Vector::set_vector(GLdouble a, GLdouble b, GLdouble c, GLdouble d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

void Vector::dot_product(Vector left) {
	x *= left.get_x();
	y *= left.get_y();
	z *= left.get_z();
	w *= left.get_w();
}

void Vector::dot_product_2(GLdouble a, GLdouble b, GLdouble c, GLdouble d) {
	x *= a;
	y *= b;
	z *= c;
	w *= d;
}

void Vector::multiply(Matrix2 left) {
	GLdouble oldX = x, oldY = y, oldZ = z, oldW = w;

	x = left.get(0)*oldX + left.get(1)*oldY + left.get(2)*oldZ + left.get(3)*oldW;
	y = left.get(4)*oldX + left.get(5)*oldY + left.get(6)*oldZ + left.get(7)*oldW;
	z = left.get(8)*oldX + left.get(9)*oldY + left.get(10)*oldZ + left.get(11)*oldW;
	w = left.get(12)*oldX + left.get(13)*oldY + left.get(14)*oldZ + left.get(15)*oldW;
}

Vector Vector::cross_product(Vector right) {
	GLdouble newX, newY, newZ;

	newX = y*right.get_z() - z*right.get_y();
	newY = z*right.get_x() - x*right.get_z();
	newZ = x*right.get_y() - y*right.get_x();

	Vector ans;

	ans.set_vector(newX, newY, newZ, 1);

	return ans;
}

	Vector Vector::subtract(Vector right) {
	GLdouble newX = x, newY = y, newZ = z, newW = w;

		newX -= right.get_x();
		newY -= right.get_y();
		newZ -= right.get_z();
		newW -= right.get_w();

		Vector ans;

		ans.set_vector(newX, newY, newZ, newW);

		return ans;
	}

	Vector Vector::plus(Vector right) {
		GLdouble newX = x, newY = y, newZ = z, newW = w;

		newX += right.get_x();
		newY += right.get_y();
		newZ += right.get_z();
		newW += right.get_w();

		Vector ans;

		ans.set_vector(newX, newY, newZ, newW);

		return ans;
	}
	
	Vector Vector::scale(GLdouble scalar) {
		GLdouble newX = x, newY = y, newZ = z, newW = w;

		newX *= scalar;
		newY *= scalar;
		newZ *= scalar;
		newW *= scalar;

		Vector ans;

		ans.set_vector(newX, newY, newZ, newW);

		return ans;
	}

	void Vector::normalize() {
		GLdouble norm = sqrt(x*x + y*y + z*z);

		if (norm != 0) {
			x /= norm;
			y /= norm;
			z /= norm;
		}
	}

	void Vector::print() {
		printf("x = %f, y = %f, z = %f, w = %f\n", x, y, z, w);
	}
