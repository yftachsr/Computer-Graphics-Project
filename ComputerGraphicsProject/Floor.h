#pragma once
#include <GL/glut.h>
#include "Texture.h"
#include "Objects.h"
#include "Robot.h"
class Floor
{
private:
	int gridSizeX, gridSizeY, squareSizeX, squareSizeY;
	Texture* t;
public:
	Floor(float, float, float, float);
	void reflection(Robot * bipbop);
	void draw();
	int getGridSizeX();
	int getGridSizeY();
	int getSquareSizeX();
	int getSquareSizeY();
	~Floor() = default;
};

