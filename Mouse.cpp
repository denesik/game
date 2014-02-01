#include "Mouse.h"


Mouse::ButtonEventState Mouse::mouseButton[5];

void Mouse::Init()
{
	ButtonEventState buttonEventState;
	buttonEventState.state = BUTTON_UP;
	buttonEventState.x = 0;
	buttonEventState.y = 0;

	for(unsigned int i = 0; i < 5; i++)
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
	for(unsigned int button = 0; button < 5; button++)
	{
		mouseButton[button].state &= (!BUTTON_PRESS);

		if((mouseButton[button].state & BUTTON_LAST_DOWN) == 0)
		{
			if((mouseButton[button].state & BUTTON_DOWN) != 0)
			{
				// ������ ���� ������ ������ ���
				mouseButton[button].state |= BUTTON_PRESS;
			}
		}

		// ������� ��������� ����� ���������� ��� ��������� ��������
		if((mouseButton[button].state & BUTTON_DOWN) != 0)
		{
			mouseButton[button].state |= BUTTON_LAST_DOWN;
		}
		else
		{
			mouseButton[button].state &= (!BUTTON_LAST_DOWN);
		}

	}
}