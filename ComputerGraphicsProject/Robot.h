#pragma once
#include "HeaderGL.h"
#include "RobotCamera.h"
#include <cmath>

#define MAX_PITCH_ANGLE 25.0f
#define MAX_YAW_ANGLE 50.0f

class Robot
{
public:
	glm::vec3 pos;
	Robot(glm::vec3);
	void draw(bool);
	void moveHead(int, RobotCamera*, float);
	void move(unsigned char, glm::vec3, float);
	void drawHand(int shoulderAngle, int elbowAngle, int wristAngle);
	float getPitch();
	float getYaw();
	~Robot() = default;
	void moveOrgan(int part, int, RobotCamera*, float);
	float angle = 0.0f;

private:
	float pitch = 0.0f, yaw = 0.0f, rotationAngle = 0.0f;
	glm::vec3 viewDirection;
	void drawLegs();
	void drawHead(float, float);
};

