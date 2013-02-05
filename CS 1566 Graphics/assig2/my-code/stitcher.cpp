/*******************************************************
FILE: stitcher.cpp
AUTHOR: Zach Sadler - zps6
DOES: Generates vertices and normals for 3d shapes, and displays them
      on screen. Also has some fun extra credit goodies
PLATFORM: macosx
********************************************************/

#include <stdio.h>
#include "stitcher.h"
#include "Matrix2.cpp"
#include "Matrix3.cpp"

int theta_x;
int theta_y;

int crt_render_mode;
int crt_shape, crt_rs= 10, crt_vs= 10;

// effectively, the shapes
Matrix3 sphere_verts;
Matrix3 cylinder_verts;
Matrix3 cone_verts;
Matrix3 torus_verts;

// default sizes for the shapes
double cyl_height=1, cyl_ray=.5;
double sph_ray=1;
double cone_ray = 1, cone_height = 1;
double torus_r1 = 1.2, torus_r2 = .2;

// used in calculations throughout
double theta, phi, h, r;

// toggle for showing the normals
short show_normals;

// extra credit things here
short slowmo;
short spin_x, spin_y, play_rs, play_vs;
int timer_speed = 50;


/*********************************
 * main: didn't touch this from the example code
************************************/

int main(int argc, char **argv) {

  /* General initialization for GLUT and OpenGL
     Must be called first */
  glutInit( &argc, argv ) ;
  
  /* we define these setup procedures */
  glut_setup() ;  
  gl_setup() ;
  my_setup();

  /* go into the main event loop */
  glutMainLoop() ;

  return(0) ;
}


/*********************************
 * glut_setup: didn't touch this either, from the example code
 * except to change the window size and position, as well as the name
************************************/
void glut_setup(void) {

  /* specify display mode -- here we ask for a double buffer and RGB coloring */
  /* NEW: tell display we care about depth now */
  glutInitDisplayMode (GLUT_DOUBLE |GLUT_RGB |GLUT_DEPTH);

  glutInitWindowSize(800 ,800);
  glutInitWindowPosition(300,3000);
  glutCreateWindow("Zach Sadler - zps6 - Assignment 2");

  /*initialize callback functions */
  glutDisplayFunc( my_display );
  glutReshapeFunc( my_reshape ); 
  glutMouseFunc( my_mouse);
  glutKeyboardFunc(my_keyboard);

  glutTimerFunc( timer_speed, my_TimeOut, 0);/* schedule a my_TimeOut call with the ID 0 in 20 seconds from now */
  return ;
}


/*********************************
 * gl_setup: didn't touch this from the example code
************************************/
void gl_setup(void) {

  /* specifies a background color: black in this case */
  glClearColor(0,0,0,0) ;

  /* NEW: now we have to enable depth handling (z-buffer) */
  glEnable(GL_DEPTH_TEST);

  /* NEW: setup for 3d projection */
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  // perspective view
  gluPerspective( 20.0, 1.0, 1.0, 100.0);
  return;
}

/*********************************
 * my_setup: added the rest of the make_OBJECT
************************************/
void my_setup(void) {
  theta_x = 0;
  theta_y = 0;
  crt_render_mode = GL_LINE_LOOP;
  crt_shape = HOUSE;
  
  make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
  make_sphere(sph_ray,crt_rs,crt_vs);
  make_cone(cone_height, cone_ray, crt_rs, crt_vs);
  make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
  return;
}

/*********************************
 * my_reshape: didn't touch this from the example code
************************************/
void my_reshape(int w, int h) {

  /* define viewport -- x, y, (origin is at lower left corner) width, height */
  glViewport (0, 0, min(w,h), min(w,h));
  return;
}


/*********************************
 * my_keyboard: added quite a bit here; see the 'Controls' part 
                of the readme file for more details
************************************/
void my_keyboard( unsigned char key, int x, int y ) {
  
  switch( key ) {
  
  // rotations
  case 'y':
  case 'Y': {
    theta_y = (theta_y+5) %360;
    glutPostRedisplay(); 
  }; break;
  case 'x':
  case 'X': {
    theta_x = (theta_x+5) %360;
    glutPostRedisplay(); 
  }; break;
  case 'z':
  case 'Z': {
    theta_x = (theta_x-5) %360;
    glutPostRedisplay(); 
  }; break;
  case 't':
  case 'T': {
    theta_y = (theta_y-5) %360;
    glutPostRedisplay(); 
  }; break;


  // changing the shape
  case 'B':
  case 'b': {
    crt_shape = CUBE;
    glutPostRedisplay();
  }; break;
  case 'H':
  case 'h': {
    crt_shape = HOUSE;
    glutPostRedisplay();
  }; break;
  case 'S':
  case 's': {
    crt_shape = SPHERE;
    glutPostRedisplay();
  }; break;
  case 'N':
  case 'n': {
    crt_shape = CONE;
    glutPostRedisplay();
  }; break;
  case 'C':
  case 'c': {
    crt_shape = CYLINDER;
    glutPostRedisplay();
  }; break;
  case 'r':
  case 'R': {
    crt_shape = TORUS;
    glutPostRedisplay();
  }; break;



  // toggle showing the normals
  case 'V':
  case 'v': {
    show_normals = (1 + show_normals)%2; 
    glutPostRedisplay();
  }; break;



  // these adjust rs and vs, and then re-call the make functions
  case '=':
  case '+': {
    if (crt_rs < 50)
      crt_rs++;
    make_sphere(sph_ray, crt_rs, crt_vs);
    make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
    make_cone(cone_height, cone_ray, crt_rs, crt_vs);
    make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
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
    glutPostRedisplay();
  }; break;

  // quit the program (not that anyone ever would want to...)
  case 'q': 
  case 'Q': {
    exit(0) ;
  }; break;


  /************************************/
  /**********EXTRA CREDIT BELOW********/
  /************************************/

  // toggle slowmo drawing
  case '1': {
    slowmo = (1 + slowmo)%2;
  }; break;

  // my sizes that I prefer over the defaults
  // I think these are much prettier and easier to see
  case '2': {
    cyl_height=3;
    cyl_ray=1;
    sph_ray=2;
    cone_ray = 1.5;
    cone_height = 3;
    torus_r1 = 2;
    torus_r2 = .5;
    crt_rs = 25;
    crt_vs = 25;
    make_sphere(sph_ray, crt_rs, crt_vs);
    make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
    make_cone(cone_height, cone_ray, crt_rs, crt_vs);
    make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
    glutPostRedisplay();
  }; break;

  // toggles automatically rotating along the x axis
  case '3': {
    spin_x = (1 + spin_x)%2;
    glutPostRedisplay();
  }; break;

  // toggles automatically rotating along the y axis
  case '4': {
    spin_y = (1 + spin_y)%2;
    glutPostRedisplay();
  }; break;

  // toggles automatically iterating through values for rs
  case '5': {
    play_rs = (1 + play_rs)%2;
    glutPostRedisplay();
  }; break;

  // toggles automatically iterating through values for vs
  case '6': {
    play_vs = (1 + play_vs)%2;
    glutPostRedisplay();
  }; break;

  // changes the timer_speed from 50 -> 100 -> 150 -> 200 -> 250 -> 50 -> ...
  case '7': {
    timer_speed = (50 + timer_speed) % 300;
    if (timer_speed == 0) {
      timer_speed = 50;
    }
  }; break;


  default: break;
  }


  return ;
}


/*********************************
 * my_mouse: largely untouched from the example code
************************************/
void my_mouse(int button, int state, int mousex, int mousey) {

  switch( button ) {
	
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ) {
      crt_render_mode = GL_LINE_LOOP;
      glutPostRedisplay();
    }
    if( state == GLUT_UP ) {
    }
    break ;

  case GLUT_RIGHT_BUTTON:
    if ( state == GLUT_DOWN ) {
      crt_render_mode = GL_POLYGON;
      glutPostRedisplay();
    }
    if( state == GLUT_UP ) {
    }
    break ;
  }
  
  return ;
}



/*********************************
 * draw_triangle: untouched from the example code
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
 * my_triangle: this is my triangle drawing function. It takes in
                a Shape object, indices into the shape's vertex array,
                and the values of rs and vs.
                It generates two triangles, stitched together, of
                different colors.
                It also displays the normals, if asked.
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
 * draw_quad: untouched from the example code
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
 * draw_param_quad: untouched from the example code
************************************/
void draw_param_quad(GLfloat vertices[][50][4], int line, int col, int ic) {

}


/*********************************
 * draw_house: untouched from the example code
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
 * draw_triangle: added bottom and top faces, as well as normals
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

  if (show_normals) {
    glBegin(GL_LINES); 
    {
      glColor3fv(colors[CYAN]);
      glVertex4f(1, 1, 1, 1);
      glVertex4f(1 + 1/sqrt(3), 1 + 1/sqrt(3), 1 + 1/sqrt(3), 1);
      glVertex4f(1, 1, -1, 1);
      glVertex4f(1 + 1/sqrt(3), 1 + 1/sqrt(3), -1 - 1/sqrt(3), 1);
      glVertex4f(1, -1, 1, 1);
      glVertex4f(1 + 1/sqrt(3), -1 - 1/sqrt(3), 1 + 1/sqrt(3), 1);
      glVertex4f(1, -1, -1, 1);
      glVertex4f(1 + 1/sqrt(3), -1 - 1/sqrt(3), -1 - 1/sqrt(3), 1);
      glVertex4f(-1, 1, 1, 1);
      glVertex4f(-1 - 1/sqrt(3), 1 + 1/sqrt(3), 1 + 1/sqrt(3), 1);
      glVertex4f(-1, 1, -1, 1); 
      glVertex4f(-1 - 1/sqrt(3), 1 + 1/sqrt(3), -1 - 1/sqrt(3), 1);
      glVertex4f(-1, -1, 1, 1); 
      glVertex4f(-1 - 1/sqrt(3), -1 - 1/sqrt(3), 1 + 1/sqrt(3), 1);
      glVertex4f(-1, -1, -1, 1); 
      glVertex4f(-1 - 1/sqrt(3), -1 - 1/sqrt(3), -1 - 1/sqrt(3), 1);
    }
    glEnd();
  }
}

/*********************************
 * calculate_norms: Takes in a shape object's address (so it can modify it),
                    indices into the shape's verts array, and rs and vs.
                    Generates face norms, and puts them into the face_norms array.
                    Just generates three vectors, then subtracts them and crosses
                    the result, which it normalizes and stores in the array.
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
}

/*********************************
 * calculate_vertex_norms: Using the face norms calculated above, generates
                           a vertex norm by simply summing and normalizing.
                           Stores the result in the vertex_norms array.
************************************/
void calculate_vertex_norms(Matrix3 &verts, int i, int j, int rs, int vs) {

  Vector v1, v2, v3, v4;
  Vector ans;

  v1 = verts.get_face_norm(i,(j-1)%vs);
  v2 = verts.get_face_norm((i-1)%rs,(j-1)%vs);
  v3 = verts.get_face_norm((i-1)%rs,j);
  v4 = verts.get_face_norm(i,j);

  ans = v4.plus(v3);
  ans = v4.plus(v2);
  ans = v4.plus(v1);

  ans.normalize();
  ans = ans.scale(.2);
  ans = verts.get_vector(i,j).subtract(ans);
  verts.set_vertex_norm(ans, i, j);
}

/*********************************
 * make_cylinder: Generates the vertices for the cylinder, then goes ahead
                  and asks for the face norms and vertex norms.
************************************/
void make_cylinder(double height, double ray, int rs, int vs) {
  
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(1, 0, 0, 1);

  int i, j;

  // populate our matrix with the starting vector
  for (i = 0; i < vs; i++) {
    for (j = 0; j < rs; j++) {
      cylinder_verts.set_vector(vstart, j, i);
    }
  }

  // then multiply by our transformation matrix
  for (i = 0, h = -height/2; i < vs; i++, h += height/vs) {
    for (j = 0, phi = -M_PI; j < rs; j++, phi += (2*M_PI)/rs) {
      
      GLdouble m_vals[16] = {
        ray*cos(phi),  0,      sin(phi),   0,
        ray*0,         1,      0,          h,
        -ray*sin(phi), 0,      cos(phi),   0,
        0,             0,      0,          1};

      m.set_matrix(m_vals);
      cylinder_verts.multiply(m, j, i);
    }
  }

  // generate face norms
  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_norms(cylinder_verts, j, i, rs, vs);
    }
  }

  // generate vertex norms
  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_vertex_norms(cylinder_verts, j, i, rs, vs);
    }
  }

}


/*********************************
 * make_sphere:   Generates the vertices for the sphere, then goes ahead
                  and asks for the face norms and vertex norms.
************************************/
void make_sphere(double ray, int rs, int vs)
{
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(0, -1, 0, 1);

  int i, j;

  for (i = 0; i <= vs; i++) {
    for (j = 0; j <= rs; j++) {
      sphere_verts.set_vector(vstart, j, i);
    }
  }

  for (i = 0, phi = 0; i <= vs; i++, phi += 2*M_PI/vs) {
    for (j = 0, theta = 0; j <= rs; j++, theta += M_PI/rs) {
      
      GLdouble m_vals[16] = {
        cos(phi)*cos(theta),  -ray*cos(phi)*sin(theta),   sin(phi), 0,
        sin(theta),            ray*cos(theta),            0,        0,
        -sin(phi)*cos(theta),  ray*sin(phi)*sin(theta),   cos(phi), 0,
        0,                     0,                         0,        1};

      m.set_matrix(m_vals);
      sphere_verts.multiply(m, j, i);
    }
  }

  for (i = 0; i <= vs; i++) {
    for (j = 0; j < rs; j++) {
      calculate_norms(sphere_verts, j, i, rs + 1, vs + 1);
      }
    }

  for (i = 0; i <= vs; i++) {
    for (j = 0; j < rs; j++) {
      calculate_vertex_norms(sphere_verts, j, i, rs + 1, vs + 1);
      }
    }
}


/*********************************
 * make_cone: Generates the vertices for the cone, then goes ahead
              and asks for the face norms and vertex norms.
************************************/
void make_cone(double height, double ray, int rs, int vs)
{
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(1, 0, 0, 1);

  int i, j;

  for (i = 0; i < vs; i++) {
    for (j = 0; j < rs; j++) {
      cone_verts.set_vector(vstart, j, i);
    }
  }

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
      cone_verts.multiply(m, j, i);
    }
  }

  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_norms(cone_verts, j, i, rs, vs);
    }
  }

  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_vertex_norms(cone_verts, j, i, rs, vs);
    }
  }
}


/*********************************
 * make_torus:    Generates the vertices for the torus, then goes ahead
                  and asks for the face norms and vertex norms.
************************************/
void make_torus(double r1, double r2, int rs, int vs)
{
  Matrix2 m;
  Vector vstart;
  vstart.set_vector(1, 0, 0, 1);

  int i, j;

  for (i = 0; i < vs; i++) {
    for (j = 0; j < rs; j++) {
      torus_verts.set_vector(vstart, j, i);
    }
  }

  for (i = 0, phi = 0; i < vs; i++, phi += 2*M_PI/vs) {
    for (j = 0, theta = 0; j < rs; j++, theta += 2*M_PI/rs) {
      
      GLdouble m_vals[16] = {
        r2*cos(phi)*cos(theta),  -cos(theta)*sin(theta), sin(phi),   r1*cos(phi),
        r2*sin(theta),            cos(theta),            0,          0,
        -r2*sin(phi)*cos(theta),  sin(phi)*sin(theta),   cos(phi),  -r1*sin(phi),
        0,                        0,                     0,          1};

      m.set_matrix(m_vals);
      torus_verts.multiply(m, j, i);
    }
  }

  for (int i = 0; i < vs; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_norms(torus_verts, j, i, rs, vs);
    }
  }
  for (int i = 0; i < vs; i++) {
    for (int j = 0; j < rs; j++) {
      calculate_vertex_norms(torus_verts, j, i, rs, vs);
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
      my_triangle(sphere_verts, j, i, rs + 1, vs + 1);
      
      // a crude, but effective way to slow down the drawing proccess
      // and show what's happening
      if (slowmo) {
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
 * draw_cone: Calls my_triangle with the correct parameters.
************************************/
void draw_cone(int rs, int vs)
{
  for (int i = 0; i < vs - 1; i++) {
    for (int j = 0; j < rs; j++) {
      my_triangle(cone_verts, j, i, rs, vs);
      
      // a crude, but effective way to slow down the drawing proccess
      // and show what's happening
      if (slowmo) {
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
      my_triangle(cylinder_verts, j, i, rs, vs);
      
      // a crude, but effective way to slow down the drawing proccess
      // and show what's happening
      if (slowmo) {
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
      my_triangle(torus_verts, j, i, rs, vs);
      
      // a crude, but effective way to slow down the drawing proccess
      // and show what's happening
      if (slowmo) {
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
  case MESH: /*TODO EC: call your function here*/ ; break;

  default: break;
  }

}

/*********************************
 * my_display: Untouched.
************************************/
void my_display(void) {
  /* clear the buffer */
  /* NEW: now we have to clear depth as well */
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT) ;

  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity();
  gluLookAt(0.0, 5.0, 25.0,  // x,y,z coord of the camera 
	    0.0, 0.0, 0.0,  // x,y,z coord of the origin
	    0.0, 1.0, 0.0); // the direction of up (default is y-axis)

  glRotatef(theta_y,0,1,0);
  glRotatef(theta_x,1,0,0);
  draw_object(crt_shape);

  /* buffer is ready */
  glutSwapBuffers();
	
  return ;
}


/*********************************
 * my_idle: I definitely don't call this.
************************************/
void my_idle(void) {
  theta_y = (theta_y+2) %360;
  glutPostRedisplay();
  return ;
}


/*********************************
 * my_TimeOut: Where a lot of the extra credit happens.
               Very simple, just increment certain values
               every timer_speed ms.
************************************/
void my_TimeOut(int id) {

  // if you're spinning, then adjust the theta value and rotate
  if (spin_x) {
    theta_x = (theta_x + 5) %360;
    glRotatef(theta_x,1,0,0);
  }
  if (spin_y) {
    theta_y = (theta_y + 5) %360;
    glRotatef(theta_y,0,1,0);
  }

  // if you're playing with rs or vs, then adjust the value
  // (but keep it in the proper range)
  // and re-make your objects with the new rs/vs value(s)
  if (play_rs) {
    crt_rs = (crt_rs + 1)%50; 
    if (crt_rs < 3) {
      crt_rs = 3; 
    }
    make_sphere(sph_ray, crt_rs, crt_vs);
    make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
    make_cone(cone_height, cone_ray, crt_rs, crt_vs);
    make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
  }
  if (play_vs) {
    crt_vs = (crt_vs + 1)%50;
    if (crt_vs < 3) {
      crt_vs = 3;
    } 
    make_sphere(sph_ray, crt_rs, crt_vs);
    make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
    make_cone(cone_height, cone_ray, crt_rs, crt_vs);
    make_torus(torus_r1, torus_r2, crt_rs, crt_vs);
  }

  // if any of the above happened, then show the user the new screen!
  if (spin_x || spin_y || play_rs || play_vs) {
    glutPostRedisplay();
  }

  // call the timer again, at the same speed
  glutTimerFunc(timer_speed, my_TimeOut, 0);
  return ;
}
