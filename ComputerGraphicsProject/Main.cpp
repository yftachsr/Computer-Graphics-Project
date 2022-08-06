#include "Scene.h"
#include <iostream>
#include <fstream>

Scene* currentInstance;

float ambientValues[] = { 0.5,0.5,0.5,1 };
float diffuseValues[] = { 1.5,1.5,1.5,1 };
int organNum = 7, objectNum = 10;

void menuHandler(int value) {

	if (value == 0) {
		exit(0);
	}
	else if (value == 1) {
		currentInstance->menu->ambientInput = true;
		currentInstance->menu->drawTextBool = true;
	}
	else if (value == 2) {
		MessageBox(NULL, TEXT("d"), TEXT("Help"), MB_HELP);
	}
	else if (value > 3 && value < 8)
		organNum = value;
	else if (value == 9) {
		currentInstance->menu->ambientInput = false;
		currentInstance->menu->drawTextBool = true;
	}

	else if (value == 3 || (value >= 8 && value <= 11)) {
		objectNum = value;
	}

	else if (value == 12) {
		currentInstance->changePov();

	}

	glutPostRedisplay();
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

void passiveMouseMotionCallback(int x, int y) {
	currentInstance->passiveMouseMotion(x, y);
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
	glutCreateWindow("");										//
	glClearColor(1.0, 1.0, 1.0, 1.0);							//

	cam = new Camera(glm::vec3(40.0f, 30.0f, -40.0f), glm::vec3(-1.0f, -1.0f, 1.0f));
	robotCam = new RobotCamera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	floor = new Floor(16, 16, 8, 8);
	light = new Light(GL_LIGHT0, 0.0f, 40.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	objects = new Objects();

	bipbop = new Robot(robotCam->viewDirection);
	room = new Room(13.0f, 13.0f, 8.0f, 8.0f);

	prevCamPos = cam->pos;
	prevCamDiraction = cam->viewDirection;

	menu = new Menu(menuHandler);


	::currentInstance = this;
	registerCallbacks();

	glutMainLoop();
}

void Scene::drawAxis() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);

	glVertex3f(0.0f, 0.02f, 125.0f);
	glVertex3f(0.0f, 0.02f, -125.0f);

	glVertex3f(0, 0.02, 125);
	glVertex3f(0, 0.02, -125);

	glColor3f(0, 1, 0);
	glVertex3f(0.0f, 125.0f, 0.0f);
	glVertex3f(0.0f, -125.0f, 0.0f);
	glColor3f(0, 0, 1);
	glVertex3f(125.0f, 0.02f, 0.0f);
	glVertex3f(-125.0f, 0.02f, 0.0f);
	glEnd();
}

void Scene::project() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, ratio, 1, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Scene::display(void) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glutSetCursor(GLUT_CURSOR_NONE);
	float amientIntensity = 0.2f;
	//float ambientLight1[] = { amientIntensity, amientIntensity, amientIntensity, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight1);

	if (!robotView)
		gluLookAt(cam->pos.x, cam->pos.y, cam->pos.z,
			cam->pos.x + cam->viewDirection.x, cam->pos.y + cam->viewDirection.y, cam->pos.z + cam->viewDirection.z, 0, 1, 0);
	else
		gluLookAt(robotCam->pos.x, robotCam->pos.y, robotCam->pos.z
			, robotCam->pos.x + robotCam->viewDirection.x, robotCam->pos.y + robotCam->viewDirection.y, robotCam->pos.z + robotCam->viewDirection.z, 0, 1, 0);

	//glutSetCursor(GLUT_CURSOR_NONE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientValues);

	menu->drawTextBox();

	light->draw();
	//floor->draw();
	room->draw();
	drawAxis();
	testingObjects();
	float currentRotationAngle = bipbop->getRotationAngle();
	//std::cout << std::to_string(cam->xoffset) << std::endl;
	glPushMatrix();
	glTranslated(bipbop->getPos().x, bipbop->getPos().y, bipbop->getPos().z);
	if(prevRotationAngle != currentRotationAngle)
		robotRotationAngle += currentRotationAngle;
	prevRotationAngle = currentRotationAngle;
	glRotated(robotRotationAngle, 0, 1, 0);
	glTranslated(-bipbop->getPos().x, -bipbop->getPos().y, -bipbop->getPos().z);
	bipbop->draw(robotView);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

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
	prevCamPos = cam->pos; // save main camera position
	prevCamDiraction = cam->viewDirection; // save main camera direction
	robotView = !robotView;
	if (robotView)
		objectNum = 11; // move robot
	else
		objectNum = 10; // move camera
}
void Scene::keyPress(unsigned char key, int x, int y) {

	if (key == '-')
		light->setCutoff(light->getCutoff() - 3.0f);
	else if (key == '=')
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
	case 8:
		changeLightPos = true;
		light->move(key, cam->viewDirection, changeLightPos, deltaTime);
		break;
	case 3:
		changeLightPos = false;
		light->move(key, cam->viewDirection, changeLightPos, deltaTime);
		break;
	case 10:
		moveCam = true;
		if (!robotView) // move main camera
			cam->move(key, deltaTime);
		break;
	case 11:
		moveCam = false;
		if (!robotView) { // move the robot reletive to the main camera
			bipbop->move(key, cam->viewDirection, robotCam, deltaTime);
			robotCam->move(key, cam->viewDirection, deltaTime);
		}
		else { // move the robot reletive to the robot camera
			bipbop->move(key, robotCam->viewDirection, robotCam, deltaTime);
			robotCam->move(key, robotCam->viewDirection, deltaTime);
		}
	}
}

void Scene::specialKeys(int key, int x, int y) {

	bipbop->moveOrgan(organNum, key,robotCam,deltaTime);

}

void Scene::mouseMotion(int x, int y) {

	if (!robotView)
		cam->lookAround(x, y, &firstMouse, screenWidth / 2, screenHeight / 2);

	project();
	glutPostRedisplay();
}

void Scene::passiveMouseMotion(int x, int y) {

	//std::cout << "(" << cam->viewDirection.x << "," << cam->viewDirection.y << "," << cam->viewDirection.z << ")" << std::endl;
	if (firstMouse) {
		glutWarpPointer(screenWidth / 2, screenHeight / 2);
		cam->lastX = screenWidth / 2;
		cam->lastY = screenHeight / 2;
		firstMouse = false;
	}
}

void Scene::testingObjects() {

	/*glPushMatrix();
	glTranslatef(10, 20, 10);
	glColor3f(0.7f, 0.3f, 0.3f);
	glutSolidCube(6);
	glPopMatrix();*/

	objects->drawObjects();

}

void Scene::registerCallbacks() {

	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyPressCallback);
	glutMotionFunc(mouseMotionCallback);
	glutPassiveMotionFunc(passiveMouseMotionCallback);
	glutSpecialFunc(specialKeysCallback);
	glutIdleFunc(idleCallback);


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
	delete floor;
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