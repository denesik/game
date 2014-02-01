#ifndef Game_h__
#define Game_h__

#include <SDL.h>
#include "Render.h"
#include "TextureManager.h"
//#include "EventHandler.h"
#include "EventManager.h"

class Game
{
protected:

	Render *render;
	TextureManager *textureManager;

	bool Running;

	const char* title;
	unsigned int width;
	unsigned int height;
	bool fullscreen;

public:
	Game(void);
	~Game(void);

	int Run();

	virtual bool Initialize();
	virtual void LoadContent(); 
	virtual void Update();
	virtual void Draw();
	virtual void ResizeWindow(unsigned int width, unsigned int height);
	virtual void UnloadContent(); 

};


#endif // Game_h__

