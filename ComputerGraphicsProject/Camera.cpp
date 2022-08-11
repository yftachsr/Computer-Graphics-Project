#include "Camera.h"

Camera::Camera(glm::vec3 pos) {

	this->pos = pos;
	this->viewDirection = glm::normalize(glm::vec3(10-pos.x, 15-pos.y, -pos.z));
	yaw = 70.0f-glm::degrees(atan(pos.x / pos.z));
	pitch = 10.0f+glm::degrees(atan(pos.y / pos.x));
	lastX = 0.0f; lastY = 0.0f;

}

void Camera::move(unsigned char key, float deltaTime) {

	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 normal = glm::cross(upVector, viewDirection);
	normal = glm::normalize(normal);
	float speed = 0.1f * deltaTime;
	viewDirection = glm::normalize(viewDirection);

	if (key == 'w' || key == 'W') 
		pos += speed * viewDirection;

	else if (key == 's' || key == 'S') 
		pos -= speed * viewDirection;
	
	else if (key == 'd' || key == 'D') 
		pos -= speed * normal;

	else if (key == 'a' || key == 'A') 
		pos += speed * normal;

}

void Camera::lookAround(int x, int y, bool* firstMouse, 
	float screenCenterX, float screenCenterY) {

	glm::vec3 direction;

	if (x <= 480 || x >= screenCenterX - 480 || y <= 480
		|| y >= screenCenterY - 480) { //keep mouse in the screen
		lastX = screenCenterX;
		lastY = screenCenterY;
		glutWarpPointer((int)screenCenterX, (int)screenCenterY);
	}

	float xoffset = (float)x - lastX; //x distance of mouse cursor from the previous position
	float yoffset = lastY - (float)y; //y distance of mouse cursor from the previous position
	lastX = (float)x;
	lastY = (float)y;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	//limit the pitch
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	viewDirection = glm::normalize(direction);
}

glm::vec3 Camera::getPos() {
	return pos;
}

glm::vec3 Camera::getViewDirection() {
	return viewDirection;
}

