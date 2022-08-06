#include "RobotCamera.h"

RobotCamera::RobotCamera(glm::vec3 pos, glm::vec3 viewDirection) 
	: Camera(pos,viewDirection) { }

void RobotCamera::lookAround(float robotYaw, float robotPitch,float rotationAngle) {

	glm::vec3 direction;
	direction.x = cos(glm::radians(-robotYaw - rotationAngle)) * cos(glm::radians(-robotPitch));
	direction.y = sin(glm::radians(-robotPitch));
	direction.z = sin(glm::radians(-robotYaw - rotationAngle)) * cos(glm::radians(-robotPitch));
	viewDirection = glm::normalize(direction);
}

void RobotCamera::move(unsigned char key,glm::vec3 moveDirection, float deltaTime) {

	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 normal = glm::cross(upVector, moveDirection);
	normal = glm::normalize(normal);
	float speed = 0.1f * deltaTime;

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