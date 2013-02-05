/***************************************************
 FILE: Images.c
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/

#include "Images.h"

void makeStripeImage(void) {
    int j;
	
    for (j = 0; j < stripeImageWidth; j++) {
        stripeImage[4*j] = (j<=4) ? 255 : 0;
        stripeImage[4*j+1] = (j>4) ? 255 : 0;
        stripeImage[4*j+2] = 0;
        stripeImage[4*j+3] = 255;
    }
}

void makeCheckImage(void) 
{
	int i,j, c;
	for (i=0; i<checkImageHeight; i++) 
		for (j=0; j<checkImageWidth; j++) {
			c = (((i&0x8)==0)^((j&0x8)==0))*255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
}

/* rbg --> rgb? */
void bmp2rgb(GLubyte img[], int size) {
	int i;
	GLubyte temp;
	
	for (i=0; i<size; i+=3) {
		temp = img[i+2];
		img[i+2] = img[i+1];
		img[i+1] = temp;
		
	}
}

void load_bmp(char *fname, GLubyte img[], int size, GLuint *ptname) {
	FILE *fp;
	
	fp = fopen(fname,"rb") ;
	if(fp == NULL) {
		fprintf(stderr,"unable to open texture file %s\n", fname) ;
		exit(1) ;
	}
	
	fseek(fp,8,SEEK_SET) ;
	fread(img,size*size*3,1,fp) ;
	bmp2rgb(img, size*size*3);
	fclose(fp) ;
	
	if (ptname) {
		// initialize the texture
		glGenTextures(1, ptname) ; 
		glBindTexture(GL_TEXTURE_2D,*ptname);
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT) ;
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT) ; 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR) ;
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR) ;
		
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,
					 size,size,
					 0,GL_RGB,GL_UNSIGNED_BYTE,img) ;
	}
}

void texture_setup() {
	// set pixel storage mode; see Red Book for details why.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// generate all the textures we might use
	
	// make stripe image
	makeStripeImage();
	glGenTextures(1, &tex_names[STRIPE_TEX]);
	glBindTexture(GL_TEXTURE_2D, tex_names[STRIPE_TEX]);
	
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 
				 stripeImageWidth, 
				 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
	
	// make check texture image
	makeCheckImage();
	
	// bind check texture
	glGenTextures(1, &tex_names[CHECK_TEX]);
	glBindTexture(GL_TEXTURE_2D, tex_names[CHECK_TEX]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
				 checkImageWidth, checkImageHeight, 
				 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	

	load_bmp("images/earth.bmp", planet_img, mediumWidth, &tex_names[PLANETIMG_TEX]); 
	load_bmp("images/bricks_256_256.bmp",  brick_img, smallWidth, &tex_names[BRICKIMG_TEX]); 
	load_bmp("images/window.bmp",    window_img,  smallWidth, &tex_names[WINDOWIMG_TEX]); 
	load_bmp("images/shingle.bmp",    shingle_img,  smallWidth, &tex_names[SHINGLEIMG_TEX]); 
	load_bmp("images/sea.bmp",    small_img,  smallWidth, &tex_names[SMALLIMG_TEX]) ; 
	load_bmp("images/tangerine.bmp",    small_img,  smallWidth, &tex_names[TANIMG_TEX]) ;



}