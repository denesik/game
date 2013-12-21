#include "GUIFont.h"
#include <math.h>

GUIFont::GUIFont(const char *_filename, unsigned int _size)
{
	size_font = _size;
	filename = _filename;
}


GUIFont::~GUIFont(void)
{
}

bool GUIFont::Generate( int width, int height )
{
	size = size_font * sqrt((float(width) / 800) * (float(height) / 600));
	return Font::Generate();
}

void GUIFont::SetSize( unsigned int _size )
{
	size_font = _size;
}

int GUIFont::GetSize()
{
	return size_font;
}
