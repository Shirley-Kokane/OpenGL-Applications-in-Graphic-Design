#ifndef OCTAHEDRON_H_INCLUDED
#define OCTAHEDRON_H_INCLUDED



#endif // OCTAHEDRON_H_INCLUDED
#include <GL/glut.h>

GLfloat pos[2];		//x,y
GLfloat dir[2];		//dx,dy
GLint rot;		//degrees

/**********************************************************/
/* Material */
/**********************************************************/

struct Material {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shiny;
};
typedef struct Material Material;

struct Point{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
typedef struct Point Point;

Material WhatIsBrass(void);

Material WhatIsRedPlastic(void);


void SetMaterial(Material m);

GLfloat vertices[6][3] =	{{1,0,0},
							{0,-1,0},
							{0,0,1},
							{-2,0,0},
							{0,2,0},
							{0,0,-2}};
GLubyte octaIndices[24] =	{0,1,2,     //face indices
							 0,1,5,
							 0,2,4,
							 0,4,5,
							 1,2,3,
							 1,3,5,
							 2,3,4,
							 3,4,5};
