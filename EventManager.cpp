#include "EventManager.h"


void EventManager::OnEvent( SDL_Event* event )
{
	MouseButtonEvent buttonEvent;

	switch(event->type) 
	{
	case SDL_KEYDOWN: 
		{
			Keyboard::KeyDown(event->key.keysym.scancode);

			//OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);

			break;
		}

	case SDL_KEYUP: 
		{
			Keyboard::KeyUp(event->key.keysym.scancode);

			break;
		}

	case SDL_MOUSEMOTION: 
		{
			//OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
			break;
		}

	case SDL_MOUSEBUTTONDOWN: 
		{
			buttonEvent.button = event->button.button;
			buttonEvent.x = event->button.x;
			buttonEvent.y = event->button.y;

			Mouse::ButtonDown(buttonEvent);

			break;
		}

	case SDL_MOUSEBUTTONUP:    
		{
			buttonEvent.button = event->button.button;
			buttonEvent.x = event->button.x;
			buttonEvent.y = event->button.y;

			Mouse::ButtonUp(buttonEvent);
			break;
		}

/*	case SDL_WINDOWEVENT:
		{
			switch(event->window.event) 
			{
			case SDL_WINDOWEVENT_RESIZED: 
				{
					event->Resize(SDLEvent->window.data1, SDLEvent->window.data2);
					break;
				}
			default:
				{
					break;
				}
			}
		}
		*/
	default: 
		{
			//OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
			break;
		}
	}
	
}

void EventManager::Init()
{
	Keyboard::Init();
	Mouse::Init();
}

void EventManager::Update()
{
	Keyboard::Update();
	Mouse::Update();
}
