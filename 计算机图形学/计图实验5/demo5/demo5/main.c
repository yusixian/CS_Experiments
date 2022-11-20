#include <stdio.h>
#include "GL/glut.h"

int axis;
float theta;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(theta, 0, 1, 0);
	gluLookAt(0.3, 0.6, 0.3, 0, 0, 0, 0, 3, 0);
	glutWireCube(3);//3表示边长
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);//glFrustum
}
void spinCube()
{
	theta += 2.0;
	if (theta > 360.0) theta -= 360.0;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("正平行六面体");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMainLoop();

	return 0;
}