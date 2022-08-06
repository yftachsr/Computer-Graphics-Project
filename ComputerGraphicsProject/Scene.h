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

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600

class Scene {
private:
	Camera* cam;
	RobotCamera* robotCam;
	Floor* floor;
	Light* light;
	Objects* objects;
	Room* room;
	double ratio = 1;
	int screenWidth = WINDOW_SIZE_X, screenHeight = WINDOW_SIZE_Y;
	float deltaTime = 0, lastFrame = 0;
	int currentFrame = 0;
	bool firstMouse = true, moveCam = true, robotView = false,
		changeLightPos = true, updateAngle = true;
	glm::vec3 prevCamPos, prevCamDiraction;
	float robotRotationAngle = 0.0f, prevRotationAngle;
public:
	Scene(int argc, char** argv);
	void display();
	void drawAxis();
	void project();
	void reshape(int, int);
	void keyPress(unsigned char, int, int);
	void mouseMotion(int, int);
	void passiveMouseMotion(int, int);
	void idle();
	void registerCallbacks();
	void specialKeys(int,int,int);
	void moveObjects(int);
	void changePov();
	void testingObjects();
	float getRotationAngle();
	void setRotationAngle(float);
	~Scene();
	Robot* bipbop;
	Menu* menu;
};