#include "GameLevel.h"

#include <sstream>
#include "ResourceManager.h"


void GameLevel::load(const char *file, unsigned int levelWidth, unsigned int levelHight)
{
	bricks_.clear();

	unsigned int tileCode;

	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;

	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode)
			{
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
		{
			init(tileData, levelWidth, levelHight);
		}

	}

}

void GameLevel::draw(SpriteRenderer& renderer)
{
	for (auto &aBrick : bricks_)
	{
		if (!aBrick.isDestroyed_)
		{
			aBrick.draw(renderer);
		}
		
	}
}

bool GameLevel::isCompleted()
{
	for (auto &aBrick : bricks_)
	{
		if (!aBrick.isDestroyed_ && !aBrick.isSolid_)
		{
			return false;
		}
	}
	return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	unsigned int heightnum = tileData.size();
	unsigned int widthnum = tileData[0].size();

	float unit_width = levelWidth / (float)widthnum;
	float unit_height = levelHeight / (float)heightnum;

	for (int y = 0; y < heightnum; y++)
	{
		for (int x = 0; x < widthnum; x++)
		{
			int bricktype = tileData[y][x]; 
			if (bricktype == 1)  //不被摧毁的砖块
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(pos, size, ResourceManager::getTexture("block_solid"),glm::vec3(0.8f, 0.8f, 0.7f));
				obj.isSolid_ = true;
				bricks_.push_back(obj);
			}
			else if (bricktype > 1) //可以被摧毁的砖块
			{
				glm::vec3 color = getColor(bricktype);
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(pos, size ,ResourceManager::getTexture("block"), color);
				bricks_.push_back(obj);
			}
		}
	}

}

glm::vec3 GameLevel::getColor(int brickType)
{
	switch (brickType)
	{
	case 0:
		break;
	case 1:
		return glm::vec3(1.0f);
	case 2:
		return glm::vec3(0.2f, 0.6f, 1.0f);
	case 3:
		return glm::vec3(0.0f, 0.7f, 0.0f);
	case 4:
		return glm::vec3(0.8f, 0.8f, 0.4f);
	case 5:
		return glm::vec3(1.0f, 0.5f, 0.0f);
	default:
		return glm::vec3(1.0f);
	}
	return glm::vec3(1.0f);
}
