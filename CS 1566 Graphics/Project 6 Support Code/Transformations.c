/***************************************************
 FILE: Transformations.c
 AUTHOR: tbl - based on Texture Town, Spring 2010
 DATE: 11/04/10
 ***************************************************/

#include "Transformations.h"
#include "Shapes.h"

/**************************************************
				Transformations
**************************************************/

void my_trans(GLfloat x, GLfloat y, GLfloat z) { // translates the camera
	
	my_cam.pos[0] = my_cam.pos[0] + x;
	my_cam.pos[1] = my_cam.pos[1] + y;
	my_cam.pos[2] = my_cam.pos[2] + z;
	
	my_cam.at[0] += x;
	my_cam.at[1] += y;
	my_cam.at[2] += z;

}

void real_translation(OBJECT *po, GLfloat x, GLfloat y, GLfloat z) { // translates the shapes
	
	int i, j;
	
	for(i = 0; i <= crt_vs; i++)
	{
		for(j = 0; j <= crt_rs; j++)
		{
			po->shape_verts[i][j][0] += x; // translate across x
			po->shape_verts[i][j][1] += y; // translates across y
			po->shape_verts[i][j][2] += z; // translates across z
			
		}
	}
	
}

void real_scaling(OBJECT *po, GLfloat sx, GLfloat sy, GLfloat sz) { // scales the object
	
	int i, j;
	
	for(i = 0; i <= crt_vs; i++)
	{
		for(j = 0; j <= crt_rs; j++)
		{
			po->shape_verts[i][j][0] = po->shape_verts[i][j][0] * sx; // scales x
			po->shape_verts[i][j][1] = po->shape_verts[i][j][1] * sy; // scales y
			po->shape_verts[i][j][2] = po->shape_verts[i][j][2] * sz; // scales z
			po->shape_normals[i][j][0] = po->shape_normals[i][j][0] * sx; // scales x
			po->shape_normals[i][j][1] = po->shape_normals[i][j][1] * sy; // scales y
			po->shape_normals[i][j][2] = po->shape_normals[i][j][2] * sz; // scales z
			
		}
	}
	
}

void real_rotation(OBJECT *po, GLfloat deg, GLfloat x, GLfloat y, GLfloat z) { // rotates the shapes
	
	GLfloat theta = (deg * M_PI/180); // deg to rotate by
	int i, j;
	
	for(i = 0; i <= crt_vs; i++)
	{
		for(j = 0; j <= crt_rs; j++)
		{
			GLfloat X = po->shape_verts[i][j][0];
			GLfloat Y = po->shape_verts[i][j][1];
			GLfloat Z = po->shape_verts[i][j][2];
			
			GLfloat nX = po->shape_normals[i][j][0];
			GLfloat nY = po->shape_normals[i][j][1];
			GLfloat nZ = po->shape_normals[i][j][2];
			
			if(x == 1) // rotate X
			{
	
				po->shape_verts[i][j][1] = Y * cos(theta) - Z * sin(theta);	
				po->shape_verts[i][j][2] = Z * cos(theta) + Y * sin(theta);
				
				po->shape_normals[i][j][1] = nY * cos(theta) - nZ * sin(theta);	
				po->shape_normals[i][j][2] = nZ * cos(theta) + nY * sin(theta);
			}
			else if(y ==1) // rotate Y
			{
								   
				po->shape_verts[i][j][0] = X * cos(theta) + Z * sin(theta);
				po->shape_verts[i][j][2] = Z * cos(theta) - X * sin(theta);
				
				po->shape_normals[i][j][0] = nX * cos(theta) + nZ * sin(theta);
				po->shape_normals[i][j][2] = nZ * cos(theta) - nX * sin(theta);
		
			}
	        else if (z ==1){ // rotate Z
				
				po->shape_verts[i][j][0] = X * cos(theta) - Y * sin(theta);	
				po->shape_verts[i][j][1] = X * sin(theta) + Y * cos(theta);
				
				po->shape_normals[i][j][0] = nX * cos(theta) - nY * sin(theta);	
				po->shape_normals[i][j][1] = nX * sin(theta) + nY * cos(theta);
	
	        }
		}
	}
}

void flashlightRotation(GLfloat deg, GLfloat x, GLfloat y, GLfloat z) // rotates the flashlight in place
{
	GLfloat theta = (deg * M_PI/180);
	
	GLfloat aX = my_cam.at[0]; // x position
	GLfloat aY = my_cam.at[1]; // y position
	GLfloat aZ = my_cam.at[2]; // z position
	
	if(x == 1) // rotate X
	{
		
		my_cam.at[1] = aY * cos(theta) - aZ * sin(theta);	
		my_cam.at[2] = aZ * cos(theta) + aY * sin(theta);
		
	}
	else if(y ==1) // rotate Y
	{
		
		my_cam.at[0] = aX * cos(theta) + aZ * sin(theta);
		my_cam.at[2] = aZ * cos(theta) - aX * sin(theta);
		
	}
	else if (z ==1){ // rotate Z
		
		my_cam.at[0] = aX * cos(theta) - aY * sin(theta);	
		my_cam.at[1] = aX * sin(theta) + aY * cos(theta);
		
		
	}
	
}
