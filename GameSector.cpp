#include "GameSector.h"


GameSector::GameSector(unsigned int w, unsigned int h, unsigned int d)
{
	width = w;
	height = h;
	depth = d;
}


GameSector::~GameSector(void)
{
}

void GameSector::Generate()
{
	for (unsigned int x = 0; x < width; x++)
		for (unsigned int y = 0; y < height; y++)
			for (unsigned int z = 0; z < depth; z++)
			{
				sectorMap[x][y][z] = 1;
			}
}

void GameSector::Draw( Render *render )
{

}
