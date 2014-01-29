#ifndef Cube_h__
#define Cube_h__

#include "Render.h"
#include "TextureManager.h"

class Block
{
protected:

	//static const unsigned int size = 10;
	Texture texture;


public:
	Block(void);
	~Block(void);

	void Draw(Render *render);
};


#endif // Cube_h__