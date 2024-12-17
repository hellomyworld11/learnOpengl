#pragma once
#include "GameObject.h"

class BallObject:public GameObject
{
public:
	BallObject();

	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity,
		Texture2D sprite);

	~BallObject()=default;

	glm::vec2 move(float dt, unsigned int window_width);

	void reset(glm::vec2 position, glm::vec2 velocity);

	float radius_;
	bool isStuck_;
};

