#include "GUIButton.h"
#include "GUIContainer.h"

GUIButton::GUIButton(int x, int y, int w, int h, std::string _text)
{
	text = _text;
	boundBoxOriginal.x = x;
	boundBoxOriginal.y = y;
	boundBoxOriginal.w = w;
	boundBoxOriginal.h = h;
	textX = 0;
	textY = 0;
}


GUIButton::~GUIButton(void)
{
}

void GUIButton::Draw(Render *render)
{
	GUIObject::Draw(render);

	glColor3ub(0,0,0);	

	if(text.length() > 0)
		font->Print(float(textX), float(textY), text);

/*
	glDisable(GL_BLEND);
	render->DrawRectangle(boundBox);
	*/
}

void GUIButton::LoadContent()
{
	GUIObject::LoadContent();
	ResizeText();
}

void GUIButton::SetText( std::string _text )
{
	text = _text;
	ResizeText();
}

void GUIButton::Resize( int width, int height )
{
	GUIObject::Resize(width, height);
	ResizeText();
}

void GUIButton::ResizeText()
{
	Rectangle2i bb = font->GetBoundBox(text);
	textX = boundBox.x + (boundBox.w - bb.w) / 2;
	textY = boundBox.y - bb.y + (boundBox.h - bb.h) / 2;
}

void GUIButton::OnMouseClick( int button, int x, int y )
{
	if(MouseClickEvent)
	{
		MouseClickEvent(x, y);
	}
}