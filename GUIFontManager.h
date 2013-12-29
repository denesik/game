#ifndef GUIFontManager_h__
#define GUIFontManager_h__

#include <vector>
#include <string>
#include "GUIFont.h"

class GUIFontManager
{
protected:
	std::vector<GUIFont*> fontsMap;
	GUIFont *defaultFont;

public:
	GUIFontManager(void);
	~GUIFontManager(void);

	void SetDefaultFont(GUIFont *font);
	GUIFont *GetDefaultFont();

	bool Add(GUIFont *font);
	bool Remove(std::string fontName);
	bool Remove(GUIFont *font);
	GUIFont *Get(std::string fontName);
	GUIFont *Get(GUIFont *font);

	bool GenerateFonts(int width, int height);

};


#endif // FontManager_h__