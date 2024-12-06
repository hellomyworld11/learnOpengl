#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
	Shader();

	Shader& use();
		
	void Compile(const char *vertexSrc, const char *fragmentsrc, const char *geometrySrc = nullptr);

	void setFloat(const char *name, float value, bool useShader = false);

	void setInteger(const char *name, int value, bool useShader = false);

	void setFloat(const char *name, float value, bool useShader = false);
private:
	unsigned int id_;
};

