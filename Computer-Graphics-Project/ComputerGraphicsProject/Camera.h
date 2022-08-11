#pragma once
#include <GL/glut.h>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "HeaderGL.h"

#define DISTANCE(x1,y1,x2,y2) sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
#define PI 3.14159265359

class Camera
{
public:
	Camera(glm::vec3);
	virtual void move(unsigned char, float);
	void lookAround(int, int, bool*, float, float);
	glm::vec3 getPos();
	glm::vec3 getViewDirection();
	~Camera() = default;

protected:
	float pitch, yaw;
	glm::vec3 viewDirection, pos;
	float lastX, lastY;
	
};

