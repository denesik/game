#include "GUIContainer.h"
#include "Logger.h"
#include <algorithm>


GUIContainer::GUIContainer(int _width, int _height)
{
	width = _width;
	height = _height;
	fontDefault = nullptr;
}


GUIContainer::~GUIContainer(void)
{
}

void GUIContainer::LoadContent()
{
	for (auto i = guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->LoadContent();
	}
}

void GUIContainer::Update()
{
	MouseButtonEvent buttonEvent;
	buttonEvent.button = SDL_BUTTON_LEFT;
	if(Mouse::IsButtonPress(buttonEvent))
	{
		buttonEvent.y = height - buttonEvent.y;

		for (auto i = guiObjectLists.rbegin(); i != guiObjectLists.rend(); i++)
		{
			GUIObject *guiObject = *i;

			if( HittingArea(buttonEvent.x, buttonEvent.y, guiObject->GetBoundBox()) )
			{
				guiObjectLists.remove(guiObject);
				guiObjectLists.push_back(guiObject);

				guiObject->OnMouseClick(buttonEvent.button, buttonEvent.x, buttonEvent.y);
				return;
			}
			// Список перемешался цикл нужно завершить.
		}
	}

	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->Update();
	}
}

void GUIContainer::Draw(Render *render)
{
	render->PushProjectionMatrix();

	for (auto i = guiObjectLists.begin(); i != guiObjectLists.end(); i++)
	{
		(*i)->Draw(render);
	}

	render->PopProjectionMatrix();
}

int GUIContainer::AddGUIObject(GUIObject *guiObject)
{
	guiObjectLists.push_back(guiObject);
	guiObject->SetContainer(this);

	if(guiObject->GetFont() == nullptr)
	{
		if(fontDefault == nullptr)
		{
			LOG(LOG_ERROR, "GUIContainer. Попытка установить элементу не существующий шрифт по умолчанию.");
		}
		guiObject->SetFont(fontDefault);
	}

	return 0;
}

int GUIContainer::RemoveGUIObject(GUIObject *guiObject)
{
	guiObjectLists.remove(guiObject);
	return 0;
}

void GUIContainer::Resize(int _width, int _height)
{
	width = _width;
	height = _height;

	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->Resize(width, height);
	}
}

void GUIContainer::SetTextureManager( TextureManager *_textureManager )
{
	textureManager = _textureManager;
}

TextureManager *GUIContainer::GetTextureManager()
{
	return textureManager;
}

bool GUIContainer::HittingArea(int x, int y, Rectangle2i area)
{
	return (x >= area.x && x <= area.x + area.w && y >= area.y && y <= area.y + area.h);
}

void GUIContainer::SetDefaultFont( IFont *font )
{
	if(font == nullptr)
	{
		LOG(LOG_ERROR, "GUIFontManager. Попытка установить не существующий шрифт шрифтом по умолчанию.");
		return;
	}

	IFont *oldFontDefault = fontDefault;
	fontDefault = font;

	for (auto i = guiObjectLists.begin(); i != guiObjectLists.end(); i++)
	{
		if((*i)->GetFont() == oldFontDefault || (*i)->GetFont() == nullptr)
		{
			(*i)->SetFont(fontDefault);
		}
	}

}

IFont *GUIContainer::GetDefaultFont()
{
	return fontDefault;
}

