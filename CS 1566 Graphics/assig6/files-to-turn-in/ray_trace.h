/**************************************
FILE: ray_trace.h
AUTHOR: Zach Sadler
EMAIL: zps6@pitt.edu
PLATFORM: macosx
HOMEWORK: 6
**************************************/

#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

// platform specific includes
#ifdef __APPLE__
 #include <GLUT/glut.h>
 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
#else
 #include <GL/glut.h>
 #include <GL/gl.h>
 #include <GL/glu.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

typedef struct color_s
{
	float r, g, b, a;
} color_t;

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

extern GLuint textureId;
extern color_t screen[WINDOW_WIDTH * WINDOW_HEIGHT];

void plotPixel(color_t *screen, int x, int y, float r, float g, float b, float a);
void initGL(void);
void displayScene(void);
void my_display(void);
void my_keyboard(unsigned char key, int x, int y);
void idle(void);
void resizeWindow(int width, int height);

void read_spec(char *fname) ;
void parse_nums(char *buffer, GLfloat nums[]) ;
void parse_bldg(char *buffer);
void parse_light(char *buffer);
void lighting_setup();

int my_raytrace_sphere(OBJECT *s, float *rayStart, float *rayDirection, float result[3]);
void my_raytrace(int mousex, int mousey, GLfloat *results);



#endif
