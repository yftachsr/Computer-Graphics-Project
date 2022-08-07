#include "Menu.h"

std::string str = "";

void Menu::drawHelp(bool show) {

	if (show){
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1, 1, 1);
		Texture* t = new Texture("helpTexture.jpg", 2);
		t->Bind();
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1,0);	glVertex2f(0.5, 0.71);
		glTexCoord2f(1,1);	glVertex2f(0.5, -0.71);
		glTexCoord2f(0,1);	glVertex2f(-0.5, -0.71);
		glTexCoord2f(0,0);	glVertex2f(-0.5, 0.71);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		t->~Texture();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}

}

void Menu::InputFromUser(float input[]) {
	std::string cur = "";
	int j = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',') {
			input[j] = std::stof(cur);
			j++;
			cur = "";
		}
		else
			cur += str[i];
	}
}

void Menu::drawTextBox() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	if (ambientInput)
		TextBox("enter new ambient light values(put comma between values)");
	else
		TextBox("enter new diffuse light values(put comma between values)");
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Menu::TextBox(std::string description) {
	if (drawTextBool) {
		glColor3f(0.2f, 0.5f, 0.2f);
		glRasterPos2f(-0.5, 0.5);
		for (int i = 0; i < description.length(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, description[i]);
		}
		glRasterPos2f(-0.4, 0.4);
		for (int i = 0; i < str.length(); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void Menu::keyPress(char key, float input[]) {
	if (drawTextBool == true) {
		if (key == 13) {
			drawTextBool = false;
			InputFromUser(input);
			str = "";
		}
		else if (key == 127 && str.length() > 0)
			str.pop_back();
		else
			str += key;
	}
}

Menu::Menu(void (*func)(int)) {
	int submenu_id1 = glutCreateMenu(func);
	glutAddMenuEntry("Quit", 0);
	glutAddMenuEntry("adjust ambient ligth", 1);
	glutAddMenuEntry("help", 2);
	int submenu_id2 = glutCreateMenu(func);
	glutAddMenuEntry("elbow", 4);
	glutAddMenuEntry("shoulder", 5);
	glutAddMenuEntry("wrist", 6);
	glutAddMenuEntry("head", 7);
	int submenu_id3 = glutCreateMenu(func);
	glutAddMenuEntry("position", 8);
	glutAddMenuEntry("power", 9);
	glutAddMenuEntry("direction", 3);
	glutCreateMenu(func);
	glutAddSubMenu("Menu", submenu_id1);
	glutAddSubMenu("Move robot organ", submenu_id2);
	glutAddSubMenu("Light", submenu_id3);
	glutAddMenuEntry("Camera", 10);
	glutAddMenuEntry("Move Robot", 11);
	glutAddMenuEntry("Change POV", 12);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	drawTextBool = false;
	ambientInput = false;
}
