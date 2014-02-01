#include "Keyboard.h"

unsigned int Keyboard::keys[SDL_NUM_SCANCODES];

void Keyboard::Init()
{
	for(unsigned int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		keys[i] = KEY_UP;
	}
}

void Keyboard::KeyDown( SDL_Scancode key )
{

	keys[key] |= KEY_DOWN;

}

void Keyboard::KeyUp( SDL_Scancode key )
{
	keys[key] = KEY_UP;
	
}
/*
void Keyboard::KeyPress( SDL_Scancode key )
{
	keys[key] |= KEY_PRESS;
}
*/
bool Keyboard::IsKeyDown( SDL_Scancode key )
{
	if((keys[key] & KEY_DOWN) != 0)
		return true;
	
	return false;
}

bool Keyboard::IsKeyUp( SDL_Scancode key )
{
	if((keys[key] & KEY_DOWN) == 0)
		return true;

	return false;
}

bool Keyboard::IsKeyPress( SDL_Scancode key )
{
	if((keys[key] & KEY_PRESS) != 0)
		return true;

	return false;
}

void Keyboard::KeyLock( SDL_Scancode key )
{

}

void Keyboard::Update()
{

	for(unsigned int key = 0; key < SDL_NUM_SCANCODES; key++)
	{
		keys[key] &= (!KEY_PRESS);

		if((keys[key] & KEY_LAST_DOWN) == 0)
		{
			if((keys[key] & KEY_DOWN) != 0)
			{
				// Кнопка была нажата только что
				keys[key] |= KEY_PRESS;
			}
		}

		// Текущее состояние стало предыдущим для следующей итерации
		if((keys[key] & KEY_DOWN) != 0)
		{
			keys[key] |= KEY_LAST_DOWN;
		}
		else
		{
			keys[key] &= (!KEY_LAST_DOWN);
		}

	}

}

