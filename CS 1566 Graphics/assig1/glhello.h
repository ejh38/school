/**********
notes:
VS users: include opengl/glut.h below instead of GL/glut.h
OSX users: include glut/glut.h below instead of GL/glut.h
**********/
#include <glut/glut.h>
#include <stdio.h>

void glut_setup(void) ;
void gl_setup(void) ;
void my_setup(void);
void my_display(void) ;
void my_reshape(int w, int h) ;
void my_idle(void) ;
