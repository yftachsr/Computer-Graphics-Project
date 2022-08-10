#include "Objects.h"

void drawCarrpet() {
	Texture* t = new Texture("carrpetTexture.jpg", 1);
	t->Bind();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);	glVertex3f(10, 0.2, 10);
	glTexCoord2f(0, 1);	glVertex3f(10, 0.2, 40);
	glTexCoord2f(0, 0);	glVertex3f(30, 0.2, 40);
	glTexCoord2f(1, 0);	glVertex3f(30, 0.2, 10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	t->~Texture();
}

void drawPhoto() {
	Texture* t1 = new Texture("photoTexture.jpg", 1);
	t1->Bind();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);	glVertex3f(20, 20, 44.5);
	glTexCoord2f(0, 1);	glVertex3f(40, 20, 44.5);
	glTexCoord2f(0, 0);	glVertex3f(40, 40, 44.5);
	glTexCoord2f(1, 0);	glVertex3f(20, 40, 44.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	t1->~Texture();
}
void Objects::drawObjects() {
	Table* b = new Table(10, 2, "woodenTexture.jpg");
	b->drawTable(20, 0, 20, true);
	Refrigerator* r = new Refrigerator(-35, 1, -30);
	r->draw();
	drawPhoto();
	drawCarrpet();
	Sofa* s = new Sofa();
	s->draw();
}
