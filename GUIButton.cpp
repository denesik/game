#include "GUIButton.h"


GUIButton::GUIButton(int x, int y, int w, int h)
{
	boundBox.x = x;
	boundBox.y = y;
	boundBox.w = w;
	boundBox.h = h;
}


GUIButton::~GUIButton(void)
{
}

void GUIButton::Draw(Render *render)
{
	font->print(20,200,"1234567890\nМама мыла раму.");
}
