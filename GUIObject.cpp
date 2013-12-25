#include "GUIObject.h"
#include "GUIManager.h"

GUIObject::GUIObject()
{
	font = nullptr;
	fontName = "FontDefault";

	bool isVisible = true;
	bool isActive = true;
}


GUIObject::~GUIObject(void)
{
}

void GUIObject::SetFont( Font *_font )
{
	font = _font;
}

Font * GUIObject::GetFont()
{
	return font;
}

void GUIObject::SetFont( std::string _fontName )
{
	Font *f = guiManager->GetFontManager()->Get(_fontName);
	if(f != nullptr)
	{
		font = f;
		fontName = _fontName;
	}
}

void GUIObject::Draw( Render *render )
{
	glColor3ub(0xef,0xef,0xef);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	Rect r;
	render->BindTexture(windowTexture.borderTop->textureId);
	r.h = windowTexture.borderBotLeft->height;
	r.w = windowTexture.borderBotLeft->width;
	r.x = boundBox.x;
	r.y = boundBox.y;
	render->DrawQuad2D(r, *windowTexture.borderBotLeft);

	r.h = windowTexture.borderTopLeft->height;
	r.w = windowTexture.borderTopLeft->width;
	r.x = boundBox.x;
	r.y = boundBox.y + boundBox.h - r.h;
	render->DrawQuad2D(r, *windowTexture.borderTopLeft);

	r.h = windowTexture.borderBotRight->height;
	r.w = windowTexture.borderBotRight->width;
	r.x = boundBox.x + boundBox.w - r.w;
	r.y = boundBox.y;
	render->DrawQuad2D(r, *windowTexture.borderBotRight);

	r.h = windowTexture.borderTopRight->height;
	r.w = windowTexture.borderTopRight->width;
	r.x = boundBox.x + boundBox.w - r.w;
	r.y = boundBox.y + boundBox.h - r.h;
	render->DrawQuad2D(r, *windowTexture.borderTopRight);

	r.x = boundBox.x + windowTexture.borderTopLeft->width;
	r.y = boundBox.y + boundBox.h - windowTexture.borderTop->height;
	r.h = windowTexture.borderTop->height;
	r.w = boundBox.w - windowTexture.borderTopLeft->width - windowTexture.borderTopRight->width;
	render->DrawQuad2D(r, *windowTexture.borderTop);

	r.x = boundBox.x + boundBox.w - windowTexture.borderRight->width;
	r.y = boundBox.y + windowTexture.borderBotRight->height;
	r.h = boundBox.h - windowTexture.borderBotRight->height - windowTexture.borderTopRight->height;
	r.w = windowTexture.borderRight->width;
	render->DrawQuad2D(r, *windowTexture.borderRight);

	r.x = boundBox.x;
	r.y = boundBox.y + windowTexture.borderBotLeft->height;
	r.h = boundBox.h - windowTexture.borderBotLeft->height - windowTexture.borderTopLeft->height;
	r.w = windowTexture.borderLeft->width;
	render->DrawQuad2D(r, *windowTexture.borderLeft);

	r.x = boundBox.x + windowTexture.borderBotLeft->width;
	r.y = boundBox.y;
	r.h = windowTexture.borderBot->height;
	r.w = boundBox.w - windowTexture.borderBotLeft->width - windowTexture.borderBotRight->width;
	render->DrawQuad2D(r, *windowTexture.borderBot);

	r.x = boundBox.x + windowTexture.borderLeft->width;
	r.y = boundBox.y + windowTexture.borderBot->height;
	r.h = boundBox.h - windowTexture.borderBot->height - windowTexture.borderTop->height;
	r.w = boundBox.w - windowTexture.borderLeft->width - windowTexture.borderRight->width;
	render->DrawQuad2D(r, *windowTexture.body);

}

void GUIObject::LoadContent()
{
	boundBox.x = boundBoxOriginal.x;
	boundBox.y = boundBoxOriginal.y;
	boundBox.w = boundBoxOriginal.w;
	boundBox.h = boundBoxOriginal.h;

	TextureManager *textureManager = guiManager->GetTextureManager();
	windowTexture.borderTop			= textureManager->GetTexture("GUI_borderTop");
	windowTexture.borderBot			= textureManager->GetTexture("GUI_borderBot");
	windowTexture.borderLeft		= textureManager->GetTexture("GUI_borderLeft");
	windowTexture.borderRight		= textureManager->GetTexture("GUI_borderRight");
	windowTexture.borderTopLeft		= textureManager->GetTexture("GUI_borderTopLeft");
	windowTexture.borderTopRight	= textureManager->GetTexture("GUI_borderTopRight");
	windowTexture.borderBotRight	= textureManager->GetTexture("GUI_borderBotRight");
	windowTexture.borderBotLeft		= textureManager->GetTexture("GUI_borderBotLeft");
	windowTexture.body				= textureManager->GetTexture("GUI_body");

}

void GUIObject::Resize(int width, int height)
{
	float w = float(width) / 800;
	float h = float(height) / 600;

	boundBox.x = int(boundBoxOriginal.x * w);
	boundBox.y = int(boundBoxOriginal.y * h);
	boundBox.w = int(boundBoxOriginal.w * w);
	boundBox.h = int(boundBoxOriginal.h * h);
}
