/***************************************************
FILE: stitcher.h
AUTHOR: gem, loosely based on hwa random skel
DATE: 01/24/08
DOES: header file for cs1566 Assignment 2 -- stitcher
PLATFORM: tested on osx, linux, and vs
***************************************************/

/**********
notes:
VS users: include gl/glut.h below instead of glut.h
OSX users: include glut/glut.h below instead of glut.j
**********/


#include <stdlib.h>
#define _USE_MATH_DEFINES //cause vs is dumb :-(
#include <math.h>
#include <glut/glut.h>


#ifndef min //In VC++ 2008, Ryan got a warning about min redefinition, so let's not redefine it if something else already did; sigh
#define min(a,b) ((a) < (b)? a:b)
#endif

#define FALSE 0 
#define TRUE  1

/* define index constants into the colors array */
#define BLACK   0
#define RED     1
#define YELLOW  2
#define MAGENTA 3
#define GREEN   4
#define CYAN    5
#define BLUE    6
#define GREY    7
#define WHITE   8


#define HOUSE    0
#define CUBE     1
#define TESCUBE  2
#define CYLINDER 3
#define SPHERE   4
#define TORUS    5
#define MESH     6
#define GEODESIC 7
#define CONE 8


void glut_setup(void) ;
void gl_setup(void) ;
void my_setup(void);
void my_display(void) ;
void my_mouse(int button, int state, int mousex, int mousey) ;
void my_reshape(int w, int h) ;
void my_keyboard( unsigned char key, int x, int y ) ;
void my_idle(void) ;
void my_TimeOut(int id) ;

void make_cylinder( double height, double ray, int rs, int vs );
void make_cone( double height, double ray, int rs, int vs );
void make_sphere( double ray, int rs, int vs );
void make_torus(double r1, double r2, int rs, int vs);
