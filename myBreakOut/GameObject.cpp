#include "GameObject.h"



GameObject::GameObject()
	:postion_(0.0f, 0.0f),size_(1.0f, 1.0f)
	,velocity_(0.0f),color_(1.0f),rotation_(0.0f)
	,sprite_()
	,isSolid_(false), isDestroyed_(false)
{
}


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color /*= glm::vec3(1.0f)*/, glm::vec2 velocity /*= glm::vec2(0.0f, 0.0f)*/)
	:postion_(pos), size_(size)
	, velocity_(velocity), color_(color), rotation_(0.0f)
	, sprite_(sprite)
	, isSolid_(false), isDestroyed_(false)
{

}

GameObject::~GameObject()
{
}

void GameObject::draw(SpriteRenderer &renderer)
{
	renderer.drawSprite(sprite_, postion_, size_, rotation_, color_);
}
