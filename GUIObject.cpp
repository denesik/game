#include "GUIObject.h"
#include "GUIManager.h"

GUIObject::GUIObject()
{
	font = nullptr;
	fontName = "FontDefault";
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