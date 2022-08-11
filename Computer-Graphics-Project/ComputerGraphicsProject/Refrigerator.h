#pragma once
#include "HeaderGL.h"

class Refrigerator
{
private:
	int x, y, z;
	void buttomDoor();
	void upperDoor();
public:
	Refrigerator(int,int,int);
	void draw();
};

