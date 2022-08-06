#include "Floor.h"

Floor::Floor(float gridSizeX, float gridSizeY, float squareSizeX, float squareSizeY) {
	
	t = new Texture("floorT1.jpg", 1);
	this->gridSizeX = gridSizeX;
	this->gridSizeY = gridSizeY;
	this->squareSizeX = squareSizeX;
	this->squareSizeY = squareSizeY;

}

void Floor::draw() {

	GLfloat ambient[] = { 0.135,0.225f,0.1575f,1.0f };
	GLfloat specular[] = { 10.0f, 10.0f, 10.0f, 1.0f };
	GLfloat diffuse[] = { 0.54f, 0.89f, 0.63f, 1.0f };
	GLfloat shininess = 128*5;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess); 
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-gridSizeX * squareSizeX / 2, 0, -gridSizeY * squareSizeY / 2);
	
	glColor3f(0.4, 0.4, 0.4);
	t->Bind();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for (unsigned int x = 0; x < gridSizeX; ++x) {
		for (unsigned int y = 0; y < gridSizeY; ++y)
		{
			//if ((x + y) & 0x00000001) //modulo 2
			//	glColor3f(0.4f, 0.4f, 0.4f); //white
			//else
			//	glColor3f(0.0f, 0.0f, 0.0f); //black

			glNormal3d(0, 1, 0);
			glTexCoord2f(0, 0);  glVertex3f(x * squareSizeX, 0, y * squareSizeY);
			glNormal3d(0, 1, 0);
			glTexCoord2f(1, 0);  glVertex3f((x + 1) * squareSizeX, 0, y * squareSizeY);
			glNormal3d(0, 1, 0);
			glTexCoord2f(1, 1);  glVertex3f((x + 1) * squareSizeX, 0, (y + 1) * squareSizeY);
			glNormal3d(0, 1, 0);
			glTexCoord2f(0, 1);  glVertex3f(x * squareSizeX, 0, (y + 1) * squareSizeY);

		}
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	t->~Texture();



}

int Floor::getGridSizeX() {
	return gridSizeX;
}

int Floor::getGridSizeY() {
	return gridSizeY;
}

int Floor::getSquareSizeX() {
	return squareSizeX;
}

int Floor::getSquareSizeY() {
	return squareSizeY;
}