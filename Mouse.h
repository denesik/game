#ifndef Mouse_h__
#define Mouse_h__

#include <SDL_events.h>


struct MouseButtonEvent
{
	unsigned int button;
	int x, y;
};

class Mouse
{
private:

	enum ButtonState
	{
		BUTTON_UP = 0,
		BUTTON_DOWN = 1,
		BUTTON_LAST_DOWN = 2,
		BUTTON_PRESS = 4,
		BUTTON_LOCK = 8
	};

	struct ButtonEventState
	{
		unsigned int state;
		int x, y;
	};

	static ButtonEventState mouseButton[6];

public:

	static void Init();

	static void Update();

	static void ButtonDown(MouseButtonEvent button);
	static void ButtonUp(MouseButtonEvent button);
	//эмуляция нажатия кнопки
	//	static void ButtonPress(ButtonEvent button, unsigned int time);

	static bool IsButtonDown(MouseButtonEvent &button);
	static bool IsButtonUp(MouseButtonEvent &button);
	static bool IsButtonPress(MouseButtonEvent &button);

	static void ButtonLock(unsigned int button);

};


#endif // Mouse_h__