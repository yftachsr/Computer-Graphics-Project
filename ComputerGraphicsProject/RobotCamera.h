#pragma once
#include "HeaderGL.h"
#include "Camera.h"

class RobotCamera : public Camera
{
public:
	RobotCamera(glm::vec3,glm::vec3);
	void lookAround(float, float);
	void move(unsigned char,glm::vec3, float);
};

