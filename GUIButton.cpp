#include "GUIButton.h"
#include "GUIManager.h"

GUIButton::GUIButton(int x, int y, int w, int h)
{
	boundBoxOriginal.x = x;
	boundBoxOriginal.y = y;
	boundBoxOriginal.w = w;
	boundBoxOriginal.h = h;
	text = "";
}


GUIButton::~GUIButton(void)
{
}

void GUIButton::Draw(Render *render)
{
	GUIObject::Draw(render);

	glColor3ub(0,0,0);	

	Rect bb = font->GetBoundBox(text);

	int fontX = boundBox.x + (boundBox.w - bb.w) / 2;
	int fontY = boundBox.y - bb.y + (boundBox.h - bb.h) / 2;
	font->Print(fontX,fontY,text);

/*	bb.x = fontX;
	bb.y += fontY;
	glDisable(GL_BLEND);
	render->DrawRectangle(bb);
	*/
}

void GUIButton::LoadContent()
{

	GUIObject::LoadContent();
}
