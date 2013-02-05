/************************************************
FILE: glhello.c
DOES: example of basic gl setup and display
AUTHOR: cs1566 Staff, University of Pittsburgh
DATE: Sept 2011
*************************************************/

#include "glhello.h"

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

/* This function sets up the windowing related glut calls */
void glut_setup(void) {

  /* specify display mode -- here we ask for a double buffer and RGB coloring */
  glutInitDisplayMode (GLUT_DOUBLE |GLUT_RGB);

  /* make a 400x300 window with the title of "GLUT Skeleton" placed at the top left corner */
  glutInitWindowSize(400,300);
  glutInitWindowPosition(0,0);
  glutCreateWindow("GLUT Skeleton");

  /*initialize callback functions */
  glutDisplayFunc( my_display );
  glutReshapeFunc( my_reshape ); 
  glutIdleFunc( my_idle );	

  return ;
}

/* This function sets up the initial states of OpenGL related environment */
void gl_setup(void) {

  /* specifies a background color: black in this case */
  glClearColor(0,0,0,0) ;

  /* setup for simple 2d projection */
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, 0, 1.0); 

  return ;
}

void my_setup(void) {
  return;
}

void my_reshape(int w, int h) {

  /* define viewport -- x, y, (origin is at lower left corner) width, height */
  glViewport (0, (int)(h*0.25), w/2, h/2); 
  
  return;
}

void my_display(void) {
  /* clear the buffer */
  glClear(GL_COLOR_BUFFER_BIT) ;
  
  glColor3f(0,1,0) ;

  /* draw something */
  glBegin(GL_POLYGON);
  glVertex2f(-1.0,1.0);
  glVertex2f(1.0,1.0);
  glVertex2f(1.0,-1.0);
  glVertex2f(-1.0,-1.0);
  glEnd();

  glColor3f(0,0,1) ;
  glBegin(GL_POLYGON);
    glVertex2f(-0.1, 0.7);
    glVertex2f(0.9, 0.7);
    glColor3f(1,0,0);
    glVertex2f(0.9, -0.3);
    glVertex2f(-0.1, -0.3);
  glEnd();
  
  /* buffer is ready */
  glutSwapBuffers();
	
  return ;
}

void my_idle(void) {
  return ;
}
