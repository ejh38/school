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
void my_motion(int a, int b);
void explode(void);

double random_number(double a, double b);

#endif
