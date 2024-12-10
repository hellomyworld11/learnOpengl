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

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
	int width, height, channel;
	unsigned char* data = stbi_load(file, &width, &height, &channel, 0);

	Texture2D texture;
	if (alpha)
	{
		texture.interal_format_ = GL_RGBA;
		texture.image_format_ = GL_RGBA;
	}
	texture.generate(width, height, data);

	stbi_image_free(data);
	return texture;
}
