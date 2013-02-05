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

#include <glut/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "hellomouse.h"
#include "Shape.cpp"    // this is the class I created
#include <math.h>       // for sin and cos

/* define and initialize some global variables */
double my_x = 0, my_y = 0; /* current position */
double window_w = 600, window_h = 450; /* window height and width */
double my_rect_w = 0.1, my_rect_h = 0.1; /* rectangle width and height */

Shape shapes[26];               // the array of shapes that we'll use throughout
unsigned short count = 0;       // keeps track of the curr position in shapes
signed short rect_or_circ = 1;  // if 1 : rect, if -1 : circ
double circle_radius_x = .1;      // radius_y is dependent on this
double circle_radius_y = .13333;    // see the resizing function for where this number came from

int timer_speed = 20;          // time in ms till next drop
double gravity = .0000035;
double deaccel_amount_circ = .00038; // this must be greater than gravity
double deaccel_amount_rect = .00051; // also must be greater than gravity, and optionally greater than circ

short temp_display = 0;        // if 1, display the temporary shape
double temp_rect_width = 0.1, temp_rect_height = 0.1;
double temp_circ_radius_x = .1, temp_circ_radius_y = .13333;

double thickness_step = .025;  // amount you adjust by when IJKL'ing

double red = 1;
double blue = 1;
double strobe = -1, strobe_amount = .005;

int old_mouse_x, old_mouse_y;
double mouse_dx, mouse_dy, dy_divisor = 12000, dx_divisor = 15000;


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
  glutInitWindowPosition(300,100);
  glutCreateWindow("zps6 Assignment 1");

  /*initialize typical callback functions */
  glutDisplayFunc( my_display );
  glutReshapeFunc( my_reshape ); 
  glutIdleFunc( my_idle );
  glutMouseFunc( my_mouse );	
  glutKeyboardFunc( my_keyboard );	
  glutTimerFunc( timer_speed, my_TimeOut, 0);/* schedule a my_TimeOut call with the ID 0 in 20 seconds from now */
  glutPassiveMotionFunc(my_motion);
  glutMotionFunc(my_motion);

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
/* DONE!! */
void my_display(void) {
  /* clear the buffer */
  glClear(GL_COLOR_BUFFER_BIT) ;
  
  // iterate through the (up to) 25 shapes + 1 temp
  for (int i = 0; i < (25 + temp_display); i++) {
    // type 1 is rectangle
    if (shapes[i].get_type() == 1) { 
      glColor3f(0,0,shapes[i].get_color()) ;  // make it blue
      glRectf(shapes[i].get_x(), shapes[i].get_y(), shapes[i].get_x() + shapes[i].get_width(), shapes[i].get_y() + shapes[i].get_height());
    } // end rect
    // type -1 is circle
    else if (shapes[i].get_type() == -1) { 
      glColor3f(shapes[i].get_color(),0,0); // make it red
      glBegin(GL_TRIANGLE_FAN); // start a fan strip
      glVertex2d(shapes[i].get_x(), shapes[i].get_y());  // centered on the mouse click

      // then once for each of the 360 degrees, make a triangle fan strip using sin, cos, and the radius
      // note that radius_x and radius_y are different because the window is not square.
      // when the window is resized, radius_y is adjusted to keep the shape a circle and not an ellipse.
      for (int j = 0; j < 360; j += 6) {
        glVertex2d(shapes[i].get_x() + cos(j)*shapes[i].get_width(), shapes[i].get_y() + sin(j)*shapes[i].get_height());   
      }
      glEnd();  // done drawing the 'circle'
    } // end circ
  } // end iterating

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
  temp_circ_radius_y = window_w * temp_circ_radius_x / window_h;    // this keeps the proportion a circle

  return;
}


// controls the temporary shape at the cursor (if turned on)
// as well as getting the mouse dy for throwing the balls up or down with initial velocity
void my_motion(int x, int y)
{
  if (temp_display) {
    if (rect_or_circ == 1)
      shapes[25].set_shape(rect_or_circ, x/window_w, (window_h - y)/window_h, temp_rect_width, temp_rect_height);
    else
      shapes[25].set_shape(rect_or_circ, x/window_w, (window_h - y)/window_h, temp_circ_radius_x, temp_circ_radius_y);
    
    shapes[25].set_color(1);

    glutPostRedisplay();
  }

  mouse_dx = old_mouse_x - x;
  mouse_dy = old_mouse_y - y;
  old_mouse_x = x;
  old_mouse_y = y;
}


/* called if mouse event (i.e., mouse click) */
/* TODO: correct my_y so we draw exactly where the mouse clicked */
/* DONE! */
/* TODO for EC: have more fun in here */
void my_mouse(int b, int s, int x, int y) {
  
  switch (b) {            /* b indicates the button */
  case GLUT_LEFT_BUTTON:
    if (s == GLUT_UP)  {      // let go of the button
      my_x = x;
      my_y = window_h - y;    // this is the needed correction

      // this if statement is used so the circle doesn't spawn with the center at the mouse click
      // instead, I want the circle to be 'above' the mouse click, just as rectangles are spawned.
      if (rect_or_circ == 1) 
        shapes[count].set_shape(rect_or_circ, my_x/window_w, my_y/window_h, temp_rect_width, temp_rect_height);
      else
        shapes[count].set_shape(rect_or_circ, my_x/window_w, my_y/window_h + circle_radius_y, temp_circ_radius_x, temp_circ_radius_y);
      
      if (mouse_dy > .9 || mouse_dy < -.9)                  // if you've moved the mouse up or down
        shapes[count].set_y_velocity(-mouse_dy/dy_divisor);   // then start with some initial velocity accordingly
      else     
        shapes[count].set_y_velocity(gravity);                // otherwise start with gravity

      if (mouse_dx > .9 || mouse_dx < -.9)
        shapes[count].set_x_velocity(-mouse_dx/dx_divisor);
      else
        shapes[count].set_x_velocity(0);
      
      shapes[count].set_color(1);                           // start out fully illuminated (see strobe effect)

      count++;              // increase the count for the array
      count = count % 25;   // circle around  the array if necessary
      rect_or_circ *= -1;   // toggle between rectangles and circles

      my_motion(x, y);
      my_display();

    }
  }
}

// returns a double between low and high
double random_number(double low, double high)
{
  double temp = (double)rand() / RAND_MAX;  // get our random int, divide it down to a double 0-1
  return (temp * (high - low)) + low;       // multiply it to get in our range, and add it to low
}

// a fun effect, throws the shapes upwards with varying velocities
void explode()
{
  for (int m = 0; m < 25; m++)
      if (shapes[m].get_type() != 0) {                            // don't do the unintialized shapes
        shapes[m].set_y_velocity(random_number(-.005,-gravity));    // but all the others get random velocity
        shapes[m].set_x_velocity(random_number(-.005,-gravity));  // for x and y
      }
      return ;
}


/* called if keyboard event (keyboard key hit) */
/* TODO for EC: do something fun in here */
void my_keyboard(unsigned char c, int x, int y) {
  switch (c) {  /* c is the key that is being hit */

  // creates an 'explosion' that randomly propels the shapes upwards
  case 'e': {
    explode();
  }
  break;

  // clears the screen
  case 'c': {
    for (int m = 0; m < 25; m++)
      shapes[m].set_shape(0,0,0,0,0); // just reset the array to all 'zero' shapes
  }
  break;

  // turns on the display of the temporary shape at the mouse cursor
  case 't': {
    temp_display = (temp_display + 1) % 2;    // switch between 0 and 1
    my_motion(x, y);                          // need to call this also to get it working
  }
    break;

  // turns on the 'strobe' effect of color changing
  case 's': {
    strobe = -strobe;   // toggle
  }
  break;

  // increases rectangle height/circle radius
  case 'i': {
    if (temp_rect_height < .5 && rect_or_circ == 1)
      temp_rect_height += thickness_step;
    else if (temp_circ_radius_x < .25 && rect_or_circ == -1) {
      temp_circ_radius_x += thickness_step;
      temp_circ_radius_y = window_w * temp_circ_radius_x / window_h;
    }
    my_motion(x, y);
   }
   break;

   // decreases rectangle width/circle radius
   case 'j': {
    if (temp_rect_width > thickness_step*2 && rect_or_circ == 1)
      temp_rect_width -= thickness_step;
    else if (temp_circ_radius_x > thickness_step*2 && rect_or_circ == -1) {
      temp_circ_radius_x -= thickness_step;
      temp_circ_radius_y = window_w * temp_circ_radius_x / window_h;
    }
    my_motion(x, y);
   }
   break;

  // decreases rectangle height/circle radius
  case 'k': {
    if (temp_rect_height > thickness_step*2 && rect_or_circ == 1)
      temp_rect_height -= thickness_step;
    else if (temp_circ_radius_x > thickness_step*2 && rect_or_circ == -1) {
      temp_circ_radius_x -= thickness_step;
      temp_circ_radius_y = window_w * temp_circ_radius_x / window_h;
    }
    my_motion(x, y);
   }
   break;
   
   // increases rectangle width/circle radius
  case 'l': {
    if (temp_rect_width <.5 && rect_or_circ == 1)
      temp_rect_width += thickness_step;
    else if (temp_circ_radius_x < .25 && rect_or_circ == -1) {
      temp_circ_radius_x += thickness_step;
      temp_circ_radius_y = window_w * temp_circ_radius_x / window_h;
    }
    my_motion(x, y);
   }
   break;
  }
}

/* called if timer event */
/* TODO for EC: do something fun in here */
// DONE
void my_TimeOut(int id) { 

  // iterate through
  for (int k = 0; k < 25; k++) {

    if (strobe == 1) {                                              // if you're strobing
      shapes[k].set_color(shapes[k].get_color() - strobe_amount);   // then decrease the color slowly
      if (shapes[k].get_color() < 0)                                // but if you go negative
        shapes[k].set_color(1);                                     // start back at 1
    }
    
    // different parameters used for rectangles and circles
    if (shapes[k].get_type() == 1)
      shapes[k].handle_gravity(timer_speed, deaccel_amount_rect, gravity, 0);
    else if (shapes[k].get_type() == -1)
      shapes[k].handle_gravity(timer_speed, deaccel_amount_circ, gravity, shapes[k].get_height());
  
  } // end iteration
 
  glutTimerFunc(timer_speed, my_TimeOut, 0); // keeps the timer moving, at timer_speed ms
  glutPostRedisplay();                       // re-draw the scene

}
