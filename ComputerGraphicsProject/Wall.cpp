#include "Wall.h"

Wall::Wall(float width, float height, std::string texture_path) {
	texture = new Texture(texture_path, 1);
	this->width = width;
	this->height = height;
}

void Wall::draw() {
	
	glColor4f(1.0f, 1.0f, 1.0f,0.5);
	texture->Bind();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);   glVertex2d(-width / 2, 0);
	glTexCoord2f(1, 0);   glVertex2d(width / 2, 0);
	glTexCoord2f(1, 1);   glVertex2d(width/2, height);
	glTexCoord2f(0, 1);   glVertex2d(-width / 2, height);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	texture-> ~Texture();

}

Wall::~Wall() {
	//delete texture;
}