#include "Game.h"

#include "SpriteRenderer.h"
#include "ResourceManager.h"




Game::Game(unsigned int width, unsigned int height) :
	width_{ width_ },
	height_{ height },
	state_{ GameState::GAME_ACTIVE },
	keys_ {}
{

}

Game::~Game()
{
}

void Game::init()
{
	//╪сть shader  texture
	ResourceManager::loadShader("F:/mycode/sourceCC++/learnOpengl/myBreakOut/shaders/sprite.vs", "F:/mycode/sourceCC++/learnOpengl/myBreakOut/shaders/sprite.fs", nullptr, "sprite");
	
	glm::mat4 projecton = glm::ortho(0.0f, static_cast<GLfloat>(width_), static_cast<GLfloat>(height_)
		,0.0f, -1.0f, 1.0f);

	ResourceManager::getShader("sprite").use().setInteger("sprite", 0);
	ResourceManager::getShader("sprite").SetMatrix4("projection", projecton);
	
	renderer_ = new SpriteRenderer(ResourceManager::getShader("sprite"));

	ResourceManager::loadTexture("F:/mycode/sourceCC++/learnOpengl/myBreakOut/textures/awesomeface.png", GL_TRUE, "face");
}

void Game::processInput(float dt)
{

}

void Game::update(float dt)
{

}

void Game::render()
{
	renderer_->drawSprite(ResourceManager::getTexture("face"), glm::vec2(200, 200)
		, glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
