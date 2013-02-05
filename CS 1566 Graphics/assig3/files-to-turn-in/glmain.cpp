/*******************************************************
FILE: glmain.cpp
AUTHOR: Zach Sadler - zps6
DOES: Transform and play with 3d objects.
      Rotate them! Translate! Scale! Spin! So much fun!
PLATFORM: macosx
********************************************************/

//VisS will not let through math.h constants such as M_PI w/out the line below
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glut/glut.h>

#include "Matrix2.cpp"
#include "Matrix3.cpp"
#include "glmain.h"

// default sizes for the shapes
double cyl_height=1, cyl_ray=.5;
double sph_ray=1;
double cone_ray = 1, cone_height = 1;
double torus_r1 = 1.2, torus_r2 = .2;
double axes_size = 2;

// camera
double x_camera = 0, y_camera = 5, z_camera = 30;

// this was all aready here
int crt_render_mode;
int crt_shape, crt_rs, crt_vs;
int crt_transform;
int spin_val = SPIN_DISABLED;

// the shapes I transform
Matrix3 sphere, cone, cylinder, torus, cube, house;
Matrix3 curr;

// tracks the transformations
Matrix2 stack;      // currently unused

// toggle for the normals
short show_normals;

// how much to spin by- adjust this for more or less
float spin_amount = .5;

// some extra credit stuff
short slowmo;


/*********************************
 * main: untouched
************************************/
int main(int argc, char** argv)
{	
  glutInit(&argc, argv);
  glut_setup();
  gl_setup();
  my_setup();

  glutMainLoop();

  return(0);
}

/*********************************
 * glut_setup: mostly untouched
************************************/
void glut_setup (){

  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(700,700);
  glutInitWindowPosition(20,20);
  glutCreateWindow("Zach Sadler - zps6 - Assignment 3");

  /* set up callback functions */
  glutDisplayFunc(my_display);
  glutReshapeFunc(my_reshape);
  glutMouseFunc(my_mouse);
  glutKeyboardFunc(my_keyboard);
  glutKeyboardUpFunc( my_keyboard_up );	
  glutTimerFunc( 200, my_TimeOut, 0 );/* schedule a my_TimeOut call with the ID 0 in 20 seconds from now */
  return;

}


/*********************************
 * glut_setup: untouched
************************************/
void gl_setup(void) {
  // enable depth handling (z-buffer)
  glEnable(GL_DEPTH_TEST);

  // define the background color 
  glClearColor(0,0,0,1);

  glMatrixMode(GL_PROJECTION) ;

  glLoadIdentity() ;

  gluPerspective( 20, 1.0, 15, 100.0);

  glMatrixMode(GL_MODELVIEW) ;

  glLoadIdentity() ;  // init modelview to identity

  return ;

}


/*********************************
 * my_setup: added stuff for the stack matrix,
               and the make_* calls
************************************/
void my_setup(){
  crt_render_mode = GL_POLYGON;//GL_LINE_LOOP;
  crt_shape = HOUSE;
  crt_transform = NONE_MODE;
  crt_rs = 20;
  crt_vs = 10;

  GLdouble identity[16] = { 1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1 };
  stack.set_matrix(identity);
  curr = house;
  curr.set_axes(axes_size);

  make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
  make_sphere(sph_ray,crt_rs,crt_vs);
  make_cone(cone_height, cone_ray, crt_rs, crt_vs);
  make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
  return;

}

/*********************************
 * set_curr: based on crt_shape's value,
             changes the reference for curr
************************************/
void set_curr()
{
  switch (crt_shape) {
    case HOUSE: {
      curr = house;
    }; break;
    case CUBE: {
      curr = cube;
    }; break;
    case TORUS: {
      curr = torus;
    }; break;
    case SPHERE: {
      curr = sphere;
    }; break;
    case CYLINDER: {
      curr = cylinder;
    }; break;
    case CONE: {
      curr = cone;
    }; break;

    default: break;
  }

  return ;
}

/*********************************
 * my_reshape: untouched
************************************/
void my_reshape(int w, int h) {
  // ensure a square view port
  glViewport(0,0,min(w,h),min(w,h)) ;
  return ;

}

/*********************************
 * ugly_hardcode_hack: this is a not very elegant way
                       to handle the cube and house transformations
                       I basically encapsulate them in my Vector type,
                       then multiply by one of my Matrix classes
************************************/
void ugly_hardcode_hack(Matrix2 m) {
  Vector temp;
  if (crt_shape == HOUSE) {
    for (int i = 0; i < 9; i++) {
      temp.set_vector(vertices_house[i][0], vertices_house[i][1], vertices_house[i][2], vertices_house[i][3]);
      temp.multiply(m);
      vertices_house[i][0] = temp.get_x();
      vertices_house[i][1] = temp.get_y();
      vertices_house[i][2] = temp.get_z();
      vertices_house[i][3] = temp.get_w(); 
    }
  }
   if (crt_shape == CUBE) {
    for (int i = 0; i < 8; i++) {
      temp.set_vector(vertices_cube_brute[i][0], vertices_cube_brute[i][1], vertices_cube_brute[i][2], vertices_cube_brute[i][3]);
      temp.multiply(m);
      vertices_cube_brute[i][0] = temp.get_x();
      vertices_cube_brute[i][1] = temp.get_y();
      vertices_cube_brute[i][2] = temp.get_z();
      vertices_cube_brute[i][3] = temp.get_w(); 
    }
  }

  return;
}


/*********************************
 * real_rot_arbitrary_axis_point:
        This is used to do the 'spinning',
        it takes an axis (ax, ay, az)
        and a center point (cx, cy, cz),
        then transforms the verts shape
        accordingly by 'deg' degrees.
************************************/
void real_rot_arbitrary_axis_point(Matrix3 &verts, GLfloat deg, GLfloat ax, GLfloat ay, GLfloat az, GLfloat cx, GLfloat cy, GLfloat cz ) {
  
  // translate to origin
  GLdouble t_vals[16] = { 1, 0, 0, -cx,
                          0, 1, 0, -cy,
                          0, 0, 1, -cz,
                          0, 0, 0, 1    };
  Matrix2 t;
  t.set_matrix(t_vals);
  verts.multiply_all(t);
  verts.multiply_norms(t);
  stack.multiply(t);
  ugly_hardcode_hack(t);


  // normalize the axis vector
  Vector w;
  w.set_vector(ax, ay, az, 1);
  w.normalize();

  GLdouble ux = w.get_x();
  GLdouble uy = w.get_y();
  GLdouble uz = w.get_z();

  // then do the local to world rotation
  GLdouble m_vals[16] = { ux*ux + cos(deg)*(1-ux*ux),       ux*uy*(1-cos(deg)) - uz*sin(deg), uz*ux*(1-cos(deg)) + uy*sin(deg), 0,
                          ux*uy*(1-cos(deg)) + uz*sin(deg), uy*uy + cos(deg)*(1-uy*uy),       uy*uz*(1-cos(deg)) - ux*sin(deg), 0,
                          uz*ux*(1-cos(deg)) - uy*sin(deg), uy*uz*(1-cos(deg)) + ux*sin(deg), uz*uz + cos(deg)*(1-uz*uz),       0,
                          0,                                0,                                0,                                1};
  Matrix2 m;
  m.set_matrix(m_vals);
  verts.multiply_all(m);
  verts.multiply_norms(m);
  stack.multiply(m);
  ugly_hardcode_hack(m);

  // then translate back
  GLdouble ti_vals[16] = { 1, 0, 0, cx,
                           0, 1, 0, cy,
                           0, 0, 1, cz,
                           0, 0, 0, 1  };
  Matrix2 ti;
  ti.set_matrix(ti_vals);
  verts.multiply_all(ti);
  verts.multiply_norms(ti);
  stack.multiply(ti);
  ugly_hardcode_hack(ti);

  return;
}

/*********************************
 * real_rev: takes deg, and x, y, z,
             then calls real_rot_arbitrary_axis_point appropriately
             wrt to x, y, or z
             (does y axis by default)
************************************/
void real_rev(GLfloat deg, GLfloat x, GLfloat y, GLfloat z) {

  int axis_to_use = 2;

  if (x == 1) {
    axis_to_use = 1;
  }
  else if (y == 1) {
    axis_to_use = 2;
  }
  else if (z == 1) {
    axis_to_use = 3;
  }

  real_rot_arbitrary_axis_point(curr, deg, curr.get_axis(axis_to_use).get_x() - curr.get_axis(0).get_x(), 
        curr.get_axis(axis_to_use).get_y() - curr.get_axis(0).get_y(), curr.get_axis(axis_to_use).get_z() - curr.get_axis(0).get_z(), 
        curr.get_axis(0).get_x(), curr.get_axis(0).get_y(), curr.get_axis(0).get_z());

  return;
}

/*********************************
 * real_translation: translates the verts object
                     by x,y,z
************************************/
void real_translation(Matrix3 &verts, GLfloat x, GLfloat y, GLfloat z) {
  GLdouble m_vals[16] = { 1, 0, 0, x,
                          0, 1, 0, y,
                          0, 0, 1, z,
                          0, 0, 0, 1  };
  Matrix2 m;
  m.set_matrix(m_vals);

  verts.multiply_all(m);
  stack.multiply(m);
  verts.multiply_norms(m);
  verts.multiply_axes(m);
  ugly_hardcode_hack(m);

  return;
}


/*********************************
 * real_scaling: scales the verts object
                 by sx,sy,sz
************************************/
void real_scaling(Matrix3 &verts, GLfloat sx, GLfloat sy, GLfloat sz) {
  GLdouble m_vals[16] = { sx, 0,  0,  0,
                          0,  sy, 0,  0,
                          0,  0,  sz, 0,
                          0,  0,  0,  1  };
  Matrix2 m;
  m.set_matrix(m_vals);
  verts.multiply_all(m);
  stack.multiply(m);
  verts.multiply_axes(m);
  ugly_hardcode_hack(m);

  return;
}

/*********************************
 * real_rotation: rotates the verts object
                  'deg' degrees, on either x, y, or z axis
************************************/
void real_rotation(Matrix3 &verts, GLfloat deg, GLfloat x, GLfloat y, GLfloat z) {

  Matrix2 m;

  if (x == 1) {
    GLdouble m_vals[16] = { 1, 0,        0,         0,
                            0, cos(deg), -sin(deg), 0,
                            0, sin(deg), cos(deg),  0,
                            0, 0,        0,         1};
    m.set_matrix(m_vals);
  }
  else if (y == 1) {
     GLdouble m_vals[16] = {  cos(deg),   0, sin(deg), 0,
                              0,          1, 0,        0,
                              -sin(deg),  0, cos(deg), 0,
                              0,          0, 0,        1};
    m.set_matrix(m_vals);
  }
  else if (z == 1) {
     GLdouble m_vals[16] = {  cos(deg), -sin(deg), 0, 0,
                              sin(deg), cos(deg),  0, 0,
                              0,        0,         1, 0,
                              0,        0,         0, 1};
    m.set_matrix(m_vals);
  }

  verts.multiply_all(m);
  verts.multiply_norms(m);
  verts.multiply_axes(m);
  stack.multiply(m);
  ugly_hardcode_hack(m);

  return;
}

/*********************************
 * reset_house: unfortunately, this ugly hack
                is how I have to reset my house
                I just manually enter the original vertices
************************************/
void reset_house()
{
  vertices_house[0][0] = 0;
  vertices_house[0][1] = 2;
  vertices_house[0][2] = 0;
  vertices_house[0][3] = 1;

  vertices_house[1][0] = -1;
  vertices_house[1][1] = 1;
  vertices_house[1][2] = 1;
  vertices_house[1][3] = 1;

  vertices_house[2][0] = 1;
  vertices_house[2][1] = 1;
  vertices_house[2][2] = 1;
  vertices_house[2][3] = 1;                    
                      
  vertices_house[3][0] = 1;                      
  vertices_house[3][1] = 1;                      
  vertices_house[3][2] = -1;                      
  vertices_house[3][3] = 1;

  vertices_house[4][0] = -1;
  vertices_house[4][1] = 1;
  vertices_house[4][2] = -1;
  vertices_house[4][3] = 1;

  vertices_house[5][0] = -1;
  vertices_house[5][1] = -1;
  vertices_house[5][2] = 1;
  vertices_house[5][3] = 1;

  vertices_house[6][0] = 1;
  vertices_house[6][1] = -1;
  vertices_house[6][2] = 1;
  vertices_house[6][3] = 1;

  vertices_house[7][0] = 1;
  vertices_house[7][1] = -1;
  vertices_house[7][2] = -1;
  vertices_house[7][3] = 1;

  vertices_house[8][0] = -1;
  vertices_house[8][1] = -1;
  vertices_house[8][2] = -1;
  vertices_house[8][3] = 1;

  return;
}

/*********************************
 * reset_cube: same as the house
************************************/
void reset_cube()
{
  vertices_cube_brute[0][0] = -1;
  vertices_cube_brute[0][1] = 1;
  vertices_cube_brute[0][2] = 1;
  vertices_cube_brute[0][3] = 1;

  vertices_cube_brute[1][0] = 1;
  vertices_cube_brute[1][1] = 1;
  vertices_cube_brute[1][2] = 1;
  vertices_cube_brute[1][3] = 1;                    
 
  vertices_cube_brute[2][0] = 1;                      
  vertices_cube_brute[2][1] = 1;                      
  vertices_cube_brute[2][2] = -1;                      
  vertices_cube_brute[2][3] = 1;

  vertices_cube_brute[3][0] = -1;
  vertices_cube_brute[3][1] = 1;
  vertices_cube_brute[3][2] = -1;
  vertices_cube_brute[3][3] = 1;

  vertices_cube_brute[4][0] = -1;
  vertices_cube_brute[4][1] = -1;
  vertices_cube_brute[4][2] = 1;
  vertices_cube_brute[4][3] = 1;

  vertices_cube_brute[5][0] = 1;
  vertices_cube_brute[5][1] = -1;
  vertices_cube_brute[5][2] = 1;
  vertices_cube_brute[5][3] = 1;

  vertices_cube_brute[6][0] = 1;
  vertices_cube_brute[6][1] = -1;
  vertices_cube_brute[6][2] = -1;
  vertices_cube_brute[6][3] = 1;

  vertices_cube_brute[7][0] = -1;
  vertices_cube_brute[7][1] = -1;
  vertices_cube_brute[7][2] = -1;
  vertices_cube_brute[7][3] = 1;

  return;
}

/*********************************
 * reset: resets the values, to make things
          as they were in the beginning
************************************/
void reset()
{
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
  x_camera = 0; y_camera = 5; z_camera =30;

  spin_val = 0;

  make_sphere(sph_ray, crt_rs, crt_vs);
  make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
  make_cone(cone_height, cone_ray, crt_rs, crt_vs);
  make_torus(torus_r1, torus_r2, crt_rs, crt_vs);

  set_curr();
  curr.set_axes(axes_size);

  reset_house();
  reset_cube();

}

/*********************************
 * calculate_norms: copied straight from hw2
************************************/
void calculate_norms(Matrix3 &verts, int i, int j, int rs, int vs) {
  
  Vector v1, v2, v3;
  Vector n1, n2;
  Vector norm;

  // start of first (upper left hand) triangle
  v1.set_vector(verts.get_vector(i, j).get_x(), 
                verts.get_vector(i, j).get_y(),
                verts.get_vector(i, j).get_z(),
                verts.get_vector(i, j).get_w());

  v2.set_vector(verts.get_vector((i+1)%rs, j).get_x(), 
                verts.get_vector((i+1)%rs, j).get_y(),
                verts.get_vector((i+1)%rs, j).get_z(),
                verts.get_vector((i+1)%rs, j).get_w());

  v3.set_vector(verts.get_vector((i+1)%rs, (j+1)%vs).get_x(), 
                verts.get_vector((i+1)%rs, (j+1)%vs).get_y(),
                verts.get_vector((i+1)%rs, (j+1)%vs).get_z(),
                verts.get_vector((i+1)%rs, (j+1)%vs).get_w());

  n1 = v2.subtract(v1);
  n2 = v3.subtract(v2);

  norm = n2.cross_product(n1);
  norm.normalize();

  verts.set_face_norm(norm, i, j);

  // start of second (lower right hand) triangle
  v1.set_vector(verts.get_vector((i+1)%rs, (j+1)%vs).get_x(), 
              verts.get_vector((i+1)%rs, (j+1)%vs).get_y(),
              verts.get_vector((i+1)%rs, (j+1)%vs).get_z(),
              verts.get_vector((i+1)%rs, (j+1)%vs).get_w());

  v2.set_vector(verts.get_vector(i, (j+1)%vs).get_x(), 
              verts.get_vector(i, (j+1)%vs).get_y(),
              verts.get_vector(i, (j+1)%vs).get_z(),
              verts.get_vector(i, (j+1)%vs).get_w());

  v3.set_vector(verts.get_vector(i, j).get_x(), 
              verts.get_vector(i, j).get_y(),
              verts.get_vector(i, j).get_z(),
              verts.get_vector(i, j).get_w());

    n1 = v2.subtract(v1);
    n2 = v3.subtract(v2);

    norm = n2.cross_product(n1);
    norm.normalize();

    verts.set_face_norm(norm, (i+rs)%(2*rs), j);
}

/*********************************
 * calculate_vertex_norms: copied straight from hw2
************************************/
void calculate_vertex_norms(Matrix3 &verts, int i, int j, int rs, int vs) {

  Vector v1, v2, v3, v4, v5, v6;
  Vector ans;

  v1 = verts.get_face_norm(i,(j-1)%vs);
  v2 = verts.get_face_norm((i-1+rs)%(2*rs),(j-1)%vs);
  v3 = verts.get_face_norm((i+rs)%(2*rs),(j-1)%vs);
  v4 = verts.get_face_norm((i-1)%(2%rs),j);
  v5 = verts.get_face_norm((i+rs)%(2*rs),j);
  v6 = verts.get_face_norm(i,j);

  ans = v6.plus(v5);
  ans = v6.plus(v4);
  ans = v6.plus(v3);
  ans = v6.plus(v2);
  ans = v6.plus(v1);

  ans.normalize();
  ans = ans.scale(.2);
  ans = verts.get_vector(i,j).subtract(ans);
  verts.set_vertex_norm(ans, i, j);
}


/*********************************
 * my_keyboard: handles all the key input
************************************/
void my_keyboard( unsigned char key, int x, int y ) {
  switch( key ) {
  
  // pick a transform case
  case 'S':
  case 's': {
    crt_transform = REAL_SCALING_MODE;
  }; break;

  case 'T':
  case 't': {
    crt_transform = REAL_TRANSLATION_MODE;
  }; break;

  case 'R':
  case 'r': {
    crt_transform = REAL_ROTATION_MODE;
  }; break;


  // reset
  case 'O':
  case 'o': {
    reset();
    glutPostRedisplay(); 
  }; break;


  // do the actual transform
  case 'y': {
  switch( crt_transform) {
  case REAL_ROTATION_MODE: real_rotation(curr, -.2,0,1,0); break;
  case REAL_TRANSLATION_MODE: real_translation(curr, 0,-.5,0); break;
  case REAL_SCALING_MODE: real_scaling(curr, 1, .9, 1); break;
  }
    glutPostRedisplay(); 
  }; break;
  case 'Y': {
  switch( crt_transform) {
  case REAL_ROTATION_MODE: real_rotation(curr, .2,0,1,0); break;
  case REAL_TRANSLATION_MODE: real_translation(curr, 0,.5,0); break;
  case REAL_SCALING_MODE: real_scaling(curr, 1, 1.1, 1); break;
  }
    glutPostRedisplay(); 
  }; break;

  case 'x': {
  switch( crt_transform) {
  case REAL_ROTATION_MODE: real_rotation(curr, -.2,1,0,0); break;
  case REAL_TRANSLATION_MODE: real_translation(curr, -.5,0,0); break;
  case REAL_SCALING_MODE: real_scaling(curr, .9, 1, 1); break;
  }
    glutPostRedisplay(); 
  }; break;
  case 'X': {
  switch( crt_transform) {
  case REAL_ROTATION_MODE: real_rotation(curr, .2,1,0,0); break;
  case REAL_TRANSLATION_MODE: real_translation(curr, .5,0,0); break;
  case REAL_SCALING_MODE: real_scaling(curr, 1.1, 1, 1); break;
  }
    glutPostRedisplay(); 
  }; break;

  case 'z': {
  switch( crt_transform) {
  case REAL_ROTATION_MODE: real_rotation(curr, -.2,0,0,1); break;
  case REAL_TRANSLATION_MODE: real_translation(curr, 0,0,-.5); break;
  case REAL_SCALING_MODE: real_scaling(curr, 1, 1, .9); break;
  }
    glutPostRedisplay(); 
  }; break;
  case 'Z': {
  switch( crt_transform) {
  case REAL_ROTATION_MODE: real_rotation(curr, .2,0,0,1); break;
  case REAL_TRANSLATION_MODE: real_translation(curr, 0,0,.5); break;
  case REAL_SCALING_MODE: real_scaling(curr, 1, 1, 1.1); break;
  }
    glutPostRedisplay(); 
  }; break;


  // change between shapes
  case '1': {
    crt_shape = CUBE;
    curr = cube;
    curr.set_axes(axes_size);
    reset_cube();
    reset_house();
    glutPostRedisplay();
  }; break;
  case '2': {
    crt_shape = SPHERE;
    curr = sphere;
    curr.set_axes(axes_size);
    reset_cube();
    reset_house();
    glutPostRedisplay();
  }; break;
  case '3':{
    crt_shape = CYLINDER;
    curr = cylinder;
    curr.set_axes(axes_size);
    reset_cube();
    reset_house();
    glutPostRedisplay();
  }; break;
  case '4': {
    crt_shape = CONE;
    curr = cone;
    curr.set_axes(axes_size);
    reset_cube();
    reset_house();
    glutPostRedisplay();
  }; break;
  case '5': {
    crt_shape = TORUS;
    curr = torus;
    curr.set_axes(axes_size);    
    reset_cube();
    reset_house();
    glutPostRedisplay();
  }; break;
  case '6': {
    crt_shape = HOUSE;
    curr = house;
    curr.set_axes(axes_size);
    reset_cube();
    reset_house();
    glutPostRedisplay();
  }; break;

  case '0': {
    slowmo = (slowmo + 1) % 2;
  }; break;


  // my default shape sizes (that I prefer)
  case 'd': {
    cyl_height=3;
    cyl_ray=1;
    sph_ray=2;
    cone_ray = 1.5;
    cone_height = 3;
    torus_r1 = 2;
    torus_r2 = .5;
    crt_rs = 25;
    crt_vs = 25;
    axes_size = 2.5;
    curr.set_axes(axes_size);
    make_sphere(sph_ray, crt_rs, crt_vs);
    make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
    make_cone(cone_height, cone_ray, crt_rs, crt_vs);
    make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
    glutPostRedisplay();
  }


  // the tessellation adjustment code from hw2
  case '=':
  case '+': {
    if (crt_rs < 50)
      crt_rs++;
      make_sphere(sph_ray, crt_rs, crt_vs);
      make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
      make_cone(cone_height, cone_ray, crt_rs, crt_vs);
      make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
      set_curr();
      curr.set_axes(axes_size);
      glutPostRedisplay();
  }; break;
  case '_':
  case '-': {
    if (crt_rs > 3)
      crt_rs--;
      make_sphere(sph_ray, crt_rs, crt_vs);
      make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
      make_cone(cone_height, cone_ray, crt_rs, crt_vs);
      make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
      set_curr();
      curr.set_axes(axes_size);
      glutPostRedisplay();
  }; break;
  case '<':
  case ',': {
    if (crt_vs < 50)
      crt_vs++;
      make_sphere(sph_ray, crt_rs, crt_vs);
      make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
      make_cone(cone_height, cone_ray, crt_rs, crt_vs);
      make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
      set_curr();
      curr.set_axes(axes_size);
      glutPostRedisplay();
  }; break;
  case '>':
  case '.': {
    if (crt_vs > 3) 
      crt_vs--;
      make_sphere(sph_ray, crt_rs, crt_vs);
      make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
      make_cone(cone_height, cone_ray, crt_rs, crt_vs);
      make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
      set_curr();      
      curr.set_axes(axes_size);
      glutPostRedisplay();
  }; break;


  // q is for quit!!!
  case 'q': 
  case 'Q':

    exit(0) ;

    break ;	

  default: break;
  }

  return ;
}

/*********************************
 * my_keyboard_up: if you're not pushing a transform button,
                   then your transform mode is none
************************************/
void my_keyboard_up( unsigned char key, int x, int y ) {
	switch( key ) {
	case 'S':
	case 's': 
	case 'T':
	case 't':
	case 'R':
	case 'r': {
		crt_transform = NONE_MODE; break;
		}
	}
  return;
}


/*********************************
 * my_mouse: largely untouched, except for the show_normals addition
************************************/
void my_mouse(int button, int state, int mousex, int mousey) {
  switch( button ) {	
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ) {
 	 if(spin_val == SPIN_ENABLED) spin_val = SPIN_DISABLED;
	  else spin_val = SPIN_ENABLED;
	  glutPostRedisplay();
    }

    if( state == GLUT_UP ) {
    }
    break ;

  case GLUT_RIGHT_BUTTON:
    if( state == GLUT_DOWN ) {
	if(crt_render_mode == GL_LINE_LOOP) crt_render_mode = GL_POLYGON;
	else crt_render_mode = GL_LINE_LOOP;
      show_normals = (show_normals + 1) % 2;

      glutPostRedisplay();
    }
    if( state == GLUT_UP ) {
    }
    break ;
  }
  
  return ;

}

/*********************************
 * my_triangle: copied from hw2
************************************/
void my_triangle(Matrix3 verts, int i, int j, int rs, int vs) {
  
  // start of triangle 1
  glBegin(crt_render_mode); 
  {
    glColor3fv(colors[MAGENTA]);

    Vector v1, v2, v3;
    v1.set_vector(verts.get_vector(i, j).get_x(), 
                  verts.get_vector(i, j).get_y(),
                  verts.get_vector(i, j).get_z(),
                  verts.get_vector(i, j).get_w());

    v2.set_vector(verts.get_vector((i+1)%rs, j).get_x(), 
                  verts.get_vector((i+1)%rs, j).get_y(),
                  verts.get_vector((i+1)%rs, j).get_z(),
                  verts.get_vector((i+1)%rs, j).get_w());

    v3.set_vector(verts.get_vector((i+1)%rs, (j+1)%vs).get_x(), 
                  verts.get_vector((i+1)%rs, (j+1)%vs).get_y(),
                  verts.get_vector((i+1)%rs, (j+1)%vs).get_z(),
                  verts.get_vector((i+1)%rs, (j+1)%vs).get_w());

    glVertex4f(v1.get_x(), v1.get_y(), v1.get_z(), v1.get_w());
    glVertex4f(v2.get_x(), v2.get_y(), v2.get_z(), v2.get_w());
    glVertex4f(v3.get_x(), v3.get_y(), v3.get_z(), v3.get_w());
  }
  glEnd();

  // start of triangle two
  glBegin(crt_render_mode);
  {
    glColor3fv(colors[WHITE]);
    Vector v1, v2, v3;
    v1.set_vector(verts.get_vector((i+1)%rs, (j+1)%vs).get_x(), 
                verts.get_vector((i+1)%rs, (j+1)%vs).get_y(),
                verts.get_vector((i+1)%rs, (j+1)%vs).get_z(),
                verts.get_vector((i+1)%rs, (j+1)%vs).get_w());

    v2.set_vector(verts.get_vector(i, (j+1)%vs).get_x(), 
                verts.get_vector(i, (j+1)%vs).get_y(),
                verts.get_vector(i, (j+1)%vs).get_z(),
                verts.get_vector(i, (j+1)%vs).get_w());

    v3.set_vector(verts.get_vector(i, j).get_x(), 
                verts.get_vector(i, j).get_y(),
                verts.get_vector(i, j).get_z(),
                verts.get_vector(i, j).get_w());

    glVertex4f(v1.get_x(), v1.get_y(), v1.get_z(), v1.get_w());
    glVertex4f(v2.get_x(), v2.get_y(), v2.get_z(), v2.get_w());
    glVertex4f(v3.get_x(), v3.get_y(), v3.get_z(), v3.get_w());
  }
  glEnd();

  // start of drawing the normals
  if (show_normals) {
    Vector v1;
    v1.set_vector(verts.get_vector(i, j).get_x(), 
                verts.get_vector(i, j).get_y(),
                verts.get_vector(i, j).get_z(),
                verts.get_vector(i, j).get_w());

    glBegin(GL_LINES);
    {
      glColor3fv(colors[CYAN]);
      glVertex4f(v1.get_x(), v1.get_y(), v1.get_z(), v1.get_w());
      glVertex4f(verts.get_vertex_norm(i,j).get_x(), verts.get_vertex_norm(i,j).get_y(), verts.get_vertex_norm(i,j).get_z(), verts.get_vertex_norm(i,j).get_w());
    }
    glEnd();
  }
  
}


/*********************************
 * draw_quad: untouched
************************************/
void draw_quad(GLfloat vertices[][4], int iv1, int iv2, int iv3, int iv4, int ic) {
  glBegin(crt_render_mode); 
  {
    glColor3fv(colors[ic]);
    /*note the explicit use of homogeneous coords below: glVertex4f*/
    glVertex4fv(vertices[iv1]);
    glVertex4fv(vertices[iv2]);
    glVertex4fv(vertices[iv3]);
    glVertex4fv(vertices[iv4]);
  }
  glEnd();
}

/*********************************
 * draw_param_quad: untouched
************************************/
void draw_param_quad(GLfloat vertices[][50][4], int line, int col, int ic) {
  glBegin(crt_render_mode); 
  {
    glColor3fv(colors[ic]);
    /*note the explicit use of homogeneous coords below: glVertex4f*/
    glVertex4fv(vertices[line][col]);
    glVertex4fv(vertices[line+1][col]);
    glVertex4fv(vertices[line+1][col+1]);
    glVertex4fv(vertices[line][col+1]);
  }
  glEnd();
}


/*********************************
 * draw_triangle: untouched
************************************/
void draw_triangle(GLfloat vertices[][4], int iv1, int iv2, int iv3, int ic) {
  glBegin(crt_render_mode); 
  {
    glColor3fv(colors[ic]);
    /*note the explicit use of homogeneous coords below: glVertex4f*/
    glVertex4fv(vertices[iv1]);
    glVertex4fv(vertices[iv2]);
    glVertex4fv(vertices[iv3]);
  }
  glEnd();
}


/*********************************
 * draw_house: untouched
************************************/
void draw_house()
{
  draw_triangle(vertices_house,0,1,2,RED);
  draw_triangle(vertices_house,0,2,3,GREEN);
  draw_triangle(vertices_house,0,3,4,WHITE);
  draw_triangle(vertices_house,0,4,1,GREY);


  draw_quad(vertices_house,2,1,5,6, BLUE);
  draw_triangle(vertices_house,2,6,3, CYAN);
  draw_triangle(vertices_house,3,6,7, CYAN);
  draw_triangle(vertices_house,3,7,8, YELLOW);
  draw_triangle(vertices_house,8,3,4, YELLOW);
  draw_triangle(vertices_house,4,8,1, MAGENTA);
  draw_triangle(vertices_house,1,8,5, MAGENTA);

}

/*********************************
 * draw_cube_brute: copied from hw2
************************************/
void draw_cube_brute()
{
  draw_triangle(vertices_cube_brute, 7,6,4,RED);
  draw_triangle(vertices_cube_brute, 6,5,4,RED);
  draw_triangle(vertices_cube_brute, 3,2,1,WHITE);
  draw_triangle(vertices_cube_brute, 0,3,1,WHITE);
  draw_triangle(vertices_cube_brute, 4,5,1,BLUE);
  draw_triangle(vertices_cube_brute, 0,4,1,BLUE);
  draw_triangle(vertices_cube_brute, 5,6,2,CYAN);
  draw_triangle(vertices_cube_brute, 1,5,2,CYAN);
  draw_triangle(vertices_cube_brute, 3,2,6,YELLOW);
  draw_triangle(vertices_cube_brute, 7,3,6,YELLOW);
  draw_triangle(vertices_cube_brute, 0,3,7,MAGENTA);
  draw_triangle(vertices_cube_brute, 4,0,7,MAGENTA);
}

/*********************************
 * draw_cone: Calls my_triangle with the correct parameters.
************************************/
void draw_cone(int rs, int vs)
{
  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      my_triangle(curr, j, i, rs, vs);
      if (slowmo) {   
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
      }
    }
  }
}

/*********************************
 * draw_torus: Calls my_triangle with the correct parameters.
************************************/
void draw_torus(int rs, int vs)
{
  for (int i = 0; i < vs; i++) {
    for (int j = 0; j < rs; j++) {
      my_triangle(curr, j, i, rs, vs);
      if (slowmo) {   
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
      }
    }
  }
}

/*********************************
 * draw_cylinder: Calls my_triangle with the correct parameters.
************************************/
void draw_cylinder(int rs, int vs)
{
  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      my_triangle(curr, j, i, rs, vs);
      if (slowmo) {   
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
      }
    }
  }
}

/*********************************
 * draw_sphere: Calls my_triangle with the correct parameters.
************************************/
void draw_sphere(int rs, int vs)
{
  for (int i = 0; i <= vs; i++) {
    for (int j = 0; j < rs; j++) {
      my_triangle(curr, j, i, rs + 1, vs + 1);
      if (slowmo) {   
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
        glutSwapBuffers();
      }
    }
  }
}

/*********************************
 * draw_local_axes: copied off of draw_axes
************************************/
void draw_local_axes() {
  glLineWidth( 5.5 );
    glBegin(GL_LINES); 
  {
    glColor3fv(colors[1]);
    glVertex4f(curr.get_axis(0).get_x(), curr.get_axis(0).get_y(), curr.get_axis(0).get_z(), curr.get_axis(0).get_w());
    glVertex4f(curr.get_axis(1).get_x(), curr.get_axis(1).get_y(), curr.get_axis(1).get_z(), curr.get_axis(1).get_w());

    glColor3fv(colors[4]);
    glVertex4f(curr.get_axis(0).get_x(), curr.get_axis(0).get_y(), curr.get_axis(0).get_z(), curr.get_axis(0).get_w());
    glVertex4f(curr.get_axis(2).get_x(), curr.get_axis(2).get_y(), curr.get_axis(2).get_z(), curr.get_axis(2).get_w());

    glColor3fv(colors[6]);
    glVertex4f(curr.get_axis(0).get_x(), curr.get_axis(0).get_y(), curr.get_axis(0).get_z(), curr.get_axis(0).get_w());
    glVertex4f(curr.get_axis(3).get_x(), curr.get_axis(3).get_y(), curr.get_axis(3).get_z(), curr.get_axis(3).get_w());
  }
  glEnd();
  glLineWidth( 1.0 );
}

/*********************************
 * draw_axes: untouched, except for changing the line width
************************************/
void draw_axes( void ) {
    glLineWidth( 3.0 );
    glBegin(GL_LINES); 
  {
    glColor3fv(colors[1]);
    glVertex4fv(vertices_axes[0]);
    glVertex4fv(vertices_axes[1]);

    glColor3fv(colors[4]);
    glVertex4fv(vertices_axes[0]);
    glVertex4fv(vertices_axes[2]);

    glColor3fv(colors[6]);
    glVertex4fv(vertices_axes[0]);
    glVertex4fv(vertices_axes[3]);
  }
	glEnd();
	glLineWidth( 1.0 );

}

/*********************************
 * draw_object: Simply added the other shapes.
************************************/
void draw_object(int shape) {

  switch(shape){
  case HOUSE: draw_house(); break;
  case CUBE: draw_cube_brute(); break; 
  case CYLINDER: draw_cylinder(crt_rs, crt_vs);  break;
  case CONE: draw_cone(crt_rs, crt_vs); break;
  case SPHERE: draw_sphere(crt_rs, crt_vs);  break;
  case TORUS: draw_torus(crt_rs, crt_vs) ; break;

  default: break;
  }

}


/*********************************
 * my_display: just added draw_local_axes
************************************/
void my_display() {

  // clear all pixels, reset depth 
  glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );
  
   // init to identity 

   glLoadIdentity() ;

   gluLookAt(x_camera, y_camera, z_camera,  // x,y,z coord of the camera 
	    0.0, 0.0, 0.0,  // x,y,z LookAt
	    0.0, 1.0, 0.0); // the direction of Up (default is y-axis)

  draw_axes();
  draw_local_axes();


   draw_object(crt_shape);

  // this buffer is ready

  glutSwapBuffers();

}

/*********************************
 * my_TimeOut: to adjust the spinning in real_rev,
               just play with calls to real_rev
************************************/
void my_TimeOut(int id) {
  /* spin counter-clockwise*/
  /* schedule next timer event, 0.2 secs from now */ 
  if(spin_val == SPIN_ENABLED){
    if (crt_shape == HOUSE || crt_shape == CUBE) {
      real_rev(spin_amount,0,1,0);   // for some reason, these spin CW unless I do this
    }
    else {
      real_rev(-spin_amount,0,1,0);  // spin wrt the y axis (0,1,0)
    }
	glutPostRedisplay();
	
  };
  glutTimerFunc(200, my_TimeOut, 0);

  return ;
}


/*********************************
 * my_idle: untouched
************************************/
void my_idle(void) {
}


/*********************************
 * make_cone: copied from hw2
************************************/
void make_cone(double height, double ray, int rs, int vs)
{
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(1, 0, 0, 1);

  int i, j;

  for (i = 0; i < vs; i++) {
    for (j = 0; j < rs; j++) {
      cone.set_vector(vstart, j, i);
    }
  }

  double h, phi, r;

  for (i = 0, h = -height/2; i < vs; i++, h += height/vs) {
    for (j = 0, phi = -M_PI; j < rs; j++, phi += (2*M_PI)/rs) {
      r = ray*(height - h)/height;
  
      // this snippet gives the top of the cone
      if (i == vs-1) {
        r = 0;
        h = height;
      }
      GLdouble m_vals[16] = {
        r*cos(phi),   0,      sin(phi),   0,
        0,            1,      0,          h,
        -r*sin(phi),  0,      cos(phi),   0,
        0,            0,      0,          1};

      m.set_matrix(m_vals);
      cone.multiply(m, j, i);
    }
  }

  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_norms(cone, j, i, rs, vs);
    }
  }

  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_vertex_norms(cone, j, i, rs, vs);
    }
  }
}


/*********************************
 * make_torus: copied from hw2
************************************/
void make_torus(double r1, double r2, int rs, int vs)
{
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(1, 0, 0, 1);

  int i, j;

  for (i = 0; i < vs; i++) {
    for (j = 0; j < rs; j++) {
      torus.set_vector(vstart, j, i);
    }
  }

  double phi, theta;

  for (i = 0, phi = 0; i < vs; i++, phi += 2*M_PI/vs) {
    for (j = 0, theta = 0; j < rs; j++, theta += 2*M_PI/rs) {
      
      GLdouble m_vals[16] = {
        r2*cos(phi)*cos(theta),  -cos(theta)*sin(theta), sin(phi),   r1*cos(phi),
        r2*sin(theta),            cos(theta),            0,          0,
        -r2*sin(phi)*cos(theta),  sin(phi)*sin(theta),   cos(phi),  -r1*sin(phi),
        0,                        0,                     0,          1};

      m.set_matrix(m_vals);
      torus.multiply(m, j, i);
    }
  }

  for (int i = 0; i < vs; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_norms(torus, j, i, rs, vs);
    }
  }
  for (int i = 0; i < vs; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_vertex_norms(torus, j, i, rs, vs);
    }
  }
}

/*********************************
 * make_cylinder: copied from hw2
************************************/
void make_cylinder(double height, double ray, int rs, int vs) {
  
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(1, 0, 0, 1);

  int i, j;

  // populate our matrix with the starting vector
  for (i = 0; i < vs; i++) {
    for (j = 0; j < rs; j++) {
      cylinder.set_vector(vstart, j, i);
    }
  }

  double h, phi;

  // then multiply by our transformation matrix
  for (i = 0, h = -height/2; i < vs; i++, h += height/vs) {
    for (j = 0, phi = -M_PI; j < rs; j++, phi += (2*M_PI)/rs) {
      
      GLdouble m_vals[16] = {
        ray*cos(phi),  0,      sin(phi),   0,
        ray*0,         1,      0,          h,
        -ray*sin(phi), 0,      cos(phi),   0,
        0,             0,      0,          1};

      m.set_matrix(m_vals);
      cylinder.multiply(m, j, i);
    }
  }

 // generate face norms
  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_norms(cylinder, j, i, rs, vs);
    }
  }

  // generate vertex norms
  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_vertex_norms(cylinder, j, i, rs, vs);
    }
  }

}

/*********************************
 * make_sphere: copied from hw2
************************************/
void make_sphere( double ray, int rs, int vs ) {
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(0, -1, 0, 1);

  int i, j;

  for (i = 0; i <= vs; i++) {
    for (j = 0; j <= rs; j++) {
      sphere.set_vector(vstart, j, i);
    }
  }

  GLdouble phi, theta;

  for (i = 0, phi = 0; i <= vs; i++, phi += 2*M_PI/vs) {
    for (j = 0, theta = 0; j <= rs; j++, theta += M_PI/rs) {
      
      GLdouble m_vals[16] = {
        cos(phi)*cos(theta),  -ray*cos(phi)*sin(theta),   sin(phi), 0,
        sin(theta),            ray*cos(theta),            0,        0,
        -sin(phi)*cos(theta),  ray*sin(phi)*sin(theta),   cos(phi), 0,
        0,                     0,                         0,        1};

      m.set_matrix(m_vals);
      sphere.multiply(m, j, i);
    }
  }

  for (i = 0; i <= vs; i++) {
    for (j = 0; j < rs; j++) {
      calculate_norms(sphere, j, i, rs + 1, vs + 1);
    }
  }

  for (i = 0; i <= vs; i++) {
    for (j = 0; j < rs; j++) {
      calculate_vertex_norms(sphere, j, i, rs + 1, vs + 1);
    }
  }
}
