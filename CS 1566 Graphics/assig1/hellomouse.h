#ifndef _HELLOMOUSE_H
#define _HELLOMOUSE_H

void glut_setup(void) ;
void gl_setup(void) ;
void my_setup(void);
void my_display(void) ;
void my_reshape(int w, int h) ;
void my_idle(void) ;
void my_mouse(int b, int s, int x, int y) ;
void my_keyboard(unsigned char c, int x, int y) ;
void my_TimeOut(int id) ;

#endif
