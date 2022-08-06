#include "Robot.h"

int shoulderAngle = 0;
int elbowAngle = 0;
int wristAngle = 0;


Robot::Robot(glm::vec3 viewDirection) {
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->viewDirection = viewDirection;
}

void Robot::draw(bool robotView) {

	GLfloat specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	GLfloat diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	GLfloat ambient[] = { 0.19225f , 0.19225f, 0.19225f, 1.0f };
	GLfloat shininess = 0.4f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * 128.0f);



	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glRotatef(90, 0, 1, 0);
	glPushMatrix();

	//Body
	glTranslated(0, 7.5, 0);
	glScaled(1.5, 1.7, 1);
	glutSolidCube(5);

	//Neck
	glTranslated(0, 3.5, 0);
	glRotated(90, 1, 0, 0);
	glColor3f(0.7f, 0.0f, 0.0f);
	gluCylinder(gluNewQuadric(), 0.8, 0.8, 1.5, 100, 100);
	glPopMatrix();

	//Legs
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslated(2, 0.45, 0);
	drawLegs();
	glPopMatrix();

	//Head
	if (!robotView) {
		glPushMatrix();
		glTranslated(0, 14.7, 0);
		drawHead(pitch, yaw);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslated(4.6, 10, 0);
	drawHand(0, 0, 0);
	glTranslated(-9.2, 0, 0);
	drawHand(shoulderAngle, elbowAngle, wristAngle);
	glPopMatrix();
	glPopMatrix();

}

void Robot::moveOrgan(int part, int key, RobotCamera* cam, float deltaTime) {
	int addAngle = 0;
	if (part == 7)
		moveHead(key, cam, deltaTime);
	else {
		if (key == GLUT_KEY_UP)
			addAngle -= 30;

		else if (key == GLUT_KEY_DOWN)
			addAngle += 30;

		if (part == 4) {
			if ((elbowAngle > -150 || addAngle > 0) && (elbowAngle < 150 || addAngle < 0))
				elbowAngle += addAngle;
		}

		else if (part == 5) {
			if ((shoulderAngle > -180 || addAngle > 0) && (shoulderAngle < 0 || addAngle < 0))
				shoulderAngle += addAngle;
		}

		else if (part == 6) {
			wristAngle += addAngle;
		}
	}
}

void Robot::drawLegs() {

	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.9, 0.9, 4, 100, 100);
	glTranslated(-4, 0, 0);
	gluCylinder(gluNewQuadric(), 0.9, 0.9, 4, 100, 100);
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslated(0, 0, -0.3);
	glutSolidCone(1.3, 1.2, 100, 100);
	glTranslated(4, 0, 0);
	glutSolidCone(1.3, 1.2, 100, 100);
	glPopMatrix();
}

void Robot::drawHead(float xangle, float yangle) {

	glPushMatrix();
	glRotated(xangle, 1, 0, 0);
	glRotated(yangle, 0, 1, 0);
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslated(1.5f, 1.0f, 1.5f);
	glPushMatrix();
	glScaled(1, 1.5, 1);
	glutSolidCube(1);
	glPopMatrix();
	glTranslated(-3.0f, 0.0f, 0.0f);
	glPushMatrix();
	glScaled(1, 1.5, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glScaled(2, 1.5, 1);
	glutSolidCube(3);
	glPopMatrix();

}

void Robot::moveHead(int key, RobotCamera* cam, float deltaTime) {

	float speed = 0.3f * deltaTime;

	if (key == GLUT_KEY_DOWN)
		pitch += speed;
	else if (key == GLUT_KEY_UP)
		pitch -= speed;
	else if (key == GLUT_KEY_LEFT)
		yaw += speed;
	else if (key == GLUT_KEY_RIGHT)
		yaw -= speed;

	if (pitch >= MAX_PITCH_ANGLE)
		pitch = MAX_PITCH_ANGLE;
	else if (pitch <= -MAX_PITCH_ANGLE)
		pitch = -MAX_PITCH_ANGLE;

	if (yaw >= MAX_YAW_ANGLE)
		yaw = MAX_YAW_ANGLE;
	else if (yaw <= -MAX_YAW_ANGLE)
		yaw = -MAX_YAW_ANGLE;

	cam->lookAround(yaw, pitch);
}

void Robot::move(unsigned char key, glm::vec3 moveDirection, RobotCamera* cam, 
	float* angle, float deltaTime) {

	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 normal = glm::cross(upVector, moveDirection);
	normal = glm::normalize(normal);
	float speed = 0.05f * deltaTime;
	float yvalue = cam->viewDirection.y;
	prevViewDirection = cam->viewDirection;
	prevViewDirection.y = 0;
	prevViewDirection = glm::normalize(prevViewDirection);
	updateIsSameDirection(key);

	glm::vec3 newViewDirection;
	if (key == 'w' || key == 'W') {
		pos.x += speed * moveDirection.x;
		pos.z += speed * moveDirection.z;
		newViewDirection = glm::vec3(moveDirection.x, 0, moveDirection.z);
		if (!isSameDirection || prevMoveDirection != moveDirection) {
			newViewDirection = glm::normalize(newViewDirection);
			glm::vec3 crossNormal = glm::cross(prevViewDirection, newViewDirection);
			crossNormal = glm::normalize(crossNormal);
			if (sign(crossNormal.y) == 1)
				rotationAngle = glm::degrees(glm::angle(prevViewDirection, newViewDirection));
			else if (sign(crossNormal.y) == -1 || crossNormal.y != 0)
				rotationAngle = -glm::degrees(glm::angle(prevViewDirection, newViewDirection));
			std::cout << "cross (" << std::to_string(crossNormal.x) << "," <<
				std::to_string(crossNormal.y) << "," << std::to_string(crossNormal.z) << std::endl;
			cam->viewDirection = newViewDirection;
			cam->viewDirection.y = yvalue;
		}
		else
			rotationAngle = 0;
		
	}
	else if (key == 's' || key == 'S') {
		pos.x -= speed * moveDirection.x;
		pos.z -= speed * moveDirection.z;
		newViewDirection = -glm::vec3(moveDirection.x, 0, moveDirection.z);
		if (!isSameDirection || prevMoveDirection != moveDirection) {
			newViewDirection = glm::normalize(newViewDirection);
			glm::vec3 crossNormal = glm::cross(prevViewDirection, newViewDirection);
			crossNormal = glm::normalize(crossNormal);

			if (sign(crossNormal.y) == 1)
				rotationAngle = glm::degrees(glm::angle(prevViewDirection, newViewDirection));
			else if (sign(crossNormal.y) == -1 || crossNormal.y != 0)
				rotationAngle = -glm::degrees(glm::angle(prevViewDirection, newViewDirection));

			cam->viewDirection = newViewDirection;
			cam->viewDirection.y = yvalue;
		}
		else
			rotationAngle = 0;
	}
	else if (key == 'd' || key == 'D') {
		pos -= speed * normal;
		newViewDirection = -glm::vec3(normal.x, 0, normal.z);
		if (!isSameDirection || prevMoveDirection != moveDirection) {
			newViewDirection = glm::normalize(newViewDirection);
			glm::vec3 crossNormal = glm::cross(prevViewDirection, newViewDirection);
			crossNormal = glm::normalize(crossNormal);

			if (sign(crossNormal.y) == 1)
				rotationAngle = glm::degrees(glm::angle(prevViewDirection, newViewDirection));
			else if (sign(crossNormal.y) == -1 || crossNormal.y != 0)
				rotationAngle = -glm::degrees(glm::angle(prevViewDirection, newViewDirection));
			
			cam->viewDirection = newViewDirection;
			cam->viewDirection.y = yvalue;

		}
		else
			rotationAngle = 0;
	}
	else if (key == 'a' || key == 'A') {
		pos += speed * normal;
		newViewDirection = glm::vec3(normal.x, 0, normal.z);
		if (!isSameDirection || prevMoveDirection != moveDirection) {
			newViewDirection = glm::normalize(newViewDirection);
			glm::vec3 crossNormal = glm::cross(prevViewDirection, newViewDirection);
			crossNormal = glm::normalize(crossNormal);
			if (sign(crossNormal.y) == 1)
				rotationAngle = glm::degrees(glm::angle(prevViewDirection, newViewDirection));
			else if (sign(crossNormal.y) == -1 || crossNormal.y != 0)
				rotationAngle = -glm::degrees(glm::angle(prevViewDirection, newViewDirection));

			cam->viewDirection = newViewDirection;
			cam->viewDirection.y = yvalue;

		}
		else
			rotationAngle = 0;
	}
	
	lastKey = key;
	prevMoveDirection = moveDirection;
	*angle += rotationAngle;
}

void Robot::drawHand(int shoulderAngle, int elbowAngle, int wristAngle) {
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(1, 100, 100);
	glRotated(shoulderAngle, 0, 1, 0);
	glTranslated(0, 0, 0.5);
	glColor3f(1.0f, 1.0f, 0.0f);
	gluCylinder(gluNewQuadric(), 0.9, 0.9, 2, 100, 100);
	glTranslated(0, 0, 2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidSphere(1, 100, 100);
	glRotated(elbowAngle, 0, 1, 0);
	glTranslated(0, 0, 0.5);
	glColor3f(0.5f, 1.0f, 0.8f);
	gluCylinder(gluNewQuadric(), 0.9, 0.9, 2, 100, 100);
	glTranslated(0, 0, 2.5);
	glRotatef(wristAngle, 0, 0, 1);
	glScaled(0.7, 0.7, 0.7);
	glColor3f(0.5f, 0.0f, 0.8f);
	glutSolidDodecahedron();
	glPopMatrix();
}

float Robot::getPitch() {
	return pitch;
}

float Robot::getYaw() {
	return yaw;
}

float Robot::getRotationAngle() {
	return rotationAngle;
}

glm::vec3 Robot::getPos() {
	return pos;
}

bool Robot::getIsSameDirection() {
	return isSameDirection;
}

void Robot::updateIsSameDirection(unsigned char key) {
	if (lastKey == key)
		isSameDirection = true;
	else
		isSameDirection = false;
}

int Robot::sign(float x) {
	if (x > 0)
		return 1;
	else if (x < 0)
		return -1;
	return 0;
}

unsigned char Robot::getLastKey() {
	return lastKey;
}