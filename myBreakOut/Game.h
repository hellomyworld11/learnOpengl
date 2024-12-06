#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
const unsigned int keynum = 1024;

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
private:
	GameState state_;
	unsigned int width_;
	unsigned int height_;
	bool	keys_[keynum];
};

