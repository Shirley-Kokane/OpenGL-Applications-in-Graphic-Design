#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <GL/glut.h>
#include <math.h>
#include "octahedron.h"

#define PI 3.14159265

GLsizei ww = 700, wh = 700;
GLdouble orthoX = 700, orthoY = 700;
GLint wcx = 180, wcy = 180;
int xTrack, yTrack;					//tracks mouse movement
int moveX, moveY;					//possibly used later for animation

float rotSpeed[2];					//to be possibly used later for automatic rotation

bool tracking = false;				//true when left mouse is held down

double rotation[2] = {0,0};			//keeps track of current rotation

//calculate the norm from three points
//could be optimized a bit
Point norm(GLfloat a[3], GLfloat b[3], GLfloat c[3])
{
	GLfloat v1[3] = {a[0] - c[0], a[1] - c[1], a[2] - c[2]};
	GLfloat v2[3] = {b[0] - c[0], b[1] - c[1], b[2] - c[2]};

	Point n = {(v1[1] * v2[2]) - (v1[2] * v2[1]),
		(v1[2] * v2[0]) - (v1[0] * v2[2]),
		(v1[0] * v2[1]) - (v1[1] * v2[0])};

	return n;
}
void Init()
{

    glColor3f(0.0, 0.0, 1.0);   //this one
    glPointSize(15);             //and this one


    gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}

//calculate normal of each face, draw the face
//for some reason the normal of each odd face points inwards, so they are negated
void drawOcta(void){
	GLfloat x,y;
	int i = 0;
	Point n;
    glEnable(GL_COLOR_MATERIAL);
    //GLfloat const blue[3] = {0,0,255};

	for(i; i < 8; i++){
		glColor3f(0.0f,0.0f,1.0f);

		n = norm(vertices[octaIndices[i*3 + 1]], vertices[octaIndices[i*3 + 2]], vertices[octaIndices[i*3]]);
        //glColor3f(0.0f, 0.0f, 1.0f);
		if(i % 2 == 0){

            glColor3f(0.0f, 0.0f, 1.0f);
			glNormal3f(n.x, n.y, n.z);
			glBegin(GL_POINTS);
            glPointSize(5.0f);
            glVertex3d(0.0, 0.0, 1.0);
            glPointSize(5.0f);
            glVertex3d(1.0, 0.0, 0.0);
            glPointSize(5.0f);
            glVertex3d(0.0, -1.0, 0.0);
            glPointSize(5.0f);
            glVertex3d(-2.0 , 0.0, 0.0);
            glVertex3d(0.0 , 2.0, 0.0);
            glVertex3d(0.0 , 0.0, -2.0);
            glColor3f(0.0, 0.0, 1.0);
            glEnd();

		}
		else
            glColor3f(0.0f, 0.0f, 1.0f);
			glNormal3f(- n.x, - n.y, - n.z);
            //glColor3f(0.0f, 0.0f, 1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);

		glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_BYTE, &octaIndices[i*3]);
		glColor3f(0.0f, 0.0f, 1.0f);


	}

}

void ani() {

GLfloat x,y;
int i, j, k;
GLfloat pos[2];		//x,y,z
GLfloat dir[2];		//dx,dy,dz
GLint rot;		//degrees

int neg;

pos[0] = (GLfloat) x - (ww/2 - orthoX/2);
pos[1] = (GLfloat) y - (wh/2 - orthoX/2);

	//randomly set x direction (rand between -2.2 and 2.2, abs value >= .2)

	if(rand()%2 == 1) neg = 1;
	else neg = -1;
	dir[0] = .2 * neg + (float)(rand() % 100) *.02 * neg;

	//randomly set y direction (rand between -2.2 and 2.2, abs value >= .2)

	if(rand()%2 == 1) neg = 1;
	else neg = -1;
	dir[1] = .2 * neg + (float)(rand() % 100) *.02 * neg;
	rot = (GLint)(rand()%180);



		//randomly set rotation if hits a boundary
		for(k=0; k < 20; k++){
		if (pos[0] + (ww/2 - orthoX/2) > ww/2 + 149)  {
			if(dir[0] > 0) dir[0] = - dir[0];
			rot = (GLint)(rand()%180);
		}
		if (pos[0] + (ww/2 - orthoX/2) < ww/2 - 149) {
			if(dir[0] < 0) dir[0] = - dir[0];
			rot = (GLint)(rand()%180);
		}
		if (pos[1] + (wh/2 - orthoY/2) > wh/2 + 149)  {
			if(dir[1] > 0) dir[1] = - dir[1];
			rot = (GLint)(rand()%180);
		}
		if (pos[1] + (wh/2 - orthoY/2) < wh/2 - 149) {
			if(dir[1] < 0) dir[1] = - dir[1];
			rot = (GLint)(rand()%180);
		}

		}

		//displaceX += dirX * 5.0; displaceY += dirY * 3.0;
		for (i = 0; i < 20000; i++)
			for (j = 0; j < 200; j++) ;
		glutPostRedisplay ( );

}



void SetMaterial(Material m)
     /* sets the current material */
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m.ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m.diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m.specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.shiny);
}

void display() {

    glEnable(GL_COLOR_MATERIAL);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//store view matrix
	glPushMatrix();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	//lights off
	glDisable(GL_LIGHT0);
	//apply rotation
	glRotated(rotation[1], 1.0, 0.0, 0.0);
	glRotated(rotation[0], 0.0, 1.0, 0.0);






	//lights on
	glEnable(GL_LIGHT0);




	drawOcta();


	//recover viewing matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();



	glFlush();
	glutSwapBuffers();


}

//left mouse toggles tracking bool
void mouse(int button, int state, int x, int y) {

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		tracking = true;

	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		tracking = false;
	}

}

//tracks mouse position while mouse button is being held
void mouseTrackActive(int x, int y) {


		if(tracking == true){

			rotation[0] = rotation[0] + .7*(x - xTrack);
			if (rotation[0] >= 360) rotation[0]-=360;
			rotation[1] = rotation[1] + .7*(y - yTrack);
			if (rotation[1] >= 360) rotation[1]-=360;
		}

		xTrack = x;
		yTrack = y;
		glutPostRedisplay();
	}

//tracks mouse position while mouse button not being held
//essential to remain consistent with active mouse function
void mouseTrackPassive(int x, int y){

		xTrack = x;
		yTrack = y;
		glutPostRedisplay();
}

int main(int argc, char **argv) {


    /* background light */
    glEnable(GL_COLOR_MATERIAL);
    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize (ww, wh);
	glutInitWindowPosition (wcx, wcy);
	glutCreateWindow ("Octahedron");
	glutDisplayFunc(display);


	glMatrixMode (GL_PROJECTION);
	glViewport (0,0, ww, wh);
	glLoadIdentity ( );
	glOrtho (-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);
	glFrustum(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

	glutIdleFunc(ani);
	glutMotionFunc(mouseTrackActive);
	glutPassiveMotionFunc(mouseTrackPassive);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);


	glBegin(GL_POINTS);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3ub(0,0,255);
	glPointSize(15);
	glEnd();

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0f, 0.0f, 1.0f);
	GLfloat const blue[3] = {0,0,255};
	glColorPointer(3,GL_UNSIGNED_BYTE, 0, blue);
	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    /* set a low background light such that objects in the scene
       can be seen at all */

	glClearColor (1.0, 1.0, 1.0, 1.0);	   /*white background */


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    Init();

	glutMainLoop();
}
