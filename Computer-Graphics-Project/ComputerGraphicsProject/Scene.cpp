#include "Scene.h"
#include <iostream>
#include <fstream>

Scene* currentInstance;

bool showHelp = false, drawMouse = false, showAxises = false;
int organNum = 7, objectNum = 10;

void menuHandler(int value) {

	if (value == 0) { // exit
		exit(0);
	}
	else if (value == 1) { // change ambient lighting
		currentInstance->menu->ambientInput = true;
		currentInstance->menu->drawTextBool = true;
	}
	else if (value == 2)  // show help
		showHelp = !showHelp;

	else if (value > 3 && value < 8) // move robot organs
		organNum = value;

	else if (value == 9) { // change lighting power
		currentInstance->menu->ambientInput = false;
		currentInstance->menu->drawTextBool = true;
	}

	else if (value == 3 || (value >= 8 && value <= 11)) { // move objects
		objectNum = value;
	}

	else if (value == 12) // change camera POV
		currentInstance->changePov();

	else if (value == 13)
		showAxises = !showAxises;

	glutPostRedisplay();
}

void menuOpen(int status) {

	if (status == GLUT_MENU_IN_USE) // menu is in use
		drawMouse = true;
	else // menu is not in use
		drawMouse = false;

}

void displayCallback() {
	currentInstance->display();
}

void reshapeCallback(int width, int height) {
	currentInstance->reshape(width, height);
}

void keyPressCallback(unsigned char key, int x, int y) {
	currentInstance->keyPress(key, x, y);
}

void mouseMotionCallback(int x, int y) {
	currentInstance->mouseMotion(x, y);
}

void idleCallback() {
	currentInstance->idle();
}

void specialKeysCallback(int key, int x, int y) {
	currentInstance->specialKeys(key, x, y);
}

Scene::Scene(int argc, char** argv) {

	glutInit(&argc, argv);										//
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);	//
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);			//
	glutInitWindowPosition(100, 100);							// INIT
	glutCreateWindow("Bipbop The Robot");						//
	glClearColor(1.0, 1.0, 1.0, 1.0);							//

	cam = new Camera(glm::vec3(-40.0f, 30.0f, -40.0f));
	robotCam = new RobotCamera(glm::vec3(0.0f, 15.0f, 0.0f));
	light = new Light(GL_LIGHT0, 20.0f, 35.0f, -35.0f, 0.0f, 0.0f, 0.0f);
	objects = new Objects();
	bipbop = new Robot();
	room = new Room(6.0f, 6.0f, 15.0f, 15.0f);
	menu = new Menu(menuHandler);

	::currentInstance = this;
	registerCallbacks();

	glutMainLoop();
}

void Scene::display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (!robotView) // main camera
		gluLookAt(cam->getPos().x, cam->getPos().y, cam->getPos().z,
			(double)cam->getPos().x + cam->getViewDirection().x,
			(double)cam->getPos().y + cam->getViewDirection().y, (double)cam->getPos().z + cam->getViewDirection().z, 0, 1, 0);
	else // robot camera
		gluLookAt(robotCam->getPos().x, robotCam->getPos().y, robotCam->getPos().z
			, (double)robotCam->getPos().x + robotCam->getViewDirection().x,
			(double)robotCam->getPos().y + robotCam->getViewDirection().y, (double)robotCam->getPos().z + robotCam->getViewDirection().z, 0, 1, 0);

	if (!drawMouse) // don't draw mouse when menu not in use
		glutSetCursor(GLUT_CURSOR_NONE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientValues);

	menu->drawTextBox();
	menu->drawHelp(showHelp);
	light->draw();
	room->draw(bipbop);

	if(showAxises)
		drawAxis();
	objects->drawObjects();
	bipbop->draw(robotView);

	glFlush();
	glutSwapBuffers();

}

void Scene::drawAxis() {

	glBegin(GL_LINES);

	// z axis
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.05f, 125.0f);
	glVertex3f(0.0f, 0.05f, -125.0f);

	// y axis
	glColor3f(0, 1, 0);
	glVertex3f(0.0f, 125.0f, 0.0f);
	glVertex3f(0.0f, -125.0f, 0.0f);

	// x axis
	glColor3f(0, 0, 1);
	glVertex3f(125.0f, 0.05f, 0.0f);
	glVertex3f(-125.0f, 0.05f, 0.0f);

	glEnd();
}

void Scene::project() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, ratio, 1, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Scene::reshape(int width, int height)
{
	if (width > height)
		ratio = (double)width / height;
	else
		ratio = (double)height / width;
	glViewport(0, 0, width, height);
	project();
}

void Scene::changePov() {

	robotView = !robotView;
	if (robotView)
		objectNum = 11; // move robot
	else
		objectNum = 10; // move camera

}

void Scene::keyPress(unsigned char key, int x, int y) {

	if (key == '-') // decrease cutoff
		light->setCutoff(light->getCutoff() - 3.0f);
	else if (key == '=') // increase cutoff
		light->setCutoff(light->getCutoff() + 3.0f);

	if (menu->ambientInput)
		menu->keyPress(key, ambientValues);
	else {
		menu->keyPress(key, diffuseValues);//changeTo difusse
		light->changeDiffuse(diffuseValues);
	}

	moveObjects(key);

	project();
	glutPostRedisplay();
}

void Scene::moveObjects(int key) {

	switch (objectNum) {
		case 8: // move light position
			changeLightPos = true;
			light->move(key, cam->getViewDirection(), changeLightPos, deltaTime);
			break;
		case 3: // move light direction
			changeLightPos = false;
			light->move(key, cam->getViewDirection(), changeLightPos, deltaTime);
			break;
		case 10: // move camera
			moveCam = true;
			if (!robotView) // move main camera
				cam->move(key, deltaTime);
			break;
		case 11: // move robot
			moveCam = false;
			if (!robotView) { // move the robot reletive to the main camera
				bipbop->move(key, cam->getViewDirection(), deltaTime);
				robotCam->move(key, cam->getViewDirection(), deltaTime);
			}
			else { // move the robot reletive to the robot camera
				bipbop->move(key, robotCam->getViewDirection(), deltaTime);
				robotCam->move(key, robotCam->getViewDirection(), deltaTime);
			}
	}
}

void Scene::specialKeys(int key, int x, int y) {

	bipbop->moveOrgan(organNum, key,robotCam,deltaTime);

}

void Scene::mouseMotion(int x, int y) {

	if (!robotView) // don't touch main camera when in robot POV
		cam->lookAround(x, y, &firstMouse, screenWidth / 2.0f, screenHeight / 2.0f);

	project();
	glutPostRedisplay();

}

float Scene::getRotationAngle() {

	return robotRotationAngle;

}

void Scene::setRotationAngle(float x) {

	robotRotationAngle = x;

}

void Scene::registerCallbacks() {

	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyPressCallback);
	glutMotionFunc(mouseMotionCallback);
	glutSpecialFunc(specialKeysCallback);
	glutIdleFunc(idleCallback);
	glutMenuStateFunc(menuOpen);

}

void Scene::idle() {

	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	glutPostRedisplay();
	lastFrame = (float)currentFrame;

}

Scene::~Scene() {

	delete cam;
	delete robotCam;
	delete light;
	delete bipbop;
	delete objects;
	delete room;

}

int main(int argc, char** argv) {

	Scene scene = Scene(argc, argv);

	delete currentInstance;

	return 0;
}