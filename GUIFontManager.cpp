#include "GUIFontManager.h"
#include "Logger.h"


GUIFontManager::GUIFontManager(void)
{
	NameDefaultFont = "FontDefault";
}


GUIFontManager::~GUIFontManager(void)
{

}

bool GUIFontManager::Add( std::string fontName, GUIFont *font )
{
	if(font == nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. ������� �������� �� ������������ �����.");
		return false;
	}
	auto f= fontsMap.find(fontName);
	if(f != fontsMap.end())
	{
		LOG(LOG_WARNING, "GUIFontManager. ����� " + fontName + " ��� ����������.");
		return false;
	}
	fontsMap[fontName] = font;
	return true;
}

int GUIFontManager::Remove( std::string fontName )
{
	return fontsMap.erase(fontName);
}

GUIFont * GUIFontManager::Get( std::string fontName )
{
	auto f = fontsMap.find(fontName);
	if(f == fontsMap.end())
	{
		LOG(LOG_WARNING, "GUIFontManager. ����� " + fontName + " �� ������.");
		return nullptr;
	}

	return (*f).second;
}

bool GUIFontManager::GenerateFonts(int width, int height)
{

	for(auto i = fontsMap.begin(), e = fontsMap.end(); i != e; /*����� !!!*/ )
	{
		if ( (*i).second->Generate(width, height) )
			++i;
		else
		{
			// ����� �� ���� ��������������, ������ ���.
			delete (*i).second;
			(*i).second = nullptr;
			fontsMap.erase(i++);
		}
	}
	
	return true;
}

void GUIFontManager::SetDefaultFont( GUIFont *font )
{
	if(font == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. ������� ���������� �� ������������ ����� ������� �� ���������.");
		return;
	}
	Add(NameDefaultFont, font);
}

std::string GUIFontManager::GetNameDefaultFont()
{
	return NameDefaultFont;
}

GUIFont * GUIFontManager::GetDefaultFont()
{
	GUIFont *fontDefault = Get(NameDefaultFont);
	if(fontDefault == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. �� ������ ����� �� ���������.");
	}
	return fontDefault;
}
