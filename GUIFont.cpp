#include "GUIFont.h"
#include <math.h>

GUIFont::GUIFont(std::string _filename, std::string _fontName, unsigned int _size)
{
	size_font = _size;
	filename = _filename;
	fontName = _fontName;
}


GUIFont::~GUIFont(void)
{
}

bool GUIFont::Generate( int width, int height )
{
	size = (unsigned int)(size_font * sqrt((float(width) / 800) * (float(height) / 600)));
	return Font::Generate();
}

void GUIFont::SetSize( unsigned int _size )
{
	size_font = _size;
}

unsigned int GUIFont::GetSize()
{
	return int(size_font);
}
