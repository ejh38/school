/*********************************
 * fireworks.c
 * The main program for the firework display.
 * For now, just some basic setup copied from glhello.c (hw1 support)
 * And a little from ray_trace.c
 * For now, it displays a quad and you can press 'q' to quit.
 */

#include "fireworks-1.h"

FIREWORK test;
SHAPE nozzles[NUM_NOZZLES];

int num_objects = 50;
SHAPE *my_objects;

int curr_vs = 10;
int curr_rs = 10;

int main(int argc, char **argv)
{
	// see if the structs all compiled and work together
	test.id = 3;
	printf("test.id is %d\nHeck yes!\n", test.id);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("Fireworks");

	initGL();
  my_setup();

	glutDisplayFunc(my_display);
  glutKeyboardFunc(my_keyboard);

	glutMainLoop();

	return 0;
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
}

void my_setup()
{
  int i;
  for (i = 0; i < 10; i++) {
    make_cylinder(&nozzles[i], .1, .1);
    real_scaling(&nozzles[i], 1, i, 1);
    real_translation(&nozzles[i], ((float)i - (float)5)/(float)5, 0, 0);
  }
}

void my_keyboard( unsigned char key, int x, int y ) 
{
  switch( key ) {
  case 'q': 
  case 'Q':
    exit(0) ;
    break ; 
  case '1': {
    real_rotation(&nozzles[4], 30, 1, 0, 0);
    break;
  }

  default: break;
  }

  glutPostRedisplay();
}

void my_display()
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  draw_nozzles();

  // restore projection
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glutSwapBuffers();
}


void draw_nozzles() {
  int i;

  for (i = 0; i < NUM_NOZZLES; i++) {
    SHAPE *cur;
    cur = &nozzles[i];

    curr_rs = CYLINDER_RS;
    curr_vs = CYLINDER_VS;

    draw_shape(cur);
  }

}

void draw_objects() {
  
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
        draw(cur);
      }break;
      case SPHERE: // sphere
      {
        curr_rs = SPHERE_RS;
        curr_vs = SPHERE_VS;
        draw_shape(cur);
      }break;
      case CYLINDER: // cylinder
      {
        curr_rs = CYLINDER_RS;
        curr_vs = CYLINDER_VS;
        draw_shape(cur);
      }break;
      case CONE: // cone
      {
        curr_rs = CONE_RS;
        curr_vs = CONE_VS;
        draw_shape(cur);
      }break;
    }
  }

}

// this draws all but the cubes and houses
void draw_shape(SHAPE *verts)
{
  int i, j; // loop variables 
  
  for(i = 0; i < curr_vs; i++) {  // handles main body of array
    for(j = 0; j < curr_rs; j++) {
      draw_quads(verts->shape_verts, i, j, i, j+1, i+1, j+1, i+1, j, BLUE); // draws shape
    }
  }
  for (i = 0; i < curr_vs; i ++) {  // connects the sides
    draw_quads(verts->shape_verts, i, curr_rs, i+1, curr_rs, i+1, 0, i, 0, BLUE);
  }

}

// draws the cube and house
void draw(SHAPE *verts) 
{ 
  int i, j; // loop variables
  
  for(i = 0; i < curr_vs; i++) {  // handles main body of array
    for(j = 0; j < curr_rs; j++) {
      draw_quads(verts->shape_verts, i, j, i, j+1, i+1, j+1, i+1, j, RED); // draws shape
    }
  }
  
  for (i = 0; i < curr_vs; i ++) {    // connects the sides
    // textures can be manipulated on the stack as well
    draw_quads(verts->shape_verts, i, curr_rs, i+1, curr_rs, i + 1, 0, i, 0, RED);
  } 
  
  for(i = 0; i < 2; i++) {    // draws tops of house and cube
    draw_quads(verts->shape_verts, curr_vs - i, 0, curr_vs - i, 1, curr_vs - i, 2, curr_vs - i, 3, RED); 
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

}

void make_sphere(SHAPE *vert, double ray) {
  int i,j,k; 
    
  for(i = 0; i <= curr_vs; i++) {   // iterates through the angles
    for(j = 0; j <= curr_rs; j++) { // iterates through the layers
   
      int t = (360/curr_vs * j);    // theta
      int p = (180/curr_rs * i) - 90; // phi
      
      GLfloat theta = (t * M_PI/180); // theta angle
      GLfloat phi = (p * M_PI/180);   // phi angle
      
      for(k = 0; k < 4; k++) {    // iterates through x,y,z coordinates
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
    }
  }

}

void make_cone(SHAPE *vert, double height, double ray)
{
  int i,j,k; // initial variables to use outside of loops
  
  for(i = 0; i <= curr_vs; i++) {     // iterates through the angles
    for(j = 0; j <= curr_rs; j++) {   // iterates through the layers
  
      int t = 360/curr_rs * j;      // next angle
      GLfloat theta = (t * M_PI/180); // angle
      
      for(k = 0; k < 4; k++) {    // iterates through x,y,z coordinates
        switch(k){
          case 0:
            vert->shape_verts[i][j][k] = (height - (height/curr_vs * i))/height * ray * cos(theta);break;   // x coordinate
          case 1:
            vert->shape_verts[i][j][k] = (height/curr_vs * i);break;  // y coordinate
          case 2:
            vert->shape_verts[i][j][k] = (height - (height/curr_vs * i))/height * ray * sin(theta); break; // z coordinate
          case 3:
            vert->shape_verts[i][j][k] = 1; // homogenious coordinate
        }
      }
    } 
  } 

  // fix wrap around
  for(i = 0; i < curr_rs; i++){
    vert->shape_verts[i][curr_vs+1][0] = vert->shape_verts[i][0][0];
    vert->shape_verts[i][curr_vs+1][1] = vert->shape_verts[i][0][1];
    vert->shape_verts[i][curr_vs+1][2] = vert->shape_verts[i][0][2];
  } 
  
  for(i = 0; i < curr_vs; i++){
    vert->shape_verts[curr_rs + 1][i][0] = vert->shape_verts[0][i][0];
    vert->shape_verts[curr_rs + 1][i][1] = vert->shape_verts[0][i][1];
    vert->shape_verts[curr_rs + 1][i][2] = vert->shape_verts[0][i][2];
  }

}

void make_torus(SHAPE *vert, double R, double r)
{
  int i,j,k; 

  for(i = 0; i <= curr_rs; i++) {     // iterates through the Fmys
    GLfloat theta = (2 * M_PI * i)/curr_rs; // angle
    
    for(j = 0; j <= curr_vs; j++) {   // iterates through the layers

      GLfloat phi = (2 * M_PI * j)/curr_vs; // angle
      
      for(k = 0; k < 4; k++) {    // iterates through x,y,z coordinates
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
    } 
  } 

}


void draw_quads(GLfloat vertices[121][121][4], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic)
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
