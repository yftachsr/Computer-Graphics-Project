#include "HeaderGl.h"
#include "string"
#pragma once

class Texture {
private:
	unsigned int id;
	std::string file_path;
	unsigned char* dataBuffer;
	int height, width, bpp;
public:
	Texture(std::string,int);
	~Texture();
	void Bind() const;
	/*void Unbind();
	inline int getWidth() const { return width; };
	inline int getHeightt() const { return height; };*/
};