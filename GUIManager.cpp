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
	fontDefault = fontManager->Get("FontDefault");

	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		if((*i)->font == nullptr)
		{
			(*i)->SetFont(fontDefault);
			(*i)->fontName = "FontDefault";
		}
	}
	
	return true;
}
/*
int GUIManager::Update()
{
	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->Update();
	}
	return 0;
}

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

	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
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

void GUIManager::OnMouseButtonClick( int button, int x, int y )
{
	for (auto i =  guiObjectLists.begin(); i != guiObjectLists.end(); ++i)
	{
		(*i)->OnClick();
	}
}

void GUIManager::Resize(int width, int height)
{
	fontManager->GenerateFonts(width, height);
}

void GUIManager::SetFontManager( GUIFontManager *_fontManager )
{
	fontManager = _fontManager;
}

GUIFontManager *GUIManager::GetFontManager()
{
	return fontManager;
}
