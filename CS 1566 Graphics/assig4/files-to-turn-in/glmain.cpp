/*******************************************************
FILE: glmain.cpp
AUTHOR: Zach Sadler - zps6
DOES: Load scene files (somewhat correctly)
      and then move the camera around (hopefully correctly)
PLATFORM: macosx
********************************************************/

//VisS will not let through math.h constants such as M_PI w/out the line below
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <glut/glut.h>

#include "Matrix2.cpp"
#include "Matrix3.cpp"
#include "glmain.h"

typedef struct _LITE{
  GLfloat amb[4];
  GLfloat diff[4];
  GLfloat spec[4];
  GLfloat pos[4];
  GLfloat dir[3];
  GLfloat angle;
}LITE;



// default sizes for the shapes
double cyl_height=.3, cyl_ray=.8;
double sph_ray=.5;
double cone_ray = .5, cone_height = .6;
double torus_r1 = .4, torus_r2 = .2;
double axes_size = 2;

// camera
double x_camera = 0, y_camera = 5, z_camera = 30;

// this was all aready here
int crt_render_mode;
int crt_shape, crt_rs, crt_vs;
int crt_transform;
int spin_val = SPIN_DISABLED;

// the shapes I transform
Matrix3 shapes[NUM_OBJECTS];
OBJECT cubes[NUM_OBJECTS];
LITE my_lights[MAX_LIGHTS];

CAM my_cam;

int num_objects;
int num_cubes;
int  num_lights;
int shapes_pointer;

Matrix3 sphere, cone, cylinder, torus, cube, house;
Matrix3 curr;

Matrix3 temp;


GLdouble R[4][4], T[4][4], S[4][4], RT[4][4];

// camera lens stuff
GLfloat left = -10, right = 10, bottom = -10, top = 10, near = 1, far = 30;
GLfloat height_angle = 40, aspect_ratio = 1.0;
// tracks the transformations
Matrix2 stack;      // currently unused

int ortho = 0;

// toggle for the normals
short show_normals = 0;

// how much to spin by- adjust this for more or less
float spin_amount = .5;

// some extra credit stuff
short slowmo = 0;

/*********************************
 * main: untouched
************************************/
int main(int argc, char** argv)
{	
  setbuf(stdout, NULL);   /* for writing to stdout asap */
  glutInit(&argc, argv);
  glut_setup();
  gl_setup();
  my_setup(argc, argv);  
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

  return;

}


void gl_setup(void) {

  // enable depth handling (z-buffer)
  glEnable(GL_DEPTH_TEST);

  // enable auto normalize
  glEnable(GL_NORMALIZE);

  // define the background color 
  glClearColor(0,0,0,1);

  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  gluPerspective(height_angle, aspect_ratio, near, far);
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;  // init modelview to identity

  // toggle to smooth shading (instead of flat)
  glShadeModel(GL_SMOOTH); 
  //lighting_setup();


  return ;
}


/*********************************
 * my_setup: added stuff for the stack matrix,
               and the make_* calls
************************************/
void my_setup(int argc, char **argv){
  num_objects = num_lights = 0;

  crt_render_mode = GL_POLYGON;//GL_LINE_LOOP;
  crt_transform = NONE_MODE;
  crt_rs = 20;
  crt_vs = 20;

  GLdouble identity[16] = { 1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1 };
  stack.set_matrix(identity);
  curr.set_axes(axes_size);

  make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
  make_sphere(sph_ray,crt_rs,crt_vs);
  make_cone(cone_height, cone_ray, crt_rs, crt_vs);
  make_torus(torus_r1, torus_r2, crt_rs, crt_vs);

  read_spec(argv[1]);
  return;

}

Vector parse_floats(char *buffer, Vector vect) {
  char *ps;
  int nums[4];

  ps = strtok(buffer, " ");
  for (int i = 0; ps; i++) {
    nums[i] = atof(ps);
    ps = strtok(NULL, " ");
    //printf("read %f ",nums[i]);
  }

  vect.set_vector(nums[0], nums[1], nums[2], nums[3]);
  return vect;
}

void parse_floats_old(char *buffer, GLfloat nums[]) {
  int i;
  char *ps;

  ps = strtok(buffer, " ");
  for (i=0; ps; i++) {
    nums[i] = atof(ps);
    ps = strtok(NULL, " ");
    //printf("read %f ",nums[i]);
  }
}




void parse_cube(char *buffer){
  OBJECT *po;
  char *pshape, *pshine, *pemi, *pamb, *pdiff, *pspec, *ptranslate, *pscale, *protate;

  po = &cubes[num_cubes++];

  pshape  = strtok(buffer, " ");
  printf("pshape is %s\n",pshape);

  ptranslate    = strtok(NULL, "()");  strtok(NULL, "()");
  pscale        = strtok(NULL, "()");  strtok(NULL, "()"); 
  protate       = strtok(NULL, "()");  strtok(NULL, "()");  

  pshine  = strtok(NULL, "()");strtok(NULL, "()");
  printf("pshine is %s\n",pshine);
 
  pemi    = strtok(NULL, "()");  strtok(NULL, "()"); 
  pamb    = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdiff   = strtok(NULL, "()");  strtok(NULL, "()"); 
  pspec   = strtok(NULL, "()");  strtok(NULL, "()"); 


  po->sid  = atoi(pshape);
  po->shine = atof(pshine);

  parse_floats_old(ptranslate, po->translate);
  parse_floats_old(pscale, po->scale);
  parse_floats_old(protate, po->rotate);

  parse_floats_old(pemi, po->emi);
  parse_floats_old(pamb, po->amb);
  parse_floats_old(pdiff, po->diff);
  parse_floats_old(pspec, po->spec);


  make_cube_smart(po, 1);
  
  // scale, rotate, translate using your real tranformations from assignment 3 depending on input from spec file
  
  real_scaling_cube(po, po->scale[0], po->scale[1], po->scale[2]);  
  real_rotation_cube(po, po->rotate[0], 1, 0, 0);
  real_rotation_cube(po, po->rotate[1], 0, 1, 0);
  real_rotation_cube(po, po->rotate[2], 0, 0, 1);
  real_translation_cube(po, po->translate[0], po->translate[1], po->translate[2]);
  
  printf("read cube #%d\n", num_cubes);
}




void parse_obj(char *buffer){

  char *pshape, *pshine, *pemi, *pamb, *pdiff, *pspec, *ptranslate, *pscale, *protate;

  pshape  = strtok(buffer, " ");
  printf("pshape is %s\n",pshape);

  ptranslate    = strtok(NULL, "()");  strtok(NULL, "()");
  pscale        = strtok(NULL, "()");  strtok(NULL, "()"); 
  protate       = strtok(NULL, "()");  strtok(NULL, "()");  

  pshine  = strtok(NULL, "()");strtok(NULL, "()");
  printf("pshine is %s\n",pshine);
 
  pemi    = strtok(NULL, "()");  strtok(NULL, "()"); 
  pamb    = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdiff   = strtok(NULL, "()");  strtok(NULL, "()"); 
  pspec   = strtok(NULL, "()");  strtok(NULL, "()"); 

  curr.set_sid(atoi(pshape));
  curr.set_shine(atof(pshine));

  temp.set_translate(parse_floats(ptranslate, temp.get_translate()));
  temp.set_scale(parse_floats(pscale, temp.get_scale()));
  temp.set_rotate(parse_floats(protate, temp.get_rotate()));

  // use switch to create your objects, cube given as example
  printf("curr.get_shape() is %d\n", curr.get_shape());
  int shape_id = curr.get_shape();
  switch (curr.get_shape()){
  case 2: //house
    //make_house
    break;
  case SPHERE:
    make_sphere(sph_ray, crt_rs, crt_vs);
    curr = sphere;
    break;
  case CYLINDER:
    make_cylinder(cyl_ray, cyl_height, crt_rs, crt_vs);
    curr = cylinder;
    break;
  case CONE:
    make_cone(cone_ray, cone_height, crt_rs, crt_vs);
    curr = cone;
    break;
  case TORUS:
    make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
    curr = torus;
    break;

  }
  
  curr.set_sid(shape_id);
  curr.set_emi(parse_floats(pemi, temp.get_emi()));
  curr.set_amb(parse_floats(pamb, temp.get_amb()));
  curr.set_diff(parse_floats(pdiff, temp.get_diff()));
  curr.set_spec(parse_floats(pspec, temp.get_spec()));

  // scale, rotate, translate using your real tranformations from assignment 3 depending on input from spec file
  real_scaling(curr, temp.get_scale().get_x(), temp.get_scale().get_y(), temp.get_scale().get_z());  
  real_rotation(curr, temp.get_rotate().get_x(), 1, 0, 0);
  real_rotation(curr, temp.get_rotate().get_y(), 0, 1, 0);
  real_rotation(curr, temp.get_rotate().get_z(), 0, 0, 1);
  real_translation(curr, temp.get_translate().get_x(), temp.get_translate().get_y(), temp.get_translate().get_z());
  
  shapes[num_objects] = curr;
  num_objects++;

  printf("read object #%d\n", num_objects);
}


float dotprod(float v1[], float v2[]) {
  float tot = 0;
  int i;
  for (i=0; i<4; i++)
    tot += v1[i]*v2[i];
  return tot;
}

void set_r() {
  R[0][0] = my_cam.u[0];
  R[0][1] = my_cam.v[0];
  R[0][2] = my_cam.w[0];
  R[0][3] = 0;
  
  R[1][0] = my_cam.u[1];
  R[1][1] = my_cam.v[1];
  R[1][2] = my_cam.w[1];
  R[1][3] = 0;
  
  R[2][0] = my_cam.u[2];
  R[2][1] = my_cam.v[2];
  R[2][2] = my_cam.w[2];
  R[2][3] = 0;
  
  R[3][0] = 0;
  R[3][1] = 0;
  R[3][2] = 0;
  R[3][3] = 1;
  
}

void set_t() {
  GLdouble Pn[4];
  Pn[0] = my_cam.pos[0] + near*my_cam.w[0];
  Pn[1] = my_cam.pos[1] + near*my_cam.w[1];
  Pn[2] = my_cam.pos[2] + near*my_cam.w[2];
  Pn[3] = my_cam.pos[3] + near*my_cam.w[3];

  T[0][0] = 1;
  T[0][1] = 0;
  T[0][2] = 0;
  T[0][3] = 0;
  
  T[1][0] = 0;
  T[1][1] = 1;
  T[1][2] = 0;
  T[1][3] = 0;
  
  T[2][0] = 0;
  T[2][1] = 0;
  T[2][2] = 1;
  T[2][3] = 0;
  
  T[3][0] = -Pn[0];
  T[3][1] = -Pn[1];
  T[3][2] = -Pn[2];
  T[3][3] = 1;
  
}

void set_s() {
  GLdouble width = right - left;
  GLdouble height = top - bottom;
  
  S[0][0] = 2/width;
  S[0][1] = 0;
  S[0][2] = 0;
  S[0][3] = 0;
  
  S[1][0] = 0;
  S[1][1] = 2/height;
  S[1][2] = 0;
  S[1][3] = 0;
  
  S[2][0] = 0;
  S[2][1] = 0;
  S[2][2] = 1/far;
  S[2][3] = 0;
  
  S[3][0] = 0;
  S[3][1] = 0;
  S[3][2] = 0;
  S[3][3] = 1;

}

void set_RT() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      RT[i][j] = R[i][0]*T[0][j];
      for (int k = 1; k < 4; k++) {
        RT[i][j] += R[i][k]*T[k][j];
      }
    }
  }
}


void parse_camera(char *buffer){
  CAM *pc;
  char *ppos, *plook, *pup;

  pc = &my_cam;

  strtok(buffer, "()");
  ppos  = strtok(NULL, "()");  strtok(NULL, "()"); 
  plook  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pup  = strtok(NULL, "()");  strtok(NULL, "()"); 

  parse_floats_old(ppos, pc->pos);
  parse_floats_old(plook, pc->at);
  parse_floats_old(pup, pc->up);

  pc->at[0] += pc->pos[0];
  pc->at[1] += pc->pos[1];
  pc->at[2] += pc->pos[2];

  pc->dir[0] = pc->at[0] - pc->pos[0];
  pc->dir[1] = pc->at[1] - pc->pos[1];
  pc->dir[2] = pc->at[2] - pc->pos[2];
  normalize(pc->dir);

  int tempsum;
  for (int i = 0; i < 3; i++) {
    pc->w[i] = pc->at[i] - pc->pos[i];
  }
  for (int j = 0; j < 3; j++) {
    tempsum += pc->w[j];
  }
  if (tempsum != 0) {
    normalize(pc->w);
  }
  tempsum = 0;
  for (int i = 0; i < 3; i++) {
    pc->v[i] = pc->up[i] - dotprod(pc->up, pc->w)*pc->w[i];
  }  
  for (int j = 0; j < 3; j++) {
    tempsum += pc->v[j];
  }
  if (tempsum != 0) {
    normalize(pc->v);
  } 


  GLdouble newX, newY, newZ;

  newX = pc->v[1]*pc->w[2] - pc->v[2]*pc->w[1];
  newY = pc->v[2]*pc->w[0] - pc->v[0]*pc->w[2];
  newZ = pc->v[0]*pc->w[1] - pc->v[1]*pc->w[0];

  pc->u[0] = newX;
  pc->u[1] = newY;
  pc->u[2] = newZ;

  printf("read camera\n");


   set_r();
   set_t();
   set_RT();
   set_s();
}


void parse_light(char *buffer){
  LITE *pl;
  char *pamb, *pdiff, *pspec, *ppos, *pdir, *pang;
  //my_assert ((num_lights < MAX_LIGHTS), "too many lights");
  pl = &my_lights[++num_lights];

  strtok(buffer, "()");
  pamb  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdiff = strtok(NULL, "()");  strtok(NULL, "()"); 
  pspec = strtok(NULL, "()");  strtok(NULL, "()"); 
  ppos  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdir  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pang  = strtok(NULL, "()");

  parse_floats_old(pamb, pl->amb);
  parse_floats_old(pdiff, pl->diff);
  parse_floats_old(pspec, pl->spec);
  parse_floats_old(ppos, pl->pos);
  if (pdir) {
    parse_floats_old(pdir, pl->dir);
    pl->angle = atof(pang);
    //printf("angle %f\n", pl->angle);
  }
  else
    pl->dir[0]= pl->dir[1]= pl->dir[2] =0;
  printf("read light\n");

}

/* assuming the spec is going to be properly written
   not error-checking here */
void read_spec(char *fname) {
  char buffer[300];
  FILE *fp;

  fp = fopen(fname, "r");
//  my_assert(fp, "can't open spec");
  while(!feof(fp)){
    fgets(buffer, 300, fp);
    //printf("read line: %s\n", buffer);
    switch (buffer[0]) {
    case '#':
      break;
    case '1': //cube
      parse_cube(buffer);
      break;
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
      //read in the cube
    parse_obj(buffer);
    break;
  //etc

    case 'l':
      parse_light(buffer);
      break;

    case 'c':
      parse_camera(buffer);
      break;

    default:
      break;
    }
  }
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
void real_rot_arbitrary_axis_point(Matrix3 &verts, GLdouble deg, GLdouble ax, GLdouble ay, GLdouble az, GLdouble cx, GLdouble cy, GLdouble cz ) {
  
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
void real_rev(GLdouble deg, GLdouble x, GLdouble y, GLdouble z) {

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



// reuse code from assignment 3 here to do transformations when reading spec
void real_translation_cube(OBJECT *po, GLfloat x, GLfloat y, GLfloat z) {
  for(int i = 0; i < 8; i++) {
    po->vertices_cube_smart[i][0] += x;
    po->vertices_cube_smart[i][1] += y;
    po->vertices_cube_smart[i][2] += z;
  }

}

void real_scaling_cube(OBJECT *po, GLfloat sx, GLfloat sy, GLfloat sz) {
  for(int i = 0; i < 8; i++) {
    po->vertices_cube_smart[i][0] *= sx;
    po->vertices_cube_smart[i][1] *= sy;
    po->vertices_cube_smart[i][2] *= sz;
  }
}

void real_rotation_cube(OBJECT *po, GLfloat deg, GLfloat x, GLfloat y, GLfloat z) {
  GLdouble xx, yy, zz;

  for(int i = 0; i < 8; i++) {
    xx = po->vertices_cube_smart[i][0];
    yy = po->vertices_cube_smart[i][1];
    zz = po->vertices_cube_smart[i][2];

    if (x == 1) {
      po->vertices_cube_smart[i][1] = cos(deg)*yy - sin(deg)*zz;
      po->vertices_cube_smart[i][2] = sin(deg)*yy + cos(deg)*zz;
    }
    if (y == 1) {
      po->vertices_cube_smart[i][0] = cos(deg)*xx + sin(deg)*zz;
      po->vertices_cube_smart[i][2] = -sin(deg)*xx + cos(deg)*zz;
    }
    if (z == 1) {
      po->vertices_cube_smart[i][0] = cos(deg)*xx - sin(deg)*yy;
      po->vertices_cube_smart[i][1] = sin(deg)*xx + cos(deg)*yy;
    }
  }

}

/*********************************
 * real_translation: translates the verts object
                     by x,y,z
************************************/
void real_translation(Matrix3 &verts, GLdouble x, GLdouble y, GLdouble z) {
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
void real_scaling(Matrix3 &verts, GLdouble sx, GLdouble sy, GLdouble sz) {
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
void real_rotation(Matrix3 &verts, GLdouble deg, GLdouble x, GLdouble y, GLdouble z) {

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
  
  float amnt = .2;
  switch( key ) {
  
  // pick a transform case
  case 'T':
  case 't': {
    crt_transform = REAL_TRANSLATION_MODE;
  }; break;

  case 'X': {
    my_cam.pos[0] += amnt;
  }; break;
  case 'x': {
    my_cam.pos[0] -= amnt;
  }; break;
  case 'Y': {
    my_cam.pos[1] += amnt;
  }; break;
  case 'y': {
    my_cam.pos[1] -= amnt;
  }; break;
  case 'Z': {
    my_cam.pos[2] += amnt;
  }; break;
  case 'z': {
    my_cam.pos[2] -= amnt;
  }; break;
  

  case 'U': {
    my_cam.pos[0] += amnt*my_cam.u[0];
    my_cam.pos[1] += amnt*my_cam.u[1];
    my_cam.pos[2] += amnt*my_cam.u[2];
    my_cam.at[0] += amnt*my_cam.u[0];
    my_cam.at[1] += amnt*my_cam.u[1];
    my_cam.at[2] += amnt*my_cam.u[2];
  }; break;
  case 'u': {
    my_cam.pos[0] -= amnt*my_cam.u[0];
    my_cam.pos[1] -= amnt*my_cam.u[1];
    my_cam.pos[2] -= amnt*my_cam.u[2]; 
    my_cam.at[0] -= amnt*my_cam.u[0];
    my_cam.at[1] -= amnt*my_cam.u[1];
    my_cam.at[2] -= amnt*my_cam.u[2];
  }; break;
  case 'V': {
    my_cam.pos[0] += amnt*my_cam.v[0];
    my_cam.pos[1] += amnt*my_cam.v[1];
    my_cam.pos[2] += amnt*my_cam.v[2];
    my_cam.at[0] += amnt*my_cam.v[0];
    my_cam.at[1] += amnt*my_cam.v[1];
    my_cam.at[2] += amnt*my_cam.v[2];
  }; break;
  case 'v': {
    my_cam.pos[0] -= amnt*my_cam.v[0];
    my_cam.pos[1] -= amnt*my_cam.v[1];
    my_cam.pos[2] -= amnt*my_cam.v[2];
    my_cam.at[0] -= amnt*my_cam.v[0];
    my_cam.at[1] -= amnt*my_cam.v[1];
    my_cam.at[2] -= amnt*my_cam.v[2];
  }; break;
  case 'L':
  case 'W': {
    my_cam.pos[0] += amnt*my_cam.w[0];
    my_cam.pos[1] += amnt*my_cam.w[1];
    my_cam.pos[2] += amnt*my_cam.w[2];
    my_cam.at[0] += amnt*my_cam.w[0];
    my_cam.at[1] += amnt*my_cam.w[1];
    my_cam.at[2] += amnt*my_cam.w[2];
  }; break;
  case 'l':
  case 'w': {
    my_cam.pos[0] -= amnt*my_cam.w[0];
    my_cam.pos[1] -= amnt*my_cam.w[1];
    my_cam.pos[2] -= amnt*my_cam.w[2];
    my_cam.at[0] -= amnt*my_cam.w[0];
    my_cam.at[1] -= amnt*my_cam.w[1];
    my_cam.at[2] -= amnt*my_cam.w[2];
  }; break;
  
  case 'H': {
   height_angle++;
  }; break;
  case 'h': {
   height_angle--;
  }; break;
  case 'A': {
    if (aspect_ratio < 3)
      aspect_ratio += .1;
  }; break;
  case 'a': {
   if (aspect_ratio > .1)
    aspect_ratio -= .1;
  }; break;
  case 'N': {
   if (near + .1 <= far)
    near += .1;
  }; break;
  case 'n': {
   if (near - .1 <= my_cam.pos[2])
    near -= .1;
  }; break;
  case 'F': {
    far += .1;
  }; break;
  case 'f': {
   if (far - .1 >= near)
    far -= .1;
  }; break;
  
  case 'c':
  case 'C': {
    ortho = (ortho + 1)%2;
  }; break;

  case 'p':
  case 'P': {
    printf("\nINFO DUMP:\n");
    printf("The eye point: %f, %f, %f\n", my_cam.pos[0], my_cam.pos[1], my_cam.pos[2]);
    printf("The look vector: %f, %f, %f\n", my_cam.at[0], my_cam.at[1], my_cam.at[2]);
    printf("The up vector: %f, %f, %f\n", my_cam.up[0], my_cam.up[1], my_cam.up[2]);
    printf("The height angle: %f\n", height_angle);
    printf("The aspect ratio: %f\n", aspect_ratio);
    printf("The world to film matrix:\n");
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        printf("%4f ", RT[i][j]);
      }
      printf("\n");
    }
  }; break;


  // q is for quit!!!
  case 'q': 
  case 'Q':

    exit(0) ;

    break ;	

  default: break;
  }
  set_r();
  set_t();
  set_RT();
  set_s();
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  gluPerspective(height_angle, aspect_ratio, near, far);
  glMatrixMode(GL_MODELVIEW) ;
    glutPostRedisplay();

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
    //  show_normals = (show_normals + 1) % 2;

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


void draw_quad(GLfloat vertices[][4], GLfloat *normals, int iv1, int iv2, int iv3, int iv4, int ic) {
  glBegin(crt_render_mode); 
  {
    glColor3fv(colors[ic]);
    glNormal3fv(normals);
    /*note the explicit use of homogeneous coords below: glVertex4f*/
    glVertex4fv(vertices[iv1]);
    glVertex4fv(vertices[iv2]);
    glVertex4fv(vertices[iv3]);
    glVertex4fv(vertices[iv4]);
  }
  glEnd();
}

/***********************************
 FUNCTION: draw_cube_smart() 
 ARGS: none
 RETURN: none
 DOES: draws a cube from quads
************************************/
void draw_cube_smart(OBJECT *po)
{

  /* sides */
  draw_quad(po->vertices_cube_smart, po->normals_cube_smart[0],0,1,2,3, BLUE);
  draw_quad(po->vertices_cube_smart, po->normals_cube_smart[1],1,5,6,2, BLUE);
  draw_quad(po->vertices_cube_smart, po->normals_cube_smart[2],5,4,7,6, BLUE);
  draw_quad(po->vertices_cube_smart, po->normals_cube_smart[3],4,0,3,7, BLUE);
    
  /* top and bottom */
  //draw_quad(po->vertices_cube_smart,3,2,6,7, BLUE);
  //draw_quad(po->vertices_cube_smart,0,1,5,4, BLUE);
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
//  case HOUSE: draw_house(); break;
  case CUBE: 
    for (int i = 0; i < num_cubes; i++)
      draw_cube_smart(&cubes[i]);
    break; 
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
 

 // REPLACE THIS HERE
  if (ortho) { 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixd(*S);
  }
   // init to identity 
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity() ;
  glMultMatrixd(*RT);
  // UNTIL HERE
  /* With the following:

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  //setup the camera (1st person? 3rd person?)

  gluLookAt(my_cam.pos[0],my_cam.pos[1], my_cam.pos[2],
      my_cam.at[0],my_cam.at[1],my_cam.at[2],
      my_cam.up[0], my_cam.up[1], my_cam.up[2]);



  */

  for (int i = 0; i < num_objects; i++) {
    curr = shapes[i];
    draw_object(curr.get_shape());
  }
  // draw the cubes
  draw_object(1);


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

void normalize(GLfloat *p) { 
  double d=0.0;
  int i;
  for(i=0; i<3; i++) d+=p[i]*p[i];
  d=sqrt(d);
  if(d > 0.0) for(i=0; i<3; i++) p[i]/=d;
}


void cross(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d) { 
  d[0]=(b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
  d[1]=(b[2]-a[2])*(c[0]-a[0])-(b[0]-a[0])*(c[2]-a[2]);
  d[2]=(b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0]);
  normalize(d);
}


void make_cube_smart(OBJECT *po, double size){
  int i;  
  // compute verts on PI/4 angels for x y z, then -x y z  
  for(i = 0; i < 4; i++){
    po->vertices_cube_smart[i][0] = size*cos((M_PI/4));
    po->vertices_cube_smart[i][1] = -size*sin(i*(M_PI/2)+(M_PI/4));
    po->vertices_cube_smart[i][2] = size*cos(i*(M_PI/2)+(M_PI/4));
    po->vertices_cube_smart[i][3] = 1;
    // mirror on x axis
    po->vertices_cube_smart[i+4][0] = -size*cos((M_PI/4));
    po->vertices_cube_smart[i+4][1] = -size*sin(i*(M_PI/2)+(M_PI/4));
    po->vertices_cube_smart[i+4][2] = size*cos(i*(M_PI/2)+(M_PI/4));
    po->vertices_cube_smart[i+4][3] = 1;
  }

  //compute normals
    cross(po->vertices_cube_smart[0], po->vertices_cube_smart[1], po->vertices_cube_smart[2], po->normals_cube_smart[0]);
    cross(po->vertices_cube_smart[1], po->vertices_cube_smart[5], po->vertices_cube_smart[6], po->normals_cube_smart[1]);
    cross(po->vertices_cube_smart[5], po->vertices_cube_smart[4], po->vertices_cube_smart[7], po->normals_cube_smart[2]);
    cross(po->vertices_cube_smart[4], po->vertices_cube_smart[0], po->vertices_cube_smart[3], po->normals_cube_smart[3]);
}
