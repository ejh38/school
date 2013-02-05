/***************************************************
FILE: glmain.h
AUTHOR: gem, loosely based on hwa random skel
DATE: 02/28/08
DOES: header file for cs1566 Assignment 4 -- Modeler
***************************************************/

#ifndef __CS1566_GLOBALS
#define __CS1566_GLOBALS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// may need to change GLUT/glut.h to GL/glut.h on PC or Linux
#include <GLUT/glut.h>


#ifndef min //In VC++ 2008, Ryan got a warning about min redefinition, so let's not redefine it if something else already did; sigh
#define min(a,b) ((a) < (b)? a:b)
#endif

#ifndef M_PI //In VS 2010 M_PI seems to be missing, so we will put it here
#define M_PI 3.14159265
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

void normalize(GLfloat *p);

void lighting_setup();
void print_matrix(float my_matrix[]);

void read_spec(char *fname) ;
void parse_nums(char *buffer, GLfloat nums[]) ;
void parse_bldg(char *buffer);
void parse_light(char *buffer);

void gen_vertices(void);
void my_mult_pt(GLfloat *p);

void draw_axes( void );
#endif
