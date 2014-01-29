#ifndef GameSector_h__
#define GameSector_h__

#include "Render.h"
#include <vector>

class GameSector
{
protected:

	unsigned int width;
	unsigned int height;
	unsigned int depth;

	std::vector< std::vector< std::vector< int > > >
		sectorMap;

public:
	GameSector(unsigned int w, unsigned int h, unsigned int d);
	~GameSector(void);

	void Generate();
	void Draw(Render *render);



};


#endif // GameSector_h__