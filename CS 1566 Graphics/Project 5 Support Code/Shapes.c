/***************************************************
 FILE: Shapes.c
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/
 
 /* Mapping Textures is an easy task. Each texture
 *  is mapped from 0 to 1, and then attacked to a
 *  shape. */
 
 #include "Transformations.h"
 
/************************************************************
					Make Sphere
************************************************************/

void make_sphere(OBJECT *vert, double ray){

	int i,j,k; // initial variables to use outside of loops
		
		for(i = 0; i <= crt_vs; i++) // iterates through the angles
		{
			
			for(j = 0; j <= crt_rs; j++) // iterates through the layers
			{
				
				int t = (360/crt_vs * j); // theta
				int p = (180/crt_rs * i) - 90; // phi
				
				GLfloat theta = (t * M_PI/180); // theta angle
				GLfloat phi = (p * M_PI/180);  // phi angle
				
				for(k = 0; k < 4; k++) // iterates through x,y,z coordinates
				{
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
				
				shape_normals(vert->shape_verts[i][j], (GLfloat)ray, (GLfloat)ray, vert->shape_normals[i][j], 1,0,0); // compute the normals 
				vert->shape_tex[i][j][0] = (float)j/crt_rs;
				vert->shape_tex[i][j][1] = (float)i/crt_vs;
			}
		}

	return;
}

/************************************************************
					Make Cone
************************************************************/

void make_cone(OBJECT *vert, double height, double ray)
{
	int i,j,k; // initial variables to use outside of loops
	
	for(i = 0; i <= crt_vs; i++) // iterates through the angles
	{
		
		for(j = 0; j <= crt_rs; j++) // iterates through the layers
		{
	
			int t = 360/crt_rs * j; // next angle
			
			GLfloat theta = (t * M_PI/180); // angle
			
			for(k = 0; k < 4; k++) // iterates through x,y,z coordinates
			{
				switch(k){
					case 0:
						vert->shape_verts[i][j][k] = (height - (height/crt_vs * i))/height * ray * cos(theta);break;   // x coordinate
					case 1:
						vert->shape_verts[i][j][k] = (height/crt_vs * i) - height/2;break;  // y coordinate
					case 2:
						vert->shape_verts[i][j][k] = (height - (height/crt_vs * i))/height * ray * sin(theta); break; // z coordinate
					case 3:
						vert->shape_verts[i][j][k] = 1; // homogenious coordinate
				}
			}
		
			// map texture		
		
			vert->shape_tex[i][j][0] = (float)j/crt_rs;
			vert->shape_tex[i][j][1] = (float)i/crt_vs;
		
		}	
	}	

	// fix wrap around

	for(i = 0; i < crt_rs; i++){
		vert->shape_verts[i][crt_vs+1][0] = vert->shape_verts[i][0][0];
		vert->shape_verts[i][crt_vs+1][1] = vert->shape_verts[i][0][1];
		vert->shape_verts[i][crt_vs+1][2] = vert->shape_verts[i][0][2];
	}	
	
	for(i = 0; i < crt_vs; i++){
		vert->shape_verts[crt_rs + 1][i][0] = vert->shape_verts[0][i][0];
		vert->shape_verts[crt_rs + 1][i][1] = vert->shape_verts[0][i][1];
		vert->shape_verts[crt_rs + 1][i][2] = vert->shape_verts[0][i][2];
	}

	findNormals(vert);	// find normals
}


/************************************************************
					Make Torus
************************************************************/
void make_torus(OBJECT *vert, double R, double r)
{
	int i,j,k; // initial variables to use outside of loops
	
	for(i = 0; i <= crt_rs; i++) // iterates through the Fmys
	{
		GLfloat theta = (2 * M_PI * i)/crt_rs; // angle
		
		for(j = 0; j <= crt_vs; j++) // iterates through the layers
		{
			
			GLfloat phi = (2 * M_PI * j)/crt_vs; // angle
			
			for(k = 0; k < 4; k++) // iterates through x,y,z coordinates
			{
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
		
			// map texture
		
			vert->shape_tex[i][j][0] = (float)j/crt_rs;
			vert->shape_tex[i][j][1] = (float)i/crt_vs;
		
		}	
	}		

	findNormals(vert); // find normals
}
/************************************************************
					Make Cube
************************************************************/

void make_cube_smart(OBJECT *po, double size){
	
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
	
	cube_normals(po); // find the normals

	// map texture

	po->cube_tex[0][0] = 0; po->cube_tex[0][1] =  0;
	po->cube_tex[1][0] = 1; po->cube_tex[1][1] =  0;
	po->cube_tex[2][0] = 1; po->cube_tex[2][1] =  1;
	po->cube_tex[3][0] = 0; po->cube_tex[3][1] =  1;
	
}

/************************************************************
					Make House
************************************************************/

void make_house(OBJECT *vert)
{	
	vert->shape_verts[1][0][0] = -1;
	vert->shape_verts[1][0][1] = 1;
	vert->shape_verts[1][0][2] = 1;
	vert->shape_verts[1][0][3] = 1;
	vert->shape_verts[1][1][0] = 1;
	vert->shape_verts[1][1][1] = 1;
	vert->shape_verts[1][1][2] = 1;
	vert->shape_verts[1][1][3] = 1;
	vert->shape_verts[1][2][0] = 1;
	vert->shape_verts[1][2][1] = 1;
	vert->shape_verts[1][2][2] = -1;
	vert->shape_verts[1][2][3] = 1;
	vert->shape_verts[1][3][0] = -1;
	vert->shape_verts[1][3][1] = 1;
	vert->shape_verts[1][3][2] = -1;
	vert->shape_verts[1][3][3] = 1;
	
	vert->shape_verts[2][0][0] = -1;
	vert->shape_verts[2][0][1] = -1;
	vert->shape_verts[2][0][2] = 1;
	vert->shape_verts[2][0][3] = 1;
	vert->shape_verts[2][1][0] = 1;
	vert->shape_verts[2][1][1] = -1;
	vert->shape_verts[2][1][2] = 1;
	vert->shape_verts[2][1][3] = 1;
	vert->shape_verts[2][2][0] = 1;
	vert->shape_verts[2][2][1] = -1;
	vert->shape_verts[2][2][2] = -1;
	vert->shape_verts[2][2][3] = 1;
	vert->shape_verts[2][3][0] = -1;
	vert->shape_verts[2][3][1] = -1;
	vert->shape_verts[2][3][2] = -1;
	vert->shape_verts[2][3][3] = 1;
	
	vert->shape_verts[0][0][0] = 0;
	vert->shape_verts[0][0][1] = 2;
	vert->shape_verts[0][0][2] = 0;
	vert->shape_verts[0][0][3] = 1;
	vert->shape_verts[0][1][0] = 0;
	vert->shape_verts[0][1][1] =  2;
	vert->shape_verts[0][1][2] = 0;
	vert->shape_verts[0][1][3] = 1;
	vert->shape_verts[0][2][0] = 0;
	vert->shape_verts[0][2][1] =  2;
	vert->shape_verts[0][2][2] = 0;
	vert->shape_verts[0][2][3] = 1;
	vert->shape_verts[0][3][0] = 0;
	vert->shape_verts[0][3][1] =  2;
	vert->shape_verts[0][3][2] = 0;
	vert->shape_verts[0][3][3] = 1;
	
	vert->shape_verts[3][0][0] = 1;
	vert->shape_verts[3][0][1] = 1;
	vert->shape_verts[3][0][2] = -1;
	vert->shape_verts[3][0][3] = 1;
	vert->shape_verts[3][1][0] = 1;
	vert->shape_verts[3][1][1] = 1;
	vert->shape_verts[3][1][2] = -1;
	vert->shape_verts[3][1][3] = 1;
	vert->shape_verts[3][2][0] = 0;
	vert->shape_verts[3][2][1] =  2;
	vert->shape_verts[3][2][2] = 0;
	vert->shape_verts[3][2][3] = 1;
	vert->shape_verts[3][3][0] = 1;
	vert->shape_verts[3][3][1] = 1;
	vert->shape_verts[3][3][2] = -1;
	vert->shape_verts[3][3][3] = 1;
	
	cube_normals(vert); // find normals

	//map texture

	vert->cube_tex[0][0] = 0; vert->cube_tex[0][1] =  0;
	vert->cube_tex[1][0] = 1; vert->cube_tex[1][1] =  0;
	vert->cube_tex[2][0] = 1; vert->cube_tex[2][1] =  1;
	vert->cube_tex[3][0] = 0; vert->cube_tex[3][1] =  1;
}
/************************************************************
					Shape Normals
************************************************************/

void shape_normals(GLfloat point[4], GLfloat R, GLfloat r, GLfloat normal[4], int sphere, int cone, int torus)
{	
	if(sphere == 1){  // gradient of a sphere

		normal[0] = point[0] / R;
		normal[1] = point[1] / R;
		normal[2] = point[2] / R;
	}	
}
void findNormals(OBJECT *vert)
{		
	GLfloat v1[4][3];
	
	int i, j;
	
	for(i = 0; i <= crt_vs; i++)
		for(j = 0; j <= crt_rs; j++)
		{
			
			cross(vert->shape_verts[i][j], vert->shape_verts[i][(j+1)%crt_rs], vert->shape_verts[(i-1)%crt_vs][j], v1[0]);
			cross(vert->shape_verts[i][j], vert->shape_verts[(i-1)%crt_vs][j], vert->shape_verts[i][(j-1)%crt_rs], v1[1]);
			cross(vert->shape_verts[i][j], vert->shape_verts[i][(j-1)%crt_rs], vert->shape_verts[(i+1)%crt_vs][j], v1[2]);
			cross(vert->shape_verts[i][j], vert->shape_verts[(i+1)%crt_vs][j], vert->shape_verts[i][(j+1)%crt_rs], v1[3]);
			
			vert->shape_normals[i][j][0] = ((v1[0][0]+v1[1][0]+v1[2][0]+v1[3][0])/4);
			vert->shape_normals[i][j][1] = ((v1[0][1]+v1[1][1]+v1[2][1]+v1[3][1])/4);
			vert->shape_normals[i][j][2] = ((v1[0][2]+v1[1][2]+v1[2][2]+v1[3][2])/4);
			
		}
}

void cube_normals(OBJECT *po) // finds the cube normals
{
	
	// this code is a little messy, but I could not get the cross product to work
	
	GLfloat vect[4];
	
	vect[0] = -1;
	vect[1] = 1;
	vect[2] = 1;
	
	normalize(vect); // normalize
	
	po->shape_normals[0][0][0] = vect[0]; // x 
	po->shape_normals[0][0][1] = vect[1]; // y
	po->shape_normals[0][0][2] = vect[2]; // z
	
	vect[0] = -1;
	vect[1] = -1;
	vect[2] = 1;
	
	normalize(vect); // normalize
	
	po->shape_normals[1][0][0] = vect[0]; // x 
	po->shape_normals[1][0][1] = vect[1]; // y
	po->shape_normals[1][0][2] = vect[2]; // z
	
	vect[0] = 1;
	vect[1] = -1;
	vect[2] = 1;
	
	normalize(vect); // normalize
	
	po->shape_normals[1][1][0] = vect[0]; // x 
	po->shape_normals[1][1][1] = vect[1]; // y
	po->shape_normals[1][1][2] = vect[2]; // z
	
	vect[0] = 1;
	vect[1] = 1;
	vect[2] = 1;
	
	normalize(vect); // normalize
	
	po->shape_normals[0][1][0] = vect[0]; // x 
	po->shape_normals[0][1][1] = vect[1]; // y
	po->shape_normals[0][1][2] = vect[2]; // z
	
	vect[0] = 1;
	vect[1] = 1;
	vect[2] = -1;
	
	normalize(vect); // normalize
	
	po->shape_normals[0][2][0] = vect[0]; // x 
	po->shape_normals[0][2][1] = vect[1]; // y
	po->shape_normals[0][2][2] = vect[2]; // z
	
	vect[0] = -1;
	vect[1] = 1;
	vect[2] = -1;
	
	normalize(vect); // normalize
	
	po->shape_normals[0][3][0] = vect[0]; // x 
	po->shape_normals[0][3][1] = vect[1]; // y
	po->shape_normals[0][3][2] = vect[2]; // z
	
	vect[0] = -1;
	vect[1] = -1;
	vect[2] = -1;
	
	normalize(vect); // normalize
	
	po->shape_normals[1][3][0] = vect[0]; // x 
	po->shape_normals[1][3][1] = vect[1]; // y
	po->shape_normals[1][3][2] = vect[2]; // z
	
	vect[0] = 1;
	vect[1] = -1;
	vect[2] = -1;
	
	normalize(vect); // normalize
	
	po->shape_normals[1][2][0] = vect[0]; // x 
	po->shape_normals[1][2][1] = vect[1]; // y
	po->shape_normals[1][2][2] = vect[2]; // z
}
