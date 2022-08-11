#pragma once
#include "HeaderGL.h"
#include "Camera.h"

class RobotCamera : public Camera
{
private:
	float robotCamRotation = 0.0f;
public:
	RobotCamera(glm::vec3);
	void lookAround(float, float,float);
	void move(unsigned char,glm::vec3, float);
};

