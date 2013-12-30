#include "FontFactory.h"
#include "Logger.h"
#include "Font.h"


IFontFactory *IFontFactory::p_instance = 0;
IFontFactoryDestroyer IFontFactory::destroyer;

IFontFactoryDestroyer::~IFontFactoryDestroyer() 
{   
	delete p_instance; 
}

void IFontFactoryDestroyer::initialize( IFontFactory* p ) 
{
	p_instance = p; 
}

FontTTFFactory::FontTTFFactory()
{

}

FontTTFFactory::~FontTTFFactory()
{

}

IFontFactory &FontTTFFactory::getInstance()
{
	if(!p_instance)     
	{
		p_instance = new FontTTFFactory();
		destroyer.initialize( p_instance);    
	}
	return *p_instance;
}


IFont *FontTTFFactory::CreateFont( std::string fileName, std::string fontName, unsigned int size )
{
	IFont *font = GetFont(fontName);
	if(font != nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. Шрифт " + fontName + " уже существует.");
		return font;
	}

	font = new FontTTF(fileName, fontName, size);
	font->Initialize();
	fontsVector.push_back(font);
	return font;
}

void FontTTFFactory::CleanUp()
{
	for (auto i = fontsVector.begin(); i != fontsVector.end(); i++)
	{
		delete (*i);
	}
}

bool FontTTFFactory::RemoveFont( std::string fontName )
{
	for (auto i = fontsVector.begin(); i != fontsVector.end(); i++)
	{
		if( (*i)->GetFontName() == fontName )
		{
			fontsVector.erase(i);
			return true;
		}
	}

	LOG(LOG_WARNING, "GUIFontManager. Попытка удалить не найденный шрифт " + fontName + ".");
	return false;
}

IFont *FontTTFFactory::GetFont( std::string fontName )
{
	for (auto i = fontsVector.begin(); i != fontsVector.end(); i++)
	{
		if( (*i)->GetFontName() == fontName )
		{
			return (*i);
		}
	}

	return nullptr;
}
