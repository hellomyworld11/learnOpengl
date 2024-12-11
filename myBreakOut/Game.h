#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
const unsigned int keynum = 1024;

class SpriteRenderer;

class Game
{
public:
	enum class GameState {
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

	Game(unsigned int width, unsigned int height);

	~Game();

	void init();

	void processInput(float dt);

	void update(float dt);

	void render();

	void setKey(int index, bool bPress = true) { keys_[index] = bPress; }
private:
	GameState state_;
	unsigned int width_;
	unsigned int height_;
	bool	keys_[keynum];

	SpriteRenderer* renderer_ = nullptr;
};

