#ifndef Game_h__
#define Game_h__

#include <SDL.h>
#include "Render.h"
#include "TextureManager.h"
#include "EventHandler.h"

class Game
{
protected:

	IEventHandler *eventHandler;
	Render *render;
	TextureManager *textureManager;

	bool Running;

	const char* title;
	int width;
	int height;
	bool fullscreen;

public:
	Game(void);
	~Game(void);

	int Run();

	virtual bool Initialize();
	virtual void LoadContent(); 
	virtual void Update();
	virtual void Draw();
	virtual void UnloadContent(); 

	IEventHandler *GetEventHandler();

};


#endif // Game_h__

