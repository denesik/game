#ifndef Game_h__
#define Game_h__

#include <SDL.h>
#include "GameComponent.h"
#include "GameComponentManager.h"
#include "Render.h"
#include "TextureManager.h"

class Game
{
protected:

	IEventHandler *eventHandler;
	GameComponentManager *gameComponentHandler;
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
	int AddGameComponent(GameComponent *gameComponent);

};


#endif // Game_h__

