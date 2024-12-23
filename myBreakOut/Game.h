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

	typedef std::tuple<bool, Direction, glm::vec2> Collision;  //�Ƿ���ײ����ײʱ����˶��������������ĵ����

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
	unsigned int width_;			//���ܴ���0 ���δ�����һֱ��ʾ���������������Ϊ���캯������������
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

