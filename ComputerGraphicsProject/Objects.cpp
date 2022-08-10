#include "Objects.h"

//draw carrpet
void drawCarrpet() {
	Texture* t = new Texture("carrpetTexture.jpg", 1);//texture object to be display on the carret
	t->Bind();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);//draw carrpet
	glTexCoord2f(1, 1);	glVertex3f(10, 0.2, 10);
	glTexCoord2f(0, 1);	glVertex3f(10, 0.2, 40);
	glTexCoord2f(0, 0);	glVertex3f(30, 0.2, 40);
	glTexCoord2f(1, 0);	glVertex3f(30, 0.2, 10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	t->~Texture();
}
//draw photo
void drawPhoto() {
	Texture* t1 = new Texture("photoTexture.jpg", 1);//texture to be display on the photo
	t1->Bind();
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);//draw photo
	glTexCoord2f(1, 1);	glVertex3f(20, 20, 44.5);
	glTexCoord2f(0, 1);	glVertex3f(40, 20, 44.5);
	glTexCoord2f(0, 0);	glVertex3f(40, 40, 44.5);
	glTexCoord2f(1, 0);	glVertex3f(20, 40, 44.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	t1->~Texture();
}
//draw all the objects in the scene 
void Objects::drawObjects() {
	Table* b = new Table(10, 2, "woodenTexture.jpg");//create table object to be display
	b->drawTable(20, 0, 20, true);//draw the table object
	Refrigerator* r = new Refrigerator(-35, 1, -30);//draw the refrigerator
	r->draw();//draw the Refrigerator
	drawPhoto();//draw photo
	drawCarrpet();//draw carrpet
}
