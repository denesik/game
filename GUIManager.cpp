#include "GUIManager.h"
#include "Logger.h"
#include <algorithm>


GUIManager::GUIManager(int _width, int _height)
{
	width = _width;
	height = _height;
	fontDefault = nullptr;
}


GUIManager::~GUIManager(void)
{
}


bool GUIManager::Initialize()
{

	return true;
}

void GUIManager::LoadContent()
{
	for (auto i = guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->LoadContent();
	}
}


void GUIManager::Update()
{
	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->Update();
	}
}

void GUIManager::Draw(Render *render)
{
	render->PushProjectionMatrix();

	for (auto i = guiObjectLists.begin(); i != guiObjectLists.end(); i++)
	{
		(*i)->Draw(render);
	}

	render->PopProjectionMatrix();
}

int GUIManager::AddGUIObject(GUIObject *guiObject)
{
	guiObjectLists.push_back(guiObject);

	if(guiObject->font == nullptr)
	{
		if(fontDefault == nullptr)
		{
			LOG(LOG_ERROR, "GUIManager. Попытка установить не существующий шрифт по умолчанию.");
		}
		guiObject->SetFont(fontDefault);
	}
	else
	{
		AddFont(guiObject->font);
	}

	guiObject->guiManager = this;
	return 0;
}

int GUIManager::RemoveGUIObject(GUIObject *guiObject)
{
	guiObjectLists.remove(guiObject);
	return 0;
}

void GUIManager::Resize(int _width, int _height)
{
	width = _width;
	height = _height;
	GenerateFonts(width, height);

	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		if( (*i)->GetFont() == nullptr )
		{
			(*i)->SetFont(fontDefault);
		}
		(*i)->Resize(width, height);
	}
}

void GUIManager::SetTextureManager( TextureManager *_textureManager )
{
	textureManager = _textureManager;
}

TextureManager *GUIManager::GetTextureManager()
{
	return textureManager;
}

void GUIManager::OnMouseButtonClick( int button, int x, int y )
{
	y = height - y;
	for (auto i = guiObjectLists.rbegin(); i != guiObjectLists.rend(); i++)
	{
		GUIObject *guiObject = *i;

		if( HittingArea(x, y, guiObject->boundBox) )
		{
			guiObjectLists.remove(guiObject);
			guiObjectLists.push_back(guiObject);

			guiObject->OnMouseClick(button, x, y);
			return;
		}
		// Список перемешался цикл нужно завершить.
	}
}

bool GUIManager::HittingArea(int x, int y, Rectangle2i area)
{
	return (x >= area.x && x <= area.x + area.w && y >= area.y && y <= area.y + area.h);
}

void GUIManager::SetDefaultFont( IFont *font )
{

	if(font == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. Попытка установить не существующий шрифт шрифтом по умолчанию.");
		return;
	}
	IFont *oldFontDefault = fontDefault;
	fontDefault = font;

	fontDefault->Generate(width, height);	

	for (auto i = guiObjectLists.begin(); i != guiObjectLists.end(); i++)
	{
		if((*i)->GetFont() == nullptr || (*i)->GetFont() == oldFontDefault)
		{
			(*i)->SetFont(fontDefault);
		}
	}

}

IFont *GUIManager::GetDefaultFont()
{
	if(fontDefault == nullptr)
	{
		LOG(LOG_WARNING, "GUIFontManager. Не найден шрифт по умолчанию.");
		return nullptr;
	}
	return fontDefault;
}

bool GUIManager::AddFont( IFont *font )
{
	if(font == nullptr)
	{
		return false;
	}

	for (auto i = fontsVector.begin(); i != fontsVector.end(); i++)
	{
		if( (*i) == font )
		{
			return false;
		}
	}

	font->Generate(width, height);	
	fontsVector.push_back(font);
	return true;
}

bool GUIManager::RemoveFont( IFont *font )
{
	if( font == nullptr)
	{
		return false;
	}

	auto i = std::remove(fontsVector.begin(), fontsVector.end(), font);
	if(i == fontsVector.end())
	{
		return false;
	}
	fontsVector.erase(i, fontsVector.end());
	return true;
}

bool GUIManager::GenerateFonts( int width, int height )
{
	if(fontDefault == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. Генерация шрифта. Отсутствует шрифт по умолчанию.");
		return false;
	}

	if(!fontDefault->Generate(width ,height))
	{
		LOG(LOG_ERROR, "GUIFontManager. Невозможно сгенерировать шрифт по умолчанию.");
		return false;
	}

	for(auto i = fontsVector.begin(), e = fontsVector.end(); i != e; /*пусто !!!*/ )
	{
		if ( (*i)->Generate(width, height) )
			++i;
		else
		{
			// Шрифт не смог сформироваться, удалим его.
			fontsVector.erase(i++);
		}
	}

	return true;
}

