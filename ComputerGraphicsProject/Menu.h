#pragma once
#include "HeaderGL.h"
#include "Texture.h"
class Menu{
private:
	void TextBox(std::string description);
	void InputFromUser(float input[]);
public:
	bool ambientInput;
	bool drawTextBool;
	Menu(void (*func)(int));
	void drawHelp(bool show);
	void drawTextBox();
	void keyPress(char key, float input[]);
};

