#ifndef GUIFont_h__
#define GUIFont_h__

#include "font.h"

class GUIFont : public Font
{
private:
	float size_font;

public:
	GUIFont(const char *_filename, unsigned int size);
	~GUIFont(void);

	void SetSize( unsigned int size );
	int GetSize();
	bool Generate(int width, int height);

};


#endif // GUIFont_h__