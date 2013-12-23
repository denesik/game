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
	glColor3ub(0,0,0xff);	
	font->print(150,300,"1234567890\nМама мыла раму.");

	glLineWidth(2);
	render->DrawRectangle(boundBox);

}
