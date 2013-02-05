/***************************************************
 FILE: glmain.c
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/

#include "glmain.h"
#define my_assert(X,Y) ((X)?(void) 0:(printf("error:%s in %s at %d", Y, __FILE__, __LINE__), myabort()))

#ifndef min
#define min(a,b) ((a) < (b)? a:b)
#endif
#define FALSE 0 
#define TRUE  1

/*******************************************
			Variable Declarations
*******************************************/			

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

/*******************************************
			Helper Functions
*******************************************/

void myabort(void) {
	abort();
	exit(1); /* exit so g++ knows we don't return. */
} 

void my_reshape(int w, int h) {
	// ensure a square view port
	glViewport(0,0,min(w,h),min(w,h)) ;
	return ;
}
void my_display() {
	
	// clear all pixels, reset depth 
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );
	
	glLoadIdentity();
	//setup the camera (1st person? 3rd person?)
	
	if(firstPersonView == 0)
	{
		gluLookAt(10,10,75,10,10,20,0,1,0);
	}else
	{
		
		gluLookAt(my_cam.pos[0],my_cam.pos[1], my_cam.pos[2],
				  my_cam.at[0],my_cam.at[1],my_cam.at[2],
				  my_cam.up[0], my_cam.up[1], my_cam.up[2]);
	}
	
	//update the flashlight to follow the person
	 
	glLightfv(GL_LIGHT0, GL_POSITION, my_cam.at);
	
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, my_cam.dir);
	
	//draw the objects

	draw_axes();
	
	draw_objects();
	
	// this buffer is ready
	
	glutSwapBuffers();
}

void my_idle(void) {
	//EC idea: Make the flashlight flicker a bit (random flicker strength) when the user is idle.
	return ;
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
/*******************************************
					Main
*******************************************/	

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

/*******************************************
					Setup
*******************************************/	

void glut_setup (){
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	
	glutInitWindowSize(700,700);
	glutInitWindowPosition(20,20);
	glutCreateWindow("CS1566 Project 5");
	
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
	gluPerspective(20, 1.0, 0.1, 200.0);
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;  // init modelview to identity
	
	// toggle to smooth shading (instead of flat)
	glShadeModel(GL_SMOOTH); 
	lighting_setup();
	texture_setup();
	
	return;
}

void my_setup(int argc, char **argv){
	
	firstPersonView = 1;
	bogus = 1;
	num_objects = num_lights = 0;
	
	// initialize global shape defaults and mode for drawing
	crt_render_mode = GL_POLYGON;
	crt_shape = 0;
	
	crt_rs = 90;
	crt_vs = 90; 
	
	my_assert(argc >1, "need to supply a spec file");
	read_spec(argv[1]);
	return;
}

/*******************************************
				Parse Scene
*******************************************/	

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
	printf("%d",po->sid);
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
		case 0: // makes house
			make_house(po);
			break;
		case 1: //cube
			make_cube_smart(po, 1);
			break;
		case 2:
			make_sphere(po, 1);
			break;
		case 3:
			make_cone(po, 1, 1);
			break;
		case 4:
			make_torus(po, 1.2, .1);
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
			case '0': // house
			case '1': //cube
			case '2': // sphere	
			case '3': // cone
			case '4': // torus
				//read in the shape
			{
				printf("parse object");
				parse_obj(buffer);
			}	break;
				//etc
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

/*******************************************
			Lighting Setup
*******************************************/	

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

  // reflective propoerites -- global ambiant light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

  glLightfv(GL_LIGHT0, GL_POSITION, my_cam.at);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, my_cam.dir);

  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);

  glEnable(GL_LIGHT0);

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

/*******************************************
			I/O Devices
*******************************************/	

void my_keyboard( unsigned char key, int x, int y ) {
	
	int i;
	
	switch( key ) {
		case 'd':
			my_trans(1,0,0);
			glutPostRedisplay() ;
			break;
		case 'a':
			my_trans(-1,0,0);
			glutPostRedisplay() ;
			break;
		case 'w':
			my_trans(0,0,-1);
			glutPostRedisplay();
			break;
		case 's':
			my_trans(0,0,1);
			glutPostRedisplay();
			break;
		case 'q': 
		case 'Q':
			exit(0);
			break;	
		default: break;
	}
	return ;
}

void my_mouse_drag(int x, int y) {
}

void my_mouse(int button, int state, int mousex, int mousey) {
	
	switch( button ) {
			
		case GLUT_LEFT_BUTTON:
			if( state == GLUT_DOWN ) {
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

/*******************************************
			Linear Algebra
*******************************************/	

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


/*******************************************
			Drawing Functions
*******************************************/

void draw_shape(OBJECT *verts)
{
	
	int i, j; // loop variables 
	// polymorphic way to draw shapes
	
	glClearColor(0,0,0,0); // else black
	
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

void draw_quads(GLfloat vertices[121][121][4], GLfloat normals[121][121][4], GLfloat tex[121][121][2], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic)
{
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(-1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	glBegin(crt_render_mode); 
	{
//		glColor3fv(colors[ic]);
		glNormal3fv(normals[iv1a][iv1b]);
		
		glTexCoord2fv(tex[iv1a][iv1b]);
		glVertex4fv(vertices[iv1a][iv1b]);
		glTexCoord2fv(tex[iv2a][iv2b]);
		glVertex4fv(vertices[iv2a][iv2b]);
		glTexCoord2fv(tex[iv3a][iv3b]);
		glVertex4fv(vertices[iv3a][iv3b]);
		glTexCoord2fv(tex[iv4a][iv4b]);
		glVertex4fv(vertices[iv4a][iv4b]);
	}
	
	glEnd();
}

void draw(OBJECT *verts) // draws the cube and house
{	
	int i, j; // loop variables

	// polymorphic way to draw shapes
	
	glClearColor(0,0,0,0); // else black
	
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

void draw_cube(GLfloat vertices[121][121][4], GLfloat normals[121][121][4], GLfloat tex[4][2], int iv1a, int iv1b, int iv2a, int iv2b, int iv3a, int iv3b, int iv4a, int iv4b, int ic)
{	
	glBegin(crt_render_mode); 
	{
		//glColor3fv(colors[ic]);
		
		/*note the explicit use of homogeneous coords below: glVertex4f*/
		glNormal3fv(normals[iv1a][iv1b]);
	
		glTexCoord2fv(tex[0]);
		glVertex4fv(vertices[iv1a][iv1b]);
		glTexCoord2fv(tex[1]);
		glVertex4fv(vertices[iv2a][iv2b]);
		glTexCoord2fv(tex[2]);
		glVertex4fv(vertices[iv3a][iv3b]);
		glTexCoord2fv(tex[3]);
		glVertex4fv(vertices[iv4a][iv4b]);
	}
	
	glEnd();
}

void draw_axes( void ) {
	glLineWidth( 5.0 );
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
			
			case 0: // house
			{
				crt_rs = 3;
				crt_vs = 2;
				glBindTexture(GL_TEXTURE_2D, tex_names[WINDOWIMG_TEX]);
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
				draw(cur);
				glDisable(GL_TEXTURE_2D);
				
			}break;
			case 1: //cube
			{
				crt_rs = 3;
				crt_vs = 1;
				glBindTexture(GL_TEXTURE_2D, tex_names[BRICKIMG_TEX]);
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
				draw(cur);
				glDisable(GL_TEXTURE_2D);
			}break;
			case 2: // sphere
			{
				crt_rs = crt_vs = 90;
				glBindTexture(GL_TEXTURE_2D, tex_names[PLANETIMG_TEX]);
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
				draw_shape(cur);
				glDisable(GL_TEXTURE_2D);
			}break;
			case 3: // cone
			{
				crt_rs = crt_vs = 90;
				glBindTexture(GL_TEXTURE_2D, tex_names[SMALLIMG_TEX]);
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
				draw_shape(cur);
				glDisable(GL_TEXTURE_2D);
			}break;
			case 4: // torus
			{
				crt_rs = crt_vs = 90;
				glBindTexture(GL_TEXTURE_2D, tex_names[TANIMG_TEX]);
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
				draw_shape(cur);
				glDisable(GL_TEXTURE_2D);
			}break;
		}
		
	}
}

