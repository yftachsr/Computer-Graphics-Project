#include "HeaderGl.h"
#include "string"
#pragma once

class Texture {
private:
	unsigned int id;
	unsigned char* dataBuffer;
	int height, width, bpp;
public:
	Texture(std::string,int);
	~Texture();
	void Bind() const;
};