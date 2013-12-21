#include "EventHandler.h"

EventHandler::EventHandler(void)
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		keys[i] = false;
	}
	for (int i = 0; i < 5; i++)
	{
		mouseButton[i] = false;
	}
}

EventHandler::~EventHandler(void)
{
}

int EventHandler::Add(IEvent *event)
{
	events.push_back(event);
	return 0;
}

int EventHandler::Remove(IEvent *event)
{
	events.remove(event);
	return 0;
}

void EventHandler::OnEvent(SDL_Event* SDLEvent) {

	for (auto i =  events.begin(); i != events.end(); ++i)
	{
		IEvent *event = *i;

		switch(SDLEvent->type) 
		{
			case SDL_KEYDOWN: 
			{
				if(keys[SDLEvent->key.keysym.scancode] == false)
					event->OnKeyPress(SDLEvent->key.keysym.scancode);

				keys[SDLEvent->key.keysym.scancode] = true;
				event->OnKeyDown(SDLEvent->key.keysym.scancode);
				//OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
				break;
			}

			case SDL_KEYUP: 
			{
				keys[SDLEvent->key.keysym.scancode] = false;
				event->OnKeyUp(SDLEvent->key.keysym.scancode);
				break;
			}

			case SDL_MOUSEMOTION: 
			{
				//OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
				break;
			}

			case SDL_MOUSEBUTTONDOWN: 
			{
				if(mouseButton[SDLEvent->button.button] == false)
					event->OnMouseButtonClick(SDLEvent->button.button, SDLEvent->button.x, SDLEvent->button.y);
				
				mouseButton[SDLEvent->button.button] = true;
				event->OnMouseButtonDown(SDLEvent->button.button, SDLEvent->button.x, SDLEvent->button.y);
				break;
			}

			case SDL_MOUSEBUTTONUP:    
			{
				mouseButton[SDLEvent->button.button] = false;
				event->OnMouseButtonUp(SDLEvent->button.button, SDLEvent->button.x, SDLEvent->button.y);
				break;
			}

			case SDL_WINDOWEVENT:
			{
				switch(SDLEvent->window.event) 
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

			default: 
			{
				//OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
				break;
			}
		}
	}
}

