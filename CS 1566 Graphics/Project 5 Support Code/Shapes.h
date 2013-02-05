/***************************************************
 FILE: Shapes.h
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/

#ifndef M_PI
#define M_PI 3.14159265
#endif

#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#if defined(_MSC_VER)
#  include <Gl/glut.h>
#elif defined(__APPLE__)
#  include <GlUT/glut.h>
#endif

#define MAX_LIGHTS  8
#define NUM_OBJECTS 8

/***************************************************
			Struct Definitions
***************************************************/

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

/***************************************************
				Variable Declarations
***************************************************/

OBJECT my_objects[NUM_OBJECTS];
LITE my_lights[MAX_LIGHTS];
int num_objects;
int  num_lights;

// camera variables
CAM my_cam;
GLfloat camx, camy, camz;
GLfloat atx, aty, atz;
GLfloat upx, upy, upz;

//TRUE or FALSE
int firstPersonView;
int bogus;

int crt_render_mode;
int crt_shape, crt_rs, crt_vs;
int crt_transform;

/***************************************************
			Function Definitions
***************************************************/
  
void findNormals(OBJECT *verts);
void shape_normals(GLfloat point[4], GLfloat R, GLfloat r, GLfloat normal[4], int sphere, int cone, int torus);
void cube_normals(OBJECT *po); 
void make_sphere(OBJECT *vert, double ray);
void make_torus(OBJECT *vert, double R, double r);
void make_cone(OBJECT *vert, double height, double ray);
void make_house(OBJECT *vert);
void make_cube_smart(OBJECT *po, double size);

#endif