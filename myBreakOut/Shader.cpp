#include "Shader.h"



Shader::Shader()
{
}


Shader& Shader::use()
{
	glUseProgram(id_);
	return *this;
}

void Shader::compile(const char *vertexSrc, const char *fragmentsrc, const char *geometrySrc /*= nullptr*/)
{
	unsigned int vshader=0, fshader=0, gshader = 0;

	if (vertexSrc != nullptr)
	{
		vshader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshader, 1, &vertexSrc, NULL);
		glCompileShader(vshader);
		checkCompileErrors(vshader);
	}

	if (fragmentsrc != nullptr)
	{
		fshader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshader, 1, &fragmentsrc, NULL);
		glCompileShader(fshader);
		checkCompileErrors(fshader);
	}

	if (geometrySrc != nullptr)
	{
		gshader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gshader, 1, &geometrySrc, NULL);
		glCompileShader(gshader);
		checkCompileErrors(gshader);
	}

	id_ = glCreateProgram();
	if (vshader != 0)
	{
		glAttachShader(id_, vshader);
	}
	if (fshader != 0)
	{
		glAttachShader(id_, fshader);
	}
	if (gshader != 0)
	{
		glAttachShader(id_, gshader);
	}
	glLinkProgram(id_);
	checkLineErrors(id_);

	glDeleteShader(vshader);
	glDeleteShader(fshader);
	glDeleteShader(gshader);
}

void Shader::setFloat(const char *name, float value, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform1f(uniformlocation, value);
}

void Shader::setInteger(const char *name, int value, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform1i(uniformlocation, value);
}

void Shader::SetVector2f(const char *name, float x, float y, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform2f(uniformlocation, x, y);
}

void Shader::SetVector2f(const char *name, const glm::vec2 &value, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform2f(uniformlocation, value.x, value.y);
}

void Shader::SetVector3f(const char *name, float x, float y, float z, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform3f(uniformlocation, x, y, z);
}

void Shader::SetVector3f(const char *name, const glm::vec3 &value, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform3f(uniformlocation, value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, float x, float y, float z, float w, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform4f(uniformlocation, x, y, z, w);
}

void Shader::SetVector4f(const char *name, const glm::vec4 &value, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniform4f(uniformlocation, value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader /*= false*/)
{
	if (useShader) use();

	GLint uniformlocation;
	uniformlocation = glGetUniformLocation(id_, name);
	glUniformMatrix4fv(uniformlocation, 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object)
{
	GLint compilestate;
	glGetShaderiv(object, GL_COMPILE_STATUS, &compilestate);

	if (!compilestate)
	{
		char infoLog[LOGSIZE];
		glGetShaderInfoLog(object, LOGSIZE, NULL, infoLog);
		std::cout << "Compile Error: object: " << object << " " << infoLog << std::endl;
	}
}

void Shader::checkLineErrors(unsigned int object)
{
	GLint linkState;
	glGetProgramiv(object, GL_LINK_STATUS, &linkState);
	if (!linkState)
	{
		char infoLog[LOGSIZE];
		glGetProgramInfoLog(object, LOGSIZE, NULL, infoLog);
		std::cout << "Link Error: object: " << object << " " << infoLog << std::endl;
	}
}
