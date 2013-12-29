#include "GUIFontManager.h"
#include "Logger.h"
#include <algorithm>


GUIFontManager::GUIFontManager(void)
{
	defaultFont = nullptr;
}


GUIFontManager::~GUIFontManager(void)
{

}

bool GUIFontManager::Add( GUIFont *font )
{
	if(font == nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. Попытка добавить не существующий шрифт.");
		return false;
	}

	for (auto i = fontsMap.begin(); i != fontsMap.end(); i++)
	{
		if( (*i) == font )
		{
			LOG(LOG_WARNING, "GUIFontManager. Шрифт " + font->GetFontName() + " уже существует.");
			return false;
		}
	}

	fontsMap.push_back(font);
	return true;
}

bool GUIFontManager::Remove( std::string fontName )
{
	for (auto i = fontsMap.begin(); i != fontsMap.end(); i++)
	{
		if( (*i)->GetFontName() == fontName )
		{
			fontsMap.erase(i);
			return true;
		}
	}

	LOG(LOG_WARNING, "GUIFontManager. Попытка удалить не найденный шрифт " + fontName + ".");
	return false;
}

bool GUIFontManager::Remove( GUIFont *font )
{
	if( font == nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. Попытка удалить несуществующий шрифт.");
		return false;
	}

	auto i = std::remove(fontsMap.begin(), fontsMap.end(), font);
	if(i == fontsMap.end())
	{
		LOG(LOG_WARNING, "GUIFontManager. Попытка удалить не найденный шрифт " + font->GetFontName() + ".");
		return false;
	}
	fontsMap.erase(i, fontsMap.end());
	return true;
}

GUIFont *GUIFontManager::Get( std::string fontName )
{
	for (auto i = fontsMap.begin(); i != fontsMap.end(); i++)
	{
		if( (*i)->GetFontName() == fontName )
		{
			return (*i);
		}
	}

	LOG(LOG_WARNING, "GUIFontManager. Шрифт " + fontName + " не найден.");
	return nullptr;
}

GUIFont *GUIFontManager::Get( GUIFont *font )
{
	if( font == nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. Попытка обращения к несуществующему шрифту.");
		return false;
	}

	for (auto i = fontsMap.begin(); i != fontsMap.end(); i++)
	{
		if( (*i) == font )
		{
			return (*i);
		}
	}

	LOG(LOG_WARNING, "GUIFontManager. Шрифт " + font->GetFontName() + " не найден.");
	return nullptr;
}

bool GUIFontManager::GenerateFonts(int width, int height)
{

	if(defaultFont == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. Генерация шрифта. Отсутствует шрифт по умолчанию.");
		return false;
	}

	if(!defaultFont->Generate(width ,height))
	{
		LOG(LOG_ERROR, "GUIFontManager. Невозможно сгенерировать шрифт по умолчанию.");
		return false;
	}

	for(auto i = fontsMap.begin(), e = fontsMap.end(); i != e; /*пусто !!!*/ )
	{
		if ( (*i)->Generate(width, height) )
			++i;
		else
		{
			// Шрифт не смог сформироваться, удалим его.
			delete (*i);
			(*i) = nullptr;
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
	defaultFont = font;
}

GUIFont * GUIFontManager::GetDefaultFont()
{
	if(defaultFont == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. Не найден шрифт по умолчанию.");
		return nullptr;
	}
	return defaultFont;
}
