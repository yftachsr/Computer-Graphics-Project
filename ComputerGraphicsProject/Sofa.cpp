#include "Sofa.h"


void Sofa::draw() {

	legs();
	glPushMatrix();
	glScaled(5, 0.5, 6);
	glTranslated(-2, 7, 2.5);
	glutSolidCube(5);

	glPopMatrix();
}

void Sofa::legs() {

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, 0, -2);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glTranslated(-20, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glTranslated(0, 30, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glTranslated(20, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2, 100, 100);
	glPopMatrix();
}