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
		LOG(LOG_WARNING, "GUIFontManager. Попытка добавить не существующий шрифт.");
		return false;
	}
	auto f= fontsMap.find(fontName);
	if(f != fontsMap.end())
	{
		LOG(LOG_WARNING, "GUIFontManager. Шрифт " + fontName + " уже существует.");
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
		LOG(LOG_WARNING, "GUIFontManager. Шрифт " + fontName + " не найден.");
		return nullptr;
	}

	return (*f).second;
}

bool GUIFontManager::GenerateFonts(int width, int height)
{

	for(auto i = fontsMap.begin(), e = fontsMap.end(); i != e; /*пусто !!!*/ )
	{
		if ( (*i).second->Generate(width, height) )
			++i;
		else
		{
			// Шрифт не смог сформироваться, удалим его.
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
		LOG(LOG_ERROR, "GUIFontManager. Попытка установить не существующий шрифт шрифтом по умолчанию.");
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
		LOG(LOG_ERROR, "GUIFontManager. Не найден шрифт по умолчанию.");
	}
	return fontDefault;
}
