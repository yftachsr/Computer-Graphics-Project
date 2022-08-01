#include "Table.h"

Table::Table( int radius ,int thickness, std::string texture_path) {
	texture = new Texture(texture_path, 1);
	this->radius = radius;
	this->thickness = thickness;
	height = radius * 3 / 4;
	quadric = gluNewQuadric();

}

void Table::drawLeg(){
	glPushMatrix();
	glTranslated(0, height, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(quadric, 1, 0.5, height, 100, 100);
	glPopMatrix();
}

void Table::drawSurface(){
	glPushMatrix();
	glTranslated(0, height, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quadric, radius, radius, thickness, 100, 100);
	glNormal3f(0.0f, -1.0f, 0.0f);
	gluDisk(quadric, 0, radius, 100, 100);
	glTranslated(0, 0, thickness);
	gluDisk(quadric, 0, radius, 100, 100);
	glPopMatrix();
}

void Table::drawTable(int x, int y, int z, bool tea){

	GLfloat specular[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
	GLfloat diffuse[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
	GLfloat ambient[] = { 0.329412f , 0.223529f, 0.027451f, 1.0f };
	GLfloat shininess = 0.21794872f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0f);
	
	glColor3f(1.f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslated(x, y, z);
	if (tea)
		drawTeapot(-2.5f, height + 4.5f, -2.0f);
	texture->Bind();
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(quadric, GL_TRUE);
	drawSurface();
	glPushMatrix();
	glTranslated(height, 0, 0);
	drawLeg();
	glTranslated(-2 * height, 0, 0);
	drawLeg();
	glTranslated(height, 0, height);
	drawLeg();
	glTranslated(0, 0, -2 * height);
	drawLeg();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	texture-> ~Texture();

}

void Table::drawTeapot(float x, float y, float z) {

	GLfloat specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	GLfloat diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	GLfloat ambient[] = { 0.19225f , 0.19225f, 0.19225f, 1.0f };
	GLfloat shininess = 0.4f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess * 128.0f);

	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(0.75f, 0.75f, 0.75f);
	glutSolidTeapot(3);
	glPopMatrix();
}

Table::~Table() {
	//delete quadric;
	delete texture;
}

