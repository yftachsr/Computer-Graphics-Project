#pragma once
#include <GL/glut.h>
#include "Texture.h"
class Floor
{
private:
	int gridSizeX, gridSizeY, squareSizeX, squareSizeY;
	Texture* t;
public:
	Floor(float, float, float, float);
	void draw();
	int getGridSizeX();
	int getGridSizeY();
	int getSquareSizeX();
	int getSquareSizeY();
	~Floor() = default;
};

