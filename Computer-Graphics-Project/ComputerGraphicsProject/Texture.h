#pragma once
#include "HeaderGl.h"
#include "string"


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