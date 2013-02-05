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

GLfloat colors [][3] = {
  {0.0, 0.0, 0.0},  /* black   */
  {1.0, 0.0, 0.0},  /* red     */
  {1.0, 1.0, 0.0},  /* yellow  */
  {1.0, 0.0, 1.0},  /* magenta */
  {0.0, 1.0, 0.0},  /* green   */
  {0.0, 1.0, 1.0},  /* cyan    */
  {0.0, 0.0, 1.0},  /* blue    */
  {0.5, 0.5, 0.5},  /* 50%grey */
  {1.0, 1.0, 1.0}   /* white   */
};

/*note the 4 (!) coordinates per vertex below; 
homogeneous coords with w = 1 (see the lecture notes);*/
GLfloat vertices_house[][4] = {
  {0,2,0,1}, 
  {-1,1,1,1}, {1,1,1,1}, {1,1,-1,1}, {-1,1,-1,1},
  {-1,-1,1,1}, {1,-1,1,1}, {1,-1,-1,1}, {-1,-1,-1,1}
};


GLfloat vertices_cube_brute[][4] = {
  {-1,1,1,1}, {1,1,1,1}, {1,1,-1,1}, {-1,1,-1,1},
  {-1,-1,1,1}, {1,-1,1,1}, {1,-1,-1,1}, {-1,-1,-1,1}
  };



// a suggestion; you don't have to use this data structure
GLfloat vertices_cyl[50][50][4];


// a suggestion; you don't have to use this data structure
GLfloat vertices_sph[50][50][4];


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
void make_sphere( double ray, int rs, int vs );
