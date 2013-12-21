#ifndef EventHandler_h__
#define EventHandler_h__

#include <SDL.h>
#include <list>

class IEvent
{
public:

	virtual void OnKeyDown(SDL_Scancode key){};
	virtual void OnKeyUp(SDL_Scancode key){};
	virtual void OnKeyPress(SDL_Scancode key){};

	virtual void OnMouseButtonDown(int button, int x, int y){};
	virtual void OnMouseButtonUp(int button, int x, int y){};
	virtual void OnMouseButtonClick(int button, int x, int y){};

	virtual void Resize(int width, int height){};
};

class IEventHandler
{
public:

	virtual int Add(IEvent *event) = 0;
	virtual int Remove(IEvent *event) = 0;

	virtual void OnEvent(SDL_Event* Event) = 0;
};

class EventHandler : public IEventHandler
{
protected:
	bool keys[SDL_NUM_SCANCODES];
	bool mouseButton[5];
	std::list<IEvent *const> events;

public:
	EventHandler();
	~EventHandler();

	virtual int Add(IEvent *event);
	virtual int Remove(IEvent *event);

	virtual void OnEvent(SDL_Event *Event);
};

#endif // EventHandler_h__
