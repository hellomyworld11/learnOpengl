#include "ResourceManager.h"

#include <fstream>
#include <sstream>

#include "image/stb_image.h"

	
std::map<std::string, Shader> ResourceManager::shaders_;
std::map<std::string, Texture2D> ResourceManager::textures_;

Shader ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
	shaders_[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders_[name];
}

Shader ResourceManager::getShader(std::string name)
{
	return shaders_[name];
}

Texture2D ResourceManager::loadTexture(const char* file, bool alpha, std::string name)
{
	textures_[name] = loadTextureFromFile(file, alpha);
	return textures_[name];
}

Texture2D ResourceManager::getTexture(std::string name)
{
	return textures_[name];
}

void ResourceManager::clear()
{
//	shaders_.clear();
//	textures_.clear();
	for (auto iter : shaders_ )
	{
		glDeleteProgram(iter.second.getId());
	}

	for (auto iter : textures_)
	{
		glDeleteTextures(1, &iter.second.id_);
	}
}


Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char* fShaderFile, const char* gShaderFile /*= nullptr*/)
{
	std::string vShaderSrc;
	std::string fShaderSrc;
	std::string gShaderSrc;

	try
	{
		std::ifstream fstream(vShaderFile, std::ios_base::in);
		std::stringstream stream;
		stream << fstream.rdbuf();
		vShaderSrc = stream.str();

		fstream.close();
	
		stream.clear();
		stream.str("");
		fstream.open(fShaderFile, std::ios_base::in);
		stream << fstream.rdbuf();
		fShaderSrc = stream.str();

		if (gShaderFile != nullptr)
		{
			fstream.open(gShaderFile, std::ios_base::in);
			stream << fstream.rdbuf();
			gShaderSrc = stream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "error::shader: failed to read shader files" << std::endl;
	}

	Shader shader;
	shader.compile(vShaderSrc.c_str(), fShaderSrc.c_str());
	return shader;
}


// Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
// {
// 	// 1. retrieve the vertex/fragment source code from filePath
// 	std::string vertexCode;
// 	std::string fragmentCode;
// 	std::string geometryCode;
// 	try
// 	{
// 		// open files
// 		std::ifstream vertexShaderFile(vShaderFile);
// 		std::ifstream fragmentShaderFile(fShaderFile);
// 		std::stringstream vShaderStream, fShaderStream;
// 		// read file's buffer contents into streams
// 		vShaderStream << vertexShaderFile.rdbuf();
// 		fShaderStream << fragmentShaderFile.rdbuf();
// 		// close file handlers
// 		vertexShaderFile.close();
// 		fragmentShaderFile.close();
// 		// convert stream into string
// 		vertexCode = vShaderStream.str();
// 		fragmentCode = fShaderStream.str();
// 		// if geometry shader path is present, also load a geometry shader
// 		if (gShaderFile != nullptr)
// 		{
// 			std::ifstream geometryShaderFile(gShaderFile);
// 			std::stringstream gShaderStream;
// 			gShaderStream << geometryShaderFile.rdbuf();
// 			geometryShaderFile.close();
// 			geometryCode = gShaderStream.str();
// 		}
// 	}
// 	catch (std::exception e)
// 	{
// 		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
// 	}
// 	const char *vShaderCode = vertexCode.c_str();
// 	const char *fShaderCode = fragmentCode.c_str();
// 	const char *gShaderCode = geometryCode.c_str();
// 	// 2. now create shader object from source code
// 	Shader shader;
// 	shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
// 	return shader;
// }


Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.interal_format_ = GL_RGBA;
		texture.image_format_ = GL_RGBA;
	}

	int width, height, channel;
	unsigned char* data = stbi_load(file, &width, &height, &channel, 0);
	if (data == nullptr)
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	else {
		std::cout << "texture data: " << data << std::endl;
	}

	texture.generate(width, height, data);

	stbi_image_free(data);
	return texture;
}
