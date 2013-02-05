/**************************************
FILE: glmain.c
AUTHOR: Zach Sadler
EMAIL: zps6@pitt.edu
PLATFORM: macosx
HOMEWORK: 5
**************************************/

#include "glmain.h"
#define my_assert(X,Y) ((X)?(void) 0:(printf("error:%s in %s at %d", Y, __FILE__, __LINE__), myabort()))

#define min(a,b) ((a) < (b)? a:b)
#define FALSE 0 
#define TRUE  1
#define MAX_LIGHTS  8
#define NUM_OBJECTS 8


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

GLfloat vertices_axes[][4] = {
	{0.0, 0.0, 0.0, 1.0},  /* origin */ 
	{5.0, 0.0, 0.0, 1.0},  /* maxx */ 
	{0.0, 5.0, 0.0, 1.0}, /* maxy */ 
	{0.0, 0.0, 5.0, 1.0}  /* maxz */ 

};

void make_cube_smart(OBJECT *po, double size );

void real_translation(OBJECT *po, GLfloat x, GLfloat y, GLfloat z);
void real_scaling(OBJECT *po, GLfloat sx, GLfloat sy, GLfloat sz);
void real_rotation(OBJECT *po, GLfloat deg, GLfloat x, GLfloat y, GLfloat z);

OBJECT my_objects[NUM_OBJECTS];
OBJECT small_spheres[100];
LITE my_lights[MAX_LIGHTS];
int num_objects = 0;
int num_spheres = 0;
int num_lights = 0;
int num_clicks = 0;

GLfloat start_lines[100][4];
GLfloat click_lines[100][4];

// camera variables
CAM my_cam;
GLfloat camx, camy, camz;
GLfloat atx, aty, atz;
GLfloat upx, upy, upz;

//TRUE or FALSE
int firstPersonView;

int crt_render_mode;
int crt_shape, crt_rs, crt_vs;
int crt_transform;

void myabort(void) {
  abort();
  exit(1); /* exit so g++ knows we don't return. */
} 

int main(int argc, char** argv)
{ 
  setbuf(stdout, NULL);   /* for writing to stdout asap */
  glutInit(&argc, argv);

  my_setup(argc, argv);  
  glut_setup();
  gl_setup();

  glutMainLoop();
  return(0);
}


void glut_setup (){

  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  
  glutInitWindowSize(700,700);
  glutInitWindowPosition(20,20);
  glutCreateWindow("Zach Sadler - zps6 - HW 5");

  /* set up callback functions */
  glutDisplayFunc(my_display);
  glutReshapeFunc(my_reshape);
  glutMouseFunc(my_mouse);
  glutMotionFunc(my_mouse_drag);
  glutKeyboardFunc(my_keyboard);
  glutIdleFunc( my_idle );	

  return;
}

void gl_setup(void) {

  // enable depth handling (z-buffer)
  glEnable(GL_DEPTH_TEST);

  // enable auto normalize
  glEnable(GL_NORMALIZE);

  // define the background color 
  glClearColor(0,0,0,1);

  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  gluPerspective( 40, 1.0, 1, 200.0);
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;  // init modelview to identity

  // toggle to smooth shading (instead of flat)
  glShadeModel(GL_SMOOTH); 
  lighting_setup();


  return ;
}

void my_setup(int argc, char **argv){

  firstPersonView = 1;
  num_objects = num_lights = 0;

  // initialize global shape defaults and mode for drawing
  crt_render_mode = GL_POLYGON;
  crt_shape = 0;

  crt_rs = 90;
  crt_vs = 90; 
 
  //If you want to allow the user to type in the spec file
  //then modify the following code.
  //Otherwise, the program will attempt to load the file as specified
  //on the command line:
  //EX: ./glmain spec3
  my_assert(argc >1, "need to supply a spec file");
  read_spec(argv[1]);
  return;
}

void parse_floats(char *buffer, GLfloat nums[]) {
  int i;
  char *ps;

  ps = strtok(buffer, " ");
  for (i=0; ps; i++) {
    nums[i] = atof(ps);
    ps = strtok(NULL, " ");
    //printf("read %f ",nums[i]);
  }

}

void parse_obj(char *buffer){
  OBJECT *po;
  char *pshape, *pshine, *pemi, *pamb, *pdiff, *pspec, *ptranslate, *pscale, *protate;

  my_assert ((num_objects < NUM_OBJECTS), "too many objects");
  po = &my_objects[num_objects++];

  pshape  = strtok(buffer, " ");
  //printf("pshape is %s\n",pshape);

  ptranslate    = strtok(NULL, "()");  strtok(NULL, "()");
  pscale        = strtok(NULL, "()");  strtok(NULL, "()"); 
  protate       = strtok(NULL, "()");  strtok(NULL, "()");  

  pshine  = strtok(NULL, "()");strtok(NULL, "()");
  //printf("pshine is %s\n",pshine);
 
  pemi    = strtok(NULL, "()");  strtok(NULL, "()"); 
  pamb    = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdiff   = strtok(NULL, "()");  strtok(NULL, "()"); 
  pspec   = strtok(NULL, "()");  strtok(NULL, "()"); 


  po->sid  = atoi(pshape);
  po->shine = atof(pshine);

  parse_floats(ptranslate, po->translate);
  parse_floats(pscale, po->scale);
  parse_floats(protate, po->rotate);

  parse_floats(pemi, po->emi);
  parse_floats(pamb, po->amb);
  parse_floats(pdiff, po->diff);
  parse_floats(pspec, po->spec);

  // use switch to create your objects, cube given as example
  switch (po->sid){
    case 1: //cube
      make_cube_smart(po, 1);
      break;
     case 2: // makes house
      make_house(po);
      break;
    case 3:
      make_sphere(po, 1);
      break;
    case 4:
      make_cylinder(po, 1, 1);
      break;
    case 5:
      make_cone(po, 1, 1);
      break;
  }
  
  // scale, rotate, translate using your real tranformations from assignment 3 depending on input from spec file
  
  real_scaling(po, po->scale[0], po->scale[1], po->scale[2]);  
  real_rotation(po, po->rotate[0], 1, 0, 0);
  real_rotation(po, po->rotate[1], 0, 1, 0);
  real_rotation(po, po->rotate[2], 0, 0, 1);
  real_translation(po, po->translate[0], po->translate[1], po->translate[2]);
  
  printf("read object\n");
}

void parse_camera(char *buffer){
  CAM *pc;
  char *ppos, *plook, *pup;
  int tempsum;
  int i, j;

  pc = &my_cam;

  strtok(buffer, "()");
  ppos  = strtok(NULL, "()");  strtok(NULL, "()"); 
  plook  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pup  = strtok(NULL, "()");  strtok(NULL, "()"); 

  parse_floats(ppos, pc->pos);
  parse_floats(plook, pc->at);
  parse_floats(pup, pc->up);

  pc->at[0] += pc->pos[0];
  pc->at[1] += pc->pos[1];
  pc->at[2] += pc->pos[2];

  pc->dir[0] = pc->at[0] - pc->pos[0];
  pc->dir[1] = pc->at[1] - pc->pos[1];
  pc->dir[2] = pc->at[2] - pc->pos[2];
  normalize(pc->dir);
  printf("read camera\n");


  for (i = 0; i < 3; i++) {
    pc->w[i] = pc->at[i] - pc->pos[i];
  }
  for (j = 0; j < 3; j++) {
    tempsum += pc->w[j];
  }
  if (tempsum != 0) {
    normalize(pc->w);
  }
  tempsum = 0;
  for (i = 0; i < 3; i++) {
    pc->v[i] = pc->up[i] - dotprod(pc->up, pc->w)*pc->w[i];
  }  
  for (j = 0; j < 3; j++) {
    tempsum += pc->v[j];
  }
  if (tempsum != 0) {
    normalize(pc->v);
  } 


  GLdouble newX, newY, newZ;

  newX = pc->v[1]*pc->w[2] - pc->v[2]*pc->w[1];
  newY = pc->v[2]*pc->w[0] - pc->v[0]*pc->w[2];
  newZ = pc->v[0]*pc->w[1] - pc->v[1]*pc->w[0];

  pc->u[0] = newX;
  pc->u[1] = newY;
  pc->u[2] = newZ;



}

void parse_light(char *buffer){
  LITE *pl;
  char *pamb, *pdiff, *pspec, *ppos, *pdir, *pang;
  my_assert ((num_lights < MAX_LIGHTS), "too many lights");
  pl = &my_lights[++num_lights];

  strtok(buffer, "()");
  pamb  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdiff = strtok(NULL, "()");  strtok(NULL, "()"); 
  pspec = strtok(NULL, "()");  strtok(NULL, "()"); 
  ppos  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pdir  = strtok(NULL, "()");  strtok(NULL, "()"); 
  pang  = strtok(NULL, "()");

  parse_floats(pamb, pl->amb);
  parse_floats(pdiff, pl->diff);
  parse_floats(pspec, pl->spec);
  parse_floats(ppos, pl->pos);
  if (pdir) {
    parse_floats(pdir, pl->dir);
    pl->angle = atof(pang);
    //printf("angle %f\n", pl->angle);
  }
  else
    pl->dir[0]= pl->dir[1]= pl->dir[2] =0;
  printf("read light\n");

}

/* assuming the spec is going to be properly written
   not error-checking here */
void read_spec(char *fname) {
  char buffer[300];
  FILE *fp;

  fp = fopen(fname, "r");
  my_assert(fp, "can't open spec");
  while(!feof(fp)){
    fgets(buffer, 300, fp);
    //printf("read line: %s\n", buffer);
    switch (buffer[0]) {
    case '#':
      break;
    case '1': // house
    case '2': //cube
    case '3': // sphere 
    case '4': // cone
    case '5': // torus
      //read in the shape
    {
      printf("parse object");
      parse_obj(buffer);
    } break;

    case 'l':
      parse_light(buffer);
      break;

    case 'c':
      parse_camera(buffer);
      break;

    default:
      break;
    }
  }
}

void lighting_setup () {
  int i;
  GLfloat globalAmb[]     = {.1, .1, .1, .1};

  // create flashlight
  GLfloat amb[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat dif[] = {0.8, 0.8, 0.8, 1.0};
  GLfloat spec[] = {5.0, 5.0, 5.0, 1.0};

  //enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  // reflective propoerites -- global ambiant light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

  // this was for the flashlights

 // glLightfv(GL_LIGHT0, GL_POSITION, my_cam.at);
 // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, my_cam.dir);

 // glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
 // glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
 // glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
 // glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);

 // glEnable(GL_LIGHT0);

  // setup properties of lighting
  for (i=1; i<=num_lights; i++) {
    glEnable(GL_LIGHT0+i);
    glLightfv(GL_LIGHT0+i, GL_AMBIENT, my_lights[i].amb);
    glLightfv(GL_LIGHT0+i, GL_DIFFUSE, my_lights[i].diff);
    glLightfv(GL_LIGHT0+i, GL_SPECULAR, my_lights[i].spec);
    glLightfv(GL_LIGHT0+i, GL_POSITION, my_lights[i].pos);
    if ((my_lights[i].dir[0] > 0) ||  (my_lights[i].dir[1] > 0) ||  (my_lights[i].dir[2] > 0)) {
      glLightf(GL_LIGHT0+i, GL_SPOT_CUTOFF, my_lights[i].angle);
      glLightfv(GL_LIGHT0+i, GL_SPOT_DIRECTION, my_lights[i].dir);
    }
  }

}

void my_reshape(int w, int h) {
  // ensure a square view port
  glViewport(0,0,min(w,h),min(w,h)) ;
  return ;
}

//For the following 3 functions, do with them as you like.
//You will have to somehow rotate / translate / scale\
//the object as specified in the spec file.

void my_rev(GLfloat deg, GLfloat x, GLfloat y, GLfloat z) 
{
  GLfloat theta = (deg * M_PI/180);
  
  GLfloat aX = my_cam.at[0]; // x position
  GLfloat aY = my_cam.at[1]; // y position
  GLfloat aZ = my_cam.at[2]; // z position
  
  if(x == 1) // rotate X
  {
    
    my_cam.at[1] = aY * cos(theta) - aZ * sin(theta); 
    my_cam.at[2] = aZ * cos(theta) + aY * sin(theta);
    
  }
  else if(y ==1) // rotate Y
  {
    
    my_cam.at[0] = aX * cos(theta) + aZ * sin(theta);
    my_cam.at[2] = aZ * cos(theta) - aX * sin(theta);
    
  }
  else if (z ==1){ // rotate Z
    
    my_cam.at[0] = aX * cos(theta) - aY * sin(theta); 
    my_cam.at[1] = aX * sin(theta) + aY * cos(theta);
    
    
  }
  
}

void my_trans(GLfloat x, GLfloat y, GLfloat z) {
  
  my_cam.pos[0] = my_cam.pos[0] + x;
  my_cam.pos[1] = my_cam.pos[1] + y;
  my_cam.pos[2] = my_cam.pos[2] + z;
  
  my_cam.at[0] += x;
  my_cam.at[1] += y;
  my_cam.at[2] += z;

}

void my_scale(GLfloat x, GLfloat y, GLfloat z) {

}


void real_translation(OBJECT *po, GLfloat x, GLfloat y, GLfloat z) { // translates the shapes
  
  int i, j;
  
  for(i = 0; i <= crt_vs; i++)
  {
    for(j = 0; j <= crt_rs; j++)
    {
      po->shape_verts[i][j][0] += x; // translate across x
      po->shape_verts[i][j][1] += y; // translates across y
      po->shape_verts[i][j][2] += z; // translates across z
      
    }
  }
  
}

void real_scaling(OBJECT *po, GLfloat sx, GLfloat sy, GLfloat sz) { // scales the object
  
  int i, j;
  
  for(i = 0; i <= crt_vs; i++)
  {
    for(j = 0; j <= crt_rs; j++)
    {
      po->shape_verts[i][j][0] = po->shape_verts[i][j][0] * sx; // scales x
      po->shape_verts[i][j][1] = po->shape_verts[i][j][1] * sy; // scales y
      po->shape_verts[i][j][2] = po->shape_verts[i][j][2] * sz; // scales z
      po->shape_normals[i][j][0] = po->shape_normals[i][j][0] * sx; // scales x
      po->shape_normals[i][j][1] = po->shape_normals[i][j][1] * sy; // scales y
      po->shape_normals[i][j][2] = po->shape_normals[i][j][2] * sz; // scales z
      
    }
  }
  
}

void real_rotation(OBJECT *po, GLfloat deg, GLfloat x, GLfloat y, GLfloat z) { // rotates the shapes
  
  GLfloat theta = (deg * M_PI/180); // deg to rotate by
  int i, j;
  
  for(i = 0; i <= crt_vs; i++)
  {
    for(j = 0; j <= crt_rs; j++)
    {
      GLfloat X = po->shape_verts[i][j][0];
      GLfloat Y = po->shape_verts[i][j][1];
      GLfloat Z = po->shape_verts[i][j][2];
      
      GLfloat nX = po->shape_normals[i][j][0];
      GLfloat nY = po->shape_normals[i][j][1];
      GLfloat nZ = po->shape_normals[i][j][2];
      
      if(x == 1) // rotate X
      {
  
        po->shape_verts[i][j][1] = Y * cos(theta) - Z * sin(theta); 
        po->shape_verts[i][j][2] = Z * cos(theta) + Y * sin(theta);
        
        po->shape_normals[i][j][1] = nY * cos(theta) - nZ * sin(theta); 
        po->shape_normals[i][j][2] = nZ * cos(theta) + nY * sin(theta);
      }
      else if(y ==1) // rotate Y
      {
                   
        po->shape_verts[i][j][0] = X * cos(theta) + Z * sin(theta);
        po->shape_verts[i][j][2] = Z * cos(theta) - X * sin(theta);
        
        po->shape_normals[i][j][0] = nX * cos(theta) + nZ * sin(theta);
        po->shape_normals[i][j][2] = nZ * cos(theta) - nX * sin(theta);
    
      }
          else if (z ==1){ // rotate Z
        
        po->shape_verts[i][j][0] = X * cos(theta) - Y * sin(theta); 
        po->shape_verts[i][j][1] = X * sin(theta) + Y * cos(theta);
        
        po->shape_normals[i][j][0] = nX * cos(theta) - nY * sin(theta); 
        po->shape_normals[i][j][1] = nX * sin(theta) + nY * cos(theta);
  
          }
    }
  }
}


void my_keyboard( unsigned char key, int x, int y ) {
  float amnt = .1;

  switch( key ) {
  case ' ':
    //code to switch between first person view and back as appropriate
    glutPostRedisplay();
    break;
  
case 'X': {
    my_cam.pos[0] += amnt;
  }; break;
  case 'x': {
    my_cam.pos[0] -= amnt;
  }; break;
  case 'Y': {
    my_cam.pos[1] += amnt;
  }; break;
  case 'y': {
    my_cam.pos[1] -= amnt;
  }; break;
  case 'Z': {
    my_cam.pos[2] += amnt;
  }; break;
  case 'z': {
    my_cam.pos[2] -= amnt;
  }; break;
  

  case 'U': {
    my_cam.pos[0] += amnt*my_cam.u[0];
    my_cam.pos[1] += amnt*my_cam.u[1];
    my_cam.pos[2] += amnt*my_cam.u[2];
    my_cam.at[0] += amnt*my_cam.u[0];
    my_cam.at[1] += amnt*my_cam.u[1];
    my_cam.at[2] += amnt*my_cam.u[2];
  }; break;
  case 'u': {
    my_cam.pos[0] -= amnt*my_cam.u[0];
    my_cam.pos[1] -= amnt*my_cam.u[1];
    my_cam.pos[2] -= amnt*my_cam.u[2]; 
    my_cam.at[0] -= amnt*my_cam.u[0];
    my_cam.at[1] -= amnt*my_cam.u[1];
    my_cam.at[2] -= amnt*my_cam.u[2];
  }; break;
  case 'V': {
    my_cam.pos[0] += amnt*my_cam.v[0];
    my_cam.pos[1] += amnt*my_cam.v[1];
    my_cam.pos[2] += amnt*my_cam.v[2];
    my_cam.at[0] += amnt*my_cam.v[0];
    my_cam.at[1] += amnt*my_cam.v[1];
    my_cam.at[2] += amnt*my_cam.v[2];
  }; break;
  case 'v': {
    my_cam.pos[0] -= amnt*my_cam.v[0];
    my_cam.pos[1] -= amnt*my_cam.v[1];
    my_cam.pos[2] -= amnt*my_cam.v[2];
    my_cam.at[0] -= amnt*my_cam.v[0];
    my_cam.at[1] -= amnt*my_cam.v[1];
    my_cam.at[2] -= amnt*my_cam.v[2];
  }; break;
  case 'L':
  case 'W': {
    my_cam.pos[0] += amnt*my_cam.w[0];
    my_cam.pos[1] += amnt*my_cam.w[1];
    my_cam.pos[2] += amnt*my_cam.w[2];
    my_cam.at[0] += amnt*my_cam.w[0];
    my_cam.at[1] += amnt*my_cam.w[1];
    my_cam.at[2] += amnt*my_cam.w[2];
  }; break;
  case 'l':
  case 'w': {
    my_cam.pos[0] -= amnt*my_cam.w[0];
    my_cam.pos[1] -= amnt*my_cam.w[1];
    my_cam.pos[2] -= amnt*my_cam.w[2];
    my_cam.at[0] -= amnt*my_cam.w[0];
    my_cam.at[1] -= amnt*my_cam.w[1];
    my_cam.at[2] -= amnt*my_cam.w[2];
  }; break;
  

  case 'q': 
  case 'Q':
    exit(0) ;
    break ;	
  default: break;
  }
  glutPostRedisplay();  
  return ;
}

void my_mouse_drag(int x, int y) {
}

int my_raytrace_cube(OBJECT *s, float *rayStart, float *rayDirection, float result[3])
{
  int i;
  double a;
  double b;
  double c;
  double discriminate;
  double t1, t2, t3, t4, t5, t6;
  double tarray[6];
  int pos_t_count = 0;

  double tx, ty, tz;
  double rx, ry, rz;
  double sx, sy, sz;

  double oldP0, oldP1, oldP2;
  double oldD0, oldD1, oldD2;

  tx = -(s->translate[0]);
  ty = -(s->translate[1]);
  tz = -(s->translate[2]);

  rx = s->rotate[0] * M_PI/180;
  ry = s->rotate[1] * M_PI/180;
  rz = s->rotate[2] * M_PI/180;

  sx = s->scale[0];
  sy = s->scale[1];
  sz = s->scale[2];

  // do the translation  
  rayStart[0] += tx;
  rayStart[1] += ty;
  rayStart[2] += tz;

  // store temporary variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];
  oldD2 = rayDirection[2];

  // do z rotation
  rayStart[0] = cos(rz)*oldP0 + sin(rz)*oldP1;
  rayStart[1] = -sin(rz)*oldP0 + cos(rz)*oldP1;
  
  // for direction too
  rayDirection[0] = cos(rz)*oldD0 + sin(rz)*oldD1;
  rayDirection[1] = -sin(rz)*oldD0 + cos(rz)*oldD1;
  
  // resave temp variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];

  // do y rotation
  rayStart[0] = cos(ry)*oldP0 - sin(ry)*oldP2;
  rayStart[2] = sin(ry)*oldP0 + cos(ry)*oldP2;

  rayDirection[0] = cos(ry)*oldD0 - sin(ry)*oldD2;
  rayDirection[2] = sin(ry)*oldD0 + cos(ry)*oldD2;

  // resave
  oldP0 = rayStart[0];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD2 = rayDirection[2];

  // do x rotation
  rayStart[1] = cos(rx)*oldP1 + sin(rx)*oldP2;
  rayStart[2] = -sin(rx)*oldP1 + cos(rx)*oldP2;

  rayDirection[1] = cos(rx)*oldD1 + sin(rx)*oldD2;
  rayDirection[2] = -sin(rx)*oldD1 + cos(rx)*oldD2;


  // SCALING TIME
  rayStart[0] *= 1./sx;
  rayStart[1] *= 1./sy;
  rayStart[2] *= 1./sz;

  rayDirection[0] *= 1./sx;
  rayDirection[1] *= 1./sy;
  rayDirection[2] *= 1./sz;



  t1 = (-rayStart[0] - .5)/rayDirection[0];
  t2 = (-rayStart[0] + .5)/rayDirection[0];
  t3 = (-rayStart[1] - .5)/rayDirection[1];
  t4 = (-rayStart[1] + .5)/rayDirection[1];
  t5 = (-rayStart[2] - .5)/rayDirection[2];
  t6 = (-rayStart[2] + .5)/rayDirection[2];

  if (t1 > 0) {
    tarray[pos_t_count] = t1;
    pos_t_count++;
  }
  if (t2 > 0) {
    tarray[pos_t_count] = t2;
    pos_t_count++;
  }
  if (t3 > 0) {
    tarray[pos_t_count] = t3;
    pos_t_count++;
  }
  if (t4 > 0) {
    tarray[pos_t_count] = t4;
    pos_t_count++;
  }
  if (t5 > 0) {
    tarray[pos_t_count] = t5;
    pos_t_count++;
  }
  if (t6 > 0) {
    tarray[pos_t_count] = t6;
    pos_t_count++;
  }

  if (pos_t_count == 0) {
    printf("no positive t\n");
    return 0;
  }
  if (pos_t_count == 1) {
    t1 = tarray[0];
  }
  if (pos_t_count == 2) {
    t1 = min(tarray[0], tarray[1]);
  }
  if (pos_t_count == 3) {
    t1 = min(tarray[0], tarray[1]);
    t1 = min(t1, tarray[2]);
  }
  if (pos_t_count == 4) {
    t1 = min(tarray[0], tarray[1]);
    t2 = min(tarray[2], tarray[3]);
    t1 = min(t1, t2);
  }
  if (pos_t_count == 5) {
    t1 = min(tarray[0], tarray[1]);
    t2 = min(tarray[2], tarray[3]);
    t1 = min(t1, t2);
    t1 = min(t1, tarray[4]);
  }
  if (pos_t_count == 6) {
    t1 = min(tarray[0], tarray[1]);
    t2 = min(tarray[2], tarray[3]);
    t3 = min(tarray[4], tarray[5]);
    t1 = min(t1, t2);
    t1 = min(t1, t3);
  }

  result[0] = rayStart[0] + t1*rayDirection[0];
  result[1] = rayStart[1] + t1*rayDirection[1];
  result[2] = rayStart[2] + t1*rayDirection[2];

  if (result[0] < -.5 || result[0] > .5) {
    printf("oob on x\n");
    return 0;
  }
  if (result[1] < -.5 || result[1] > .5) {
    printf("oob on y\n");
    return 0;
  }
  if (result[2] < -.5 || result[2] > .5) {
    printf("oob on z\n");
    return 0;
  }

  result[0] *= sx;
  result[1] *= sy;
  result[2] *= sz;

  // resave
  oldP0 = result[0];
  oldP1 = result[1];
  oldP2 = result[2];

  // do x rotation
  result[1] = cos(rx)*oldP1 - sin(rx)*oldP2;
  result[2] = sin(rx)*oldP1 + cos(rx)*oldP2;

  oldP1 = result[1];
  oldP2 = result[2];

  // do y rotation
  result[0] = cos(ry)*oldP0 + sin(ry)*oldP2;
  result[2] = -sin(ry)*oldP0 + cos(ry)*oldP2;

  oldP0 = result[0];
  oldP2 = result[2];

  // do z rotation
  result[0] = cos(rz)*oldP0 - sin(rz)*oldP1;
  result[1] = sin(rz)*oldP0 + cos(rz)*oldP1;

  // translate back
  result[0] -= tx;
  result[1] -= ty;
  result[2] -= tz;

  return 1;
}

int my_raytrace_house(OBJECT *s, float *rayStart, float *rayDirection, float result[3])
{

  return 0; 
}

int my_raytrace_cone(OBJECT *s, float *rayStart, float *rayDirection, float result[3])
{
  int i;
  double a;
  double b;
  double c;
  double discriminate;
  double t1, t2, t3;

  double tx, ty, tz;
  double rx, ry, rz;
  double sx, sy, sz;

  double oldP0, oldP1, oldP2;
  double oldD0, oldD1, oldD2;

  tx = -(s->translate[0]);
  ty = -(s->translate[1]);
  tz = -(s->translate[2]);

  rx = s->rotate[0] * M_PI/180;
  ry = s->rotate[1] * M_PI/180;
  rz = s->rotate[2] * M_PI/180;

  sx = s->scale[0];
  sy = s->scale[1];
  sz = s->scale[2];

  // do the translation  
  rayStart[0] += tx;
  rayStart[1] += ty;
  rayStart[2] += tz;

  // store temporary variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];
  oldD2 = rayDirection[2];

  // do z rotation
  rayStart[0] = cos(rz)*oldP0 + sin(rz)*oldP1;
  rayStart[1] = -sin(rz)*oldP0 + cos(rz)*oldP1;
  
  // for direction too
  rayDirection[0] = cos(rz)*oldD0 + sin(rz)*oldD1;
  rayDirection[1] = -sin(rz)*oldD0 + cos(rz)*oldD1;
  
  // resave temp variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];

  // do y rotation
  rayStart[0] = cos(ry)*oldP0 - sin(ry)*oldP2;
  rayStart[2] = sin(ry)*oldP0 + cos(ry)*oldP2;

  rayDirection[0] = cos(ry)*oldD0 - sin(ry)*oldD2;
  rayDirection[2] = sin(ry)*oldD0 + cos(ry)*oldD2;

  // resave
  oldP0 = rayStart[0];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD2 = rayDirection[2];

  // do x rotation
  rayStart[1] = cos(rx)*oldP1 + sin(rx)*oldP2;
  rayStart[2] = -sin(rx)*oldP1 + cos(rx)*oldP2;

  rayDirection[1] = cos(rx)*oldD1 + sin(rx)*oldD2;
  rayDirection[2] = -sin(rx)*oldD1 + cos(rx)*oldD2;


  // SCALING TIME
  rayStart[0] /= sx;
  rayStart[1] /= sy;
  rayStart[2] /= sz;

  rayDirection[0] /= sx;
  rayDirection[1] /= sy;
  rayDirection[2] /= sz;



  a = rayDirection[0]*rayDirection[0] - rayDirection[1]*rayDirection[1] + rayDirection[2]*rayDirection[2];
  b = 2*(rayStart[0]*rayDirection[0] - rayStart[1]*rayDirection[1] + rayStart[2]*rayDirection[2] + rayDirection[1]);
  c = rayStart[0]*rayStart[0] - rayStart[1]*rayStart[1] + rayStart[2]*rayStart[2] + 2*rayStart[1] - 1; 
  
  discriminate = b*b - 4*a*c;
  
  t3 = -rayStart[1]/rayDirection[1];

  if (discriminate < 0 && t3 <= 0) {       // no matches
    return 0;
  }
  if (discriminate < 0 && t3 > 0)
  {
    result[0] = rayStart[0] + t3*rayDirection[0];
    result[1] = rayStart[1] + t3*rayDirection[1];
    result[2] = rayStart[2] + t3*rayDirection[2];

    if (result[1] < 0 || result[1] > 1) {
      return 0;
    }

    // put it back
    result[0] *= sx;
    result[1] *= sy;
    result[2] *= sz;

    // resave
    oldP0 = result[0];
    oldP1 = result[1];
    oldP2 = result[2];

    // do x rotation
    result[1] = cos(rx)*oldP1 - sin(rx)*oldP2;
    result[2] = sin(rx)*oldP1 + cos(rx)*oldP2;

    oldP1 = result[1];
    oldP2 = result[2];

    // do y rotation
    result[0] = cos(ry)*oldP0 + sin(ry)*oldP2;
    result[2] = -sin(ry)*oldP0 + cos(ry)*oldP2;

    oldP0 = result[0];
    oldP2 = result[2];

    // do z rotation
    result[0] = cos(rz)*oldP0 - sin(rz)*oldP1;
    result[1] = sin(rz)*oldP0 + cos(rz)*oldP1;

    // translate back
    result[0] -= tx;
    result[1] -= ty;
    result[2] -= tz;

    printf("RETURNING HERE\n");
    return 1;

  }
  else {
    t1 = (-b + sqrt(discriminate))/(2*a);
    t2 = (-b - sqrt(discriminate))/(2*a);

    if (t1 > 0 && t2 > 0 && t3 > 0) {
      t1 = min(t1, t3);
      t1 = min(t1, t2);
    }
    else if (t1 > 0 && t2 > 0 && t3 <= 0) {
      t1 = min(t1, t2);
    }
    else if (t2 > 0 && t3 > 0 && t1 <= 0) {
      t1 = min(t2, t3);
    }
    else if (t1 > 0 && t3 > 0 && t2 <= 0) {
      t1 = min(t1, t3);
    }


    result[0] = rayStart[0] + t1*rayDirection[0];
    result[1] = rayStart[1] + t1*rayDirection[1];
    result[2] = rayStart[2] + t1*rayDirection[2];

    if (result[1] < 0 || result[1] > 1) {
      return 0;
    }


    result[0] *= sx;
    result[1] *= sy;
    result[2] *= sz;

    // resave
    oldP0 = result[0];
    oldP1 = result[1];
    oldP2 = result[2];

    // do x rotation
    result[1] = cos(rx)*oldP1 - sin(rx)*oldP2;
    result[2] = sin(rx)*oldP1 + cos(rx)*oldP2;

    oldP1 = result[1];
    oldP2 = result[2];

    // do y rotation
    result[0] = cos(ry)*oldP0 + sin(ry)*oldP2;
    result[2] = -sin(ry)*oldP0 + cos(ry)*oldP2;

    oldP0 = result[0];
    oldP2 = result[2];

    // do z rotation
    result[0] = cos(rz)*oldP0 - sin(rz)*oldP1;
    result[1] = sin(rz)*oldP0 + cos(rz)*oldP1;

    // translate back
    result[0] -= tx;
    result[1] -= ty;
    result[2] -= tz;
  
        printf(" VS *** RETURNING HERE\n");
  return 1;
  }

  return 0;
  
}

int my_raytrace_cylinder(OBJECT *s, float *rayStart, float *rayDirection, float result[3])
{
  int i;
  double a;
  double b;
  double c;
  double discriminate;
  double t1, t2;

  double tx, ty, tz;
  double rx, ry, rz;
  double sx, sy, sz;

  double oldP0, oldP1, oldP2;
  double oldD0, oldD1, oldD2;

  tx = -(s->translate[0]);
  ty = -(s->translate[1]);
  tz = -(s->translate[2]);

  rx = s->rotate[0] * M_PI/180;
  ry = s->rotate[1] * M_PI/180;
  rz = s->rotate[2] * M_PI/180;

  sx = s->scale[0];
  sy = s->scale[1];
  sz = s->scale[2];

  // do the translation  
  rayStart[0] += tx;
  rayStart[1] += ty;
  rayStart[2] += tz;

  // store temporary variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];
  oldD2 = rayDirection[2];

  // do z rotation
  rayStart[0] = cos(rz)*oldP0 + sin(rz)*oldP1;
  rayStart[1] = -sin(rz)*oldP0 + cos(rz)*oldP1;
  
  // for direction too
  rayDirection[0] = cos(rz)*oldD0 + sin(rz)*oldD1;
  rayDirection[1] = -sin(rz)*oldD0 + cos(rz)*oldD1;
  
  // resave temp variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];

  // do y rotation
  rayStart[0] = cos(ry)*oldP0 - sin(ry)*oldP2;
  rayStart[2] = sin(ry)*oldP0 + cos(ry)*oldP2;

  rayDirection[0] = cos(ry)*oldD0 - sin(ry)*oldD2;
  rayDirection[2] = sin(ry)*oldD0 + cos(ry)*oldD2;

  // resave
  oldP0 = rayStart[0];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD2 = rayDirection[2];

  // do x rotation
  rayStart[1] = cos(rx)*oldP1 + sin(rx)*oldP2;
  rayStart[2] = -sin(rx)*oldP1 + cos(rx)*oldP2;

  rayDirection[1] = cos(rx)*oldD1 + sin(rx)*oldD2;
  rayDirection[2] = -sin(rx)*oldD1 + cos(rx)*oldD2;


  // SCALING TIME
  rayStart[0] /= sx;
  rayStart[1] /= sy;
  rayStart[2] /= sz;

  rayDirection[0] /= sx;
  rayDirection[1] /= sy;
  rayDirection[2] /= sz;



  a = rayDirection[0]*rayDirection[0] + rayDirection[2]*rayDirection[2];
  b = 2*(rayStart[0]*rayDirection[0] + rayStart[2]*rayDirection[2]);
  c = rayStart[0]*rayStart[0] + rayStart[2]*rayStart[2] - 1; 
  
  discriminate = b*b - 4*a*c;
  
  if (discriminate < 0) {       // no matches
    return 0;
  }
  else {
    t1 = (-b + sqrt(discriminate))/(2*a);
    t2 = (-b - sqrt(discriminate))/(2*a);
    result[0] = rayStart[0] + min(t1, t2)*rayDirection[0];
    result[1] = rayStart[1] + min(t1, t2)*rayDirection[1];
    result[2] = rayStart[2] + min(t1, t2)*rayDirection[2];
  }

  if (result[1] > .5 || result[1] < -.5)
  {
    printf("Result oob : %f\n", result[1]);
    return 0;
  }
  else {

    result[0] *= sx;
    result[1] *= sy;
    result[2] *= sz;

    // resave
    oldP0 = result[0];
    oldP1 = result[1];
    oldP2 = result[2];

    // do x rotation
    result[1] = cos(rx)*oldP1 - sin(rx)*oldP2;
    result[2] = sin(rx)*oldP1 + cos(rx)*oldP2;

    oldP1 = result[1];
    oldP2 = result[2];

    // do y rotation
    result[0] = cos(ry)*oldP0 + sin(ry)*oldP2;
    result[2] = -sin(ry)*oldP0 + cos(ry)*oldP2;

    oldP0 = result[0];
    oldP2 = result[2];

    // do z rotation
    result[0] = cos(rz)*oldP0 - sin(rz)*oldP1;
    result[1] = sin(rz)*oldP0 + cos(rz)*oldP1;

    // translate back
    result[0] -= tx;
    result[1] -= ty;
    result[2] -= tz;
  }
  
  return 1;
}

int my_raytrace_sphere(OBJECT *s, float *rayStart, float *rayDirection, float result[3])
{
  int i;
  double a;
  double b;
  double c;
  double discriminate;
  double t1, t2;

  double tx, ty, tz;
  double rx, ry, rz;
  double sx, sy, sz;

  double oldP0, oldP1, oldP2;
  double oldD0, oldD1, oldD2;

  tx = -(s->translate[0]);
  ty = -(s->translate[1]);
  tz = -(s->translate[2]);

  rx = s->rotate[0]* M_PI/180;
  ry = s->rotate[1]* M_PI/180;
  rz = s->rotate[2]* M_PI/180;

  sx = s->scale[0];
  sy = s->scale[1];
  sz = s->scale[2];

  // do the translation  
  rayStart[0] += tx;
  rayStart[1] += ty;
  rayStart[2] += tz;

  // store temporary variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];
  oldD2 = rayDirection[2];

  // do z rotation
  rayStart[0] = cos(rz)*oldP0 + sin(rz)*oldP1;
  rayStart[1] = -sin(rz)*oldP0 + cos(rz)*oldP1;
  
  // for direction too
  rayDirection[0] = cos(rz)*oldD0 + sin(rz)*oldD1;
  rayDirection[1] = -sin(rz)*oldD0 + cos(rz)*oldD1;
  
  // resave temp variables
  oldP0 = rayStart[0];
  oldP1 = rayStart[1];

  oldD0 = rayDirection[0];
  oldD1 = rayDirection[1];

  // do y rotation
  rayStart[0] = cos(ry)*oldP0 - sin(ry)*oldP2;
  rayStart[2] = sin(ry)*oldP0 + cos(ry)*oldP2;

  rayDirection[0] = cos(ry)*oldD0 - sin(ry)*oldD2;
  rayDirection[2] = sin(ry)*oldD0 + cos(ry)*oldD2;

  // resave
  oldP0 = rayStart[0];
  oldP2 = rayStart[2];

  oldD0 = rayDirection[0];
  oldD2 = rayDirection[2];

  // do x rotation
  rayStart[1] = cos(rx)*oldP1 + sin(rx)*oldP2;
  rayStart[2] = -sin(rx)*oldP1 + cos(rx)*oldP2;

  rayDirection[1] = cos(rx)*oldD1 + sin(rx)*oldD2;
  rayDirection[2] = -sin(rx)*oldD1 + cos(rx)*oldD2;


  // SCALING TIME
  rayStart[0] /= sx;
  rayStart[1] /= sy;
  rayStart[2] /= sz;

  rayDirection[0] /= sx;
  rayDirection[1] /= sy;
  rayDirection[2] /= sz;

  // UNIT STUFF


  a = rayDirection[0]*rayDirection[0] + rayDirection[1]*rayDirection[1] + rayDirection[2]*rayDirection[2];
  b = 2*(rayStart[0]*rayDirection[0] + rayStart[1]*rayDirection[1] + rayStart[2]*rayDirection[2]);
  c = rayStart[0]*rayStart[0] + rayStart[1]*rayStart[1] + rayStart[2]*rayStart[2] - 1; 
  discriminate = b*b - 4*a*c;
  if (discriminate < 0) {       // no matches
    return 0;
  }
  else {
    t1 = (-b + sqrt(discriminate))/(2*a);
    t2 = (-b - sqrt(discriminate))/(2*a);
   

    result[0] = rayStart[0] + min(t1, t2)*rayDirection[0];
    result[1] = rayStart[1] + min(t1, t2)*rayDirection[1];
    result[2] = rayStart[2] + min(t1, t2)*rayDirection[2];


    result[0] *= sx;
    result[1] *= sy;
    result[2] *= sz;

    // resave
    oldP0 = result[0];
    oldP1 = result[1];
    oldP2 = result[2];

    // do x rotation
    result[1] = cos(rx)*oldP1 - sin(rx)*oldP2;
    result[2] = sin(rx)*oldP1 + cos(rx)*oldP2;

    oldP1 = result[1];
    oldP2 = result[2];

    // do y rotation
    result[0] = cos(ry)*oldP0 + sin(ry)*oldP2;
    result[2] = -sin(ry)*oldP0 + cos(ry)*oldP2;

    oldP0 = result[0];
    oldP2 = result[2];

    // do z rotation
    result[0] = cos(rz)*oldP0 - sin(rz)*oldP1;
    result[1] = sin(rz)*oldP0 + cos(rz)*oldP1;

    // translate back
    result[0] -= tx;
    result[1] -= ty;
    result[2] -= tz;




  }
  
  return 1;
}

void my_raytrace(int mousex, int mousey)
{
	double modelViewMatrix[16];
	double projMatrix[16];
	int viewport[4];
	int foundIntersection = 0;
	int hit = 0;
	int i, j;
	double clickPoint[3];
	float intersectionPoint[3];
	float closestPoint[3];
	float rayStart[3];
	float rayDirection[3];
	OBJECT *cur;

  float holdStart[3];
  float holdDirection[3];

	// first we need to get the modelview matrix, the projection matrix, and the viewport
	glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
  mousey = viewport[3] - mousey;

	// gluUnProject with a Z value of 1 will find the point on the far clipping plane
	// corresponding the the mouse click. This is not the same as the vector
	// representing the click.
	gluUnProject(mousex, mousey, 1.0, modelViewMatrix, projMatrix, viewport, &clickPoint[0], &clickPoint[1], &clickPoint[2]);

	// Now we need a vector representing the click. It should start at the camera
	// position. We can subtract the click point, we will get the vector

  /* code for finding direction vector, set rayStart and rayDirection */

  for (i = 0; i < 3; i++){
    rayStart[i] = my_cam.pos[i]; 
  }

  rayDirection[0] = clickPoint[0] - rayStart[0];
  rayDirection[1] = clickPoint[1] - rayStart[1];
  rayDirection[2] = clickPoint[2] - rayStart[2];
  normalize(rayDirection);

  for (i = 0; i < 3; ++i)
  {
    holdStart[i] = rayStart[i];
    holdDirection[i] = rayDirection[i];
  }


	// now go through the shapes and see if there is a hit
	for (i=0; i<num_objects; i++)
	{
		cur = my_objects + i;
		hit = 0;

    for (j = 0; j < 3; j++)
    {
      rayStart[j] = holdStart[j];
      rayDirection[j] = holdDirection[j];
    }

		switch (cur->sid)
		{
    case 1:
      hit = my_raytrace_cube(cur, rayStart, rayDirection, intersectionPoint);
      break;
    case 2:
      hit = my_raytrace_house(cur, rayStart, rayDirection, intersectionPoint);
      break;
    case 3:
      hit = my_raytrace_sphere(cur, rayStart, rayDirection, intersectionPoint);
      break;
    case 4:
      hit = my_raytrace_cylinder(cur, rayStart, rayDirection, intersectionPoint);
      break;
    case 5:
      hit = my_raytrace_cone(cur, rayStart, rayDirection, intersectionPoint);
      break;
    default:
			break;
		}

		// found intersection
		if (hit)
		{

			if (foundIntersection)
			{
				if (intersectionPoint[2] > closestPoint[2]) {
          closestPoint[0] = intersectionPoint[0];
          closestPoint[1] = intersectionPoint[1];
          closestPoint[2] = intersectionPoint[2];
          printf("Found a closer one!\n");
        }
			}
			else
			{
				closestPoint[0] = intersectionPoint[0];
				closestPoint[1] = intersectionPoint[1];
				closestPoint[2] = intersectionPoint[2];
			}

			foundIntersection = 1;
		}
	}

	if (foundIntersection)
	{
		printf("Intersected with object %s at (%f, %f, %f)\n", "object_name", closestPoint[0], closestPoint[1], closestPoint[2]);
	  make_sphere(&small_spheres[num_spheres], .1);
    real_translation(&small_spheres[num_spheres], closestPoint[0], closestPoint[1], closestPoint[2]);
    num_spheres++;

    start_lines[num_clicks][0] = rayStart[0];
    start_lines[num_clicks][1] = rayStart[1];
    start_lines[num_clicks][2] = rayStart[2];
    start_lines[num_clicks][3] = 1;

    click_lines[num_clicks][0] = clickPoint[0];
    click_lines[num_clicks][1] = clickPoint[1];
    click_lines[num_clicks][2] = clickPoint[2];
    click_lines[num_clicks][3] = 1;

    num_clicks++;


    glutPostRedisplay();

  }
	else
	{
		printf("No intersection\n");
	}
}

void my_mouse(int button, int state, int mousex, int mousey) {

  switch( button ) {
	
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ) {
		
		my_raytrace(mousex, mousey);
    }
    
    if( state == GLUT_UP ) {
    }
    break ;

  case GLUT_RIGHT_BUTTON:
    if ( state == GLUT_DOWN ) {
    }
    
    if( state == GLUT_UP ) {
    }
    break ;
  }
  

  
  return ;
}

float dotprod(float v1[], float v2[]) {
  float tot = 0;
  int i;
  for (i=0; i<4; i++)
    tot += v1[i]*v2[i];
  return tot;
}


void normalize(GLfloat *p) { 
  double d=0.0;
  int i;
  for(i=0; i<3; i++) d+=p[i]*p[i];
  d=sqrt(d);
  if(d > 0.0) for(i=0; i<3; i++) p[i]/=d;
}


void cross(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d) { 
  d[0]=(b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
  d[1]=(b[2]-a[2])*(c[0]-a[0])-(b[0]-a[0])*(c[2]-a[2]);
  d[2]=(b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0]);
  normalize(d);
}

void print_matrix(float my_matrix[])
{ 
  int i, j;

  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      printf ("%f ", my_matrix[i+j*4]);
    }
    printf ("\n");
  }
  printf ("\n");
}

/*************************************
 FUNCTION: make_*; reuse your stitcher code here.
*************************************/



void make_cube_smart(OBJECT *po, double size){
  
  // top
  size = size/2;

  po->shape_verts[0][0][0] = -size;
  po->shape_verts[0][0][1] = size;
  po->shape_verts[0][0][2] = size;
  po->shape_verts[0][0][3] = 1;
  po->shape_verts[0][1][0] = size;
  po->shape_verts[0][1][1] = size;
  po->shape_verts[0][1][2] = size;
  po->shape_verts[0][1][3] = 1;
  po->shape_verts[0][2][0] = size;
  po->shape_verts[0][2][1] = size;
  po->shape_verts[0][2][2] = -size;
  po->shape_verts[0][2][3] = 1;
  po->shape_verts[0][3][0] = -size;
  po->shape_verts[0][3][1] = size;
  po->shape_verts[0][3][2] = -size;
  po->shape_verts[0][3][3] = 1;
  
  // bottom
  
  po->shape_verts[1][0][0] = -size;
  po->shape_verts[1][0][1] = -size;
  po->shape_verts[1][0][2] = size;
  po->shape_verts[1][0][3] = 1;
  po->shape_verts[1][1][0] = size;
  po->shape_verts[1][1][1] = -size;
  po->shape_verts[1][1][2] = size;
  po->shape_verts[1][1][3] = 1;
  po->shape_verts[1][2][0] = size;
  po->shape_verts[1][2][1] = -size;
  po->shape_verts[1][2][2] = -size;
  po->shape_verts[1][2][3] = 1;
  po->shape_verts[1][3][0] = -size;
  po->shape_verts[1][3][1] = -size;
  po->shape_verts[1][3][2] = -size;
  po->shape_verts[1][3][3] = 1;
  
  cube_normals(po); // find the normals

  // map texture

  po->cube_tex[0][0] = 0; po->cube_tex[0][1] =  0;
  po->cube_tex[1][0] = 1; po->cube_tex[1][1] =  0;
  po->cube_tex[2][0] = 1; po->cube_tex[2][1] =  1;
  po->cube_tex[3][0] = 0; po->cube_tex[3][1] =  1;
  
}



void cube_normals(OBJECT *po) // finds the cube normals
{
  
  // this code is a little messy, but I could not get the cross product to work
  
  GLfloat vect[4];
  
  vect[0] = -1;
  vect[1] = 1;
  vect[2] = 1;
  
  normalize(vect); // normalize
  
  po->shape_normals[0][0][0] = vect[0]; // x 
  po->shape_normals[0][0][1] = vect[1]; // y
  po->shape_normals[0][0][2] = vect[2]; // z
  
  vect[0] = -1;
  vect[1] = -1;
  vect[2] = 1;
  
  normalize(vect); // normalize
  
  po->shape_normals[1][0][0] = vect[0]; // x 
  po->shape_normals[1][0][1] = vect[1]; // y
  po->shape_normals[1][0][2] = vect[2]; // z
  
  vect[0] = 1;
  vect[1] = -1;
  vect[2] = 1;
  
  normalize(vect); // normalize
  
  po->shape_normals[1][1][0] = vect[0]; // x 
  po->shape_normals[1][1][1] = vect[1]; // y
  po->shape_normals[1][1][2] = vect[2]; // z
  
  vect[0] = 1;
  vect[1] = 1;
  vect[2] = 1;
  
  normalize(vect); // normalize
  
  po->shape_normals[0][1][0] = vect[0]; // x 
  po->shape_normals[0][1][1] = vect[1]; // y
  po->shape_normals[0][1][2] = vect[2]; // z
  
  vect[0] = 1;
  vect[1] = 1;
  vect[2] = -1;
  
  normalize(vect); // normalize
  
  po->shape_normals[0][2][0] = vect[0]; // x 
  po->shape_normals[0][2][1] = vect[1]; // y
  po->shape_normals[0][2][2] = vect[2]; // z
  
  vect[0] = -1;
  vect[1] = 1;
  vect[2] = -1;
  
  normalize(vect); // normalize
  
  po->shape_normals[0][3][0] = vect[0]; // x 
  po->shape_normals[0][3][1] = vect[1]; // y
  po->shape_normals[0][3][2] = vect[2]; // z
  
  vect[0] = -1;
  vect[1] = -1;
  vect[2] = -1;
  
  normalize(vect); // normalize
  
  po->shape_normals[1][3][0] = vect[0]; // x 
  po->shape_normals[1][3][1] = vect[1]; // y
  po->shape_normals[1][3][2] = vect[2]; // z
  
  vect[0] = 1;
  vect[1] = -1;
  vect[2] = -1;
  
  normalize(vect); // normalize
  
  po->shape_normals[1][2][0] = vect[0]; // x 
  po->shape_normals[1][2][1] = vect[1]; // y
  po->shape_normals[1][2][2] = vect[2]; // z
}


void make_cylinder(OBJECT *vert, double ray, double height){
  int i,j,k; // initial variables to use outside of loops

    for(i = 0; i <= crt_vs; i++) // iterates through the angles
    {
      
      for(j = 0; j <= crt_rs; j++) // iterates through the layers
      {
        
        int t = (360/crt_rs * j); // theta        
        GLfloat theta = (t * M_PI/180); // theta angle
        
        for(k = 0; k < 4; k++) // iterates through x,y,z coordinates
        {
          switch(k){
            case 0:
              vert->shape_verts[i][j][k] = ray * cos(theta); break; // x coordinate
            case 1:
              vert->shape_verts[i][j][k] = (height/crt_vs * i) - height/2; break; // y coordinate
            case 2:
              vert->shape_verts[i][j][k] = ray * sin(theta); break; // z coordinate
            case 3:
              vert->shape_verts[i][j][k] = 1; // homogenious coordinate
          }
        }

        shape_normals(vert->shape_verts[i][j], (GLfloat)ray, (GLfloat)ray, vert->shape_normals[i][j], 1,0,0); // compute the normals 
        vert->shape_tex[i][j][0] = (float)j/crt_rs;
        vert->shape_tex[i][j][1] = (float)i/crt_vs;
      }
    }

  return;



}


void make_sphere(OBJECT *vert, double ray){

  int i,j,k; // initial variables to use outside of loops
    
    for(i = 0; i <= crt_vs; i++) // iterates through the angles
    {
      
      for(j = 0; j <= crt_rs; j++) // iterates through the layers
      {
        
        int t = (360/crt_vs * j); // theta
        int p = (180/crt_rs * i) - 90; // phi
        
        GLfloat theta = (t * M_PI/180); // theta angle
        GLfloat phi = (p * M_PI/180);  // phi angle
        
        for(k = 0; k < 4; k++) // iterates through x,y,z coordinates
        {
          switch(k){
            case 0:
              vert->shape_verts[i][j][k] = ray * cos(phi) * cos(theta); break; // x coordinate
            case 1:
              vert->shape_verts[i][j][k] = ray * sin(phi); break; // y coordinate
            case 2:
              vert->shape_verts[i][j][k] = -ray * cos(phi) * sin(theta); break; // z coordinate
            case 3:
              vert->shape_verts[i][j][k] = 1; // homogenious coordinate
          }
        }
        
        shape_normals(vert->shape_verts[i][j], (GLfloat)ray, (GLfloat)ray, vert->shape_normals[i][j], 1,0,0); // compute the normals 
        vert->shape_tex[i][j][0] = (float)j/crt_rs;
        vert->shape_tex[i][j][1] = (float)i/crt_vs;
      }
    }

  return;
}

/************************************************************
          Make Cone
************************************************************/

void make_cone(OBJECT *vert, double height, double ray)
{
  int i,j,k; // initial variables to use outside of loops
  
  for(i = 0; i <= crt_vs; i++) // iterates through the angles
  {
    
    for(j = 0; j <= crt_rs; j++) // iterates through the layers
    {
  
      int t = 360/crt_rs * j; // next angle
      
      GLfloat theta = (t * M_PI/180); // angle
      
      for(k = 0; k < 4; k++) // iterates through x,y,z coordinates
      {
        switch(k){
          case 0:
            vert->shape_verts[i][j][k] = (height - (height/crt_vs * i))/height * ray * cos(theta);break;   // x coordinate
          case 1:
            vert->shape_verts[i][j][k] = (height/crt_vs * i);break;  // y coordinate
          case 2:
            vert->shape_verts[i][j][k] = (height - (height/crt_vs * i))/height * ray * sin(theta); break; // z coordinate
          case 3:
            vert->shape_verts[i][j][k] = 1; // homogenious coordinate
        }
      }
    
      // map texture    
    
      vert->shape_tex[i][j][0] = (float)j/crt_rs;
      vert->shape_tex[i][j][1] = (float)i/crt_vs;
    
    } 
  } 

  // fix wrap around

  for(i = 0; i < crt_rs; i++){
    vert->shape_verts[i][crt_vs+1][0] = vert->shape_verts[i][0][0];
    vert->shape_verts[i][crt_vs+1][1] = vert->shape_verts[i][0][1];
    vert->shape_verts[i][crt_vs+1][2] = vert->shape_verts[i][0][2];
  } 
  
  for(i = 0; i < crt_vs; i++){
    vert->shape_verts[crt_rs + 1][i][0] = vert->shape_verts[0][i][0];
    vert->shape_verts[crt_rs + 1][i][1] = vert->shape_verts[0][i][1];
    vert->shape_verts[crt_rs + 1][i][2] = vert->shape_verts[0][i][2];
  }

  findNormals(vert);  // find normals
}


/************************************************************
          Make Torus
************************************************************/
void make_torus(OBJECT *vert, double R, double r)
{
  int i,j,k; // initial variables to use outside of loops
  
  for(i = 0; i <= crt_rs; i++) // iterates through the Fmys
  {
    GLfloat theta = (2 * M_PI * i)/crt_rs; // angle
    
    for(j = 0; j <= crt_vs; j++) // iterates through the layers
    {
      
      GLfloat phi = (2 * M_PI * j)/crt_vs; // angle
      
      for(k = 0; k < 4; k++) // iterates through x,y,z coordinates
      {
        switch(k){
          case 0:
            vert->shape_verts[i][j][k] = (R + r * cos(phi)) * cos(theta);break; // x coordinate
          case 1:
            vert->shape_verts[i][j][k] = r * sin(phi);break; // y coordinate
          case 2:
            vert->shape_verts[i][j][k] = -(R + r * cos(phi)) * sin(theta);break; // z coordinate
          case 3:
            vert->shape_verts[i][j][k] = 1; // homogenious coordinate
        }
      }
    
      // map texture
    
      vert->shape_tex[i][j][0] = (float)j/crt_rs;
      vert->shape_tex[i][j][1] = (float)i/crt_vs;
    
    } 
  }   

  findNormals(vert); // find normals
}


void make_house(OBJECT *vert)
{ 
  vert->shape_verts[1][0][0] = -1;
  vert->shape_verts[1][0][1] = 1;
  vert->shape_verts[1][0][2] = 1;
  vert->shape_verts[1][0][3] = 1;
  vert->shape_verts[1][1][0] = 1;
  vert->shape_verts[1][1][1] = 1;
  vert->shape_verts[1][1][2] = 1;
  vert->shape_verts[1][1][3] = 1;
  vert->shape_verts[1][2][0] = 1;
  vert->shape_verts[1][2][1] = 1;
  vert->shape_verts[1][2][2] = -1;
  vert->shape_verts[1][2][3] = 1;
  vert->shape_verts[1][3][0] = -1;
  vert->shape_verts[1][3][1] = 1;
  vert->shape_verts[1][3][2] = -1;
  vert->shape_verts[1][3][3] = 1;
  
  vert->shape_verts[2][0][0] = -1;
  vert->shape_verts[2][0][1] = -1;
  vert->shape_verts[2][0][2] = 1;
  vert->shape_verts[2][0][3] = 1;
  vert->shape_verts[2][1][0] = 1;
  vert->shape_verts[2][1][1] = -1;
  vert->shape_verts[2][1][2] = 1;
  vert->shape_verts[2][1][3] = 1;
  vert->shape_verts[2][2][0] = 1;
  vert->shape_verts[2][2][1] = -1;
  vert->shape_verts[2][2][2] = -1;
  vert->shape_verts[2][2][3] = 1;
  vert->shape_verts[2][3][0] = -1;
  vert->shape_verts[2][3][1] = -1;
  vert->shape_verts[2][3][2] = -1;
  vert->shape_verts[2][3][3] = 1;
  
  vert->shape_verts[0][0][0] = 0;
  vert->shape_verts[0][0][1] = 2;
  vert->shape_verts[0][0][2] = 0;
  vert->shape_verts[0][0][3] = 1;
  vert->shape_verts[0][1][0] = 0;
  vert->shape_verts[0][1][1] =  2;
  vert->shape_verts[0][1][2] = 0;
  vert->shape_verts[0][1][3] = 1;
  vert->shape_verts[0][2][0] = 0;
  vert->shape_verts[0][2][1] =  2;
  vert->shape_verts[0][2][2] = 0;
  vert->shape_verts[0][2][3] = 1;
  vert->shape_verts[0][3][0] = 0;
  vert->shape_verts[0][3][1] =  2;
  vert->shape_verts[0][3][2] = 0;
  vert->shape_verts[0][3][3] = 1;
  
  vert->shape_verts[3][0][0] = 1;
  vert->shape_verts[3][0][1] = 1;
  vert->shape_verts[3][0][2] = -1;
  vert->shape_verts[3][0][3] = 1;
  vert->shape_verts[3][1][0] = 1;
  vert->shape_verts[3][1][1] = 1;
  vert->shape_verts[3][1][2] = -1;
  vert->shape_verts[3][1][3] = 1;
  vert->shape_verts[3][2][0] = 0;
  vert->shape_verts[3][2][1] =  2;
  vert->shape_verts[3][2][2] = 0;
  vert->shape_verts[3][2][3] = 1;
  vert->shape_verts[3][3][0] = 1;
  vert->shape_verts[3][3][1] = 1;
  vert->shape_verts[3][3][2] = -1;
  vert->shape_verts[3][3][3] = 1;
  
  cube_normals(vert); // find normals

  //map texture

  vert->cube_tex[0][0] = 0; vert->cube_tex[0][1] =  0;
  vert->cube_tex[1][0] = 1; vert->cube_tex[1][1] =  0;
  vert->cube_tex[2][0] = 1; vert->cube_tex[2][1] =  1;
  vert->cube_tex[3][0] = 0; vert->cube_tex[3][1] =  1;
}
/************************************************************
          Shape Normals
************************************************************/

void shape_normals(GLfloat point[4], GLfloat R, GLfloat r, GLfloat normal[4], int sphere, int cone, int torus)
{ 
  if(sphere == 1){  // gradient of a sphere

    normal[0] = point[0] / R;
    normal[1] = point[1] / R;
    normal[2] = point[2] / R;
  } 
}
void findNormals(OBJECT *vert)
{   
  GLfloat v1[4][3];
  
  int i, j;
  
  for(i = 0; i <= crt_vs; i++)
    for(j = 0; j <= crt_rs; j++)
    {
      
      cross(vert->shape_verts[i][j], vert->shape_verts[i][(j+1)%crt_rs], vert->shape_verts[(i-1)%crt_vs][j], v1[0]);
      cross(vert->shape_verts[i][j], vert->shape_verts[(i-1)%crt_vs][j], vert->shape_verts[i][(j-1)%crt_rs], v1[1]);
      cross(vert->shape_verts[i][j], vert->shape_verts[i][(j-1)%crt_rs], vert->shape_verts[(i+1)%crt_vs][j], v1[2]);
      cross(vert->shape_verts[i][j], vert->shape_verts[(i+1)%crt_vs][j], vert->shape_verts[i][(j+1)%crt_rs], v1[3]);
      
      vert->shape_normals[i][j][0] = ((v1[0][0]+v1[1][0]+v1[2][0]+v1[3][0])/4);
      vert->shape_normals[i][j][1] = ((v1[0][1]+v1[1][1]+v1[2][1]+v1[3][1])/4);
      vert->shape_normals[i][j][2] = ((v1[0][2]+v1[1][2]+v1[2][2]+v1[3][2])/4);
      
    }
}



/***********************************
 FUNCTION: draw_quad 
 ARGS: - a vertex array
 - 4 indices into the vertex array defining a quad face
 - an index into the color array.
 RETURN: none
 DOES:  helper drawing function; draws one quad. 
 For the normal to work out, follow left-hand-rule (i.e., counter clock
 wise) 
*************************************/
void draw_quads(GLfloat vertices[121][121][4], GLfloat normals[121][121][4], GLfloat tex[121][121][2], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic)
{
  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glScalef(-1.0, 1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  
  glBegin(crt_render_mode); 
  {
//    glColor3fv(colors[ic]);
    glNormal3fv(normals[iv1a][iv1b]);
    
    glVertex4fv(vertices[iv1a][iv1b]);
    glVertex4fv(vertices[iv2a][iv2b]);
    glVertex4fv(vertices[iv3a][iv3b]);
    glVertex4fv(vertices[iv4a][iv4b]);
  }
  
  glEnd();
}


/***********************************
 FUNCTION: draw_cube_smart() 
 ARGS: none
 RETURN: none
 DOES: draws a cube from quads
************************************/

void draw_cube(GLfloat vertices[121][121][4], GLfloat normals[121][121][4], GLfloat tex[4][2], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic)
{ 
  glBegin(crt_render_mode); 
  {
    //glColor3fv(colors[ic]);
    
    /*note the explicit use of homogeneous coords below: glVertex4f*/
    glNormal3fv(normals[iv1a][iv1b]);
  
    glVertex4fv(vertices[iv1a][iv1b]);
    glVertex4fv(vertices[iv2a][iv2b]);
    glVertex4fv(vertices[iv3a][iv3b]);
    glVertex4fv(vertices[iv4a][iv4b]);
  }
  
  glEnd();
}

/***********************************
 FUNCTION: draw_axes
 ARGS: none
 RETURN: none
 DOES: draws main X, Y, Z axes
************************************/
void draw_axes( void ) {
  glLineWidth( 5.0 );

  glDisable(GL_LIGHTING);

  glBegin(GL_LINES); 
  {
    glColor3fv(colors[1]);
    glVertex4fv(vertices_axes[0]);
    glVertex4fv(vertices_axes[1]);
		
    glColor3fv(colors[4]);
    glVertex4fv(vertices_axes[0]);
    glVertex4fv(vertices_axes[2]);
		
    glColor3fv(colors[6]);
    glVertex4fv(vertices_axes[0]);
    glVertex4fv(vertices_axes[3]);
  }
  glEnd();
  glLineWidth( 1.0 );

  glEnable(GL_LIGHTING);
	
}


void draw_objects() {
  
  int i;
  for(i=0; i<num_objects; i++){
    OBJECT *cur;
    cur = &my_objects[i];
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, cur->amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cur->diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cur->spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, &cur->shine);
    //glMaterialfv(GL_FRONT, GL_EMISSION, cur->emi);

    switch(cur->sid){
      
    
      case 1: //cube
      {
        crt_rs = 3;
        crt_vs = 1;
        draw(cur);
      }break;
      case 2: // house
      {
        crt_rs = 3;
        crt_vs = 2;
        draw(cur);
      }break;
      case 3: // sphere
      {
        crt_rs = crt_vs = 90;
        draw_shape(cur);
      }break;
      case 4: // cylinder
      {
        crt_rs = crt_vs = 90;
        draw_shape(cur);
      }break;
      case 5: // cone
      {
        crt_rs = crt_vs = 90;
        draw_shape(cur);
      }break;
    }
    
  }
  for(i=0; i<num_spheres; i++){
    OBJECT *cur;
    cur = &small_spheres[i];
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, cur->amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cur->diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cur->spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, &cur->shine);
    //glMaterialfv(GL_FRONT, GL_EMISSION, cur->emi);

    crt_rs = crt_vs = 90;
    draw_shape(cur);
    
  }
}

void draw_shape(OBJECT *verts)
{
  
  int i, j; // loop variables 
  // polymorphic way to draw shapes
  
  glClearColor(0,0,0,1); // else black
  
  for(i = 0; i < crt_vs; i++) // handles main body of array
  { 
    for(j = 0; j < crt_rs; j++)
    {
      draw_quads(verts->shape_verts, verts->shape_normals, verts->shape_tex, i,j,i,j+1,i+1,j+1,i+1,j, RED); // draws shape
    }
  }
  for (i = 0; i < crt_vs; i ++) // connects the sides
  {
    draw_quads(verts->shape_verts, verts->shape_normals, verts->shape_tex, i, crt_rs, i+ 1, crt_rs, i + 1, 0, i, 0, RED);
  }
  if(my_objects[num_objects - 1].sid == 0 || my_objects[num_objects].sid == 1) // fixes cube and house normal
  {
    
    for(i = 0; i < 2; i++) // draws tops of house and cube
    {
      draw_quads(verts->shape_verts,verts->shape_normals, verts->shape_tex, crt_vs - i, 0, crt_vs - i, 1, crt_vs - i, 2, crt_vs - i, 3, RED); 
    }
  }
}

void draw(OBJECT *verts) // draws the cube and house
{ 
  int i, j; // loop variables

  // polymorphic way to draw shapes
  
  glClearColor(0,0,0,1); // else black
  
  for(i = 0; i < crt_vs; i++) // handles main body of array
  { 
    for(j = 0; j < crt_rs; j++)
    {
      draw_cube(verts->shape_verts, verts->shape_normals, verts->cube_tex, i,j,i,j+1,i+1,j+1,i+1,j, RED); // draws shape
    }
  }
  
  for (i = 0; i < crt_vs; i ++) // connects the sides
  {
    // textures can be manipulated on the stack as well
  
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glRotatef(90.0, 0, 0, 1); 
    
    draw_cube(verts->shape_verts, verts->shape_normals, verts->cube_tex, i, crt_rs, i+1, crt_rs, i + 1, 0, i, 0, RED);
  
    glRotatef(-90.0, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW); 
  } 
  
  if(my_objects[num_objects - 1].sid == 0 || my_objects[num_objects].sid == 1) // fixes cube and house normal
  {
    
    for(i = 0; i < 2; i++) // draws tops of house and cube
    {
      draw_cube(verts->shape_verts,verts->shape_normals, verts->cube_tex, crt_vs - i, 0, crt_vs - i, 1, crt_vs - i, 2, crt_vs - i, 3, RED); 
    }
  } 
}

void draw_lines() {
  int i;

  for (i = 0; i < num_clicks; ++i)
  {
    glEnable(GL_BLEND); 
    glColor3fv(colors[2]);
    glLineWidth(3);
    glBegin(GL_LINES);
      glVertex4f(start_lines[i][0], start_lines[i][1], start_lines[i][2], 1);
      glVertex4f(click_lines[i][0], click_lines[i][1], click_lines[i][2], 1);
    glEnd(); 
    glDisable(GL_BLEND);

  }
  
}




void my_display() {

  // clear all pixels, reset depth 
  glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );
  
  glLoadIdentity();
  //setup the camera (1st person? 3rd person?)

  gluLookAt(my_cam.pos[0],my_cam.pos[1], my_cam.pos[2],
	    my_cam.at[0],my_cam.at[1],my_cam.at[2],
	    my_cam.up[0], my_cam.up[1], my_cam.up[2]);

  //update the flashlight to follow the person
  
  //draw the objects
  draw_axes();

  draw_objects();

  draw_lines();

  // this buffer is ready
  glutSwapBuffers();
}

void my_idle(void) {
  //EC idea: Make the flashlight flicker a bit (random flicker strength) when the user is idle.
  return ;
}
