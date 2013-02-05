/*********************************
 * fireworks.h
 * Contains the structs for the main program, and some MACROs.
 * Also contains function prottypes, after the structs.
 * Heavily commented, but also pretty tentative
 */

#ifndef _FIREWORKS_20_H_
#define _FIREWORKS_20_H_
#endif

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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

#define NUM_NOZZLES 7

#define CYLINDER_RS 10
#define CYLINDER_VS 10
#define CUBE_RS 3
#define CUBE_VS 1
#define SPHERE_RS 20
#define SPHERE_VS 20
#define CONE_RS 10
#define CONE_VS 10
#define TORUS_RS 10
#define TORUS_VS 10

// for making your own firework
#define RADIUS 0
#define DENSITY 1
#define QUANTITY 2
#define CUBE_SIZE 3
#define AFTER_COUNTER 5

// some MACROs for various sound types
#define BANG 0
#define BOOM 1
#define SIZZLE 2
#define CRACK 3
#define POP 4
#define SONG 5
#define etc 6

// colors
#define BLACK   0
#define RED     1
#define YELLOW  2
#define MAGENTA 3
#define GREEN   4
#define CYAN    5
#define BLUE    6
#define GREY    7
#define WHITE   8

// macros for shape_id's
#define SPHERE 0
#define CUBE 1
#define CYLINDER 2
#define CONE 3
#define TORUS 4
#define HOUSE lololololjk

// macros for explosion shapes
#define WILLOW 0
#define BURST 1
#define SPARKLER 2
#define you get the idea

// because why not
#define min(a,b) ((a) < (b)? a:b)
#define max(a,b) ((a) > (b)? a:b)

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


// a generic way to describe the various 'bang', 'sizzle', and 'boom's
// as well as the music (1812 overture, etc)
typedef struct _Sound {
	short type;						// see the MACROs above
	GLfloat duration;			// how long should the sound last
	GLfloat volume;				// because some will be louder than others

}SOUND;

// this is the basic cube/sphere/cone/cylinder/torus shape class
// it may turn out that we use the same shape for everything,
// (ie, all are cubes or all are spheres) and then we won't need this
typedef struct _Shape {
	short shape_id;										// to distinguish between shapes
	
	GLfloat shape_verts[12][12][4];		// vertices for the shape

}SHAPE;

// a wrapper around shape that includes info about color, brightness, etc
typedef struct _Particle {
	GLfloat init_color[3];					// the starting/base color
	GLfloat init_brightness[3];			// initial value/brightness
	short single_color;							// if true, then the color doesn't change
	GLfloat end_color[3];						// otherwise, this is the end color
	GLfloat end_brightness[3];			// and end value/brightness
	short interpolate_how;					// a flag to determine how to go init->end
	

	GLfloat duration;								// how long the particle is visible

	GLfloat translation[3];						// this is direction and velocity rolled into one

	SHAPE shape;										// which shape is it?

}PARTICLE;

// the component of a firework between launch and explosion
typedef struct _Fuse {
	GLfloat hangtime;			// time between ignition and explosion
	GLfloat velocity;			// initial velocity out of the nozzle
	// note, the above two could easily be consoldiated together

	short trail;							// a boolean to determine if there is a trail
	GLfloat trail_color[4];		// if there is a trail, then what color is it?

	GLfloat direction;		// determines the initial angle the fireowrk is shot

	SOUND sound;					// the sound that the fuse will make (if any)

}FUSE;

// the factors that determine the actual explosion
typedef struct _Explosion {
	GLfloat radius;			// the distance the farthest particle will travel
	GLfloat density;		// a measure of how close particles will be to each other
	int quantity;		// how many particles comprise the explosion

	PARTICLE *particles;	// the array of particles, to be malloc'd later
												// once we know 'quantity'
	
	GLfloat cube_size;
	GLfloat start_x;
	GLfloat start_y;

 	short fizz; 					//fizz for specific explosion
	short shape;				// willow, burst, boom, sparkler, etc
	int counter;				// used to keep track of how long the firework has been exploding
	int after_counter;	// how long the explosion stays on screen after stopping

	SOUND sound;				// the sound that the explosion will make

}EXPLOSION;

// the firework!
typedef struct _Firework {
	short id;							// because we might want to keep track of which one it is
	short nozzle;					// which nozzle it comes out of (probably not necessary)

	FUSE fuse;						// the fuse!
	EXPLOSION explosion;	// the explosion!

}FIREWORK;

// nozzle class for launch point of firework
typedef struct _Nozzle {
	short cur_firework;				// position in the firework array
	short nozzle_id;				//nozzle id to specify
	
	GLfloat x;
	GLfloat y;
	GLfloat z;

	FIREWORK *all_fireworks;	//array of the fireworks for that nozzle
	SHAPE shape;					//cylinder of nozzle

}NOZZLE;



void initGL(void);
void my_display(void);
void my_keyboard(unsigned char key, int x, int y);
void make_cube_smart(SHAPE *po, double size );

void draw_shape(SHAPE *verts,GLfloat *color);
void draw(SHAPE *verts);
void draw_objects(SHAPE *my_objects, int num_objects);
void draw_nozzles(void);
void draw_particles(void);
void draw_explosion(void);


void draw_quads(GLfloat vertices[12][12][4], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, GLfloat *color);

void my_setup(void);
void setup_nozzles(void);
void setup_particles(void);
void spawn_particle(int i);

void setup_BASS(void);

void print_cur(void);

void my_time_out(int id);

void make_particle(PARTICLE *po, GLfloat *init_color, GLfloat *init_brightness,
                            short single_color, GLfloat *end_color, 
                            GLfloat *end_brightness, short interpolate_how, 
                            GLfloat duration, SHAPE shape, 
                            GLfloat trans_x, GLfloat trans_y, GLfloat trans_z);

void make_explosion(EXPLOSION *po, GLfloat radius, GLfloat density, 
                          int quantity, GLfloat cube_size, int after_counter,
                          short shape, SOUND sound, GLfloat start_x, GLfloat start_y);

void make_nozzle(NOZZLE* noz, double ray, double h, int id);
void make_sphere(SHAPE *vert, double ray);
void make_cylinder(SHAPE *vert, double ray, double h);
void make_torus(SHAPE *vert, double R, double r);
void make_cone(SHAPE *vert, double height, double ray);
void make_house(SHAPE *vert);
void make_cube_smart(SHAPE *po, double size);

void real_translation(SHAPE *po, GLfloat x, GLfloat y, GLfloat z);
void real_scaling(SHAPE *po, GLfloat sx, GLfloat sy, GLfloat sz);
void real_rotation(SHAPE *po, GLfloat deg, GLfloat x, GLfloat y, GLfloat z);
