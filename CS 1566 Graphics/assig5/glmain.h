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

typedef struct _Object {
	int sid;
	
	GLfloat shape_verts[121][121][4];
	GLfloat shape_normals[121][121][4];
	GLfloat cube_tex[4][2]; 
	GLfloat shape_tex[121][121][2];

	GLfloat shine;
	GLfloat emi[4];
	GLfloat amb[4];
	GLfloat diff[4];
	GLfloat spec[4];
	
	GLfloat translate[4];
	GLfloat scale[4];
	GLfloat rotate[4];
	
}OBJECT;

typedef struct _CAM{
	GLfloat pos[4];
	GLfloat at[4];
	GLfloat up[4];
	
  GLfloat u[4];
  GLfloat v[4];
  GLfloat w[4];


	GLfloat dir[4];
}CAM;

typedef struct _LITE{
	GLfloat amb[4];
	GLfloat diff[4];
	GLfloat spec[4];
	GLfloat pos[4];
	GLfloat dir[3];
	GLfloat angle;
	
}LITE; 



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

void findNormals(OBJECT *verts);
void shape_normals(GLfloat point[4], GLfloat R, GLfloat r, GLfloat normal[4], int sphere, int cone, int torus);
void cube_normals(OBJECT *po); 
void make_sphere(OBJECT *vert, double ray);
void make_cylinder(OBJECT *vert, double ray, double h);
void make_torus(OBJECT *vert, double R, double r);
void make_cone(OBJECT *vert, double height, double ray);
void make_house(OBJECT *vert);
void make_cube_smart(OBJECT *po, double size);

void draw_shape(OBJECT *verts);
void draw(OBJECT *verts);

float dotprod(float v1[], float v2[]);


void draw_axes( void );
#endif
