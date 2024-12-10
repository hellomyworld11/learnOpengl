#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>
#define LOGSIZE 1024

class Shader
{
public:
	Shader();

	Shader& use();
		
	void compile(const char *vertexSrc, const char *fragmentsrc, const char *geometrySrc = nullptr);

	void setFloat(const char *name, float value, bool useShader = false);

	void setInteger(const char *name, int value, bool useShader = false);

	void    SetVector2f(const char *name, float x, float y, bool useShader = false);

	void    SetVector2f(const char *name, const glm::vec2 &value, bool useShader = false);

	void    SetVector3f(const char *name, float x, float y, float z, bool useShader = false);

	void    SetVector3f(const char *name, const glm::vec3 &value, bool useShader = false);

	void    SetVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);
	
	void    SetVector4f(const char *name, const glm::vec4 &value, bool useShader = false);
	
	void    SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader = false);

	unsigned int	getId() { return id_; }
private:
	void checkCompileErrors(unsigned int object);

	void checkLineErrors(unsigned int object);
private:
	unsigned int id_;
};

