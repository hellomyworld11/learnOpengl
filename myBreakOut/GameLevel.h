#pragma once
#include "GameObject.h"
#include <vector>
#include <fstream>

class GameLevel
{
public:
	GameLevel()=default;

	~GameLevel()=default;

	void load(const char *file, unsigned int levelWidth, unsigned int levelHight);

	void draw(SpriteRenderer& renderer);

	bool isCompleted();
public:
	std::vector<GameObject> bricks_;
private:
	void init(std::vector<std::vector<unsigned int>> tileData,
		unsigned int levelWidth, unsigned int levelHeight);
};

