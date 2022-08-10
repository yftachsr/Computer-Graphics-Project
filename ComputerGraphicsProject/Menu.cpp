#include "Menu.h"

std::string str = "";
//constructor
Menu::Menu(void (*func)(int)) {
	int submenu_id1 = glutCreateMenu(func);
	glutAddMenuEntry("Quit", 0);
	glutAddMenuEntry("Adjust ambient ligth", 1);
	glutAddMenuEntry("Open\Close help", 2);
	int submenu_id2 = glutCreateMenu(func);
	glutAddMenuEntry("shoulder", 5);
	glutAddMenuEntry("Elbow", 4);
	glutAddMenuEntry("Wrist", 6);
	glutAddMenuEntry("Head", 7);
	int submenu_id3 = glutCreateMenu(func);
	glutAddMenuEntry("Position", 8);
	glutAddMenuEntry("Power", 9);
	glutAddMenuEntry("Direction", 3);
	glutCreateMenu(func);
	glutAddSubMenu("Menu", submenu_id1);
	glutAddSubMenu("Move robot organs", submenu_id2);
	glutAddSubMenu("Light", submenu_id3);
	glutAddMenuEntry("Move camera", 10);
	glutAddMenuEntry("Move Robot", 11);
	glutAddMenuEntry("Change POV", 12);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	drawTextBool = false;//set asking user for input to false
	ambientInput = false;//set asking user for new ambient valuse to false
}
//draw the help window
void Menu::drawHelp(bool show) {
	if (show){//if the help window need to be shown
		glDisable(GL_LIGHTING);//draw on the xy surface without lighting 
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1, 1, 1);
		
		Texture* t = new Texture("helpTexture1.jpg", 1);//load window texture
		t->Bind();
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);//draw help window
		glTexCoord2f(1,0);	glVertex2f(0.5, 0.8);
		glTexCoord2f(1,1);	glVertex2f(0.5, -0.8);
		glTexCoord2f(0,1);	glVertex2f(-0.5, -0.8);
		glTexCoord2f(0,0);	glVertex2f(-0.5, 0.8);
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
		t->~Texture();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
}
//function to be called when the user press a key 
void Menu::keyPress(char key, float input[]) {
	if (drawTextBool == true) {//if waiting for user input
		if (key == 13) {//if key is enter stop get input from user
			drawTextBool = false;
			InputFromUser(input);
			str = "";
		}
		else if (key == 127 && str.length() > 0)//if the key is delete
			str.pop_back();
		else//add new key to the str variable
			str += key;
	}
}
//help function to keyPress , get input from user - split at , and convert to float , put the user values in given array (input)
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
//draw text to the user screen, asking for values
void Menu::drawTextBox() {
	glDisable(GL_LIGHTING);//draw on the xy surface without lighting 
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
//help function to drawTextBox - draw the strings to be print
void Menu::TextBox(std::string description) {
	if (drawTextBool) {
		glColor3f(0.2f, 0.5f, 0.2f);
		glRasterPos2f(-0.5, 0.5);
		for (int i = 0; i < description.length(); i++) {//draw string to be display to user screen
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, description[i]);
		}
		glRasterPos2f(-0.4, 0.4);
		for (int i = 0; i < str.length(); i++)//draw the keys clicked by the user
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}
