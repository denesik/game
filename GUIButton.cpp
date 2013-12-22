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
	glColor3ub(0,0xff,0);	

	font->print(150,300,"1234567890\nМама мыла раму.");

	glLineWidth(2);
	render->DrawRectangle(boundBox);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glBindTexture(GL_TEXTURE_2D, render->GetTextureManager()->GetTexture("gui")->textureId);

	glColor4ub(0xb0,0xb0,0xb0,0xff);	
	render->DrawQuad2D(300,300,316,316);
}
