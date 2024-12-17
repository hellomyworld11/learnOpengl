#include "BallObject.h"



BallObject::BallObject():GameObject()
{
}

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
	:GameObject(pos, glm::vec2(radius*2.0f, radius*2.0f), sprite, glm::vec3(1.0f), velocity),
	radius_(radius),isStuck_(true)
{
	
}

glm::vec2 BallObject::move(float dt, unsigned int window_width)
{
	if (!isStuck_)
	{
		postion_ += dt * velocity_;

		if (postion_.x < 0.0f)
		{//·´Ïò
			velocity_.x = -velocity_.x;
			postion_.x = 0.0f;
		}
		else if (postion_.x + size_.x >= window_width)
		{
			velocity_.x = -velocity_.x;
			postion_.x = window_width - size_.x;
		}
		if (postion_.y <= 0.0f)
		{
			velocity_.y = -velocity_.y;
			postion_.y = 0.0f;
		}
	}
	return postion_;
}

void BallObject::reset(glm::vec2 position, glm::vec2 velocity)
{
	postion_ = position;
	velocity_ = velocity;
	isStuck_ = true;
}

