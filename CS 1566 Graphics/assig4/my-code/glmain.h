/*******************************************************
FILE: glmain.ch
AUTHOR: Zach Sadler - zps6
DOES: Header, almost entirely untouched
PLATFORM: macosx
********************************************************/

#ifndef __CS1566_GLOBALS
#define __CS1566_GLOBALS


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

#define CUBE     1
#define HOUSE    2
#define SPHERE   3
#define CYLINDER 4
#define CONE     5
#define TORUS    6



#define TRANSLATION_MODE 0
#define SCALING_MODE 1
#define ROTATION_MODE 2
#define NONE_MODE 3
#define AXIS_ROTATION_MODE 4
#define REAL_TRANSLATION_MODE 5
#define REAL_SCALING_MODE 6
#define REAL_ROTATION_MODE 7

#define SPIN_ENABLED 1
#define SPIN_DISABLED 0

#define MAX_LIGHTS  8
#define NUM_OBJECTS 30


typedef struct _Object {
  int sid;

  // example object storage arrays for vertex and normals
  GLfloat vertices_cube_smart[8][4];
  GLfloat normals_cube_smart[8][3];
 
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

/*note to cs1566 staff:
colors and vertices below shd actually be in some .c file*/

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

GLfloat vertices_cube_smart[8][4];


// a suggestion; you don't have to use this data structure
GLfloat vertices_cyl[50][50][4];


// a suggestion; you don't have to use this data structure
GLfloat vertices_sph[50][50][4];


GLfloat vertices_axes[][4] = {
	{0.0, 0.0, 0.0, 1.0},  /* origin */ 
	{3.5, 0.0, 0.0, 1.0},  /* maxx */ 
	{0.0, 3.5, 0.0, 1.0}, /* maxy */ 
	{0.0, 0.0, 3.5, 1.0}  /* maxz */ 

};


void glut_setup(void) ;
void gl_setup(void) ;
void my_setup(int argc, char **argv);
void my_display(void) ;
void my_mouse(int button, int state, int mousex, int mousey) ;
void my_reshape(int w, int h) ;
void my_keyboard_up( unsigned char key, int x, int y ) ;
void my_keyboard( unsigned char key, int x, int y ) ;
void my_idle(void) ;
void my_TimeOut(int id) ;

void make_cylinder( double height, double ray, int rs, int vs );
void make_cone( double height, double ray, int rs, int vs );
void make_sphere( double ray, int rs, int vs );
void make_torus(double r1, double r2, int rs, int vs);
void make_cube_smart(OBJECT *, double);

void real_scaling(Matrix3 &, GLdouble, GLdouble, GLdouble);
void real_translation(Matrix3 &, GLdouble, GLdouble, GLdouble);
void real_rotation(Matrix3 &, GLdouble, GLdouble, GLdouble, GLdouble);
void read_spec(char *);


// reuse code from assignment 3 here to do transformations when reading spec
void real_translation_cube(OBJECT *, GLfloat, GLfloat, GLfloat);
void real_scaling_cube(OBJECT *, GLfloat, GLfloat, GLfloat);
void real_rotation_cube(OBJECT *, GLfloat, GLfloat, GLfloat, GLfloat);

void normalize(GLfloat *);

#endif
