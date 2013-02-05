/***************************************************
 FILE: Images.h
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/

#ifndef M_PI
#define M_PI 3.14159265
#endif

#ifndef IMAGES_H
#define IMAGES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#if defined(_MSC_VER)
#  include <Gl/glut.h>
#elif defined(__APPLE__)
#  include <GlUT/glut.h>
#endif

#define NUM_TEXTURES 12
#define STRIPE_TEX   0
#define CHECK_TEX    1
#define BRICKIMG_TEX 2
#define WINDOWIMG_TEX  3
#define SHINGLEIMG_TEX	4
#define PLANETIMG_TEX	5
#define SMALLIMG_TEX	6
#define TANIMG_TEX	7

/* checkerboard texture */
#define stripeImageWidth 32
#define checkImageWidth  64
#define checkImageHeight 64
#define smallWidth      256
#define mediumWidth		512
#define largeWidth     1024

GLuint tex_names[NUM_TEXTURES];

static GLubyte stripeImage[4*stripeImageWidth];
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLubyte small_img[mediumWidth*mediumWidth*3] ;
static GLubyte brick_img[largeWidth*largeWidth*3] ;
static GLubyte shingle_img[smallWidth*smallWidth*3] ;
static GLubyte planet_img[mediumWidth*mediumWidth*3] ;
static GLubyte window_img[smallWidth*smallWidth*3] ;
static GLubyte tan_img[smallWidth*smallWidth*3] ;

void texture_setup();

#endif