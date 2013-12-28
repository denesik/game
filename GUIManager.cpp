#include "GUIManager.h"


GUIManager::GUIManager(int _width, int _height)
{
	width = _width;
	height = _height;
}


GUIManager::~GUIManager(void)
{
}


bool GUIManager::Initialize()
{

	fontManager->GenerateFonts(width, height);
	NameDefaultFont = fontManager->GetNameDefaultFont();
	fontDefault = fontManager->GetDefaultFont();

	for (auto i = guiObjectLists.begin(); i != guiObjectLists.end(); i++)
	{
		if((*i)->font == nullptr)
		{
			(*i)->SetFont(fontDefault);
			(*i)->fontName = NameDefaultFont;
		}
	}
	
	return true;
}

void GUIManager::LoadContent()
{

	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
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
/*
int GUIManager::Cleanup()
{
	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->Cleanup();
	}
	return 0;
}
*/

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
	fontManager->GenerateFonts(width, height);

//	NameDefaultFont = fontManager->GetNameDefaultFont();
//	fontDefault = fontManager->GetDefaultFont();

	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		if( (*i)->GetFont() == nullptr )
		{
			(*i)->fontName = NameDefaultFont;
			(*i)->SetFont(fontDefault);
		}
		(*i)->Resize(width, height);
	}
}

void GUIManager::SetFontManager( GUIFontManager *_fontManager )
{
	fontManager = _fontManager;
}

GUIFontManager *GUIManager::GetFontManager()
{
	return fontManager;
}

void GUIManager::SetTextureManager( TextureManager *_textureManager )
{
	textureManager = _textureManager;
}

TextureManager * GUIManager::GetTextureManager()
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

