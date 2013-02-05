/*********************************
 * fireworks.c
 * The main program for the firework display.
 * Copied in the ability to make and draw shapes.
 * For now, it displays 10 cylinders and you can press 'q' to quit.
 * As well as press '1' to rotate the 5th cylinder, so that you
 * can easily see they're 3d and not 2d. 
 */

#include "fireworks-14.h"

FIREWORK test;
SOUND test_sound;

NOZZLE nozzles[NUM_NOZZLES];
PARTICLE particles[NUM_NOZZLES];
EXPLOSION explosions[NUM_NOZZLES];

int curr_vs = 10;
int curr_rs = 10;

int cur_quantity = 64; 

int timer_speed = 20;             // time in ms till next drop
short shift_camera = 1;   // change this value to set the camera at an angle


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("Fireworks");

	initGL();
  setup_nozzles();
//  setup_particles();


	glutDisplayFunc(my_display);
  glutKeyboardFunc(my_keyboard);
  glutTimerFunc( timer_speed, my_time_out, 0);/* schedule a my_TimeOut call with the ID 0 in 20 seconds from now */

	glutMainLoop();

	return 0;
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);

  if (shift_camera) {
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluPerspective( 40, 1.0, 1, 200.0);
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;  // init modelview to identity
  }
}

void setup_nozzles()
{
  int i;
  GLfloat trans_x;
  GLfloat trans_y;

  for (i = 0; i < NUM_NOZZLES; i++) {
    trans_x = -1 + (float)2/(float)NUM_NOZZLES + (2 - (float)2/(float)NUM_NOZZLES)*(float)i/(float)NUM_NOZZLES;
    trans_y = -.95;
    make_nozzle(&nozzles[i], .008, .25, i + 1);
    real_scaling(&(nozzles[i].shape), 1, .3, 1);
    real_translation(&(nozzles[i].shape), trans_x, trans_y, 0);
    
    nozzles[i].x = trans_x;
    nozzles[i].y = trans_y;
  }
}

void setup_particles()
{
  int i;
  for (i = 0; i < NUM_NOZZLES; i++) {
    spawn_particle(i);
  }    

}

void spawn_particle(int i)
{
  SHAPE cur;
  NOZZLE *cur_nozzle;

  cur_nozzle = &nozzles[i];
  make_cube_smart(&cur, .1);
  make_particle(&particles[i], colors[RED], colors[BLACK], 1, colors[RED], colors[BLACK], 0, 0, cur, 0, .05, 0);
  real_translation(&(particles[i].shape), cur_nozzle->x, cur_nozzle->y + .1, 0);
}

void my_keyboard( unsigned char key, int x, int y ) 
{
  switch( key ) {
  case 'q': 
  case 'Q':
    exit(0) ;
    break ; 
  case '+':
  case '=': {
    cur_quantity++;
    printf("quantity is %d\n", cur_quantity);
  } break;
  case '-':
  case '_': {
    cur_quantity--;
    printf("quantity is %d\n", cur_quantity);
  } break;

  case '1': {
    
    make_explosion(&explosions[0], 1000, 1, 100, .02, 600, 1, test_sound, (&nozzles[0])->x, (&nozzles[0])->y + 1);
    
    break;
  }
  case '2': {
    make_explosion(&explosions[1], 500, 1, 100, .01, 1100, 1, test_sound, (&nozzles[1])->x, (&nozzles[1])->y + 1);
    
    break;
  }
  case '3': {
    make_explosion(&explosions[2], 650, 1, 100, .05, 800, 1, test_sound, (&nozzles[2])->x, (&nozzles[2])->y + 1);
    
    break;
  }
  case '4': {
    make_explosion(&explosions[3], 1000, 1, 100, .05, 900, 1, test_sound, (&nozzles[3])->x, (&nozzles[3])->y + 1);
    
    break;
  }
  case '5': {
    make_explosion(&explosions[4], 1500, 1, 100, .1, 1000, 1, test_sound, (&nozzles[4])->x, (&nozzles[4])->y + 1);
    
    break;
  }
  case '6': {
    make_explosion(&explosions[5], 600, 1, 100, .09, 1100, 1, test_sound, (&nozzles[5])->x, (&nozzles[5])->y + 1);
    
    break;
  }
  case '7': {
    make_explosion(&explosions[6], 2500, 1, 100, .3, 1200, 1, test_sound, (&nozzles[6])->x, (&nozzles[6])->y + 1);
    
    break;
  }
  default: break;
  }

  glutPostRedisplay();
}

void my_display()
{
 glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

 if (shift_camera) {
    glLoadIdentity();
    //setup the camera (1st person? 3rd person?)

    gluLookAt(3, 0, 6,
        0, 0, 0,
        0, 1, 0);
  }
  else {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  }

  draw_nozzles();
  draw_particles();
  draw_explosion();

  if (!shift_camera) {
    // restore projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  }
  glutSwapBuffers();
}

void draw_nozzles() {
  int i;
  GLfloat v1[4];
  GLfloat v2[4];

  for (i = 0; i < NUM_NOZZLES; i++) {
    NOZZLE *cur;
    cur = &nozzles[i];

    curr_rs = CYLINDER_RS;
    curr_vs = CYLINDER_VS;

    draw_shape(&(cur->shape), BLUE);
  }

}

void draw_particles() 
{
  int i;
  for (i = 0; i < NUM_NOZZLES; i++) {
    PARTICLE *cur;
    cur = &particles[i];

    curr_rs = CUBE_RS;
    curr_vs = CUBE_VS;

    draw_shape(&(cur->shape), RED);
  }
}

void draw_explosion()
{
  int i, j;
  for (j = 0; j < NUM_NOZZLES; j++) {
    for (i = 0; i < (&explosions[j])->quantity; i++) {
      PARTICLE *cur;
      cur = &((&explosions[j])->particles[i]);

      curr_rs = CUBE_RS;
      curr_vs = CUBE_VS;

      draw_shape(&(cur->shape), RED);
    }
  }
}

void draw_objects(SHAPE *my_objects, int num_objects) {
  
  int i;

  // this for loop draws the nozzles
  for(i = 0; i < num_objects; i++) {
    SHAPE *cur;
    cur = &my_objects[i];

    switch(cur->shape_id) {
      case CUBE: //cube
      {
        curr_rs = CUBE_RS;
        curr_vs = CUBE_VS;
      }break;
      case CYLINDER: // cylinder
      {
        curr_rs = CYLINDER_RS;
        curr_vs = CYLINDER_VS;
      }break;
    }
    draw_shape(cur, BLUE);

  }

}

// this works for all shapes
void draw_shape(SHAPE *verts, int color)
{
  int i, j; // loop variables 
  
  for(i = 0; i < curr_vs; i++) {  // handles main body of array
    for(j = 0; j < curr_rs; j++) {
      draw_quads(verts->shape_verts, i, j, i, j+1, i+1, j+1, i+1, j, color); // draws shape
    }
  }
  for (i = 0; i < curr_vs; i ++) {  // connects the sides
    draw_quads(verts->shape_verts, i, curr_rs, i+1, curr_rs, i+1, 0, i, 0, color);
  }

  // this handles the cube top
  if (curr_rs == CUBE_RS && curr_vs == CUBE_VS) {
    for(i = 0; i < 2; i++) {  
    draw_quads(verts->shape_verts, curr_vs - i, 0, curr_vs - i, 1, curr_vs - i, 2, curr_vs - i, 3, color); 
    }
  }

}

void real_translation(SHAPE *po, GLfloat x, GLfloat y, GLfloat z) {
  int i, j;

  for(i = 0; i <= curr_vs; i++) {
    for(j = 0; j <= curr_rs; j++) {
      po->shape_verts[i][j][0] += x; // translate across x
      po->shape_verts[i][j][1] += y; // translates across y
      po->shape_verts[i][j][2] += z; // translates across z
    }
  }
  
}

void real_scaling(SHAPE *po, GLfloat sx, GLfloat sy, GLfloat sz) {
  int i, j;
  
  for(i = 0; i <= curr_vs; i++) {
    for(j = 0; j <= curr_rs; j++) {
      po->shape_verts[i][j][0] = po->shape_verts[i][j][0] * sx; // scales x
      po->shape_verts[i][j][1] = po->shape_verts[i][j][1] * sy; // scales y
      po->shape_verts[i][j][2] = po->shape_verts[i][j][2] * sz; // scales z
    }
  }
  
}

void real_rotation(SHAPE *po, GLfloat deg, GLfloat x, GLfloat y, GLfloat z) { 
  int i, j;

  GLfloat theta = (deg * M_PI/180); // deg to rotate by
  
  for(i = 0; i <= curr_vs; i++) {
    for(j = 0; j <= curr_rs; j++) {
      GLfloat X = po->shape_verts[i][j][0];
      GLfloat Y = po->shape_verts[i][j][1];
      GLfloat Z = po->shape_verts[i][j][2];
     
      if(x == 1) {    // rotate X
        po->shape_verts[i][j][1] = Y * cos(theta) - Z * sin(theta); 
        po->shape_verts[i][j][2] = Z * cos(theta) + Y * sin(theta);
      }
      else if(y ==1) {  // rotate Y             
        po->shape_verts[i][j][0] = X * cos(theta) + Z * sin(theta);
        po->shape_verts[i][j][2] = Z * cos(theta) - X * sin(theta);
      }
      else if (z ==1) { // rotate Z
        po->shape_verts[i][j][0] = X * cos(theta) - Y * sin(theta); 
        po->shape_verts[i][j][1] = X * sin(theta) + Y * cos(theta);
      }
    }
  }

}

// quantity needs to be a square number
void make_explosion(EXPLOSION *po, GLfloat radius, GLfloat density, 
                          int quantity, GLfloat cube_size, int after_counter,
                          short shape, SOUND sound, GLfloat start_x, GLfloat start_y) {
  int i, j, k;
  int count = 0;
  SHAPE cur;
  GLfloat trans_x, trans_y, trans_z;
  GLfloat ray = cube_size;

  po -> radius = radius;
  po -> density = density;
  po -> quantity = quantity;
  po -> cube_size = cube_size;
  po -> shape = shape;
  po -> sound = sound;
  po -> counter = 0;
  po -> start_x = start_x;
  po -> start_y = start_y;
  po -> after_counter = after_counter + radius;

  po -> particles = malloc(quantity*sizeof(PARTICLE));

  k = sqrt(quantity)/2;

  // draw the top half
  for (i = 0; i <= k; i++) {
    for (j = 0; j <= k; j++) {

      make_cube_smart(&cur, ray);
      real_translation(&cur, start_x, start_y, 0);

      int t = (360.0/(float)(k) * j);    // theta
      int p = (180.0/(float)(k) * i); // phi

      GLfloat theta = (t * M_PI/180.); // theta angle
      GLfloat phi = (p * M_PI/180.);  // phi angle
      
      trans_x = ray * cos(phi) * cos(theta);
      trans_y = ray * sin(phi);
      trans_z = -ray * cos(phi) * sin(theta);
    
      make_particle(&(po->particles[i*4 + j]), colors[RED], colors[BLACK], 1, colors[RED],
                   colors[BLACK], 1, 1000, cur, trans_x, trans_y, trans_z);
      count++;
    }
  }
  // draw the bottom half
  for (i = 0; i <= k; i++) {
    for (j = 0; j <= k; j++) {

      make_cube_smart(&cur, ray);
      real_translation(&cur, start_x, start_y, 0);

      int t = (360.0/(float)(k) * j);    // theta
      int p = (180.0/(float)(k) * i - 180); // phi

      GLfloat theta = (t * M_PI/180.); // theta angle
      GLfloat phi = (p * M_PI/180.);  // phi angle
      
      trans_x = ray * cos(phi) * cos(theta);
      trans_y = ray * sin(phi);
      trans_z = -ray * cos(phi) * sin(theta);
    
      make_particle(&(po->particles[count - 1 + i*4 + j]), colors[RED], colors[BLACK], 1, colors[RED],
                   colors[BLACK], 1, 1000, cur, trans_x, trans_y, trans_z);
    }
  }
}

void make_particle(PARTICLE *po, GLfloat *init_color, GLfloat *init_brightness,
                            short single_color, GLfloat *end_color, 
                            GLfloat *end_brightness, short interpolate_how, 
                            GLfloat duration, SHAPE shape,
                            GLfloat trans_x, GLfloat trans_y, GLfloat trans_z) {
  // just put it all in
  int i;
  for (i = 0; i < 3; i++) {
    po -> init_color[i] = init_color[i];
    po -> init_brightness[i] = init_brightness[i];
    po -> end_color[i] = end_color[i];
    po -> end_brightness[i] = end_brightness[i];
  }
  po->single_color = single_color;

  po -> interpolate_how = interpolate_how;
  po -> duration = duration;
  po -> shape = shape;

  po -> translation[0] = trans_x;
  po -> translation[1] = trans_y;
  po -> translation[2] = trans_z;


}

void make_nozzle(NOZZLE* noz, double ray, double height, int id){
  SHAPE cyl;
  make_cylinder(&cyl, ray, height);
  noz->shape = cyl;
  noz->cur_firework = 0;    // at position 0 in the fireworks array
  noz->nozzle_id = id;      // set the nozzle id

  // TODO -- set the array of fireworks that are in the nozzle  

}

void make_cube_smart(SHAPE *po, double size){
  size = size/2;

  // top
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

  po->shape_id = CUBE;
  
}

void make_cylinder(SHAPE *vert, double ray, double height){
  int i,j,k;

  for(i = 0; i <= curr_vs; i++) {   // iterates through the angles
    for(j = 0; j <= curr_rs; j++) { // iterates through the layers
    
      int t = (360/curr_rs * j);    // theta        
      GLfloat theta = (t * M_PI/180); // theta angle
      
      for(k = 0; k < 4; k++) {      // iterates through x,y,z coordinates
        switch(k){
          case 0:
            vert->shape_verts[i][j][k] = ray * cos(theta); break; // x coordinate
          case 1:
            vert->shape_verts[i][j][k] = (height/curr_vs * i) - height/2; break; // y coordinate
          case 2:
            vert->shape_verts[i][j][k] = ray * sin(theta); break; // z coordinate
          case 3:
            vert->shape_verts[i][j][k] = 1; // homogenious coordinate
        }
      }
    }
  }

  vert->shape_id = CYLINDER;

}


void draw_quads(GLfloat vertices[12][12][4], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic)
{
  glMatrixMode(GL_MODELVIEW);
  
  glBegin(GL_LINE_LOOP); 
  {
    glColor3fv(colors[ic]);    

    glVertex4fv(vertices[iv1a][iv1b]);
    glVertex4fv(vertices[iv2a][iv2b]);
    glVertex4fv(vertices[iv3a][iv3b]);
    glVertex4fv(vertices[iv4a][iv4b]);
  }
  
  glEnd();
}

void my_time_out(int id) { 
  int i, j;
  PARTICLE *cur;
  EXPLOSION *cur_explosion;
  for (i = 0; i < NUM_NOZZLES; i++) {
    cur = &particles[i];
    real_translation(&(particles[i].shape), cur->translation[0], cur->translation[1], cur->translation[2]);
  }
  for (j = 0; j < NUM_NOZZLES; j++) {
    for (i = 0; i < (&explosions[j])->quantity; i++) {
      cur_explosion = &explosions[j];
      cur = &(cur_explosion->particles[i]);
      if (cur_explosion->counter < cur_explosion->radius) {
        real_translation(&(cur->shape), cur->translation[0], cur->translation[1], cur->translation[2]);
      }
      else {
        if (cur_explosion->counter > cur_explosion->after_counter && cur_explosion -> radius > 0) {
          printf("Resetting explosion for key %d\n", j+1);
          free(&(cur_explosion->particles[0]));
          cur_explosion -> radius = 0;
          cur_explosion -> density = 0;
          cur_explosion -> quantity = 0;
          cur_explosion -> cube_size = 0;
          cur_explosion -> shape = 0;
          cur_explosion -> counter = 0;
          cur_explosion -> start_x = 0;
          cur_explosion -> start_y = 0;
          cur_explosion -> after_counter =0;
        }
      }
      if (cur_explosion->radius > 0) {
        cur_explosion->counter += 1;
      }
    }
  }
  glutPostRedisplay();                       // re-draw the scene
  glutTimerFunc(timer_speed, my_time_out, 0); // keeps the timer moving, at timer_speed ms

}
