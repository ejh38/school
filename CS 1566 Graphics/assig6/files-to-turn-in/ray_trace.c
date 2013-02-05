/**************************************
FILE: ray_trace.c
AUTHOR: Zach Sadler
EMAIL: zps6@pitt.edu
PLATFORM: macosx
HOMEWORK: 6
**************************************/

#include "ray_trace.h"

#define MAX_LIGHTS  8
#define MAX_OBJECTS 8
#define min(a,b) ((a) < (b)? a:b)

GLuint texId;

color_t screen[WINDOW_WIDTH * WINDOW_HEIGHT];

int raster_x = 0;       // the pixel to draw, x position
int raster_y = 0;       // the pixel to draw, y position

OBJECT my_objects[MAX_OBJECTS];     // the array of objects
LITE my_lights[MAX_LIGHTS];         // and of lights, read in from spec

int num_objects = 0;    // to keep track of my_objects length
int num_lights = 0;     // to keep track of my_lights length

CAM my_cam;             // the camera read in from spec

GLfloat globalAmb[4] = {.15, .15, .15, .1};     // the RGBA values for global ambient
GLfloat globalDif = .2;                         // and global diffuse light


// this function puts a certain color (specified by RGBA) to pixel x,y
void plotPixel(color_t *screen, int x, int y, float r, float g, float b, float a)
{
	screen[y*WINDOW_WIDTH + x].r = r;
	screen[y*WINDOW_WIDTH + x].g = g;
	screen[y*WINDOW_WIDTH + x].b = b;
	screen[y*WINDOW_WIDTH + x].a = a;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	// depth buffer not really needed, but whatever
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("Zach Sadler - zps6- HW 6");

	initGL();
  if (argc == 1) {
    printf("Need to specify a spec file as second argument!\nExiting program.\n");
    return 1;
  }
  if (argc > 2) {
    printf("Please only specify one spec file.\nExiting program.\n");
    return 2;
  }
	read_spec(argv[1]);

	glutDisplayFunc(my_display);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(idle);
  glutKeyboardFunc(my_keyboard);

	glutMainLoop();

	return 0;
}

// I left this untouched
void initGL()
{
	int i, j;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);

	resizeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	// erase texture
	for (i=0;i<sizeof(screen)/sizeof(color_t);i++)
	{
		screen[i].r = 0.0f;
		screen[i].g = 0.0f;
		screen[i].b = 0.0f;
		screen[i].a = 1.0f;
	}

	// create texture for drawing
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_FLOAT, (void*)screen);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

// this is straight from previous hws
void normalize(GLfloat *p) { 
  double d=0.0;
  int i;
  for(i=0; i<3; i++) d+=p[i]*p[i];
  d=sqrt(d);
  if(d > 0.0) for(i=0; i<3; i++) p[i]/=d;
}

// this is also straight from previous hws
float dotprod(float v1[], float v2[]) {
  float tot = 0;
  int i;
  for (i=0; i<3; i++)
    tot += v1[i]*v2[i];
  return tot;
}

// taken from hw5
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

// untouched from hw5
void parse_obj(char *buffer){
  OBJECT *po;
  char *pshape, *pshine, *pemi, *pamb, *pdiff, *pspec, *ptranslate, *pscale, *protate;

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
      
  printf("read object\n");
}

// I took out the calculation of w, v, u from hw5
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

}

// untouched from hw5
void parse_light(char *buffer){
  LITE *pl;
  char *pamb, *pdiff, *pspec, *ppos, *pdir, *pang;
  pl = &my_lights[num_lights++];

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

// simplified the logic from hw5
void read_spec(char *fname) {
  char buffer[300];
  FILE *fp;

  fp = fopen(fname, "r");
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

// took out the flashlight code 
void lighting_setup () {
  int i;

  //enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  // reflective propoerites -- global ambiant light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

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

// added this function, which just does some camera work 
// and acts as a wrapper around displayScene()
void my_display()
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texId);
// /*
  // load orthographic projection
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  displayScene();

  // restore projection
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glutSwapBuffers();
}

// I moved some of the contents to my_display
void displayScene()
{
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
  glEnd();
}

// I included this just for the ability to hit 'q' to quit
void my_keyboard( unsigned char key, int x, int y ) {
  switch( key ) {
  case 'q': 
  case 'Q':
    exit(0) ;
    break ; 
  default: break;
  }
  return ;
}

// this is where the actual work happens
void idle()
{
  GLfloat colors[3];  // these are the colors we'll draw

	if (raster_x < WINDOW_WIDTH && raster_y < WINDOW_HEIGHT)
	{
    // do a raytrace at the current pixel, and save the value to 'colors'
    my_raytrace(raster_x, raster_y, colors);

    if (colors[0] == -111 && colors[1] == -111 && colors[2] == -111) {
      // -111 is the code for a miss, so this means we didn't hit anything
      // do nothing
    }
    else {
    // print out the RGB values
    plotPixel(screen, raster_x, raster_y, colors[0], colors[1], colors[2], 1);

    glBindTexture(GL_TEXTURE_2D, texId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, raster_x, raster_y, 1, 1, GL_RGBA, GL_FLOAT, (void*)(screen + (raster_y*WINDOW_WIDTH+raster_x)));
    }
	}

	if (raster_x < WINDOW_WIDTH)
		raster_x++;     // haven't hit the end of the line, so move right

	if (raster_x == WINDOW_WIDTH)
	{                  // we hit the end of the line
		raster_x = 0;    // so reset our x position
		raster_y++;      // and move down a line
	}

	if (raster_y == WINDOW_HEIGHT) {
		glutPostRedisplay();        // only redraw once the whole scene is ready
	}	
}

// untouched
void resizeWindow(int width, int height)
{
	if (height == 0) // prevent div/0
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width/(double)height, 0.1, 4096.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// this is completely copied from hw5, except for the addition of
// a vector to return the results of the point hit
int my_raytrace_sphere(OBJECT *s, float *rayStart, float *rayDirection, float *result)
{
  int i, j, k;
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

void my_raytrace(int mousex, int mousey, GLfloat *return_values)
{
  double modelViewMatrix[16];
  double projMatrix[16];
  int viewport[4];
  int foundIntersection = 0;
  int hit = 0;
  int i, j, k;
  double clickPoint[3];
  float intersectionPoint[3];
  float closestPoint[3];
  float rayStart[3];
  float rayDirection[3];
  OBJECT *cur;

  float holdStart[3];
  float holdDirection[3];
  GLfloat sigma[3];
  GLfloat sigmaSum[3];
  GLfloat normals[3];
  GLfloat lightVec[3][3];

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

    hit = my_raytrace_sphere(cur, rayStart, rayDirection, &intersectionPoint[0]);

    // found intersection
    if (hit)
    {

      if (foundIntersection)
      {
        if (intersectionPoint[2] > closestPoint[2]) {
          closestPoint[0] = intersectionPoint[0];
          closestPoint[1] = intersectionPoint[1];
          closestPoint[2] = intersectionPoint[2];
        }
      }
      else
      {
        closestPoint[0] = intersectionPoint[0];
        closestPoint[1] = intersectionPoint[1];
        closestPoint[2] = intersectionPoint[2];
      }

      // so at this point we have our hit, now let's calculate some values

      foundIntersection = 1;

      // first make the normals for the shape, by subtracting out the
      // center of the shape from the point we hit
      for (j = 0; j < 3; j++) {
        normals[j] = intersectionPoint[j] - (cur->translate[j]);
      }
      normalize(normals);   // normalize that value

      // per light, find the light normals
      for (k = 0; k < num_lights; k++) {   // iterate through the lights
        for (j = 0; j < 3; j++) {          // and their xyz
          lightVec[k][j] = my_lights[k].pos[j]-intersectionPoint[j];
        }
      }

      // normalize each of the light vectors
      for (j = 0; j < num_lights; j++) {
        normalize(lightVec[k]);
      }

      // reinitialize these values to 0
      for (j = 0; j < 3; j++) {
        sigmaSum[j] = 0;
        sigma[j] = 0;
      }

      // for each channel in rgb, and for each light, apply the formula
      for (j = 0; j < 3; j++) {           // for r, g, b channels
        for (k = 0; k < num_lights; k++) {    // for the number of lights
          sigmaSum[j] += my_lights[k].diff[j]*(globalDif*(cur->diff[j]))*(dotprod(normals, lightVec[k]));
        }
      }

      for (i = 0; i < 3; i++) {
        return_values[i] = globalAmb[i]*(cur->amb[i]) + sigmaSum[i];
      }

    } // end of the foundIntersection if statement
  }   // end of the my_objects for loop iteration 

  if (foundIntersection)
  {
    // do nothing, since we already adjusted the return values above
  }
  else
  {
    // we didn't get a hit, so return the 'error' values so we know that
    return_values[0] = -111;
    return_values[1] = -111;
    return_values[2] = -111;
  }
}
