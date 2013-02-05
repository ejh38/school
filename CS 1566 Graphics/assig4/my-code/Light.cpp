#include <glut/glut.h>

class Light {

  Vector amb;
  Vector diff;
  Vector spec;
  Vector pos;
  Vector dir;
  GLdouble angle;

public:
  Vector get_amb() { return amb; }
  Vector get_diff() { return diff; }
  Vector get_spec() { return spec; }
  Vector get_pos() { return pos; }
  Vector get_dir() { return dir; }
  GLdouble get_angle() { return angle; }


  void set_amb(Vector);
  void set_diff(Vector);
  void set_spec(Vector);
  void set_pos(Vector);
  void set_dir(Vector);
  void set_angle(GLdouble);

} ;

void Light::set_amb(Vector a) {
  amb = a;
}

void Light::set_diff(Vector a) {
  diff = a;
}

void Light::set_spec(Vector a) {
  spec = a;
}

void Light::set_pos(Vector a) {
  pos = a;
}

void Light::set_dir(Vector a) {
  dir = a;
}

void Light::set_angle(GLdouble a) {
  angle = a;
}
