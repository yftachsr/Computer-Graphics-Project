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
	void drawHand(int shoulderAngle, int elbowAngle, int wristAngle);
	float getPitch();
	float getYaw();
	~Robot() = default;
	void moveOrgan(int part, int, RobotCamera*, float);
	glm::vec3 getPos();
	float getRotationAngle();
	bool getIsSameDirection();
	unsigned char getLastKey();

private:
	glm::vec3 pos;
	unsigned char lastKey;
	float pitch = 0.0f, yaw = 0.0f, rotationAngle = 0.0f;
	bool isSameDirection = false;
	void drawLegs();
	void drawHead(float, float);
	void updateIsSameDirection(unsigned char);
	int sign(float);
};

