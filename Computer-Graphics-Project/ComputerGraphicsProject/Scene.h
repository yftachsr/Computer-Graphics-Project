#pragma once
#include "HeaderGL.h"
#include "Light.h"
#include "Floor.h"
#include "Camera.h"
#include "RobotCamera.h"
#include "Robot.h"
#include "Objects.h"
#include "Room.h"
#include "Menu.h"
#include <math.h>

#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 700

class Scene {
private:
	Camera* cam;
	RobotCamera* robotCam;
	Light* light;
	Objects* objects;
	Room* room;
	double ratio = 1;
	int screenWidth = WINDOW_SIZE_X, screenHeight = WINDOW_SIZE_Y;
	float deltaTime = 0, lastFrame = 0;
	int currentFrame = 0;
	bool firstMouse = true, moveCam = true, robotView = false,
		changeLightPos = true, updateAngle = true;
	float robotRotationAngle = 0.0f, prevRotationAngle;
	float ambientValues[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float diffuseValues[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
public:
	Scene(int argc, char** argv);
	void display();
	void drawAxis();
	void project();
	void reshape(int, int);
	void keyPress(unsigned char, int, int);
	void mouseMotion(int, int);
	void idle();
	void registerCallbacks();
	void specialKeys(int,int,int);
	void moveObjects(int);
	void changePov();
	float getRotationAngle();
	void setRotationAngle(float);
	~Scene();
	Robot* bipbop;
	Menu* menu;
};