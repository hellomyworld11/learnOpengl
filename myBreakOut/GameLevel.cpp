#include "GameLevel.h"




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
		//	std::istringstream sstream(line);

		}
	}

}
