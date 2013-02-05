/**************************************************************************
File: hellomouse.c
Does: basic drawing and interaction in OpenGL/GLUT
Author: gem, based on hwa's
Date: 01/08/08
**************************************************************************/
/**********
notes:
VS users: include opengl/glut.h below instead of GL/glut.h
OSX users: include glut/glut.h below instead of GL/glut.h
**********/



#include <GL/glut.h>
#include <stdio.h>
#include "hellomouse.h"


/* define and initialize some global variables */
double my_x = 0, my_y = 0; /* current position */
int window_w = 400, window_h = 300; /* window height and width */
double my_rect_w = 0.1, my_rect_h = 0.1; /* rectangle width and height */



/*Typical OpenGL/GLUT Main function */ 
int main(int argc, char **argv) { /* program arguments */

  /* initialize GLUT and OpenGL; Must be called first */
  glutInit( &argc, argv ) ;
  
  /* our own initializations; we'll define these setup procedures */
  glut_setup() ;  
  gl_setup() ;
  my_setup();

  /* turn control over to GLUT */
  glutMainLoop() ;

  return(0) ; /* make the compiler happy */
}



/* Typical function to set up GLUT*/
void glut_setup(void) {

  /* specify display mode -- here we ask for double buffering and RGB coloring */
  glutInitDisplayMode (GLUT_DOUBLE |GLUT_RGB);

  /* make a window of size window_w by window_h; title of "GLUT Basic Interaction" placed at top left corner */
  glutInitWindowSize(window_w, window_h);
  glutInitWindowPosition(0,0);
  glutCreateWindow("GLUT Basic Interaction");

  /*initialize typical callback functions */
  glutDisplayFunc( my_display );
  glutReshapeFunc( my_reshape ); 
  glutIdleFunc( my_idle );
  glutMouseFunc( my_mouse );	
  glutKeyboardFunc( my_keyboard );	
  glutTimerFunc( 20000, my_TimeOut, 0);/* schedule a my_TimeOut call with the ID 0 in 20 seconds from now */
  return ;
}

/* Typical function to set up OpenGL */
/* For now, ignore the contents of function */
void gl_setup(void) {

  /* specifies a background color: black in this case */
  glClearColor(0,0,0,0) ;

  /* setup for simple 2d projection */
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  /* map unit square to viewport window */
  gluOrtho2D(0.0, 1.0, 0.0, 1.0); 

  return ;
}


void my_idle(void) {
  return ;
}


void my_setup(void) {
  return;
}




/* drawing function */
/* TODO: draw some other shape, use some other colors */
/* TODO part 2: draw at the location of the mouse click */
void my_display(void) {
  /* clear the buffer */
  glClear(GL_COLOR_BUFFER_BIT) ;
  
  glColor3f(0,0,1) ; /* (Red, Green, Blue); so here we ask for Blue */

  /* draw small rectangle; specify two opposing corners as arguments*/
  /* note how the rectangle coordinates we pass as arguments are mapped to the window coordinates */
  /* basically, we need to map x values between (0,window_w) to the (0,1) interval etc. */
  glRectf( my_x/window_w, my_y/window_h, my_x/window_w + my_rect_w, my_y/window_h + my_rect_h);


  /* buffer is ready; show me the money! */

  glutSwapBuffers();
	
  return ;
}





/* called if resize event (i.e., when we create the window and later whenever we resize the window) */ 
void my_reshape(int w, int h) {
  /* define the viewport to be the entire window */
  glViewport (0, 0, w, h); 
  window_w = w;
  window_h = h;
  return;
}





/* called if mouse event (i.e., mouse click) */
/* TODO: correct my_y so we draw exactly where the mouse clicked */
/* TODO for EC: have more fun in here */
void my_mouse(int b, int s, int x, int y) {
  switch (b) {            /* b indicates the button */
  case GLUT_LEFT_BUTTON:
    if (s == GLUT_DOWN)  {    /* button pressed */
      printf("Left button pressed at %d %d\n", x, y);
      my_x = x; 
      my_y = y;
      my_display();

    }
    else if (s == GLUT_UP) { /* button released */
      printf("Left button released\n");
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if (s == GLUT_DOWN)  {    /* button pressed */
      printf("Right button pressed\n");
    }
    else if (s == GLUT_UP) { /* button released */
      printf("Right button released\n");
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    if (s == GLUT_DOWN)  {    /* button pressed */
      printf("Middle button pressed at %d %d\n", x, y);
    }
    else if (s == GLUT_UP) { /* button released */
      printf("Middle button released\n");
    }
    break;

  }
}


/* called if keyboard event (keyboard key hit) */
/* TODO for EC: do something fun in here */
void my_keyboard(unsigned char c, int x, int y) {
  switch (c) {  /* c is the key that is being hit */
  case 'c': {
    printf("C key is hit\n");
  }
    break;
   case 'y': {
    printf("Y key is hit\n");
  }
    break;
    /* and so on*/
  }


}


/* called if timer event */
/* TODO for EC: do something fun in here */
void my_TimeOut(int id) { 
  /* id is the id of the timer; you can schedule as many timer events as you want in the callback setup section of glut_setup */

  /*...you could use this timer event to advance the state of animation incrementally */
  /* if animating you shd replace the 20 secs with something smaller, like 20 msec */
  /* but anyway, right now it only displays a benign message */
  printf("Tick! It's been 20 seconds: benign timer at your service!\n");
 
  glutTimerFunc(20000, my_TimeOut, 0);/* schedule next timer event, 20 secs from now */

}
