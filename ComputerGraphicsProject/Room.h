#pragma once
#include "Wall.h"
#include "Floor.h"
#include "HeaderGL.h"

#define NUM_OF_WALLS 5

class Room
{
private:
	Wall* walls[NUM_OF_WALLS];
	Floor* floor;
	float sizeX, sizeY;
public:
	Room(float, float, float, float);
	~Room();
	void draw();

};

