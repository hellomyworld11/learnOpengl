#include "GameLevel.h"

#include <sstream>



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

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	unsigned int heightnum = tileData.size();
	unsigned int widthnum = tileData[0].size();

	float unit_width = levelWidth / (float)widthnum;
	float unit_height = levelHeight / (float)heightnum;



}
