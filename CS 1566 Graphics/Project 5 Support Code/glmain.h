/***************************************************
 FILE: glmain.h
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/

#ifndef M_PI
#define M_PI 3.14159265
#endif

#ifndef GLMAIN_H
#define GLMAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Images.h"
#include "Transformations.h"

#if defined(_MSC_VER)
#  include <Gl/glut.h>
#elif defined(__APPLE__)
#  include <GlUT/glut.h>
#endif

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

#define DRAW_HOUSE  1
#define DRAW_CAN    2

void glut_setup(void) ;
void gl_setup(void) ;
void my_init(int argc, char **argv);
void my_setup(int argc, char **argv);
void myabort(void);
void my_display(void) ;
void my_mouse(int button, int state, int mousex, int mousey) ;
void my_mouse_drag (int mousex, int mousey);
void my_reshape(int w, int h) ;
void my_keyboard_up( unsigned char key, int x, int y ) ;
void my_keyboard( unsigned char key, int x, int y ) ;
void my_idle(void) ;
void my_TimeOut(int id) ;

int display_mode = DRAW_HOUSE;  

void draw_quads(GLfloat vertices[121][121][4], GLfloat normals[121][121][4], GLfloat tex[121][121][2], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic);
void draw_cube(GLfloat vertices[121][121][4], GLfloat normals[121][121][4], GLfloat tex[4][2], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic);
void draw(OBJECT *verts);
void draw_axes();
void draw_objects();

void read_spec(char *fname);
void lighting_setup ();
void normalize(GLfloat *p);

#endif