#pragma once
#include "HeaderGL.h"
#include "RobotCamera.h"
#include <cmath>

#define MAX_PITCH_ANGLE 25.0f
#define MAX_YAW_ANGLE 50.0f

class Robot
{
public:

	Robot();
	void draw(bool);
	void moveHead(int, RobotCamera*, float);
	void move(unsigned char, glm::vec3, float);
	void drawArm(int shoulderAngle, int elbowAngle, int wristAngle);
	float getPitch();
	float getYaw();
	~Robot() = default;
	void moveOrgan(int part, int, RobotCamera*, float);
	glm::vec3 getPos();
	float getRotationAngle();

private:
	glm::vec3 pos;
	float pitch = 0.0f, yaw = 0.0f, rotationAngle = 0.0f;
	bool isSameDirection = false;
	int shoulderAngle = 0;
	int elbowAngle = 0;
	int wristAngle = 0;
	void drawLegs();
	void drawHead(float, float);
};
