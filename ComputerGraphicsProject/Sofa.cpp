#include "Sofa.h"


void Sofa::draw() {

	legs();

	//base
	glPushMatrix();
	glScaled(4.7, 0.5, 6.5);
	glTranslated(-2, 6, 2.3);
	glutSolidCube(5);
	//buttom pillow
	glColor3f(0.0f, 0.0f, 1.0f);
	glScaled(0.7, 1.3, 1.2);
	glTranslated(0, 4, 0);
	glutSolidTorus(2, 2, 20, 20); 
	glPopMatrix();
	
	//back pillow
	glPushMatrix();
	glColor3f(0.0f, 0.9f, 0.0f);
	glRotated(90, 0, 0, 1);
	glScaled(3.5, 2.4, 0.65);
	glTranslated(-4.5, 6, -27);
	
	glutSolidTorus(2, 2, 20, 20);
	glPopMatrix();
	//side 1
	glColor3f(0.6f, 0.2f, 0.3f);
	glPushMatrix();
	glScaled(4.7, 2.6, 0.5);
	glTranslated(-2, 3.2, 0);
	glutSolidCube(5);
	//side 2
	glTranslated(0, 0, 60);
	glutSolidCube(5);
	glPopMatrix();

	//back side
	glPushMatrix();
	glScaled(0.5, 3, 6.455);
	glTranslated(-40, 3.2, 2.33);
	glutSolidCube(5);
	glPopMatrix();
}

void Sofa::legs() {

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, 0, -2);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glTranslated(-17, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glTranslated(0, 30, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glTranslated(17, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glPopMatrix();
}