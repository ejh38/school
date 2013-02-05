/*******************************************************
FILE: stitcher.c
AUTHOR: gem, loosely based on random hwa skel
DATE: 01/24/08
DOES: skeleton for hmkw2 redux
PLATFORM: tested on osx, linux, and vs
********************************************************/

#include "stitcher.h"

int theta_x;
int theta_y;
int crt_render_mode;
int crt_shape, crt_rs, crt_vs;
double cyl_height=3;
double cyl_ray=1;
double sph_ray=3;
 
double theta, phi;

/*******************************************************
FUNCTION: main
ARGS: argc, argv
RETURN: 0
DOES: main function (duh!); starts GL, GLU, GLUT, then loops 
********************************************************/
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


/*******************************************************
FUNCTION: glut_setup
ARGS: none
RETURN: none
DOES: sets up GLUT; done here because we like our 'main's tidy
********************************************************/
/* This function sets up the windowing related glut calls */
void glut_setup(void) {

  /* specify display mode -- here we ask for a double buffer and RGB coloring */
  /* NEW: tell display we care about depth now */
  glutInitDisplayMode (GLUT_DOUBLE |GLUT_RGB |GLUT_DEPTH);

  /* make a 400x400 window with the title of "Stitcher" placed at the top left corner */
  glutInitWindowSize(400,400);
  glutInitWindowPosition(300,3000);
  glutCreateWindow("Stitcher");

  /*initialize callback functions */
  glutDisplayFunc( my_display );
  glutReshapeFunc( my_reshape ); 
  glutMouseFunc( my_mouse);
  glutKeyboardFunc(my_keyboard);

  /*just for fun, uncomment the line below and observe the effect :-)
    Do you understand now why you shd use timer events, 
    and stay away from the idle event?  */
  //  glutIdleFunc( my_idle );
	
  glutTimerFunc( 20000, my_TimeOut, 0);/* schedule a my_TimeOut call with the ID 0 in 20 seconds from now */
  return ;
}


/*******************************************************
FUNCTION: gl_setup
ARGS: none
RETURN: none
DOES: sets up OpenGL (name starts with gl but not followed by capital letter, so it's ours)
********************************************************/
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

/*******************************************************
FUNCTION: my_setup
ARGS: 
RETURN:
DOES: pre-computes staff and presets some values
********************************************************/
/*TODO EC: add make_torus etc.   */
void my_setup(void) {
  theta_x = 0;
  theta_y = 0;
  crt_render_mode = GL_LINE_LOOP;
  crt_shape = HOUSE;
  crt_rs = 20;
  crt_vs = 10;
  
  make_cylinder(cyl_height,cyl_ray,crt_rs,crt_vs);
  make_sphere(sph_ray,crt_rs,crt_vs);
  //add make_torus etc...
  return;
}

/*******************************************************
FUNCTION: my_reshape
ARGS: new window width and height 
RETURN:
DOES: remaps viewport to the Window Manager's window
********************************************************/
void my_reshape(int w, int h) {

  /* define viewport -- x, y, (origin is at lower left corner) width, height */
  glViewport (0, 0, min(w,h), min(w,h));
  return;
}


/*******************************************************
FUNCTION: my_keyboard
ARGS: key id, x, y
RETURN:
DOES: handles keyboard events
********************************************************/
/*TODO: expand to add asgn 2 keyboard events */
void my_keyboard( unsigned char key, int x, int y ) {
  
  switch( key ) {
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
 case 'q': 
  case 'Q':
    exit(0) ;
  default: break;
  }
  //add spheres etc...
  return ;
}


/*******************************************************
FUNCTION: my_mouse
ARGS: button, state, x, y
RETURN:
DOES: handles mouse events
********************************************************/
void my_mouse(int button, int state, int mousex, int mousey) {

  switch( button ) {
	
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ) {
      crt_render_mode = GL_LINE_LOOP;
      /* if you're not sure what glutPostRedisplay does for us,
	 try commenting out the line below; observe the effect.*/
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



/***********************************
  FUNCTION: draw_triangle 
  ARGS: - a vertex array
        - 3 indices into the vertex array defining a triangular face
        - an index into the color array.
  RETURN: none
  DOES:  helper drawing function; draws one triangle. 
   For the normal to work out, follow left-hand-rule (i.e., ccw)
*************************************/
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

/***********************************
  FUNCTION: draw_quad 
  ARGS: - a vertex array
        - 4 indices into the vertex array defining a quad face
        - an index into the color array.
  RETURN: none
  DOES:  helper drawing function; draws one quad. 
   For the normal to work out, follow left-hand-rule (i.e., counter clock
   wise) 
*************************************/
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

/***********************************
  FUNCTION: draw_param_quad 
  ARGS: - a 50 by 50 by 4 vertex array
        - 2 indices into the vertex array defining the top left of a quad face
        - an index into the color array.
  RETURN: none
  DOES:  helper drawing function; draws one quad. 
*************************************/
/*TODO: redefine and implement as needed, according to your data structures */
void draw_param_quad(GLfloat vertices[][50][4], int line, int col, int ic) {

}


/***********************************
  FUNCTION: draw_house 
  ARGS: none
  RETURN: none
  DOES: helper build function; 
        defines a hollow cube with a bottomless pyramid as rooftop
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

/***********************************
  FUNCTION: draw_cube_brute 
  ARGS: none
  RETURN: none
  DOES: helper build function; 
        defines a hollow cube without a bottom or a top
************************************/
/*TODO: add bottom and top face triangles*/
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




/***********************************
  FUNCTION: make_cylinder 
  ARGS: height (along the Y axis), ray, and tesselation parameter (how many side faces) 
  RETURN: none
  DOES: helper build function; 
        defines a cylinder centered at the origin, 
        of height 'height' along the Y axis,
        and ray 'ray' in the XOZ plane
************************************/
/*TODO: compute cylinder vertices*/
void make_cylinder(double height, double ray, int rs, int vs)
{
  /*hint: top-face vertices lie on a circle (same for bottom); 
    if need be, generate top-face vertices by cutting the circle in pie slices*/
}


/***********************************
  FUNCTION: make_sphere 
  ARGS: ray, and tessellation parameters (how many meridians, respectively parallels) 
  RETURN: none
  DOES: helper build function; 
        defines a sphere centered at the origin and of ray 'ray'
************************************/
/*TODO: compute sphere vertices, 
        don't bother about color*/
void make_sphere(double ray, int rs, int vs)
{
  for (int i = 0, phi = 0; i < vs; i++, phi += 2*M_PI/vs) {
    for (int j = 0, theta = -M_PI/2; j < rs; j++, theta += M_PI/rs) {
      // do this
    }
  }

}


/***********************************
  FUNCTION: draw_cylinder() 
  ARGS: none
  RETURN: none
  DOES: draws a cylinder from triangles
************************************/
/*TODO: stitch cylinder vertices together to make faces
don't call gl directly, use my_draw_triangle and my_draw_quad instead*/
void draw_cylinder(int rs, int vs)
{
}

/***********************************
  FUNCTION: draw_sphere() 
  ARGS: none
  RETURN: none
  DOES: draws a sphere from triangles
************************************/
/*TODO: stitch sphere vertices together to make faces
don't call gl directly, use make_triangle and make_quad instead*/
void draw_sphere(int rs, int vs)
{
}


/***********************************
  FUNCTION: draw_object 
  ARGS: shape to create (HOUSE, CUBE, CYLINDER, etc)
  RETURN: none
  DOES: draws an object from triangles
************************************/
/*TODO: expand according to assignment 2 specs*/
void draw_object(int shape) {

  switch(shape){
  case HOUSE: draw_house(); break;
  case CUBE: draw_cube_brute(); break; 
  case CYLINDER: draw_cylinder(crt_rs, crt_vs);  break;
  case SPHERE: draw_sphere(crt_rs, crt_vs);  break;
  case TORUS: /*TODO EC: call your function here*/ ; break;
  case MESH: /*TODO EC: call your function here*/ ; break;

  default: break;
  }

}



/***********************************
  FUNCTION: my_display
  ARGS: none
  RETURN: none
  DOES: main drawing function
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


/***********************************
  FUNCTION: my_idle
  ARGS: none
  RETURN: none
  DOES: handles the "idle" event
************************************/
void my_idle(void) {
  theta_y = (theta_y+2) %360;
  glutPostRedisplay();
  return ;
}


/***********************************
  FUNCTION: my_TimeOut
  ARGS: timer id
  RETURN: none
  DOES: handles "timer" events
************************************/
void my_TimeOut(int id) {
  /* right now, does nothing*/
  /* schedule next timer event, 20 secs from now */ 
  glutTimerFunc(20000, my_TimeOut, 0);

  return ;
}



