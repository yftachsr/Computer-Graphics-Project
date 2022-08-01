#pragma once
#include "HeaderGL.h"
#include "Texture.h"

class Wall
{
private:
	int width, height;
	Texture* texture;
public: 
	Wall(float, float, std::string);
	void draw();
	~Wall();
};

