#ifndef GameComponent_h__
#define GameComponent_h__

#include "EventHandler.h"
#include "Render.h"

class GameComponent : public IEvent
{
public:

	GameComponent(void);
	~GameComponent(void);

	virtual bool Initialize(){return true;};
	virtual void LoadContent(){};
	virtual void Update(){};
	virtual void Draw(Render *render){};
	virtual void UnloadContent(){};
};

#endif // GameComponent_h__
