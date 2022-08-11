#pragma once
#include <GL/glut.h>
#include "Texture.h"
#include "Objects.h"
#include "Robot.h"
class Floor
{
private:
	float gridSizeX, gridSizeY, squareSizeX, squareSizeY;
	Texture* t;
public:
	Floor(float, float, float, float);
	void reflection(Robot * bipbop);
	void draw();
	float getGridSizeX();
	float getGridSizeY();
	float getSquareSizeX();
	float getSquareSizeY();
	~Floor() = default;
};

