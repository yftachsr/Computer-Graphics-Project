#include "Texture.h"
#include "stb_image.h"

GLuint texName; //hold the texture

//constructor
Texture::Texture(std::string path,int idNum){
	id = idNum;
	dataBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 0);//load the photo in to the buffer 
}

//delete texture
Texture::~Texture(){
	glDeleteTextures(id, &texName);
}

//bind and load the current texture to  GL_TEXTURE_2D
void Texture::Bind() const{
	glGenTextures(1, &texName);//generate one texture to store in texName
	glBindTexture(GL_TEXTURE_2D, texName);//bind the texture in texName to GL_TEXTURE_2D
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// texture paramters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,	GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,	GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width , height , 0, GL_RGB, GL_UNSIGNED_BYTE,dataBuffer);//load the texture
}
