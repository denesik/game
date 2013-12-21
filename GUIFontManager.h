#ifndef GUIFontManager_h__
#define GUIFontManager_h__

#include <map>
#include <string>
#include "GUIFont.h"

class GUIFontManager
{
protected:
	std::map<std::string, GUIFont*> fontsMap;


public:
	GUIFontManager(void);
	~GUIFontManager(void);

	bool Add(std::string fontName, GUIFont *font);
	int Remove(std::string fontName);
	GUIFont *Get(std::string fontName);

	bool GenerateFonts(int width, int height);

};


#endif // FontManager_h__