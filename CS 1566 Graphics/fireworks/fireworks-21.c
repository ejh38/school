/*********************************
 * fireworks.c
 * The main program for the firework display.
 * Copied in the ability to make and draw shapes.
 * For now, it displays 10 cylinders and you can press 'q' to quit.
 * As well as press '1' to rotate the 5th cylinder, so that you
 * can easily see they're 3d and not 2d. 
 */

#include "fireworks-21.h"
#include "bass.h"

FIREWORK test;
SOUND test_sound;

NOZZLE nozzles[NUM_NOZZLES];
EXPLOSION explosions[NUM_NOZZLES];

int curr_vs = 10;
int curr_rs = 10;

 
GLfloat cur_radius = 17;
GLfloat cur_density = 3;
int cur_quantity = 460;
GLfloat cur_cube_size = .007;
int cur_after_counter = 100;
int cur_shape = 1;

int cur_variable = RADIUS;

int timer_speed = 20;             // time in ms till next drop
short shift_camera = 0;   // change this value to set the camera at an angle

// for BASS
#define NUM_SOUNDS 9
DWORD sounds[NUM_SOUNDS];

int music_playing = 0;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("Fireworks");
	initGL();
  setup_BASS();
  setup_nozzles();

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

  srand((unsigned int)time(NULL));        // seed the rng

}

void setup_BASS()
{
  int i;
  if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
    printf("An incorrect version of BASS was loaded");
    return;
  }
  // setup output - default device
  if (!BASS_Init(-1,44100,0,0,NULL))
    exit(0);

    // this could probably be a simple for loop, but can't figure it out yet
    sounds[0] = BASS_StreamCreateFile(FALSE, "./sound/bang0.mp3", 0, 0, 0);
    sounds[1] = BASS_StreamCreateFile(FALSE, "./sound/bang1.mp3", 0, 0, 0);
    sounds[2] = BASS_StreamCreateFile(FALSE, "./sound/bang2.mp3", 0, 0, 0);
    sounds[3] = BASS_StreamCreateFile(FALSE, "./sound/bang3.mp3", 0, 0, 0);
    sounds[4] = BASS_StreamCreateFile(FALSE, "./sound/bang4.mp3", 0, 0, 0);
    sounds[5] = BASS_StreamCreateFile(FALSE, "./sound/bang5.mp3", 0, 0, 0);
    sounds[6] = BASS_StreamCreateFile(FALSE, "./sound/bang6.mp3", 0, 0, 0);
    sounds[7] = BASS_StreamCreateFile(FALSE, "./sound/fizz_out.wav", 0, 0, 0);
    sounds[8] = BASS_StreamCreateFile(FALSE, "./sound/1812.wav", 0, 0, 0);
    BASS_ChannelSetAttribute(sounds[7], BASS_ATTRIB_VOL, .2);
}

void setup_nozzles()
{
  int i;
  GLfloat trans_x;
  GLfloat trans_y;
  GLfloat trans_z;

  for (i = 0; i < NUM_NOZZLES; i++) {
    trans_x = -1 + (float)2/(float)NUM_NOZZLES + (2 - (float)2/(float)NUM_NOZZLES)*(float)i/(float)NUM_NOZZLES;
    trans_y = -.95;
    trans_z = .7;
    make_nozzle(&nozzles[i], .004, .12, i + 1);
    real_scaling(&(nozzles[i].shape), 1, .3, 1);
    real_translation(&(nozzles[i].shape), trans_x, trans_y, trans_z);
    
    nozzles[i].x = trans_x;
    nozzles[i].y = trans_y;
    nozzles[i].z = trans_z;
    
  }
}

void my_keyboard( unsigned char key, int x, int y ) 
{
  int num = rand() % (NUM_SOUNDS - 2);
  GLfloat new_radius = (float)((rand()%41 -20)/100.)*cur_radius +cur_radius;
  GLfloat new_density = (float)((rand()%41 -20)/100.)*cur_density +cur_density;
  int new_quantity = (int)((float)(rand()%41 -20)/100.)*cur_quantity +cur_quantity;
  GLfloat new_after_counter= (float)((rand()%41 -20)/100.)*cur_after_counter +cur_after_counter;
  //GLfloat cur_cube_size = .007;

  int cur_shape = 1;
  
  printf("num is %d", num);
  
  

  switch( key ) {

  case 'q': 
  case 'Q': {
    exit(0) ;
    break ; 
  }

  case '+':
  case '=': {
    if (cur_variable == RADIUS) {
      cur_radius += 2;
    }
    if (cur_variable == DENSITY) {
      cur_density += 1;
    }
    if (cur_variable == QUANTITY) {
      cur_quantity += 5;
    }
    if (cur_variable == CUBE_SIZE) {
      cur_cube_size += .001;
    }
    if (cur_variable == AFTER_COUNTER) {
      cur_after_counter += 10;
    }
    print_cur();
  } break;

  case '-':
  case '_': {
    if (cur_variable == RADIUS) {
      cur_radius -= 2;
    }
    if (cur_variable == DENSITY) {
      cur_density -= 1;
    }
    if (cur_variable == QUANTITY) {
      cur_quantity -= 5;
    }
    if (cur_variable == CUBE_SIZE) {
      cur_cube_size -= .001;
    }
    if (cur_variable == AFTER_COUNTER) {
      cur_after_counter -= 10;
    }
    print_cur();
  } break;


  case 'z': {
    music_playing = (music_playing + 1) % 2;
    if (music_playing) {
      BASS_ChannelPlay(sounds[8], FALSE);
    }
    else {
      BASS_ChannelPause(sounds[8]);
    }
  } break;



  case 'a':
  case 'A': {
    cur_variable = RADIUS;
    print_cur();
  } break;
  case 's':
  case 'S': {
    cur_variable = DENSITY;
    print_cur();
  } break;
  case 'd':
  case 'D': {
    cur_variable = QUANTITY;
    print_cur();
  } break;
  case 'f':
  case 'F': {
    cur_variable = CUBE_SIZE;
    print_cur();
  } break;
  case 'g':
  case 'G': {
    cur_variable = AFTER_COUNTER;
    print_cur();
  } break;

  case '1': {
  	 make_explosion(&explosions[0], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[0])->x, (&nozzles[0])->y + 1.2);
    //make_explosion(&explosions[0], 60, 1, 5000, .02, 48, 1, test_sound, (&nozzles[0])->x, (&nozzles[0])->y + 1);
    BASS_ChannelPlay(sounds[num], TRUE);

    break;
  }
  case '2': {
  	 make_explosion(&explosions[1], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[1])->x, (&nozzles[1])->y + 1.2);
    //make_explosion(&explosions[1], 500, 1, 100, .01, 1100, 1, test_sound, (&nozzles[1])->x, (&nozzles[1])->y + 1);
        BASS_ChannelPlay(sounds[num], TRUE);

    break;
  }
  case '3': {
  	 make_explosion(&explosions[2], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[2])->x, (&nozzles[2])->y + 1.2);
    //make_explosion(&explosions[2], 650, 1, 100, .05, 800, 1, test_sound, (&nozzles[2])->x, (&nozzles[2])->y + 1);
        BASS_ChannelPlay(sounds[num], TRUE);

    break;
  }
  case '4': {
  	 make_explosion(&explosions[3], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[3])->x, (&nozzles[3])->y + 1.2);
    //make_explosion(&explosions[3], 1000, 1, 100, .05, 900, 1, test_sound, (&nozzles[3])->x, (&nozzles[3])->y + 1);
        BASS_ChannelPlay(sounds[num], TRUE);

    break;
  }
  case '5': {
  	 make_explosion(&explosions[4], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[4])->x, (&nozzles[4])->y + 1.2);
    //make_explosion(&explosions[4], 1500, 1, 100, .1, 1000, 1, test_sound, (&nozzles[4])->x, (&nozzles[4])->y + 1);
        BASS_ChannelPlay(sounds[num], TRUE);

    break;
  }
  case '6': {
  	 make_explosion(&explosions[5], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[5])->x, (&nozzles[5])->y + 1.2);
    //make_explosion(&explosions[5], 600, 1, 100, .09, 1100, 1, test_sound, (&nozzles[5])->x, (&nozzles[5])->y + 1);
        BASS_ChannelPlay(sounds[num], TRUE);

    break;
  }
  case '7': {
  	 make_explosion(&explosions[6], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[6])->x, (&nozzles[6])->y + 1.2);
    //make_explosion(&explosions[6], 2500, 1, 100, .3, 1200, 1, test_sound, (&nozzles[6])->x, (&nozzles[6])->y + 1);
        BASS_ChannelPlay(sounds[num], TRUE);

    break;
  }
  case '0': {
  	
    make_explosion(&explosions[3], new_radius, new_density, new_quantity, cur_cube_size, new_after_counter, cur_shape, test_sound, (&nozzles[3])->x, (&nozzles[3])->y + 1);
  } break;

  default: break;
  }

  glutPostRedisplay();
}

void print_cur() {
  printf("\nHere's a dump of the cur_variables:\n");
  printf("cur_radius: %f, cur_density: %f\n", cur_radius, cur_density);
  printf("cur_quantity: %d, cur_cube_size: %f\n", cur_quantity, cur_cube_size);
  printf("cur_after_counter: %d\n", cur_after_counter);
  printf("You're adjusting %d\n", cur_variable);
  printf("Where RADIUS 0, DENSITY 1, QUANTITY 2,\nCUBE_SIZE 3, SHAPE 4, AFTER_COUNTER 5\n");
  printf("firework with quantity 200 is %ld\n", sizeof(&explosions[3]) + 200*sizeof(PARTICLE));
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

    draw_shape(&(cur->shape), colors[BLUE]);
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

      draw_shape(&(cur->shape), cur->init_color);
    }
  }
}

// this works for all shapes
void draw_shape(SHAPE *verts, GLfloat* color)
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
  short solid = rand()%2;
  GLfloat color[3];
  if(solid){
  		for(i=0;i<3;++i){
  			color[i] =(float)((rand() % (100)))/100.;			//randomize color
  		}
  }
  else{
  	 	for(i=0;i<3;++i){
  			color[i] =0;
  		}
  
  }
  	
  SHAPE cur;
  GLfloat trans_x, trans_y, trans_z;
  GLfloat ray = cube_size;
  
  start_y +=(float)((rand() % (7)) - 3)/10.;
  start_x +=(float)((rand() % (11)) - 5)/100.;

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
  po -> fizz=0;
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
      


      trans_x = ray * cos(phi) * cos(theta) + (float)((rand() % (3)) - 1)/80.;
      trans_y = ray * sin(phi) + (float)((rand() % (3)) - 1)/80.;
      trans_z = -ray * cos(phi) * sin(theta) + (float)((rand() % (3)) - 1)/80.;
    
      make_particle(&(po->particles[i*4 + j]), color, colors[BLACK], solid, colors[RED],
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
      
      trans_x = ray * cos(phi) * cos(theta) + (float)((rand() % (3)) - 1)/100.;;
      trans_y = ray * sin(phi) + (float)((rand() % (3)) - 1)/100.;;
      trans_z = -ray * cos(phi) * sin(theta) + (float)((rand() % (3)) - 1)/100.;;
    
      make_particle(&(po->particles[count - 1 + i*4 + j]), colors[RED], colors[BLACK], solid, colors[RED],
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
  	if(!single_color)
  		init_color[i] =(float)((rand() % (100)))/100.;			//randomize color
  		
  		
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


void draw_quads(GLfloat vertices[12][12][4], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, GLfloat* color)
{
  glMatrixMode(GL_MODELVIEW);
  
  glBegin(GL_POLYGON); 
  {
    glColor3fv(color);    

    glVertex4fv(vertices[iv1a][iv1b]);
    glVertex4fv(vertices[iv2a][iv2b]);
    glVertex4fv(vertices[iv3a][iv3b]);
    glVertex4fv(vertices[iv4a][iv4b]);
  }
  
  glEnd();
}

void my_time_out(int id) { 
  int i, j,k;
  
  PARTICLE *cur;
  EXPLOSION *cur_explosion;
  float fall_time;
  for (j = 0; j < NUM_NOZZLES; j++) {
    
    cur_explosion = &explosions[j];
    for (i = 0; i < (&explosions[j])->quantity; i++) {
    
      cur = &(cur_explosion->particles[i]);
    
      if (cur_explosion->counter < cur_explosion->radius) {
        real_translation(&(cur->shape), cur->translation[0], cur->translation[1], cur->translation[2]);
      }
    
      else {
    
        if (cur_explosion->counter > cur_explosion->radius && cur_explosion->counter < cur_explosion->radius + cur_explosion->after_counter && cur_explosion -> radius > 0) {
          fall_time =(float)((rand() % (10)))/100000.;
          real_translation(&(cur->shape), 0, -fall_time*5, 0);
          cur->init_color[0]=cur->init_color[0]-250*fall_time;
          cur->init_color[1]=cur->init_color[1]-250*fall_time;
          cur->init_color[2]=cur->init_color[2]-250*fall_time;
          if(!cur_explosion->fizz){
         // 	BASS_ChannelPlay(sounds[7], TRUE);
          	cur_explosion->fizz=1;
          	
          }
          // TODO THIS IS WHERE WE WANT TO START FADING AS WELL
        }

        if (cur_explosion->counter > cur_explosion->after_counter && cur_explosion -> radius > 0) {
          printf("Resetting explosion for key %d\n", j+1);
          cur_explosion->fizz=0;
          free(&(cur_explosion->particles[0]));
          cur_explosion -> radius = 0;
          cur_explosion -> density = 0;
          cur_explosion -> quantity = 0;
          cur_explosion -> cube_size = 0;
          cur_explosion -> shape = 0;
          cur_explosion -> counter = 0;
          cur_explosion -> start_x = 0;
          cur_explosion -> start_y = 0;
          cur_explosion -> after_counter = 0;
        }
      }  
    }
    if (cur_explosion->radius > 0) {
      cur_explosion->counter += 1;
    }
  }
  glutPostRedisplay();                       // re-draw the scene
  glutTimerFunc(timer_speed, my_time_out, 0); // keeps the timer moving, at timer_speed ms

}
