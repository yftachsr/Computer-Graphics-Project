#include "RobotCamera.h"

RobotCamera::RobotCamera(glm::vec3 pos) : Camera(pos) {

	this -> viewDirection = glm::vec3(-1, 0, 0);

}

void RobotCamera::lookAround(float robotYaw, float robotPitch,float rotationAngle) {

	robotCamRotation = rotationAngle + 180.0f;
	viewDirection.x = cos(glm::radians(-robotYaw - robotCamRotation)) * cos(glm::radians(-robotPitch));
	viewDirection.y = sin(glm::radians(-robotPitch));
	viewDirection.z = sin(glm::radians(-robotYaw - robotCamRotation)) * cos(glm::radians(-robotPitch));
	viewDirection = glm::normalize(viewDirection);

}

void RobotCamera::move(unsigned char key,glm::vec3 moveDirection, float deltaTime) {

	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 normal = glm::cross(upVector, moveDirection);
	normal = glm::normalize(normal);
	float speed = 0.04f * deltaTime;

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