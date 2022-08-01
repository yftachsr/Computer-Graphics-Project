#include "Texture.h"
#include "stb_image.h"

GLuint texName;
Texture::Texture(std::string path,int idNum){
	id = idNum;
	file_path = path;
	dataBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 0);
}

Texture::~Texture(){
	glDeleteTextures(id, &texName);
}

void Texture::Bind() const{
	glGenTextures(id, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width ,
		height , 0, GL_RGB, GL_UNSIGNED_BYTE,
		dataBuffer);
	//stbi_image_free(dataBuffer);
}
