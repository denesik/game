#include "GUIButton.h"
#include "GUIManager.h"

GUIButton::GUIButton(int x, int y, int w, int h)
{
	boundBoxOriginal.x = x;
	boundBoxOriginal.y = y;
	boundBoxOriginal.w = w;
	boundBoxOriginal.h = h;
}


GUIButton::~GUIButton(void)
{
}

void GUIButton::Draw(Render *render)
{
	GUIObject::Draw(render);
}

void GUIButton::LoadContent()
{

	GUIObject::LoadContent();
}
