#include "Game.h"

#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "BallObject.h"
#include <tuple>
#include <stdlib.h>



Game::Game(unsigned int width, unsigned int height) :
	width_{ width },
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
	//¼ÓÔØ shader  texture
	ResourceManager::loadShader("F:/mycode/sourceCC++/learnOpengl/myBreakOut/shaders/sprite.vs", "F:/mycode/sourceCC++/learnOpengl/myBreakOut/shaders/sprite.fs", nullptr, "sprite");
	
	glm::mat4 projecton = glm::ortho(0.0f, static_cast<GLfloat>(width_), static_cast<GLfloat>(height_)
		,0.0f, -1.0f, 1.0f);

	ResourceManager::getShader("sprite").use().setInteger("sprite", 0);
	ResourceManager::getShader("sprite").SetMatrix4("projection", projecton);
	ResourceManager::getShader("sprite").use().SetVector3f("spriteColor", glm::vec3(1.0f, 0.0f, 0.0f));

	renderer_ = new SpriteRenderer(ResourceManager::getShader("sprite"));

	ResourceManager::loadTexture("F:/mycode/sourceCC++/learnOpengl/myBreakOut/textures/awesomeface.png", GL_TRUE, "face");


	//load textures
	ResourceManager::loadTexture("F:/mycode/sourceCC++/learnOpengl/myBreakOut/textures/background.png", GL_FALSE, "background");
	ResourceManager::loadTexture("F:/mycode/sourceCC++/learnOpengl/myBreakOut/textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::loadTexture("F:/mycode/sourceCC++/learnOpengl/myBreakOut/textures/block.png", GL_FALSE, "block");
	ResourceManager::loadTexture("F:/mycode/sourceCC++/learnOpengl/myBreakOut/textures/paddle.png", GL_TRUE, "player");
	ResourceManager::loadTexture("F:/mycode/sourceCC++/learnOpengl/myBreakOut/textures/awesomeface.png", GL_TRUE, "ball");

	//load level
	GameLevel level1;
	level1.load("F:/mycode/sourceCC++/learnOpengl/myBreakOut/levels/one.lvl", width_, height_ / 2.0);
	GameLevel level2;
	level2.load("F:/mycode/sourceCC++/learnOpengl/myBreakOut/levels/two.lvl", width_, height_ / 2.0);
	GameLevel level3;
	level3.load("F:/mycode/sourceCC++/learnOpengl/myBreakOut/levels/three.lvl", width_, height_ / 2.0);
	GameLevel level4;
	level4.load("F:/mycode/sourceCC++/learnOpengl/myBreakOut/levels/four.lvl", width_, height_ / 2.0);
	levels_.push_back(level1);
	levels_.push_back(level2);
	levels_.push_back(level3);
	levels_.push_back(level4);
	level_ = 0;

	//set player
	glm::vec2 size(100.0f, 20.0f);
	//float player_velocity(500.0f);
	glm::vec2 playerPos = glm::vec2(width_/2.0f - size.x/2.0f, height_ - size.y);
	player_ = new GameObject(playerPos, size, ResourceManager::getTexture("player"));

	//ball
	glm::vec2 ballPos = glm::vec2(width_/2.0f - ball_radius_, height_ - size.y - ball_radius_*2.0f);
	ball_ = new BallObject(ballPos, ball_radius_, ball_velocity_, ResourceManager::getTexture("ball"));
}

void Game::processInput(float dt)
{
	if (state_ == GameState::GAME_ACTIVE)
	{
		float velocity = player_velocity_ * dt;
		if (keys_[GLFW_KEY_A])
		{
			if (player_->postion_.x >= 0.0f)
			{
				player_->postion_.x -= velocity;
				if (ball_->isStuck_) //Çò¸úËæ°åÒÆ¶¯
				{
					ball_->postion_.x -= velocity;
				}
			}
		}
		if (keys_[GLFW_KEY_D])
		{
			if (player_->postion_.x <= width_ - player_->size_.x)
			{
				player_->postion_.x += velocity;
				if (ball_->isStuck_) //Çò¸úËæ°åÒÆ¶¯
				{
					ball_->postion_.x += velocity;
				}
			}
		}

		if (keys_[GLFW_KEY_SPACE])
		{
			ball_->isStuck_ = false;
		}
	}
}

void Game::update(float dt)
{
	ball_->move(dt, width_);
	checkCollisions();
}

void Game::render()
{
//	renderer_->drawSprite(ResourceManager::getTexture("face"), glm::vec2(200.0f, 200.0f)
//		, glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	if (state_ == GameState::GAME_ACTIVE)
	{
		//»æÖÆ±³¾°
		renderer_->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f)
			, glm::vec2(width_, height_), 0.0f);
		//»æÖÆ¹Ø¿¨
		levels_[level_].draw(*renderer_);
		//»æÖÆ½ÇÉ«
		player_->draw(*renderer_);
		//»æÖÆÇò
		ball_->draw(*renderer_);
	}
}

void Game::checkCollisions()
{
	//ÇòºÍ×©¿é¼ì²âÅö×²
	for (auto& aBrick : levels_[level_].bricks_)
	{
		if (aBrick.isDestroyed_) continue;

		Collision collision = checkCollisions(*ball_, aBrick);
		if (!std::get<0>(collision)) 
			continue;

		//·¢ÉúÁËÅö×²
		if (!aBrick.isSolid_)
		{
			aBrick.isDestroyed_ = true;
		}

		Direction dir = std::get<1>(collision);
		glm::vec2 dir_vector = std::get<2>(collision);
		if (dir == Direction::LEFT || dir == Direction::RIGHT)
		{
			ball_->velocity_.x = -ball_->velocity_.x;
			float penetration = ball_->radius_ - std::abs(dir_vector.x);
			if (dir == Direction::LEFT)
			{
				ball_->postion_.x += penetration;
			}
			else {
				ball_->postion_.x -= penetration;
			}
		}
		else {
			ball_->velocity_.y = -ball_->velocity_.y;
			float penetration = ball_->radius_ - std::abs(dir_vector.y);
			if (dir == Direction::UP)
			{
				ball_->postion_.y -= penetration;
			}
			else {
				ball_->postion_.y += penetration;
			}
		}
	}
}

Game::Collision Game::checkCollisions(BallObject& ball, GameObject& brick)
{
	//Ô²ÐÎºÍ¾ØÐÎÅö×²¼ì²â
	glm::vec2 pBrickCt = glm::vec2(brick.postion_.x + brick.size_.x/2.0f,
		brick.postion_.y + brick.size_.y/2.0f);

	glm::vec2 pBallCt = glm::vec2(ball.postion_.x + ball.radius_,
		ball.postion_.y + ball.radius_);

	glm::vec2 vDiff = pBallCt - pBrickCt;

	glm::vec2 vSize = glm::vec2(brick.size_.x/2.0f, brick.size_.y/2.0f);

	glm::vec2 vCloset = glm::clamp(vDiff, -vSize, vSize);

	glm::vec2 closetPt = vCloset + pBrickCt;

	vDiff = closetPt - pBallCt;
	if (glm::length(vDiff) < ball.radius_)
	{
		return std::make_tuple(true, vectorDirection(vDiff), vDiff);
	}
	else {
		return std::make_tuple(false, Direction::UP, glm::vec2(0.0f));
	}
}

Game::Direction Game::vectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, -1.0f),
		glm::vec2(-1.0f, 0.0f)
	};

	float max = 0.0f;
	unsigned int maxindex = -1;
	for (int i = 0; i < 4; i++)
	{
		glm::vec2 vtest = compass[i];
		float dot = glm::dot(vtest, target);
		if (dot > max)
		{
			max = dot;
			maxindex = i;
		}
	}

	return (Direction)maxindex;
}
