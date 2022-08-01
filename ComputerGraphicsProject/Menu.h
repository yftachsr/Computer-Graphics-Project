#pragma once
#include "HeaderGL.h"
class Menu{
private:
	void TextBox(std::string description);
	void InputFromUser(float input[]);
public:
	bool ambientInput;
	bool drawTextBool;
	Menu(void (*func)(int));
	void drawTextBox();
	void keyPress(char key, float input[]);
};

