#include "GUIFontManager.h"


GUIFontManager::GUIFontManager(void)
{

}


GUIFontManager::~GUIFontManager(void)
{

}

bool GUIFontManager::Add( std::string fontName, GUIFont *font )
{
	if(font == nullptr)
		return false;

	auto f= fontsMap.find(fontName);
	if(f != fontsMap.end())
		return false;

	fontsMap[fontName] = font;
	return true;
}

int GUIFontManager::Remove( std::string fontName )
{
	return fontsMap.erase(fontName);
}

GUIFont * GUIFontManager::Get( std::string fontName )
{
	auto f= fontsMap.find(fontName);
	if(f == fontsMap.end())
		return nullptr;

	return (*f).second;
}

bool GUIFontManager::GenerateFonts(int width, int height)
{
	
	for (auto i = fontsMap.begin(); i != fontsMap.end(); i++)
	{
		if(i == fontsMap.end())
			return false;
		(*i).second->Generate(width, height);
	}
	
	return true;
}
