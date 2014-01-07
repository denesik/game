#ifndef GameComponentHandler_h__
#define GameComponentHandler_h__

#include "GameComponent.h"
#include <list>
#include <SDL_events.h>

class GameComponentManager
{
protected:
	std::list<GameComponent *const> gameComponents;

public:
	GameComponentManager(void);
	~GameComponentManager(void);

	virtual int Add(GameComponent *gameComponent);
	virtual int Remove(GameComponent *gameComponent);

	virtual bool Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw(Render *render);
	virtual void UnloadContent();
};

#endif // GameComponentHandler_h__