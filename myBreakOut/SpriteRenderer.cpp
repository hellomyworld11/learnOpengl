#include "SpriteRenderer.h"





SpriteRenderer::SpriteRenderer(Shader& shader)
{
	shader_ = shader;
	initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &quadVAO_);
}

void SpriteRenderer::drawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size /*= glm::vec2(10, 10)*/, GLfloat rotate /*= 0.0f*/, glm::vec3 color /*= glm::vec3(1.0f)*/)
{ 
	shader_.use();
	glm::mat4 model = glm::mat4(1.0f);	
	//Œª÷√
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f *size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f *size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader_.SetMatrix4("model", model);

	shader_.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(quadVAO_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	GLuint VBO;
	GLfloat vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &quadVAO_);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO_);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
