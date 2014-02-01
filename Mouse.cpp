#include "Mouse.h"


Mouse::ButtonEventState Mouse::mouseButton[6];

void Mouse::Init()
{
	ButtonEventState buttonEventState;
	buttonEventState.state = BUTTON_UP;
	buttonEventState.x = 0;
	buttonEventState.y = 0;

	for(unsigned int i = 0; i < 6; i++)
	{
		mouseButton[i] = buttonEventState;
	}
}

void Mouse::ButtonDown( MouseButtonEvent button )
{
	mouseButton[button.button].state |= BUTTON_DOWN;
	mouseButton[button.button].x = button.x;
	mouseButton[button.button].y = button.y;
}

void Mouse::ButtonUp( MouseButtonEvent button )
{
	mouseButton[button.button].state = 10;
	mouseButton[button.button].state = BUTTON_UP;
	mouseButton[button.button].x = button.x;
	mouseButton[button.button].y = button.y;
}

bool Mouse::IsButtonDown( MouseButtonEvent &button )
{
	if((mouseButton[button.button].state & BUTTON_DOWN) != 0)
	{
		button.x = mouseButton[button.button].x;
		button.y = mouseButton[button.button].y;
		return true;
	}

	return false;
}

bool Mouse::IsButtonUp( MouseButtonEvent &button )
{
	if((mouseButton[button.button].state & BUTTON_DOWN) == 0)
	{
		button.x = mouseButton[button.button].x;
		button.y = mouseButton[button.button].y;
		return true;
	}

	return false;
}

bool Mouse::IsButtonPress( MouseButtonEvent &button )
{
	if((mouseButton[button.button].state & BUTTON_PRESS) != 0)
	{
		button.x = mouseButton[button.button].x;
		button.y = mouseButton[button.button].y;
		return true;
	}

	return false;
}

void Mouse::ButtonLock( unsigned int button )
{

}


void Mouse::Update()
{
	for(unsigned int button = 0; button < 6; button++)
	{
		mouseButton[button].state &= (~BUTTON_PRESS);

		unsigned int test = ~4;
		test &= 1;
		test;

		if((mouseButton[button].state & BUTTON_LAST_DOWN) == 0)
		{
			if((mouseButton[button].state & BUTTON_DOWN) != 0)
			{
				// Кнопка была нажата только что
				mouseButton[button].state |= BUTTON_PRESS;
			}
		}

		// Текущее состояние стало предыдущим для следующей итерации
		if((mouseButton[button].state & BUTTON_DOWN) != 0)
		{
			mouseButton[button].state |= BUTTON_LAST_DOWN;
		}
		else
		{
			mouseButton[button].state &= (~BUTTON_LAST_DOWN);
		}

	}
}