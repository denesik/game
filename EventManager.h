#ifndef EventManager_h__
#define EventManager_h__

#include <SDL_events.h>
#include "Keyboard.h"
#include "Mouse.h"

class EventManager
{

public:

	static void Init();

	static void Update();

	static void OnEvent(SDL_Event* Event);
};


#endif // EventManager_h__