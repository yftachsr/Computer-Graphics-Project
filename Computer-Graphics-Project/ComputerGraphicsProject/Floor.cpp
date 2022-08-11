#include "Floor.h"
//constructor
Floor::Floor(float gridSizeX, float gridSizeY, float squareSizeX, float squareSizeY) {
	
	t = new Texture("floorT1.jpg", 1);//create texture object to the floor
	this->gridSizeX = gridSizeX;
	this->gridSizeY = gridSizeY;
	this->squareSizeX = squareSizeX;
	this->squareSizeY = squareSizeY;

}

void Floor::reflection(Robot * bipbop) {
	glClear(GL_STENCIL_BUFFER_BIT);
	glColorMask(false, false, false, false);//Disable writting in color buffer
	glDepthMask(false);//Disable writting in depth buffer

	glEnable(GL_STENCIL_TEST);//Enable Stencil test
	glStencilFunc(GL_ALWAYS, 1, 1);//Test always success, value written 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);//Stencil & Depth test passes => replace existing value
	
	glBegin(GL_QUADS);
	glVertex3f(gridSizeX * squareSizeX/2.0f,0.0f, gridSizeY * squareSizeY/2.0f);
	glVertex3f(-gridSizeX * squareSizeX / 2.0f, 0.0f, gridSizeY * squareSizeY / 2.0f);
	glVertex3f(-gridSizeX * squareSizeX / 2.0f, 0.0f, -gridSizeY * squareSizeY / 2.0f);
	glVertex3f(gridSizeX * squareSizeX / 2.0f, 0.0f, -gridSizeY * squareSizeY / 2.0f);
	glEnd();

	glColorMask(true, true, true, true);//Disable writting in color buffer
	glDepthMask(true);

	glStencilFunc(GL_EQUAL, 1, 1);//Draw only where stencil buffer is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);//Stencil buffer read only

	glPushMatrix();
	glScalef(1.0f, -1.0f, 1.0f);//Mirror Y
	glColor3f(1.0f, 0.0f, 0.0f);
	Objects::drawObjects();
	bipbop->draw(NULL);
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);//Disable Stencil test
	glDepthMask(true);
	glColorMask(true, true, true, true);//Enable drawing of r, g, b & a

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
	this->draw();
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);

}

void Floor::draw() {
	GLfloat ambient[] = { 0.135f ,0.225f, 0.1575f, 1.0f };
	GLfloat specular[] = { 10.0f, 10.0f, 10.0f, 1.0f };
	GLfloat diffuse[] = { 0.54f, 0.89f, 0.63f, 1.0f };
	GLfloat shininess = 128.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess); 
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-gridSizeX * squareSizeX / 2, 0, -gridSizeY * squareSizeY / 2);
	
	t->Bind();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for (unsigned int x = 0; x < gridSizeX; ++x) {
		for (unsigned int y = 0; y < gridSizeY; ++y)
		{

			glNormal3d(0, 1, 0);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f((float)x * squareSizeX, 0.0f, (float)y * squareSizeY);
			glNormal3d(0, 1, 0);
			glTexCoord2f(1.0f, 0.0f);  glVertex3f((float)(x + 1) * squareSizeX, 0.0f, (float)y * squareSizeY);
			glNormal3d(0, 1, 0);
			glTexCoord2f(1.0f, 1.0f);  glVertex3f((float)(x + 1) * squareSizeX, 0.0f, (float)(y + 1) * squareSizeY);
			glNormal3d(0, 1, 0);
			glTexCoord2f(0.0f, 1.0f);  glVertex3f((float)x * squareSizeX, 0.0f, (float)(y + 1) * squareSizeY);

		}
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	t->~Texture();
}
//get GridSizeX
float Floor::getGridSizeX() {
	return gridSizeX;
}
//get GridSizeY
float Floor::getGridSizeY() {
	return gridSizeY;
}
//get SquareSizeX 
float Floor::getSquareSizeX() {
	return squareSizeX;
}
//get SquareSizeY
float Floor::getSquareSizeY() {
	return squareSizeY;
}