/***************************************************
 FILE: Transformations.h
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/


#ifndef M_PI
#define M_PI 3.14159265
#endif

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Shapes.h"

#if defined(_MSC_VER)
#  include <Gl/glut.h>
#elif defined(__APPLE__)
#  include <GlUT/glut.h>
#endif

/*************************************************
				Function Definitions
*************************************************/

void real_translation(OBJECT *po, GLfloat x, GLfloat y, GLfloat z);
void real_scaling(OBJECT *po, GLfloat sx, GLfloat sy, GLfloat sz);
void real_rotation(OBJECT *po, GLfloat deg, GLfloat x, GLfloat y, GLfloat z);
void flashlightRotation(GLfloat deg, GLfloat x, GLfloat y, GLfloat z); // rotates the flashlight in place
void my_trans(GLfloat x, GLfloat y, GLfloat z);

#endif