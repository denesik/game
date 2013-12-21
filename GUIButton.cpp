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

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glBindTexture(GL_TEXTURE_2D, render->GetTextureManager()->Get("gui"));

	glColor4ub(0xff,0xff,0xff,0xff);	
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex2f(300,416);
		glTexCoord2d(0,1); glVertex2f(300,300);
		glTexCoord2d(1,1); glVertex2f(416,300);
		glTexCoord2d(1,0); glVertex2f(416,416);
	glEnd();
}
