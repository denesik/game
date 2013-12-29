#ifndef GUIFont_h__
#define GUIFont_h__

#include "font.h"

class GUIFont : public Font
{
private:
	unsigned int size_font; 

public:
	GUIFont(std::string filename, std::string fontName, unsigned int size);
	~GUIFont(void);

	void SetSize( unsigned int size );
	unsigned int GetSize();
	bool Generate(int width, int height);

};


#endif // GUIFont_h__