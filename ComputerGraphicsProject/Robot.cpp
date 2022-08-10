#include "Robot.h"


Robot::Robot() {
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
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
	glRotatef(rotationAngle-90, 0, 1, 0);
	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	//Body
	glTranslated(0, 7.5, 0);
	glScaled(1.5, 1.7, 1);
	glutSolidCube(5);

	//Neck
	glTranslated(0, 3.5, 0);
	glRotated(90, 1, 0, 0);
	glColor3f(0.7f, 0.0f, 0.0f);
	gluCylinder(gluNewQuadric(), 0.8, 0.8, 1.5, 10, 10);
	glPopMatrix();

	//Legs
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslated(2, 0.45, 0);
	drawLegs();
	glPopMatrix();

	//Head
	if (!robotView) { // don't draw head when in robot POV (camera interferens)
		glPushMatrix();
		glTranslated(0, 14.7, 0);
		drawHead(pitch, yaw);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslated(4.6, 10, 0);
	drawArm(0, 0, 0);
	glTranslated(-9.2, 0, 0);
	drawArm(shoulderAngle, elbowAngle, wristAngle);
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

		else if (part == 6) 
			wristAngle += addAngle;
		
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
	glutSolidCone(1.3, 1.2, 20, 20);
	glTranslated(4, 0, 0);
	glutSolidCone(1.3, 1.2, 20, 20);
	glPopMatrix();
}

void Robot::drawHead(float xangle, float yangle) {

	glPushMatrix();
	glRotated(xangle, 1, 0, 0);
	glRotated(yangle, 0, 1, 0);

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslated(1.5f, 1.0f, 1.5f);

	// eye 1
	glPushMatrix();
	glScaled(1, 1.5, 1);
	glutSolidCube(1);
	glPopMatrix();

	glTranslated(-3.0f, 0.0f, 0.0f);

	// eye 2
	glPushMatrix();
	glScaled(1, 1.5, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	// head itself
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glScaled(2, 1.5, 1);
	glutSolidCube(3);
	glPopMatrix();

	// antena
	glPushMatrix();
	glTranslated(0, 4, 0);
	glRotated(90, 1, 0, 0);
	glColor3f(0.7f, 0.7f, 0.7f);
	gluCylinder(gluNewQuadric(), 0.1, 0.1, 4, 10, 10);
	glTranslated(0, 0, -0.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	gluSphere(gluNewQuadric(), 0.5, 10, 10);
	glPopMatrix();
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

	// limit pitch
	if (pitch >= MAX_PITCH_ANGLE)
		pitch = MAX_PITCH_ANGLE;
	else if (pitch <= -MAX_PITCH_ANGLE)
		pitch = -MAX_PITCH_ANGLE;

	// when yaw at maximum, rotate body
	if (yaw >= MAX_YAW_ANGLE && !(key == GLUT_KEY_DOWN || key == GLUT_KEY_UP)) {
		yaw = MAX_YAW_ANGLE;
		rotationAngle += speed;
	}	
	else if (yaw <= -MAX_YAW_ANGLE && !(key == GLUT_KEY_DOWN || key == GLUT_KEY_UP)) {
		yaw = -MAX_YAW_ANGLE;
		rotationAngle -= speed;
	}
	
	// update robot camera
	cam->lookAround(yaw, pitch, rotationAngle);
}

void Robot::move(unsigned char key, glm::vec3 moveDirection, float deltaTime) {

	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 normal = glm::cross(upVector, moveDirection);
	normal = glm::normalize(normal);
	float speed = 0.05f * deltaTime;

	if (key == 'w' || key == 'W') {
		pos.x += speed * moveDirection.x;
		pos.z += speed * moveDirection.z;
	}
	else if (key == 's' || key == 'S') {
		pos.x -= speed * moveDirection.x;
		pos.z -= speed * moveDirection.z;	
	}
	else if (key == 'd' || key == 'D') 
		pos -= speed * normal;
	
	else if (key == 'a' || key == 'A') 
		pos += speed * normal;
		
}

void Robot::drawArm(int shoulderAngle, int elbowAngle, int wristAngle) {

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);

	// shoulder joint
	glutSolidSphere(1, 15, 15);
	glRotated(shoulderAngle, 0, 1, 0);

	// upper arm
	glTranslated(0, 0, 0.5);
	glColor3f(1.0f, 1.0f, 0.0f);
	gluCylinder(gluNewQuadric(), 0.9, 0.9, 2, 30, 30);

	// elbow joint
	glTranslated(0, 0, 2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidSphere(1, 40, 40);
	glRotated(elbowAngle, 0, 1, 0);

	// forearm
	glTranslated(0, 0, 0.5);
	glColor3f(0.5f, 1.0f, 0.8f);
	gluCylinder(gluNewQuadric(), 0.9, 0.9, 2, 30, 30);

	// wrist joint
	glTranslated(0, 0, 2.5);
	glRotatef(wristAngle, 0, 0, 1);

	//hand
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