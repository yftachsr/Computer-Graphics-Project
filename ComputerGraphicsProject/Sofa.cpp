#include "Sofa.h"


void Sofa::draw() {
	GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	GLfloat ambient[] = { 0.19225f , 0.19225f, 0.19225f, 1.0f };
	GLfloat shininess = 0.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess );

	glPushMatrix();
	glTranslated(-26, 0, 18);
	glScaled(0.75,0.75,0.65);
	glRotated(30, 0, 1, 0);
	glColor3f(0.6f, 0.2f, 0.3f);
	
	glColor3f(0.6164,0.5929, 0.6509);
	legs();

	glColor3f(0.6542, 0.3542, 0.3542);
	//side 1
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

	//base
	glPushMatrix();
	glScaled(4.7, 0.5, 6.5);
	glTranslated(-2, 6, 2.3);
	glutSolidCube(5);

	glColor3f(0.6f, 0.2f, 0.3f);
	//glColor3f(0.464843, 0.533333, 0.59765);
	//buttom pillow
	glScaled(0.7, 1.3, 1.2);
	glTranslated(0, 4, 0);
	glutSolidTorus(2, 2, 20, 20); 
	glPopMatrix();
	
	//back pillow
	glPushMatrix();
	glRotated(20, 0, 0, 1);
	glRotated(90, 0, 1, 0);
	glScaled(3.5, 2.4, 0.65);
	glTranslated(-4.25, 8, -15);
	
	glutSolidTorus(2, 2, 20, 20);
	glPopMatrix();

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