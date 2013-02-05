#include <glut/glut.h>

class Camera {

  Vector position;
  Vector lookAt;
  Vector up;
  Vector dir;

public:
  Vector get_position() { return position; }
  Vector get_lookAt() { return lookAt; }
  Vector get_up() { return up; }
  Vector get_dir() { return dir; }

  void set_position(Vector);
  void set_lookAt(Vector);
  void set_up(Vector);
  void set_dir(Vector);

} ;

void Camera::set_position(Vector a) {
  position = a;
}

void Camera::set_lookAt(Vector a) {
  lookAt = a;
}

void Camera::set_up(Vector a) {
  up = a;
}

void Camera::set_dir(Vector a) {
  dir = a;
}
