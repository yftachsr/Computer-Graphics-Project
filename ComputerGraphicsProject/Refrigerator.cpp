#include "Refrigerator.h"

Refrigerator::Refrigerator(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Refrigerator::draw() {

	GLfloat specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	GLfloat diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	GLfloat ambient[] = { 0.19225f , 0.19225f, 0.19225f, 1.0f };
	GLfloat shininess = 0.8f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * 128.0f);

	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(180, 0, 1, 0);

	glColor3f(0.75, 0.75, 0.75);
	glPushMatrix();
	glTranslated(0, 14, 0);
	glScaled(1, 2.7, 2);
	glutSolidCube(11);
	glPopMatrix();
	
	buttomDoor();
	upperDoor();
	glTranslated(0, 38, 0);
	glRotated(180, 1, 0, 0);
	upperDoor();

	glPopMatrix();
}

void Refrigerator::buttomDoor() {

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslated(5, 5, 0);
	glScaled(0.4, 0.9, 1.7);
	glutSolidCube(11);
	glPopMatrix();

	glColor3f(0.824, 0.824, 0.824);
	glPushMatrix();
	glTranslated(8.5, 8, -7.5);
	gluCylinder(gluNewQuadric(), 0.4, 0.4, 15, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.7, 8, -6.5);
	glRotatef(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.3, 0.3, 3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.7, 8, 6.5);
	glRotatef(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.3, 0.3, 3, 100, 100);
	glPopMatrix();
}

void Refrigerator::upperDoor() {

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslated(5, 19, 4.9);
	glScaled(0.4, 1.5, 0.8);
	glutSolidCube(11);
	glPopMatrix();

	glColor3f(0.824, 0.824, 0.824);
	glPushMatrix();
	glTranslated(8.5, 25.5, 2);
	glRotatef(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.4, 0.4, 13, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(6.5, 24, 2);
	glRotatef(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.4, 0.4, 2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(6.5, 14, 2);
	glRotatef(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.4, 0.4, 2, 100, 100);
	glPopMatrix();
}