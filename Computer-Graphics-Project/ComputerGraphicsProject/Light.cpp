#include "Light.h"

Light::Light(int id, float pX, float pY, float pZ,
	GLfloat tX, GLfloat tY, GLfloat tZ) {

	this->id = id;
	this->pos = glm::vec3(pX, pY, pZ);
	this->target = glm::vec3(tX, tY, tZ);

	glEnable(id);

}

void Light::draw() {

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.26f);
	glutSolidSphere(1, 20, 20);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	float posArr[] = { pos.x, pos.y, pos.z, 1.0f };
	glLightfv(id, GL_AMBIENT, ambient);
	glLightfv(id, GL_DIFFUSE, diffuse);
	glLightfv(id, GL_SPECULAR, specular);
	glLightfv(id, GL_POSITION, posArr);
	glm::vec3 directionVec = target - pos;
	GLfloat direction[3] = { directionVec.x, directionVec.y, directionVec.z }; // calc light direction
	glLightfv(id, GL_SPOT_DIRECTION, direction);
	glLightf(id, GL_SPOT_CUTOFF, cutoff);

}

void Light::move(unsigned char key, glm::vec3 viewDirection, bool changePos, float deltaTime) {

	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 normal = glm::cross(upVector, viewDirection);
	normal = glm::normalize(normal);
	float speed = 0.04f * deltaTime;
	glm::vec3 result;

	if (changePos)
		result = pos;
	else
		result = target;

	if (key == 'a' || key == 'A')
		result += speed * normal;

	else if (key == 'd' || key == 'D')
		result -= speed * normal;

	else if (key == 'w' || key == 'W') {
		result.x += speed * viewDirection.x;
		result.z += speed * viewDirection.z;
	}
	else if (key == 's' || key == 'S') {
		result.x -= speed * viewDirection.x;
		result.z -= speed * viewDirection.z;
	}
	else if (key == ']') // increase height
		result.y += speed;

	else if (key == '[') // decrease height
		result.y -= speed;

	if (changePos)
		pos = result;
	else
		target = result;

}

float Light::getCutoff() {
	return cutoff;
}

void Light::setCutoff(float x) {

	//limit cutoff
	if (x <= MIN_CUTOFF)
		x = MIN_CUTOFF;
	else if (x >= MAX_CUTOFF)
		x = MAX_CUTOFF;

	cutoff = x;
}

void Light::changeDiffuse(float* values) {
	diffuse[0] = values[0];
	diffuse[1] = values[1];
	diffuse[2] = values[2];
	diffuse[3] = values[3];
}

glm::vec3 Light::getTarget() {
	return target;
}

glm::vec3 Light::getPos() {
	return pos;
}
