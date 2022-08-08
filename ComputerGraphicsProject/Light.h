#pragma once
#include "HeaderGL.h"
#include <algorithm>
#include <iterator>

#define MAX_CUTOFF 180.0f
#define MIN_CUTOFF 1.0f

class Light
{
private:
	int id;
	glm::vec3 pos, target;
	float cutoff = 50.0f;
	GLfloat ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
public:

	GLfloat color[3] = { 1.0f,1.0f,1.0f };
	glm::vec3 towardVector = glm::vec3(0, -1, 0);


	Light(int, float, float, float,
		GLfloat, GLfloat, GLfloat);

	void draw();
	void fixDirection();
	void move(unsigned char, glm::vec3, bool, float);
	float getCutoff();
	void setCutoff(float);
	void changeDiffuse(float*);
	glm::vec3 getPos();
	glm::vec3 getTarget();

	~Light() = default;

};