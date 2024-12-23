#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameLevel.h"

const unsigned int keynum = 1024;

class SpriteRenderer;
class BallObject;

class Game
{
public:
	enum class GameState {
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

	enum class Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	typedef std::tuple<bool, Direction, glm::vec2> Collision;  //是否碰撞，碰撞时球的运动方向，最近点和球心点距离

	Game(unsigned int width, unsigned int height);

	~Game();

	void init();

	void processInput(float dt);

	void update(float dt);

	void render();

	void setKey(int index, bool bPress = true) { keys_[index] = bPress; }

	void checkCollisions();

	Collision checkCollisions(BallObject& ball, GameObject& brick);

	Direction vectorDirection(glm::vec2 target);

	void resetLevel();

	void resetPlayer();
private:
	GameState state_;
	unsigned int width_;			//不能传入0 传参错误导致一直显示不出结果，就是因为构造函数传的是自身
	unsigned int height_;
	bool	keys_[keynum];

	float player_velocity_ = (500.0f);
	glm::vec2 ball_velocity_ =  glm::vec2(100.0f, -350.0f);
	const float ball_radius_ = 12.5;	

	std::vector<GameLevel> levels_;
	unsigned int level_;

	SpriteRenderer* renderer_ = nullptr;

	GameObject *player_ = nullptr;

	BallObject *ball_ = nullptr;
};

