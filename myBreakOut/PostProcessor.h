#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "SpriteRenderer.h"

//∫Û¥¶¿Ì
class PostProcessor
{
public:
	PostProcessor(Shader shader, unsigned int width, unsigned int height);

	void beginRender();

	void endRender();

	void render(float time);
	
	Shader postProcessingShader_;
	Texture2D texture_;
	unsigned int width_;
	unsigned int height_;
	bool confuse_;
	bool chaos_;
	bool shake_;

private:
	void initRenderData();

	unsigned int MSFBO;
	unsigned int FBO;
	unsigned int RBO;
	unsigned int VAO;
};

