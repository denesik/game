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
		LOG(LOG_WARNING, "GUIFontManager. ������� �������� �� ������������ �����.");
		return false;
	}

	for (auto i = fontsMap.begin(); i != fontsMap.end(); i++)
	{
		if( (*i) == font )
		{
			LOG(LOG_WARNING, "GUIFontManager. ����� " + font->GetFontName() + " ��� ����������.");
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

	LOG(LOG_WARNING, "GUIFontManager. ������� ������� �� ��������� ����� " + fontName + ".");
	return false;
}

bool GUIFontManager::Remove( GUIFont *font )
{
	if( font == nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. ������� ������� �������������� �����.");
		return false;
	}

	auto i = std::remove(fontsMap.begin(), fontsMap.end(), font);
	if(i == fontsMap.end())
	{
		LOG(LOG_WARNING, "GUIFontManager. ������� ������� �� ��������� ����� " + font->GetFontName() + ".");
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

	LOG(LOG_WARNING, "GUIFontManager. ����� " + fontName + " �� ������.");
	return nullptr;
}

GUIFont *GUIFontManager::Get( GUIFont *font )
{
	if( font == nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. ������� ��������� � ��������������� ������.");
		return false;
	}

	for (auto i = fontsMap.begin(); i != fontsMap.end(); i++)
	{
		if( (*i) == font )
		{
			return (*i);
		}
	}

	LOG(LOG_WARNING, "GUIFontManager. ����� " + font->GetFontName() + " �� ������.");
	return nullptr;
}

bool GUIFontManager::GenerateFonts(int width, int height)
{

	if(defaultFont == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. ��������� ������. ����������� ����� �� ���������.");
		return false;
	}

	if(!defaultFont->Generate(width ,height))
	{
		LOG(LOG_ERROR, "GUIFontManager. ���������� ������������� ����� �� ���������.");
		return false;
	}

	for(auto i = fontsMap.begin(), e = fontsMap.end(); i != e; /*����� !!!*/ )
	{
		if ( (*i)->Generate(width, height) )
			++i;
		else
		{
			// ����� �� ���� ��������������, ������ ���.
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
		LOG(LOG_ERROR, "GUIFontManager. ������� ���������� �� ������������ ����� ������� �� ���������.");
		return;
	}
	defaultFont = font;
}

GUIFont * GUIFontManager::GetDefaultFont()
{
	if(defaultFont == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. �� ������ ����� �� ���������.");
		return nullptr;
	}
	return defaultFont;
}
