#ifndef Keyboard_h__
#define Keyboard_h__

#include <SDL_events.h>


class Keyboard
{
private:

	enum KeyState
	{
		KEY_UP = 0,
		KEY_DOWN = 1,
		KEY_LAST_DOWN = 2,
		KEY_PRESS = 4,
		KEY_LOCK = 8
	};

	static unsigned int keys[SDL_NUM_SCANCODES];

public:

	static void Init();

	static void Update();

	static void KeyDown(SDL_Scancode key);
	static void KeyUp(SDL_Scancode key);
	//эмуляция нажатия клавиши
//	static void KeyPress(SDL_Scancode key, unsigned int time);

	static bool IsKeyDown(SDL_Scancode key);
	static bool IsKeyUp(SDL_Scancode key);
	static bool IsKeyPress(SDL_Scancode key);

	static void KeyLock(SDL_Scancode key);
};


#endif // Keyboard_h__