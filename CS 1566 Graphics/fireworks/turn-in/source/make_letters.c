
void make_heart(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	
	SHAPE cur;
	int solid = 1;
	
	double trans_z=0;
	double y_fac =1.3;
	double ray =.007;
	
	GLfloat color[3];
	if(color_type){
		color[0]=1;
  		color[1]=1;
  		color[2]=1;
  		scale_y+=.003;
  	}
  	else{
  		color[0]=1;
  		color[1]=0;
  		color[2]=0;
  		scale_y-=.003;
  	}
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .107*scale_x,0.01*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .092*scale_x,-0.014*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .12*scale_x,.03*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .13*scale_x,.06*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .12*scale_x,.09*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .09*scale_x,.12*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .05*scale_x,.12*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,.1*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0,.07*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.107*scale_x,0.01*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.092*scale_x,-0.014*y_fac*scale_y, trans_z);

	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.12*scale_x,.03*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.13*scale_x,.06*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.12*scale_x,.09*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.09*scale_x,.12*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.05*scale_x,.12*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.02*scale_x,.1*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.08*scale_x,-.03*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.065*scale_x,-.045*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.05*scale_x,-.06*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.035*scale_x,-.075*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.02*scale_x,-.0925*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);	
	make_particle(&(po->particles[i++]), color, solid, cur, .08*scale_x,-.03*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .065*scale_x,-.045*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .05*scale_x,-.06*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .035*scale_x,-.075*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,-.0925*y_fac*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0,-.11*y_fac*scale_y, trans_z);

}


void make_b(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	
	SHAPE cur;
	int solid = 1;
	
	double trans_z=0;
	double ray =.007;
	
	
	double start_x=-.6;
	double start_y=.5;
	GLfloat color[3];
	
	color[0]=1;
  	color[1]=1;
  	color[2]=1;
  	
  	po->start_x = start_x;
  	po->start_y = start_y;


	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,0, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.01*scale_x,0, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .035*scale_x,0.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.035*scale_x,-.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .06*scale_x,.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .06*scale_x,-.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.055*scale_x,.09*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.055*scale_x,-.09*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .03*scale_x,.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .03*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0,0.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0,-0.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,0, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,.033*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,-.033*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,.066*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,-.066*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,-.1*scale_y, trans_z);
	
	

}



void make_y(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){

	SHAPE cur;
	int solid = 1;
	
	double trans_z=0;
	double ray =.007;
	double start_x;
	double start_y;
	
	
	
	
	GLfloat color[3];
	if(color_type){
		color[0]=.7;
  		color[1]=.7;
  		color[2]=.7;
  		start_x=-.4;
  		start_y=.4;
  	}
  	else{
  		color[0]=.1;
  		color[1]=.3;
  		color[2]=.6;
  		start_x=.8;
  		start_y=-.25;
  	
  	}
  	
  	po->start_x = start_x;
  	po->start_y = start_y;
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -0.021*scale_x,-.055*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -0.025*scale_x,-.075*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.012*scale_x,-.089*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .006*scale_x,-.093*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .024*scale_x,-0.09*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .032*scale_x,-0.075*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .034*scale_x,-.055*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .035*scale_x,-.035*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .032*scale_x,-.013*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .03*scale_x,.005*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .029*scale_x,.029*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .032*scale_x,.059*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .035*scale_x,.068*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .022*scale_x,.019*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .013*scale_x,.005*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.018*scale_x,.009*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.025*scale_x,.023*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.030*scale_x,.041*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.037*scale_x,.057*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.045*scale_x,.065*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .032*scale_x,.044*scale_y, trans_z);
	

}


void make_z(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){

	SHAPE cur;
	int solid = 1;

	double trans_z=0;
	double ray =.007;
	
	
	double start_x=0;
	double start_y=.45;
	
	GLfloat color[3];
	color[0]=.9;
  	color[1]=.3;
  	color[2]=.1;
  	
  	po->start_x = start_x;
  	po->start_y = start_y;


	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0,0, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .041*scale_x,.037*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .058*scale_x,0.053*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .069*scale_x,0.069*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur,0.077*scale_x,.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.07*scale_x,.099*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.055*scale_x,.11*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .023*scale_x,.112*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .005*scale_x,.114*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.021*scale_x,.112*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.058*scale_x,0.108*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.08*scale_x,.106*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.103*scale_x,.104*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.11*scale_x,.083*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .025*scale_x,.007*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.045*scale_x,.009*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.067*scale_x,.01*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0.085*scale_x,-.001*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.013*scale_x,-.003*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.029*scale_x,-.007*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.051*scale_x,-.01*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.022*scale_x,-.018*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.049*scale_x,-.038*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.069*scale_x,-.047*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.09*scale_x,-.065*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.11*scale_x,-.079*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.12*scale_x,-.099*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.107*scale_x,-.116*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.08*scale_x,-.118*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.057*scale_x,-.119*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.021*scale_x,-.12*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .009*scale_x,-.121*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .037*scale_x,-.120*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .06*scale_x,-.118*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .093*scale_x,-.118*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .120*scale_x,-.115*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .15*scale_x,-.111*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .172*scale_x,-.103*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .186*scale_x,-.094*scale_y, trans_z);
	



}

void make_a(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	SHAPE cur;
	int solid = 1;
	double trans_z=0;
	double ray =.007;
	double start_x;
	double start_y;
	
	
	
	GLfloat color[3];
	if(color_type==1){
		color[0]=.9;
  		color[1]=.3;
  		color[2]=.1;
  		start_x=.2;
  		start_y=.45;
  	}
  	else if(color_type ==2){
  		color[0]=.7;
  		color[1]=.7;
  		color[2]=.7;
  		start_x=-.55;
		start_y=.05;
  	
  	}
  	else if(color_type ==3){
  		color[0]=.1;
  		color[1]=.3;
  		color[2]=.6;
  		start_x=.18;
		start_y=-.18;
  	
  	}
  	
  	po->start_x = start_x;
  	po->start_y = start_y;
  	
  	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .045*scale_x,0, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .043*scale_x,.014*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .041*scale_x,.031*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .039*scale_x,.047*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,.043*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .002*scale_x,.035*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.015*scale_x,.022*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.029*scale_x,.013*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.039*scale_x,-.006*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.036*scale_x,-.029*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.021*scale_x,-.045*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.001*scale_x,-.048*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,-.041*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .038*scale_x,-.03*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .052*scale_x,-.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .062*scale_x,-.041*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .078*scale_x,-.051*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .099*scale_x,-.056*scale_y, trans_z);
  	


}

void make_c(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	SHAPE cur;
	int solid = 1;
	double trans_z=0;
	double ray =.007;
	
	
	double start_x=.4;
	double start_y=.45;
	
	GLfloat color[3];
	color[0]=.9;
  	color[1]=.3;
  	color[2]=.1;
  	
  	po->start_x = start_x;
  	po->start_y = start_y;
  	
  	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .054*scale_x,.038*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .059*scale_x,.063*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .041*scale_x,.072*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.005*scale_x,.065*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.038*scale_x,.045*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.052*scale_x,.010*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.049*scale_x,-.024*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.020*scale_x,-.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .001*scale_x,-.044*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .04*scale_x,-.035*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .07*scale_x,-.015*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .081*scale_x,-.005*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .115*scale_x,.022*scale_y, trans_z);
	
	


}

void make_h(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	SHAPE cur;
	int solid = 1;
	double trans_z=0;
	double ray =.007;
	
	
	double start_x=.6;
	double start_y=.45;
	
	GLfloat color[3];
	color[0]=.9;
  	color[1]=.3;
  	color[2]=.1;
  	
  	po->start_x = start_x;
  	po->start_y = start_y;
  	
  	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.014*scale_x,.099*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.022*scale_x,.077*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,.057*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.04*scale_x,.03*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.038*scale_x,0, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.035*scale_x,-.026*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.022*scale_x,-.039*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.005*scale_x,-.022*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .01*scale_x,-.01*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .022*scale_x,.01*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .030*scale_x,.029*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .032*scale_x,-.01*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .042*scale_x,-.022*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .063*scale_x,-.035*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .081*scale_x,-.038*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .1*scale_x,-.04*scale_y, trans_z);


}

void make_n(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	SHAPE cur;
	int solid = 1;
	double trans_z=0;
	double ray =.007;
	double start_x;
	double start_y;
	
	GLfloat color[3];
	if(color_type){
		color[0]=.7;
  		color[1]=.7;
  		color[2]=.7;
  		start_x=-.3;
  		start_y=.05;
  	}
  	else{
  		color[0]=.1;
  		color[1]=.3;
  		color[2]=.6;
  		start_x=.42;
  		start_y=-.18;
  	
  	}
  	
  	po->start_x = start_x;
  	po->start_y = start_y;
  	
  	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .07*scale_x,-.075*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .056*scale_x,-.079*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .052*scale_x,-.059*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .049*scale_x,-.036*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .045*scale_x,-.018*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .044*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .042*scale_x,.026*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .041*scale_x,.044*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .028*scale_x,.063*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .014*scale_x,.071*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,.076*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.018*scale_x,.075*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.032*scale_x,.068*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.046*scale_x,.058*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.05*scale_x,.038*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.06*scale_x,.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.06*scale_x,-.008*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.063*scale_x,-.03*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.066*scale_x,-.046*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.075*scale_x,-.065*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.081*scale_x,-.081*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.067*scale_x,.039*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.074*scale_x,.058*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.078*scale_x,.078*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.092*scale_x,.081*scale_y, trans_z);

}

void make_d(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	SHAPE cur;
	int solid = 1;
	double trans_z=0;
	double ray =.007;

	
	double start_x=.15;
	double start_y=.45;
	
	GLfloat color[3];
	if(color_type){
		color[0]=.7;
  		color[1]=.7;
  		color[2]=.7;
  		start_x=-.1;
		start_y=.05;
  	}
  	else{
  		color[0]=.1;
  		color[1]=.3;
  		color[2]=.6;
  		
  		start_x=.6;
		start_y=-.18;
  	
  	}
  	
  	po->start_x = start_x;
  	po->start_y = start_y;
  	
  	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .083*scale_x,-.057*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .065*scale_x,-.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .056*scale_x,-.048*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .046*scale_x,-.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .043*scale_x,.005*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .041*scale_x,.035*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .043*scale_x,.058*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .048*scale_x,.084*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .051*scale_x,.103*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .06*scale_x,.124*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .038*scale_x,.031*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .019*scale_x,.039*scale_y, trans_z);
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.007*scale_x,.036*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,.024*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.043*scale_x,.008*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.052*scale_x,-.009*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.042*scale_x,-.045*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.021*scale_x,-.059*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,-.064*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .022*scale_x,-.056*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .04*scale_x,-.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.052*scale_x,-.031*scale_y, trans_z);
}

void make_tri(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	SHAPE cur;
	int solid = 1;
	double trans_z=0;
	double ray =.007;
	
	GLfloat color[3];
	color[0]=.8;
	color[1]=.8;
	color[2]=.5;
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .0*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.02*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .04*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.04*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .06*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.06*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .012*scale_x,.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.012*scale_x,.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .024*scale_x,.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.024*scale_x,.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .036*scale_x,.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.036*scale_x,.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .048*scale_x,.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.048*scale_x,.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .012*scale_x,-.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.012*scale_x,-.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .024*scale_x,-.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.024*scale_x,-.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .036*scale_x,-.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.036*scale_x,-.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .048*scale_x,-.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.048*scale_x,-.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.12*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .12*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.108*scale_x,-.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.096*scale_x,-.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.084*scale_x,-.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.072*scale_x,-.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .108*scale_x,-.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .096*scale_x,-.06*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .084*scale_x,-.04*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .072*scale_x,-.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.1*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.08*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.06*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.04*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.02*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .1*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .08*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .06*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .04*scale_x,-.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .02*scale_x,-.1*scale_y, trans_z);
	
	

}
void make_shroom(EXPLOSION *po,double scale_x,double scale_y,int color_type,int i){
	SHAPE cur;
	int solid = 1;
	double trans_z=0;
	double ray =.007;
	
	GLfloat color[3];
	
	if(color_type){
		color[0]=0;
		color[1]=.8;
		color[2]=0;
	}
	else{
		color[0]=.8;
		color[1]=0;
		color[2]=0;
	
	}
	
	
	//
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,.22*scale_y, trans_z);
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .019*scale_x,.218*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .04*scale_x,.215*scale_y, trans_z);
	//6
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .063*scale_x,.212*scale_y, trans_z);//*****
	//5
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .082*scale_x,.201*scale_y, trans_z);//****
	//4
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .1*scale_x,.19*scale_y, trans_z);//***
	//3
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .117*scale_x,.18*scale_y, trans_z);//**
	//2
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .133*scale_x,.162*scale_y, trans_z);//*
	//1
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .145*scale_x,.15*scale_y, trans_z);
	//1
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .158*scale_x,.128*scale_y, trans_z);//*
	//2
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .17*scale_x,.112*scale_y, trans_z);//**
	//3
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .18*scale_x,.096*scale_y, trans_z);//***
	//4
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .189*scale_x,.08*scale_y, trans_z);//****
	//5
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .198*scale_x,.055*scale_y, trans_z);//*****
	//6
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .204*scale_x,.039*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .206*scale_x,.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .208*scale_x,0*scale_y, trans_z);
	
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.019*scale_x,.218*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.04*scale_x,.215*scale_y, trans_z);
	//6
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.063*scale_x,.212*scale_y, trans_z);//*****
	//5
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.082*scale_x,.201*scale_y, trans_z);//****
	//4
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.1*scale_x,.19*scale_y, trans_z);//***
	//3
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.117*scale_x,.18*scale_y, trans_z);//**
	//2
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.133*scale_x,.162*scale_y, trans_z);//*
	//1
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.145*scale_x,.15*scale_y, trans_z);
	//1
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.158*scale_x,.128*scale_y, trans_z);//*
	//2
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.17*scale_x,.112*scale_y, trans_z);//**
	//3
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.18*scale_x,.096*scale_y, trans_z);//***
	//4
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.189*scale_x,.08*scale_y, trans_z);//****
	//5
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.198*scale_x,.055*scale_y, trans_z);//*****
	//6
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.204*scale_x,.039*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.206*scale_x,.02*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.208*scale_x,0*scale_y, trans_z);
	
	//
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .209*scale_x,-.019*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .207*scale_x,-.036*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .204*scale_x,-.045*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .199*scale_x,-.061*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .190*scale_x,-.08*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .179*scale_x,-.097*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .159*scale_x,-.116*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .139*scale_x,-.12*scale_y, trans_z);//**
	
	
	//
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.209*scale_x,-.019*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.207*scale_x,-.036*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.204*scale_x,-.045*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.199*scale_x,-.061*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.190*scale_x,-.08*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.179*scale_x,-.097*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.159*scale_x,-.116*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.139*scale_x,-.12*scale_y, trans_z);//**
	
	color[0]=.8;
	color[1]=.7;
	color[2]=.5;
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,-.056*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .018*scale_x,-.056*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .032*scale_x,-.057*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .050*scale_x,-.059*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .065*scale_x,-.062*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .083*scale_x,-.073*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .1*scale_x,-.083*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .118*scale_x,-.102*scale_y, trans_z);//**
	
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .12*scale_x,-.12*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .118*scale_x,-.141*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .105*scale_x,-.162*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .096*scale_x,-.179*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .083*scale_x,-.189*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .07*scale_x,-.194*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .052*scale_x,-.196*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .035*scale_x,-.198*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .017*scale_x,-.199*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,-.2*scale_y, trans_z);//**
	
	//
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.018*scale_x,-.056*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.032*scale_x,-.057*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.050*scale_x,-.059*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.065*scale_x,-.062*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.083*scale_x,-.073*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.1*scale_x,-.083*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.118*scale_x,-.102*scale_y, trans_z);//**
	
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.12*scale_x,-.12*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.118*scale_x,-.141*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.105*scale_x,-.162*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.096*scale_x,-.179*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.083*scale_x,-.189*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.07*scale_x,-.194*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.052*scale_x,-.196*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.035*scale_x,-.198*scale_y, trans_z);//**
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.017*scale_x,-.199*scale_y, trans_z);//**
	

	
	
	
	
	
	
	
	
	color[0]=.7;
	color[1]=.7;
	color[2]=.7;
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .158*scale_x,.108*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .148*scale_x,.082*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .142*scale_x,.063*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .14*scale_x,.045*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .143*scale_x,.03*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .147*scale_x,.009*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .158*scale_x,-.008*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .168*scale_x,-.023*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .179*scale_x,-.03*scale_y, trans_z);
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .193*scale_x,-.04*scale_y, trans_z);
	//
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.158*scale_x,.108*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.148*scale_x,.082*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.142*scale_x,.063*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.14*scale_x,.045*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.143*scale_x,.03*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.147*scale_x,.009*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.158*scale_x,-.008*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.168*scale_x,-.023*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.179*scale_x,-.03*scale_y, trans_z);
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.193*scale_x,-.04*scale_y, trans_z);
	
	//&
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,0*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .03*scale_x,.008*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .057*scale_x,.019*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .072*scale_x,.039*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .09*scale_x,.059*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .1*scale_x,.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .103*scale_x,.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .1*scale_x,.12*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .09*scale_x,.141*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .072*scale_x,.161*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .057*scale_x,.181*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .03*scale_x,.192*scale_y, trans_z);
	//
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, .0*scale_x,.2*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,.008*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.057*scale_x,.019*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.072*scale_x,.039*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.09*scale_x,.059*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.1*scale_x,.08*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.103*scale_x,.1*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.1*scale_x,.12*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.09*scale_x,.141*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.072*scale_x,.161*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.057*scale_x,.181*scale_y, trans_z);
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, -.03*scale_x,.192*scale_y, trans_z);
	
	
	make_cube_smart(&cur,ray);
	real_translation(&cur,po->start_x,po->start_y,0);
	make_particle(&(po->particles[i++]), color, solid, cur, 0*scale_x,.2*scale_y, trans_z);

	
	
	
	
}