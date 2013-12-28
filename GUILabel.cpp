#include "GUILabel.h"


GUILabel::GUILabel( int x, int y, std::string _text )
{
	text = _text;
	textX = x;
	textY = y;
	boundBoxOriginal.x = x;
	boundBoxOriginal.y = y;
}

GUILabel::GUILabel()
{

}


GUILabel::~GUILabel(void)
{
}

void GUILabel::Draw( Render *render )
{
	glColor3ub(0,0,0);	

	font->Print(float(textX),float(textY),text);

/*	glDisable(GL_BLEND);
	render->DrawRectangle(boundBox);*/
}

void GUILabel::Resize( int width, int height )
{
	float w = float(width) / 800;
	float h = float(height) / 600;

	textX = int(boundBoxOriginal.x * w);
	textY = int(boundBoxOriginal.y * h);

	ResizeText();
}

void GUILabel::SetText( std::string _text )
{
	text = _text;
	Rectangle2i bb = font->GetBoundBox(text);

	ResizeText();
}

void GUILabel::LoadContent()
{
	ResizeText();
}

void GUILabel::ResizeText()
{
	Rectangle2i bb = font->GetBoundBox(text);
	boundBox.x = textX;
	boundBox.y = textY + bb.y;
	boundBox.w = bb.w;
	boundBox.h = bb.h;
}
