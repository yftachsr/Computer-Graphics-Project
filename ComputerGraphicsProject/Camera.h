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
	Camera(glm::vec3, glm::vec3);
	virtual void move(unsigned char, float);
	void lookAround(int, int, bool*, int, int);
	//void rotate(float, float);
	glm::vec3 viewDirection, pos;
	int lastX, lastY;

	~Camera() = default;

private:
	float angle = 10.0f, pitch = 26.565f, yaw = -90.0f;
	//int deltaTime, lastFrame;
	
};

