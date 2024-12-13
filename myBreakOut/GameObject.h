#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Texture2D.h"
#include "SpriteRenderer.h"


class GameObject
{
public:
	GameObject();

	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
		glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	~GameObject()=default;

	virtual void draw(SpriteRenderer &renderer);

	glm::vec2 postion_;	
	glm::vec2 size_;
	glm::vec2 velocity_;

	glm::vec3 color_;
	Texture2D sprite_;
	float	  rotation_;
	bool	  isSolid_;
	bool	  isDestroyed_;
};

